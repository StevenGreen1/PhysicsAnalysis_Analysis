#include "CouplingAnalysis.h"

//============================================================================

CouplingAnalysis::CouplingAnalysis() : 
    m_NumberUniqueAlpha4(0),
    m_NumberUniqueAlpha5(0)
{
    this->LoadXml();
    this->AnalyseSingleEvent(1);
    this->AnalyseSingleEvent(2);
    this->AnalyseSingleEvent(3);
    this->AnalyseSingleEvent(4);
    this->AnalyseSingleEvent(5);
}

//============================================================================

CouplingAnalysis::~CouplingAnalysis()
{
}

//============================================================================

void CouplingAnalysis::LoadXml()
{
    std::string process("ee_nunuww_nunuqqqq");
    std::string energy("1400");

    for (int i = -2; i < 3; i++)
    {
        for (int j = -2; j < 3; j++)
        {
            const float alpha4(i * 0.05);
            const float alpha5(j * 0.05);
            std::cout << "Loading : (Alpha4,Alpha5) = (" << this->AlphasToString(alpha4) << "," << this->AlphasToString(alpha5) << ")" << std::endl;
            this->LoadIndividualXml(process,energy,alpha4,alpha5);
        }
    }

    std::sort(m_Alpha4Vector.begin(), m_Alpha4Vector.end());
    std::sort(m_Alpha5Vector.begin(), m_Alpha5Vector.end());
}

//============================================================================

void CouplingAnalysis::LoadIndividualXml(std::string process, std::string energy, const float alpha4, const float alpha5)
{
    std::string pathToResults("/var/clus/usera/sg568/PhysicsAnalysis/Generator/ASCIIConverter/");
    std::string fileName(pathToResults + "Reweighting_" + process + "_" + energy + "GeV_Alpha4_" + this->AlphasToString(alpha4) + "_Alpha5_" + this->AlphasToString(alpha5) + ".xml");

    TiXmlDocument *pTiXmlDocument = new TiXmlDocument();

    if(!pTiXmlDocument->LoadFile(fileName.c_str()))
    {
        std::cerr << pTiXmlDocument->ErrorDesc() << std::endl;
    }

    TiXmlElement* pHeadTiXmlElement = pTiXmlDocument->FirstChildElement();

    if(pHeadTiXmlElement == NULL)
    {
        std::cerr << "Failed to load file: No root element." << std::endl;
        pTiXmlDocument->Clear();
    }

    for(TiXmlElement* pTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pTiXmlElement != NULL; pTiXmlElement = pTiXmlElement->NextSiblingElement())
    {
        std::string process(pTiXmlElement->Attribute("Process"));
        std::string energy(pTiXmlElement->Attribute("Energy"));
        const int eventNumber(atoi(pTiXmlElement->Attribute("Event_Number")));
        const double alpha4(atof(pTiXmlElement->Attribute("Alpha_Four")));
        const double alpha5(atof(pTiXmlElement->Attribute("Alpha_Five")));
        const double weight(atof(pTiXmlElement->Attribute("Ratio_of_Integrands")));

        if (eventNumber > 5)
          continue;

        CouplingAnalysis::Event *pEvent = new CouplingAnalysis::Event();

        pEvent->SetProcess(process);
        pEvent->SetEnergy(energy);
        pEvent->SetAlpha4(alpha4);
        pEvent->SetAlpha5(alpha5);
        pEvent->SetEventNumber(eventNumber);
        pEvent->SetWeight(weight);
        m_Events.push_back(pEvent);

        int alpha4Key(std::numeric_limits<int>::max());
        int alpha5Key(std::numeric_limits<int>::max());

        if (!this->GetAlpha4Key(alpha4,alpha4Key))
        {
            m_KeyToAlpha4Map.insert(std::make_pair(m_NumberUniqueAlpha4,alpha4));
            m_NumberUniqueAlpha4++;
            m_Alpha4Vector.push_back(alpha4);
            std::cout << "m_NumberUniqueAlpha4 : " << m_NumberUniqueAlpha4 << std::endl;
            std::cout << "Adding alpha4 : " << alpha4 << " to the list." << std::endl;
        }

        if (!this->GetAlpha5Key(alpha5,alpha5Key))
        {
            m_KeyToAlpha5Map.insert(std::make_pair(m_NumberUniqueAlpha5,alpha5));
            m_NumberUniqueAlpha5++;
            m_Alpha5Vector.push_back(alpha5);
            std::cout << "m_NumberUniqueAlpha5 : " << m_NumberUniqueAlpha5 << std::endl;
            std::cout << "Adding alpha5 : " << alpha5 << " to the list." << std::endl;
        }

        this->GetAlpha4Key(alpha4,alpha4Key);
        this->GetAlpha5Key(alpha5,alpha5Key);

        m_EventToAlpha4ToAlpha5ToWeightMap[eventNumber][alpha4Key][alpha5Key] = weight;
    }

    pTiXmlDocument->Clear();
}

//============================================================================
/*
void CouplingAnalysis::AnalyseSingleEvent(const int eventNumber)  
{
    gStyle->SetNumberContours(99);

    std::string evtNumber(this->NumberToString(eventNumber));

    std::string plotName("AnalyseSingleEvent_Evt" + evtNumber);
    std::string plotTitle("Analyse Single Event, Event Number " + evtNumber);

    TH2F *pTH2F = new TH2F(plotName.c_str(), plotTitle.c_str(), 5, -0.125, 0.125, 5, -0.125, 0.125);
    TGraph2D *pTGraph2D = new TGraph2D();

    std::string plotNameG("Graph_AnalyseSingleEvent_Evt" + evtNumber);
    std::string plotTitleG("Graph_Analyse Single Event, Event Number " + evtNumber);
    pTGraph2D->SetNameTitle(plotNameG.c_str(),plotTitleG.c_str());

    for (EventVector::const_iterator iter = m_Events.begin(); iter != m_Events.end(); iter++)
    {
        CouplingAnalysis::Event *pEvent(*iter);

        if (pEvent->GetEventNumber() != eventNumber)
            continue;

        const float alpha4(pEvent->GetAlpha4());
        const float alpha5(pEvent->GetAlpha5());
        const float weight(pEvent->GetWeight());
        pTH2F->Fill(alpha4,alpha5,weight);
        std::cout << "pTGraph2D->GetN() : " << pTGraph2D->GetN() << std::endl;
        pTGraph2D->SetPoint(pTGraph2D->GetN(),alpha4,alpha5,weight);
    }
    m_2DHistToFit = pTH2F;
    this->MinuitFitEvent();

    std::string fitName("Fit_EvtNumber_" + evtNumber);

    TF2 *pTF2 = new TF2(fitName.c_str(),"[0] + (x*[1]) + (y*[2]) + (x*x*[3]) + (x*y*[4]) + (y*y*[5])",-0.0125,0.0125,-0.0125,0.0125);

    pTH2F->Fit(fitName.c_str());

    pTF2->SetParameter(0,m_constant);
    pTF2->SetParameter(1,m_A);
    pTF2->SetParameter(2,m_B);
    pTF2->SetParameter(3,m_C);
    pTF2->SetParameter(4,m_D);
    pTF2->SetParameter(5,m_E);

    TCanvas *pTCanvas = new TCanvas();
//    pTH2F->Draw("scat");
//    pTGraph2D->Draw("pcol");
    pTGraph2D->Draw("p0");
//    pTGraph2D->Draw("surf1");
    pTF2->Draw("surf1 same");

    std::string plotName1("TestingEvent" + NumberToString(eventNumber) + ".png");
    std::string plotName2("TestingEvent" + NumberToString(eventNumber) + ".pdf");
    std::string plotName3("TestingEvent" + NumberToString(eventNumber) + ".C");

    pTCanvas->SaveAs(plotName1.c_str());
    pTCanvas->SaveAs(plotName2.c_str());
    pTCanvas->SaveAs(plotName3.c_str());
}
*/
//============================================================================

bool CouplingAnalysis::GetAlpha4Key(const float alpha4, int &alpha4Key) const
{
    for (IntToFloatMap::const_iterator iter = m_KeyToAlpha4Map.begin(); iter != m_KeyToAlpha4Map.end(); ++iter)
    {
        if (std::fabs(iter->second - alpha4) < std::numeric_limits<float>::min())
        {
            alpha4Key = iter->first;
            return true;
        }
    }
    return false;
}

//============================================================================

bool CouplingAnalysis::GetAlpha5Key(const float alpha5, int &alpha5Key) const
{
    for (IntToFloatMap::const_iterator iter = m_KeyToAlpha5Map.begin(); iter != m_KeyToAlpha5Map.end(); ++iter)
    {
        if (std::fabs(iter->second - alpha5) < std::numeric_limits<float>::min())
        {
            alpha5Key = iter->first;
            return true;
        }
    }
    return false;
}

//============================================================================

float CouplingAnalysis::GetAlpha4(int key) const
{
    return m_KeyToAlpha4Map.at(key);
}

//============================================================================

float CouplingAnalysis::GetAlpha5(int key) const
{
    return m_KeyToAlpha5Map.at(key);
}

//============================================================================
/*
void CouplingAnalysis::MinuitFitEvent()
{
//    const char *minName = "GSLMultiMin";
    const char *minName = "Minuit2";
//    const char *algoName = "BFGS";
    const char *algoName = "Migrad";

    ROOT::Math::Minimizer* pMinimizer = ROOT::Math::Factory::CreateMinimizer(minName, algoName);
    pMinimizer->SetMaxFunctionCalls(1000000);
    pMinimizer->SetTolerance(1.f);
    pMinimizer->SetPrintLevel(1);

    ROOT::Math::Functor functorChi2(this, &CouplingAnalysis::MinuitChi2,6);
    pMinimizer->SetFunction(functorChi2);

    const double step = 0.001, minVar(-0.5f), maxVar(0.5f);
    double fitPar0 = 1.f;
//    pMinimizer->SetVariable(0, "p0", fitPar0, step);
    pMinimizer->SetFixedVariable(0, "p0", fitPar0);
//    pMinimizer->SetVariableLimits(0,minVar,maxVar);
    double fitPar1(0.f);
    pMinimizer->SetVariable(1, "p1", fitPar1, step);
    pMinimizer->SetVariableLimits(1,minVar,maxVar);
    double fitPar2(0.f);
    pMinimizer->SetVariable(2, "p2", fitPar2, step);
    pMinimizer->SetVariableLimits(2,minVar,maxVar);
    double fitPar3(0.f);
    pMinimizer->SetVariable(3, "p3", fitPar3, step);
    pMinimizer->SetVariableLimits(3,minVar,maxVar);
    double fitPar4(0.f);
    pMinimizer->SetVariable(4, "p4", fitPar4, step);
    pMinimizer->SetVariableLimits(4,minVar,maxVar);
    double fitPar5(0.f);
    pMinimizer->SetVariable(5, "p5", fitPar5, step);
    pMinimizer->SetVariableLimits(5,minVar,maxVar);

    pMinimizer->Minimize();
    const double *xs = pMinimizer->X();
    std::cout << "Minimum: chi2 = " << pMinimizer->MinValue()  << std::endl;

    if ( pMinimizer->MinValue()  < 1.E-4  && this->MinuitChi2(xs) < 1.E-4)
    {
        std::cout << "Minimizer " << minName << " - " << algoName << "   converged to the right minimum" << std::endl;
    }

    else
    {
        std::cout << "Minimizer " << minName << " - " << algoName << "   failed to converge !!!" << std::endl;
        std::cout << "MinValue " << pMinimizer->MinValue() << std::endl;
    }

    for (int i = 0; i < 6; i++)
    {
        std::cout << "Parameter " << i << " is " << xs[i] << std::endl;
    }

    m_constant = xs[0];
    m_A = xs[1];
    m_B = xs[2];
    m_C = xs[3];
    m_D = xs[4];
    m_E = xs[5];
}

//============================================================================

double CouplingAnalysis::MinuitChi2(const double *par)
{
    double chi2(0.f);

    TH2F *pTH2F = m_2DHistToFit;

    for (unsigned int xBin = 1; xBin < pTH2F->GetNbinsX() + 1; xBin++)
    {
        for (unsigned int yBin = 1; yBin < pTH2F->GetNbinsY() + 1; yBin++)
        {
            const double a4 = pTH2F->GetXaxis()->GetBinCenter(xBin);
            const double a5 = pTH2F->GetYaxis()->GetBinCenter(yBin);
            const double estimatedWeight(this->EstimatedWeight(a4,a5,par));
            const double actualWeight(pTH2F->GetBinContent(xBin,yBin)); 
            const double diff = (actualWeight - estimatedWeight) * (actualWeight - estimatedWeight) / (0.5*actualWeight);
            chi2 += diff;
        }
    }
    return chi2;
}

//============================================================================

double CouplingAnalysis::EstimatedWeight(const double a4, const double a5, const double *par)
{
    const double constant(par[0]);
    const double A(par[1]);
    const double B(par[2]);
    const double C(par[3]);
    const double D(par[4]);
    const double E(par[5]);
    const double estimatedWeight = constant + (A * a4) + (B * a5) + (C * a4 * a4) + (D * a4 * a5) + (E * a5 * a5);
    return estimatedWeight;
}
*/
//============================================================================

template <class T>
std::string CouplingAnalysis::NumberToString(T Number) const 
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string CouplingAnalysis::FileNumberToString(T Number) const 
{
    std::ostringstream ss;
    ss << setfill('0') << setw(3) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string CouplingAnalysis::AlphasToString(T Number) const 
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(5) << Number;
    return ss.str();
}

//============================================================================
