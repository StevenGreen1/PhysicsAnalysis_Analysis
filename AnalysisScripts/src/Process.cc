/**
 *  @file   AnalysisScripts/src/Process.cc 
 * 
 *  @brief  Implementation of the process class.
 * 
 *  $Log: $
 */

#include "Process.h"

//=====================================================================

Process::Process(std::string jobDescription, std::string detectorModel, std::string reconstructionVariant, std::string eventType, const float crossSection, const float luminoscity, const int energy) :
    m_jobDescription(jobDescription),
    m_detectorModel(detectorModel),
    m_reconstructionVariant(reconstructionVariant),
    m_eventType(eventType),
    m_crossSection(crossSection),
    m_luminoscity(luminoscity),
    m_energy(energy),
    m_pTChain(NULL),
    m_numberOfEntries(std::numeric_limits<int>::max()),
    m_processWeight(std::numeric_limits<float>::max())
{
    m_pathToFiles = "/r06/lc/sg568/" + jobDescription + "/MarlinJobs/Detector_Model_" + detectorModel + "/Reconstruction_Variant_" + reconstructionVariant + "/" + eventType + "/" + this->NumberToString(energy) + "GeV/";

    this->MakeTChain();
}

//=====================================================================

TChain* Process::GetTChain()
{
    return m_pTChain;
}

//=====================================================================

float Process::GetProcessWeight()
{
    return m_processWeight;
}

//=====================================================================

void Process::Print()
{
    std::cout << "For the process   : " << m_eventType << std::endl
              << "Det Model         : " << m_detectorModel << std::endl
              << "Reco Var          : " << m_reconstructionVariant << std::endl
              << "Cross Section     : " << m_crossSection << std::endl
              << "Luminoscity       : " << m_luminoscity << std::endl
              << "Number of Entries : " << m_numberOfEntries << std::endl
              << "Process Weight    : " << m_processWeight << std::endl;
}

//=====================================================================

void Process::MakeTChain()
{
    m_pTChain = new TChain("SelectionProcessorTree");
    std::string rootFilesToAdd = m_pathToFiles + "*Selected.root";
    m_pTChain->Add(rootFilesToAdd.c_str());
    m_numberOfEntries = m_pTChain->GetEntries();
    m_processWeight = m_luminoscity * m_crossSection / (float)(m_numberOfEntries);
}

//=====================================================================

template <class T>
std::string Process::NumberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
