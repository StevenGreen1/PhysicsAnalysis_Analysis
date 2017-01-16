TGraph2D *SinglePlot(TString name);

//================================================================

void FinalPlot()
{
    TString name1 = "SPFOs_kt_0p90_Final_1400GeV_FitData.root";

    TCanvas *pTCanvas = new TCanvas("Canvas", "", 600, 600);
    pTCanvas->Divide(3,2);
    TGraph2D *pTGraph2D_a = SinglePlot(name1,"Chi2CosThetaStarSynJets_vs_Bosons");
    TGraph2D *pTGraph2D_b = SinglePlot(name1,"Chi2CosThetaStarSynJets");
    TGraph2D *pTGraph2D_c = SinglePlot(name1,"Chi2CosThetaStarSynBosons");

    TCanvas *pTCanvas_1 = new TCanvas("SPFOs_kt_0p90_Final", "", 600, 600);
    pTCanvas_1->SetRightMargin(0.05);
    pTCanvas_1->SetLeftMargin(0.15);
    pTCanvas_1->SetTopMargin(0.10);
    pTCanvas_1->SetBottomMargin(0.10);
    TH1F *pTH1FDummy1 = new TH1F();
    pTH1FDummy1->SetLineColor(2);
    TH1F *pTH1FDummy2 = new TH1F();
    pTH1FDummy2->SetLineColor(418);
    TH1F *pTH1FDummy3 = new TH1F();
    pTH1FDummy3->SetLineColor(4);

    TLine *pLineAlpha4High = new TLine(0.0093,-0.02,0.0093,0.02);
    pLineAlpha4High->SetLineColor(kBlack);
    pLineAlpha4High->SetLineStyle(2);
    pLineAlpha4High->SetLineWidth(2);

    TLine *pLineAlpha4Low = new TLine(-0.0071,-0.02,-0.0071,0.02);
    pLineAlpha4Low->SetLineColor(kBlack);
    pLineAlpha4Low->SetLineStyle(2);
    pLineAlpha4Low->SetLineWidth(2);

    TLine *pLineAlpha5High = new TLine(-0.02,0.0051,0.02,0.0051);
    pLineAlpha5High->SetLineColor(kBlack);
    pLineAlpha5High->SetLineStyle(2);
    pLineAlpha5High->SetLineWidth(2);

    TLine *pLineAlpha5Low = new TLine(-0.02,-0.006,0.02,-0.006);
    pLineAlpha5Low->SetLineColor(kBlack);
    pLineAlpha5Low->SetLineStyle(2);
    pLineAlpha5Low->SetLineWidth(2);

    gStyle->SetLegendBorderSize(1); 

    TLegend *pTLegend_all = new TLegend(0.2, 0.15, 0.6, 0.35);
    pTLegend_all->AddEntry(pTH1FDummy1,"68\% Confidence Contour", "l");
    pTLegend_all->AddEntry(pTH1FDummy2,"90\% Confidence Contour", "l");
    pTLegend_all->AddEntry(pTH1FDummy3,"99\% Confidence Contour", "l");
    pTLegend_all->SetLineWidth(2);
    pTLegend_all->SetLineColor(kBlack);
    pTLegend_all->SetFillColor(10);

    TCanvas *pTCanvas = new TCanvas("Canvas_Final", "", 600, 600);
    pTCanvas->SetRightMargin(0.05);
    pTCanvas->SetLeftMargin(0.15);
    pTCanvas->SetTopMargin(0.10);
    pTCanvas->SetBottomMargin(0.10);
    pTGraph2D_b->SetTitle("Longitudinally Invariant Kt, Selected PFOs, R = 0.9");
    pTGraph2D_b->SetLineWidth(3);
    pTGraph2D_b->Draw("CONT1");
    pLineAlpha4High->Draw();
    pLineAlpha4Low->Draw();
    pLineAlpha5High->Draw();
    pLineAlpha5Low->Draw();
    pTLegend_all->Draw();
    pTCanvas->Update();
    pTCanvas->SaveAs("Final.pdf");
    pTCanvas->SaveAs("Final.C");
}

//================================================================

TGraph2D *SinglePlot(TString name, TString quantity)
{
    TFile *pTFile = new TFile(name);
    TTree *pTTree = (TTree*)pTFile->Get("AnalysisProcessorTree");

    Double_t alpha4, alpha5, chi2;

    pTTree->SetBranchAddress("Alpha4",&alpha4);
    pTTree->SetBranchAddress("Alpha5",&alpha5);
    pTTree->SetBranchAddress(quantity,&chi2);

    TGraph2D *pTGraph2D = new TGraph2D(); 
    pTGraph2D->SetTitle(name + "_" + quantity);

    unsigned int nEntries = pTTree->GetEntries();
    for (unsigned int i = 0; i < nEntries; i++)
    {
        pTTree->GetEntry(i);
        pTGraph2D->SetPoint(pTGraph2D->GetN(), alpha4, alpha5, chi2);
    }

    Int_t colors[] = {0, 2, 418, 4, 1};
    gStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);
    Double_t levels[] = {0.0, 2.28, 4.61, 9.21, 1.79e308};
    pTGraph2D->GetHistogram()->SetContour((sizeof(levels)/sizeof(Double_t)), levels);

    pTGraph2D->GetXaxis()->SetTitleSize(0.05);
    pTGraph2D->GetXaxis()->SetLabelSize(0.035);
    pTGraph2D->GetXaxis()->SetTitle("#alpha_{4}");
    pTGraph2D->GetYaxis()->SetTitleOffset(1.6);
    pTGraph2D->GetYaxis()->SetTitleSize(0.05);
    pTGraph2D->GetYaxis()->SetLabelSize(0.035);
    pTGraph2D->GetYaxis()->SetTitle("#alpha_{5}");
    pTGraph2D->SetTitle("");

    return pTGraph2D;
}

