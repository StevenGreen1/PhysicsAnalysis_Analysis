/**
 *  @file   AnalysisScripts/src/ConcatenateWeights.cc
 *
 *  @brief  Implementation of the concatenate weights class.
 *
 *  $Log: $
 */

#include "ConcatenateWeights.h"

//============================================================================

ConcatenateWeights::ConcatenateWeights(PostMVASelection *pPostMVASelection) : 
    m_eventsNeedingWeights(pPostMVASelection->GetEventsNeedingWeightsList()),
    m_a4IntMin(-7),
    m_a4IntMax(7),
    m_a5IntMin(-7),
    m_a5IntMax(7),
    m_a4Step(0.01f),
    m_a5Step(0.01f)
{
    m_weightsDirectory = "/r06/lc/sg568/PhysicsAnalysis/Generator/ee_nunuqqqq/1400GeV/ConcatenatedWeightsXml/";
}

//============================================================================

ConcatenateWeights::~ConcatenateWeights()
{
}

//============================================================================ Concatenate Data

void ConcatenateWeights::LoadWeightXml(const int simulationEventNumber, const std::shared_ptr<const Process> pProcess)
{
    m_events.clear();
    m_pTiXmlResultsDocument = new TiXmlDocument();
    m_pDocumentTiXmlElement = new TiXmlElement("Weights");
    m_pTiXmlResultsDocument->LinkEndChild(m_pDocumentTiXmlElement);

    for (int a4Int = m_a4IntMin; a4Int < m_a4IntMax+1; a4Int++)
    {
        float alpha4(a4Int*m_a4Step);

        for (int a5Int = m_a5IntMin; a5Int < m_a5IntMax+1; a5Int++)
        {
            float alpha5(a5Int*m_a5Step);
            this->LoadIndividualWeightXml(simulationEventNumber,alpha4,alpha5,pProcess);
        }
    }
    this->SaveConcatenatedWeightXml(simulationEventNumber);
}

//============================================================================

void ConcatenateWeights::LoadIndividualWeightXml(const int &simulationEventNumber, const float &alpha4, const float &alpha5, const std::shared_ptr<const Process> pProcess)
{
    EventNumbers *pEventNumbers = new EventNumbers();

    const std::string processName(pProcess->GetEventType());
    const int energy(pProcess->GetEnergy());
    const int whizardJobSet(pEventNumbers->GetGeneratorNumberFromSimulation(simulationEventNumber));

    std::string pathToResults("/r06/lc/sg568/PhysicsAnalysis/Generator/" + processName + "/" + this->NumberToString(energy) + "GeV/WhizardJobSet" + this->NumberToString(whizardJobSet) + "/Alpha4_" + this->AlphasToString(alpha4) + "_Alpha5_" + this->AlphasToString(alpha5) + "/");
    std::string fileName(pathToResults + "Reweighting_GenN" + this->NumberToString(simulationEventNumber) + "_" + processName + "_" + this->NumberToString(energy) + "GeV_Alpha4_" + this->AlphasToString(alpha4) + "_Alpha5_" + this->AlphasToString(alpha5) + ".xml");

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

    std::string process(pHeadTiXmlElement->Attribute("EventType"));
    const int energyFromXml(atoi(pHeadTiXmlElement->Attribute("Energy")));
    const double alpha4FromXml(atof(pHeadTiXmlElement->Attribute("Alpha_Four")));
    const double alpha5FromXml(atof(pHeadTiXmlElement->Attribute("Alpha_Five")));

    for (TiXmlElement* pTiXmlElement = pHeadTiXmlElement->FirstChildElement(); pTiXmlElement != NULL; pTiXmlElement = pTiXmlElement->NextSiblingElement())
    {
        const int eventNumber(pEventNumbers->SetGlobalEventNumber(simulationEventNumber, atoi(pTiXmlElement->Attribute("Event_Number"))));
        const double weight(atof(pTiXmlElement->Attribute("Ratio_of_Integrands")));
        ConcatenateWeights::Event *pEvent = new ConcatenateWeights::Event();
        pEvent->SetEventNumber(eventNumber);
        pEvent->SetWeight(weight);
        m_events.push_back(pEvent);
    }

    pTiXmlDocument->Clear();
    delete pTiXmlDocument;

    this->ConcatenateIndividualWeightXml(process, energyFromXml, alpha4FromXml, alpha5FromXml);
    delete pEventNumbers;
}

//============================================================================

void ConcatenateWeights::ConcatenateIndividualWeightXml(std::string eventType, const int energy, const float alpha4, const float alpha5)
{
    TiXmlElement *pHeadTiXmlElement = new TiXmlElement("Process");
    m_pDocumentTiXmlElement->LinkEndChild(pHeadTiXmlElement);

    pHeadTiXmlElement->SetAttribute("EventType", eventType.c_str());
    pHeadTiXmlElement->SetAttribute("Energy", this->NumberToString(energy).c_str());
    pHeadTiXmlElement->SetDoubleAttribute("Alpha_Four", alpha4);
    pHeadTiXmlElement->SetDoubleAttribute("Alpha_Five", alpha5);

    for (EventVector::iterator iter = m_events.begin(); iter != m_events.end(); iter++)
    {
        ConcatenateWeights::Event *pEvent(*iter);
        TiXmlElement* pTiXmlElement = new TiXmlElement("Event");
        const int eventNumber(pEvent->GetEventNumber());

        if (std::find(m_eventsNeedingWeights.begin(), m_eventsNeedingWeights.end(), eventNumber) == m_eventsNeedingWeights.end())
            continue;

        pTiXmlElement->SetAttribute("Event_Number", eventNumber);
        pTiXmlElement->SetDoubleAttribute("Ratio_of_Integrands", pEvent->GetWeight());
        pHeadTiXmlElement->LinkEndChild(pTiXmlElement);
    }
    m_events.clear();
}

//============================================================================

void ConcatenateWeights::SaveConcatenatedWeightXml(int generatorNumber)
{
    std::string weightsFileName(m_weightsDirectory + "ConcatenatedWeights" + this->NumberToString(generatorNumber) + ".xml");
    bool success = m_pTiXmlResultsDocument->SaveFile(weightsFileName.c_str());
    std::cout << "Saving xml file : " << weightsFileName << std::endl;
    m_pTiXmlResultsDocument->Clear();
}

//============================================================================ Helper

template <class T>
std::string ConcatenateWeights::FileNumberToString(T Number) const 
{
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(3) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string ConcatenateWeights::AlphasToString(T Number) const 
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(5) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string ConcatenateWeights::NumberToString(T Number) const
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

//============================================================================
