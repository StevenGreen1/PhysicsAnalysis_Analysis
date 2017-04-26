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
    m_rootFileName(outputPath + descriptor + "_BuildDistributionData.root"),
    m_splitDistributions(false)
{
    TH1::AddDirectory(kFALSE);

    if (!processVector.empty())
    {
        m_energy = processVector.at(0)->GetEnergy();
    }

    m_lowMVV = 0.f;
    m_highMVV = (float)(m_energy);
    const float binWidth(50.f);
    m_nBinsMVV = round((m_highMVV-m_lowMVV)/binWidth);

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

void BuildDistributions::BuildDistribution(bool backgrounds)
{
    double alpha4Min(0.0);
    double alpha4Max(0.0);
    double alpha4Step(1.0);
    double alpha5Min(0.0);
    double alpha5Max(0.0);
    double alpha5Step(1.0);

    if (m_energy == 1400 && !backgrounds)
    {
        alpha4Min = -0.015;
        alpha4Max = 0.0155;
        alpha4Step = 0.001;
        alpha5Min = -0.015;
        alpha5Max = 0.0155;
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

    this->Initialise();
    this->FillReferenceDistribution();

    for (double alpha4 = alpha4Min; alpha4 < alpha4Max + (0.5 * alpha4Step); alpha4 = alpha4 + alpha4Step)
    {
        for (double alpha5 = alpha5Min; alpha5 < alpha5Max + (0.5 * alpha5Step); alpha5 = alpha5 + alpha5Step)
        {
            this->FillDistribution(alpha4, alpha5);

            std::string title_CosThetaStarSynJets = "CosThetaStarSynJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarSynJets->SetTitle(title_CosThetaStarSynJets.c_str());
            m_cosThetaStarSynJets->SetName(title_CosThetaStarSynJets.c_str());
            m_cosThetaStarSynJets->Write();

            std::string title_CosThetaStarSynBosons = "CosThetaStarSynBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarSynBosons->SetTitle(title_CosThetaStarSynBosons.c_str());
            m_cosThetaStarSynBosons->SetName(title_CosThetaStarSynBosons.c_str());
            m_cosThetaStarSynBosons->Write();

            std::string title_MVV = "MVV_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_mVVSynBosons->SetTitle(title_MVV.c_str());
            m_mVVSynBosons->SetName(title_MVV.c_str());
            m_mVVSynBosons->Write();
        }
    }
}

//=====================================================================

void BuildDistributions::MCBuildDistribution()
{
    TH2F *pTH2F = new TH2F("pTH2F","",10,0,1,10,0,1);
    TH1F *pTH1F = new TH1F("pTH1F","",10,0,1);
    TH1F *pTH1Fw = new TH1F("pTH1Fw","",10,0,1);
    TH1F *pTH1FmVV = new TH1F("pTH1FmVV","",28,200,3000);
    TH1F *pTH1FmVVw = new TH1F("pTH1FmVVw","",28,200,3000);

    for (const auto &pProcess: m_processVector)
    {
        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());

        Int_t globalEventNumber(std::numeric_limits<int>::max());
        Double_t quarkEnergy1(std::numeric_limits<double>::max());
        Double_t quarkPx1(std::numeric_limits<double>::max());
        Double_t quarkPy1(std::numeric_limits<double>::max());
        Double_t quarkPz1(std::numeric_limits<double>::max());
        Double_t quarkEnergy2(std::numeric_limits<double>::max());
        Double_t quarkPx2(std::numeric_limits<double>::max());
        Double_t quarkPy2(std::numeric_limits<double>::max());
        Double_t quarkPz2(std::numeric_limits<double>::max());
        Double_t quarkEnergy3(std::numeric_limits<double>::max());
        Double_t quarkPx3(std::numeric_limits<double>::max());
        Double_t quarkPy3(std::numeric_limits<double>::max());
        Double_t quarkPz3(std::numeric_limits<double>::max());
        Double_t quarkEnergy4(std::numeric_limits<double>::max());
        Double_t quarkPx4(std::numeric_limits<double>::max());
        Double_t quarkPy4(std::numeric_limits<double>::max());
        Double_t quarkPz4(std::numeric_limits<double>::max());
        Double_t mVV(std::numeric_limits<double>::max());

        // BuildDistributions Variables
        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("QuarkEnergy1", &quarkEnergy1);
        pTChain->SetBranchAddress("QuarkPx1", &quarkPx1);
        pTChain->SetBranchAddress("QuarkPy1", &quarkPy1);
        pTChain->SetBranchAddress("QuarkPz1", &quarkPz1);
        pTChain->SetBranchAddress("QuarkEnergy2", &quarkEnergy2);
        pTChain->SetBranchAddress("QuarkPx2", &quarkPx2);
        pTChain->SetBranchAddress("QuarkPy2", &quarkPy2);
        pTChain->SetBranchAddress("QuarkPz2", &quarkPz2);
        pTChain->SetBranchAddress("QuarkEnergy3", &quarkEnergy3);
        pTChain->SetBranchAddress("QuarkPx3", &quarkPx3);
        pTChain->SetBranchAddress("QuarkPy3", &quarkPy3);
        pTChain->SetBranchAddress("QuarkPz3", &quarkPz3);
        pTChain->SetBranchAddress("QuarkEnergy4", &quarkEnergy4);
        pTChain->SetBranchAddress("QuarkPx4", &quarkPx4);
        pTChain->SetBranchAddress("QuarkPy4", &quarkPy4);
        pTChain->SetBranchAddress("QuarkPz4", &quarkPz4);
        pTChain->SetBranchAddress("InvariantMassSystem", &mVV);

        if (pTChain->GetEntries() < m_nEvtsStart)
            continue;

        if (pTChain->GetEntries() < m_nEvtsEnd)
            m_nEvtsEnd = pTChain->GetEntries();

        int nEventsToProcess(m_nEvtsEnd-m_nEvtsStart);
        weight = weight * pTChain->GetEntries() / (double)(nEventsToProcess);

        for (unsigned int event = m_nEvtsStart; event < m_nEvtsEnd; event++)
        {
            pTChain->GetEntry(event);
            float matrixElementWeight(1.f);
            TLorentzVector *quark1 = new TLorentzVector(quarkPx1, quarkPy1, quarkPz1, quarkEnergy1);
            TLorentzVector *quark2 = new TLorentzVector(quarkPx2, quarkPy2, quarkPz2, quarkEnergy2);
            TLorentzVector *quark3 = new TLorentzVector(quarkPx3, quarkPy3, quarkPz3, quarkEnergy3);
            TLorentzVector *quark4 = new TLorentzVector(quarkPx4, quarkPy4, quarkPz4, quarkEnergy4);
            double cosThetaStarMC1(-2.f), cosThetaStarMC2(-2.f);
            this->PairQuarks(quark1, quark2, quark3, quark4, cosThetaStarMC1, cosThetaStarMC2);
            pTH2F->Fill(cosThetaStarMC1, cosThetaStarMC2, weight);
            pTH1F->Fill(cosThetaStarMC1, weight);
            pTH1F->Fill(cosThetaStarMC2, weight);

            m_pCouplingAnalysis->GetWeight(globalEventNumber, 0.005, 0.005, matrixElementWeight);
            pTH1Fw->Fill(cosThetaStarMC1,matrixElementWeight*weight);
            pTH1Fw->Fill(cosThetaStarMC2,matrixElementWeight*weight);

            pTH1FmVV->Fill(mVV, weight);
            pTH1FmVVw->Fill(mVV, matrixElementWeight*weight);

            delete quark1, quark2, quark3, quark4;
        }
    }

    TCanvas *pTCanvas = new TCanvas("pTCanvas","");
    pTCanvas->Draw();
    pTH2F->Draw();
    pTCanvas->SaveAs("2DMCHist.C");
    pTCanvas->SaveAs("2DMCHist.pdf");
    pTCanvas->SaveAs("2DMCHist.png");
    delete pTCanvas;

    pTCanvas = new TCanvas("pTCanvas","");
    pTH1F->Draw();
    pTCanvas->SaveAs("1DMCHist.C");
    pTCanvas->SaveAs("1DMCHist.pdf");
    pTCanvas->SaveAs("1DMCHist.png");

    pTCanvas = new TCanvas("pTCanvas","");
    pTH1Fw->Draw();
    pTCanvas->SaveAs("1DMCHistw.C");
    pTCanvas->SaveAs("1DMCHistw.pdf");
    pTCanvas->SaveAs("1DMCHistw.png");

    pTCanvas = new TCanvas("pTCanvas","");
    pTH1FmVV->Draw();
    pTCanvas->SaveAs("1DMCHistmVV.C");
    pTCanvas->SaveAs("1DMCHistmVV.pdf");
    pTCanvas->SaveAs("1DMCHistmVV.png");

    pTCanvas = new TCanvas("pTCanvas","");
    pTH1FmVVw->Draw();
    pTCanvas->SaveAs("1DMCHistmVVw.C");
    pTCanvas->SaveAs("1DMCHistmVVw.pdf");
    pTCanvas->SaveAs("1DMCHistmVVw.png");

}

//=====================================================================

void BuildDistributions::PairQuarks(TLorentzVector *quark1, TLorentzVector *quark2, TLorentzVector *quark3, TLorentzVector *quark4, double &cosThetaStar1, double &cosThetaStar2)
{
    TLorentzVector pairing1a = *quark1 + *quark2; 
    TLorentzVector pairing1b = *quark3 + *quark4; 
    TLorentzVector pairing2a = *quark1 + *quark3; 
    TLorentzVector pairing2b = *quark2 + *quark4; 
    TLorentzVector pairing3a = *quark1 + *quark4; 
    TLorentzVector pairing3b = *quark2 + *quark3; 

    double metric1((pairing1a.M() - pairing1b.M())*(pairing1a.M() - pairing1b.M()));
    double metric2((pairing2a.M() - pairing2b.M())*(pairing2a.M() - pairing2b.M()));
    double metric3((pairing3a.M() - pairing3b.M())*(pairing3a.M() - pairing3b.M()));

    if (metric1 < metric2 && metric1 < metric3)
    {
//        if (std::fabs(pairing1a.M() - 91.f) < 1.f)
            this->CalculateCosThetaStar(quark1,quark2,cosThetaStar1);

//        if (std::fabs(pairing1b.M() - 91.f) < 1.f)
            this->CalculateCosThetaStar(quark3,quark4,cosThetaStar2);

    }
    else if (metric2 < metric1 && metric2 < metric3)
    {
//        if (std::fabs(pairing2a.M() - 91.f) < 1.f)
            this->CalculateCosThetaStar(quark1,quark3,cosThetaStar1);

//        if (std::fabs(pairing2b.M() - 91.f) < 1.f)
            this->CalculateCosThetaStar(quark2,quark4,cosThetaStar2);
    }
    else if (metric3 < metric1 && metric3 < metric2)
    {
//        if (std::fabs(pairing3a.M() - 91.f) < 1.f)
            this->CalculateCosThetaStar(quark1,quark4,cosThetaStar1);

//        if (std::fabs(pairing3b.M() - 91.f) < 1.f)
            this->CalculateCosThetaStar(quark2,quark3,cosThetaStar2);
    }
}

//=====================================================================

void BuildDistributions::CalculateCosThetaStar(TLorentzVector *quark1, TLorentzVector *quark2, double &cosThetaStar)
{
    cosThetaStar = -1.f;
    TLorentzVector boson = *quark1 + *quark2;
    TVector3 boostvector = -boson.BoostVector();
    quark1->Boost(boostvector);
    cosThetaStar = std::fabs(quark1->Vect().Dot(boson.Vect()) / (quark1->Vect().Mag() * boson.Vect().Mag()));
}

//=====================================================================

void BuildDistributions::EventWeightsForSingleEvent(int maxEventNumber, bool backgrounds)
{
    gROOT->ProcessLine(".x /var/clus/usera/sg568/StyleFile/CLICStyleMod.C");

    double alpha4Min(-0.04);
    double alpha4Max(0.041);
    double alpha4Step(0.001);
    double alpha5Min(-0.04);
    double alpha5Max(0.041);
    double alpha5Step(0.001);
    double alpha4StepRef(0.01);
    double alpha5StepRef(0.01);

    if (m_energy == 1400 && !backgrounds)
    {
        alpha4Min = -0.02;
        alpha4Max = 0.0205;
        alpha4Step = 0.001;
        alpha5Min = -0.02;
        alpha5Max = 0.0205;
        alpha5Step = 0.001;
        alpha4StepRef = 0.01;
        alpha5StepRef = 0.01;
    }
    else if (m_energy == 1400 && backgrounds)
    {
        alpha4Min = -0.045;
        alpha4Max = 0.0455;
        alpha4Step = 0.0025;
        alpha5Min = -0.045;
        alpha5Max = 0.0455;
        alpha5Step = 0.0025;
        alpha4StepRef = 0.01;
        alpha5StepRef = 0.01;
    }
    else if (m_energy == 3000 && !backgrounds)
    {
        alpha4Min = -0.002;
        alpha4Max = 0.00205;
        alpha4Step = 0.0001;
        alpha5Min = -0.002;
        alpha5Max = 0.00205;
        alpha5Step = 0.0001;
        alpha4StepRef = 0.00025;
        alpha5StepRef = 0.00025;
    }
    else if (m_energy == 3000 && backgrounds)
    {
        alpha4Min = -0.0039;
        alpha4Max = 0.0039;
        alpha4Step = 0.0001;
        alpha5Min = -0.0039;
        alpha5Max = 0.0039;
        alpha5Step = 0.0001;
        alpha4StepRef = 0.00025;
        alpha5StepRef = 0.00025;
    }

    TH3F *pTH3F = new TH3F("AxisName","",100,alpha4Min,alpha4Max,100,alpha5Min,alpha5Max,100,0.75,1.25);
    pTH3F->GetXaxis()->SetTitle("#alpha_{4}");
    pTH3F->GetXaxis()->SetLabelSize(0.05);
    pTH3F->GetXaxis()->SetTitleSize(0.05);
    pTH3F->GetXaxis()->SetTitleOffset(1.75);
    pTH3F->GetXaxis()->SetNdivisions(5);
    pTH3F->GetYaxis()->SetTitle("#alpha_{5}");
    pTH3F->GetYaxis()->SetLabelSize(0.05);
    pTH3F->GetYaxis()->SetTitleSize(0.05);
    pTH3F->GetYaxis()->SetTitleOffset(1.75);
    pTH3F->GetYaxis()->SetNdivisions(5);
    pTH3F->GetZaxis()->SetTitle("Event Weight");
    pTH3F->GetZaxis()->SetLabelSize(0.05);
    pTH3F->GetZaxis()->SetTitleSize(0.05);
    pTH3F->GetZaxis()->SetTitleOffset(1.5);
    pTH3F->GetZaxis()->SetNdivisions(5);

    for (const auto &pProcess: m_processVector)
    {
        if (pProcess->GetEventType() != "ee_nunuqqqq")
            continue;

        TChain *pTChain(pProcess->GetPostMVATChain());

        Int_t globalEventNumber(std::numeric_limits<int>::max());

        // Selection Variables
        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);

        int nEventsToProcess(pTChain->GetEntries() > maxEventNumber ? maxEventNumber : pTChain->GetEntries());

//        for (unsigned int event = 0; event < nEventsToProcess; event++)
        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);
if (globalEventNumber != 64084036) continue;

            float matrixElementWeight(1.f);
            std::string name("EventWeightsForEvent" + this->NumberToString(globalEventNumber));
            std::string nameRef("EventWeightsForEvent" + this->NumberToString(globalEventNumber) + "Ref");

            TGraph2D *pTGraph2D = new TGraph2D();
            pTGraph2D->SetTitle(name.c_str());

            std::string canvasName(name + "Canvas");
            std::string canvasName2(name + "Canvas2");
            TCanvas *pTCanvas = new TCanvas(canvasName.c_str(), canvasName.c_str(), 800, 600);
            pTCanvas->SetTopMargin(0.05);
            pTCanvas->SetBottomMargin(0.15);
            pTCanvas->SetLeftMargin(0.15);
            pTCanvas->SetRightMargin(0.05);
            pTH3F->Draw("");

            for (double alpha4 = alpha4Min; alpha4 < alpha4Max; alpha4 = alpha4 + alpha4Step)
            {
                for (double alpha5 = alpha5Min; alpha5 < alpha5Max; alpha5 = alpha5 + alpha5Step)
                {
                    m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                    pTGraph2D->SetPoint(pTGraph2D->GetN(), alpha4, alpha5, matrixElementWeight);
                }
            }

            pTGraph2D->Draw("surf1 same");
            pTGraph2D->SetMaximum(1.25);
            pTGraph2D->SetMinimum(0.75);

            TGraph2D *pTGraph2DRef = new TGraph2D();
            pTGraph2DRef->SetTitle(nameRef.c_str());

            for (double alpha4 = alpha4Min; alpha4 < alpha4Max; alpha4 = alpha4 + alpha4StepRef)
            {
                for (double alpha5 = alpha5Min; alpha5 < alpha5Max; alpha5 = alpha5 + alpha5StepRef)
                {
                    m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                    pTGraph2DRef->SetPoint(pTGraph2DRef->GetN(), alpha4, alpha5, matrixElementWeight);
                }
            }

            pTGraph2DRef->SetMarkerStyle(4);
            pTGraph2DRef->SetMarkerColor(kBlack);
            pTGraph2DRef->Draw("P same");
            pTGraph2DRef->SetMaximum(1.25);
            pTGraph2DRef->SetMinimum(0.75);
            pTCanvas->Update();
            std::string plotName(name + "_" + this->NumberToString(m_energy) + "GeV_" + m_descriptor + "_Interpolated.C");
            std::string pngPlotName(name + "_" + this->NumberToString(m_energy) + "GeV_" + m_descriptor + "_Interpolated.png");
            std::string pdfPlotName(name + "_" + this->NumberToString(m_energy) + "GeV_" + m_descriptor + "_Interpolated.pdf");
            gPad->SetTheta(30); // default is 30
            gPad->SetPhi(120); // default is 30
            gPad->Update();
            pTCanvas->SaveAs(plotName.c_str());
            pTCanvas->SaveAs(pngPlotName.c_str());
            pTCanvas->SaveAs(pdfPlotName.c_str());
            delete pTCanvas, pTGraph2D;

            TCanvas *pTCanvas2 = new TCanvas(canvasName2.c_str(), canvasName2.c_str(), 800, 600);
            pTCanvas2->SetTopMargin(0.05);
            pTCanvas2->SetBottomMargin(0.15);
            pTCanvas2->SetLeftMargin(0.15);
            pTCanvas2->SetRightMargin(0.05);
            pTH3F->Draw("");
            pTGraph2DRef->Draw("PCOL same");
            pTGraph2DRef->SetMaximum(1.25);
            pTGraph2DRef->SetMinimum(0.75);
            std::string plotName2(name + "_" + this->NumberToString(m_energy) + "GeV_" + m_descriptor + "_Raw.C");
            std::string pngPlotName2(name + "_" + this->NumberToString(m_energy) + "GeV_" + m_descriptor + "_Raw.png");
            std::string pdfPlotName2(name + "_" + this->NumberToString(m_energy) + "GeV_" + m_descriptor + "_Raw.pdf");
            gPad->SetTheta(30); // default is 30
            gPad->SetPhi(120); // default is 30
            gPad->Update();
            pTCanvas2->SaveAs(plotName2.c_str());
            pTCanvas2->SaveAs(pngPlotName2.c_str());
            pTCanvas2->SaveAs(pdfPlotName2.c_str());
            delete pTCanvas2, pTGraph2DRef;
        }
    }
    delete pTH3F;
}

//=====================================================================

void BuildDistributions::Initialise()
{
    m_cosThetaStarSynJetsRef = new TH2F(this->SafeName("CosThetaStarSynJetsRef"),"Reference Cos(#theta_{Jets}^{*})",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarSynJetsRef->GetXaxis()->SetTitle("Cos(#theta_{Jets}^{*}) Boson 1");
    m_cosThetaStarSynJetsRef->GetYaxis()->SetTitle("Cos(#theta_{Jets}^{*}) Boson 2");
    m_cosThetaStarSynBosonsRef = new TH1F(this->SafeName("CosThetaStarSynBosonsRef"),"Reference Cos(#theta_{Bosons}^{*})",m_nBins,0,1);
    m_cosThetaStarSynBosonsRef->GetXaxis()->SetTitle("Cos(#theta_{Bosons}^{*})");
    m_cosThetaStarSynBosonsRef->GetYaxis()->SetTitle("Entries");
    m_mVVSynBosonsRef = new TH1F(this->SafeName("MVVSynBosonsRef"),"Reference Invariant Mass VV",m_nBinsMVV,m_lowMVV,m_highMVV);
    m_mVVSynBosonsRef->GetXaxis()->SetTitle("MVV [GeV]");
    m_mVVSynBosonsRef->GetYaxis()->SetTitle("Entries");

    m_cosThetaStarSynJetsBkg = new TH2F(this->SafeName("CosThetaStarSynJets"),"Backgrounds Cos(#theta_{Jets}^{*})",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarSynJetsBkg->GetXaxis()->SetTitle("Cos(#theta_{Jets}^{*}) Boson 1");
    m_cosThetaStarSynJetsBkg->GetYaxis()->SetTitle("Cos(#theta_{Jets}^{*}) Boson 2");
    m_cosThetaStarSynBosonsBkg = new TH1F(this->SafeName("CosThetaStarSynBosons"),"Backgrounds Cos#theta_{Bosons}^{*}",m_nBins,0,1);
    m_cosThetaStarSynBosonsBkg->GetXaxis()->SetTitle("Cos(#theta_{Bosons}^{*})");
    m_cosThetaStarSynBosonsBkg->GetYaxis()->SetTitle("Entries");
    m_mVVSynBosonsBkg = new TH1F(this->SafeName("MVVSynBosonsBkg"),"Backgrounds Invariant Mass VV",m_nBinsMVV,m_lowMVV,m_highMVV);
    m_mVVSynBosonsBkg->GetXaxis()->SetTitle("MVV [GeV]");
    m_mVVSynBosonsBkg->GetYaxis()->SetTitle("Entries");
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
    delete m_cosThetaStarSynJetsRef, m_cosThetaStarSynBosonsRef, m_cosThetaStarSynJetsBkg, m_cosThetaStarSynBosonsBkg;
}

//=====================================================================

void BuildDistributions::FillReferenceDistribution()
{
    for (const auto &pProcess: m_processVector)
    {
        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());
//        const double wzSeparationCut(87.0); // Not using at the moment but possibly for MT idea of a4w/a4z/a5w/a5z

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

            m_cosThetaStarSynJetsRef->Fill(cosThetaStarSynJetMostEnergetic, cosThetaStarSynJetLeastEnergetic, weight);
            m_cosThetaStarSynBosonsRef->Fill(cosThetaStarSynBosons, weight);
            m_mVVSynBosonsRef->Fill(invariantMassSystem, weight);

            if (pProcess->GetEventType() != "ee_nunuqqqq")
            {
                m_cosThetaStarSynJetsBkg->Fill(cosThetaStarSynJetMostEnergetic, cosThetaStarSynJetLeastEnergetic, weight);
                m_cosThetaStarSynBosonsBkg->Fill(cosThetaStarSynBosons, weight);
                m_mVVSynBosonsBkg->Fill(invariantMassSystem, weight);
            }
        }
        delete pTChain;
    }
}

//=====================================================================

void BuildDistributions::FillDistribution(const double alpha4, const double alpha5)
{
    m_cosThetaStarSynJets = (TH2F*)(m_cosThetaStarSynJetsBkg->Clone());
    m_cosThetaStarSynBosons = (TH1F*)(m_cosThetaStarSynBosonsBkg->Clone());
    m_mVVSynBosons = (TH1F*)(m_mVVSynBosonsBkg->Clone());

    for (const auto &pProcess: m_processVector)
    {
        if (pProcess->GetEventType() != "ee_nunuqqqq")
            continue;

        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());
        const double wzSeparationCut(87.0);

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

            float matrixElementWeight(1.f);
            m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
            m_cosThetaStarSynJets->Fill(cosThetaStarSynJetMostEnergetic, cosThetaStarSynJetLeastEnergetic, weight*matrixElementWeight);
            m_cosThetaStarSynBosons->Fill(cosThetaStarSynBosons, weight*matrixElementWeight);
            m_mVVSynBosons->Fill(invariantMassSystem, weight*matrixElementWeight);
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
    if (number < 0.00000001 and -0.00000001 < number)
        return "0.0";

    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================

void BuildDistributions::Pause()
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
