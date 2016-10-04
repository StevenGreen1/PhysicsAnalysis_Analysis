#include "CouplingAnalysis.h"

//============================================================================

CouplingAnalysis::CouplingAnalysis(const ProcessVector &processVector, PostMVASelection *pPostMVASelection) : 
    m_processVector(processVector),
    m_pPostMVASelection(pPostMVASelection),
    m_eventsNeedingWeights(pPostMVASelection->GetEventsNeedingWeightsList()),
    m_numberUniqueAlpha4(0),
    m_numberUniqueAlpha5(0),
    m_a4IntMin(-5),
    m_a4IntMax(4),
    m_a4Step(0.01f),
    m_a5IntMin(-5),
    m_a5IntMax(4),
    m_a5Step(0.01f)
{
    for (int a4Int = m_a4IntMin; a4Int < m_a4IntMax; a4Int++)
    {
        m_alpha4Vector.push_back((float)(m_a4Step*a4Int));
    }

    for (int a5Int = m_a5IntMin; a5Int < m_a5IntMax; a5Int++)
    {
        m_alpha5Vector.push_back((float)(m_a5Step*a5Int));
    }

    std::sort(m_alpha4Vector.begin(), m_alpha4Vector.end());
    std::sort(m_alpha5Vector.begin(), m_alpha5Vector.end());
}

//============================================================================

CouplingAnalysis::~CouplingAnalysis()
{
}

//============================================================================ Concatenate Data

void CouplingAnalysis::GetWeightsFromFiles()
{
    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it++)
    {
        const Process *pProcess(*it);
        if (pProcess->GetEventType() != "ee_nunuqqqq")
            continue;

        IntVector generatorNumbersToRead;
    
        for (IntVector::iterator enIt = m_eventsNeedingWeights.begin(); enIt != m_eventsNeedingWeights.end(); enIt++)
        {
            const int eventNumber(*enIt);

            int generatorNumber(std::numeric_limits<int>::max());
std::cout << "eventNumber : " << eventNumber << std::endl;
            if (eventNumber % 1000 == 0)
            {
                generatorNumber = (int)(eventNumber/1000.0) - 1;
std::cout << "generatorNumber = (eventNumber/1000.f) - 1; " << eventNumber/1000.f << " " << generatorNumber << std::endl;
            }
            else
            {
                const double doubleNumber(eventNumber/1000.0);
                generatorNumber = floor(doubleNumber);
std::cout << "generatorNumber = dn " << doubleNumber << " " << generatorNumber << std::endl;
            }

std::cout << "generatorNumber : " << generatorNumber << std::endl;
            if (std::find(generatorNumbersToRead.begin(), generatorNumbersToRead.end(), generatorNumber) == generatorNumbersToRead.end())
            {
                std::cout << "Reading in generatorNumber : " << generatorNumber << std::endl;
                this->LoadXmlData(generatorNumber, pProcess);
                generatorNumbersToRead.push_back(generatorNumber);

                for (IntVector::iterator it = generatorNumbersToRead.begin(); it != generatorNumbersToRead.end(); it++)
                {
                    std::cout << *it << " ";
                }
                std::cout << std::endl;
                this->SaveXmlData(generatorNumber);
            }
        }
    }
}

//============================================================================

void CouplingAnalysis::LoadXmlData(const int genN, const Process *pProcess)
{
    m_Events.clear();

    for (int a4Int = m_a4IntMin; a4Int < m_a4IntMax; a4Int++)
    {
        float alpha4(a4Int*m_a4Step);

        for (int a5Int = m_a5IntMin; a5Int < m_a5IntMax; a5Int++)
        {
            float alpha5(a5Int*m_a5Step);
//std::cout << "alpha4 " << alpha4 << std::endl;
//std::cout << "alpha5 " << alpha5 << std::endl;
            this->LoadIndividualXmlData(genN,alpha4,alpha5,pProcess);
        }
    }
}

//============================================================================

void CouplingAnalysis::LoadIndividualXmlData(const int &genN, const float &alpha4, const float &alpha5, const Process *pProcess)
{
    const std::string processName(pProcess->GetEventType());
    const int energy(pProcess->GetEnergy());
    const int whizardJobSet(floor(genN/1000));

std::cout << "whizardJobSet : " << whizardJobSet << std::endl;

    std::string pathToResults("/r06/lc/sg568/PhysicsAnalysis/Generator/" + processName + "/" + this->NumberToString(energy) + "GeV/WhizardJobSet" + this->NumberToString(whizardJobSet) + "/Alpha4_" + this->AlphasToString(alpha4) + "_Alpha5_" + this->AlphasToString(alpha5) + "/");
    std::string fileName(pathToResults + "Reweighting_GenN" + this->NumberToString(genN) + "_" + processName + "_" + this->NumberToString(energy) + "GeV_Alpha4_" + this->AlphasToString(alpha4) + "_Alpha5_" + this->AlphasToString(alpha5) + ".xml");
std::cout << fileName << std::endl;

    TiXmlDocument *pTiXmlDocument = new TiXmlDocument();

    if (!pTiXmlDocument->LoadFile(fileName.c_str()))
    {
        std::cerr << pTiXmlDocument->ErrorDesc() << std::endl;
    }

    TiXmlElement* pHeadTiXmlElement = pTiXmlDocument->FirstChildElement();

    if (pHeadTiXmlElement == NULL)
    {
        std::cerr << "Failed to load file: No root element." << std::endl;
        pTiXmlDocument->Clear();
    }

    std::string process(pHeadTiXmlElement->Attribute("Process"));
    std::string energyFromXml(pHeadTiXmlElement->Attribute("Energy"));
    const double currentAlpha4(atof(pHeadTiXmlElement->Attribute("Alpha_Four")));
    const double currentAlpha5(atof(pHeadTiXmlElement->Attribute("Alpha_Five")));

    for (TiXmlElement* pTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pTiXmlElement != NULL; pTiXmlElement = pTiXmlElement->NextSiblingElement())
    {
        const int eventNumber((1e3*genN) + atoi(pTiXmlElement->Attribute("Event_Number")));
        const double weight(atof(pTiXmlElement->Attribute("Ratio_of_Integrands")));
        CouplingAnalysis::Event *pEvent = new CouplingAnalysis::Event();
        pEvent->SetProcess(process);
        pEvent->SetEnergy(energyFromXml);
        pEvent->SetAlpha4(currentAlpha4);
        pEvent->SetAlpha5(currentAlpha5);
        pEvent->SetEventNumber(eventNumber);
        pEvent->SetWeight(weight);
        m_Events.push_back(pEvent);
    }

    pTiXmlDocument->Clear();
    delete pTiXmlDocument;
}

//============================================================================

void CouplingAnalysis::SaveXmlData(int generatorNumber)
{
    std::string weightsFileName("ConcatenatedWeights" + this->NumberToString(generatorNumber) + ".xml");

    TiXmlDocument tiXmlDocument;
    TiXmlElement *pHeadTiXmlElement = new TiXmlElement("Event");
    tiXmlDocument.LinkEndChild(pHeadTiXmlElement);

    for (EventVector::iterator iter = m_Events.begin(); iter != m_Events.end(); iter++)
    {
        CouplingAnalysis::Event *pEvent(*iter);
        const int eventNumber(pEvent->GetEventNumber());

        if (std::find(m_eventsNeedingWeights.begin(), m_eventsNeedingWeights.end(), eventNumber) == m_eventsNeedingWeights.end())
            continue;

        TiXmlElement* pTiXmlElement = new TiXmlElement("Event");
        pTiXmlElement->SetAttribute("Event_Number", pEvent->GetEventNumber());
        pTiXmlElement->SetAttribute("Process", pEvent->GetProcess().c_str());
        pTiXmlElement->SetAttribute("Energy", pEvent->GetEnergy().c_str());
        pTiXmlElement->SetDoubleAttribute("Alpha_Four", pEvent->GetAlpha4());
        pTiXmlElement->SetDoubleAttribute("Alpha_Five", pEvent->GetAlpha5());
        pTiXmlElement->SetDoubleAttribute("Ratio_of_Integrands", pEvent->GetWeight());
        pHeadTiXmlElement->LinkEndChild(pTiXmlElement);
    }

    bool success = tiXmlDocument.SaveFile(weightsFileName.c_str());

    tiXmlDocument.Clear();
}

//============================================================================ Read in Concatenated Data

void CouplingAnalysis::LoadData()
{
    std::string pathToResults("/var/clus/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin");
    std::string fileName(pathToResults + "ConcatenatedWeights.xml");

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

    for (TiXmlElement* pTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pTiXmlElement != NULL; pTiXmlElement = pTiXmlElement->NextSiblingElement())
    {
        const int eventNumber(atoi(pTiXmlElement->Attribute("Event_Number")));
        std::string process(pHeadTiXmlElement->Attribute("Process"));
        std::string energy(pHeadTiXmlElement->Attribute("Energy"));
        const double alpha4(atof(pHeadTiXmlElement->Attribute("Alpha_Four")));
        const double alpha5(atof(pHeadTiXmlElement->Attribute("Alpha_Five")));
        const double weight(atof(pTiXmlElement->Attribute("Ratio_of_Integrands")));

        if (!this->DoesAlpha4KeyExist(alpha4))
            this->SetAlpha4Key(alpha4);

        if (!this->DoesAlpha5KeyExist(alpha5))
            this->SetAlpha5Key(alpha5);

        const int alpha4Key(this->GetAlpha4Key(alpha4));
        const int alpha5Key(this->GetAlpha5Key(alpha5));

        m_eventToAlpha4ToAlpha5ToWeightMap[eventNumber][alpha4Key][alpha5Key] = weight;
    }

    pTiXmlDocument->Clear();
    delete pTiXmlDocument;
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

bool CouplingAnalysis::DoesAlpha4KeyExist(const float alpha4) const
{
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha4Map.begin(); iter != m_keyToAlpha4Map.end(); ++iter)
    {
        if (this->DoFloatsMatch(iter->second, alpha4))
            return true;
    }
    return false;
}

//============================================================================

void CouplingAnalysis::SetAlpha4Key(const float alpha4)
{
    m_keyToAlpha4Map.insert(std::make_pair(m_numberUniqueAlpha4,alpha4));
    m_numberUniqueAlpha4++;
    m_alpha4Vector.push_back(alpha4);
}

//============================================================================

int CouplingAnalysis::GetAlpha4Key(const float alpha4) const
{
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha4Map.begin(); iter != m_keyToAlpha4Map.end(); ++iter)
    {
        if (this->DoFloatsMatch(iter->second, alpha4))
        {
            return iter->first;
        }
    }
}

//============================================================================

float CouplingAnalysis::GetAlpha4(int key) const
{
    return m_keyToAlpha4Map.at(key);
}

//============================================================================

bool CouplingAnalysis::DoesAlpha5KeyExist(const float alpha5) const
{
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha5Map.begin(); iter != m_keyToAlpha5Map.end(); ++iter)
    {
        if (this->DoFloatsMatch(iter->second, alpha5))
            return true;
    }
    return false;
}

//============================================================================

void CouplingAnalysis::SetAlpha5Key(const float alpha5)
{
    m_keyToAlpha5Map.insert(std::make_pair(m_numberUniqueAlpha5,alpha5));
    m_numberUniqueAlpha5++;
    m_alpha5Vector.push_back(alpha5);
}

//============================================================================

int CouplingAnalysis::GetAlpha5Key(const float alpha5) const
{
    for (IntToFloatMap::const_iterator iter = m_keyToAlpha5Map.begin(); iter != m_keyToAlpha5Map.end(); ++iter)
    {
        if (this->DoFloatsMatch(iter->second, alpha5))
        {
            return iter->first;
        }
    }
}

//============================================================================

float CouplingAnalysis::GetAlpha5(int key) const
{
    return m_keyToAlpha5Map.at(key);
}

//============================================================================ Do Weighting

void CouplingAnalysis::GetWeight(const int eventNumber, const float alpha4, const float alpha5, float &eventWeight) const 
{
    if (alpha4 < *m_alpha4Vector.begin() or m_alpha4Vector.back() <= alpha4 or alpha5 < *m_alpha5Vector.begin() or m_alpha5Vector.back() <= alpha5)
    {
        std::cout << "Unable to apply bilinear interpolation to event, please add more weight samples.  Setting event weight to 1." << std::endl;
        eventWeight = 1.f;
    }

    int lowAlpha4Key(std::numeric_limits<int>::max());
    int highAlpha4Key(std::numeric_limits<int>::max());
    int lowAlpha5Key(std::numeric_limits<int>::max());
    int highAlpha5Key(std::numeric_limits<int>::max());

    this->SetAlpha4BoundingKeys(alpha4, lowAlpha4Key, highAlpha4Key);
    this->SetAlpha5BoundingKeys(alpha5, lowAlpha5Key, highAlpha5Key);

    IntToIntToIntToFloatMap::const_iterator it = m_eventToAlpha4ToAlpha5ToWeightMap.find(eventNumber);

    if (it == m_eventToAlpha4ToAlpha5ToWeightMap.end())
        std::cout << "Missing event number " << eventNumber << std::endl;

    const float lowerA4(this->GetAlpha4(lowAlpha4Key));
    const float upperA4(this->GetAlpha4(highAlpha4Key));
    const float lowerA5(this->GetAlpha4(lowAlpha5Key));
    const float upperA5(this->GetAlpha4(highAlpha5Key));
    const float lowerA4lowerA5(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(lowAlpha4Key).at(lowAlpha5Key));
    const float lowerA4upperA5(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(highAlpha4Key).at(lowAlpha5Key));
    const float upperA4lowerA5(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(lowAlpha4Key).at(highAlpha5Key));
    const float upperA4upperA5(m_eventToAlpha4ToAlpha5ToWeightMap.at(eventNumber).at(highAlpha4Key).at(highAlpha5Key));
    eventWeight = this->BilinearInterpolation(lowerA4lowerA5,lowerA4upperA5,upperA4lowerA5,upperA4upperA5,alpha4,lowerA4,upperA4,alpha5,lowerA5,upperA5);
}

//============================================================================

void CouplingAnalysis::SetAlpha4BoundingKeys(const float alpha4, int &lowAlpha4Key, int &highAlpha4Key) const
{
    for (FloatVector::const_iterator iter = m_alpha4Vector.begin(); iter != m_alpha4Vector.end() - 1; iter++)
    {
        int position(iter - m_alpha4Vector.begin());

        if (m_alpha4Vector.at(position) <= alpha4 and alpha4 < m_alpha4Vector.at(position+1))
        { 
            lowAlpha4Key = this->GetAlpha4Key(m_alpha4Vector.at(position));
            highAlpha4Key = this->GetAlpha4Key(m_alpha4Vector.at(position+1));
            return;
        }
    }
}

//============================================================================

void CouplingAnalysis::SetAlpha5BoundingKeys(const float alpha5, int &lowAlpha5Key, int &highAlpha5Key) const 
{
    for (FloatVector::const_iterator iter = m_alpha5Vector.begin(); iter != m_alpha5Vector.end() - 1; iter++)
    {
        int position(iter - m_alpha5Vector.begin());
        if (m_alpha5Vector.at(position) <= alpha5 and alpha5 < m_alpha5Vector.at(position+1))
        {
            lowAlpha5Key = this->GetAlpha5Key(m_alpha5Vector.at(position));
            highAlpha5Key = this->GetAlpha4Key(m_alpha5Vector.at(position+1));
            return;
        }
    }
}

//============================================================================

float CouplingAnalysis::BilinearInterpolation(const float f11, const float f12, const float f21, const float f22, const float x, const float x1, const float x2, const float y, const float y1, const float y2) const
{
    const float numerator((x2-x) * ((f11 * (y2-y)) + (f12 * (y-y1))) + (x-x1) * ((f21 * (y2-y)) + (f22 * (y-y1))));
    const float denominator((x2-x1)*(y2-y1));
    return numerator/denominator;
}

//============================================================================ Helper

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
    ss << std::setfill('0') << std::setw(3) << Number;
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
