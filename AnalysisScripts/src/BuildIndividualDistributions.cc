/**
 *  @file   AnalysisScripts/src/BuildIndividualDistributions.cc 
 * 
 *  @brief  Implementation of the fit class.
 * 
 *  $Log: $
 */

#include "BuildIndividualDistributions.h"

#include "TSystem.h"
#include <fcntl.h>

void Pause2();

//=====================================================================

BuildIndividualDistributions::BuildIndividualDistributions(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis, int nEvtsStart, int nEvtsEnd, std::string descriptor, std::string outputPath) : 
    m_processVector(processVector),
    m_pPostMVASelection(pCouplingAnalysis->GetPostMVASelection()),
    m_pCouplingAnalysis(pCouplingAnalysis),
    m_descriptor(descriptor),
    m_nEvtsStart(nEvtsStart),
    m_nEvtsEnd(nEvtsEnd),
    m_outputPath(outputPath),
    m_nBins(10),
    m_rootFileName(outputPath + descriptor + "_BuildIndividualDistributionData.root")
{
    TH1::AddDirectory(kFALSE);

    if (!processVector.empty())
    {
        m_energy = processVector.at(0)->GetEnergy();
    }

    // Output data file
    m_pTFile = new TFile(m_rootFileName.c_str(), "recreate");
    //m_pTTree = new TTree("BuildDistributionTree", "BuildDistributionTree");
    //m_pTTree->SetDirectory(m_pTFile);
}

//=====================================================================

BuildIndividualDistributions::~BuildIndividualDistributions()
{
    m_pTFile->cd();
    //m_pTTree->Write();
    m_pTFile->Close();
    this->Clear();
    this->ClearReference();
    delete m_pTFile;
}

//=====================================================================

void BuildIndividualDistributions::SetNBins(const int &nBins)
{
    m_nBins = nBins;
}

//=====================================================================

void BuildIndividualDistributions::BuildDistribution(bool backgrounds)
{
    double alpha4Min(0.0);
    double alpha4Max(0.0);
    double alpha4Step(1.0);
    double alpha5Min(0.0);
    double alpha5Max(0.0);
    double alpha5Step(1.0);

    if (m_energy == 1400 && !backgrounds)
    {
        alpha4Min = -0.02;
        alpha4Max = 0.0205;
        alpha4Step = 0.001;
        alpha5Min = -0.02;
        alpha5Max = 0.0205;
        alpha5Step = 0.001;
    }
    else if (m_energy == 1400 && backgrounds)
    {
        alpha4Min = -0.045;
        alpha4Max = 0.0455;
        alpha4Step = 0.0025;
        alpha5Min = -0.045;
        alpha5Max = 0.0455;
        alpha5Step = 0.0025;
    }
    else if (m_energy == 3000 && !backgrounds)
    {
        alpha4Min = -0.002;
        alpha4Max = 0.00205;
        alpha4Step = 0.0001;
        alpha5Min = -0.002;
        alpha5Max = 0.00205;
        alpha5Step = 0.0001;
    }
    else if (m_energy == 3000 && backgrounds)
    {
        alpha4Min = -0.0092;
        alpha4Max = 0.0092;
        alpha4Step = 0.0001;
        alpha5Min = -0.0062;
        alpha5Max = 0.0062;
        alpha5Step = 0.0001;
    }

    this->InitialiseReference();
    this->FillReferenceDistribution();

    // Save all histograms for background channels only 
    for (const auto &pProcess: m_processVector)
    {
        std::string processName(pProcess->GetEventType());

        if (processName == "ee_nunuqqqq")
            continue;

        TH2F *pTH2F_J;
        if (m_cosThetaStarSynJetsRef.find(processName) != m_cosThetaStarSynJets.end())
            pTH2F_J = m_cosThetaStarSynJetsRef.at(processName);

        TH1F *pTH1F_B;
        if (m_cosThetaStarSynBosonsRef.find(processName) != m_cosThetaStarSynBosons.end())
            pTH1F_B  = m_cosThetaStarSynBosonsRef.at(processName);

        if (pTH2F_J == NULL or pTH1F_B == NULL)
            std::cout << "Problem related to initialisation of histograms." << std::endl;

        std::string title = "CosThetaStarSynJets_Alpha4_0.0_Alpha5_0.0_" + processName;
        pTH2F_J->SetTitle(this->SafeName(title));
        pTH2F_J->SetName(title.c_str());
        pTH2F_J->Write();
    }

    for (double alpha4 = alpha4Min; alpha4 < alpha4Max + (0.5 * alpha4Step); alpha4 = alpha4 + alpha4Step)
    {
        for (double alpha5 = alpha5Min; alpha5 < alpha5Max + (0.5 *alpha5Step); alpha5 = alpha5 + alpha5Step)
        {
            this->Initialise();
            this->FillDistribution(alpha4, alpha5);

            // Save histograms for signal channels only as others do not change
            for (const auto &pProcess: m_processVector)
            {
                std::string processName(pProcess->GetEventType());

                if (processName != "ee_nunuqqqq")
                    continue;

                TH2F *pTH2F_J;
                if (m_cosThetaStarSynJets.find(processName) != m_cosThetaStarSynJets.end())
                    pTH2F_J = m_cosThetaStarSynJets.at(processName);

                TH1F *pTH1F_B;
                if (m_cosThetaStarSynBosons.find(processName) != m_cosThetaStarSynBosons.end())
                    pTH1F_B  = m_cosThetaStarSynBosons.at(processName);

                if (pTH2F_J == NULL or pTH1F_B == NULL)
                    std::cout << "Problem related to initialisation of histograms." << std::endl;

                std::string title = "CosThetaStarSynJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5) + "_" + processName;
                pTH2F_J->SetTitle(this->SafeName(title));
                pTH2F_J->SetName(title.c_str());
                pTH2F_J->Write();
            }
        }
    }
}

//=====================================================================

void BuildIndividualDistributions::InitialiseReference()
{
    this->ClearReference();

    for (const auto &pProcess: m_processVector)
    {
        std::string processName(pProcess->GetEventType());

        std::string name2("CosThetaStarSynJetsRef_" + processName);
        std::string title2("Reference Cos#theta_{Jets}^{*} for " + processName);
        TH2F *pTH2F_J = new TH2F(this->SafeName(name2),title2.c_str(),m_nBins,0,1,m_nBins,0,1);
        pTH2F_J->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH2F_J->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynJetsRef.insert(std::make_pair(processName, pTH2F_J));

        std::string name3("CosThetaStarSynBosonsRef_" + processName);
        std::string title3("Reference Cos#theta_{Bosons}^{*} for " + processName);
        TH1F *pTH1F_B = new TH1F(this->SafeName(name3),title3.c_str(),m_nBins,0,1);
        pTH1F_B->GetXaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        pTH1F_B->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynBosonsRef.insert(std::make_pair(processName, pTH1F_B));
    }
}

//=====================================================================

void BuildIndividualDistributions::Initialise()
{
    this->Clear();

    for (const auto &pProcess: m_processVector)
    {
        std::string processName(pProcess->GetEventType());

        std::string name2("CosThetaStarSynJets_" + processName);
        std::string title2("Cos#theta_{Jets}^{*} for " + processName);
        TH2F *pTH2F_J = new TH2F(this->SafeName(name2),title2.c_str(),m_nBins,0,1,m_nBins,0,1);
        pTH2F_J->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH2F_J->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynJets.insert(std::make_pair(processName, pTH2F_J));

        std::string name3("CosThetaStarSynBosons_" + processName);
        std::string title3("Cos#theta_{Bosons}^{*} for " + processName);
        TH1F *pTH1F_B = new TH1F(this->SafeName(name3),title3.c_str(),m_nBins,0,1);
        pTH1F_B->GetXaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        pTH1F_B->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynBosons.insert(std::make_pair(processName, pTH1F_B));
    }
}

//=====================================================================

TString BuildIndividualDistributions::SafeName(const TString &name)
{
    TObject *pTObject = gROOT->FindObject(name);
    if (pTObject) delete pTObject;
    return name;
}

//=====================================================================

void BuildIndividualDistributions::ClearReference()
{
    for (const auto &pProcess: m_processVector)
    {
        std::string processName(pProcess->GetEventType());

        if (m_cosThetaStarSynJetsRef.find(processName) != m_cosThetaStarSynJetsRef.end())
        {
            TH2F *pTH2F_J = m_cosThetaStarSynJetsRef.at(processName);
            if (pTH2F_J != NULL) delete pTH2F_J;
        }

        if (m_cosThetaStarSynBosonsRef.find(processName) != m_cosThetaStarSynBosonsRef.end())
        {
            TH1F *pTH1F_B = m_cosThetaStarSynBosonsRef.at(processName);
            if (pTH1F_B != NULL) delete pTH1F_B;
        }
    }
     m_cosThetaStarSynJetsRef.clear();
     m_cosThetaStarSynBosonsRef.clear();
}

//=====================================================================

void BuildIndividualDistributions::Clear()
{
    for (const auto &pProcess: m_processVector)
    {
        std::string processName(pProcess->GetEventType());

        if (m_cosThetaStarSynJets.find(processName) != m_cosThetaStarSynJets.end())
        {
            TH2F *pTH2F_J = m_cosThetaStarSynJets.at(processName);
            if (pTH2F_J != NULL) delete pTH2F_J;
        }

        if (m_cosThetaStarSynBosons.find(processName) != m_cosThetaStarSynBosons.end())
        {
            TH1F *pTH1F_B = m_cosThetaStarSynBosons.at(processName);
            if (pTH1F_B != NULL) delete pTH1F_B;
        }
    }
     m_cosThetaStarSynJets.clear();
     m_cosThetaStarSynBosons.clear();
}

//=====================================================================

void BuildIndividualDistributions::FillReferenceDistribution()
{
    for (const auto &pProcess: m_processVector)
    {
        std::string processName(pProcess->GetEventType());
        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());

        TH2F *pTH2F_J;
        if (m_cosThetaStarSynJetsRef.find(processName) != m_cosThetaStarSynJetsRef.end())
            pTH2F_J = m_cosThetaStarSynJetsRef.at(processName);

        TH1F *pTH1F_B;
        if (m_cosThetaStarSynBosonsRef.find(processName) != m_cosThetaStarSynBosonsRef.end())
            pTH1F_B  = m_cosThetaStarSynBosonsRef.at(processName);

        if (pTH2F_J == NULL or pTH1F_B == NULL)
            std::cout << "Problem related to initialisation of histograms." << std::endl;

        Int_t nIsolatedLeptons(std::numeric_limits<int>::max());
        Double_t transverseMomentum(std::numeric_limits<double>::max());
        Double_t invariantMassSystem(std::numeric_limits<double>::max());
        Double_t bdt(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynBosons(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet1(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet2(std::numeric_limits<double>::max());
        Double_t energyBosonSyn1(std::numeric_limits<double>::max());
        Double_t energyBosonSyn2(std::numeric_limits<double>::max());
        Double_t momentumBosonSyn1(std::numeric_limits<double>::max());
        Double_t momentumBosonSyn2(std::numeric_limits<double>::max());

        // Selection Variables
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("BDT", &bdt);
        pTChain->SetBranchAddress("EnergyBosonSyn1", &energyBosonSyn1);
        pTChain->SetBranchAddress("EnergyBosonSyn2", &energyBosonSyn2);
        pTChain->SetBranchAddress("MomentumBosonSyn1", &momentumBosonSyn1);
        pTChain->SetBranchAddress("MomentumBosonSyn2", &momentumBosonSyn2);

        // BuildIndividualDistributions Variables
        pTChain->SetBranchAddress("CosThetaStarSynBosons", &cosThetaStarSynBosons);
        pTChain->SetBranchAddress("CosThetaStarSynJet1", &cosThetaStarSynJet1);
        pTChain->SetBranchAddress("CosThetaStarSynJet2", &cosThetaStarSynJet2);

        if (pTChain->GetEntries() < m_nEvtsStart)
            continue;

        if (pTChain->GetEntries() < m_nEvtsEnd)
            m_nEvtsEnd = pTChain->GetEntries();

        for (unsigned int event = m_nEvtsStart; event < m_nEvtsEnd; event++)
        {
            pTChain->GetEntry(event);

            // Cuts
            if (bdt < m_pPostMVASelection->GetBDTLowCut() or m_pPostMVASelection->GetBDTHighCut() < bdt)
                continue;
            if (nIsolatedLeptons < m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsLowCut() or m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsHighCut() < nIsolatedLeptons)
                continue;
            if (transverseMomentum < m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumLowCut() or m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumHighCut() < transverseMomentum)
                continue;
            if (invariantMassSystem < m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemLowCut() or m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemHighCut() < invariantMassSystem)
                continue;

            double boson1Mass(sqrt(energyBosonSyn1*energyBosonSyn1-momentumBosonSyn1*momentumBosonSyn1));
            double boson2Mass(sqrt(energyBosonSyn2*energyBosonSyn2-momentumBosonSyn2*momentumBosonSyn2));
            double cosThetaStarSynJetMostEnergetic(std::numeric_limits<double>::max());
            double cosThetaStarSynJetLeastEnergetic(std::numeric_limits<double>::max());

            if ((boson1Mass > boson2Mass && energyBosonSyn1 > energyBosonSyn2) || (boson2Mass > boson1Mass) && energyBosonSyn2 > energyBosonSyn1) // Most massive is most energetic
            {
                cosThetaStarSynJetMostEnergetic = cosThetaStarSynJet1;
                cosThetaStarSynJetLeastEnergetic = cosThetaStarSynJet2;
            }
            else // Least massive is most energetic
            {
                cosThetaStarSynJetMostEnergetic = cosThetaStarSynJet2;
                cosThetaStarSynJetLeastEnergetic = cosThetaStarSynJet1;
            }

            pTH2F_J->Fill(cosThetaStarSynJetMostEnergetic, cosThetaStarSynJetLeastEnergetic, weight);
            pTH1F_B->Fill(cosThetaStarSynBosons, weight);
        }
        delete pTChain;
    }
}

//=====================================================================

void BuildIndividualDistributions::FillDistribution(const double alpha4, const double alpha5)
{
    for (const auto &pProcess: m_processVector)
    {
        std::string processName(pProcess->GetEventType());
        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());

        TH2F *pTH2F_J;
        if (m_cosThetaStarSynJets.find(processName) != m_cosThetaStarSynJets.end())
            pTH2F_J = m_cosThetaStarSynJets.at(processName);

        TH1F *pTH1F_B;
        if (m_cosThetaStarSynBosons.find(processName) != m_cosThetaStarSynBosons.end())
            pTH1F_B  = m_cosThetaStarSynBosons.at(processName);

        if (pTH2F_J == NULL or pTH1F_B == NULL)
            std::cout << "Problem related to initialisation of histograms." << std::endl;

        Int_t globalEventNumber(std::numeric_limits<int>::max());
        Int_t nIsolatedLeptons(std::numeric_limits<int>::max());
        Double_t transverseMomentum(std::numeric_limits<double>::max());
        Double_t invariantMassSystem(std::numeric_limits<double>::max());
        Double_t bdt(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynBosons(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet1(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet2(std::numeric_limits<double>::max());
        Double_t energyBosonSyn1(std::numeric_limits<double>::max());
        Double_t energyBosonSyn2(std::numeric_limits<double>::max());
        Double_t momentumBosonSyn1(std::numeric_limits<double>::max());
        Double_t momentumBosonSyn2(std::numeric_limits<double>::max());

        // Selection Variables
        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("BDT", &bdt);
        pTChain->SetBranchAddress("EnergyBosonSyn1", &energyBosonSyn1);
        pTChain->SetBranchAddress("EnergyBosonSyn2", &energyBosonSyn2);
        pTChain->SetBranchAddress("MomentumBosonSyn1", &momentumBosonSyn1);
        pTChain->SetBranchAddress("MomentumBosonSyn2", &momentumBosonSyn2);

        // BuildIndividualDistributions Variables
        pTChain->SetBranchAddress("CosThetaStarSynBosons", &cosThetaStarSynBosons);
        pTChain->SetBranchAddress("CosThetaStarSynJet1", &cosThetaStarSynJet1);
        pTChain->SetBranchAddress("CosThetaStarSynJet2", &cosThetaStarSynJet2);

        if (pTChain->GetEntries() < m_nEvtsStart)
            continue;

        if (pTChain->GetEntries() < m_nEvtsEnd)
            m_nEvtsEnd = pTChain->GetEntries();

        for (unsigned int event = m_nEvtsStart; event < m_nEvtsEnd; event++)
        {
            pTChain->GetEntry(event);

            // Cuts
            if (bdt < m_pPostMVASelection->GetBDTLowCut() or m_pPostMVASelection->GetBDTHighCut() < bdt)
                continue;
            if (nIsolatedLeptons < m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsLowCut() or m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsHighCut() < nIsolatedLeptons)
                continue;
            if (transverseMomentum < m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumLowCut() or m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumHighCut() < transverseMomentum)
                continue;
            if (invariantMassSystem < m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemLowCut() or m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemHighCut() < invariantMassSystem)
                continue;

            float matrixElementWeight(1.f);

            if (pProcess->GetEventType() == "ee_nunuqqqq")
            {
                m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
            }

            double boson1Mass(sqrt(energyBosonSyn1*energyBosonSyn1-momentumBosonSyn1*momentumBosonSyn1));
            double boson2Mass(sqrt(energyBosonSyn2*energyBosonSyn2-momentumBosonSyn2*momentumBosonSyn2));
            double cosThetaStarSynJetMostEnergetic(std::numeric_limits<double>::max());
            double cosThetaStarSynJetLeastEnergetic(std::numeric_limits<double>::max());

            if ((boson1Mass > boson2Mass && energyBosonSyn1 > energyBosonSyn2) || (boson2Mass > boson1Mass) && energyBosonSyn2 > energyBosonSyn1) // Most massive is most energetic
            {
                cosThetaStarSynJetMostEnergetic = cosThetaStarSynJet1;
                cosThetaStarSynJetLeastEnergetic = cosThetaStarSynJet2;
            }
            else // Least massive is most energetic
            {
                cosThetaStarSynJetMostEnergetic = cosThetaStarSynJet2;
                cosThetaStarSynJetLeastEnergetic = cosThetaStarSynJet1;
            }

            pTH2F_J->Fill(cosThetaStarSynJetMostEnergetic, cosThetaStarSynJetLeastEnergetic, weight*matrixElementWeight);
            pTH1F_B->Fill(cosThetaStarSynBosons, weight*matrixElementWeight);
        }
        delete pTChain;
    } 
}

//=====================================================================

std::string BuildIndividualDistributions::RandomName()
{
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int strLen = sizeof(alphabet)-1;
    char genRandom;
    std::string str;
    for(int i=0; i < 10; i++)
    {
        genRandom = alphabet[rand()%strLen];
        str += genRandom;
    }
    return str;
}

//=====================================================================

template <class T>
std::string BuildIndividualDistributions::NumberToString(T number)
{
    if (number < 0.00000001 and -0.00000001 < number)
        return "0.0";

    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================

void Pause2()
{
#ifdef __unix__
    std::cout << "Press return to continue ..." << std::endl;
    int flag = fcntl(1, F_GETFL, 0);

    int key = 0;
    while(true)
    {
        gSystem->ProcessEvents();
        fcntl(1, F_SETFL, flag | O_NONBLOCK);
        key = getchar();

        if((key == '\n') || (key == '\r'))
            break;

        usleep(1000);
    }

    fcntl(1, F_SETFL, flag);
#else
    std::cout << "Pause() is only implemented for unix operating systems." << std::endl;
#endif
}


