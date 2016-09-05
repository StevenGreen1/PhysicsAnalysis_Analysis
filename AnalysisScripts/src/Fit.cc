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
    const int a4IntMax(5);
    const float a4Step(0.01);
    const int a5IntMin(-5);
    const int a5IntMax(5);
    const float a5Step(0.01);

    std::map<int, std::map<int, std::map<int, float> > > alphaInt_EvtNumber_Weight;

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it++)
    {
        const Process *pProcess(*it);
        if (pProcess->GetEventType() != "ee_nunuqqqq") 
            continue;

        TChain *pTChain(pProcess->GetPostBDTTChain());
        CouplingAnalysis *pCouplingAnalysis = new CouplingAnalysis(pProcess->GetEventType(),this->NumberToString(pProcess->GetEnergy()));

        int generatorSerialInt(std::numeric_limits<int>::max());
        double bdt(std::numeric_limits<double>::max());

        pTChain->SetBranchAddress("GeneratorSerialNumber", &generatorSerialInt);
        pTChain->SetBranchAddress("BDT", &bdt);

        int eventCounter(0);
        IntVector readInSGN;

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);               
            eventCounter++;

            if (std::find(readInSGN.begin(), readInSGN.end(), generatorSerialInt) == readInSGN.end())
            {
                readInSGN.push_back(generatorSerialInt);
                eventCounter = 1;
            }

            if (bdt < 0.f)
                continue;

            const int eventNumber(1000*(generatorSerialInt-1) + eventCounter);

            for (int a4Int = a4IntMin; a4Int < a4IntMax+1; a4Int++)
            {
                for (int a5Int = a5IntMin; a5Int < a5IntMax+1; a5Int++)
                {
                    float a4Current = a4Step * (float)(a4Int);
                    float a5Current = a5Step * (float)(a5Int);
                    float matrixElementWeight(std::numeric_limits<float>::max());
                    pCouplingAnalysis->GetWeight(eventNumber, a4Current, a5Current, matrixElementWeight);
                    alphaInt_EvtNumber_Weight[a4Int][a5Int][eventCounter] = matrixElementWeight;
                }
            }
        }
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
        double weight(pProcess->GetPostBDTProcessWeight());

        TChain *pTChain(pProcess->GetPostBDTTChain());

        int generatorSerialInt(std::numeric_limits<int>::max());
        double cosThetaStarW(0.0);
        double bdt(std::numeric_limits<double>::max());
        DoubleVector *cosThetaStarWJets(NULL);
        
        pTChain->SetBranchAddress("GeneratorSerialNumber", &generatorSerialInt);
        pTChain->SetBranchAddress("CosThetaStarWBosons", &cosThetaStarW);
        pTChain->SetBranchAddress("BDT", &bdt);
        pTChain->SetBranchAddress("CosThetaStarWJets", &cosThetaStarWJets);

        int eventCounter(0);
        IntVector readInSGN;

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);
            eventCounter++;

            if (std::find(readInSGN.begin(), readInSGN.end(), generatorSerialInt) == readInSGN.end())
            {
                readInSGN.push_back(generatorSerialInt);
                eventCounter = 1;
            }

//            std::cout << "bdt " << bdt << std::endl;

            if (bdt < 0.f)
                continue;

            const int eventNumber(1000*(generatorSerialInt-1) + eventCounter);

//            std::cout << "m_pTH1F_DistributionW_Sample->Fill(" << cosThetaStarW << "," << weight << ");" << std::endl;
            m_pTH1F_DistributionW_Sample->Fill(cosThetaStarW,weight);

            for (DoubleVector::iterator it = cosThetaStarWJets->begin(); it != cosThetaStarWJets->end(); it++)
            {
                double cosThetaStarWJet(*it);
                m_pTH1F_DistributionJ_Sample->Fill(cosThetaStarWJet,weight);
            }

            for (int a4Int = a4IntMin; a4Int < a4IntMax+1; a4Int++)
            {
                for (int a5Int = a5IntMin; a5Int < a5IntMax+1; a5Int++)
                {
                    float matrixElementWeight(1.f);

                    if (pProcess->GetEventType() == "ee_nunuqqqq")
                        matrixElementWeight = alphaInt_EvtNumber_Weight.at(a4Int).at(a5Int).at(eventCounter);

//                    std::cout << "alphaInt_EvtNumber_Weight.at(a4Int).at(a5Int).at(eventCounter)" << std::endl;
//                    std::cout << "alphaInt_EvtNumber_Weight.at(" << a4Int << ").at(" << a5Int << ").at(" << eventCounter << ")" << alphaInt_EvtNumber_Weight.at(a4Int).at(a5Int).at(eventCounter) << std::endl;
//                    std::cout << "alphaInt_EvtNumber_Weight.at(" << -a4Int << ").at(" << -a5Int << ").at(" << eventCounter << ")" << alphaInt_EvtNumber_Weight.at(-a4Int).at(-a5Int).at(eventCounter) << std::endl;
//                    std::cout << "alphaInt_EvtNumber_Weight.at(" << a4Int << ").at(" << -a5Int << ").at(" << eventCounter << ")" << alphaInt_EvtNumber_Weight.at(a4Int).at(-a5Int).at(eventCounter) << std::endl;
//                    std::cout << "alphaInt_EvtNumber_Weight.at(" << -a4Int << ").at(" << a5Int << ").at(" << eventCounter << ")" << alphaInt_EvtNumber_Weight.at(-a4Int).at(a5Int).at(eventCounter) << std::endl;

//                    std::cout << "alphaInt_HistW[" << a4Int << "][" << a5Int << "]->Fill(" << cosThetaStarW << "," << weight << "*" << matrixElementWeight << ");" << std::endl;
                    alphaInt_HistW[a4Int][a5Int]->Fill(cosThetaStarW,weight*matrixElementWeight);

                    for (DoubleVector::iterator it = cosThetaStarWJets->begin(); it != cosThetaStarWJets->end(); it++)
                    {
                        double cosThetaStarWJet(*it);
//                        std::cout << "alphaInt_HistWJ[" << a4Int << "][" << a5Int << "]->Fill(" << cosThetaStarWJet << "," << weight <<"*" << matrixElementWeight << ");" << std::endl;
                        alphaInt_HistWJ[a4Int][a5Int]->Fill(cosThetaStarWJet,weight*matrixElementWeight);
                    }
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
/*
            TCanvas *pTCanvas = new TCanvas();
            pTCanvas->Draw();
            pTCanvas->Divide(2,1);
            pTCanvas->cd(1);
            pTH1F->Draw();
            pTCanvas->cd(2);
            m_pTH1F_DistributionJ_Sample->Draw();
            pTCanvas->SaveAs("Test.png");
            Pause();
*/
            double nll(0.f);
            this->CalculateLogLikelihood1D(pTH1F,m_pTH1F_DistributionJ_Sample,nll);
            m_Alpah4.push_back(a4Int*a4Step);
            m_Alpah5.push_back(a5Int*a5Step);
            m_NLLJ.push_back(nll);
        }
    } 

/*
    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);
//        double weight(pProcess->GetProcessWeight());
        double weight(pProcess->GetPostBDTProcessWeight());
//        TChain *pTChain(pProcess->GetTChain());
        TChain *pTChain(pProcess->GetPostBDTTChain());

        CouplingAnalysis *pCouplingAnalysis = NULL;

        if (pProcess->GetEventType() == "ee_nunuqqqq")
            pCouplingAnalysis = new CouplingAnalysis(pProcess->GetEventType(),this->NumberToString(pProcess->GetEnergy()));

        double cosThetaStarW(0.0);
        DoubleVector *cosThetaStarWJets(NULL);
        double cosThetaStarZ(0.0);
        DoubleVector *cosThetaStarZJets(NULL);
        double bdt(std::numeric_limits<double>::max());
        int generatorSerialInt(std::numeric_limits<int>::max());

        pTChain->SetBranchAddress("CosThetaStarWBosons", &cosThetaStarW);
        pTChain->SetBranchAddress("CosThetaStarWJets", &cosThetaStarWJets);
        pTChain->SetBranchAddress("CosThetaStarZBosons", &cosThetaStarZ);
        pTChain->SetBranchAddress("CosThetaStarZJets", &cosThetaStarZJets);
        pTChain->SetBranchAddress("BDT", &bdt);
        pTChain->SetBranchAddress("GeneratorSerialNumber", &generatorSerialInt);

        int eventCounter(0);
*/
/*
    for (int a4Int = -5; a4Int < 6; a4Int++)
    {
        for (int a5Int = -5; a5Int < 6; a5Int++)
        {
            const double a4Current((float)(a4Int) * 0.01);
            const double a5Current((float)(a5Int) * 0.01);

            TH1F *pTH1F_DistributionJ = new TH1F("CosThetaJets","Cos#theta_{Jets}",100,0,1);
            TH1F *pTH1F_DistributionW = new TH1F("CosThetaW","Cos#theta_{W}",100,0,1);

            for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
            {
                const Process *pProcess(*it);
//        double weight(pProcess->GetProcessWeight());
                double weight(pProcess->GetPostBDTProcessWeight());
//        TChain *pTChain(pProcess->GetTChain());
                TChain *pTChain(pProcess->GetPostBDTTChain());

                CouplingAnalysis *pCouplingAnalysis = NULL;

                if (pProcess->GetEventType() == "ee_nunuqqqq")
                    pCouplingAnalysis = new CouplingAnalysis(pProcess->GetEventType(),this->NumberToString(pProcess->GetEnergy()));

                double cosThetaStarW(0.0);
                DoubleVector *cosThetaStarWJets(NULL);
                double cosThetaStarZ(0.0);
                DoubleVector *cosThetaStarZJets(NULL);
                double bdt(std::numeric_limits<double>::max());
                int generatorSerialInt(std::numeric_limits<int>::max());

                pTChain->SetBranchAddress("CosThetaStarWBosons", &cosThetaStarW);
                pTChain->SetBranchAddress("CosThetaStarWJets", &cosThetaStarWJets);
                pTChain->SetBranchAddress("CosThetaStarZBosons", &cosThetaStarZ);
                pTChain->SetBranchAddress("CosThetaStarZJets", &cosThetaStarZJets);
                pTChain->SetBranchAddress("BDT", &bdt);
                pTChain->SetBranchAddress("GeneratorSerialNumber", &generatorSerialInt);

                int eventCounter(0);
                IntVector readInSGN;

                for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
                {
                    pTChain->GetEntry(event);
                    eventCounter++;

                    if (std::find(readInSGN.begin(), readInSGN.end(), generatorSerialInt) == readInSGN.end())
                    {
                        readInSGN.push_back(generatorSerialInt);
                        eventCounter = 1;
                    }

                    if (bdt > 0.4) // and pProcess->DoesEventPassCuts(event))
                    {
                        float matrixElementWeight(1.f);

                        if (pProcess->GetEventType() == "ee_nunuqqqq")
                        {
//                        std::cout << "Getting weight " << generatorSerialInt << std::endl; 
                            const int eventNumber(1000*(generatorSerialInt-1) + eventCounter);
//                        std::cout << "GeneratorSerialInt " << generatorSerialInt << std::endl;
//                        std::cout << "eventCounter " << eventCounter << std::endl;
//                        std::cout << "eventNumber " << eventNumber << std::endl;

                            pCouplingAnalysis->GetWeight(eventNumber, a4Current, a5Current, matrixElementWeight);
                        }

                        pTH1F_DistributionW->Fill(cosThetaStarW,weight*matrixElementWeight);

                        for (DoubleVector::iterator it = cosThetaStarWJets->begin(); it != cosThetaStarWJets->end(); it++)
                        {
                            const double cosThetaStarWJet(*it);
                            pTH1F_DistributionJ->Fill(cosThetaStarWJet,weight*matrixElementWeight);
                        }
                    }
                }
            }
 
            double nllJ(0.0), nllW(0.0);

            std::cout << "a4Current : " << a4Current << std::endl;
            std::cout << "a5Current : " << a5Current << std::endl;

            this->CalculateLogLikelihood1D(pTH1F_DistributionJ, m_pTH1F_DistributionJ_Sample, nllJ);
            this->CalculateLogLikelihood1D(pTH1F_DistributionW, m_pTH1F_DistributionW_Sample, nllW);

            TCanvas *pTCanvas = new TCanvas();
            pTCanvas->Draw();
            pTCanvas->Divide(2);
            pTCanvas->cd(0);
            pTH1F_DistributionJ->Draw();
            pTCanvas->cd(1);
            m_pTH1F_DistributionJ_Sample->Draw();

            Pause();

            m_Alpah4.push_back(a4Current);
            m_Alpah5.push_back(a5Current);
            m_NLLW.push_back(nllW);
            m_NLLJ.push_back(nllJ);
        }
    }
*/
}

//=====================================================================

std::string Fit::GetGeneratorSerialNumber(std::string filename)
{
    std::size_t position = filename.find("GenNumber");
    return filename.substr(position+10,3);
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