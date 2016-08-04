/**
 *  @file   AnalysisScripts/src/Fit.cc 
 * 
 *  @brief  Implementation of the fit class.
 * 
 *  $Log: $
 */

#include "Fit.h"

//=====================================================================

Fit::Fit(const ProcessVector &processVector) :
    m_processVector(processVector)
{
    m_distribution = new TH2F("CosThetaJetsVsCosThetaW","Cos#theta_{Jets} Vs Cos#theta_{W}",10,0,1,10,0,1);
    m_derivative = new TH2F("DerivativeCosThetaJetsVsCosThetaW","DerivativeCos#theta_{Jets} Vs Cos#theta_{W}",9,0.05,0.95,9,0.05,0.95);

    this->FillDistribution();
    this->SetDerivative();
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
            eventCounter++;

            TFile *pTFileActive = pTChain->GetCurrentFile();
            std::string activeFileName(pTFileActive->GetName());
            std::string generatorSerialString(this->GetGeneratorSerialNumber(activeFileName));

            if (std::find(readInFiles.begin(), readInFiles.end(), activeFileName) == readInFiles.end())
            {
                readInFiles.push_back(activeFileName);
                eventCounter = 1;
            }

            std::cout << activeFileName << std::endl;
            std::cout << generatorSerialString << std::endl;
            std::cout << eventCounter << std::endl;



            for (DoubleVector::iterator it = cosThetaStarWJets->begin(); it != cosThetaStarWJets->end(); it++)
            {
                double cosThetaStarWJet(*it);
                m_distribution->Fill(cosThetaStarW,cosThetaStarWJet,weight);
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

void Fit::SetDerivative()
{
    const int nBinsX = m_distribution->GetXaxis()->GetNbins();
    const int nBinsY = m_distribution->GetXaxis()->GetNbins();

    // No underflow xBin = 0 or overflow xBin = nBinsX + 1 included in loop (or second to last bin which makes no sense for calculation
    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
        for (unsigned int yBin = 1; yBin < nBinsY; yBin++)
        {
            const double binContentX0Y0 = m_distribution->GetBinContent(xBin,yBin);
            const double binContentX1Y0 = m_distribution->GetBinContent(xBin+1,yBin);
            const double binContentX0Y1 = m_distribution->GetBinContent(xBin,yBin+1);
            const double binContentX1Y1 = m_distribution->GetBinContent(xBin+1,yBin+1);

            const double binCentreX0 = m_distribution->GetXaxis()->GetBinCenter(xBin);
            const double binCentreX1 = m_distribution->GetXaxis()->GetBinCenter(xBin+1);
            const double binCentreY0 = m_distribution->GetYaxis()->GetBinCenter(yBin);
            const double binCentreY1 = m_distribution->GetYaxis()->GetBinCenter(yBin+1);

            const double deltaX(binCentreX1-binCentreX0);
            const double deltaY(binCentreY1-binCentreY0);

            const double newBinContent((binContentX0Y0 + binContentX1Y1 - binContentX1Y0 - binContentX0Y1)/(deltaX*deltaY));
            const double newBinCentreX((binCentreX0+binCentreX1)*0.5);
            const double newBinCentreY((binCentreY0+binCentreY1)*0.5);

            m_derivative->Fill(newBinCentreX,newBinCentreY,newBinContent);
        }
    }
}

//=====================================================================

void Fit::SaveDistribution()
{
    TH2F *pTH2F = (TH2F*)(m_distribution->Clone());
    std::string processName = pTH2F->GetName();
    std::string saveName = processName + ".C";
    TCanvas *pTCanvas = new TCanvas();
    pTH2F->Draw("COLZ");
    pTCanvas->SaveAs(saveName.c_str());
    pTH2F->SetName(this->RandomName().c_str());

    pTH2F = (TH2F*)(m_derivative->Clone());
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
