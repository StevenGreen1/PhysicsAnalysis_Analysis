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

Fit::Fit(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis, std::string descriptor) : 
    m_processVector(processVector),
    m_pPostMVASelection(pCouplingAnalysis->GetPostMVASelection()),
    m_pCouplingAnalysis(pCouplingAnalysis),
    m_descriptor(descriptor),
    m_wBosonMass(80.385f),
    m_zBosonMass(91.1876f),
    m_alpha4(0.0),
    m_alpha5(0.0),
    m_chi2_CTSWJets_vs_CTSWBosons(0.0),
    m_chi2_CTSZJets_vs_CTSZBosons(0.0),
    m_chi2_CTSWJets(0.0),
    m_chi2_CTSZJets(0.0),
    m_chi2_CTSWBosons(0.0),
    m_chi2_CTSZBosons(0.0),
    m_nBins(10),
    m_nEvents(10000),
    m_option(0),
    m_rootFileName(descriptor + "FitData.root")
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
    m_pTTree->Branch("chi2_CTSWJets_vs_CTSWBosons", &m_chi2_CTSWJets_vs_CTSWBosons, "chi2_CTSWJets_vs_CTSWBosons/D");
    m_pTTree->Branch("chi2_CTSZJets_vs_CTSZBosons", &m_chi2_CTSZJets_vs_CTSZBosons, "chi2_CTSZJets_vs_CTSZBosons/D");
    m_pTTree->Branch("chi2_CTSWJets", &m_chi2_CTSWJets, "chi2_CTSWJets/D");
    m_pTTree->Branch("chi2_CTSZJets", &m_chi2_CTSZJets, "chi2_CTSZJets/D");
    m_pTTree->Branch("chi2_CTSWBosons", &m_chi2_CTSWBosons, "chi2_CTSWBosons/D");
    m_pTTree->Branch("chi2_CTSZBosons", &m_chi2_CTSZBosons, "chi2_CTSZBosons/D");
    m_pTTree->Branch("alpha4", &m_alpha4, "alpha4/D");
    m_pTTree->Branch("alpha5", &m_alpha5, "alpha5/D");

//    m_option = 1; // CTSWJets vs CTSWBosons
//    this->MinuitFit();
//    this->MyFit();
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

void Fit::SetNBins(const int &nBins)
{
    m_nBins = nBins;
}

//=====================================================================

void Fit::SetNEvents(const int &nEvents)
{
    m_nEvents = nEvents;
}

//=====================================================================

void Fit::SetOption(const int &option)
{
    m_option = option;
}

//=====================================================================

void Fit::MinuitFit()
{
    ROOT::Math::Minimizer *pMinimiser = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

    pMinimiser->SetMaxFunctionCalls(10000000);
    pMinimiser->SetTolerance(1E-4);
    pMinimiser->SetPrintLevel(1);

    ROOT::Math::Functor likelihoodFunctor(this, &Fit::Chi2, 2);
    pMinimiser->SetFunction(likelihoodFunctor);

    double step[2] = {0.0001, 0.0001};
    double variable[2] = {0.0, 0.0};
    pMinimiser->SetLimitedVariable(0, "alpha4", variable[0], step[0], -0.03, 0.03);
    pMinimiser->SetLimitedVariable(1, "alpha5", variable[1], step[1], -0.03, 0.03);
    pMinimiser->Minimize();

    // ------------------------------------
    // | Confidence Limits % | Delta Chi2 |
    // ------------------------------------
    // |         68        % |    2.28    |
    // |         90        % |    4.61    |
    // |         95        % |    5.99    |
    // |         99        % |    9.21    |

    unsigned int numPoints(100);

    double alpha4_c1[numPoints];
    double alpha5_c1[numPoints];
    pMinimiser->SetErrorDef(2.28);
    pMinimiser->Contour(0, 1, numPoints, &alpha4_c1[0], &alpha5_c1[0]);

    double alpha4_c2[numPoints];
    double alpha5_c2[numPoints];
    pMinimiser->SetErrorDef(4.61); 
    pMinimiser->Contour(0, 1, numPoints, &alpha4_c2[0], &alpha5_c2[0]);

    TCanvas *pTCanvas = new TCanvas("Dummy", "Dummy");
    TLegend *pTLegend = new TLegend(0.15, 0.15, 0.55, 0.35);
    TGraph *pTGraph_c1 = new TGraph(numPoints, alpha4_c1, alpha5_c1);
    pTGraph_c1->SetName("68PercentCL");
    TGraph *pTGraph_c2 = new TGraph(numPoints, alpha4_c2, alpha5_c2);
    pTGraph_c2->SetName("90PercentCL");

    pTGraph_c2->Draw("acf");
    pTGraph_c2->SetLineColor(kBlue);
    pTGraph_c2->SetFillColor(kBlue);
    pTGraph_c2->SetFillStyle(3001);
    TH1F *pTH1F_c2 = new TH1F();
    pTH1F_c2->SetLineColor(kBlue);
    pTH1F_c2->SetFillStyle(3001);
    pTLegend->AddEntry(pTH1F_c2, "90\% Confidence Contour","f");

    pTGraph_c1->Draw("cf");
    pTGraph_c1->SetLineColor(kRed);
    pTGraph_c1->SetFillColor(kRed);
    pTGraph_c1->SetFillStyle(3001);
    pTGraph_c1->GetXaxis()->SetTitle("#alpha_{4}");
    pTGraph_c1->GetYaxis()->SetTitle("#alpha_{5}");
    TH1F *pTH1F_c1 = new TH1F();
    pTH1F_c1->SetLineColor(kRed);
    pTH1F_c1->SetFillStyle(3001);
    pTLegend->AddEntry(pTH1F_c1, "68\% Confidence Contour","f");
    pTLegend->Draw("same");
    pTCanvas->Update();

    std::string plotNameDotC(m_descriptor + "_Contour.C");
    std::string plotNamePng(m_descriptor + "_Contour.png");

    pTCanvas->SaveAs(plotNameDotC.c_str());
    pTCanvas->SaveAs(plotNamePng.c_str());

    m_pTFile->cd();
    pTGraph_c1->Write();
    pTGraph_c2->Write();
    pTCanvas->Write();

    delete pTCanvas, pTLegend, pTGraph_c1, pTGraph_c2, pTH1F_c1, pTH1F_c2;
}

//=====================================================================

void Fit::MyFit()
{
    double alpha4Min(-0.02);
    double alpha4Max(0.021);
//    double alpha4Step(0.000625);
    double alpha4Step(0.002);
    double alpha5Min(-0.02);
    double alpha5Max(0.021);
//    double alpha5Step(0.000625);
    double alpha5Step(0.002);

    for (double alpha4 = alpha4Min; alpha4 < alpha4Max; alpha4 = alpha4 + alpha4Step)
    {
        for (double alpha5 = alpha5Min; alpha5 < alpha5Max; alpha5 = alpha5 + alpha5Step)
        {
            this->Initialise();
            this->FillDistribution(alpha4, alpha5);

            m_chi2_CTSWJets_vs_CTSWBosons = this->CalculateChi2In2D(m_pTH2F_CTSWJets_vs_CTSWBosons, m_pTH2F_CTSWJets_vs_CTSWBosonsRef);
            m_chi2_CTSZJets_vs_CTSZBosons = this->CalculateChi2In2D(m_pTH2F_CTSZJets_vs_CTSZBosons, m_pTH2F_CTSZJets_vs_CTSZBosonsRef);
            m_chi2_CTSWJets = this->CalculateChi2In1D(m_pTH1F_CTSWJets, m_pTH1F_CTSWJetsRef);
            m_chi2_CTSZJets = this->CalculateChi2In1D(m_pTH1F_CTSZJets, m_pTH1F_CTSZJetsRef);
            m_chi2_CTSWBosons = this->CalculateChi2In1D(m_pTH1F_CTSWBosons, m_pTH1F_CTSWBosonsRef);
            m_chi2_CTSZBosons = this->CalculateChi2In1D(m_pTH1F_CTSZBosons, m_pTH1F_CTSZBosonsRef);
            m_alpha4 = alpha4;
            m_alpha5 = alpha5;
            m_pTTree->Fill();

            std::string title_CTSWJets_vs_CTSWBosons = "Chi2_CTSWJets_vs_CTSWBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_pTH2F_CTSWJets_vs_CTSWBosons->SetTitle(title_CTSWJets_vs_CTSWBosons.c_str());
            m_pTH2F_CTSWJets_vs_CTSWBosons->SetName(title_CTSWJets_vs_CTSWBosons.c_str());
            m_pTH2F_CTSWJets_vs_CTSWBosons->Write();

            std::string title_CTSZJets_vs_CTSZBosons = "Chi2_CTSZJets_vs_CTSZBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_pTH2F_CTSZJets_vs_CTSZBosons->SetTitle(title_CTSZJets_vs_CTSZBosons.c_str());
            m_pTH2F_CTSZJets_vs_CTSZBosons->SetName(title_CTSZJets_vs_CTSZBosons.c_str());
            m_pTH2F_CTSZJets_vs_CTSZBosons->Write();

            std::string title_CTSWJets = "Chi2_CTSWJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_pTH1F_CTSWJets->SetTitle(title_CTSWJets.c_str());
            m_pTH1F_CTSWJets->SetName(title_CTSWJets.c_str());
            m_pTH1F_CTSWJets->Write();

            std::string title_CTSZJets = "Chi2_CTSZJets_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_pTH1F_CTSZJets->SetTitle(title_CTSZJets.c_str());
            m_pTH1F_CTSZJets->SetName(title_CTSZJets.c_str());
            m_pTH1F_CTSZJets->Write();

            std::string title_CTSWBosons = "Chi2_CTSWBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_pTH1F_CTSWBosons->SetTitle(title_CTSWBosons.c_str());
            m_pTH1F_CTSWBosons->SetName(title_CTSWBosons.c_str());
            m_pTH1F_CTSWBosons->Write();

            std::string title_CTSZBosons = "Chi2_CTSZBosons_Alpha4_"  + this->NumberToString(alpha4) + "_Alpha5_" + this->NumberToString(alpha5);
            m_pTH1F_CTSZBosons->SetTitle(title_CTSZBosons.c_str());
            m_pTH1F_CTSZBosons->SetName(title_CTSZBosons.c_str());
            m_pTH1F_CTSZBosons->Write();
        }
    }
}

//=====================================================================

double Fit::Chi2(const double *par)
{
    if (m_option == 1)
        return this->Chi2_CTSWJets_vs_CTSWBosons(par);
    else if (m_option == 2)
        return this->Chi2_CTSZJets_vs_CTSZBosons(par);
    else if (m_option == 3)
        return this->Chi2_CTSWJets(par);
    else if (m_option == 4)
        return this->Chi2_CTSZJets(par);
    else if (m_option == 5)
        return this->Chi2_CTSWBosons(par);
    else if (m_option == 6)
        return this->Chi2_CTSZBosons(par);
    else
        return 0.0;
}

//=====================================================================

double Fit::Chi2_CTSWJets_vs_CTSWBosons(const double *par)
{
    this->Initialise();
    this->FillDistribution(par[0], par[1]);
    double chi2(this->CalculateChi2In2D(m_pTH2F_CTSWJets_vs_CTSWBosons, m_pTH2F_CTSWJets_vs_CTSWBosonsRef));
    m_alpha4 = par[0];
    m_alpha5 = par[1];
    m_chi2_CTSWJets_vs_CTSWBosons = chi2;
    m_pTTree->Fill();
    return chi2;
}

//=====================================================================

double Fit::Chi2_CTSZJets_vs_CTSZBosons(const double *par)
{
    this->Initialise();
    this->FillDistribution(par[0], par[1]);
    double chi2(this->CalculateChi2In2D(m_pTH2F_CTSZJets_vs_CTSZBosons, m_pTH2F_CTSZJets_vs_CTSZBosonsRef));
    m_alpha4 = par[0];
    m_alpha5 = par[1];
    m_chi2_CTSZJets_vs_CTSZBosons = chi2;
    m_pTTree->Fill();
    return chi2;
}

//=====================================================================

double Fit::Chi2_CTSWJets(const double *par)
{
    this->Initialise();
    this->FillDistribution(par[0], par[1]);
    double chi2(this->CalculateChi2In1D(m_pTH1F_CTSWJets, m_pTH1F_CTSWJetsRef));
    m_alpha4 = par[0];
    m_alpha5 = par[1];
    m_chi2_CTSWJets = chi2;
    m_pTTree->Fill();
    return chi2;
}

//=====================================================================

double Fit::Chi2_CTSZJets(const double *par)
{
    this->Initialise();
    this->FillDistribution(par[0], par[1]);
    double chi2(this->CalculateChi2In1D(m_pTH1F_CTSZJets, m_pTH1F_CTSZJetsRef));
    m_alpha4 = par[0];
    m_alpha5 = par[1];
    m_chi2_CTSZJets = chi2;
    m_pTTree->Fill();
    return chi2;
}

//=====================================================================

double Fit::Chi2_CTSWBosons(const double *par)
{
    this->Initialise();
    this->FillDistribution(par[0], par[1]);
    double chi2(this->CalculateChi2In1D(m_pTH1F_CTSWBosons, m_pTH1F_CTSWBosonsRef));
    m_alpha4 = par[0];
    m_alpha5 = par[1];
    m_chi2_CTSWBosons = chi2;
    m_pTTree->Fill();
    return chi2;
}

//=====================================================================

double Fit::Chi2_CTSZBosons(const double *par)
{
    this->Initialise();
    this->FillDistribution(par[0], par[1]);
    double chi2(this->CalculateChi2In1D(m_pTH1F_CTSZBosons, m_pTH1F_CTSZBosonsRef));
    m_alpha4 = par[0];
    m_alpha5 = par[1];
    m_chi2_CTSZBosons = chi2;
    m_pTTree->Fill();
    return chi2;
}

//=====================================================================

void Fit::Initialise()
{
    if (m_option == 1)
    {
        m_pTH2F_CTSWJets_vs_CTSWBosonsRef = new TH2F(this->SafeName("CTSWJets_vs_CTSWBosonsRef"),"Reference Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_pTH2F_CTSWJets_vs_CTSWBosonsRef->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_pTH2F_CTSWJets_vs_CTSWBosonsRef->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_pTH2F_CTSWJets_vs_CTSWBosons = new TH2F(this->SafeName("CTSWJets_vs_CTSWBosons"),"Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_pTH2F_CTSWJets_vs_CTSWBosons->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_pTH2F_CTSWJets_vs_CTSWBosons->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
    }
    else if (m_option == 2)
    {
        m_pTH2F_CTSZJets_vs_CTSZBosonsRef = new TH2F(this->SafeName("CTSZJets_vs_CTSZBosonsRef"),"Reference Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_pTH2F_CTSZJets_vs_CTSZBosonsRef->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_pTH2F_CTSZJets_vs_CTSZBosonsRef->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_pTH2F_CTSZJets_vs_CTSZBosons = new TH2F(this->SafeName("CTSZJets_vs_CTSZBosons"),"Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_pTH2F_CTSZJets_vs_CTSZBosons->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_pTH2F_CTSZJets_vs_CTSZBosons->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
    }
    else if (m_option == 3)
    {
        m_pTH1F_CTSWJetsRef = new TH1F(this->SafeName("CTSWJetsRef"),"Reference Cos#theta_{WJets}^{*}",m_nBins,0,1);
        m_pTH1F_CTSWJetsRef->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_pTH1F_CTSWJetsRef->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSWJets = new TH1F(this->SafeName("CTSWJets"),"Cos#theta_{WJets}^{*}",m_nBins,0,1);
        m_pTH1F_CTSWJets->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_pTH1F_CTSWJets->GetYaxis()->SetTitle("Entries");
    }
    else if (m_option == 4)
    {
        m_pTH1F_CTSZJetsRef = new TH1F(this->SafeName("CTSZJetsRef"),"Reference Cos#theta_{ZJets}^{*}",m_nBins,0,1);
        m_pTH1F_CTSZJetsRef->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_pTH1F_CTSZJetsRef->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSZJets = new TH1F(this->SafeName("CTSZJets"),"Cos#theta_{ZJets}^{*}",m_nBins,0,1);
        m_pTH1F_CTSZJets->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_pTH1F_CTSZJets->GetYaxis()->SetTitle("Entries");
    }
    else if (m_option == 5)
    {
        m_pTH1F_CTSWBosonsRef = new TH1F(this->SafeName("CTSWBosonsRef"),"Reference Cos#theta_{WBosons}^{*}",m_nBins,0,1);
        m_pTH1F_CTSWBosonsRef->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_pTH1F_CTSWBosonsRef->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSWBosons = new TH1F(this->SafeName("CTSWBosons"),"Cos#theta_{WBosons}^{*}",m_nBins,0,1);
        m_pTH1F_CTSWBosons->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_pTH1F_CTSWBosons->GetYaxis()->SetTitle("Entries");
    }
    else if (m_option == 6)
    {
        m_pTH1F_CTSZBosonsRef = new TH1F(this->SafeName("CTSZBosonsRef"),"Reference Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
        m_pTH1F_CTSZBosonsRef->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_pTH1F_CTSZBosonsRef->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSZBosons = new TH1F(this->SafeName("CTSZBosons"),"Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
        m_pTH1F_CTSZBosons->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_pTH1F_CTSZBosons->GetYaxis()->SetTitle("Entries");
    }
    else
    {
        m_pTH2F_CTSWJets_vs_CTSWBosonsRef = new TH2F(this->SafeName("CTSWJets_vs_CTSWBosonsRef"),"Reference Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_pTH2F_CTSWJets_vs_CTSWBosonsRef->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_pTH2F_CTSWJets_vs_CTSWBosonsRef->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_pTH2F_CTSWJets_vs_CTSWBosons = new TH2F(this->SafeName("CTSWJets_vs_CTSWBosons"),"Cos#theta_{WJets}^{*} vs Cos#theta_{WBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_pTH2F_CTSWJets_vs_CTSWBosons->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_pTH2F_CTSWJets_vs_CTSWBosons->GetYaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_pTH2F_CTSZJets_vs_CTSZBosonsRef = new TH2F(this->SafeName("CTSZJets_vs_CTSZBosonsRef"),"Reference Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_pTH2F_CTSZJets_vs_CTSZBosonsRef->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_pTH2F_CTSZJets_vs_CTSZBosonsRef->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_pTH2F_CTSZJets_vs_CTSZBosons = new TH2F(this->SafeName("CTSZJets_vs_CTSZBosons"),"Cos#theta_{ZJets}^{*} vs Cos#theta_{ZBosons}^{*}",m_nBins,0,1,m_nBins,0,1);
        m_pTH2F_CTSZJets_vs_CTSZBosons->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_pTH2F_CTSZJets_vs_CTSZBosons->GetYaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_pTH1F_CTSWJetsRef = new TH1F(this->SafeName("CTSWJetsRef"),"Reference Cos#theta_{WJets}^{*}",m_nBins,0,1);
        m_pTH1F_CTSWJetsRef->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_pTH1F_CTSWJetsRef->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSWJets = new TH1F(this->SafeName("CTSWJets"),"Cos#theta_{WJets}^{*}",m_nBins,0,1);
        m_pTH1F_CTSWJets->GetXaxis()->SetTitle("Cos#theta_{WJets}^{*}");
        m_pTH1F_CTSWJets->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSZJetsRef = new TH1F(this->SafeName("CTSZJetsRef"),"Reference Cos#theta_{ZJets}^{*}",m_nBins,0,1);
        m_pTH1F_CTSZJetsRef->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_pTH1F_CTSZJetsRef->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSZJets = new TH1F(this->SafeName("CTSZJets"),"Cos#theta_{ZJets}^{*}",m_nBins,0,1);
        m_pTH1F_CTSZJets->GetXaxis()->SetTitle("Cos#theta_{ZJets}^{*}");
        m_pTH1F_CTSZJets->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSWBosonsRef = new TH1F(this->SafeName("CTSWBosonsRef"),"Reference Cos#theta_{WBosons}^{*}",m_nBins,0,1);
        m_pTH1F_CTSWBosonsRef->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_pTH1F_CTSWBosonsRef->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSWBosons = new TH1F(this->SafeName("CTSWBosons"),"Cos#theta_{WBosons}^{*}",m_nBins,0,1);
        m_pTH1F_CTSWBosons->GetXaxis()->SetTitle("Cos#theta_{WBosons}^{*}");
        m_pTH1F_CTSWBosons->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSZBosonsRef = new TH1F(this->SafeName("CTSZBosonsRef"),"Reference Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
        m_pTH1F_CTSZBosonsRef->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_pTH1F_CTSZBosonsRef->GetYaxis()->SetTitle("Entries");
        m_pTH1F_CTSZBosons = new TH1F(this->SafeName("CTSZBosons"),"Cos#theta_{ZBosons}^{*}",m_nBins,0,1);
        m_pTH1F_CTSZBosons->GetXaxis()->SetTitle("Cos#theta_{ZBosons}^{*}");
        m_pTH1F_CTSZBosons->GetYaxis()->SetTitle("Entries");
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
    delete m_pTH1F_CTSWJetsRef, m_pTH1F_CTSWBosonsRef, m_pTH2F_CTSWJets_vs_CTSWBosonsRef, m_pTH1F_CTSZJetsRef, m_pTH1F_CTSZBosonsRef, m_pTH2F_CTSZJets_vs_CTSZBosonsRef;
}

//=====================================================================

void Fit::FillDistribution(const double alpha4, const double alpha5)
{
    for (const auto &pProcess: m_processVector)
    {
        double weight(pProcess->GetPostMVAProcessWeight());
        TChain *pTChain(pProcess->GetPostMVATChain());

        Int_t globalEventNumber(std::numeric_limits<int>::max());
        Int_t nIsolatedLeptons(std::numeric_limits<int>::max());
        Double_t transverseMomentum(std::numeric_limits<double>::max());
        Double_t invariantMassSystem(std::numeric_limits<double>::max());
        Double_t ctsWBoson(std::numeric_limits<double>::max());
        Double_t ctsWJet1(std::numeric_limits<double>::max());
        Double_t ctsWJet2(std::numeric_limits<double>::max());
        Double_t invMassWBoson1(std::numeric_limits<double>::max());
        Double_t invMassWBoson2(std::numeric_limits<double>::max());
        Double_t ctsZBoson(std::numeric_limits<double>::max());
        Double_t ctsZJet1(std::numeric_limits<double>::max());
        Double_t ctsZJet2(std::numeric_limits<double>::max());
        Double_t invMassZBoson1(std::numeric_limits<double>::max());
        Double_t invMassZBoson2(std::numeric_limits<double>::max());
        Double_t bdt(std::numeric_limits<double>::max());

        // Selection Variables
        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("BDT", &bdt);
        // W or Z Boson Selection
        pTChain->SetBranchAddress("InvMassWVector1", &invMassWBoson1);
        pTChain->SetBranchAddress("InvMassWVector2", &invMassWBoson2);
        pTChain->SetBranchAddress("InvMassZVector1", &invMassZBoson1);
        pTChain->SetBranchAddress("InvMassZVector2", &invMassZBoson2);

        if (m_option == 1 or m_option == 3)
        {
            pTChain->SetBranchAddress("CosThetaStarWJet1", &ctsWJet1);
            pTChain->SetBranchAddress("CosThetaStarWJet2", &ctsWJet2);
        }

        if (m_option == 2 or m_option == 4)
        {
            pTChain->SetBranchAddress("CosThetaStarZJet1", &ctsZJet1);
            pTChain->SetBranchAddress("CosThetaStarZJet2", &ctsZJet2);
        }

        if (m_option == 5 or m_option == 1)
        {
            pTChain->SetBranchAddress("CosThetaStarWBosons", &ctsWBoson);
        }

        if (m_option == 6 or m_option == 2)
        {
            pTChain->SetBranchAddress("CosThetaStarZBosons", &ctsZBoson);
        }

        if (m_option < 1 or m_option > 6)
        {
            pTChain->SetBranchAddress("CosThetaStarWJet1", &ctsWJet1);
            pTChain->SetBranchAddress("CosThetaStarWJet2", &ctsWJet2);
            pTChain->SetBranchAddress("CosThetaStarZJet1", &ctsZJet1);
            pTChain->SetBranchAddress("CosThetaStarZJet2", &ctsZJet2);
            pTChain->SetBranchAddress("CosThetaStarWBosons", &ctsWBoson);
            pTChain->SetBranchAddress("CosThetaStarZBosons", &ctsZBoson);
        }

        int nEventsToProcess(pTChain->GetEntries() > m_nEvents ? m_nEvents : pTChain->GetEntries());

        weight = weight * (float)(pTChain->GetEntries()) / (float)(nEventsToProcess);

        for (unsigned int event = 0; event < nEventsToProcess; event++)
        {
            pTChain->GetEntry(event);

            // Cuts
            if (bdt < m_pPostMVASelection->GetBDTLowCut() or m_pPostMVASelection->GetBDTHighCut() < bdt)
                continue;
            if (nIsolatedLeptons < m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsLowCut() or m_pPostMVASelection->GetPreSelection()->GetNumberOfIsolatedLeptonsHighCut() < nIsolatedLeptons)
                continue;
            if (transverseMomentum < m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumLowCut() or m_pPostMVASelection->GetPreSelection()->GetTransverseMomentumHighCut() < transverseMomentum)
                continue;
            if (invariantMassSystem < m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemLowCut() or m_pPostMVASelection->GetPreSelection()->GetInvariantMassSystemHighCut() < invariantMassSystem)
                continue;

            // W or Z Selection
            double rW = std::sqrt( (m_wBosonMass - invMassWBoson1) * (m_wBosonMass - invMassWBoson1) + (m_wBosonMass - invMassWBoson2) * (m_wBosonMass - invMassWBoson2) );
            double rZ = std::sqrt( (m_zBosonMass - invMassZBoson1) * (m_zBosonMass - invMassZBoson1) + (m_zBosonMass - invMassZBoson2) * (m_zBosonMass - invMassZBoson2) );

            bool isW(false);

            if (rZ > rW)
                isW = true;
            else
                isW = false;

            if (isW)
            {
                float matrixElementWeight(1.f); 
                if (pProcess->GetEventType() == "ee_nunuqqqq")
                {   
                    m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                }

                if (m_option == 1)
                {
                    m_pTH2F_CTSWJets_vs_CTSWBosonsRef->Fill(ctsWJet1, ctsWBoson, weight);
                    m_pTH2F_CTSWJets_vs_CTSWBosonsRef->Fill(ctsWJet2, ctsWBoson, weight);
                    m_pTH2F_CTSWJets_vs_CTSWBosons->Fill(ctsWJet1, ctsWBoson, weight*matrixElementWeight);
                    m_pTH2F_CTSWJets_vs_CTSWBosons->Fill(ctsWJet2, ctsWBoson, weight*matrixElementWeight);
                }
                else if (m_option == 3)
                {
                    m_pTH1F_CTSWJetsRef->Fill(ctsWJet1, weight);
                    m_pTH1F_CTSWJetsRef->Fill(ctsWJet2, weight);
                    m_pTH1F_CTSWJets->Fill(ctsWJet1, weight*matrixElementWeight);
                    m_pTH1F_CTSWJets->Fill(ctsWJet2, weight*matrixElementWeight);
                }
                else if (m_option == 5)
                {
                    m_pTH1F_CTSWBosonsRef->Fill(ctsWBoson, weight);
                    m_pTH1F_CTSWBosons->Fill(ctsWBoson, weight*matrixElementWeight);
                }
                else if (m_option < 1 or m_option > 6)
                {
                    m_pTH2F_CTSWJets_vs_CTSWBosonsRef->Fill(ctsWJet1, ctsWBoson, weight);
                    m_pTH2F_CTSWJets_vs_CTSWBosonsRef->Fill(ctsWJet2, ctsWBoson, weight);
                    m_pTH2F_CTSWJets_vs_CTSWBosons->Fill(ctsWJet1, ctsWBoson, weight*matrixElementWeight);
                    m_pTH2F_CTSWJets_vs_CTSWBosons->Fill(ctsWJet2, ctsWBoson, weight*matrixElementWeight);
                    m_pTH1F_CTSWJetsRef->Fill(ctsWJet1, weight);
                    m_pTH1F_CTSWJetsRef->Fill(ctsWJet2, weight);
                    m_pTH1F_CTSWJets->Fill(ctsWJet1, weight*matrixElementWeight);
                    m_pTH1F_CTSWJets->Fill(ctsWJet2, weight*matrixElementWeight);
                    m_pTH1F_CTSWBosonsRef->Fill(ctsWBoson, weight);
                    m_pTH1F_CTSWBosons->Fill(ctsWBoson, weight*matrixElementWeight);
                }
            }

            else
            {
                float matrixElementWeight(1.f);
                if (pProcess->GetEventType() == "ee_nunuqqqq")
                {
                    m_pCouplingAnalysis->GetWeight(globalEventNumber, alpha4, alpha5, matrixElementWeight);
                }

                if (m_option == 2)
                {  
                    m_pTH2F_CTSZJets_vs_CTSZBosonsRef->Fill(ctsZJet1, ctsZBoson, weight);
                    m_pTH2F_CTSZJets_vs_CTSZBosonsRef->Fill(ctsZJet2, ctsZBoson, weight);
                    m_pTH2F_CTSZJets_vs_CTSZBosons->Fill(ctsZJet1, ctsZBoson, weight*matrixElementWeight);
                    m_pTH2F_CTSZJets_vs_CTSZBosons->Fill(ctsZJet2, ctsZBoson, weight*matrixElementWeight);
                }
                else if (m_option == 4)
                {
                    m_pTH1F_CTSZJetsRef->Fill(ctsZJet1, weight);
                    m_pTH1F_CTSZJetsRef->Fill(ctsZJet2, weight);
                    m_pTH1F_CTSZJets->Fill(ctsZJet1, weight*matrixElementWeight);
                    m_pTH1F_CTSZJets->Fill(ctsZJet2, weight*matrixElementWeight);
                }
                else if (m_option == 6)
                {
                    m_pTH1F_CTSZBosonsRef->Fill(ctsZBoson, weight);
                    m_pTH1F_CTSZBosons->Fill(ctsZBoson, weight*matrixElementWeight);
                }
                else if (m_option < 1 or m_option > 6)
                {
                    m_pTH2F_CTSZJets_vs_CTSZBosonsRef->Fill(ctsZJet1, ctsZBoson, weight);
                    m_pTH2F_CTSZJets_vs_CTSZBosonsRef->Fill(ctsZJet2, ctsZBoson, weight);
                    m_pTH2F_CTSZJets_vs_CTSZBosons->Fill(ctsZJet1, ctsZBoson, weight*matrixElementWeight);
                    m_pTH2F_CTSZJets_vs_CTSZBosons->Fill(ctsZJet2, ctsZBoson, weight*matrixElementWeight);
                    m_pTH1F_CTSZJetsRef->Fill(ctsZJet1, weight);
                    m_pTH1F_CTSZJetsRef->Fill(ctsZJet2, weight);
                    m_pTH1F_CTSZJets->Fill(ctsZJet1, weight*matrixElementWeight);
                    m_pTH1F_CTSZJets->Fill(ctsZJet2, weight*matrixElementWeight);
                    m_pTH1F_CTSZBosonsRef->Fill(ctsZBoson, weight);
                    m_pTH1F_CTSZBosons->Fill(ctsZBoson, weight*matrixElementWeight);
                }
            }
        }
        delete pTChain;
    } 
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
