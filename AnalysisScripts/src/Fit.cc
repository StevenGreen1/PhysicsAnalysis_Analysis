/**
 *  @file   AnalysisScripts/src/Fit.cc 
 * 
 *  @brief  Implementation of the fit class.
 * 
 *  $Log: $
 */

#include "Fit.h"

#include "TSystem.h"
#include <fcntl.h>

void Pause();

//=====================================================================

Fit::Fit(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis) : 
    m_processVector(processVector),
    m_pPostMVASelection(pCouplingAnalysis->GetPostMVASelection()),
    m_pCouplingAnalysis(pCouplingAnalysis),
    m_alpha4IntMin(-19),
    m_alpha4IntMax(14),
    m_alpha4Step(0.002),
    m_alpha5IntMin(-19),
    m_alpha5IntMax(14),
    m_alpha5Step(0.002),
    m_rootFileName("FitData.root")
{
    m_pTFile = new TFile(m_rootFileName.c_str(), "recreate");

    m_pTH1FCosThetaStarWJetsRef = new TH1F("CosThetaStarWJetsRef","Reference Cos#theta_{Jets}",50,0,1);
    m_pTH1FCosThetaStarWRef = new TH1F("CosThetaStarWRef","Reference Cos#theta_{W}",50,0,1);

    for (int alpha4Int = m_alpha4IntMin; alpha4Int < m_alpha4IntMax+1; alpha4Int++)
    {
        for (int alpha5Int = m_alpha5IntMin; alpha5Int < m_alpha5IntMax+1; alpha5Int++)
        {
            std::string cosThetaStarWBosonHistName = "CosThetaStarW_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_" + this->NumberToString(alpha5Int*m_alpha5Step);
            std::string cosThetaStarWBosonHistTitle = "Cos#theta_{W}^{*}";
            TH1F *pTH1FCosThetaStarWBoson = new TH1F(cosThetaStarWBosonHistName.c_str(), cosThetaStarWBosonHistTitle.c_str(), 50, 0 ,1);
            m_alphaIntToCosThetaStarW[alpha4Int][alpha5Int] = (TH1F*)(pTH1FCosThetaStarWBoson->Clone());

            std::string cosThetaStarWJetsHistName =  "CosThetaStarWJets_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_" + this->NumberToString(alpha5Int*m_alpha5Step);
            std::string cosThetaStarWJetsHistTitle = "Cos#theta_{WJets}^{*}";
            TH1F *pTH1FCosThetaStarWJets = new TH1F(cosThetaStarWJetsHistName.c_str(), cosThetaStarWJetsHistTitle.c_str(), 50, 0 ,1);
            m_alphaIntToCosThetaStarWJets[alpha4Int][alpha5Int] = (TH1F*)(pTH1FCosThetaStarWJets->Clone());
        }
    }

    this->FillDistribution();
    this->AnalyseDistribution();
    this->SaveDistribution();
}

//=====================================================================

void Fit::FillDistribution()
{
    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);
        double weight(pProcess->GetPostMVAProcessWeight());

        TChain *pTChain(pProcess->GetPostMVATChain());

        Int_t globalEventNumber(std::numeric_limits<int>::max());
        Int_t nIsolatedLeptons(std::numeric_limits<float>::max());
        Double_t transverseMomentum(std::numeric_limits<float>::max());
        Double_t invariantMassSystem(std::numeric_limits<float>::max());
        Double_t cosThetaStarW(std::numeric_limits<float>::max());
        Double_t cosThetaStarWJet1(std::numeric_limits<float>::max());
        Double_t cosThetaStarWJet2(std::numeric_limits<float>::max());
        Double_t bdt(std::numeric_limits<double>::max());

        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("CosThetaStarWBosons", &cosThetaStarW);
        pTChain->SetBranchAddress("CosThetaStarWJet1", &cosThetaStarWJet1);
        pTChain->SetBranchAddress("CosThetaStarWJet2", &cosThetaStarWJet2);
        pTChain->SetBranchAddress("BDT", &bdt);

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
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

            // Fill Reference Distributions
            m_pTH1FCosThetaStarWRef->Fill(cosThetaStarW,weight);
            m_pTH1FCosThetaStarWJetsRef->Fill(cosThetaStarWJet1, weight);
            m_pTH1FCosThetaStarWJetsRef->Fill(cosThetaStarWJet2, weight);

            // Fill Weighted Distribution
            for (int alpha4Int = m_alpha4IntMin; alpha4Int < m_alpha4IntMax+1; alpha4Int++)
            {
                for (int alpha5Int = m_alpha5IntMin; alpha5Int < m_alpha5IntMax+1; alpha5Int++)
                {
                    float matrixElementWeight(1.f);

                    if (pProcess->GetEventType() == "ee_nunuqqqq")
                    {
                        const float alpha4(m_alpha4Step * (float)(alpha4Int));
                        const float alpha5(m_alpha5Step * (float)(alpha5Int));
                        m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                    }

                    m_alphaIntToCosThetaStarW[alpha4Int][alpha5Int]->Fill(cosThetaStarW,weight*matrixElementWeight);
                    m_alphaIntToCosThetaStarWJets[alpha4Int][alpha5Int]->Fill(cosThetaStarWJet1, weight*matrixElementWeight);
                    m_alphaIntToCosThetaStarWJets[alpha4Int][alpha5Int]->Fill(cosThetaStarWJet2, weight*matrixElementWeight);
                }
            }
        }
    } 
}

//=====================================================================

void Fit::AnalyseDistribution()
{
    for (IntIntHistMap::iterator it = m_alphaIntToCosThetaStarWJets.begin(); it != m_alphaIntToCosThetaStarWJets.end(); it++)
    {
        const int alpha4Int(it->first);
        std::cout << "alpha4Int : " << alpha4Int << std::endl;

        for (IntHistMap::iterator iter = it->second.begin(); iter != it->second.end(); iter++)
        {
            const int alpha5Int(iter->first);
            std::cout << "alpha5Int : " << alpha5Int << std::endl;
            TH1F *pTH1FCosThetaStarWJets = iter->second;

            TCanvas *pTCanvas = new TCanvas();
            pTCanvas->Draw();
            m_pTH1FCosThetaStarWJetsRef->Draw();

            m_pTH1FCosThetaStarWJetsRef->SetLineColor(kRed);
            m_pTH1FCosThetaStarWJetsRef->SetFillColor(kRed);
            m_pTH1FCosThetaStarWJetsRef->SetFillStyle(3004);

            pTH1FCosThetaStarWJets->SetLineColor(kGreen-2);
            pTH1FCosThetaStarWJets->SetFillColor(kGreen-2);
            pTH1FCosThetaStarWJets->SetFillStyle(3005);

            int binMaxRef = m_pTH1FCosThetaStarWJetsRef->GetBinContent(m_pTH1FCosThetaStarWJetsRef->GetMaximumBin());
            int binMax = pTH1FCosThetaStarWJets->GetBinContent(pTH1FCosThetaStarWJets->GetMaximumBin());

            if (binMaxRef > binMax)
            {
                m_pTH1FCosThetaStarWJetsRef->GetYaxis()->SetRangeUser(0,binMaxRef*1.05);
                pTH1FCosThetaStarWJets->GetYaxis()->SetRangeUser(0,binMaxRef*1.05);
                m_pTH1FCosThetaStarWJetsRef->Draw();
                pTH1FCosThetaStarWJets->Draw("same");
            }

            else 
            {
                m_pTH1FCosThetaStarWJetsRef->GetYaxis()->SetRangeUser(0,binMax*1.05);
                pTH1FCosThetaStarWJets->GetYaxis()->SetRangeUser(0,binMax*1.05);
                pTH1FCosThetaStarWJets->Draw();
                m_pTH1FCosThetaStarWJetsRef->Draw("same");
            }

            TLegend *pTLegend = new TLegend(0.5,0.7,0.9,0.9);

            std::string legendDescriptionRef = "#alpha_{4} = 0, #alpha_{5} = 0";
            std::string legendDescription = "#alpha_{4} = " + this->NumberToString(alpha4Int*m_alpha4Step) + ", #alpha_{5} = " + this->NumberToString(alpha5Int*m_alpha5Step);

            pTLegend->AddEntry(pTH1FCosThetaStarWJets,legendDescription.c_str(),"f");
            pTLegend->AddEntry(m_pTH1FCosThetaStarWJetsRef,legendDescriptionRef.c_str(),"f");
            pTLegend->Draw("same");

            m_pTFile->cd();
            pTH1FCosThetaStarWJets->Write();
            pTCanvas->Write();

            std::string plotTitlePng("CosThetaStarWJets_Alpha4_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_Alpha5_" + this->NumberToString(alpha5Int*m_alpha5Step) + ".png");
            std::string plotTitleDotC("CosThetaStarWJets_Alpha4_" + this->NumberToString(alpha4Int*m_alpha4Step) + "_Alpha5_" + this->NumberToString(alpha5Int*m_alpha5Step) + ".C");
            pTCanvas->SaveAs(plotTitlePng.c_str());
            pTCanvas->SaveAs(plotTitleDotC.c_str());

            double negativeLogLikelihood(this->CalculateLogLikelihood(pTH1FCosThetaStarWJets,m_pTH1FCosThetaStarWJetsRef));
            m_alpha4.push_back(alpha4Int*m_alpha4Step);
            m_alpha5.push_back(alpha5Int*m_alpha5Step);
            m_nllCosThetaStarWJets.push_back(negativeLogLikelihood);
        }
    } 
}

//=====================================================================

double Fit::CalculateLogLikelihood(TH1F *pTH1F, TH1F *pTH1FRef)
{
    if (!gApplication) new TApplication("Application", ((int *)0), ((char **)0));

    double negativeLogLikelihood(0.0);
    const int nBinsX = pTH1F->GetXaxis()->GetNbins();
    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
        const double binContent = pTH1F->GetBinContent(xBin);
        const double binContentRef = pTH1FRef->GetBinContent(xBin);
        negativeLogLikelihood += (-1.0 * binContentRef * log(binContent)) + binContent;
    }
    return negativeLogLikelihood;
}

//=====================================================================

void Fit::SaveDistribution()
{
    TCanvas *pTCanvas = new TCanvas();
    TGraph2D *pTGraph2DNLLCosThetaStarWJets = new TGraph2D();

    double minNLLCosThetaStarWJets(std::numeric_limits<double>::max());

    for (DoubleVector::iterator iter = m_alpha4.begin(); iter != m_alpha4.end(); iter++)
    {
        const int position(iter-m_alpha4.begin());
        if (minNLLCosThetaStarWJets > m_nllCosThetaStarWJets.at(position))
            minNLLCosThetaStarWJets = m_nllCosThetaStarWJets.at(position);
    }

    for (DoubleVector::iterator iter = m_alpha4.begin(); iter != m_alpha4.end(); iter++)
    {
        const int position(iter-m_alpha4.begin());
        pTGraph2DNLLCosThetaStarWJets->SetPoint(pTGraph2DNLLCosThetaStarWJets->GetN(), m_alpha4.at(position), m_alpha5.at(position), m_nllCosThetaStarWJets.at(position) - minNLLCosThetaStarWJets);
    }

    pTGraph2DNLLCosThetaStarWJets->Draw("SURF3");

    m_pTFile->cd();
    pTGraph2DNLLCosThetaStarWJets->Write();

    pTCanvas->SaveAs("NegativeLogLikelihoodCosThetaStarWJets.C");
}

//=====================================================================

std::string Fit::RandomName()
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
std::string Fit::NumberToString(T number)
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
