/**
 *  @file   AnalysisScripts/src/NuisanceFit.cc 
 * 
 *  @brief  Implementation of the fit class.
 * 
 *  $Log: $
 */

#include "NuisanceFit.h"

#include "TSystem.h"
#include <fcntl.h>

//=====================================================================

NuisanceFit::NuisanceFit(std::string inputDescriptor, std::string inputPath, std::string outputDescriptor, std::string outputPath, const int energy, const int nBins, bool background) :
    m_inputDescriptor(inputDescriptor),
    m_inputPath(inputPath),
    m_outputDescriptor(outputDescriptor),
    m_outputPath(outputPath),
    m_energy(energy),
    m_nBins(nBins),
    m_background(background),
    m_fluctuateNominal(false),
    m_alpha4(0.0),
    m_alpha5(0.0),
    m_chi2CosThetaStarSynJets_vs_Bosons(0.0),
    m_chi2CosThetaStarSynJets(0.0),
    m_chi2CosThetaStarSynBosons(0.0),
    m_rootFileName(outputPath + outputDescriptor + "_" + this->NumberToString(energy) + "GeV_NuisanceFitData.root")
{
    m_processNames.clear();
    m_processNames.push_back("ee_nunuqqqq");
    m_processNames.push_back("ee_lnuqqqq");
    m_processNames.push_back("ee_llqqqq");
    m_processNames.push_back("ee_qqqq");
    m_processNames.push_back("ee_nunuqq");
    m_processNames.push_back("ee_lnuqq");
    m_processNames.push_back("ee_qqll");
    m_processNames.push_back("ee_qq");
    m_processNames.push_back("egamma_qqqqe_EPA");
    m_processNames.push_back("egamma_qqqqe_BS");
    m_processNames.push_back("gammae_qqqqe_EPA");
    m_processNames.push_back("gammae_qqqqe_BS");
    m_processNames.push_back("egamma_qqqqnu_EPA");
    m_processNames.push_back("egamma_qqqqnu_BS");
    m_processNames.push_back("gammae_qqqqnu_EPA");
    m_processNames.push_back("gammae_qqqqnu_BS");
    m_processNames.push_back("gammagamma_qqqq_EPA_EPA");
    m_processNames.push_back("gammagamma_qqqq_EPA_BS");
    m_processNames.push_back("gammagamma_qqqq_BS_EPA");
    m_processNames.push_back("gammagamma_qqqq_BS_BS");

    m_nuisanceBackgrounds.clear();
//    m_nuisanceBackgrounds.insert(std::make_pair("egamma_qqqqnu_BS",0.1));
//    m_nuisanceBackgrounds.insert(std::make_pair("gammae_qqqqnu_BS",0.1));

    TH1::AddDirectory(kFALSE);

    // Output data file
    m_pTFile = new TFile(m_rootFileName.c_str(), "recreate");

    m_pTTree = new TTree("AnalysisProcessorTree", "AnalysisProcessorTree");
    m_pTTree->SetDirectory(m_pTFile);
//    m_pTTree->Branch("Chi2CosThetaStarSynJets_vs_Bosons", &m_chi2CosThetaStarSynJets_vs_Bosons, "Chi2CosThetaStarSynJets_vs_Bosons/D");
    m_pTTree->Branch("Chi2CosThetaStarSynJets", &m_chi2CosThetaStarSynJets, "Chi2CosThetaStarSynJets/D");
//    m_pTTree->Branch("Chi2CosThetaStarSynBosons", &m_chi2CosThetaStarSynBosons, "Chi2CosThetaStarSynBosons/D");
    m_pTTree->Branch("Alpha4", &m_alpha4, "Alpha4/D");
    m_pTTree->Branch("Alpha5", &m_alpha5, "Alpha5/D");
}

//=====================================================================

NuisanceFit::~NuisanceFit()
{
    m_pTFile->cd();
    m_pTTree->Write();
    m_pTFile->Close();
    delete m_pTFile;
}

//=====================================================================

void NuisanceFit::AddNuisance(std::string processName, double sigma)
{
    if (sigma < 0.000001)
    {
        std::cout << "Adding nuisance term to " << processName << " with sigma " << sigma << " is basically forcing the cross section to be a delta function and so adding nuisance is irrelevant and so it is skipped." << std::endl;  
        return;
    }

    if (m_nuisanceBackgrounds.find(processName) != m_nuisanceBackgrounds.end())
    {
        m_nuisanceBackgrounds.at(processName) = sigma;
    }
    else
    {
        m_nuisanceBackgrounds.insert(std::make_pair(processName, sigma));
    }
}

//=====================================================================

void NuisanceFit::Merge()
{
    double alpha4Min(0.0);
    double alpha4Max(0.0);
    double alpha4Step(1.0);
    double alpha5Min(0.0);
    double alpha5Max(0.0);
    double alpha5Step(1.0);

    if (m_energy == 1400 and !m_background)
    {
        alpha4Min = -0.02;
        alpha4Max = 0.0205;
        alpha4Step = 0.001;
        alpha5Min = -0.02;
        alpha5Max = 0.0205;
        alpha5Step = 0.001;
    }
    else if (m_energy == 1400 and m_background)
    {
/*
        alpha4Min = -0.005;
        alpha4Max = 0.0055;
        alpha4Step = 0.0025;
        alpha5Min = -0.005;
        alpha5Max = 0.0055;
        alpha5Step = 0.0025;
*/
        alpha4Min = -0.045;
        alpha4Max = 0.0455;
        alpha4Step = 0.0025;
        alpha5Min = -0.045;
        alpha5Max = 0.0455;
        alpha5Step = 0.0025;
    }
    else if (m_energy == 3000 and !m_background)
    {
        alpha4Min = -0.002;
        alpha4Max = 0.00205;
        alpha4Step = 0.0001;
        alpha5Min = -0.002;
        alpha5Max = 0.00205;
        alpha5Step = 0.0001;
    }
    else if (m_energy == 3000 and m_background)
    {
        alpha4Min = -0.002;
        alpha4Max = 0.00205;
        alpha4Step = 0.0001;
        alpha5Min = -0.002;
        alpha5Max = 0.00205;
        alpha5Step = 0.0001;
    }

    this->FindFiles();
    this->InitialiseObserved();
    this->MergeFiles(0.f, 0.f, true);

    for (double alpha4 = alpha4Min; alpha4 < alpha4Max; alpha4 = alpha4 + alpha4Step)
    {
        for (double alpha5 = alpha5Min; alpha5 < alpha5Max; alpha5 = alpha5 + alpha5Step)
        {
            this->InitialiseExpected();
            this->MergeFiles(alpha4, alpha5);

            m_pTFile->cd();
            m_alpha4 = alpha4;
            m_alpha5 = alpha5;

//std::cout << "Minimising : " << alpha4 << ", " << alpha5 << std::endl;
//            m_chi2CosThetaStarSynJets = this->CalculateNuisanceChi2In1D(m_cosThetaStarSynJetsExpected, m_cosThetaStarSynJetsObserved);  // Good not MINUIT fit
//std::cout << "Chi2 from drawing from Gaussian distributions = " << this->CalculateNuisanceChi2In1D(m_cosThetaStarSynJetsExpected, m_cosThetaStarSynJetsObserved) << std::endl;
            m_chi2CosThetaStarSynJets = this->CalculateNuisanceChi2MINUITIn1D(); // EVIL!, but may work...
//std::cout << m_chi2CosThetaStarSynJets << std::endl;
            m_pTTree->Fill();
        }
    }
}

//=====================================================================

void NuisanceFit::FindFiles()
{
    TSystemDirectory directory(m_inputPath.c_str(), m_inputPath.c_str());
    TList *listOfFiles = directory.GetListOfFiles();
    listOfFiles->Sort(); // Alphabetises the list

    if (listOfFiles)
    {
        TSystemFile *file;
        TString fileCandidate;
        TIter next(listOfFiles);
        while ((file=(TSystemFile*)next()))
        {
            fileCandidate = file->GetName();
            TString energyString = this->NumberToString(m_energy) + "GeV";
            if (m_background)
            {
                if (!file->IsDirectory() and fileCandidate.EndsWith("root") and fileCandidate.Contains(m_inputDescriptor.c_str()) and fileCandidate.Contains(energyString) and fileCandidate.Contains("Final_BuildIndividualDistributionData"))
                {
                    std::string filePath = m_inputPath + fileCandidate.Data();
                    m_filesToReadIn.push_back(filePath);
                }
            }
            else 
            {
                if (!file->IsDirectory() and fileCandidate.EndsWith("root") and fileCandidate.Contains(m_inputDescriptor.c_str()) and fileCandidate.Contains(energyString) and !fileCandidate.Contains("Final_BuildIndividualDistributionData"))
                {
                    std::string filePath = m_inputPath + fileCandidate.Data();
                    m_filesToReadIn.push_back(filePath);
                }
            }
        }
    }
}

//=====================================================================

void NuisanceFit::InitialiseObserved()
{
    this->ClearObserved();

    for (const auto &processName: m_processNames)
    {
/*
        std::string name1("CosThetaStarSynJets_vs_BosonsObserved_" + processName);
        std::string title1("Observed Cos#theta_{Jets}^{*} vs Cos#theta_{Bosons}^{*} for " + processName);
        TH2F *pTH2F = new TH2F(this->SafeName(name1),title1.c_str(),m_nBins,0,1,m_nBins,0,1);
        pTH2F->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH2F->GetYaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        m_cosThetaStarSynJets_vs_BosonsObserved.insert(std::make_pair(processName, pTH2F));
*/
        std::string name2("CosThetaStarSynJetsObserved_" + processName);
        std::string title2("Observed Cos#theta_{Jets}^{*} for " + processName);
        TH1F *pTH1F_J = new TH1F(this->SafeName(name2),title2.c_str(),m_nBins,0,1);
        pTH1F_J->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH1F_J->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynJetsObserved.insert(std::make_pair(processName, pTH1F_J));
/*
        std::string name3("CosThetaStarSynBosonsObserved_" + processName);
        std::string title3("Observed Cos#theta_{Bosons}^{*} for " + processName);
        TH1F *pTH1F_B = new TH1F(this->SafeName(name3),title3.c_str(),m_nBins,0,1);
        pTH1F_B->GetXaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        pTH1F_B->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynBosonsObserved.insert(std::make_pair(processName, pTH1F_B));
*/
    }
}

//=====================================================================

void NuisanceFit::InitialiseExpected()
{
    this->ClearExpected();

    for (const auto &processName: m_processNames)
    {
/*
        std::string name1("CosThetaStarSynJets_vs_BosonsExpected_" + processName);
        std::string title1("Expected Cos#theta_{Jets}^{*} vs Cos#theta_{Bosons}^{*} for " + processName);
        TH2F *pTH2F = new TH2F(this->SafeName(name1),title1.c_str(),m_nBins,0,1,m_nBins,0,1);
        pTH2F->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH2F->GetYaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        m_cosThetaStarSynJets_vs_BosonsExpected.insert(std::make_pair(processName, pTH2F));
*/
        std::string name2("CosThetaStarSynJetsExpected_" + processName);
        std::string title2("Expected Cos#theta_{Jets}^{*} for " + processName);
        TH1F *pTH1F_J = new TH1F(this->SafeName(name2),title2.c_str(),m_nBins,0,1);
        pTH1F_J->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH1F_J->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynJetsExpected.insert(std::make_pair(processName, pTH1F_J));
/*
        std::string name3("CosThetaStarSynBosonsExpected_" + processName);
        std::string title3("Expected Cos#theta_{Bosons}^{*} for " + processName);
        TH1F *pTH1F_B = new TH1F(this->SafeName(name3),title3.c_str(),m_nBins,0,1);
        pTH1F_B->GetXaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        pTH1F_B->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynBosonsExpected.insert(std::make_pair(processName, pTH1F_B));
*/
    }
}

//=====================================================================

void NuisanceFit::ClearObserved()
{
    for (const auto &processName: m_processNames)
    {
/*
        if (m_cosThetaStarSynJets_vs_BosonsObserved.find(processName) != m_cosThetaStarSynJets_vs_BosonsObserved.end())
        {
            TH2F *pTH2F = m_cosThetaStarSynJets_vs_BosonsObserved.at(processName);
            if (pTH2F != NULL) delete pTH2F;
        }
*/
        if (m_cosThetaStarSynJetsObserved.find(processName) != m_cosThetaStarSynJetsObserved.end())
        {
            TH1F *pTH1F_J = m_cosThetaStarSynJetsObserved.at(processName);
            if (pTH1F_J != NULL) delete pTH1F_J;
        }
/*
        if (m_cosThetaStarSynBosonsObserved.find(processName) != m_cosThetaStarSynBosonsObserved.end())
        {
            TH1F *pTH1F_B = m_cosThetaStarSynBosonsObserved.at(processName);
            if (pTH1F_B != NULL) delete pTH1F_B;
        }
*/
    }
//     m_cosThetaStarSynJets_vs_BosonsObserved.clear();
     m_cosThetaStarSynJetsObserved.clear();
//     m_cosThetaStarSynBosonsObserved.clear();
}

//=====================================================================

void NuisanceFit::ClearExpected()
{
    for (const auto &processName: m_processNames)
    {
/* 
       if (m_cosThetaStarSynJets_vs_BosonsExpected.find(processName) != m_cosThetaStarSynJets_vs_BosonsExpected.end())
        {
            TH2F *pTH2F = m_cosThetaStarSynJets_vs_BosonsExpected.at(processName);
            if (pTH2F != NULL) delete pTH2F;
        }
*/
        if (m_cosThetaStarSynJetsExpected.find(processName) != m_cosThetaStarSynJetsExpected.end())
        {
            TH1F *pTH1F_J = m_cosThetaStarSynJetsExpected.at(processName);
            if (pTH1F_J != NULL) delete pTH1F_J;
        }
/*
        if (m_cosThetaStarSynBosonsExpected.find(processName) != m_cosThetaStarSynBosonsExpected.end())
        {
            TH1F *pTH1F_B = m_cosThetaStarSynBosonsExpected.at(processName);
            if (pTH1F_B != NULL) delete pTH1F_B;
        }
*/
    }
//     m_cosThetaStarSynJets_vs_BosonsExpected.clear();
     m_cosThetaStarSynJetsExpected.clear();
//     m_cosThetaStarSynBosonsExpected.clear();
}

//=====================================================================

void NuisanceFit::MergeFiles(float alpha4, float alpha5, bool observed)
{
    std::cout << "Merging files for (alpha4,alpha5) = (" << alpha4 << "," << alpha5 << "), observed = " << observed << std::endl;
    for (const auto &fileName: m_filesToReadIn)
    {
        TFile *pTFile = new TFile(fileName.c_str());

        for (const auto &processName: m_processNames)
        {
            std::string plotName1("CosThetaStarSynJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5) + "_" + processName);
            TH1F *pTH1F_J = (TH1F*)pTFile->Get(plotName1.c_str());
/*
            std::string plotName2("CosThetaStarSynBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5) + "_" + processName);
            TH1F *pTH1F_B = (TH1F*)pTFile->Get(plotName2.c_str());
            std::string plotName3("CosThetaStarSynJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5) + "_" + processName);
            TH2F *pTH2F = (TH2F*)pTFile->Get(plotName3.c_str());
*/

            if (pTH1F_J == NULL)
                continue;

            if (!observed)
            {
/*
                if (m_cosThetaStarSynJets_vs_BosonsExpected.find(processName) == m_cosThetaStarSynJets_vs_BosonsExpected.end() or 
                    m_cosThetaStarSynJetsExpected.find(processName) == m_cosThetaStarSynJetsExpected.end() or 
                    m_cosThetaStarSynBosonsExpected.find(processName) == m_cosThetaStarSynBosonsExpected.end())
*/
                if (m_cosThetaStarSynJetsExpected.find(processName) == m_cosThetaStarSynJetsExpected.end())
                {
                    std::cout << "Missing expected histogram.  Please locate..." << std::endl;
                    continue;
                }

                m_cosThetaStarSynJetsExpected.at(processName)->Add(pTH1F_J);
//                m_cosThetaStarSynBosonsExpected.at(processName)->Add(pTH1F_B);
//                m_cosThetaStarSynJets_vs_BosonsExpected.at(processName)->Add(pTH2F);
            }
            else
            {
/*
                if (m_cosThetaStarSynJets_vs_BosonsObserved.find(processName) == m_cosThetaStarSynJets_vs_BosonsObserved.end() or
                    m_cosThetaStarSynJetsObserved.find(processName) == m_cosThetaStarSynJetsObserved.end() or
                    m_cosThetaStarSynBosonsObserved.find(processName) == m_cosThetaStarSynBosonsObserved.end())
*/
                if (m_cosThetaStarSynJetsObserved.find(processName) == m_cosThetaStarSynJetsObserved.end())
                {
                    std::cout << "Missing observed histogram.  Please locate..." << std::endl;
                    continue;
                }

                m_cosThetaStarSynJetsObserved.at(processName)->Add(pTH1F_J);
//                m_cosThetaStarSynBosonsObserved.at(processName)->Add(pTH1F_B);
//                m_cosThetaStarSynJets_vs_BosonsObserved.at(processName)->Add(pTH2F);
            }
        }
        delete pTFile;
    }
}

//=====================================================================

double NuisanceFit::CalculateNuisanceChi2MINUITIn1D()
{
    ROOT::Math::Minimizer *pMinimizer = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
    pMinimizer->SetMaxFunctionCalls(100000);
    pMinimizer->SetMaxIterations(10000);
    pMinimizer->SetTolerance(0.001);

    ROOT::Math::Functor functor(this, &NuisanceFit::GetChi2In1D, 2); 
    double step[2] = {0.01,0.01};
    double variable[2] = {1.0, 1.0};
 
    pMinimizer->SetFunction(functor);
    pMinimizer->SetVariable(0,"sigma_egamma_qqqqnu_BS",variable[0], step[0]);
    pMinimizer->SetVariable(1,"sigma_gammae_qqqqnu_BS",variable[1], step[1]);
    pMinimizer->Minimize(); 
 
    const double *minParam = pMinimizer->X();
    const double minChi2(this->GetChi2In1D(minParam));
    std::cout << "Minimum: f(" << minParam[0] << "," << minParam[1] << "): " << minChi2 << std::endl;
    delete pMinimizer;
    return minChi2;
}

//=====================================================================

double NuisanceFit::GetChi2In1D(const double *param)
{
    double r0(1.0);
    double chi2(0.0);
    const int nBinsX(m_cosThetaStarSynJetsExpected.begin()->second->GetXaxis()->GetNbins());

    typedef std::map<int, double> IntToDoubleMap;
    IntToDoubleMap binToContentMapObserved;
    IntToDoubleMap binToContentMapExpected;

    for (const auto &stringToHistExpected: m_cosThetaStarSynJetsExpected)
    {
        std::string processName(stringToHistExpected.first);
        TH1F *pTH1F_Expected(stringToHistExpected.second); // Alpha4 and Alpha5 non-zero
        TH1F *pTH1F_Observed(m_cosThetaStarSynJetsObserved.at(processName)); // Alpha4 and Alpha5 zero
        double r(1.0);

        if (processName == "egamma_qqqqnu_BS")
        {
            double nuisanceSigma = m_nuisanceBackgrounds.at(processName);
            r = param[0];
            chi2 += (r - r0) * (r - r0) / (2 * nuisanceSigma * nuisanceSigma);
        }
        else if (processName == "gammae_qqqqnu_BS")
        {
            double nuisanceSigma = m_nuisanceBackgrounds.at(processName);
            r = param[1];
            chi2 += (r - r0) * (r - r0) / (2 * nuisanceSigma * nuisanceSigma);
        }

        for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
        {
            if (binToContentMapObserved.find(xBin) == binToContentMapObserved.end())
            {
                binToContentMapObserved.insert(std::make_pair(xBin,pTH1F_Observed->GetBinContent(xBin)));
            }
            else
            {
                binToContentMapObserved.at(xBin) += pTH1F_Observed->GetBinContent(xBin);
            }

            if (binToContentMapExpected.find(xBin) == binToContentMapExpected.end())
            {
                binToContentMapExpected.insert(std::make_pair(xBin,pTH1F_Expected->GetBinContent(xBin) * r));
            }
            else
            {
                binToContentMapExpected.at(xBin) += pTH1F_Expected->GetBinContent(xBin) * r;
            }
        }
    }

    for (const auto &binContentPairObserved: binToContentMapObserved)
    {
        int bin(binContentPairObserved.first);
        double binContentObserved(binContentPairObserved.second); // Observed, this is fixed.
        double binContentExpected(binToContentMapExpected.at(bin)); // Expected, this is fluctuated with nuisance.
        chi2 += (binContentObserved - binContentExpected) * (binContentObserved - binContentExpected) / binContentExpected;
    }
    return chi2;
}

//=====================================================================

double NuisanceFit::CalculateNuisanceChi2In1D(OneDHistogramMap histsExpected, OneDHistogramMap histsObserved)
{
    typedef std::map<std::string, double> StringToDoubleMap;
    double r0(1.0);
    double chi2Best(std::numeric_limits<double>::max());

    int randomN(0);
    const int nIterations(10000);
    for (int i = 0; i < nIterations; i++)
    {
        double chi2(0.0);
        const int nBinsX(histsExpected.begin()->second->GetXaxis()->GetNbins());

        typedef std::map<int, double> IntToDoubleMap;
        IntToDoubleMap binToContentMapObserved;
        IntToDoubleMap binToContentMapExpected;

        for (const auto &stringToHistExpected: histsExpected)
        {
            std::string processName(stringToHistExpected.first);
            TH1F *pTH1F_Expected(stringToHistExpected.second);
            TH1F *pTH1F_Observed(histsObserved.at(processName));
            double r(1.0);

            if (m_nuisanceBackgrounds.find(processName) != m_nuisanceBackgrounds.end())
            {
                TRandom3 *pTRandom3 = new TRandom3(randomN);
                randomN++;
                double nuisanceSigma = m_nuisanceBackgrounds.at(processName);
                r = pTRandom3->Gaus(r0, nuisanceSigma);
                chi2 += (r - r0) * (r - r0) / (2 * nuisanceSigma * nuisanceSigma);
//std::cout << "For process " << processName << ", the r parameter is " << r << std::endl;
//std::cout << "With nuisance sigma " << nuisanceSigma << std::endl;
                delete pTRandom3;
            }

            for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
            {
                if (binToContentMapObserved.find(xBin) == binToContentMapObserved.end())
                {
                    binToContentMapObserved.insert(std::make_pair(xBin,pTH1F_Observed->GetBinContent(xBin)));
                }
                else
                {
                    binToContentMapObserved.at(xBin) += pTH1F_Observed->GetBinContent(xBin);
                }

                if (binToContentMapExpected.find(xBin) == binToContentMapExpected.end())
                {
                    binToContentMapExpected.insert(std::make_pair(xBin,pTH1F_Expected->GetBinContent(xBin)*r));
                }
                else
                {
                    binToContentMapExpected.at(xBin) += pTH1F_Expected->GetBinContent(xBin) * r;
                }
            }
        }

        for (const auto &binContentPair: binToContentMapObserved)
        {
            int bin(binContentPair.first);
            double binContentObserved(binContentPair.second);
            double binContentExpected(binToContentMapExpected.at(bin));
//std::cout << "Bin Contents, expected and observed " << binContentExpected << " " << binContentObserved << std::endl;
            chi2 += (binContentObserved - binContentExpected) * (binContentObserved - binContentExpected) / binContentExpected;
        }

//std::cout << "Giving a chi squared of " << chi2 << std::endl;
        if (chi2 < chi2Best) chi2Best = chi2;
//std::cout << "Best chi squared is " << chi2Best << std::endl;
    }
    return chi2Best;
}

//=====================================================================

TString NuisanceFit::SafeName(const TString &name)
{
    TObject *pTObject = gROOT->FindObject(name);
    if (pTObject) delete pTObject;
    return name;
}

//=====================================================================

double NuisanceFit::CalculateChi2In1D(TH1F *pTH1F_Expected, TH1F *pTH1F_Observed)
{
    if (m_fluctuateNominal)
    {
        double chi2(0.0);
        const int nIterations(10000);
        const int nBinsX(pTH1F_Expected->GetXaxis()->GetNbins());
        TRandom3 *pTRandom3 = new TRandom3();

        for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
        {
            double sumOfChi2(0.0);
            const double binContentExpected = pTH1F_Expected->GetBinContent(xBin);
            const double binContentObserved = pTH1F_Observed->GetBinContent(xBin);

            for (unsigned int i = 0; i < nIterations; i++)
            {
                const double binContentFluctuatedExpected = (double)(pTRandom3->Poisson(binContentExpected));
                sumOfChi2 += (binContentObserved - binContentFluctuatedExpected) * (binContentObserved - binContentFluctuatedExpected) / binContentFluctuatedExpected;
            }
            chi2 += sumOfChi2 / (double)(nIterations);
        }
        delete pTRandom3;
        return chi2;
    }

    else
    {
        double chi2(0.0);
        const int nBinsX(pTH1F_Expected->GetXaxis()->GetNbins());

        for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
        {
            const double binContentExpected = pTH1F_Expected->GetBinContent(xBin);
            const double binContentObserved = pTH1F_Observed->GetBinContent(xBin);
            chi2 += (binContentObserved - binContentExpected) * (binContentObserved - binContentExpected) / binContentExpected;
        }

        return chi2;
    }
}

//=====================================================================

double NuisanceFit::CalculateChi2In2D(TH2F *pTH2F_Expected, TH2F *pTH2F_Observed)
{
    double chi2(0.0);
    const int nBinsX(pTH2F_Expected->GetXaxis()->GetNbins());
    const int nBinsY(pTH2F_Expected->GetYaxis()->GetNbins());

    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
        for (unsigned int yBin = 1; yBin < nBinsY; yBin++)
        {
            const double binContentExpected = pTH2F_Expected->GetBinContent(xBin, yBin);
            const double binContentObserved = pTH2F_Observed->GetBinContent(xBin, yBin);
            chi2 += (binContentObserved - binContentExpected) * (binContentObserved - binContentExpected) / binContentExpected;
        }
    }

    return chi2;
}

//=====================================================================

std::string NuisanceFit::RandomName()
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
std::string NuisanceFit::NumberToString(T number)
{
    if (number < 0.00001 and number > -0.00001 and m_energy == 1400 and !m_background)
        return "1.04083e-17";

    else if (number < 0.00001 and number > -0.00001 and m_energy == 1400 and m_background)
        return "0.0";  // For the nuisance fit
//        return "7.80626e-18"; // For the normal fit

    else if (number < 0.00001 and number > -0.00001 and m_energy == 3000)
        return "0.0";

    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
