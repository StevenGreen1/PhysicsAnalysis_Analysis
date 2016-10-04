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

Fit::Fit(const ProcessVector &processVector, PostMVASelection *pPostMVASelection) :
    m_processVector(processVector),
    m_pPostMVASelection(pPostMVASelection),
    m_a4IntMin(-1),
    m_a4IntMax(1),
    m_a4Step(0.005),
    m_a5IntMin(-1),
    m_a5IntMax(1),
    m_a5Step(0.005)
{
    m_pTH1F_DistributionJ_Sample = new TH1F("SampleCosThetaJets","Sample Cos#theta_{Jets}",50,0,1);
    m_pTH1F_DistributionW_Sample = new TH1F("SampleCosThetaW","Sample Cos#theta_{W}",50,0,1);

    this->FillDistribution();
    this->SaveDistribution();
}

//=====================================================================

void Fit::FillDistribution()
{
    std::map<int, std::map<int, std::map<int, float> > > alphaInt_EvtNumber_Weight;

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it++)
    {
        const Process *pProcess(*it);
        if (pProcess->GetEventType() != "ee_nunuqqqq") 
            continue;

        TChain *pTChain(pProcess->GetPostMVATChain());
//        CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pProcess->GetEventType(), this->NumberToString(pProcess->GetEnergy()));

        int globalEventNumber(std::numeric_limits<int>::max());
        float nIsolatedLeptons(std::numeric_limits<float>::max());
        float transverseMomentum(std::numeric_limits<float>::max());
        float invariantMassSystem(std::numeric_limits<float>::max());
        double bdt(std::numeric_limits<double>::max());

        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("BDT", &bdt);

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);               

            if (bdt < m_pPostMVASelection->GetBDTLowCut() or m_pPostMVASelection->GetBDTHighCut() < bdt)
                continue;
            if (nIsolatedLeptons < m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsLowCut() or m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsHighCut() < nIsolatedLeptons)
                continue;
            if (transverseMomentum < m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumLowCut() or m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumHighCut() < transverseMomentum)
                continue;
            if (invariantMassSystem < m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemLowCut() or m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemHighCut() < invariantMassSystem)
                continue;

            for (int a4Int = m_a4IntMin; a4Int < m_a4IntMax+1; a4Int++)
            {
                for (int a5Int = m_a5IntMin; a5Int < m_a5IntMax+1; a5Int++)
                {
                    float a4Current = m_a4Step * (float)(a4Int);
                    float a5Current = m_a5Step * (float)(a5Int);
                    float matrixElementWeight(std::numeric_limits<float>::max());
//                    pCouplingAnalysis->GetWeight(globalEventNumber, a4Current, a5Current, matrixElementWeight);
                    alphaInt_EvtNumber_Weight[a4Int][a5Int][globalEventNumber] = matrixElementWeight;
                }
            }
        }
//        delete pCouplingAnalysis, pTChain, pProcess;
    }

    std::map<int, std::map<int, TH1F*> > alphaInt_HistW;
    std::map<int, std::map<int, TH1F*> > alphaInt_HistWJ;

    for (int a4Int = m_a4IntMin; a4Int < m_a4IntMax+1; a4Int++)
    {
        for (int a5Int = m_a5IntMin; a5Int < m_a5IntMax+1; a5Int++)
        {
            TString name1 = "CosThetaStarW_" + this->NumberToString(a4Int) + "_" + this->NumberToString(a5Int);
            TString title1 = "Cos#theta_{W}^{*}";
            TH1F *pTH1F1 = new TH1F(name1, title1, 50, 0 ,1);
            alphaInt_HistW[a4Int][a5Int] = (TH1F*)(pTH1F1->Clone());

            TString name2 = "CosThetaStarWJets_" + this->NumberToString(a4Int) + "_" + this->NumberToString(a5Int);
            TString title2 = "Cos#theta_{WJets}^{*}";
            TH1F *pTH1F2 = new TH1F(name2, title2, 50, 0 ,1);
            alphaInt_HistWJ[a4Int][a5Int] = (TH1F*)(pTH1F2->Clone());
        }
    }

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);
        double weight(pProcess->GetPostMVAProcessWeight());

        TChain *pTChain(pProcess->GetPostMVATChain());

        int globalEventNumber(std::numeric_limits<int>::max());
        float nIsolatedLeptons(std::numeric_limits<float>::max());
        float transverseMomentum(std::numeric_limits<float>::max());
        float invariantMassSystem(std::numeric_limits<float>::max());
        float cosThetaStarW(std::numeric_limits<float>::max());
        float cosThetaStarWJet1(std::numeric_limits<float>::max());
        float cosThetaStarWJet2(std::numeric_limits<float>::max());
        double bdt(std::numeric_limits<double>::max());

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

            if (bdt < m_pPostMVASelection->GetBDTLowCut() or m_pPostMVASelection->GetBDTHighCut() < bdt)
                continue;
            if (nIsolatedLeptons < m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsLowCut() or m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsHighCut() < nIsolatedLeptons)
                continue;
            if (transverseMomentum < m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumLowCut() or m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumHighCut() < transverseMomentum)
                continue;
            if (invariantMassSystem < m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemLowCut() or m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemHighCut() < invariantMassSystem)
                continue;

//            std::cout << "m_pTH1F_DistributionW_Sample->Fill(" << cosThetaStarW << "," << weight << ");" << std::endl;
            m_pTH1F_DistributionW_Sample->Fill(cosThetaStarW,weight);

            m_pTH1F_DistributionJ_Sample->Fill(cosThetaStarWJet1, weight);
            m_pTH1F_DistributionJ_Sample->Fill(cosThetaStarWJet2, weight);

            for (int a4Int = m_a4IntMin; a4Int < m_a4IntMax+1; a4Int++)
            {
                for (int a5Int = m_a5IntMin; a5Int < m_a5IntMax+1; a5Int++)
                {
                    float matrixElementWeight(1.f);

                    if (pProcess->GetEventType() == "ee_nunuqqqq")
                        matrixElementWeight = alphaInt_EvtNumber_Weight.at(a4Int).at(a5Int).at(globalEventNumber);

//                    std::cout << "alphaInt_EvtNumber_Weight.at(a4Int).at(a5Int).at(globalEventNumber)" << std::endl;
//                    std::cout << "alphaInt_EvtNumber_Weight.at(" << a4Int << ").at(" << a5Int << ").at(" << globalEventNumber << ")" << alphaInt_EvtNumber_Weight.at(a4Int).at(a5Int).at(globalEventNumber) << std::endl;
//                    std::cout << "alphaInt_EvtNumber_Weight.at(" << -a4Int << ").at(" << -a5Int << ").at(" << globalEventNumber << ")" << alphaInt_EvtNumber_Weight.at(-a4Int).at(-a5Int).at(globalEventNumber) << std::endl;
//                    std::cout << "alphaInt_EvtNumber_Weight.at(" << a4Int << ").at(" << -a5Int << ").at(" << globalEventNumber << ")" << alphaInt_EvtNumber_Weight.at(a4Int).at(-a5Int).at(globalEventNumber) << std::endl;
//                    std::cout << "alphaInt_EvtNumber_Weight.at(" << -a4Int << ").at(" << a5Int << ").at(" << globalEventNumber << ")" << alphaInt_EvtNumber_Weight.at(-a4Int).at(a5Int).at(globalEventNumber) << std::endl;

//                    std::cout << "alphaInt_HistW[" << a4Int << "][" << a5Int << "]->Fill(" << cosThetaStarW << "," << weight << "*" << matrixElementWeight << ");" << std::endl;
                    alphaInt_HistW[a4Int][a5Int]->Fill(cosThetaStarW,weight*matrixElementWeight);
                    alphaInt_HistWJ[a4Int][a5Int]->Fill(cosThetaStarWJet1, weight*matrixElementWeight);
                    alphaInt_HistWJ[a4Int][a5Int]->Fill(cosThetaStarWJet2, weight*matrixElementWeight);
                }
            }
        }
    } 

    for (std::map<int, std::map<int, TH1F*> >::iterator it = alphaInt_HistWJ.begin(); it != alphaInt_HistWJ.end(); it++)
    {
        const int a4Int(it->first);
        std::cout << "a4Int : " << a4Int << std::endl;

        for (std::map<int, TH1F*>::iterator iter = it->second.begin(); iter != it->second.end(); iter++)
        {
            const int a5Int(iter->first);
            std::cout << "a5Int : " << a5Int << std::endl;
            TH1F *pTH1F = iter->second;

            TCanvas *pTCanvas = new TCanvas();
            pTCanvas->Draw();
            m_pTH1F_DistributionJ_Sample->Draw();

            m_pTH1F_DistributionJ_Sample->SetLineColor(kRed);
            m_pTH1F_DistributionJ_Sample->SetFillColor(kRed);
            m_pTH1F_DistributionJ_Sample->SetFillStyle(3004);

            pTH1F->SetLineColor(kGreen-2);
            pTH1F->SetFillColor(kGreen-2);
            pTH1F->SetFillStyle(3005);

            int binMax1 = m_pTH1F_DistributionJ_Sample->GetBinContent(m_pTH1F_DistributionJ_Sample->GetMaximumBin());
            int binMax2 = pTH1F->GetBinContent(pTH1F->GetMaximumBin());

            if (binMax1 > binMax2)
            {
                m_pTH1F_DistributionJ_Sample->GetYaxis()->SetRangeUser(0,binMax1*1.05);
                pTH1F->GetYaxis()->SetRangeUser(0,binMax1*1.05);
                m_pTH1F_DistributionJ_Sample->Draw();
                pTH1F->Draw("same");
            }

            else 
            {
                m_pTH1F_DistributionJ_Sample->GetYaxis()->SetRangeUser(0,binMax2*1.05);
                pTH1F->GetYaxis()->SetRangeUser(0,binMax2*1.05);
                pTH1F->Draw();
                m_pTH1F_DistributionJ_Sample->Draw("same");
            }

            TLegend *pTLegend = new TLegend(0.5,0.7,0.9,0.9);

            std::string title1 = "#alpha_{4} = 0, #alpha_{5} = 0";
            std::string title2 = "#alpha_{4} = " + this->NumberToString(a4Int*m_a4Step) + ", #alpha_{5} = " + this->NumberToString(a5Int*m_a5Step);

            pTLegend->AddEntry(pTH1F,title2.c_str(),"f");
            pTLegend->AddEntry(m_pTH1F_DistributionJ_Sample,title1.c_str(),"f");
            pTLegend->Draw("same");
            pTCanvas->SaveAs("Test.png");
            pTCanvas->SaveAs("Test.C");
            Pause();

            double nll(0.f);
            this->CalculateLogLikelihood1D(pTH1F,m_pTH1F_DistributionJ_Sample,nll);
            m_Alpah4.push_back(a4Int*m_a4Step);
            m_Alpah5.push_back(a5Int*m_a5Step);
            m_NLLJ.push_back(nll);
        }
    } 
}

//=====================================================================

void Fit::CalculateLogLikelihood1D(TH1F *pTH1F_Distribution, TH1F *pTH1F_Distribution_Sample, double &nll)
{
    if (!gApplication) new TApplication("Application", ((int *)0), ((char **)0));

    nll = 0.0;
    const int nBinsX = pTH1F_Distribution->GetXaxis()->GetNbins();
    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
//        std::cout << "nll : " << nll << std::endl;
        const double binContent = pTH1F_Distribution->GetBinContent(xBin);
        const double binContentSample = pTH1F_Distribution_Sample->GetBinContent(xBin);
        nll += (-1.0 * binContentSample * log(binContent)) + binContent;

//        std::cout << "ni  : " << binContentSample << std::endl;
//        std::cout << "mui : " << binContent << std::endl;
//        std::cout << "ln (mui) : " << log(binContent) << std::endl;
//        std::cout << "+= -ni*ln(mui) + mui  : " << (-1.0 * binContentSample * log(binContent)) + binContent<< std::endl;
//        std::cout << "nll : " << nll << std::endl;
    }
/*
    TCanvas *pTCanvas = new TCanvas("One","One");
    pTH1F_Distribution->Draw();

    TCanvas *pTCanvas2 = new TCanvas("Two","Two");
    pTH1F_Distribution_Sample->Draw();
    Pause();
*/
}

//=====================================================================

void Fit::SaveDistribution()
{
    TCanvas *pTCanvas = new TCanvas();
//    TGraph2D *pTGraph2DW = new TGraph2D();
    TGraph2D *pTGraph2DJ = new TGraph2D();

    double minnllw(std::numeric_limits<double>::max()), minnllj(std::numeric_limits<double>::max());

    for (DoubleVector::iterator iter = m_Alpah4.begin(); iter != m_Alpah4.end(); iter++)
    {
        const int position(iter-m_Alpah4.begin());
//        if (minnllw > m_NLLW.at(position))
//            minnllw = m_NLLW.at(position);

        if (minnllj > m_NLLJ.at(position))
            minnllj = m_NLLJ.at(position);
    }

    for (DoubleVector::iterator iter = m_Alpah4.begin(); iter != m_Alpah4.end(); iter++)
    {
        const int position(iter-m_Alpah4.begin());
//        pTGraph2DW->SetPoint(pTGraph2DW->GetN(), m_Alpah4.at(position), m_Alpah5.at(position), m_NLLW.at(position) - minnllw);
        pTGraph2DJ->SetPoint(pTGraph2DJ->GetN(), m_Alpah4.at(position), m_Alpah5.at(position), m_NLLJ.at(position) - minnllj);
    }
//    pTGraph2DW->Draw("SURF3");
//    pTCanvas->SaveAs("LoglikelihoddPlotW.C");

    pTGraph2DJ->Draw("SURF3");
    pTCanvas->SaveAs("LoglikelihoddPlotJ.C");
/*
    TH2F *pTH2F = (TH2F*)(m_pTH2F_Distribution_Sample->Clone());
    std::string processName = pTH2F->GetName();
    std::string saveName = processName + ".C";
    pTCanvas = new TCanvas();
    pTH2F->Draw("COLZ");
    pTCanvas->SaveAs(saveName.c_str());
    pTH2F->SetName(this->RandomName().c_str());

    pTH2F = (TH2F*)(m_pTH2F_Derivative_Sample->Clone());
    processName = pTH2F->GetName();
    saveName = processName + ".C";
    pTCanvas = new TCanvas();
    pTH2F->Draw("COLZ");
    pTCanvas->SaveAs(saveName.c_str());
    pTH2F->SetName(this->RandomName().c_str());
*/
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
