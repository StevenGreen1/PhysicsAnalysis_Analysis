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
    this->InitialiseReference();
    this->MergeFiles(0.f, 0.f, true);

    for (double alpha4 = alpha4Min; alpha4 < alpha4Max; alpha4 = alpha4 + alpha4Step)
    {
        for (double alpha5 = alpha5Min; alpha5 < alpha5Max; alpha5 = alpha5 + alpha5Step)
        {
            this->Initialise();
            this->MergeFiles(alpha4, alpha5);

            m_pTFile->cd();
            m_alpha4 = alpha4;
            m_alpha5 = alpha5;

//std::cout << "Minimising : " << alpha4 << ", " << alpha5 << std::endl;
//            m_chi2CosThetaStarSynJets = this->CalculateNuisanceChi2In1D(m_cosThetaStarSynJets, m_cosThetaStarSynJetsRef);  // Good not MINUIT fit
//std::cout << "Chi2 from drawing from Gaussian distributions = " << this->CalculateNuisanceChi2In1D(m_cosThetaStarSynJets, m_cosThetaStarSynJetsRef) << std::endl;
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

void NuisanceFit::InitialiseReference()
{
    this->ClearReference();

    for (const auto &processName: m_processNames)
    {
/*
        std::string name1("CosThetaStarSynJets_vs_BosonsRef_" + processName);
        std::string title1("Reference Cos#theta_{Jets}^{*} vs Cos#theta_{Bosons}^{*} for " + processName);
        TH2F *pTH2F = new TH2F(this->SafeName(name1),title1.c_str(),m_nBins,0,1,m_nBins,0,1);
        pTH2F->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH2F->GetYaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        m_cosThetaStarSynJets_vs_BosonsRef.insert(std::make_pair(processName, pTH2F));
*/
        std::string name2("CosThetaStarSynJetsRef_" + processName);
        std::string title2("Reference Cos#theta_{Jets}^{*} for " + processName);
        TH1F *pTH1F_J = new TH1F(this->SafeName(name2),title2.c_str(),m_nBins,0,1);
        pTH1F_J->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH1F_J->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynJetsRef.insert(std::make_pair(processName, pTH1F_J));
/*
        std::string name3("CosThetaStarSynBosonsRef_" + processName);
        std::string title3("Reference Cos#theta_{Bosons}^{*} for " + processName);
        TH1F *pTH1F_B = new TH1F(this->SafeName(name3),title3.c_str(),m_nBins,0,1);
        pTH1F_B->GetXaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        pTH1F_B->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynBosonsRef.insert(std::make_pair(processName, pTH1F_B));
*/
    }
}

//=====================================================================

void NuisanceFit::Initialise()
{
    this->Clear();

    for (const auto &processName: m_processNames)
    {
/*
        std::string name1("CosThetaStarSynJets_vs_Bosons_" + processName);
        std::string title1("Cos#theta_{Jets}^{*} vs Cos#theta_{Bosons}^{*} for " + processName);
        TH2F *pTH2F = new TH2F(this->SafeName(name1),title1.c_str(),m_nBins,0,1,m_nBins,0,1);
        pTH2F->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH2F->GetYaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        m_cosThetaStarSynJets_vs_Bosons.insert(std::make_pair(processName, pTH2F));
*/
        std::string name2("CosThetaStarSynJets_" + processName);
        std::string title2("Cos#theta_{Jets}^{*} for " + processName);
        TH1F *pTH1F_J = new TH1F(this->SafeName(name2),title2.c_str(),m_nBins,0,1);
        pTH1F_J->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH1F_J->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynJets.insert(std::make_pair(processName, pTH1F_J));
/*
        std::string name3("CosThetaStarSynBosons_" + processName);
        std::string title3("Cos#theta_{Bosons}^{*} for " + processName);
        TH1F *pTH1F_B = new TH1F(this->SafeName(name3),title3.c_str(),m_nBins,0,1);
        pTH1F_B->GetXaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        pTH1F_B->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynBosons.insert(std::make_pair(processName, pTH1F_B));
*/
    }
}

//=====================================================================

void NuisanceFit::ClearReference()
{
    for (const auto &processName: m_processNames)
    {
/*
        if (m_cosThetaStarSynJets_vs_BosonsRef.find(processName) != m_cosThetaStarSynJets_vs_BosonsRef.end())
        {
            TH2F *pTH2F = m_cosThetaStarSynJets_vs_BosonsRef.at(processName);
            if (pTH2F != NULL) delete pTH2F;
        }
*/
        if (m_cosThetaStarSynJetsRef.find(processName) != m_cosThetaStarSynJetsRef.end())
        {
            TH1F *pTH1F_J = m_cosThetaStarSynJetsRef.at(processName);
            if (pTH1F_J != NULL) delete pTH1F_J;
        }
/*
        if (m_cosThetaStarSynBosonsRef.find(processName) != m_cosThetaStarSynBosonsRef.end())
        {
            TH1F *pTH1F_B = m_cosThetaStarSynBosonsRef.at(processName);
            if (pTH1F_B != NULL) delete pTH1F_B;
        }
*/
    }
//     m_cosThetaStarSynJets_vs_BosonsRef.clear();
     m_cosThetaStarSynJetsRef.clear();
//     m_cosThetaStarSynBosonsRef.clear();
}

//=====================================================================

void NuisanceFit::Clear()
{
    for (const auto &processName: m_processNames)
    {
/* 
       if (m_cosThetaStarSynJets_vs_Bosons.find(processName) != m_cosThetaStarSynJets_vs_Bosons.end())
        {
            TH2F *pTH2F = m_cosThetaStarSynJets_vs_Bosons.at(processName);
            if (pTH2F != NULL) delete pTH2F;
        }
*/
        if (m_cosThetaStarSynJets.find(processName) != m_cosThetaStarSynJets.end())
        {
            TH1F *pTH1F_J = m_cosThetaStarSynJets.at(processName);
            if (pTH1F_J != NULL) delete pTH1F_J;
        }
/*
        if (m_cosThetaStarSynBosons.find(processName) != m_cosThetaStarSynBosons.end())
        {
            TH1F *pTH1F_B = m_cosThetaStarSynBosons.at(processName);
            if (pTH1F_B != NULL) delete pTH1F_B;
        }
*/
    }
//     m_cosThetaStarSynJets_vs_Bosons.clear();
     m_cosThetaStarSynJets.clear();
//     m_cosThetaStarSynBosons.clear();
}

//=====================================================================

void NuisanceFit::MergeFiles(float alpha4, float alpha5, bool reference)
{
    std::cout << "Merging files for (alpha4,alpha5) = (" << alpha4 << "," << alpha5 << "), reference = " << reference << std::endl;
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

            if (!reference)
            {
/*
                if (m_cosThetaStarSynJets_vs_Bosons.find(processName) == m_cosThetaStarSynJets_vs_Bosons.end() or 
                    m_cosThetaStarSynJets.find(processName) == m_cosThetaStarSynJets.end() or 
                    m_cosThetaStarSynBosons.find(processName) == m_cosThetaStarSynBosons.end())
*/
                if (m_cosThetaStarSynJets.find(processName) == m_cosThetaStarSynJets.end())
                {
                    std::cout << "Missing histogram.  Please locate..." << std::endl;
                    continue;
                }

                m_cosThetaStarSynJets.at(processName)->Add(pTH1F_J);
//                m_cosThetaStarSynBosons.at(processName)->Add(pTH1F_B);
//                m_cosThetaStarSynJets_vs_Bosons.at(processName)->Add(pTH2F);
            }
            else
            {
/*
                if (m_cosThetaStarSynJets_vs_BosonsRef.find(processName) == m_cosThetaStarSynJets_vs_BosonsRef.end() or
                    m_cosThetaStarSynJetsRef.find(processName) == m_cosThetaStarSynJetsRef.end() or
                    m_cosThetaStarSynBosonsRef.find(processName) == m_cosThetaStarSynBosonsRef.end())
*/
                if (m_cosThetaStarSynJetsRef.find(processName) == m_cosThetaStarSynJetsRef.end())
                {
                    std::cout << "Missing reference histogram.  Please locate..." << std::endl;
                    continue;
                }

                m_cosThetaStarSynJetsRef.at(processName)->Add(pTH1F_J);
//                m_cosThetaStarSynBosonsRef.at(processName)->Add(pTH1F_B);
//                m_cosThetaStarSynJets_vs_BosonsRef.at(processName)->Add(pTH2F);
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
//    std::cout << "Minimum: f(" << minParam[0] << "," << minParam[1] << "): " << minChi2 << std::endl;
    delete pMinimizer;
    return minChi2;
}

//=====================================================================

double NuisanceFit::GetChi2In1D(const double *param)
{
    double r0(1.0);
    double chi2(0.0);
    const int nBinsX(m_cosThetaStarSynJets.begin()->second->GetXaxis()->GetNbins());

    typedef std::map<int, double> IntToDoubleMap;
    IntToDoubleMap binToContentMap;
    IntToDoubleMap binToContentMapRef;

    for (const auto &stringHistPair: m_cosThetaStarSynJets)
    {
        std::string processName(stringHistPair.first);
        TH1F *pTH1F(stringHistPair.second);
        TH1F *pTH1FRef(m_cosThetaStarSynJetsRef.at(processName));
        double r(1.0);

        if (processName == "egamma_qqqqnu_BS")
        {
            double nuisanceSigma = 0.1;
            r = param[0];
            chi2 += (r - r0) * (r - r0) / (2 * nuisanceSigma * nuisanceSigma);
        }
        else if (processName == "gammae_qqqqnu_BS")
        {
            double nuisanceSigma = 0.1;
            r = param[1];
            chi2 += (r - r0) * (r - r0) / (2 * nuisanceSigma * nuisanceSigma);
        }

        for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
        {
            if (binToContentMap.find(xBin) == binToContentMap.end())
            {
                binToContentMap.insert(std::make_pair(xBin,pTH1F->GetBinContent(xBin)));
            }
            else
            {
                binToContentMap.at(xBin) += pTH1F->GetBinContent(xBin);
            }

            if (binToContentMapRef.find(xBin) == binToContentMapRef.end())
            {
                binToContentMapRef.insert(std::make_pair(xBin,pTH1FRef->GetBinContent(xBin)*r));
            }
            else
            {
                binToContentMapRef.at(xBin) += pTH1FRef->GetBinContent(xBin) * r;
            }
        }
    }

    for (const auto &binContentPair: binToContentMap)
    {
        int bin(binContentPair.first);
        double binContent(binContentPair.second);
        double binContentRef(binToContentMapRef.at(bin));
        chi2 += (binContent - binContentRef) * (binContent - binContentRef) / binContentRef;
    }
    return chi2;
}

//=====================================================================

double NuisanceFit::CalculateNuisanceChi2In1D(OneDHistogramMap hists, OneDHistogramMap histsRef)
{
    typedef std::map<std::string, double> StringToDoubleMap;
    double r0(1.0);
    double chi2Best(std::numeric_limits<double>::max());

    int randomN(0);
    const int nIterations(10000);
    for (int i = 0; i < nIterations; i++)
    {
        double chi2(0.0);
        const int nBinsX(hists.begin()->second->GetXaxis()->GetNbins());

        typedef std::map<int, double> IntToDoubleMap;
        IntToDoubleMap binToContentMap;
        IntToDoubleMap binToContentMapRef;

        for (const auto &stringHistPair: hists)
        {
            std::string processName(stringHistPair.first);
            TH1F *pTH1F(stringHistPair.second);
            TH1F *pTH1FRef(histsRef.at(processName));
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
                if (binToContentMap.find(xBin) == binToContentMap.end())
                {
                    binToContentMap.insert(std::make_pair(xBin,pTH1F->GetBinContent(xBin)));
                }
                else
                {
                    binToContentMap.at(xBin) += pTH1F->GetBinContent(xBin);
                }

                if (binToContentMapRef.find(xBin) == binToContentMapRef.end())
                {
                    binToContentMapRef.insert(std::make_pair(xBin,pTH1FRef->GetBinContent(xBin)*r));
                }
                else
                {
                    binToContentMapRef.at(xBin) += pTH1FRef->GetBinContent(xBin) * r;
                }
            }
        }

        for (const auto &binContentPair: binToContentMap)
        {
            int bin(binContentPair.first);
            double binContent(binContentPair.second);
            double binContentRef(binToContentMapRef.at(bin));
//std::cout << "Bin Contentes and ref " << binContent << " " << binContentRef << std::endl;
            chi2 += (binContent - binContentRef) * (binContent - binContentRef) / binContentRef;
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

double NuisanceFit::CalculateChi2In1D(TH1F *pTH1F, TH1F *pTH1FRef)
{
    if (m_fluctuateNominal)
    {
        double chi2(0.0);
        const int nIterations(10000);
        const int nBinsX(pTH1F->GetXaxis()->GetNbins());
        TRandom3 *pTRandom3 = new TRandom3();

        for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
        {
            double sumOfChi2(0.0);
            const double binContent = pTH1F->GetBinContent(xBin);
            const double expected = pTH1FRef->GetBinContent(xBin);

            for (unsigned int i = 0; i < nIterations; i++)
            {
                const double observed = (double)(pTRandom3->Poisson(expected));
                sumOfChi2 += (binContent - observed) * (binContent - observed) / observed;
//std::cout << "binContent  : " << binContent << std::endl;
//std::cout << "expected    : " << expected << std::endl;
//std::cout << "observed    : " << observed << std::endl;
            }
            chi2 += sumOfChi2 / (double)(nIterations);
        }
        delete pTRandom3;
        return chi2;
    }

    else
    {
        double chi2(0.0);
        const int nBinsX(pTH1F->GetXaxis()->GetNbins());

        for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
        {
            const double binContent = pTH1F->GetBinContent(xBin);
            const double binContentRef = pTH1FRef->GetBinContent(xBin);
            chi2 += (binContent - binContentRef) * (binContent - binContentRef) / binContentRef;
        }

        return chi2;
    }
}

//=====================================================================

double NuisanceFit::CalculateChi2In2D(TH2F *pTH2F, TH2F *pTH2FRef)
{
    double chi2(0.0);
    const int nBinsX(pTH2F->GetXaxis()->GetNbins());
    const int nBinsY(pTH2F->GetYaxis()->GetNbins());

    for (unsigned int xBin = 1; xBin < nBinsX; xBin++)
    {
        for (unsigned int yBin = 1; yBin < nBinsY; yBin++)
        {
            const double binContent = pTH2F->GetBinContent(xBin, yBin);
            const double binContentRef = pTH2FRef->GetBinContent(xBin, yBin);
            chi2 += (binContent - binContentRef) * (binContent - binContentRef) / binContentRef;
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
