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

Fit::Fit(std::string descriptor, int nBins, std::string inputPath) : 
    m_descriptor(descriptor),
    m_nBins(nBins),
    m_inputPath(inputPath),
    m_alpha4(0.0),
    m_alpha5(0.0),
    m_chi2CosThetaStarWSynJets_vs_Bosons(0.0),
    m_chi2CosThetaStarZSynJets_vs_Bosons(0.0),
    m_chi2CosThetaStarWSynJets(0.0),
    m_chi2CosThetaStarZSynJets(0.0),
    m_chi2CosThetaStarWSynBosons(0.0),
    m_chi2CosThetaStarZSynBosons(0.0),
    m_rootFileName(descriptor + "_FitData.root")
{
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
    m_pTTree->Branch("Chi2CosThetaStarWSynJets_vs_Bosons", &m_chi2CosThetaStarWSynJets_vs_Bosons, "Chi2CosThetaStarWSynJets_vs_Bosons/D");
    m_pTTree->Branch("Chi2CosThetaStarZSynJets_vs_Bosons", &m_chi2CosThetaStarZSynJets_vs_Bosons, "Chi2CosThetaStarZSynJets_vs_Bosons/D");
    m_pTTree->Branch("Chi2CosThetaStarWSynJets", &m_chi2CosThetaStarWSynJets, "Chi2CosThetaStarWSynJets/D");
    m_pTTree->Branch("Chi2CosThetaStarZSynJets", &m_chi2CosThetaStarZSynJets, "Chi2CosThetaStarZSynJets/D");
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

void Fit::Merge()
{
    double alpha4Min(-0.02);
    double alpha4Max(0.0205);
    double alpha4Step(0.001);
    double alpha5Min(-0.02);
    double alpha5Max(0.0205);
    double alpha5Step(0.001);

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

            m_chi2CosThetaStarWSynJets = this->CalculateChi2In1D(m_cosThetaStarWSynJets, m_cosThetaStarWSynJetsRef);
            m_chi2CosThetaStarZSynJets = this->CalculateChi2In1D(m_cosThetaStarZSynJets, m_cosThetaStarZSynJetsRef);
            m_chi2CosThetaStarWSynBosons = this->CalculateChi2In1D(m_cosThetaStarWSynBosons, m_cosThetaStarWSynBosonsRef);
            m_chi2CosThetaStarZSynBosons = this->CalculateChi2In1D(m_cosThetaStarZSynBosons, m_cosThetaStarZSynBosonsRef);
            m_chi2CosThetaStarWSynJets_vs_Bosons = this->CalculateChi2In2D(m_cosThetaStarWSynJets_vs_Bosons, m_cosThetaStarWSynJets_vs_BosonsRef);
            m_chi2CosThetaStarZSynJets_vs_Bosons = this->CalculateChi2In2D(m_cosThetaStarZSynJets_vs_Bosons, m_cosThetaStarZSynJets_vs_BosonsRef);
            m_alpha4 = alpha4;
            m_alpha5 = alpha5;
            m_pTTree->Fill();

            std::string title_CosThetaStarSynWJets_vs_CosThetaStarSynWBosons = "Chi2_CosThetaStarSynWJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarWSynJets_vs_Bosons->SetTitle(title_CosThetaStarSynWJets_vs_CosThetaStarSynWBosons.c_str());
            m_cosThetaStarWSynJets_vs_Bosons->SetName(title_CosThetaStarSynWJets_vs_CosThetaStarSynWBosons.c_str());
            m_cosThetaStarWSynJets_vs_Bosons->Write();

            std::string title_CosThetaStarSynZJets_vs_CosThetaStarSynZBosons = "Chi2_CosThetaStarSynZJets_vs_Bosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarZSynJets_vs_Bosons->SetTitle(title_CosThetaStarSynZJets_vs_CosThetaStarSynZBosons.c_str());
            m_cosThetaStarZSynJets_vs_Bosons->SetName(title_CosThetaStarSynZJets_vs_CosThetaStarSynZBosons.c_str());
            m_cosThetaStarZSynJets_vs_Bosons->Write();

            std::string title_CosThetaStarSynWJets = "Chi2_CosThetaStarSynWJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarWSynJets->SetTitle(title_CosThetaStarSynWJets.c_str());
            m_cosThetaStarWSynJets->SetName(title_CosThetaStarSynWJets.c_str());
            m_cosThetaStarWSynJets->Write();

            std::string title_CosThetaStarSynZJets = "Chi2_CosThetaStarSynZJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarZSynJets->SetTitle(title_CosThetaStarSynZJets.c_str());
            m_cosThetaStarZSynJets->SetName(title_CosThetaStarSynZJets.c_str());
            m_cosThetaStarZSynJets->Write();

            std::string title_CosThetaStarSynWBosons = "Chi2_CosThetaStarSynWBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarWSynBosons->SetTitle(title_CosThetaStarSynWBosons.c_str());
            m_cosThetaStarWSynBosons->SetName(title_CosThetaStarSynWBosons.c_str());
            m_cosThetaStarWSynBosons->Write();

            std::string title_CosThetaStarSynZBosons = "Chi2_CosThetaStarSynZBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_cosThetaStarZSynBosons->SetTitle(title_CosThetaStarSynZBosons.c_str());
            m_cosThetaStarZSynBosons->SetName(title_CosThetaStarSynZBosons.c_str());
            m_cosThetaStarZSynBosons->Write();
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

            if (!file->IsDirectory() and fileCandidate.EndsWith("root") and fileCandidate.Contains(m_descriptor.c_str())) 
            {
                std::string filePath = m_inputPath + fileCandidate.Data();
                m_filesToReadIn.push_back(filePath);
            }
        }
    }
}

//=====================================================================

void Fit::InitialiseReference()
{
    m_cosThetaStarWSynJets_vs_BosonsRef = new TH2F(this->SafeName("CosThetaStarSynWJets_vs_BosonsRef"),"Reference Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarWSynJets_vs_BosonsRef->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
    m_cosThetaStarWSynJets_vs_BosonsRef->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    m_cosThetaStarZSynJets_vs_BosonsRef = new TH2F(this->SafeName("CosThetaStarSynZJets_vs_BosonsRef"),"Reference Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarZSynJets_vs_BosonsRef->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
    m_cosThetaStarZSynJets_vs_BosonsRef->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    m_cosThetaStarWSynJetsRef = new TH1F(this->SafeName("CosThetaStarSynWJetsRef"),"Reference Cos#theta_{WJets}^{*}",m_nBins,0,1);
    m_cosThetaStarWSynJetsRef->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
    m_cosThetaStarWSynJetsRef->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarZSynJetsRef = new TH1F(this->SafeName("CosThetaStarSynZJetsRef"),"Reference Cos#theta_{ZJets}^{*}",m_nBins,0,1);
    m_cosThetaStarZSynJetsRef->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
    m_cosThetaStarZSynJetsRef->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarWSynBosonsRef = new TH1F(this->SafeName("CosThetaStarSynWBosonsRef"),"Reference Cos#theta_{WBosons}^{*}",m_nBins,0,1);
    m_cosThetaStarWSynBosonsRef->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    m_cosThetaStarWSynBosonsRef->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarZSynBosonsRef = new TH1F(this->SafeName("CosThetaStarSynZBosonsRef"),"Reference Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
    m_cosThetaStarZSynBosonsRef->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    m_cosThetaStarZSynBosonsRef->GetYaxis()->SetTitle("Entries");
}

//=====================================================================

void Fit::Initialise()
{
    m_cosThetaStarWSynJets_vs_Bosons = new TH2F(this->SafeName("CosThetaStarSynWJets_vs_Bosons"),"Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarWSynJets_vs_Bosons->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
    m_cosThetaStarWSynJets_vs_Bosons->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    m_cosThetaStarZSynJets_vs_Bosons = new TH2F(this->SafeName("CosThetaStarSynZJets_vs_Bosons"),"Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
    m_cosThetaStarZSynJets_vs_Bosons->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
    m_cosThetaStarZSynJets_vs_Bosons->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    m_cosThetaStarWSynJets = new TH1F(this->SafeName("CosThetaStarSynWJets"),"Cos#theta_{WJets}^{*}",m_nBins,0,1);
    m_cosThetaStarWSynJets->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
    m_cosThetaStarWSynJets->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarZSynJets = new TH1F(this->SafeName("CosThetaStarSynZJets"),"Cos#theta_{ZJets}^{*}",m_nBins,0,1);
    m_cosThetaStarZSynJets->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
    m_cosThetaStarZSynJets->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarWSynBosons = new TH1F(this->SafeName("CosThetaStarSynWBosons"),"Cos#theta_{WBosons}^{*}",m_nBins,0,1);
    m_cosThetaStarWSynBosons->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    m_cosThetaStarWSynBosons->GetYaxis()->SetTitle("Entries");
    m_cosThetaStarZSynBosons = new TH1F(this->SafeName("CosThetaStarSynZBosons"),"Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
    m_cosThetaStarZSynBosons->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    m_cosThetaStarZSynBosons->GetYaxis()->SetTitle("Entries");
}

//=====================================================================

void Fit::MergeFiles(float alpha4, float alpha5, bool reference)
{
    for (const auto &fileName: m_filesToReadIn)
    {
        TFile *pTFile = new TFile(fileName.c_str());
        std::string plotName1("Chi2_CosThetaStarSynWJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
        TH1F *pTH1F_CosThetaStarSynWJets = (TH1F*)pTFile->Get(plotName1.c_str());
        std::string plotName2("Chi2_CosThetaStarSynZJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
        TH1F *pTH1F_CosThetaStarSynZJets = (TH1F*)pTFile->Get(plotName2.c_str());
        std::string plotName3("Chi2_CosThetaStarSynWBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
        TH1F *pTH1F_CosThetaStarSynWBosons = (TH1F*)pTFile->Get(plotName3.c_str());
        std::string plotName4("Chi2_CosThetaStarSynZBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
        TH1F *pTH1F_CosThetaStarSynZBosons = (TH1F*)pTFile->Get(plotName4.c_str());
        std::string plotName5("Chi2_CosThetaStarSynWJets_vs_CosThetaStarSynWBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
        TH2F *pTH2F_CosThetaStarWSynJets_vs_Bosons = (TH2F*)pTFile->Get(plotName5.c_str());
        std::string plotName6("Chi2_CosThetaStarSynZJets_vs_CosThetaStarSynZBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5));
        TH2F *pTH2F_CosThetaStarZSynJets_vs_Bosons = (TH2F*)pTFile->Get(plotName6.c_str());

        if (!reference)
        {
            m_cosThetaStarWSynJets->Add(pTH1F_CosThetaStarSynWJets);
            m_cosThetaStarZSynJets->Add(pTH1F_CosThetaStarSynZJets);
            m_cosThetaStarWSynBosons->Add(pTH1F_CosThetaStarSynWBosons);
            m_cosThetaStarZSynBosons->Add(pTH1F_CosThetaStarSynZBosons);
            m_cosThetaStarWSynJets_vs_Bosons->Add(pTH2F_CosThetaStarWSynJets_vs_Bosons);
            m_cosThetaStarZSynJets_vs_Bosons->Add(pTH2F_CosThetaStarZSynJets_vs_Bosons);
        }
        else
        {
            m_cosThetaStarWSynJetsRef->Add(pTH1F_CosThetaStarSynWJets);
            m_cosThetaStarZSynJetsRef->Add(pTH1F_CosThetaStarSynZJets);
            m_cosThetaStarWSynBosonsRef->Add(pTH1F_CosThetaStarSynWBosons);
            m_cosThetaStarZSynBosonsRef->Add(pTH1F_CosThetaStarSynZBosons);
            m_cosThetaStarWSynJets_vs_BosonsRef->Add(pTH2F_CosThetaStarWSynJets_vs_Bosons);
            m_cosThetaStarZSynJets_vs_BosonsRef->Add(pTH2F_CosThetaStarZSynJets_vs_Bosons);
        }
        delete pTFile, pTH1F_CosThetaStarSynWJets, pTH1F_CosThetaStarSynZJets, pTH1F_CosThetaStarSynWBosons ,pTH1F_CosThetaStarSynZBosons, pTH2F_CosThetaStarWSynJets_vs_Bosons, pTH2F_CosThetaStarZSynJets_vs_Bosons;
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
    delete m_cosThetaStarWSynJets, m_cosThetaStarWSynBosons, m_cosThetaStarWSynJets_vs_Bosons, m_cosThetaStarZSynJets, m_cosThetaStarZSynBosons, m_cosThetaStarZSynJets_vs_Bosons;
    delete m_cosThetaStarWSynJetsRef, m_cosThetaStarWSynBosonsRef, m_cosThetaStarWSynJets_vs_BosonsRef, m_cosThetaStarZSynJetsRef, m_cosThetaStarZSynBosonsRef, m_cosThetaStarZSynJets_vs_BosonsRef;
}

//=====================================================================

double Fit::CalculateChi2In1D(TH1F *pTH1F, TH1F *pTH1FRef)
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

//=====================================================================

double Fit::CalculateChi2In2D(TH2F *pTH2F, TH2F *pTH2FRef)
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
