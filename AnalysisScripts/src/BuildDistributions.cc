/**
 *  @file   AnalysisScripts/src/BuildDistributions.cc 
 * 
 *  @brief  Implementation of the fit class.
 * 
 *  $Log: $
 */

#include "BuildDistributions.h"

#include "TSystem.h"
#include <fcntl.h>

void Pause();

//=====================================================================

BuildDistributions::BuildDistributions(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis, int nEvtsStart, int nEvtsEnd, std::string descriptor, std::string outputPath) : 
    m_processVector(processVector),
    m_pPostMVASelection(pCouplingAnalysis->GetPostMVASelection()),
    m_pCouplingAnalysis(pCouplingAnalysis),
    m_descriptor(descriptor),
    m_nEvtsStart(nEvtsStart),
    m_nEvtsEnd(nEvtsEnd),
    m_outputPath(outputPath),
    m_wBosonMass(80.385f),
    m_zBosonMass(91.1876f),
    m_nBins(10),
    m_rootFileName(outputPath + descriptor + "_BuildDistributionData.root")
{
    TH1::AddDirectory(kFALSE);

    // Output data file
    m_pTFile = new TFile(m_rootFileName.c_str(), "recreate");
    m_pTTree = new TTree("BuildDistributionTree", "BuildDistributionTree");
    m_pTTree->SetDirectory(m_pTFile);
}

//=====================================================================

BuildDistributions::~BuildDistributions()
{
    m_pTFile->cd();
    m_pTTree->Write();
    m_pTFile->Close();
    this->Clear();
    delete m_pTFile;
}

//=====================================================================

void BuildDistributions::SetNBins(const int &nBins)
{
    m_nBins = nBins;
}

//=====================================================================

void BuildDistributions::BuildDistribution()
{
    double alpha4Min(-0.02);
    double alpha4Max(0.0205);
    double alpha4Step(0.001);
    double alpha5Min(-0.02);
    double alpha5Max(0.0205);
    double alpha5Step(0.001);

    this->InitialiseReference();
    this->FillReferenceDistribution();

    for (double alpha4 = alpha4Min; alpha4 < alpha4Max; alpha4 = alpha4 + alpha4Step)
    {
        for (double alpha5 = alpha5Min; alpha5 < alpha5Max; alpha5 = alpha5 + alpha5Step)
        {
            this->Initialise();
            this->FillDistribution(alpha4, alpha5);

            std::string title_CosThetaStarSynWJets_vs_Bosons = "CosThetaStarSynWJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarWSynJets_vs_Bosons->SetTitle(title_CosThetaStarSynWJets_vs_Bosons.c_str());
            m_cosThetaStarWSynJets_vs_Bosons->SetName(title_CosThetaStarSynWJets_vs_Bosons.c_str());
            m_cosThetaStarWSynJets_vs_Bosons->Write();

            std::string title_CosThetaStarSynZJets_vs_Bosons = "CosThetaStarSynZJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarZSynJets_vs_Bosons->SetTitle(title_CosThetaStarSynZJets_vs_Bosons.c_str());
            m_cosThetaStarZSynJets_vs_Bosons->SetName(title_CosThetaStarSynZJets_vs_Bosons.c_str());
            m_cosThetaStarZSynJets_vs_Bosons->Write();

            std::string title_CosThetaStarSynWJets = "CosThetaStarSynWJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarWSynJets->SetTitle(title_CosThetaStarSynWJets.c_str());
            m_cosThetaStarWSynJets->SetName(title_CosThetaStarSynWJets.c_str());
            m_cosThetaStarWSynJets->Write();

            std::string title_CosThetaStarSynZJets = "CosThetaStarSynZJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarZSynJets->SetTitle(title_CosThetaStarSynZJets.c_str());
            m_cosThetaStarZSynJets->SetName(title_CosThetaStarSynZJets.c_str());
            m_cosThetaStarZSynJets->Write();

            std::string title_CosThetaStarSynWBosons = "CosThetaStarSynWBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarWSynBosons->SetTitle(title_CosThetaStarSynWBosons.c_str());
            m_cosThetaStarWSynBosons->SetName(title_CosThetaStarSynWBosons.c_str());
            m_cosThetaStarWSynBosons->Write();

            std::string title_CosThetaStarSynZBosons = "CosThetaStarSynZBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarZSynBosons->SetTitle(title_CosThetaStarSynZBosons.c_str());
            m_cosThetaStarZSynBosons->SetName(title_CosThetaStarSynZBosons.c_str());
            m_cosThetaStarZSynBosons->Write();
        }
    }
}

//=====================================================================

void BuildDistributions::EventWeightsForSingleEvent(int maxEventNumber)
{
    const double alpha4Min(-0.04);
    const double alpha4Max(0.041);
    const double alpha4Step(0.01);
    const double alpha5Min(-0.04);
    const double alpha5Max(0.041);
    const double alpha5Step(0.01);

    TH3F *pTH3F = new TH3F("AxisName","",100,alpha4Min,alpha4Max,100,alpha5Min,alpha5Max,100,0.75,1.25);
    pTH3F->GetXaxis()->SetTitle("#alpha_{4}");
    pTH3F->GetYaxis()->SetTitle("#alpha_{5}");
    pTH3F->GetZaxis()->SetTitle("Event Weight");

    for (const auto &pProcess: m_processVector)
    {
        if (pProcess->GetEventType() != "ee_nunuqqqq")
            continue;

        TChain *pTChain(pProcess->GetPostMVATChain());

        Int_t globalEventNumber(std::numeric_limits<int>::max());

        // Selection Variables
        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);

        int nEventsToProcess(pTChain->GetEntries() > maxEventNumber ? maxEventNumber : pTChain->GetEntries());

        for (unsigned int event = 0; event < nEventsToProcess; event++)
        {
            pTChain->GetEntry(event);

            float matrixElementWeight(1.f);
            std::string name("EventWeightsForEvent" + this->NumberToString(globalEventNumber));

            TGraph2D *pTGraph2D = new TGraph2D();
            pTGraph2D->SetTitle(name.c_str());

            for (double alpha4 = alpha4Min; alpha4 < alpha4Max; alpha4 = alpha4 + alpha4Step)
            {
                for (double alpha5 = alpha5Min; alpha5 < alpha5Max; alpha5 = alpha5 + alpha5Step)
                {
                    m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                    pTGraph2D->SetPoint(pTGraph2D->GetN(), alpha4, alpha5, matrixElementWeight);
                }
            }

            std::string plotName(name + ".C");
            std::string canvasName(name + "Canvas");

            TCanvas *pTCanvas = new TCanvas(canvasName.c_str(), canvasName.c_str(), 800, 600);
            pTH3F->Draw();
            pTGraph2D->Draw("PCOL same");
            pTCanvas->Update();
            pTCanvas->SaveAs(plotName.c_str());
            delete pTCanvas, pTGraph2D;
        }
    }
    delete pTH3F;
}

//=====================================================================

void BuildDistributions::InitialiseReference()
{
    m_cosThetaStarWSynJets_vs_BosonsRef = new TH2F(this->SafeName("CosThetaStarSynWJets_vs_BosonsRef"),"Reference Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarWSynJets_vs_BosonsRef->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
    m_cosThetaStarWSynJets_vs_BosonsRef->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    m_cosThetaStarZSynJets_vs_BosonsRef = new TH2F(this->SafeName("CosThetaStarSynZJets_vs_BosonsRef"),"Reference Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarZSynJets_vs_BosonsRef->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
    m_cosThetaStarZSynJets_vs_BosonsRef->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    m_cosThetaStarWSynJetsRef = new TH1F(this->SafeName("CosThetaStarSynWJetsRef"),"Reference Cos#theta_{WJets}^{*}",m_nBins,0,1);
    m_cosThetaStarWSynJetsRef->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
    m_cosThetaStarWSynJetsRef->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarZSynJetsRef = new TH1F(this->SafeName("CosThetaStarSynZJetsRef"),"Reference Cos#theta_{ZJets}^{*}",m_nBins,0,1);
    m_cosThetaStarZSynJetsRef->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
    m_cosThetaStarZSynJetsRef->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarWSynBosonsRef = new TH1F(this->SafeName("CosThetaStarSynWBosonsRef"),"Reference Cos#theta_{WBosons}^{*}",m_nBins,0,1);
    m_cosThetaStarWSynBosonsRef->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    m_cosThetaStarWSynBosonsRef->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarZSynBosonsRef = new TH1F(this->SafeName("CosThetaStarSynZBosonsRef"),"Reference Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
    m_cosThetaStarZSynBosonsRef->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    m_cosThetaStarZSynBosonsRef->GetYaxis()->SetTitle("Entries");
}

//=====================================================================

void BuildDistributions::Initialise()
{
    m_cosThetaStarWSynJets_vs_Bosons = new TH2F(this->SafeName("CosThetaStarSynWJets_vs_Bosons"),"Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarWSynJets_vs_Bosons->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
    m_cosThetaStarWSynJets_vs_Bosons->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    m_cosThetaStarZSynJets_vs_Bosons = new TH2F(this->SafeName("CosThetaStarSynZJets_vs_Bosons"),"Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarZSynJets_vs_Bosons->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
    m_cosThetaStarZSynJets_vs_Bosons->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    m_cosThetaStarWSynJets = new TH1F(this->SafeName("CosThetaStarSynWJets"),"Cos#theta_{WJets}^{*}",m_nBins,0,1);
    m_cosThetaStarWSynJets->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
    m_cosThetaStarWSynJets->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarZSynJets = new TH1F(this->SafeName("CosThetaStarSynZJets"),"Cos#theta_{ZJets}^{*}",m_nBins,0,1);
    m_cosThetaStarZSynJets->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
    m_cosThetaStarZSynJets->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarWSynBosons = new TH1F(this->SafeName("CosThetaStarSynWBosons"),"Cos#theta_{WBosons}^{*}",m_nBins,0,1);
    m_cosThetaStarWSynBosons->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    m_cosThetaStarWSynBosons->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarZSynBosons = new TH1F(this->SafeName("CosThetaStarSynZBosons"),"Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
    m_cosThetaStarZSynBosons->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    m_cosThetaStarZSynBosons->GetYaxis()->SetTitle("Entries");
}

//=====================================================================

TString BuildDistributions::SafeName(const TString &name)
{
    TObject *pTObject = gROOT->FindObject(name);
    if (pTObject) delete pTObject;
    return name;
}

//=====================================================================

void BuildDistributions::Clear()
{
    delete m_cosThetaStarWSynJetsRef, m_cosThetaStarWSynBosonsRef, m_cosThetaStarWSynJets_vs_BosonsRef, m_cosThetaStarZSynJetsRef, m_cosThetaStarZSynBosonsRef, m_cosThetaStarZSynJets_vs_BosonsRef;
}

//=====================================================================

void BuildDistributions::FillReferenceDistribution()
{
   for (const auto &pProcess: m_processVector)
    {
        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());
        const double wzSeparationCut(pProcess->GetWZSeparationCut());

        Int_t nIsolatedLeptons(std::numeric_limits<int>::max());
        Double_t transverseMomentum(std::numeric_limits<double>::max());
        Double_t invariantMassSystem(std::numeric_limits<double>::max());
        Double_t bdt(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynBosons(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet1(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet2(std::numeric_limits<double>::max());
        Double_t invariantMassSynBoson1(std::numeric_limits<double>::max());
        Double_t invariantMassSynBoson2(std::numeric_limits<double>::max());

        // Selection Variables
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("BDT", &bdt);
        // W or Z Boson Selection
        pTChain->SetBranchAddress("InvariantMassSynBoson1", &invariantMassSynBoson1);
        pTChain->SetBranchAddress("InvariantMassSynBoson2", &invariantMassSynBoson2);
        // BuildDistributions Variables
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

            bool isW(invariantMassSynBoson1 < wzSeparationCut && invariantMassSynBoson2 < wzSeparationCut);
            bool isZ(invariantMassSynBoson1 > wzSeparationCut && invariantMassSynBoson2 > wzSeparationCut);

            if (isW)
            {
                m_cosThetaStarWSynJets_vs_BosonsRef->Fill(cosThetaStarSynJet1, cosThetaStarSynBosons, weight);
                m_cosThetaStarWSynJets_vs_BosonsRef->Fill(cosThetaStarSynJet2, cosThetaStarSynBosons, weight);
                m_cosThetaStarWSynJetsRef->Fill(cosThetaStarSynJet1, weight);
                m_cosThetaStarWSynJetsRef->Fill(cosThetaStarSynJet2, weight);
                m_cosThetaStarWSynBosonsRef->Fill(cosThetaStarSynBosons, weight);
            }

            if (isZ)
            {
                m_cosThetaStarZSynJets_vs_BosonsRef->Fill(cosThetaStarSynJet1, cosThetaStarSynBosons, weight);
                m_cosThetaStarZSynJets_vs_BosonsRef->Fill(cosThetaStarSynJet2, cosThetaStarSynBosons, weight);
                m_cosThetaStarZSynJetsRef->Fill(cosThetaStarSynJet1, weight);
                m_cosThetaStarZSynJetsRef->Fill(cosThetaStarSynJet2, weight);
                m_cosThetaStarZSynBosonsRef->Fill(cosThetaStarSynBosons, weight);
            }
        }
        delete pTChain;
    }
}

//=====================================================================

void BuildDistributions::FillDistribution(const double alpha4, const double alpha5)
{
    for (const auto &pProcess: m_processVector)
    {
        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());
        const double wzSeparationCut(pProcess->GetWZSeparationCut());

        Int_t globalEventNumber(std::numeric_limits<int>::max());
        Int_t nIsolatedLeptons(std::numeric_limits<int>::max());
        Double_t transverseMomentum(std::numeric_limits<double>::max());
        Double_t invariantMassSystem(std::numeric_limits<double>::max());
        Double_t bdt(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynBosons(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet1(std::numeric_limits<double>::max());
        Double_t cosThetaStarSynJet2(std::numeric_limits<double>::max());
        Double_t invariantMassSynBoson1(std::numeric_limits<double>::max());
        Double_t invariantMassSynBoson2(std::numeric_limits<double>::max());

        // Selection Variables
        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("BDT", &bdt);
        // W or Z Boson Selection
        pTChain->SetBranchAddress("InvariantMassSynBoson1", &invariantMassSynBoson1);
        pTChain->SetBranchAddress("InvariantMassSynBoson2", &invariantMassSynBoson2);
        // BuildDistributions Variables
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

            bool isW(invariantMassSynBoson1 < wzSeparationCut && invariantMassSynBoson2 < wzSeparationCut);
            bool isZ(invariantMassSynBoson1 > wzSeparationCut && invariantMassSynBoson2 > wzSeparationCut);
            float matrixElementWeight(1.f);

            if (isW || isZ)
            {
                if (pProcess->GetEventType() == "ee_nunuqqqq")
                {
                    m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                }
            }

            if (isW)
            {
                m_cosThetaStarWSynJets_vs_Bosons->Fill(cosThetaStarSynJet1, cosThetaStarSynBosons, weight*matrixElementWeight);
                m_cosThetaStarWSynJets_vs_Bosons->Fill(cosThetaStarSynJet2, cosThetaStarSynBosons, weight*matrixElementWeight);
                m_cosThetaStarWSynJets->Fill(cosThetaStarSynJet1, weight*matrixElementWeight);
                m_cosThetaStarWSynJets->Fill(cosThetaStarSynJet2, weight*matrixElementWeight);
                m_cosThetaStarWSynBosons->Fill(cosThetaStarSynBosons, weight*matrixElementWeight);
            }

            if (isZ)
            {
                m_cosThetaStarZSynJets_vs_Bosons->Fill(cosThetaStarSynJet1, cosThetaStarSynBosons, weight*matrixElementWeight);
                m_cosThetaStarZSynJets_vs_Bosons->Fill(cosThetaStarSynJet2, cosThetaStarSynBosons, weight*matrixElementWeight);
                m_cosThetaStarZSynJets->Fill(cosThetaStarSynJet1, weight*matrixElementWeight);
                m_cosThetaStarZSynJets->Fill(cosThetaStarSynJet2, weight*matrixElementWeight);
                m_cosThetaStarZSynBosons->Fill(cosThetaStarSynBosons, weight*matrixElementWeight);
            }
        }
        delete pTChain;
    } 
}

//=====================================================================

std::string BuildDistributions::RandomName()
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
std::string BuildDistributions::NumberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================

void Pause()
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

//=====================================================================
