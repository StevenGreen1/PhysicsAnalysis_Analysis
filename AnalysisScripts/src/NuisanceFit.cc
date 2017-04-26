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
    std::cout << "Adding nuisance term for process " << processName << " with sigma " << sigma << std::endl;

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
        alpha4Min = -0.007;
        alpha4Max = 0.007;
        alpha4Step = 0.001;
        alpha5Min = -0.006;
        alpha5Max = 0.006;
        alpha5Step = 0.001;
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

std::cout << "Minimising : " << alpha4 << ", " << alpha5 << std::endl;
//            m_chi2CosThetaStarSynJets = this->CalculateNuisanceChi2In1D(m_cosThetaStarSynJetsExpected, m_cosThetaStarSynJetsObserved);  // Good not MINUIT fit
//std::cout << "Chi2 from drawing from Gaussian distributions = " << this->CalculateNuisanceChi2In1D(m_cosThetaStarSynJetsExpected, m_cosThetaStarSynJetsObserved) << std::endl;
            m_chi2CosThetaStarSynJets = this->CalculateNuisanceChi2MINUITIn2D(); // EVIL!, but may work...
std::cout << m_chi2CosThetaStarSynJets << std::endl;
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
std::cout << "Adding " << filePath << std::endl;
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
        std::string name("CosThetaStarSynJetsObserved_" + processName);
        std::string title("Observed Cos#theta_{Jets}^{*} for " + processName);
        TH2F *pTH2F_J = new TH2F(this->SafeName(name),title.c_str(),m_nBins,0,1,m_nBins,0,1);
        pTH2F_J->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH2F_J->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynJetsObserved.insert(std::make_pair(processName, pTH2F_J));
    }
}

//=====================================================================

void NuisanceFit::InitialiseExpected()
{
    this->ClearExpected();

    for (const auto &processName: m_processNames)
    {
        std::string name("CosThetaStarSynJetsExpected_" + processName);
        std::string title("Expected Cos#theta_{Jets}^{*} for " + processName);
        TH2F *pTH2F_J = new TH2F(this->SafeName(name),title.c_str(),m_nBins,0,1,m_nBins,0,1);
        pTH2F_J->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        pTH2F_J->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynJetsExpected.insert(std::make_pair(processName, pTH2F_J));
    }
}

//=====================================================================

void NuisanceFit::ClearObserved()
{
    for (const auto &processName: m_processNames)
    {
        if (m_cosThetaStarSynJetsObserved.find(processName) != m_cosThetaStarSynJetsObserved.end())
        {
            TH2F *pTH2F_J = m_cosThetaStarSynJetsObserved.at(processName);
            if (pTH2F_J != NULL) delete pTH2F_J;
        }
    }
     m_cosThetaStarSynJetsObserved.clear();
}

//=====================================================================

void NuisanceFit::ClearExpected()
{
    for (const auto &processName: m_processNames)
    {
        if (m_cosThetaStarSynJetsExpected.find(processName) != m_cosThetaStarSynJetsExpected.end())
        {
            TH2F *pTH2F_J = m_cosThetaStarSynJetsExpected.at(processName);
            if (pTH2F_J != NULL) delete pTH2F_J;
        }
    }
     m_cosThetaStarSynJetsExpected.clear();
}

//=====================================================================

void NuisanceFit::MergeFiles(float alpha4, float alpha5, bool observed)
{
    std::cout << "Merging files for (alpha4,alpha5) = (" << alpha4 << "," << alpha5 << "), observed = " << observed << std::endl;

    if (observed && (abs(alpha4) > std::numeric_limits<float>::min() && abs(alpha5) > std::numeric_limits<float>::min()))
    {
        std::cout << "This looks like the observed value, but has been set as an expected.  Please check. "  << alpha4 << ", " << alpha5 << ", " << observed << std::endl;
        return;
    }

    for (const auto &fileName: m_filesToReadIn)
    {
        TFile *pTFile = new TFile(fileName.c_str());

        for (const auto &processName: m_processNames)
        {
            std::string plotName("");

            if (processName != "ee_nunuqqqq")
            {
                plotName = "CosThetaStarSynJets_Alpha4_"  + this->NumberToString(0.f) + "_Alpha5_" + this->NumberToString(0.f) + "_" + processName;
            }
            else
            {
                plotName = "CosThetaStarSynJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5) + "_" + processName;
            }

            TH2F *pTH2F_J = (TH2F*)pTFile->Get(plotName.c_str());

            if (pTH2F_J == NULL)
                continue;

            if (!observed)
            {
                if (m_cosThetaStarSynJetsExpected.find(processName) == m_cosThetaStarSynJetsExpected.end())
                {
                    std::cout << "Missing expected histogram.  Please locate..." << std::endl;
                    continue;
                }
//std::cout << std::setprecision(15) << "Adding Expected " << plotName << " " << pTH2F_J->Integral() << std::endl;
                m_cosThetaStarSynJetsExpected.at(processName)->Add(pTH2F_J);
            }
            else
            {
                if (m_cosThetaStarSynJetsObserved.find(processName) == m_cosThetaStarSynJetsObserved.end())
                {
                    std::cout << "Missing observed histogram.  Please locate..." << std::endl;
                    continue;
                }

                m_cosThetaStarSynJetsObserved.at(processName)->Add(pTH2F_J);
            }
        }
        delete pTFile;
    }
}

//=====================================================================

double NuisanceFit::CalculateNuisanceChi2MINUITIn2D()
{
    ROOT::Math::Minimizer *pMinimizer = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
    pMinimizer->SetMaxFunctionCalls(100000);
    pMinimizer->SetMaxIterations(10000);
    pMinimizer->SetTolerance(0.001);

    ROOT::Math::Functor functor(this, &NuisanceFit::GetChi2In2D, 2); 
    double step[2] = {0.01,0.01};
    double variable[2] = {1.0, 1.0};
 
    pMinimizer->SetFunction(functor);
    pMinimizer->SetVariable(0,"sigma_egamma_qqqqnu_BS",variable[0], step[0]);
    pMinimizer->SetVariable(1,"sigma_gammae_qqqqnu_BS",variable[1], step[1]);
    pMinimizer->Minimize(); 
 
    const double *minParam = pMinimizer->X();
    const double minChi2(this->GetChi2In2D(minParam));
    std::cout << "Minimum: f(" << minParam[0] << "," << minParam[1] << "): " << minChi2 << std::endl;
    delete pMinimizer;
    return minChi2;
}

//=====================================================================

double NuisanceFit::GetChi2In2D(const double *param)
{
    double r0(1.0);
    double chi2(0.0);
    const int nBinsX(m_cosThetaStarSynJetsExpected.begin()->second->GetXaxis()->GetNbins());
    const int nBinsY(m_cosThetaStarSynJetsExpected.begin()->second->GetYaxis()->GetNbins());

    typedef std::map<std::pair<int, int>, double> IntToIntToDoubleMap;
    IntToIntToDoubleMap binToContentMapObserved;
    IntToIntToDoubleMap binToContentMapExpected;

    for (const auto &stringToHistExpected: m_cosThetaStarSynJetsExpected)
    {
        std::string processName(stringToHistExpected.first);
std::cout << processName << std::endl;
        TH2F *pTH2F_Expected(stringToHistExpected.second); // Alpha4 and Alpha5 non-zero
        TH2F *pTH2F_Observed(m_cosThetaStarSynJetsObserved.at(processName)); // Alpha4 and Alpha5 zero
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
            for (unsigned int yBin = 1; yBin < nBinsY; yBin++)
            {
                double observedBinContent(pTH2F_Observed->GetBinContent(xBin,yBin));
                double expectedBinContent(pTH2F_Expected->GetBinContent(xBin,yBin) * r);

                if (binToContentMapObserved.find(std::make_pair(xBin,yBin)) == binToContentMapObserved.end())
                {
                    binToContentMapObserved.insert(std::make_pair(std::make_pair(xBin,yBin), observedBinContent));
                }
                else 
                {
                    binToContentMapObserved.at(std::make_pair(xBin,yBin)) += observedBinContent;
                }

                if (binToContentMapExpected.find(std::make_pair(xBin,yBin)) == binToContentMapExpected.end())
                {
                    binToContentMapExpected.insert(std::make_pair(std::make_pair(xBin,yBin), expectedBinContent));
                }
                else
                {
                    binToContentMapExpected.at(std::make_pair(xBin,yBin)) += expectedBinContent;
                }
            }
        }
    }

    for (const auto &binContentPairObserved: binToContentMapObserved)
    {
        int xBin(binContentPairObserved.first.first);
        int yBin(binContentPairObserved.first.second);
        double binContentObserved(binContentPairObserved.second); // Observed, this is fixed.
        double binContentExpected(binToContentMapExpected.at(std::make_pair(xBin,yBin))); // Expected, this is fluctuated with nuisance.
        chi2 += (binContentObserved - binContentExpected) * (binContentObserved - binContentExpected) / binContentExpected;
    }
    return chi2;
}

//=====================================================================

TString NuisanceFit::SafeName(const TString &name)
{
    TObject *pTObject = gROOT->FindObject(name);
    if (pTObject) delete pTObject;
    return name;
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
