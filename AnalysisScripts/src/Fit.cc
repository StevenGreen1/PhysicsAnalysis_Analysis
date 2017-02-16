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

//=====================================================================

Fit::Fit(std::string descriptor, const int energy, const int nBins, std::string inputPath, bool background) : 
    m_descriptor(descriptor),
    m_energy(energy),
    m_nBins(nBins),
    m_inputPath(inputPath),
    m_background(background),
    m_fluctuateNominal(false),
    m_alpha4(0.0),
    m_alpha5(0.0),
    m_chi2CosThetaStarSynJets_vs_Bosons(0.0),
    m_chi2CosThetaStarWSynJets_vs_Bosons(0.0),
    m_chi2CosThetaStarZSynJets_vs_Bosons(0.0),
    m_chi2CosThetaStarSynJets(0.0),
    m_chi2CosThetaStarWSynJets(0.0),
    m_chi2CosThetaStarZSynJets(0.0),
    m_chi2CosThetaStarSynBosons(0.0),
    m_chi2CosThetaStarWSynBosons(0.0),
    m_chi2CosThetaStarZSynBosons(0.0),
    m_splitDistributions(false)
{
    if (background)
        m_rootFileName = descriptor + "_" + this->NumberToString(energy) + "GeV_FitDataOptimal.root";
    else
        m_rootFileName = descriptor + "_" + this->NumberToString(energy) + "GeV_FitData.root";

    TH1::AddDirectory(kFALSE);

    // Make things look pretty 
    m_red = {0.0, 0.00392156862745, 0.835294117647, 1.0, 0.619607843137, 0.0549019607843, 1.0, 0.0, 0.0, 0.58431372549, 1.0, 0.643137254902, 0.0, 0.56862745098, 0.38431372549, 0.419607843137, 0.0, 0.0, 0.41568627451, 0.0, 0.760784313725, 0.745098039216, 0.0, 0.372549019608, 1.0, 1.0, 1.0, 0.407843137255, 1.0, 0.588235294118, 0.596078431373, 0.654901960784, 0.00392156862745, 1.0, 0.996078431373, 0.741176470588, 0.00392156862745, 0.733333333333, 0.458823529412, 0.647058823529, 1.0, 0.466666666667, 0.478431372549, 0.149019607843, 0.0, 0.262745098039, 0.709803921569, 1.0, 1.0, 0.564705882353, 0.494117647059, 0.741176470588, 0.898039215686, 0.870588235294, 0.0, 0.0, 0.0, 0.0, 0.521568627451, 0.0, 0.470588235294, 0.0, 1.0, 0.909803921569};
    m_green = {0.0, 0.0, 1.0, 0.0, 0.0, 0.298039215686, 0.898039215686, 0.372549019608, 1.0, 0.0, 0.576470588235, 0.141176470588, 0.0823529411765, 0.81568627451, 0.0549019607843, 0.407843137255, 0.0, 0.490196078431, 0.509803921569, 0.682352941176, 0.549019607843, 0.6, 0.560784313725, 0.678431372549, 0.0, 0.0, 0.0078431372549, 0.239215686275, 0.454901960784, 0.541176470588, 1.0, 0.341176470588, 1.0, 0.933333333333, 0.537254901961, 0.776470588235, 0.81568627451, 0.533333333333, 0.266666666667, 1.0, 0.650980392157, 0.301960784314, 0.278431372549, 0.203921568627, 0.278431372549, 0.0, 0.0, 0.694117647059, 0.858823529412, 0.98431372549, 0.176470588235, 0.827450980392, 0.435294117647, 1.0, 1.0, 0.607843137255, 0.392156862745, 0.462745098039, 0.662745098039, 0.725490196078, 0.509803921569, 1.0, 0.43137254902, 0.36862745098};
    m_blue = {0.0, 0.403921568627, 0.0, 0.337254901961, 0.556862745098, 0.63137254902, 0.0078431372549, 0.223529411765, 0.0, 0.227450980392, 0.494117647059, 0.0, 0.266666666667, 0.796078431373, 0.0, 0.509803921569, 1.0, 0.709803921569, 0.423529411765, 0.494117647059, 0.623529411765, 0.439215686275, 0.611764705882, 0.305882352941, 0.0, 0.964705882353, 0.61568627451, 0.23137254902, 0.639215686275, 0.909803921569, 0.321568627451, 0.250980392157, 0.996078431373, 0.909803921569, 0.0, 1.0, 1.0, 0.0, 0.694117647059, 0.823529411765, 0.996078431373, 0.0, 0.509803921569, 0.0, 0.329411764706, 0.172549019608, 1.0, 0.403921568627, 0.4, 0.572549019608, 0.823529411765, 0.576470588235, 0.996078431373, 0.454901960784, 0.470588235294, 1.0, 0.00392156862745, 1.0, 0.0, 0.0901960784314, 0.192156862745, 0.776470588235, 0.254901960784, 0.745098039216};

    m_fillStyle = {3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001};

    // Output data file
    m_pTFile = new TFile(m_rootFileName.c_str(), "recreate");

    m_pTTree = new TTree("AnalysisProcessorTree", "AnalysisProcessorTree");
    m_pTTree->SetDirectory(m_pTFile);
    m_pTTree->Branch("Chi2CosThetaStarSynJets_vs_Bosons", &m_chi2CosThetaStarSynJets_vs_Bosons, "Chi2CosThetaStarSynJets_vs_Bosons/D");
    m_pTTree->Branch("Chi2CosThetaStarWSynJets_vs_Bosons", &m_chi2CosThetaStarWSynJets_vs_Bosons, "Chi2CosThetaStarWSynJets_vs_Bosons/D");
    m_pTTree->Branch("Chi2CosThetaStarZSynJets_vs_Bosons", &m_chi2CosThetaStarZSynJets_vs_Bosons, "Chi2CosThetaStarZSynJets_vs_Bosons/D");
    m_pTTree->Branch("Chi2CosThetaStarSynJets", &m_chi2CosThetaStarSynJets, "Chi2CosThetaStarSynJets/D");
    m_pTTree->Branch("Chi2CosThetaStarWSynJets", &m_chi2CosThetaStarWSynJets, "Chi2CosThetaStarWSynJets/D");
    m_pTTree->Branch("Chi2CosThetaStarZSynJets", &m_chi2CosThetaStarZSynJets, "Chi2CosThetaStarZSynJets/D");
    m_pTTree->Branch("Chi2CosThetaStarSynBosons", &m_chi2CosThetaStarSynBosons, "Chi2CosThetaStarSynBosons/D");
    m_pTTree->Branch("Chi2CosThetaStarWSynBosons", &m_chi2CosThetaStarWSynBosons, "Chi2CosThetaStarWSynBosons/D");
    m_pTTree->Branch("Chi2CosThetaStarZSynBosons", &m_chi2CosThetaStarZSynBosons, "Chi2CosThetaStarZSynBosons/D");
    m_pTTree->Branch("Alpha4", &m_alpha4, "Alpha4/D");
    m_pTTree->Branch("Alpha5", &m_alpha5, "Alpha5/D");
}

//=====================================================================

Fit::~Fit()
{
    m_pTFile->cd();
    m_pTTree->Write();
    m_pTFile->Close();
    delete m_pTFile;
}

//=====================================================================

void Fit::FluctuateNominal()
{
    m_fluctuateNominal = true;
}

//=====================================================================

void Fit::Merge()
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
        alpha4Min = -0.0039;
//        alpha4Max = 0.00395;
        alpha4Max = 0.00005;
        alpha4Step = 0.0001;
//        alpha5Min = -0.0039;
        alpha5Min = -0.0000;
        alpha5Max = 0.00395;
        alpha5Step = 0.0001;
/*
        alpha4Min = -0.002;
        alpha4Max = 0.00205;
        alpha4Step = 0.0001;
        alpha5Min = -0.002;
        alpha5Max = 0.00205;
        alpha5Step = 0.0001;
*/
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

            if (!m_splitDistributions)
            {
                m_chi2CosThetaStarSynJets = this->CalculateChi2In1D(m_cosThetaStarSynJetsExpected, m_cosThetaStarSynJetsObserved);
                m_chi2CosThetaStarSynBosons = this->CalculateChi2In1D(m_cosThetaStarSynBosonsExpected, m_cosThetaStarSynBosonsObserved);
                m_chi2CosThetaStarSynJets_vs_Bosons = this->CalculateChi2In2D(m_cosThetaStarSynJets_vs_BosonsExpected, m_cosThetaStarSynJets_vs_BosonsObserved);
            }
            else
            {
                m_chi2CosThetaStarWSynJets = this->CalculateChi2In1D(m_cosThetaStarWSynJetsExpected, m_cosThetaStarWSynJetsObserved);
                m_chi2CosThetaStarZSynJets = this->CalculateChi2In1D(m_cosThetaStarZSynJetsExpected, m_cosThetaStarZSynJetsObserved);
                m_chi2CosThetaStarWSynBosons = this->CalculateChi2In1D(m_cosThetaStarWSynBosonsExpected, m_cosThetaStarWSynBosonsObserved);
                m_chi2CosThetaStarZSynBosons = this->CalculateChi2In1D(m_cosThetaStarZSynBosonsExpected, m_cosThetaStarZSynBosonsObserved);
                m_chi2CosThetaStarWSynJets_vs_Bosons = this->CalculateChi2In2D(m_cosThetaStarWSynJets_vs_BosonsExpected, m_cosThetaStarWSynJets_vs_BosonsObserved);
                m_chi2CosThetaStarZSynJets_vs_Bosons = this->CalculateChi2In2D(m_cosThetaStarZSynJets_vs_BosonsExpected, m_cosThetaStarZSynJets_vs_BosonsObserved);
            }

            m_pTTree->Fill();

            if (!m_splitDistributions)
            {
                std::string title_CosThetaStarSynJets_vs_Bosons = "CosThetaStarSynJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarSynJets_vs_BosonsExpected->SetTitle(title_CosThetaStarSynJets_vs_Bosons.c_str());
                m_cosThetaStarSynJets_vs_BosonsExpected->SetName(title_CosThetaStarSynJets_vs_Bosons.c_str());
                m_cosThetaStarSynJets_vs_BosonsExpected->Write(m_cosThetaStarSynJets_vs_BosonsExpected->GetName(),TObject::kOverwrite);

                std::string title_CosThetaStarSynJets = "CosThetaStarSynJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarSynJetsExpected->SetTitle(title_CosThetaStarSynJets.c_str());
                m_cosThetaStarSynJetsExpected->SetName(title_CosThetaStarSynJets.c_str());
                m_cosThetaStarSynJetsExpected->Write(m_cosThetaStarSynJetsExpected->GetName(),TObject::kOverwrite);

                std::string title_CosThetaStarSynBosons = "CosThetaStarSynBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarSynBosonsExpected->SetTitle(title_CosThetaStarSynBosons.c_str());
                m_cosThetaStarSynBosonsExpected->SetName(title_CosThetaStarSynBosons.c_str());
                m_cosThetaStarSynBosonsExpected->Write(m_cosThetaStarSynBosonsExpected->GetName(),TObject::kOverwrite);
            }
            else
            {
                std::string title_CosThetaStarSynWJets_vs_Bosons = "CosThetaStarSynWJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarWSynJets_vs_BosonsExpected->SetTitle(title_CosThetaStarSynWJets_vs_Bosons.c_str());
                m_cosThetaStarWSynJets_vs_BosonsExpected->SetName(title_CosThetaStarSynWJets_vs_Bosons.c_str());
                m_cosThetaStarWSynJets_vs_BosonsExpected->Write(m_cosThetaStarWSynJets_vs_BosonsExpected->GetName(),TObject::kOverwrite);

                std::string title_CosThetaStarSynZJets_vs_Bosons = "CosThetaStarSynZJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarZSynJets_vs_BosonsExpected->SetTitle(title_CosThetaStarSynZJets_vs_Bosons.c_str());
                m_cosThetaStarZSynJets_vs_BosonsExpected->SetName(title_CosThetaStarSynZJets_vs_Bosons.c_str());
                m_cosThetaStarZSynJets_vs_BosonsExpected->Write(m_cosThetaStarZSynJets_vs_BosonsExpected->GetName(),TObject::kOverwrite);

                std::string title_CosThetaStarSynWJets = "CosThetaStarSynWJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarWSynJetsExpected->SetTitle(title_CosThetaStarSynWJets.c_str());
                m_cosThetaStarWSynJetsExpected->SetName(title_CosThetaStarSynWJets.c_str());
                m_cosThetaStarWSynJetsExpected->Write(m_cosThetaStarWSynJetsExpected->GetName(),TObject::kOverwrite);

                std::string title_CosThetaStarSynZJets = "CosThetaStarSynZJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarZSynJetsExpected->SetTitle(title_CosThetaStarSynZJets.c_str());
                m_cosThetaStarZSynJetsExpected->SetName(title_CosThetaStarSynZJets.c_str());
                m_cosThetaStarZSynJetsExpected->Write(m_cosThetaStarZSynJetsExpected->GetName(),TObject::kOverwrite);

                std::string title_CosThetaStarSynWBosons = "CosThetaStarSynWBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarWSynBosonsExpected->SetTitle(title_CosThetaStarSynWBosons.c_str());
                m_cosThetaStarWSynBosonsExpected->SetName(title_CosThetaStarSynWBosons.c_str());
                m_cosThetaStarWSynBosonsExpected->Write(m_cosThetaStarWSynBosonsExpected->GetName(),TObject::kOverwrite);

                std::string title_CosThetaStarSynZBosons = "CosThetaStarSynZBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
                m_cosThetaStarZSynBosonsExpected->SetTitle(title_CosThetaStarSynZBosons.c_str());
                m_cosThetaStarZSynBosonsExpected->SetName(title_CosThetaStarSynZBosons.c_str());
                m_cosThetaStarZSynBosonsExpected->Write(m_cosThetaStarZSynBosonsExpected->GetName(),TObject::kOverwrite);
            }
        }
    }
}

//=====================================================================

void Fit::FindFiles()
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
                if (!file->IsDirectory() and fileCandidate.EndsWith("root") and fileCandidate.Contains(m_descriptor.c_str()) and fileCandidate.Contains(energyString) and fileCandidate.Contains("Final") and !fileCandidate.Contains("IndividualDistributionData"))
                {
                    std::string filePath = m_inputPath + fileCandidate.Data();
                    m_filesToReadIn.push_back(filePath);
std::cout << "Including : " <<  fileCandidate << std::endl;
                }
            }
            else 
            {
                if (!file->IsDirectory() and fileCandidate.EndsWith("root") and fileCandidate.Contains(m_descriptor.c_str()) and fileCandidate.Contains(energyString) and !fileCandidate.Contains("Final") and !fileCandidate.Contains("IndividualDistributionData"))
                {
                    std::string filePath = m_inputPath + fileCandidate.Data();
                    m_filesToReadIn.push_back(filePath);
                }
            }
        }
    }
}

//=====================================================================

void Fit::InitialiseObserved()
{
    if (!m_splitDistributions)
    {
        m_cosThetaStarSynJets_vs_BosonsObserved = new TH2F(this->SafeName("CosThetaStarSynJets_vs_BosonsObserved"),"Observed Cos#theta_{Jets}^{*} vs Cos#theta_{Bosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_cosThetaStarSynJets_vs_BosonsObserved->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        m_cosThetaStarSynJets_vs_BosonsObserved->GetYaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        m_cosThetaStarSynJetsObserved = new TH1F(this->SafeName("CosThetaStarSynJetsObserved"),"Observed Cos#theta_{Jets}^{*}",m_nBins,0,1);
        m_cosThetaStarSynJetsObserved->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        m_cosThetaStarSynJetsObserved->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynBosonsObserved = new TH1F(this->SafeName("CosThetaStarSynBosonsObserved"),"Observed Cos#theta_{Bosons}^{*}",m_nBins,0,1);
        m_cosThetaStarSynBosonsObserved->GetXaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        m_cosThetaStarSynBosonsObserved->GetYaxis()->SetTitle("Entries");
    }
    else
    {
        m_cosThetaStarWSynJets_vs_BosonsObserved = new TH2F(this->SafeName("CosThetaStarSynWJets_vs_BosonsObserved"),"Observed Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_cosThetaStarWSynJets_vs_BosonsObserved->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_cosThetaStarWSynJets_vs_BosonsObserved->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_cosThetaStarZSynJets_vs_BosonsObserved = new TH2F(this->SafeName("CosThetaStarSynZJets_vs_BosonsObserved"),"Observed Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_cosThetaStarZSynJets_vs_BosonsObserved->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_cosThetaStarZSynJets_vs_BosonsObserved->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_cosThetaStarWSynJetsObserved = new TH1F(this->SafeName("CosThetaStarSynWJetsObserved"),"Observed Cos#theta_{WJets}^{*}",m_nBins,0,1);
        m_cosThetaStarWSynJetsObserved->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_cosThetaStarWSynJetsObserved->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarZSynJetsObserved = new TH1F(this->SafeName("CosThetaStarSynZJetsObserved"),"Observed Cos#theta_{ZJets}^{*}",m_nBins,0,1);
        m_cosThetaStarZSynJetsObserved->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_cosThetaStarZSynJetsObserved->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarWSynBosonsObserved = new TH1F(this->SafeName("CosThetaStarSynWBosonsObserved"),"Observed Cos#theta_{WBosons}^{*}",m_nBins,0,1);
        m_cosThetaStarWSynBosonsObserved->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_cosThetaStarWSynBosonsObserved->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarZSynBosonsObserved = new TH1F(this->SafeName("CosThetaStarSynZBosonsObserved"),"Observede Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
        m_cosThetaStarZSynBosonsObserved->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_cosThetaStarZSynBosonsObserved->GetYaxis()->SetTitle("Entries");
    }
}

//=====================================================================

void Fit::InitialiseExpected()
{
    if (!m_splitDistributions)
    {
        m_cosThetaStarSynJets_vs_BosonsExpected = new TH2F(this->SafeName("CosThetaStarSynJets_vs_BosonsExpected"),"Expected Cos#theta_{Jets}^{*} vs Cos#theta_{Bosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_cosThetaStarSynJets_vs_BosonsExpected->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        m_cosThetaStarSynJets_vs_BosonsExpected->GetYaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        m_cosThetaStarSynJetsExpected = new TH1F(this->SafeName("CosThetaStarSynJetsExpected"),"Expected Cos#theta_{Jets}^{*}",m_nBins,0,1);
        m_cosThetaStarSynJetsExpected->GetXaxis()->SetTitle("Cos#theta_{Jets}^{*}");
        m_cosThetaStarSynJetsExpected->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarSynBosonsExpected = new TH1F(this->SafeName("CosThetaStarSynBosonsExpected"),"Expected Cos#theta_{Bosons}^{*}",m_nBins,0,1);
        m_cosThetaStarSynBosonsExpected->GetXaxis()->SetTitle("Cos#theta_{Bosons}^{*}");
        m_cosThetaStarSynBosonsExpected->GetYaxis()->SetTitle("Entries");
    }
    else
    {
        m_cosThetaStarWSynJets_vs_BosonsExpected = new TH2F(this->SafeName("CosThetaStarSynWJets_vs_BosonsExpected"),"Expected Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_cosThetaStarWSynJets_vs_BosonsExpected->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_cosThetaStarWSynJets_vs_BosonsExpected->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_cosThetaStarZSynJets_vs_BosonsExpected = new TH2F(this->SafeName("CosThetaStarSynZJets_vs_BosonsExpected"),"Expected Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_cosThetaStarZSynJets_vs_BosonsExpected->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_cosThetaStarZSynJets_vs_BosonsExpected->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_cosThetaStarWSynJetsExpected = new TH1F(this->SafeName("CosThetaStarSynWJetsExpected"),"Expected Cos#theta_{WJets}^{*}",m_nBins,0,1);
        m_cosThetaStarWSynJetsExpected->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_cosThetaStarWSynJetsExpected->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarZSynJetsExpected = new TH1F(this->SafeName("CosThetaStarSynZJetsExpected"),"Expected Cos#theta_{ZJets}^{*}",m_nBins,0,1);
        m_cosThetaStarZSynJetsExpected->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_cosThetaStarZSynJetsExpected->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarWSynBosonsExpected = new TH1F(this->SafeName("CosThetaStarSynWBosonsExpected"),"Expected Cos#theta_{WBosons}^{*}",m_nBins,0,1);
        m_cosThetaStarWSynBosonsExpected->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_cosThetaStarWSynBosonsExpected->GetYaxis()->SetTitle("Entries");
        m_cosThetaStarZSynBosonsExpected = new TH1F(this->SafeName("CosThetaStarSynZBosonsExpected"),"Expected Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
        m_cosThetaStarZSynBosonsExpected->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_cosThetaStarZSynBosonsExpected->GetYaxis()->SetTitle("Entries");
    }
}

//=====================================================================

void Fit::MergeFiles(float alpha4, float alpha5, bool observed)
{
    std::cout << "Merging files for (alpha4,alpha5) = (" << alpha4 << "," << alpha5 << ")" << std::endl;
    for (const auto &fileName: m_filesToReadIn)
    {
        TH1F *pTH1F_CosThetaStarSynJets;
        TH1F *pTH1F_CosThetaStarSynWJets;
        TH1F *pTH1F_CosThetaStarSynZJets;
        TH1F *pTH1F_CosThetaStarSynBosons;
        TH1F *pTH1F_CosThetaStarSynWBosons;
        TH1F *pTH1F_CosThetaStarSynZBosons;
        TH2F *pTH2F_CosThetaStarSynJets_vs_Bosons;
        TH2F *pTH2F_CosThetaStarWSynJets_vs_Bosons;
        TH2F *pTH2F_CosThetaStarZSynJets_vs_Bosons;

        TFile *pTFile = new TFile(fileName.c_str());

        if (!m_splitDistributions)
        {
            std::string plotName1("CosThetaStarSynJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH1F_CosThetaStarSynJets = (TH1F*)pTFile->Get(plotName1.c_str());
            std::string plotName2("CosThetaStarSynBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH1F_CosThetaStarSynBosons = (TH1F*)pTFile->Get(plotName2.c_str());
            std::string plotName3("CosThetaStarSynJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH2F_CosThetaStarSynJets_vs_Bosons = (TH2F*)pTFile->Get(plotName3.c_str());

            if (!observed)
            {
                m_cosThetaStarSynJetsExpected->Add(pTH1F_CosThetaStarSynJets);
                m_cosThetaStarSynBosonsExpected->Add(pTH1F_CosThetaStarSynBosons);
                m_cosThetaStarSynJets_vs_BosonsExpected->Add(pTH2F_CosThetaStarSynJets_vs_Bosons);
            }
            else
            {
                m_cosThetaStarSynJetsObserved->Add(pTH1F_CosThetaStarSynJets);
                m_cosThetaStarSynBosonsObserved->Add(pTH1F_CosThetaStarSynBosons);
                m_cosThetaStarSynJets_vs_BosonsObserved->Add(pTH2F_CosThetaStarSynJets_vs_Bosons);
            }
        }
        else
        {
            std::string plotName4("CosThetaStarSynWJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH1F_CosThetaStarSynWJets = (TH1F*)pTFile->Get(plotName4.c_str());
            std::string plotName5("CosThetaStarSynZJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH1F_CosThetaStarSynZJets = (TH1F*)pTFile->Get(plotName5.c_str());
            std::string plotName6("CosThetaStarSynWBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH1F_CosThetaStarSynWBosons = (TH1F*)pTFile->Get(plotName6.c_str());
            std::string plotName7("CosThetaStarSynZBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH1F_CosThetaStarSynZBosons = (TH1F*)pTFile->Get(plotName7.c_str());
            std::string plotName8("CosThetaStarSynWJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH2F_CosThetaStarWSynJets_vs_Bosons = (TH2F*)pTFile->Get(plotName8.c_str());
            std::string plotName9("CosThetaStarSynZJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
            pTH2F_CosThetaStarZSynJets_vs_Bosons = (TH2F*)pTFile->Get(plotName9.c_str());

            if (!observed)
            {
                m_cosThetaStarWSynJetsExpected->Add(pTH1F_CosThetaStarSynWJets);
                m_cosThetaStarZSynJetsExpected->Add(pTH1F_CosThetaStarSynZJets);
                m_cosThetaStarWSynBosonsExpected->Add(pTH1F_CosThetaStarSynWBosons);
                m_cosThetaStarZSynBosonsExpected->Add(pTH1F_CosThetaStarSynZBosons);
                m_cosThetaStarWSynJets_vs_BosonsExpected->Add(pTH2F_CosThetaStarWSynJets_vs_Bosons);
                m_cosThetaStarZSynJets_vs_BosonsExpected->Add(pTH2F_CosThetaStarZSynJets_vs_Bosons);
            }
            else 
            {
                m_cosThetaStarWSynJetsObserved->Add(pTH1F_CosThetaStarSynWJets);
                m_cosThetaStarZSynJetsObserved->Add(pTH1F_CosThetaStarSynZJets);
                m_cosThetaStarWSynBosonsObserved->Add(pTH1F_CosThetaStarSynWBosons);
                m_cosThetaStarZSynBosonsObserved->Add(pTH1F_CosThetaStarSynZBosons);
                m_cosThetaStarWSynJets_vs_BosonsObserved->Add(pTH2F_CosThetaStarWSynJets_vs_Bosons);
                m_cosThetaStarZSynJets_vs_BosonsObserved->Add(pTH2F_CosThetaStarZSynJets_vs_Bosons);
            }
        }

        delete pTFile;

        if (!m_splitDistributions)
        {
            delete pTH1F_CosThetaStarSynJets;
            delete pTH1F_CosThetaStarSynBosons;
            delete pTH2F_CosThetaStarSynJets_vs_Bosons;
        }
        else
        {
            delete pTH1F_CosThetaStarSynWJets;
            delete pTH1F_CosThetaStarSynZJets;
            delete pTH1F_CosThetaStarSynWBosons;
            delete pTH1F_CosThetaStarSynZBosons;
            delete pTH2F_CosThetaStarWSynJets_vs_Bosons;
            delete pTH2F_CosThetaStarZSynJets_vs_Bosons;
        }
    }
}

//=====================================================================

TString Fit::SafeName(const TString &name)
{
    TObject *pTObject = gROOT->FindObject(name);
    if (pTObject) delete pTObject;
    return name;
}

//=====================================================================

void Fit::Clear()
{
    if (!m_splitDistributions)
    {
        delete m_cosThetaStarSynJetsExpected, m_cosThetaStarSynBosonsExpected, m_cosThetaStarSynJets_vs_BosonsExpected;
        delete m_cosThetaStarSynJetsObserved, m_cosThetaStarSynBosonsObserved, m_cosThetaStarSynJets_vs_BosonsObserved;
    }
    else
    {
        delete m_cosThetaStarWSynJetsExpected, m_cosThetaStarWSynBosonsExpected, m_cosThetaStarWSynJets_vs_BosonsExpected, m_cosThetaStarZSynJetsExpected, m_cosThetaStarZSynBosonsExpected, m_cosThetaStarZSynJets_vs_BosonsExpected;
        delete m_cosThetaStarWSynJetsObserved, m_cosThetaStarWSynBosonsObserved, m_cosThetaStarWSynJets_vs_BosonsObserved, m_cosThetaStarZSynJetsObserved, m_cosThetaStarZSynBosonsObserved, m_cosThetaStarZSynJets_vs_BosonsObserved;
    }
}

//=====================================================================

double Fit::CalculateChi2In1D(TH1F *pTH1F_Expected, TH1F *pTH1F_Observed)
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

double Fit::CalculateChi2In2D(TH2F *pTH2F_Expected, TH2F *pTH2F_Observed)
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
    if (number < 0.00001 and number > -0.00001 and m_energy == 1400 and !m_background)
        return "1.04083e-17";

    else if (number < 0.00001 and number > -0.00001 and m_energy == 1400 and m_background)
        return "0.0";

    else if (number < 0.00001 and number > -0.00001 and m_energy == 3000)
        return "0.0";

    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
