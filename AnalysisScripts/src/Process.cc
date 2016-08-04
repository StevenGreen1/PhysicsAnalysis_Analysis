/**
 *  @file   AnalysisScripts/src/Process.cc 
 * 
 *  @brief  Implementation of the process class.
 * 
 *  $Log: $
 */

#include "Process.h"

//=====================================================================

Process::Process(std::string jobDescription, std::string detectorModel, std::string reconstructionVariant, std::string eventType, const float crossSection, const float luminosity, const int energy, const int analysisTag) :
    m_jobDescription(jobDescription),
    m_detectorModel(detectorModel),
    m_reconstructionVariant(reconstructionVariant),
    m_eventType(eventType),
    m_crossSection(crossSection),
    m_luminosity(luminosity),
    m_energy(energy),
    m_analysisTag(analysisTag),
    m_pTChain(NULL),
    m_numberOfEntries(std::numeric_limits<int>::max()),
    m_processWeight(std::numeric_limits<float>::max())
{
    m_pathToFiles = "/r06/lc/sg568/" + jobDescription + "/MarlinJobs/Detector_Model_" + detectorModel + "/Reconstruction_Variant_" + reconstructionVariant + "/" + eventType + "/" + this->NumberToString(energy) + "GeV/";

    this->MakeTChain();
}

//=====================================================================

TChain* Process::GetTChain() const
{
    return m_pTChain;
}

//=====================================================================

float Process::GetProcessWeight() const 
{
    return m_processWeight;
}

//=====================================================================

std::string Process::GetEventType() const 
{
    return m_eventType;
}

//=====================================================================

int Process::GetAnalysisTag() const
{
    return m_analysisTag;
}

//=====================================================================

void Process::Print() const 
{
    std::cout << "For the process   : " << m_eventType << std::endl
              << "Det Model         : " << m_detectorModel << std::endl
              << "Reco Var          : " << m_reconstructionVariant << std::endl
              << "Cross Section     : " << m_crossSection << std::endl
              << "Luminosity        : " << m_luminosity << std::endl
              << "Number of Entries : " << m_numberOfEntries << std::endl
              << "Process Weight    : " << m_processWeight << std::endl
              << "Analysis Tag      : " << m_analysisTag << std::endl;
}

//=====================================================================

void Process::MakeTChain()
{
    m_pTChain = new TChain("SelectionProcessorTree");
//    std::string rootFilesToAdd = m_pathToFiles + "*Analysis_" + this->NumberToString(m_analysisTag) + "_*Selected.root";
//    std::string extension("root");

    TSystemDirectory directory(m_pathToFiles.c_str(), m_pathToFiles.c_str());
    TList *listOfFiles = directory.GetListOfFiles();

    if (listOfFiles) 
    {
        TSystemFile *file;
        TString fileCandidate;
        TIter next(listOfFiles);

        while ((file=(TSystemFile*)next())) 
        {
            fileCandidate = file->GetName();
            std::string analysisTagString("Analysis_" + this->NumberToString(m_analysisTag));

            if (!file->IsDirectory() and fileCandidate.EndsWith("root") and fileCandidate.Contains(analysisTagString.c_str()) and fileCandidate.Contains("Selected") and m_pTChain->GetEntries() < 10000) 
            {
                TString rootFileToAdd = m_pathToFiles + "/" + fileCandidate.Data();
                m_pTChain->Add(rootFileToAdd.Data());
            }
        }
    }

//    m_pTChain->Add(rootFilesToAdd.c_str(),1000);
    m_numberOfEntries = m_pTChain->GetEntries();
    m_processWeight = m_luminosity * m_crossSection / (float)(m_numberOfEntries);
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
