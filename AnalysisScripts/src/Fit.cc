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
    m_pTH2F_Distribution_Sample = new TH2F("SampleCosThetaJetsVsCosThetaW","Sample Cos#theta_{Jets} Vs Cos#theta_{W}",10,0,1,10,0,1);
    m_pTH2F_Derivative_Sample = new TH2F("SampleDerivativeCosThetaJetsVsCosThetaW","Sample Derivative Cos#theta_{Jets} Vs Cos#theta_{W}",9,0.05,0.95,9,0.05,0.95);

    m_pTH1F_DistributionJ_Sample = new TH1F("SampleCosThetaJets","Sample Cos#theta_{Jets}",100,0,1);
    m_pTH1F_DistributionW_Sample = new TH1F("SampleCosThetaW","Sample Cos#theta_{W}",100,0,1);

    this->FillDistribution();
    this->SaveDistribution();
}

//=====================================================================

void Fit::FillDistribution()
{
    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);
        double weight(pProcess->GetProcessWeight());
        TChain *pTChain(pProcess->GetTChain());

        CouplingAnalysis *pCouplingAnalysis = NULL;

        if (pProcess->GetEventType() == "ee_nunuqqqq")
            pCouplingAnalysis = new CouplingAnalysis(pProcess->GetEventType(),this->NumberToString(pProcess->GetEnergy()));

        double cosThetaStarW(0.0);
        DoubleVector *cosThetaStarWJets(NULL);
        double cosThetaStarZ(0.0);
        DoubleVector *cosThetaStarZJets(NULL);

        pTChain->SetBranchAddress("CosThetaStarWBosons", &cosThetaStarW);
        pTChain->SetBranchAddress("CosThetaStarWJets", &cosThetaStarWJets);
//        pTChain->SetBranchAddress("CosThetaStarZBosons", &cosThetaStarZ);
//        pTChain->SetBranchAddress("CosThetaStarZJets", &cosThetaStarZJets);

        StringVector readInFiles;
        std::string filename;
        int eventCounter(0);

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);

            if (!pProcess->DoesEventPassCuts(event))
                continue;

            m_pTH1F_DistributionW_Sample->Fill(cosThetaStarW,weight);

            for (DoubleVector::iterator it = cosThetaStarWJets->begin(); it != cosThetaStarWJets->end(); it++)
            {
                double cosThetaStarWJet(*it);
                m_pTH1F_DistributionJ_Sample->Fill(cosThetaStarWJet,weight);
                m_pTH2F_Distribution_Sample->Fill(cosThetaStarW,cosThetaStarWJet,weight);
            }
        }

        this->SetDerivative(m_pTH2F_Distribution_Sample, m_pTH2F_Derivative_Sample);

        for (int a4Int = -5; a4Int < 6; a4Int++)
        {
            for (int a5Int = -5; a5Int < 6; a5Int++)
            {
                const double a4Current((float)(a4Int) * 0.01);
                const double a5Current((float)(a5Int) * 0.01);

//                TH2F *pTH2F_Distribution = new TH2F("CosThetaJetsVsCosThetaW","Cos#theta_{Jets} Vs Cos#theta_{W}",10,0,1,10,0,1);
//                TH2F *pTH2F_Derivative = new TH2F("DerivativeCosThetaJetsVsCosThetaW","Derivative Cos#theta_{Jets} Vs Cos#theta_{W}",9,0.05,0.95,9,0.05,0.95);


                TH1F *pTH1F_DistributionJ = new TH1F("CosThetaJets","Cos#theta_{Jets}",100,0,1);
                TH1F *pTH1F_DistributionW = new TH1F("CosThetaW","Cos#theta_{W}",100,0,1);

                StringVector readInFiles;
                std::string filename;
                int eventCounter(0);

                for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
                {
                    pTChain->GetEntry(event);
                    eventCounter++;

                    if (!pProcess->DoesEventPassCuts(event))
                        continue;

                    TFile *pTFileActive = pTChain->GetCurrentFile();
                    std::string activeFileName(pTFileActive->GetName());
                    const int generatorSerialInt(atoi(this->GetGeneratorSerialNumber(activeFileName).c_str()));

                    if (std::find(readInFiles.begin(), readInFiles.end(), activeFileName) == readInFiles.end())
                    {
                        readInFiles.push_back(activeFileName);
                        eventCounter = 1;
                    }

                    const int eventNumber(1000*(generatorSerialInt-1) + eventCounter);

//            if (eventNumber >= 5)
//                continue;

//            std::cout << "activeFileName     : " << activeFileName << std::endl;
//            std::cout << "generatorSerialInt : " << generatorSerialInt << std::endl;
//            std::cout << "eventCounter       : " << eventCounter << std::endl;
//            std::cout << "eventNumber        : " << eventNumber << std::endl;

                    float matrixElementWeight(1.f);

                    if (pProcess->GetEventType() == "ee_nunuqqqq")
                        pCouplingAnalysis->GetWeight(eventNumber, a4Current, a5Current, matrixElementWeight);

                    pTH1F_DistributionW->Fill(cosThetaStarW,weight*matrixElementWeight);

                    for (DoubleVector::iterator it = cosThetaStarWJets->begin(); it != cosThetaStarWJets->end(); it++)
                    {
                        const double cosThetaStarWJet(*it);
                        pTH1F_DistributionJ->Fill(cosThetaStarWJet,weight*matrixElementWeight);
//                        pTH2F_Distribution->Fill(cosThetaStarW,cosThetaStarWJet,weight*matrixElementWeight);
                    }
                }
//                this->SetDerivative(pTH2F_Distribution, pTH2F_Derivative);
//                this->CalculateLogLikelihood(pTH2F_Derivative, a4Current, a5Current);

                double nllJ(0.0), nllW(0.0);

                std::cout << "a4Current : " << a4Current << std::endl;
                std::cout << "a5Current : " << a5Current << std::endl;

                this->CalculateLogLikelihood1D(pTH1F_DistributionJ, m_pTH1F_DistributionJ_Sample, nllJ);
                this->CalculateLogLikelihood1D(pTH1F_DistributionW, m_pTH1F_DistributionW_Sample, nllW);

                m_Alpah4.push_back(a4Current);
                m_Alpah5.push_back(a5Current);
                m_NLLW.push_back(nllW);
                m_NLLJ.push_back(nllJ);
            }
        }
    }
}

//=====================================================================

std::string Fit::GetGeneratorSerialNumber(std::string filename)
{
    std::size_t position = filename.find("GenNumber");
    return filename.substr(position+10,3);
}

//=====================================================================

void Fit::SetDerivative(TH2F *pTH2F_Distribution, TH2F *&pTH2F_Derivative) const 
{
    const int nBinsX = pTH2F_Distribution->GetXaxis()->GetNbins();
    const int nBinsY = pTH2F_Distribution->GetXaxis()->GetNbins();

    // No underflow xBin = 0 or overflow xBin = nBinsX + 1 included in loop (or second to last bin which makes no sense for calculation
    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
        for (unsigned int yBin = 1; yBin < nBinsY; yBin++)
        {
            const double binContentX0Y0 = pTH2F_Distribution->GetBinContent(xBin,yBin);
            const double binContentX1Y0 = pTH2F_Distribution->GetBinContent(xBin+1,yBin);
            const double binContentX0Y1 = pTH2F_Distribution->GetBinContent(xBin,yBin+1);
            const double binContentX1Y1 = pTH2F_Distribution->GetBinContent(xBin+1,yBin+1);

            const double binCentreX0 = pTH2F_Distribution->GetXaxis()->GetBinCenter(xBin);
            const double binCentreX1 = pTH2F_Distribution->GetXaxis()->GetBinCenter(xBin+1);
            const double binCentreY0 = pTH2F_Distribution->GetYaxis()->GetBinCenter(yBin);
            const double binCentreY1 = pTH2F_Distribution->GetYaxis()->GetBinCenter(yBin+1);

            const double deltaX(binCentreX1-binCentreX0);
            const double deltaY(binCentreY1-binCentreY0);

            const double newBinContent((binContentX0Y0 + binContentX1Y1 - binContentX1Y0 - binContentX0Y1)/(deltaX*deltaY));
            const double newBinCentreX((binCentreX0+binCentreX1)*0.5);
            const double newBinCentreY((binCentreY0+binCentreY1)*0.5);

            pTH2F_Derivative->Fill(newBinCentreX,newBinCentreY,newBinContent);
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
        std::cout << "nll : " << nll << std::endl;
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

void Fit::CalculateLogLikelihood(TH2F *pTH2F_Derivative, const double alpha4, const double alpha5) 
{
    if (!gApplication) new TApplication("Application", ((int *)0), ((char **)0));

    const int nBinsX = pTH2F_Derivative->GetXaxis()->GetNbins();
    const int nBinsY = pTH2F_Derivative->GetXaxis()->GetNbins();
    long double nll(0.0);

    TH1F *pTH1F = new TH1F("Distribution","Distribution",10000,-100000,100000);
    TH1F *pTH1FSample = new TH1F("DistributionSample","DistributionSample",10000,-100000,100000);

    // No underflow xBin = 0 or overflow xBin = nBinsX + 1 included in loop (or second to last bin which makes no sense for calculation
    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
        for (unsigned int yBin = 1; yBin < nBinsY; yBin++)
        {
            const double binContent = pTH2F_Derivative->GetBinContent(xBin,yBin);
            const double binContentSample = m_pTH2F_Derivative_Sample->GetBinContent(xBin,yBin);
            const double binCentreA4 = pTH2F_Derivative->GetXaxis()->GetBinCenter(xBin);
            const double binCentreA5 = pTH2F_Derivative->GetYaxis()->GetBinCenter(yBin);

//            std::cout << "binContent       : " << binContent << std::endl;
//            std::cout << "binContentSample : " << binContentSample << std::endl;
//            std::cout << "Adding           : " << (-1.0 * binContentSample * log(binContent)) + binContent << std::endl;
            pTH1F->Fill(binContent);
            pTH1FSample->Fill(binContentSample);
//            nll += (-1.0 * binContentSample * log(binContent)) + binContent;
//            std::cout << "nll : " << nll << std::endl; 
        }
    }
//    std::cout << "alpha4           : " << alpha4 << std::endl;
//    std::cout << "alpha5           : " << alpha5 << std::endl;
/*
    TCanvas *pTCanvas = new TCanvas("One","One");
    pTH1F->Draw();

    TCanvas *pTCanvas2 = new TCanvas("Two","Two");
    pTH1FSample->Draw();
    Pause();
*/
    const int nBinsXX = pTH1F->GetXaxis()->GetNbins();
    for (unsigned int xBin = 1; xBin < nBinsXX; xBin++)
    {
        const double binContent = pTH1F->GetBinContent(xBin);
        const double binContentSample = pTH1FSample->GetBinContent(xBin);

        if (binContent > 0)
        {
            nll += (-1.0 * binContentSample * log(binContent)) + binContent;
//            std::cout << "binContent       : " << binContent << std::endl;
//            std::cout << "log(binContent)  : " << log(binContent) << std::endl;
//            std::cout << "binContentSample : " << binContentSample << std::endl;
//            std::cout << "Adding           : " << (-1.0 * binContentSample * log(binContent)) + binContent << std::endl;
//            std::cout << "nll : " << nll << std::endl;
        }
    }

//    m_Alpah4.push_back(alpha4);
//    m_Alpah5.push_back(alpha5);
//    m_NLL.push_back(nll);
}

//=====================================================================

void Fit::SaveDistribution()
{
    TCanvas *pTCanvas = new TCanvas();
    TGraph2D *pTGraph2DW = new TGraph2D();
    TGraph2D *pTGraph2DJ = new TGraph2D();

    double minnllw(std::numeric_limits<double>::max()), minnllj(std::numeric_limits<double>::max());

    for (DoubleVector::iterator iter = m_Alpah4.begin(); iter != m_Alpah4.end(); iter++)
    {
        const int position(iter-m_Alpah4.begin());
        if (minnllw > m_NLLW.at(position))
            minnllw = m_NLLW.at(position);

        if (minnllj > m_NLLJ.at(position))
            minnllj = m_NLLJ.at(position);
    }

    for (DoubleVector::iterator iter = m_Alpah4.begin(); iter != m_Alpah4.end(); iter++)
    {
        const int position(iter-m_Alpah4.begin());
        pTGraph2DW->SetPoint(pTGraph2DW->GetN(), m_Alpah4.at(position), m_Alpah5.at(position), m_NLLW.at(position) - minnllw);
        pTGraph2DJ->SetPoint(pTGraph2DJ->GetN(), m_Alpah4.at(position), m_Alpah5.at(position), m_NLLJ.at(position) - minnllj);
    }
    pTGraph2DW->Draw("SURF3");
    pTCanvas->SaveAs("LoglikelihoddPlotW.C");

    pTGraph2DJ->Draw("SURF3");
    pTCanvas->SaveAs("LoglikelihoddPlotJ.C");

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
