#include "CouplingAnalysis.h"

//============================================================================

CouplingAnalysis::CouplingAnalysis() : 
    m_NumberUniqueAlpha4(0),
    m_NumberUniqueAlpha5(0)
{
    this->LoadXml();
    this->AnalyseSingleEvent(1);
}

//============================================================================

void CouplingAnalysis::GetWeight(const int eventNumber, const float alpha4, const float alpha5, float &eventWeight) const 
{
    float lowerAlpha4(std::numeric_limits<float>::max());
    float upperAlpha4(std::numeric_limits<float>::max());
    float lowerAlpha5(std::numeric_limits<float>::max());
    float upperAlpha5(std::numeric_limits<float>::max());

    this->Bounds(m_Alpha4Vector, lowerAlpha4, upperAlpha4, alpha4);
    this->Bounds(m_Alpha5Vector, lowerAlpha5, upperAlpha5, alpha5);

    int lowerAlpha4Key(std::numeric_limits<int>::max());
    int upperAlpha4Key(std::numeric_limits<int>::max());
    int lowerAlpha5Key(std::numeric_limits<int>::max());
    int upperAlpha5Key(std::numeric_limits<int>::max());

    this->GetAlpha4Key(lowerAlpha4,lowerAlpha4Key);
    this->GetAlpha4Key(upperAlpha4,upperAlpha4Key);
    this->GetAlpha5Key(lowerAlpha5,lowerAlpha5Key);
    this->GetAlpha5Key(upperAlpha5,upperAlpha5Key);

    std::cout << "Lower Bound Alpha4 Value " << lowerAlpha4 << ", Key : " << lowerAlpha4Key << std::endl;;
    std::cout << "Upper Bound Alpha4 Value " << upperAlpha4 << ", Key : " << upperAlpha4Key << std::endl;
    std::cout << "Lower Bound Alpha5 Value " << lowerAlpha5 << ", Key : " << lowerAlpha5Key << std::endl;;
    std::cout << "Upper Bound Alpha5 Value " << upperAlpha5 << ", Key : " << upperAlpha5Key << std::endl;;

    float lowerLeftBound(this->GetStoredWeight(eventNumber,lowerAlpha4,lowerAlpha5));
    float upperLeftBound(this->GetStoredWeight(eventNumber,lowerAlpha4,upperAlpha5));
    float lowerRightBound(this->GetStoredWeight(eventNumber,upperAlpha4,lowerAlpha5));
    float upperRightBound(this->GetStoredWeight(eventNumber,upperAlpha4,upperAlpha5));

    eventWeight = this->BilinearInterpolation(lowerLeftBound,upperLeftBound,lowerRightBound,upperRightBound,lowerAlpha4,upperAlpha4,lowerAlpha5,upperAlpha5,alpha4,alpha5);

    std::cout << "UL : " << upperLeftBound << " " << upperRightBound << " : UR" << std::endl;
    std::cout << "LL : " << lowerLeftBound << " " << lowerRightBound << " : LR" << std::endl;
    std::cout << "BilinearInterpolation : " << eventWeight << std::endl;
    
}

//============================================================================

float CouplingAnalysis::BilinearInterpolation(const float l4l5, const float l4u5, const float u4l5, const float u4u5, const float lowerAlpha4, const float upperAlpha4, const float lowerAlpha5, const float upperAlpha5, const float alpha4, const float alpha5) const
{
    const float x(alpha4);
    const float x1(lowerAlpha4);
    const float x2(upperAlpha4);
    const float y(alpha5);
    const float y1(lowerAlpha5);
    const float y2(upperAlpha5);
    const float f11(l4l5);
    const float f12(l4u5);
    const float f21(u4l5);
    const float f22(u4u5);

    const float denominator((x2-x1) * (y2-y1));
    const float numerator(((x2-x) * (f11 * (y2-y) + f12 * (y-y1))) + ((x-x1) * (f21 * (y2-y) + f22 * (y-y1))));
    return numerator / denominator;
}

//============================================================================

void CouplingAnalysis::LoadXml()
{
    std::string process("ee_nunuww_nunuqqqq");
    std::string energy("1400");

//    for (int i = -5; i < 6; i++)
    for (int i = -2; i < 3; i++)
    {
//        for (int j = -5; j < 6; j++)
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

//    std::cout << "Loading file: " << fileName << std::endl;

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

void CouplingAnalysis::AnalyseSingleEvent(const int eventNumber) const 
{
    TH2F *pTH2F = new TH2F("Name", "Title", 11, -0.0275, 0.0275, 11, -0.0275, 0.0275);

    for (EventVector::const_iterator iter = m_Events.begin(); iter != m_Events.end(); iter++)
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

void CouplingAnalysis::Bounds(const FloatVector &alphaVector, float &lowAlpha, float &highAlpha, const float currentAlpha) const
{
    if (currentAlpha <= alphaVector.front() or currentAlpha >= alphaVector.back())
    {
        std::cout << "Alpha value out of range, unknown bounds.  Returning unset bounds." << std::endl;
        return;
    }

    for (FloatVector::const_iterator iter = alphaVector.begin(); iter != alphaVector.end(); iter++)
    {
        const float value(*iter);
        unsigned int position(iter-alphaVector.begin());
        if (value >= currentAlpha)
        {
            lowAlpha = alphaVector.at(position-1);
            highAlpha = alphaVector.at(position);
            return;
        }
    }
}

//============================================================================

float CouplingAnalysis::GetStoredWeight(const int eventNumber, const float alpha4, const float alpha5) const
{
    int alpha4Key(std::numeric_limits<int>::max());
    int alpha5Key(std::numeric_limits<int>::max());
    this->GetAlpha4Key(alpha4,alpha4Key);
    this->GetAlpha5Key(alpha5,alpha5Key);
    return m_EventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(alpha4Key).at(alpha5Key);
}

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

template <class T>
std::string CouplingAnalysis::NumberToString(T Number) const 
{
    std::ostringstream ss;
    ss << setfill('0') << setw(3) << Number;
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
