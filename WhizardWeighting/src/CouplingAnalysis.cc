#include "CouplingAnalysis.h"

//============================================================================

CouplingAnalysis::CouplingAnalysis() 
{
    this->LoadXml();
    this->AnalyseSingleEvent(1);
    this->AnalyseSingleEvent(2);
    this->AnalyseSingleEvent(3);
    this->AnalyseSingleEvent(4);
    this->AnalyseSingleEvent(5);
    this->AnalyseSingleEvent(130);
}

//============================================================================

void CouplingAnalysis::LoadXml()
{
    std::string process("ee_nunuzz_nunuqqqq");
    std::string energy("1400");

    for (int i = -5; i < 6; i++)
    {
        for (int j = -5; j < 6; j++)
        {
            const float alpha4(i * 0.005);
            const float alpha5(j * 0.005);
            this->LoadIndividualXml(process,energy,alpha4,alpha5);
        }
    }
}

//============================================================================

void CouplingAnalysis::LoadIndividualXml(std::string process, std::string energy, const float alpha4, const float alpha5)
{
    std::string pathToResults("/var/clus/usera/sg568/PhysicsAnalysis/Generator/ASCIIConverter/");

    std::string fileName(pathToResults + "Reweighting_" + process + "_" + energy + "GeV_Alpha4_" + this->AlphasToString(alpha4) + "_Alpha5_" + this->AlphasToString(alpha5) + ".xml");

    std::cout << "Loading file: " << fileName << std::endl;

    TiXmlDocument tiXmlDocument;

    if(!tiXmlDocument.LoadFile(fileName.c_str()))
    {
        std::cerr << tiXmlDocument.ErrorDesc() << std::endl;
    }

    TiXmlElement* pHeadTiXmlElement = tiXmlDocument.FirstChildElement();

    if(pHeadTiXmlElement == NULL)
    {
        std::cerr << "Failed to load file: No root element." << std::endl;
        tiXmlDocument.Clear();
    }

    for(TiXmlElement* pTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pTiXmlElement != NULL; pTiXmlElement = pTiXmlElement->NextSiblingElement())
    {
        std::string process(pTiXmlElement->Attribute("Process"));
        std::string energy(pTiXmlElement->Attribute("Energy"));
        const int eventNumber(atoi(pTiXmlElement->Attribute("Event_Number")));
        const double alpha4(atof(pTiXmlElement->Attribute("Alpha_Four")));
        const double alpha5(atof(pTiXmlElement->Attribute("Alpha_Five")));
        const double weight(atof(pTiXmlElement->Attribute("Ratio_of_Integrands")));

        CouplingAnalysis::Event *pEvent = new CouplingAnalysis::Event();

        if (eventNumber > 5 and eventNumber != 130) continue;

        pEvent->SetProcess(process);
        pEvent->SetEnergy(energy);
        pEvent->SetAlpha4(alpha4);
        pEvent->SetAlpha5(alpha5);
        pEvent->SetEventNumber(eventNumber);
        pEvent->SetWeight(weight);
        m_Events.push_back(pEvent);
    }

    tiXmlDocument.Clear();
}

//============================================================================

void CouplingAnalysis::AnalyseSingleEvent(const int eventNumber)
{
    TH2F *pTH2F = new TH2F("Name", "Title", 11, -0.0275, 0.0275, 11, -0.0275, 0.0275);

    for (EventVector::iterator iter = m_Events.begin(); iter != m_Events.end(); iter++)
    {
        CouplingAnalysis::Event *pEvent(*iter);

        if (pEvent->GetEventNumber() != eventNumber)
            continue;

        const float alpha4(pEvent->GetAlpha4());
        const float alpha5(pEvent->GetAlpha5());
        const float weight(pEvent->GetWeight());
        pTH2F->Fill(alpha4,alpha5,weight);
    }
    TCanvas *pTCanvas = new TCanvas();
    pTH2F->Draw("COLZ");

    std::string plotName1("TestingEvent" + NumberToString(eventNumber) + ".png");
    std::string plotName2("TestingEvent" + NumberToString(eventNumber) + ".pdf");
    std::string plotName3("TestingEvent" + NumberToString(eventNumber) + ".C");

    pTCanvas->SaveAs(plotName1.c_str());
    pTCanvas->SaveAs(plotName2.c_str());
    pTCanvas->SaveAs(plotName3.c_str());
}

//============================================================================

template <class T>
std::string CouplingAnalysis::NumberToString(T Number)
{
    std::ostringstream ss;
    ss << setfill('0') << setw(3) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string CouplingAnalysis::FileNumberToString(T Number)
{
    std::ostringstream ss;
    ss << setfill('0') << setw(3) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string CouplingAnalysis::AlphasToString(T Number)
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(5) << Number;
    return ss.str();
}

//============================================================================

int main(int argc, char* argv[])
{
    CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis();
    return 0;
}
