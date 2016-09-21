#include "CouplingAnalysis.h"

//============================================================================

CouplingAnalysis::CouplingAnalysis(std::string process, std::string energy) : 
    m_process(process),
    m_energy(energy),
    m_NumberUniqueAlpha4(0),
    m_NumberUniqueAlpha5(0)
{
    this->LoadXml();
}

//============================================================================

CouplingAnalysis::~CouplingAnalysis()
{
}

//============================================================================

void CouplingAnalysis::GetWeight(const int eventNumber, const float alpha4, const float alpha5, float &eventWeight) const  
{
//    std::cout << "Getting weight " << eventNumber << " alpha4 " << alpha4 << " alpha5 " << alpha5 << " " << std::endl; 

    float lowerA4Bound(-1.f*std::numeric_limits<float>::max());
    int lowerA4Key(std::numeric_limits<int>::max());

    float upperA4Bound(std::numeric_limits<float>::max());
    int upperA4Key(std::numeric_limits<int>::max());

    float lowerA5Bound(-1.f*std::numeric_limits<float>::max());
    int lowerA5Key(std::numeric_limits<int>::max());

    float upperA5Bound(std::numeric_limits<float>::max());
    int upperA5Key(std::numeric_limits<int>::max());

//    if (alpha4 <= *m_Alpha4Vector.begin() or m_Alpha4Vector.back() <= alpha4 or alpha5 <= *m_Alpha5Vector.begin() or m_Alpha5Vector.back() <= alpha5)
    if (alpha4 < *m_Alpha4Vector.begin() or m_Alpha4Vector.back() < alpha4 or alpha5 < *m_Alpha5Vector.begin() or m_Alpha5Vector.back() < alpha5)
    {
        std::cout << "Unable to apply bilinear interpolation to event, please add more weight samples.  Setting event weight to 1." << std::endl;
        eventWeight = 1.f;

    }

    for (FloatVector::const_iterator iter = m_Alpha4Vector.begin(); iter != m_Alpha4Vector.end(); iter++)
    {
        int position(iter - m_Alpha4Vector.begin());
        //if (m_Alpha4Vector.at(position) <= alpha4 and alpha4 < m_Alpha4Vector.at(position+1))
        if (m_Alpha4Vector.at(position) <= alpha4 and alpha4 <= m_Alpha4Vector.at(position+1))
        {
            lowerA4Bound = m_Alpha4Vector.at(position);
            upperA4Bound = m_Alpha4Vector.at(position+1);
            this->GetAlpha4Key(lowerA4Bound,lowerA4Key);
            this->GetAlpha4Key(upperA4Bound,upperA4Key);
        }
    }

    for (FloatVector::const_iterator iter = m_Alpha5Vector.begin(); iter != m_Alpha5Vector.end(); iter++)
    {
        int position(iter - m_Alpha5Vector.begin());
        //if (m_Alpha5Vector.at(position) <= alpha5 and alpha5 < m_Alpha5Vector.at(position+1))
        if (m_Alpha5Vector.at(position) <= alpha5 and alpha5 < m_Alpha5Vector.at(position+1))
        {
            lowerA5Bound = m_Alpha5Vector.at(position);
            upperA5Bound = m_Alpha5Vector.at(position+1);
            this->GetAlpha5Key(lowerA5Bound,lowerA5Key);
            this->GetAlpha5Key(upperA5Bound,upperA5Key);
        }
    }
/*
    std::cout << "lowerA4Bound " << lowerA4Bound << std::endl;
    std::cout << "upperA4Bound " << upperA4Bound << std::endl;
    std::cout << "lowerA5Bound " << lowerA5Bound << std::endl;
    std::cout << "upperA5Bound " << upperA5Bound << std::endl;

    std::cout << "lowerA4Key " << lowerA4Key << std::endl;
    std::cout << "upperA4Key " << upperA4Key << std::endl;
    std::cout << "lowerA5Key " << lowerA5Key << std::endl;
    std::cout << "upperA5Key " << upperA5Key << std::endl;
*/
    IntToIntToIntToFloatMap::const_iterator it = m_EventToAlpha4ToAlpha5ToWeightMap.find(eventNumber);

    if (it == m_EventToAlpha4ToAlpha5ToWeightMap.end())
        std::cout << "Missing event number " << eventNumber << std::endl;

    const float lowerA4lowerA5(m_EventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(lowerA4Key).at(lowerA5Key));
    const float lowerA4upperA5(m_EventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(upperA4Key).at(lowerA5Key));
    const float upperA4lowerA5(m_EventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(lowerA4Key).at(upperA5Key));
    const float upperA4upperA5(m_EventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(upperA4Key).at(upperA5Key));

//    std::cout << "calculating eventWeight" << std::endl;
    eventWeight = this->BilinearInterpolation(lowerA4lowerA5,lowerA4upperA5,upperA4lowerA5,upperA4upperA5,alpha4,lowerA4Bound,upperA4Bound,alpha5,lowerA5Bound,upperA5Bound);

//    std::cout << "eventWeight : " << eventWeight << std::endl;
}

//============================================================================

float CouplingAnalysis::BilinearInterpolation(const float f11, const float f12, const float f21, const float f22, const float x, const float x1, const float x2, const float y, const float y1, const float y2) const
{
    const float numerator((x2-x) * ((f11 * (y2-y)) + (f12 * (y-y1))) + (x-x1) * ((f21 * (y2-y)) + (f22 * (y-y1))));
    const float denominator((x2-x1)*(y2-y1));
    return numerator/denominator;
}

//============================================================================

void CouplingAnalysis::LoadXml()
{
    for (int i = -5; i < -2; i++)
    {
        for (int j = -5; j < -2; j++)
        {
            std::cout << i << " " << j << std::endl;
            const float alpha4(i * 0.01);
            const float alpha5(j * 0.01);
            std::cout << "Loading : (Alpha4,Alpha5) = (" << this->AlphasToString(alpha4) << "," << this->AlphasToString(alpha5) << ")" << std::endl;
            this->LoadIndividualXml(alpha4,alpha5);
        }
    }

    std::sort(m_Alpha4Vector.begin(), m_Alpha4Vector.end());
    std::sort(m_Alpha5Vector.begin(), m_Alpha5Vector.end());
}

//============================================================================

void CouplingAnalysis::LoadIndividualXml(const float alpha4, const float alpha5)
{
    //for (unsigned int whizardJobSet = 350; whizardJobSet <=350; whizardJobSet++)
    for (unsigned int whizardJobSet = 1; whizardJobSet <=350; whizardJobSet++)
    {
        std::string pathToResults("/r06/lc/sg568/PhysicsAnalysis/Generator/" + m_process + "/" + m_energy + "GeV/WhizardJobSet" + this->NumberToString(whizardJobSet) + "/Alpha4_" + this->AlphasToString(alpha4) + "_Alpha5_" + this->AlphasToString(alpha5) + "/");
        std::string fileName(pathToResults + "Reweighting_WhizardJobSet" + this->NumberToString(whizardJobSet) + "_" + m_process + "_" + m_energy + "GeV_Alpha4_" + this->AlphasToString(alpha4) + "_Alpha5_" + this->AlphasToString(alpha5) + ".xml");

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

        std::string process(pHeadTiXmlElement->Attribute("Process"));
        std::string energy(pHeadTiXmlElement->Attribute("Energy"));
        const double currentAlpha4(atof(pHeadTiXmlElement->Attribute("Alpha_Four")));
        const double currentAlpha5(atof(pHeadTiXmlElement->Attribute("Alpha_Five")));

        if (process != m_process or energy != m_energy)
            return;

        int alpha4Key(0);
        int alpha5Key(0);
        this->SetAlpha4Key(alpha4,alpha4Key);
        this->SetAlpha5Key(alpha5,alpha5Key);

        for (TiXmlElement* pTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pTiXmlElement != NULL; pTiXmlElement = pTiXmlElement->NextSiblingElement())
        {
            const int eventNumber((1e6*whizardJobSet) + atoi(pTiXmlElement->Attribute("Event_Number")));
            const double weight(atof(pTiXmlElement->Attribute("Ratio_of_Integrands")));

//            std::cout << "atoi(pTiXmlElement->Attribute(\"Event_Number\")) : " << atoi(pTiXmlElement->Attribute("Event_Number")) << std::endl;
//            std::cout << "whizardJobSet : " << whizardJobSet << std::endl;
//            std::cout << "eventNumber : " << eventNumber << std::endl;

//        if (eventNumber > 5)
//          continue;
            m_EventToAlpha4ToAlpha5ToWeightMap[eventNumber][alpha4Key][alpha5Key] = weight;
        }

        pTiXmlDocument->Clear();
        delete pTiXmlDocument;
    }
}

//============================================================================

bool CouplingAnalysis::DoFloatsMatch(float a, float b) const
{
    if (a*b >= 0.f and fabs(a-b) < std::numeric_limits<float>::min())
        return true;
    else
        return false;
}

//============================================================================

void CouplingAnalysis::SetAlpha4Key(const float alpha4, int &alpha4Key)
{
//    if (m_KeyToAlpha4Map.size() != 0)
//    {
        for (IntToFloatMap::const_iterator iter = m_KeyToAlpha4Map.begin(); iter != m_KeyToAlpha4Map.end(); ++iter)
        {
            if (this->DoFloatsMatch(iter->second, alpha4))
            {
                alpha4Key = iter->first;
                return;
             }
        }
//    }

//    std::cout << m_NumberUniqueAlpha4 << std::endl;
//    std::cout << alpha4 << std::endl;

    m_KeyToAlpha4Map.insert(std::make_pair(m_NumberUniqueAlpha4,alpha4));
    m_NumberUniqueAlpha4++;
    m_Alpha4Vector.push_back(alpha4);

        for (IntToFloatMap::const_iterator iter = m_KeyToAlpha4Map.begin(); iter != m_KeyToAlpha4Map.end(); ++iter)
        {
            if (this->DoFloatsMatch(iter->second, alpha4))
            {
                alpha4Key = iter->first;
                return;
             }
        }

    std::cout << "m_NumberUniqueAlpha4 : " << m_NumberUniqueAlpha4 << std::endl;
    std::cout << "Adding alpha4 : " << alpha4 << " to the list." << std::endl;
}

//============================================================================

void CouplingAnalysis::GetAlpha4Key(const float alpha4, int &alpha4Key) const 
{
    for (IntToFloatMap::const_iterator iter = m_KeyToAlpha4Map.begin(); iter != m_KeyToAlpha4Map.end(); ++iter)
    {
        if (this->DoFloatsMatch(iter->second, alpha4))
        {
            alpha4Key = iter->first;
            return;
        }
    }
}

//============================================================================

void CouplingAnalysis::SetAlpha5Key(const float alpha5, int &alpha5Key)
{
//    if (m_KeyToAlpha5Map.size() != 0)
//    {
        for (IntToFloatMap::const_iterator iter = m_KeyToAlpha5Map.begin(); iter != m_KeyToAlpha5Map.end(); ++iter)
        {
            if (this->DoFloatsMatch(iter->second, alpha5))
            {
                alpha5Key = iter->first;
                return;
            }
        }
//    }

    m_KeyToAlpha5Map.insert(std::make_pair(m_NumberUniqueAlpha5,alpha5));
    m_NumberUniqueAlpha5++;
    m_Alpha5Vector.push_back(alpha5);

        for (IntToFloatMap::const_iterator iter = m_KeyToAlpha5Map.begin(); iter != m_KeyToAlpha5Map.end(); ++iter)
        {
            if (this->DoFloatsMatch(iter->second, alpha5))
            {
                alpha5Key = iter->first;
                return;
            }
        }

    std::cout << "m_NumberUniqueAlpha5 : " << m_NumberUniqueAlpha5 << std::endl;
    std::cout << "Adding alpha5 : " << alpha5 << " to the list." << std::endl;
}

//============================================================================

void CouplingAnalysis::GetAlpha5Key(const float alpha5, int &alpha5Key) const
{
    for (IntToFloatMap::const_iterator iter = m_KeyToAlpha5Map.begin(); iter != m_KeyToAlpha5Map.end(); ++iter)
    {
        if (this->DoFloatsMatch(iter->second, alpha5))
        {
            alpha5Key = iter->first;
            return;
        }
    }
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
