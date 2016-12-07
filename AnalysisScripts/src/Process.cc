/**
 *  @file   AnalysisScripts/src/Process.cc 
 * 
 *  @brief  Implementation of the process class.
 * 
 *  $Log: $
 */

#include "Process.h"

//=====================================================================

Process::Process(std::string jobDescription, std::string detectorModel, std::string reconstructionVariant, std::string pandoraPFOs, std::string jetClusteringMode, const int nJetsToCluster, std::string jetClusteringAlgorithm, std::string jetClusteringRadius, const float wzSeparationCut, std::string eventType, const float crossSection, const float luminosity, const int energy, const int analysisTag, bool quickLoad) :
    m_jobDescription(jobDescription),
    m_detectorModel(detectorModel),
    m_reconstructionVariant(reconstructionVariant),
    m_pandoraPFOs(pandoraPFOs),
    m_jetClusteringMode(jetClusteringMode),
    m_nJetsToCluster(nJetsToCluster),
    m_jetClusteringAlgorithm(jetClusteringAlgorithm),
    m_jetClusteringRadius(jetClusteringRadius),
    m_wzSeparationCut(wzSeparationCut),
    m_eventType(eventType),
    m_crossSection(crossSection),
    m_luminosity(luminosity),
    m_energy(energy),
    m_analysisTag(analysisTag),
    m_pTChain(NULL),
    m_pTrainTChain(NULL),
    m_pPostMVATChain(NULL),
    m_numberOfEntries(std::numeric_limits<int>::max()),
    m_postMVAProcessWeight(std::numeric_limits<float>::max()),
    m_processWeight(std::numeric_limits<float>::max())
{
    if (pandoraPFOs == "SelectedPandoraPFANewPFOs")
        m_rootSuffix += "S";
    else if (pandoraPFOs == "TightSelectedPandoraPFANewPFOs")
        m_rootSuffix += "T";
    else if (pandoraPFOs == "LooseSelectedPandoraPFANewPFOs")
        m_rootSuffix += "L";

    m_rootSuffix += "PFOs_";

    if (jetClusteringAlgorithm == "kt_algorithm")
        m_rootSuffix += "kt";
    else if (jetClusteringAlgorithm == "cambridge_algorithm")
        m_rootSuffix += "cam";
    else if (jetClusteringAlgorithm == "ee_kt_algorithm")
        m_rootSuffix += "ee_kt";

    if (analysisTag >= 11)
        m_rootSuffix += "_";
    else 
        m_rootSuffix += "_2jets_";

    if (jetClusteringRadius == "0.5")
        m_rootSuffix += "0p50";
    else if (jetClusteringRadius == "0.7")
        m_rootSuffix += "0p70";
    else if (jetClusteringRadius == "0.9")
        m_rootSuffix += "0p90";
    else if (jetClusteringRadius == "1.0")
        m_rootSuffix += "1p00";
    else if (jetClusteringRadius == "1.1")
        m_rootSuffix += "1p10";

    m_pathToFiles = "/r06/lc/sg568/" + jobDescription + "/MarlinJobs/Detector_Model_" + detectorModel + "/Reconstruction_Variant_" + reconstructionVariant + "/" + eventType + "/" + this->NumberToString(energy) + "GeV/AnalysisTag" + this->NumberToString(analysisTag) + "/" + m_rootSuffix + "/";

    if (!quickLoad)
        this->MakeTChain();

    this->SetMVARootFiles();
}

//=====================================================================

Process::~Process()
{
}

//=====================================================================

TChain* Process::GetTChain() const
{
    return (TChain*)(m_pTChain->Clone());
}

//=====================================================================

TChain* Process::GetTrainingTChain() const
{
    return (TChain*)(m_pTrainTChain->Clone());
}

//=====================================================================

TChain* Process::GetPostMVATChain() const
{   
    return (TChain*)(m_pPostMVATChain->Clone());
}

//=====================================================================

float Process::GetProcessWeight() const 
{
    return m_processWeight;
}

//=====================================================================

float Process::GetPostMVAProcessWeight() const
{
    return m_postMVAProcessWeight;
}

//=====================================================================

float Process::GetWZSeparationCut() const
{
    return m_wzSeparationCut;
}

//=====================================================================

std::string Process::GetEventType() const 
{
    return m_eventType;
}

//=====================================================================

float Process::GetCrossSection() const
{
    return m_crossSection;
}

//=====================================================================

float Process::GetLuminosity() const
{
    return m_luminosity;
}

//=====================================================================

int Process::GetEnergy() const
{
    return m_energy;
}

//=====================================================================

int Process::GetAnalysisTag() const
{
    return m_analysisTag;
}

//=====================================================================

std::string Process::GetRootSuffix() const
{
    return m_rootSuffix;
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

bool Process::DoesEventPassCuts(int eventNumber) const
{
    return m_doesEventPassSelection.at(eventNumber);
}

//=====================================================================

void Process::SetMVARootFiles()
{
    m_pPostMVATChain = new TChain("MVATree");
    TString fileToAdd = "/r06/lc/sg568/PhysicsAnalysis/Analysis/RootFilesPostMVA/RootFiles_Multivariant_" + m_eventType + "_" + this->NumberToString(m_energy) + "GeV_" + m_rootSuffix + "_AnalysisTag" + this->NumberToString(m_analysisTag) + ".root";
    m_pPostMVATChain->Add(fileToAdd);
    m_postMVAProcessWeight = m_luminosity * m_crossSection / (float)(m_pPostMVATChain->GetEntries());
}

//=====================================================================

void Process::MakeTChain()
{
    m_pTChain = new TChain("AnalysisProcessorTree");
    m_pTrainTChain = new TChain("AnalysisProcessorTree");

    TSystemDirectory directory(m_pathToFiles.c_str(), m_pathToFiles.c_str());
    TList *listOfFiles = directory.GetListOfFiles();
    listOfFiles->Sort(); // Alphabetises the list

    bool trainingSample(false);

    if (listOfFiles) 
    {
        TSystemFile *file;
        TString fileCandidate;
        TIter next(listOfFiles);
        while ((file=(TSystemFile*)next())) 
        {
            fileCandidate = file->GetName();
            std::string analysisTagString("Tag" + this->NumberToString(m_analysisTag));

            if (!file->IsDirectory() and fileCandidate.EndsWith("root") and fileCandidate.Contains(analysisTagString.c_str()) and fileCandidate.Contains(m_rootSuffix.c_str())) // and m_pTrainTChain->GetEntries() < 50000) // and m_pTChain->GetEntries() < 50000) 
            {
                if (m_eventType == "ee_nunuqqqq" and m_energy == 1400)
                {
                    std::string fileCandidate2 = fileCandidate.Data();
                    std::string startDel = "GenN_";
                    std::string stopDel = "_1000_0_";
                    unsigned firstLim = fileCandidate2.find(startDel);
                    unsigned lastLim = fileCandidate2.find(stopDel);
                    std::string strNew = fileCandidate2.substr (firstLim+5,lastLim-firstLim);
                    int simulationNumber = atoi(strNew.c_str());
                    if (simulationNumber < 1000)
                        continue;
                }
                else if (m_eventType == "ee_nunuqqqq" and m_energy == 3000)
                {
                    std::string fileCandidate2 = fileCandidate.Data();
                    std::string startDel = "GenN_";
                    std::string stopDel = "_100_0_";
                    unsigned firstLim = fileCandidate2.find(startDel);
                    unsigned lastLim = fileCandidate2.find(stopDel);
                    std::string strNew = fileCandidate2.substr (firstLim+5,lastLim-firstLim);
                    int simulationNumber = atoi(strNew.c_str());
                    if (simulationNumber < 1000)
                        continue;
                }

                TString rootFileToAdd = m_pathToFiles + fileCandidate.Data();

                if (trainingSample)
                {
                    m_pTChain->Add(rootFileToAdd.Data());
                    trainingSample = false;
                }
                else
                {
                    m_pTrainTChain->Add(rootFileToAdd.Data()); 
                    trainingSample = true;
                }
            }
        }
    }

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
