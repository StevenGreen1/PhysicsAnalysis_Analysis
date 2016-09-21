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

Fit::Fit(const ProcessVector &processVector) :
    m_processVector(processVector)
{
    m_pTH1F_DistributionJ_Sample = new TH1F("SampleCosThetaJets","Sample Cos#theta_{Jets}",100,0,1);
    m_pTH1F_DistributionW_Sample = new TH1F("SampleCosThetaW","Sample Cos#theta_{W}",100,0,1);

    this->FillDistribution();
    this->SaveDistribution();
}

//=====================================================================

void Fit::FillDistribution()
{
    const int a4IntMin(-5);
    const int a4IntMax(-4);
    const float a4Step(0.01);
    const int a5IntMin(-5);
    const int a5IntMax(-4);
    const float a5Step(0.01);

    std::map<int, std::map<int, std::map<int, float> > > alphaInt_EvtNumber_Weight;

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it++)
    {
        const Process *pProcess(*it);
        if (pProcess->GetEventType() != "ee_nunuqqqq") 
            continue;

        TChain *pTChain(pProcess->GetPostMVATChain());
        CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pProcess->GetEventType(),this->NumberToString(pProcess->GetEnergy()));

        int globalEventNumber(std::numeric_limits<int>::max());
        double bdt(std::numeric_limits<double>::max());

        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("BDT", &bdt);

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);               

            globalEventNumber = globalEventNumber-1000;

            if (globalEventNumber < 1e6)
                continue;

//            if (bdt < 0.f)
//                continue;

            for (int a4Int = a4IntMin; a4Int < a4IntMax+1; a4Int++)
            {
                for (int a5Int = a5IntMin; a5Int < a5IntMax+1; a5Int++)
                {
                    float a4Current = a4Step * (float)(a4Int);
                    float a5Current = a5Step * (float)(a5Int);
                    float matrixElementWeight(std::numeric_limits<float>::max());
                    pCouplingAnalysis->GetWeight(globalEventNumber, a4Current, a5Current, matrixElementWeight);
                    alphaInt_EvtNumber_Weight[a4Int][a5Int][globalEventNumber] = matrixElementWeight;
                }
            }
        }
        delete pCouplingAnalysis, pTChain, pProcess;
    }

    std::map<int, std::map<int, TH1F*> > alphaInt_HistW;
    std::map<int, std::map<int, TH1F*> > alphaInt_HistWJ;

    for (int a4Int = a4IntMin; a4Int < a4IntMax+1; a4Int++)
    {
        for (int a5Int = a5IntMin; a5Int < a5IntMax+1; a5Int++)
        {
            TString name1 = "CosThetaStarW_" + this->NumberToString(a4Int) + "_" + this->NumberToString(a5Int);
            TString title1 = "Cos#theta_{W}^{*}";
            TH1F *pTH1F1 = new TH1F(name1, title1, 100, 0 ,1);
            alphaInt_HistW[a4Int][a5Int] = (TH1F*)(pTH1F1->Clone());

            TString name2 = "CosThetaStarWJets_" + this->NumberToString(a4Int) + "_" + this->NumberToString(a5Int);
            TString title2 = "Cos#theta_{WJets}^{*}";
            TH1F *pTH1F2 = new TH1F(name2, title2, 100, 0 ,1);
            alphaInt_HistWJ[a4Int][a5Int] = (TH1F*)(pTH1F2->Clone());
        }
    }

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);
        double weight(pProcess->GetPostMVAProcessWeight());

        TChain *pTChain(pProcess->GetPostMVATChain());

        int globalEventNumber(std::numeric_limits<int>::max());
        double cosThetaStarW(0.0);
        double bdt(std::numeric_limits<double>::max());
        double cosThetaStarWJet1(std::numeric_limits<double>::max());
        double cosThetaStarWJet2(std::numeric_limits<double>::max());
 
        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("CosThetaStarWBosons", &cosThetaStarW);
        pTChain->SetBranchAddress("BDT", &bdt);
        pTChain->SetBranchAddress("CosThetaStarWJet1", &cosThetaStarWJet1);
        pTChain->SetBranchAddress("CosThetaStarWJet2", &cosThetaStarWJet2);

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);

            globalEventNumber = globalEventNumber-1000;

            if (globalEventNumber < 1e6)
                continue;

//            std::cout << "bdt " << bdt << std::endl;

//            if (bdt < 0.f)
//                continue;

//            std::cout << "m_pTH1F_DistributionW_Sample->Fill(" << cosThetaStarW << "," << weight << ");" << std::endl;
            m_pTH1F_DistributionW_Sample->Fill(cosThetaStarW,weight);

            m_pTH1F_DistributionJ_Sample->Fill(cosThetaStarWJet1, weight);
            m_pTH1F_DistributionJ_Sample->Fill(cosThetaStarWJet2, weight);

            for (int a4Int = a4IntMin; a4Int < a4IntMax+1; a4Int++)
            {
                for (int a5Int = a5IntMin; a5Int < a5IntMax+1; a5Int++)
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
            pTCanvas->Divide(2,1);
            pTCanvas->cd(1);
            pTH1F->Draw();
            pTCanvas->cd(2);
            m_pTH1F_DistributionJ_Sample->Draw();
            pTCanvas->SaveAs("Test.png");
            pTCanvas->SaveAs("Test.C");
            Pause();

            double nll(0.f);
            this->CalculateLogLikelihood1D(pTH1F,m_pTH1F_DistributionJ_Sample,nll);
            m_Alpah4.push_back(a4Int*a4Step);
            m_Alpah5.push_back(a5Int*a5Step);
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
