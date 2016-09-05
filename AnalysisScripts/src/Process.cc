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
    m_pTrainTChain(NULL),
    m_pPostBDTTChain(NULL),
    m_numberOfEntries(std::numeric_limits<int>::max()),
    m_postBDTProcessWeight(std::numeric_limits<float>::max()),
    m_processWeight(std::numeric_limits<float>::max())
{
    m_pathToFiles = "/r06/lc/sg568/" + jobDescription + "/MarlinJobs/Detector_Model_" + detectorModel + "/Reconstruction_Variant_" + reconstructionVariant + "/" + eventType + "/" + this->NumberToString(energy) + "GeV/";

    this->MakeTChain();
    this->MakeSelection();
    this->SetBDTRootFiles();
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

TChain* Process::GetPostBDTTChain() const
{   
    return (TChain*)(m_pPostBDTTChain->Clone());
}

//=====================================================================

float Process::GetProcessWeight() const 
{
    return m_processWeight;
}

//=====================================================================

float Process::GetPostBDTProcessWeight() const
{
    return m_postBDTProcessWeight;
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

/*
RootFiles_BDT_ee_ll_1400GeV.root       RootFiles_BDT_ee_nunuqqqq_1400GeV.root       RootFiles_BDT_egamma_qqqqnu_BS_1400GeV.root   RootFiles_BDT_gammae_qqqqnu_EPA_1400GeV.root
RootFiles_BDT_ee_llqqqq_1400GeV.root   RootFiles_BDT_ee_qq_1400GeV.root             RootFiles_BDT_egamma_qqqqnu_EPA_1400GeV.root  RootFiles_BDT_gammagamma_qqqq_BS_BS_1400GeV.root
RootFiles_BDT_ee_lnuqq_1400GeV.root    RootFiles_BDT_ee_qqqq_1400GeV.root           RootFiles_BDT_gammae_qqqqe_BS_1400GeV.root    RootFiles_BDT_gammagamma_qqqq_BS_EPA_1400GeV.root
RootFiles_BDT_ee_lnuqqqq_1400GeV.root  RootFiles_BDT_egamma_qqqqe_BS_1400GeV.root   RootFiles_BDT_gammae_qqqqe_EPA_1400GeV.root   RootFiles_BDT_gammagamma_qqqq_EPA_BS_1400GeV.root
RootFiles_BDT_ee_nunuqq_1400GeV.root   RootFiles_BDT_egamma_qqqqe_EPA_1400GeV.root  RootFiles_BDT_gammae_qqqqnu_BS_1400GeV.root   RootFiles_BDT_gammagamma_qqqq_EPA_EPA_1400GeV.root
-bash-4.1$ pwd
/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/RootFilesPostBDT
*/

void Process::SetBDTRootFiles()
{
    m_pPostBDTTChain = new TChain("BDTTree");
    TString fileToAdd = "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/RootFilesPostBDT/RootFiles_BDT_" + m_eventType + "_" + this->NumberToString(m_energy) + "GeV.root";
    m_pPostBDTTChain->Add(fileToAdd);
    m_postBDTProcessWeight = m_luminosity * m_crossSection / (float)(m_pTChain->GetEntries());
}

//=====================================================================

void Process::MakeTChain()
{
    m_pTChain = new TChain("SelectionProcessorTree");
    m_pTrainTChain = new TChain("SelectionProcessorTree");

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
            std::string analysisTagString("Analysis_" + this->NumberToString(m_analysisTag));

            if (!file->IsDirectory() and fileCandidate.EndsWith("root") and fileCandidate.Contains(analysisTagString.c_str()) and fileCandidate.Contains("Selected")) // and m_pTChain->GetEntries() < 10000) 
            {
                TString rootFileToAdd = m_pathToFiles + "/" + fileCandidate.Data();

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

void Process::MakeSelection()
{
    double recoilMass(std::numeric_limits<double>::max());
    double transverseMomentum(std::numeric_limits<double>::max());
    double transverseEnergy(std::numeric_limits<double>::max());
    double cosThetaMissing(std::numeric_limits<double>::max());
    double cosThetaMostEnergeticTrack(std::numeric_limits<double>::max());
    double energyAroundMostEnergeticTrack(std::numeric_limits<double>::max());
    double y34(std::numeric_limits<double>::max());

    IntVector *nParticlesJets(NULL);
    IntVector *nChargedParticlesJets(NULL);

    DoubleVector *energyJets(NULL);
    DoubleVector *invMassWVectors(NULL);
    DoubleVector *invMassZVectors(NULL);

    m_pTChain->SetBranchAddress("RecoilMass", &recoilMass);
    m_pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
    m_pTChain->SetBranchAddress("TransverseEnergy", &transverseEnergy);
    m_pTChain->SetBranchAddress("CosThetaMissing", &cosThetaMissing);
    m_pTChain->SetBranchAddress("CosThetaMostEnergeticTrack",&cosThetaMostEnergeticTrack);
    m_pTChain->SetBranchAddress("EnergyAroundMostEnergeticTrack",&energyAroundMostEnergeticTrack);
    m_pTChain->SetBranchAddress("y34",&y34);
    m_pTChain->SetBranchAddress("NParticlesJets",&nParticlesJets);
    m_pTChain->SetBranchAddress("NChargedParticlesJets",&nChargedParticlesJets);
    m_pTChain->SetBranchAddress("EnergyJets",&energyJets);
    m_pTChain->SetBranchAddress("InvMassWVectors", &invMassWVectors);
    m_pTChain->SetBranchAddress("InvMassZVectors", &invMassZVectors);

    bool doesEventPassSelection(true);

    for (unsigned int event = 0; event < m_pTChain->GetEntries(); event++)
    {
        doesEventPassSelection = true;
        m_pTChain->GetEntry(event);

//        std::cout << recoilMass << " 250.0 : " << transverseMomentum << " 40 : " << transverseEnergy << " 150 : " << std::fabs(cosThetaMissing) << " 0.99 : " << std::fabs(cosThetaMostEnergeticTrack) << " 0.99 : " << energyAroundMostEnergeticTrack << " 2.0 : " << y34 << " 3.5 : " << std::endl;

        if (recoilMass < 250.0 or transverseMomentum < 40 or transverseEnergy < 150 or std::fabs(cosThetaMissing) > 0.99 or std::fabs(cosThetaMostEnergeticTrack) > 0.99 or y34 > 3.5) //energyAroundMostEnergeticTrack < 2.0 
        {
           doesEventPassSelection = false;
        }
/*
if (recoilMass < 250.0) std::cout << "Recoil Mass" << std::endl;
else if (transverseMomentum < 40) std::cout << "transverseMomentum" << std::endl;
else if (transverseEnergy < 150)std::cout << "transverseEnergy" << std::endl;
else if (std::fabs(cosThetaMissing) > 0.99)std::cout << "cosThetaMissing" << std::endl;
else if (std::fabs(cosThetaMostEnergeticTrack) > 0.99)std::cout << "cosThetaMostEnergeticTrack" << std::endl;
else if (energyAroundMostEnergeticTrack < 2.0)std::cout << "EnergyAroundMostEnergeticTrack" << std::endl;
else if (y34 > 3.5)std::cout << "Y34" << std::endl;
*/
        for (IntVector::iterator iter = nParticlesJets->begin(); iter != nParticlesJets->end(); iter++)
        {
            int nParticlesJets(*iter);
            if (nParticlesJets < 3)
            {
                doesEventPassSelection = false;
            }
        }

        for (IntVector::iterator iter = nChargedParticlesJets->begin(); iter != nChargedParticlesJets->end(); iter++)
        {
            int nChargedParticlesJets(*iter);
            if (nChargedParticlesJets < 2)
            {
                doesEventPassSelection = false;
            }
        }

        for (DoubleVector::iterator iter = energyJets->begin(); iter != energyJets->end(); iter++)
        {
            int energyJet(*iter);
            if (energyJet < 10.0)
            {
                doesEventPassSelection = false;
            }
        }

        bool goodBosonsW(true);

        for (DoubleVector::iterator iter = invMassWVectors->begin(); iter != invMassWVectors->end(); iter++)
        {
            int invMassW(*iter);
            if (invMassW < 60 or 88 < invMassW)
            {
                goodBosonsW = false;
            }
        }

        bool goodBosonsZ(true);

        for (DoubleVector::iterator iter = invMassZVectors->begin(); iter != invMassZVectors->end(); iter++)
        {
            int invMassZ(*iter);
            if (invMassZ < 85 or 100 < invMassZ)
            {
                goodBosonsZ = false;
            }
        }

        if (!goodBosonsW and !goodBosonsZ)
            doesEventPassSelection = false;

//        std::cout << "Process : " << m_eventType <<  ", Event number : " << event << ", doesEventPassSelection " << doesEventPassSelection << std::endl;

        m_doesEventPassSelection.insert(std::make_pair(event,doesEventPassSelection));
    }
}

//=====================================================================
