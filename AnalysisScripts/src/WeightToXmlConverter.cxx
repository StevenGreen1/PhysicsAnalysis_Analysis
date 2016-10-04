/**
 *  @file   AnalysisScripts/src/WeightToXmlConverter.cxx
 *
 *  @brief  Implementation of the WeightToXmlConverter class.
 *
 *  $Log: $
 */
 
#include "WeightToXmlConverter.h"

//============================================================================

int main(int argc, char* argv[])
{
    std::string process("ee_nunuqqqq");
    int energy(1400);

    for (int i = -5; i < 5; i++)
    {
        for (int j = -5; j < 5; j++)
        {
            const float alpha4(i * 0.01);
            const float alpha5(j * 0.01);
            WeightToXmlConverter *pWeightToXmlConverter = new WeightToXmlConverter(process,energy,alpha4,alpha5,atoi(argv[1]));
        }
    }
    return 0;
}

//============================================================================

WeightToXmlConverter::WeightToXmlConverter(const std::string process, const int energy, const float alpha4, const float alpha5, const int whizardJobSet) :
    m_eventType(process),
    m_energy(energy),
    m_whizardJobSet(whizardJobSet),
    m_alpha4(alpha4),
    m_alpha5(alpha5)
{
    this->LoadASCII();
}

//============================================================================

void WeightToXmlConverter::LoadASCII()
{
    std::string folder("/r06/lc/sg568/PhysicsAnalysis/Generator/" + m_eventType + "/" + this->NumberToString(m_energy) + "GeV/WhizardJobSet" + this->NumberToString(m_whizardJobSet) + "/Alpha4_" + this->AlphasToStringReading(m_alpha4) + "_Alpha5_" + this->AlphasToStringReading(m_alpha5));
    std::cout << folder << std::endl;

    int nFilesToProcess(10);

    if (m_whizardJobSet == 0)
        nFilesToProcess = 350;

    for (unsigned int i = 1; i <= nFilesToProcess; i++)
    {
        m_events.clear();

        std::string fileName(folder);

        if (m_whizardJobSet == 0)
        {
            fileName += "/whizard.";
            fileName += this->FileNumberToString(i);
            fileName += ".evt";
        }

        else
        {
            fileName += "/WhizardJobSet" + this->NumberToString(m_whizardJobSet) + ".";
            fileName += this->FileNumberToString(i);
            fileName += ".evt";
        }

        ifstream file;
        file.open (fileName.c_str());

        if (!file.is_open()) return;

        std::string eventNumber;
        std::string weight;

        while (file >> eventNumber >> weight)
        {
            WeightToXmlConverter::Event *pEvent = new WeightToXmlConverter::Event();
//            pEvent->SetProcess(m_eventType);
//            pEvent->SetEnergy(m_energy);
//            pEvent->SetAlpha4(m_alpha4);
//            pEvent->SetAlpha5(m_alpha5);
            const int eventNumberInt(atoi(eventNumber.c_str())-1e3*(i-1));
            pEvent->SetEventNumber(eventNumberInt);
            pEvent->SetWeight(atof(weight.c_str()));
            m_events.push_back(pEvent); 
            std::cout << "For event number : " << eventNumber << ", the weight is " << weight << std::endl;
        }

        int generatorNumber = 1e3*m_whizardJobSet + i;
        std::string weightsFileName("/r06/lc/sg568/PhysicsAnalysis/Generator/" + m_eventType + "/" + this->NumberToString(m_energy) + "GeV/WhizardJobSet" + this->NumberToString(m_whizardJobSet) + "/Alpha4_" + this->AlphasToStringReading(m_alpha4) + "_Alpha5_" + this->AlphasToStringReading(m_alpha5) + "/Reweighting_GenN" + this->NumberToString(generatorNumber) + "_" + m_eventType + "_" + this->NumberToString(m_energy) + "GeV_Alpha4_" + this->AlphasToStringWriting(m_alpha4) + "_Alpha5_" + this->AlphasToStringWriting(m_alpha5) + ".xml");
        this->SaveXml(weightsFileName);
    }
    return;
}

//============================================================================

void WeightToXmlConverter::SaveXml(std::string weightsFileName)
{
    TiXmlDocument tiXmlDocument;

    TiXmlElement *pHeadTiXmlElement = new TiXmlElement("Process");
    tiXmlDocument.LinkEndChild(pHeadTiXmlElement);

    pHeadTiXmlElement->SetAttribute("EventType", m_eventType.c_str());
    pHeadTiXmlElement->SetAttribute("Energy", this->NumberToString(m_energy).c_str());
    pHeadTiXmlElement->SetDoubleAttribute("Alpha_Four", m_alpha4);
    pHeadTiXmlElement->SetDoubleAttribute("Alpha_Five", m_alpha5);

    for (EventVector::iterator iter = m_events.begin(); iter != m_events.end(); iter++)
    {
        WeightToXmlConverter::Event *pEvent(*iter);
        TiXmlElement* pTiXmlElement = new TiXmlElement("Event");
        pTiXmlElement->SetAttribute("Event_Number", pEvent->GetEventNumber());
        pTiXmlElement->SetDoubleAttribute("Ratio_of_Integrands", pEvent->GetWeight());
        pHeadTiXmlElement->LinkEndChild(pTiXmlElement);
    }

    bool success = tiXmlDocument.SaveFile(weightsFileName.c_str());

    tiXmlDocument.Clear();
}

//============================================================================

template <class T>
std::string WeightToXmlConverter::FileNumberToString(T Number)
{
    std::ostringstream ss;
    ss << setfill('0') << setw(3) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string WeightToXmlConverter::AlphasToStringReading(T Number)
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(5) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string WeightToXmlConverter::AlphasToStringWriting(T Number)
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(5) << Number;
    return ss.str();
}

//============================================================================

template <class T>
std::string WeightToXmlConverter::NumberToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

//============================================================================
