/**
  *  @file   AnalysisScripts/src/MakeSimplePlots.cc 
  * 
  *  @brief  Implementation of the make plots class.
  * 
  *  $Log: $
  */

#include "MakeSimplePlots.h"

//=====================================================================

MakeSimplePlots::MakeSimplePlots(const ProcessVector &processVector) :
    m_processVector(processVector)
{
    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);

        this->Register1DPlot(pProcess, "TransverseMomentum", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "MCTransverseMomentum", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "TransverseEnergy", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "MCTransverseEnergy", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "CosThetaMissing", "double", 200, -1.f, 1.f);
        this->Register1DPlot(pProcess, "MCCosThetaMissing", "double", 200, -1.f, 1.f);
        this->Register1DPlot(pProcess, "CosThetaMostEnergeticTrack", "double", 200, -1.f, 1.f);
        this->Register1DPlot(pProcess, "RecoilMass", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "MCRecoilMass", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "EnergyAroundMostEnergeticTrack", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "y12", "double", 100, 0.f, 10.f);
        this->Register1DPlot(pProcess, "y23", "double", 100, 0.f, 10.f);
        this->Register1DPlot(pProcess, "y34", "double", 100, 0.f, 10.f);
        this->Register1DPlot(pProcess, "y45", "double", 100, 0.f, 10.f);
        this->Register1DPlot(pProcess, "y56", "double", 100, 0.f, 10.f);
        this->Register1DPlot(pProcess, "y67", "double", 100, 0.f, 10.f);
        this->Register1DPlot(pProcess, "InvariantMassSystem", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "MCInvariantMassSystem", "double", 140, 0.f, 1400.f);
        this->Register1DPlot(pProcess, "CosThetaStarWBosons", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "MCCosThetaStarWBosons", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "CosThetaStarZBosons", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "MCCosThetaStarZBosons", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "AcolinearityBosonsW", "double", 90, 0.f, 180.f);
        this->Register1DPlot(pProcess, "AcolinearityBosonsZ", "double", 90, 0.f, 180.f);
        this->Register1DPlot(pProcess, "PrincipleThrustValue", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "MajorThrustValue", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "MinorThrustValue", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "XThrustAxis", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "YThrustAxis", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "ZThrustAxis", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "Sphericity", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "Aplanarity", "double", 100, 0.f, 1.f);
        this->Register1DPlot(pProcess, "NPFOs", "double", 100, 0.f, 100.f);



        this->Register2DPlot(pProcess, "InvMassWVector1", "InvMassWVector2", 100, 0.f, 500.f, 100, 0.f, 500.f);
        this->Register2DPlot(pProcess, "InvMassZVector1", "InvMassZVector2", 100, 0.f, 500.f, 100, 0.f, 500.f);
    }

    this->LoadData();
    this->WritePlots(); // Stacks and multi plots
//    this->WriteIndividualPlots(); <-- Makes too many plots really
}

//=====================================================================
/*
run             = 1
 event           = 1
 IsAppropriateEvent = 0
 IsEventWW       = 0
 IsMCEventWW     = 0
 IsEventZZ       = 0
 IsMCEventZZ     = 0
 NPfosBosonW1    = 34
 NPfosBosonW2    = 28
 NPfosBosonZ1    = 22
 NPfosBosonZ2    = 40
 WBosonJet1Is    = 0
 WBosonJet2Is    = 1
 WBosonJet3Is    = 2
 WBosonJet4Is    = 3
 ZBosonJet1Is    = 0
 ZBosonJet2Is    = 3
 ZBosonJet3Is    = 1
 ZBosonJet4Is    = 2
 NParticlesJet1  = 31
 NParticlesJet2  = 3
 NParticlesJet3  = 19
 NParticlesJet4  = 9
 NParticlesJet1  = 8
 NParticlesJet2  = 3
 NParticlesJet3  = 13
 NParticlesJet4  = 4
 TransverseMomentum = 213.034
 TransverseMomentumBosonW1 = 172.821
 TransverseMomentumBosonW2 = 40.213
 TransverseMomentumBosonZ1 = 60.8325
 TransverseMomentumBosonZ2 = 152.201
 MCTransverseMomentum = 1.79769e+308
 TransverseEnergy = 214.56
 TransverseEnergyBosonW1 = 173.678
 TransverseEnergyBosonW2 = 40.8817
 TransverseEnergyBosonZ1 = 61.422
 TransverseEnergyBosonZ2 = 153.138
 MCTransverseEnergy = 1.79769e+308
 CosThetaMissing = -0.753999
 MCCosThetaMissing = 1.79769e+308
 CosThetaMostEnergeticTrack = 0.926763
 RecoilMass      = 1063
 MCRecoilMass    = 1.79769e+308
 EnergyAroundMostEnergeticTrack = 0
 y12             = 0.378918
 y23             = 3.96335
 y34             = 2.26813
 y45             = 3.4356
 y56             = 3.66944
 y67             = 4.23
 InvariantMassSystem = 280.273
 MCInvariantMassSystem = 1.79769e+308
 CosThetaStarWBosons = 0.967515
 MCCosThetaStarWBosons = 1.79769e+308
 CosThetaStarZBosons = 0.589915
 MCCosThetaStarZBosons = 1.79769e+308
 AcolinearityJetsW1 = 87.5732
 AcolinearityJetsW2 = 21.7612
 AcolinearityJetsZ1 = 42.0506
 AcolinearityJetsZ2 = 42.0506
 AcolinearityBosonsW = 54.8702
 AcolinearityBosonsZ = 78.0565
 PrincipleThrustValue = 0.784348
 MajorThrustValue = 0.466748
 MinorThrustValue = 0.192834
 XThrustAxis     = -0.41102
 YThrustAxis     = -0.000395772
 ZThrustAxis     = 0.911626
 Sphericity      = 0.217747
 Aplanarity      = 0.0242223
 InvMassWVector1 = 176.929
 InvMassWVector2 = 76.1012
 MCInvMassWVector1 = 0
 MCInvMassWVector2 = 0
 InvMassZVector1 = 128.778
 InvMassZVector2 = 66.503
 MCInvMassZVector1 = 0
 MCInvMassZVector2 = 0
 EnergyJet1      = 135.582
 EnergyJet2      = 109.92
 EnergyJet3      = 43.5228
 EnergyJet4      = 34.3406
 CosThetaStarWJet1 = 0.141681
 CosThetaStarWJet2 = 0.488605
 CosThetaStarZJet1 = 0.812337
 CosThetaStarZJet2 = 0.627743
 BTagForJet1     = 0.989327
 BTagForJet2     = 0.0268879
 BTagForJet3     = 0.111148
 BTagForJet4     = 0.0961533
 CTagForJet1     = 0.00615293
 CTagForJet2     = 0.118742
 CTagForJet3     = 0.602369
 CTagForJet4     = 0.0939233

*/
//=====================================================================

void MakeSimplePlots::WritePlots()
{
    std::cout << "Begin: MakeSimplePlots::WritePlots" << std::endl;

    static const float redArray[] = {0.0, 0.00392156862745, 0.835294117647, 1.0, 0.619607843137, 0.0549019607843, 1.0, 0.0, 0.0, 0.58431372549, 1.0, 0.643137254902, 0.0, 0.56862745098, 0.38431372549, 0.419607843137, 0.0, 0.0, 0.41568627451, 0.0, 0.760784313725, 0.745098039216, 0.0, 0.372549019608, 1.0, 1.0, 1.0, 0.407843137255, 1.0, 0.588235294118, 0.596078431373, 0.654901960784, 0.00392156862745, 1.0, 0.996078431373, 0.741176470588, 0.00392156862745, 0.733333333333, 0.458823529412, 0.647058823529, 1.0, 0.466666666667, 0.478431372549, 0.149019607843, 0.0, 0.262745098039, 0.709803921569, 1.0, 1.0, 0.564705882353, 0.494117647059, 0.741176470588, 0.898039215686, 0.870588235294, 0.0, 0.0, 0.0, 0.0, 0.521568627451, 0.0, 0.470588235294, 0.0, 1.0, 0.909803921569};
    static const float greenArray[] = {0.0, 0.0, 1.0, 0.0, 0.0, 0.298039215686, 0.898039215686, 0.372549019608, 1.0, 0.0, 0.576470588235, 0.141176470588, 0.0823529411765, 0.81568627451, 0.0549019607843, 0.407843137255, 0.0, 0.490196078431, 0.509803921569, 0.682352941176, 0.549019607843, 0.6, 0.560784313725, 0.678431372549, 0.0, 0.0, 0.0078431372549, 0.239215686275, 0.454901960784, 0.541176470588, 1.0, 0.341176470588, 1.0, 0.933333333333, 0.537254901961, 0.776470588235, 0.81568627451, 0.533333333333, 0.266666666667, 1.0, 0.650980392157, 0.301960784314, 0.278431372549, 0.203921568627, 0.278431372549, 0.0, 0.0, 0.694117647059, 0.858823529412, 0.98431372549, 0.176470588235, 0.827450980392, 0.435294117647, 1.0, 1.0, 0.607843137255, 0.392156862745, 0.462745098039, 0.662745098039, 0.725490196078, 0.509803921569, 1.0, 0.43137254902, 0.36862745098};
    static const float blueArray[] = {0.0, 0.403921568627, 0.0, 0.337254901961, 0.556862745098, 0.63137254902, 0.0078431372549, 0.223529411765, 0.0, 0.227450980392, 0.494117647059, 0.0, 0.266666666667, 0.796078431373, 0.0, 0.509803921569, 1.0, 0.709803921569, 0.423529411765, 0.494117647059, 0.623529411765, 0.439215686275, 0.611764705882, 0.305882352941, 0.0, 0.964705882353, 0.61568627451, 0.23137254902, 0.639215686275, 0.909803921569, 0.321568627451, 0.250980392157, 0.996078431373, 0.909803921569, 0.0, 1.0, 1.0, 0.0, 0.694117647059, 0.823529411765, 0.996078431373, 0.0, 0.509803921569, 0.0, 0.329411764706, 0.172549019608, 1.0, 0.403921568627, 0.4, 0.572549019608, 0.823529411765, 0.576470588235, 0.996078431373, 0.454901960784, 0.470588235294, 1.0, 0.00392156862745, 1.0, 0.0, 0.0901960784314, 0.192156862745, 0.776470588235, 0.254901960784, 0.745098039216};

//    static const int fillStyleArray[] = {3001,3002,3006,3007,3016,3017,3001,3002,3006,3007,3016,3017,3001,3002,3006,3007,3016,3017,3001,3002,3006,3007,3016,3017,3001,3002,3006,3007,3016,3017,3001,3002,3006,3007,3016,3017,3001,3002,3006,3007,3016,3017,3001,3002,3006,3007,3016,3017};
    static const int fillStyleArray[] = {3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001};

    std::vector<float> red (redArray, redArray + sizeof(redArray) / sizeof(redArray[0]) );
    std::vector<float> green (greenArray, greenArray + sizeof(greenArray) / sizeof(greenArray[0]) );
    std::vector<float> blue (blueArray, blueArray + sizeof(blueArray) / sizeof(blueArray[0]) );
    std::vector<int> fillStyle (fillStyleArray, fillStyleArray + sizeof(fillStyleArray) / sizeof(fillStyleArray[0]) );

    StringVector plottedVariableNames;

    for (Double1DPlotToProcessMap::iterator iterI = m_int1DPlotToProcess.begin(); iterI != m_int1DPlotToProcess.end(); iterI++)
    {
        TH1F *pTH1F_I_Init = iterI->first;
        const int position_I(m_1DIntPlots.at(pTH1F_I_Init));
        std::string variableName_I(m_intVariablesToRead.at(position_I));
        THStack *pTHStack = new THStack(this->RandomName().c_str(),variableName_I.c_str());

        if (std::find(plottedVariableNames.begin(), plottedVariableNames.end(), variableName_I) != plottedVariableNames.end())
            continue;

        plottedVariableNames.push_back(variableName_I);

        TCanvas *pTCanvas = new TCanvas(variableName_I.c_str(),variableName_I.c_str());
        TLegend *pTLegend = new TLegend(0.5,0.7,0.9,0.9);
        int colourCounter(0);

        for (Double1DPlotToProcessMap::iterator iterJ = iterI; iterJ != m_int1DPlotToProcess.end(); iterJ++)
        {
            TH1F *pTH1F_J_Init = iterI->first;
            TH1F *pTH1F_J = (TH1F*)(iterI->first->Clone());
            pTH1F_J->SetName(this->RandomName().c_str());
            const Process *pActiveProcess_J = iterJ->second;
            const int position_J(m_1DIntPlots.at(pTH1F_J_Init));
            std::string variableName_J(m_intVariablesToRead.at(position_J));

            if (variableName_I == variableName_J)
            {
                Color_t color = TColor::GetColor(red.at(colourCounter), green.at(colourCounter), blue.at(colourCounter));        
                colourCounter++;
                pTH1F_J->SetLineColor(color);
                pTH1F_J->SetFillColor(color);
                pTH1F_J->SetFillStyle(fillStyle.at(colourCounter));
                pTH1F_J->SetMinimum(0.001);
                pTH1F_J->SetMaximum(2*pTH1F_J->GetBinContent(pTH1F_J->GetMaximumBin()));
                pTH1F_J->SetFillStyle(3001);
                pTH1F_J->Draw("same");
                pTHStack->Add(pTH1F_J);
                std::string processName(pActiveProcess_J->GetEventType());
                pTLegend->AddEntry(pTH1F_J,processName.c_str(),"f");
            }
        }

        std::string plotName = variableName_I + "_MultiPlot.C";
        gStyle->SetOptStat(0);
        pTLegend->Draw("same");
        pTCanvas->SetLogy();
        pTCanvas->Update();
        pTCanvas->SaveAs(plotName.c_str());

        plotName = variableName_I + "_StackPlot.C";
        pTCanvas = new TCanvas(variableName_I.c_str(),variableName_I.c_str());
        pTHStack->SetMinimum(0.001);
        pTHStack->Draw();
        pTHStack->GetXaxis()->SetTitle(variableName_I.c_str());
        pTHStack->GetYaxis()->SetTitle("Entries");
        pTLegend->Draw("same");
        pTCanvas->SetLogy();
        pTCanvas->Update();
        pTCanvas->SaveAs(plotName.c_str());
    }

    for (Double1DPlotToProcessMap::iterator iterI = m_double1DPlotToProcess.begin(); iterI != m_double1DPlotToProcess.end(); iterI++)
    {
        TH1F *pTH1F_I_Init = iterI->first;
        const int position_I(m_1DDoublePlots.at(pTH1F_I_Init));
        std::string variableName_I(m_doubleVariablesToRead.at(position_I));
        THStack *pTHStack = new THStack(this->RandomName().c_str(),variableName_I.c_str());

        if (std::find(plottedVariableNames.begin(), plottedVariableNames.end(), variableName_I) != plottedVariableNames.end())
            continue;

        plottedVariableNames.push_back(variableName_I);

        TCanvas *pTCanvas = new TCanvas(variableName_I.c_str(),variableName_I.c_str());
        TLegend *pTLegend = new TLegend(0.5,0.7,0.9,0.9);
        int colourCounter(0);

        for (Double1DPlotToProcessMap::iterator iterJ = iterI; iterJ != m_double1DPlotToProcess.end(); iterJ++)
        {
            TH1F *pTH1F_J_Init = iterJ->first;
            TH1F *pTH1F_J = (TH1F*)(iterJ->first->Clone());
            pTH1F_J->SetName(this->RandomName().c_str());
            const Process *pActiveProcess_J = iterJ->second;
            const int position_J(m_1DDoublePlots.at(pTH1F_J_Init));
            std::string variableName_J(m_doubleVariablesToRead.at(position_J));

            if (variableName_I == variableName_J)
            {
                Color_t color = TColor::GetColor(red.at(colourCounter), green.at(colourCounter), blue.at(colourCounter));
                colourCounter++;
                pTH1F_J->SetLineColor(color);
                pTH1F_J->SetFillColor(color);
                pTH1F_J->SetFillStyle(fillStyle.at(colourCounter));
                pTH1F_J->SetMinimum(0.001);
                pTH1F_J->SetMaximum(2*pTH1F_J->GetBinContent(pTH1F_J->GetMaximumBin()));
                pTH1F_J->Draw("same");
                pTHStack->Add(pTH1F_J);
                std::string processName(pActiveProcess_J->GetEventType());
                pTLegend->AddEntry(pTH1F_J,processName.c_str(),"f");
            }
        }

        std::string plotName = variableName_I + "_MultiPlot.C";
        gStyle->SetOptStat(0);
        pTLegend->Draw("same");
        pTCanvas->SetLogy();
        pTCanvas->Update();
        pTCanvas->SaveAs(plotName.c_str());

        plotName = variableName_I + "_StackPlot.C";
        pTCanvas = new TCanvas(variableName_I.c_str(),variableName_I.c_str());
        pTHStack->SetMinimum(0.001);
        pTHStack->Draw();
        pTHStack->GetXaxis()->SetTitle(variableName_I.c_str());
        pTHStack->GetYaxis()->SetTitle("Entries");
        pTLegend->Draw("same");
        pTCanvas->SetLogy();
        pTCanvas->Update();
        pTCanvas->SaveAs(plotName.c_str());
    }

    std::cout << "End: MakeSimplePlots::WritePlots" << std::endl;
}

//=====================================================================

void MakeSimplePlots::WriteIndividualPlots()
{
    std::cout << "Begin: MakeSimplePlots::WriteIndividualPlots" << std::endl;
    for (Double1DPlotToProcessMap::iterator iter = m_int1DPlotToProcess.begin(); iter != m_int1DPlotToProcess.end(); iter++)
    {
        TH1F *pTH1F = (TH1F*)(iter->first->Clone());
        const Process *pProcess = iter->second;
        std::string processName = pTH1F->GetName();
        std::string saveName = processName + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH1F->Draw();
        pTCanvas->SaveAs(saveName.c_str());
        pTH1F->SetName(this->RandomName().c_str());
    }

    for (Double1DPlotToProcessMap::iterator iter = m_double1DPlotToProcess.begin(); iter != m_double1DPlotToProcess.end(); iter++)
    {
        TH1F *pTH1F = (TH1F*)(iter->first->Clone());
        const Process *pProcess = iter->second;
        std::string processName = pTH1F->GetName();
        std::string saveName = processName + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH1F->Draw();
        pTCanvas->SaveAs(saveName.c_str());
        pTH1F->SetName(this->RandomName().c_str());
    }

    for (Double2DPlotToProcessMap::iterator iter = m_double2DPlotToProcess.begin(); iter != m_double2DPlotToProcess.end(); iter++)
    {
        TH2F *pTH2F = (TH2F*)(iter->first->Clone());
        const Process *pProcess = iter->second;
        std::string processName = pTH2F->GetName();
        std::string saveName = processName + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH2F->Draw("COLZ");
        pTCanvas->SaveAs(saveName.c_str());
        pTH2F->SetName(this->RandomName().c_str());
    }

    std::cout << "End: MakeSimplePlots::WriteIndividualPlots" << std::endl;
}

//=====================================================================

void MakeSimplePlots::LoadData()
{
    std::cout << "Begin: MakeSimplePlots::LoadData" << std::endl;

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it++)
    {
        const Process *pProcess(*it);
        TChain *pTChain(pProcess->GetTChain());

        double weight(pProcess->GetProcessWeight());
        int intsToRead[m_intVariablesToRead.size()];
        double doublesToRead[m_doubleVariablesToRead.size()];

        for (StringVector::iterator iter = m_intVariablesToRead.begin(); iter != m_intVariablesToRead.end(); iter++)
        {
            std::string variableName(*iter);
            int position(iter-m_intVariablesToRead.begin());
            pTChain->SetBranchAddress(variableName.c_str(), &intsToRead[position]);
        }

        for (StringVector::iterator iter = m_doubleVariablesToRead.begin(); iter != m_doubleVariablesToRead.end(); iter++)
        {
            std::string variableName(*iter);
            int position(iter-m_doubleVariablesToRead.begin());
            pTChain->SetBranchAddress(variableName.c_str(), &doublesToRead[position]);
        }

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);

            if (!pProcess->DoesEventPassCuts(event))
                continue;

            for (Int1DPlotToPositionMap::iterator iter = m_1DIntPlots.begin(); iter != m_1DIntPlots.end(); iter++)
            {
                TH1F *pTH1F = iter->first;
                int position = iter->second;
                const Process *pActiveProcess = m_int1DPlotToProcess.at(pTH1F);
                if (&*pActiveProcess == &*pProcess)
                    pTH1F->Fill(intsToRead[position], weight);
            }

            for (Double1DPlotToPositionMap::iterator iter = m_1DDoublePlots.begin(); iter != m_1DDoublePlots.end(); iter++)
            {
                TH1F *pTH1F = iter->first;
                int position = iter->second;
                const Process *pActiveProcess = m_double1DPlotToProcess.at(pTH1F);
                if (&*pActiveProcess == &*pProcess)
                    pTH1F->Fill(doublesToRead[position], weight);
            }

            for (Double2DPlotToPositionMap::iterator iter = m_2DDoublePlots.begin(); iter != m_2DDoublePlots.end(); iter++)
            {
                TH2F *pTH2F(iter->first);
                int positionX(iter->second.first);
                int positionY(iter->second.second);
                const Process *pActiveProcess = m_double2DPlotToProcess.at(pTH2F);
                if (&*pActiveProcess == &*pProcess)
                    pTH2F->Fill(doublesToRead[positionX], doublesToRead[positionY], weight);
            }
        }
    }
    std::cout << "End: MakeSimplePlots::LoadData" << std::endl;
}

//=====================================================================

void MakeSimplePlots::Register2DPlot(const Process *pProcess, const std::string &variableNameX, const std::string &variableNameY, const int &nBinsX, const double &lowBinX, const double &highBinX, const int &nBinsY, const double &lowBinY, const double &highBinY)
{
    std::cout << "Begin: MakeSimplePlots::Register2DPlot" << std::endl;

    int positionInVectorX = std::find(m_doubleVariablesToRead.begin(), m_doubleVariablesToRead.end(), variableNameX) - m_doubleVariablesToRead.begin();
    int positionX(std::numeric_limits<int>::max());

    if (positionInVectorX != m_doubleVariablesToRead.size())
    {
        positionX = positionInVectorX;
    }
    else
    {
        positionX = m_doubleVariablesToRead.size();
        m_doubleVariablesToRead.push_back(variableNameX);
    }

    int positionInVectorY = std::find(m_doubleVariablesToRead.begin(), m_doubleVariablesToRead.end(), variableNameY) - m_doubleVariablesToRead.begin();
    int positionY(std::numeric_limits<int>::max());

    if (positionInVectorY != m_doubleVariablesToRead.size())
    {
        positionY = positionInVectorY;
    }
    else
    {
        positionY = m_doubleVariablesToRead.size();
        m_doubleVariablesToRead.push_back(variableNameY);
    }

    std::string plotName = variableNameX + "_" + variableNameY + "_" + pProcess->GetEventType();
    std::string plotTitle = variableNameX + " vs " + variableNameY + " For " + pProcess->GetEventType();
    const char* name(plotName.c_str());
    const char* title(plotTitle.c_str());
    TH2F *pTH2F = new TH2F(name, title, nBinsX, lowBinX, highBinX, nBinsY, lowBinY, highBinY);
    pTH2F->GetXaxis()->SetTitle(variableNameX.c_str());
    pTH2F->GetYaxis()->SetTitle(variableNameY.c_str());

    m_2DDoublePlots.insert(std::make_pair(pTH2F,std::make_pair(positionX,positionY)));
    m_double2DPlotToProcess.insert(std::make_pair(pTH2F,pProcess));
    std::cout << "End: MakeSimplePlots::Register2DPlot" << std::endl;
}

//=====================================================================

void MakeSimplePlots::Register1DPlot(const Process *pProcess, const std::string &variableName, const std::string &objectType, const int &nBins, const double &lowBin, const double &highBin) 
{
    std::cout << "Begin: MakeSimplePlots::Register1DPlot" << std::endl;
    if (objectType == "int")
    {
        this->Register1DIntPlot(pProcess,variableName,nBins,lowBin,highBin);
    }
    if (objectType == "double")
    {
        this->Register1DDoublePlot(pProcess,variableName,nBins,lowBin,highBin);
    }
    std::cout << "End: MakeSimplePlots::Register1DPlot" << std::endl;
}

//=====================================================================

void MakeSimplePlots::Register1DIntPlot(const Process *pProcess, const std::string &variableName, const int &nBins, const double &lowBin, const double &highBin)
{
    std::cout << "Begin: MakeSimplePlots::Register1DIntPlot" << std::endl;
    int positionInVector = std::find(m_intVariablesToRead.begin(), m_intVariablesToRead.end(), variableName) - m_intVariablesToRead.begin();
    int position(std::numeric_limits<int>::max());

    if (positionInVector != m_intVariablesToRead.size())
    {
        position = positionInVector;
    }
    else 
    {
        position = m_intVariablesToRead.size();
        m_intVariablesToRead.push_back(variableName);
    }

    std::string plotName = variableName + "_" + pProcess->GetEventType();
    std::string plotTitle = variableName + " " + pProcess->GetEventType();
    const char* name(plotName.c_str());
    const char* title(plotTitle.c_str());
    TH1F *pTH1F = new TH1F(name, title, nBins, lowBin, highBin);
    pTH1F->GetXaxis()->SetTitle(variableName.c_str());
    pTH1F->GetYaxis()->SetTitle("Entries");

    m_1DIntPlots.insert(std::make_pair(pTH1F,position));
    m_int1DPlotToProcess.insert(std::make_pair(pTH1F,pProcess));
    std::cout << "End: MakeSimplePlots::Register1DIntPlot" << std::endl;
}

//=====================================================================

void MakeSimplePlots::Register1DDoublePlot(const Process *pProcess, const std::string &variableName, const int &nBins, const double &lowBin, const double &highBin)
{
    std::cout << "Begin: MakeSimplePlots::Register1DDoublePlot" << std::endl;
    int positionInVector = std::find(m_doubleVariablesToRead.begin(), m_doubleVariablesToRead.end(), variableName) - m_doubleVariablesToRead.begin();
    int position(std::numeric_limits<int>::max());

    if (positionInVector != m_doubleVariablesToRead.size())
    {   
        position = positionInVector;
    }
    else
    {   
        position = m_doubleVariablesToRead.size();
        m_doubleVariablesToRead.push_back(variableName);
    }

    std::string plotName = variableName + "_" + pProcess->GetEventType(); 
    std::string plotTitle = variableName + " " + pProcess->GetEventType(); 
    const char* name(plotName.c_str());
    const char* title(plotTitle.c_str());
    TH1F *pTH1F = new TH1F(name, title, nBins, lowBin, highBin);
    pTH1F->GetXaxis()->SetTitle(variableName.c_str());
    pTH1F->GetYaxis()->SetTitle("Entries");

    m_1DDoublePlots.insert(std::make_pair(pTH1F,position));
    m_double1DPlotToProcess.insert(std::make_pair(pTH1F,pProcess));
    std::cout << "End: MakeSimplePlots::Register1DDoublePlot" << std::endl;
}

//=====================================================================

std::string MakeSimplePlots::RandomName()
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
std::string MakeSimplePlots::NumberToString(const T &number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
