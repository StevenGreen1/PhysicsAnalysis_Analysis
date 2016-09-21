/**
  *  @file   AnalysisScripts/src/MakeDerivedPlots.cc 
  * 
  *  @brief  Implementation of the make plots class.
  * 
  *  $Log: $
  */

#include "MakeDerivedPlots.h"

//=====================================================================

MakeDerivedPlots::MakeDerivedPlots(const ProcessVector &processVector, PreSelection *pPreSelection) :
    m_pPreSelection(pPreSelection),
    m_processVector(processVector)
{
    MakeDerivedPlots::PlotContainer *pNPfosPlotContainer = new MakeDerivedPlots::PlotContainer("NPfos", 400, 0.0, 400.0);
    MakeDerivedPlots::PlotContainer *pNPfosBosonWPlotContainer = new MakeDerivedPlots::PlotContainer("NPfosBosonW", 200, 0.0, 200.0);
    MakeDerivedPlots::PlotContainer *pNPfosBosonZPlotContainer = new MakeDerivedPlots::PlotContainer("NPfosBosonZ", 200, 0.0, 200.0);
    MakeDerivedPlots::PlotContainer *pEnergyWPlotContainer = new MakeDerivedPlots::PlotContainer("EnergyW", 1400, 0.0, 1400.0);
    MakeDerivedPlots::PlotContainer *pEnergyZPlotContainer = new MakeDerivedPlots::PlotContainer("EnergyZ", 1400, 0.0, 1400.0);
    MakeDerivedPlots::PlotContainer *pTransverseMomentumPlotContainer = new MakeDerivedPlots::PlotContainer("TransverseMomentum", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pTransverseMomentumBosonWPlotContainer = new MakeDerivedPlots::PlotContainer("TransverseMomentumBosonW", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pTransverseMomentumBosonZPlotContainer = new MakeDerivedPlots::PlotContainer("TransverseMomentumBosonZ", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pTransverseEnergyPlotContainer = new MakeDerivedPlots::PlotContainer("TransverseEnergy", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pTransverseEnergyBosonWPlotContainer = new MakeDerivedPlots::PlotContainer("TransverseEnergyBosonW", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pTransverseEnergyBosonZPlotContainer = new MakeDerivedPlots::PlotContainer("TransverseEnergyBosonZ", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pCosThetaMissingPlotContainer = new MakeDerivedPlots::PlotContainer("CosThetaMissing", 200, -1.0, 1.0);
    MakeDerivedPlots::PlotContainer *pRecoilMassPlotContainer = new MakeDerivedPlots::PlotContainer("RecoilMass", 1400, -2000.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pY12PlotContainer = new MakeDerivedPlots::PlotContainer("Y12", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY23PlotContainer = new MakeDerivedPlots::PlotContainer("Y23", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY34PlotContainer = new MakeDerivedPlots::PlotContainer("Y34", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY45PlotContainer = new MakeDerivedPlots::PlotContainer("Y45", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY56PlotContainer = new MakeDerivedPlots::PlotContainer("Y56", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY67PlotContainer = new MakeDerivedPlots::PlotContainer("Y67", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pInvariantMassSystemPlotContainer =  new MakeDerivedPlots::PlotContainer("InvariantMassSystem", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pCosThetaStarWBosonsPlotContainer =  new MakeDerivedPlots::PlotContainer("CosThetaStarWBosons", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pCosThetaStarZBosonsPlotContainer =  new MakeDerivedPlots::PlotContainer("CosThetaStarZBosons", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pAcolinearityJetsWPlotContainer = new MakeDerivedPlots::PlotContainer("AcolinearityJetsW", 180, 0.0, 180.0);
    MakeDerivedPlots::PlotContainer *pAcolinearityJetsZPlotContainer = new MakeDerivedPlots::PlotContainer("AcolinearityJetsZ", 180, 0.0, 180.0);
    MakeDerivedPlots::PlotContainer *pAcolinearityBosonsWPlotContainer = new MakeDerivedPlots::PlotContainer("AcolinearityBosonsW", 180, 0.0, 180.0);
    MakeDerivedPlots::PlotContainer *pAcolinearityBosonsZPlotContainer = new MakeDerivedPlots::PlotContainer("AcolinearityBosonsZ", 180, 0.0, 180.0);
    MakeDerivedPlots::PlotContainer *pPrincipleThrustValuePlotContainer =  new MakeDerivedPlots::PlotContainer("PrincipleThrustValue", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pMajorThrustValuePlotContainer =  new MakeDerivedPlots::PlotContainer("MajorThrustValue", 80, 0.0, 0.8);
    MakeDerivedPlots::PlotContainer *pMinorThrustValuePlotContainer =  new MakeDerivedPlots::PlotContainer("MinorThrustValue", 60, 0.0, 0.6);
    MakeDerivedPlots::PlotContainer *pSphericityPlotContainer =  new MakeDerivedPlots::PlotContainer("Sphericity", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pAplanarityPlotContainer =  new MakeDerivedPlots::PlotContainer("Aplanarity", 50, 0.0, 0.5);
    MakeDerivedPlots::PlotContainer *pInvariantMassWPlotContainer =  new MakeDerivedPlots::PlotContainer("InvariantMassW", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pInvariantMassZPlotContainer =  new MakeDerivedPlots::PlotContainer("InvariantMassZ", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pCosThetaStarWJetPlotContainer = new MakeDerivedPlots::PlotContainer("CosThetaStarWJet", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pCosThetaStarZJetPlotContainer = new MakeDerivedPlots::PlotContainer("CosThetaStarZJet", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pHighestBTagWPlotContainer = new MakeDerivedPlots::PlotContainer("HighestBTagW", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pLowestBTagWPlotContainer = new MakeDerivedPlots::PlotContainer("LowestBTagW", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pHighestBTagZPlotContainer = new MakeDerivedPlots::PlotContainer("HighestBTagZ", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pLowestBTagZPlotContainer = new MakeDerivedPlots::PlotContainer("LowestBTagZ", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pHighestCTagWPlotContainer = new MakeDerivedPlots::PlotContainer("HighestCTagW", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pLowestCTagWPlotContainer = new MakeDerivedPlots::PlotContainer("LowestCTagW", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pHighestCTagZPlotContainer = new MakeDerivedPlots::PlotContainer("HighestCTagZ", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pLowestCTagZPlotContainer = new MakeDerivedPlots::PlotContainer("LowestCTagZ", 100, 0.0, 1.0);

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);
        double weight(pProcess->GetProcessWeight());

        TChain *pTChain = pProcess->GetTChain(); 
        Variables *pVariables = new Variables();
        pVariables->SetBranchAddresses(pTChain);

        for (int entry = 0; entry < pTChain->GetEntries(); entry++)
        {
            pTChain->GetEntry(entry);

            if (pVariables->m_transverseMomentum < m_pPreSelection->m_transverseMomentumLow or m_pPreSelection->m_transverseMomentumHigh < pVariables->m_transverseMomentum)
                continue;

            if (pVariables->m_invariantMassSystem < m_pPreSelection->m_invariantMassSystemLow or m_pPreSelection->m_invariantMassSystemHigh < pVariables->m_invariantMassSystem)
                continue;

            if (pVariables->m_invariantMassWBosons1 < m_pPreSelection->m_invariantMassBosonLow or m_pPreSelection->m_invariantMassBosonHigh < pVariables->m_invariantMassWBosons1)
                continue;

            if (pVariables->m_invariantMassWBosons2 < m_pPreSelection->m_invariantMassBosonLow or m_pPreSelection->m_invariantMassBosonHigh < pVariables->m_invariantMassWBosons2)
                continue;

            if (pVariables->m_invariantMassZBosons1 < m_pPreSelection->m_invariantMassBosonLow or m_pPreSelection->m_invariantMassBosonHigh < pVariables->m_invariantMassZBosons1)
                continue;

            if (pVariables->m_invariantMassZBosons2 < m_pPreSelection->m_invariantMassBosonLow or m_pPreSelection->m_invariantMassBosonHigh < pVariables->m_invariantMassZBosons2)
                continue;

            pNPfosPlotContainer->Fill(pVariables->m_nPfosBosonW1 + pVariables->m_nPfosBosonW2, weight);
            pNPfosBosonWPlotContainer->Fill(pVariables->m_nPfosBosonW1, weight);
            pNPfosBosonWPlotContainer->Fill(pVariables->m_nPfosBosonW2, weight);
            pNPfosBosonZPlotContainer->Fill(pVariables->m_nPfosBosonZ1, weight);
            pNPfosBosonZPlotContainer->Fill(pVariables->m_nPfosBosonZ2, weight);

            double jetEW11(std::numeric_limits<double>::max());
            double jetEW12(std::numeric_limits<double>::max());
            double jetEW21(std::numeric_limits<double>::max());
            double jetEW22(std::numeric_limits<double>::max());
            double jetEZ11(std::numeric_limits<double>::max());
            double jetEZ12(std::numeric_limits<double>::max());
            double jetEZ21(std::numeric_limits<double>::max());
            double jetEZ22(std::numeric_limits<double>::max());
            pVariables->SplitJetsForBosonEnergiesW(jetEW11, jetEW12, jetEW21, jetEW22);
            pVariables->SplitJetsForBosonEnergiesZ(jetEZ11, jetEZ12, jetEZ21, jetEZ22);

            pEnergyWPlotContainer->Fill(jetEW11+jetEW12, weight);
            pEnergyWPlotContainer->Fill(jetEW21+jetEW22, weight);
            pEnergyZPlotContainer->Fill(jetEZ11+jetEZ12, weight);
            pEnergyZPlotContainer->Fill(jetEZ21+jetEZ22, weight);
            pTransverseMomentumPlotContainer->Fill(pVariables->m_transverseMomentum, weight);
            pTransverseMomentumBosonWPlotContainer->Fill(pVariables->m_transverseMomentumBosonW1, weight);
            pTransverseMomentumBosonWPlotContainer->Fill(pVariables->m_transverseMomentumBosonW2, weight);
            pTransverseMomentumBosonZPlotContainer->Fill(pVariables->m_transverseMomentumBosonZ1, weight);
            pTransverseMomentumBosonZPlotContainer->Fill(pVariables->m_transverseMomentumBosonZ2, weight);
            pTransverseEnergyPlotContainer->Fill(pVariables->m_transverseEnergy, weight);
            pTransverseEnergyBosonWPlotContainer->Fill(pVariables->m_transverseEnergyBosonW1, weight);
            pTransverseEnergyBosonWPlotContainer->Fill(pVariables->m_transverseEnergyBosonW2, weight);
            pTransverseEnergyBosonZPlotContainer->Fill(pVariables->m_transverseEnergyBosonZ1, weight);
            pTransverseEnergyBosonZPlotContainer->Fill(pVariables->m_transverseEnergyBosonZ2, weight);
            pCosThetaMissingPlotContainer->Fill(pVariables->m_cosThetaMissing, weight);
            pRecoilMassPlotContainer->Fill(pVariables->m_recoilMass, weight);
            pY12PlotContainer->Fill(pVariables->m_y12, weight);
            pY23PlotContainer->Fill(pVariables->m_y23, weight);
            pY34PlotContainer->Fill(pVariables->m_y34, weight);
            pY45PlotContainer->Fill(pVariables->m_y45, weight);
            pY56PlotContainer->Fill(pVariables->m_y56, weight);
            pY67PlotContainer->Fill(pVariables->m_y67, weight);
            pInvariantMassSystemPlotContainer->Fill(pVariables->m_invariantMassSystem, weight);
            pCosThetaStarWBosonsPlotContainer->Fill(pVariables->m_cosThetaStarWBosons, weight);
            pCosThetaStarZBosonsPlotContainer->Fill(pVariables->m_cosThetaStarZBosons, weight);
            pAcolinearityJetsWPlotContainer->Fill(pVariables->m_acolinearityJetsW1, weight);
            pAcolinearityJetsWPlotContainer->Fill(pVariables->m_acolinearityJetsW2, weight);
            pAcolinearityJetsZPlotContainer->Fill(pVariables->m_acolinearityJetsZ1, weight);
            pAcolinearityJetsZPlotContainer->Fill(pVariables->m_acolinearityJetsZ2, weight);
            pAcolinearityBosonsWPlotContainer->Fill(pVariables->m_acolinearityBosonsW, weight);
            pAcolinearityBosonsZPlotContainer->Fill(pVariables->m_acolinearityBosonsZ, weight);
            pPrincipleThrustValuePlotContainer->Fill(pVariables->m_principleThrustValue, weight);
            pMajorThrustValuePlotContainer->Fill(pVariables->m_majorThrustValue, weight);
            pMinorThrustValuePlotContainer->Fill(pVariables->m_minorThrustValue, weight);
            pSphericityPlotContainer->Fill(pVariables->m_sphericity, weight);
            pAplanarityPlotContainer->Fill(pVariables->m_aplanarity, weight);
            pInvariantMassWPlotContainer->Fill(pVariables->m_invariantMassWBosons1, weight);
            pInvariantMassWPlotContainer->Fill(pVariables->m_invariantMassWBosons2, weight);
            pInvariantMassZPlotContainer->Fill(pVariables->m_invariantMassZBosons1, weight);
            pInvariantMassZPlotContainer->Fill(pVariables->m_invariantMassZBosons2, weight);
            pCosThetaStarWJetPlotContainer->Fill(pVariables->m_cosThetaStarWJets1, weight);
            pCosThetaStarWJetPlotContainer->Fill(pVariables->m_cosThetaStarWJets2, weight);
            pCosThetaStarZJetPlotContainer->Fill(pVariables->m_cosThetaStarZJets1, weight);
            pCosThetaStarZJetPlotContainer->Fill(pVariables->m_cosThetaStarZJets2, weight);

            double highestBTagW1(std::numeric_limits<double>::max());
            double lowestBTagW1(std::numeric_limits<double>::max());
            double highestBTagW2(std::numeric_limits<double>::max());
            double lowestBTagW2(std::numeric_limits<double>::max());
            double highestCTagW1(std::numeric_limits<double>::max());
            double lowestCTagW1(std::numeric_limits<double>::max());
            double highestCTagW2(std::numeric_limits<double>::max());
            double lowestCTagW2(std::numeric_limits<double>::max());
            double highestBTagZ1(std::numeric_limits<double>::max());
            double lowestBTagZ1(std::numeric_limits<double>::max());
            double highestBTagZ2(std::numeric_limits<double>::max());
            double lowestBTagZ2(std::numeric_limits<double>::max());
            double highestCTagZ1(std::numeric_limits<double>::max());
            double lowestCTagZ1(std::numeric_limits<double>::max());
            double highestCTagZ2(std::numeric_limits<double>::max());
            double lowestCTagZ2(std::numeric_limits<double>::max());
            pVariables->FlavourTagSettingW(highestBTagW1,lowestBTagW1,highestBTagW2,lowestBTagW2,highestCTagW1,lowestCTagW1,highestCTagW2,lowestCTagW2);
            pVariables->FlavourTagSettingZ(highestBTagZ1,lowestBTagZ1,highestBTagZ2,lowestBTagZ2,highestCTagZ1,lowestCTagZ1,highestCTagZ2,lowestCTagZ2);

            pHighestBTagWPlotContainer->Fill(highestBTagW1,weight);
            pHighestBTagWPlotContainer->Fill(highestBTagW2,weight);
            pLowestBTagWPlotContainer->Fill(lowestBTagW1,weight);
            pLowestBTagWPlotContainer->Fill(lowestBTagW2,weight);
            pHighestBTagZPlotContainer->Fill(highestBTagZ1,weight);
            pHighestBTagZPlotContainer->Fill(highestBTagZ2,weight);
            pLowestBTagZPlotContainer->Fill(lowestBTagZ1,weight);
            pLowestBTagZPlotContainer->Fill(lowestBTagZ2,weight);
            pHighestCTagWPlotContainer->Fill(highestCTagW1,weight);
            pHighestCTagWPlotContainer->Fill(highestCTagW2,weight);
            pLowestCTagWPlotContainer->Fill(lowestCTagW1,weight);
            pLowestCTagWPlotContainer->Fill(lowestCTagW2,weight);
            pHighestCTagZPlotContainer->Fill(highestCTagZ1,weight);
            pHighestCTagZPlotContainer->Fill(highestCTagZ2,weight);
            pLowestCTagZPlotContainer->Fill(lowestCTagZ1,weight);
            pLowestCTagZPlotContainer->Fill(lowestCTagZ2,weight);
        }

        pNPfosPlotContainer->DrawHistograms(pProcess->GetEventType());
        pNPfosBosonWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pNPfosBosonZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseMomentumPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseMomentumBosonWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseMomentumBosonZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseEnergyPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseEnergyBosonWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseEnergyBosonZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaMissingPlotContainer->DrawHistograms(pProcess->GetEventType());
        pRecoilMassPlotContainer->DrawHistograms(pProcess->GetEventType());
        pY12PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY23PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY34PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY45PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY56PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY67PlotContainer->DrawHistograms(pProcess->GetEventType());
        pInvariantMassSystemPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaStarWBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaStarZBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pAcolinearityJetsWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pAcolinearityJetsZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pAcolinearityBosonsWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pAcolinearityBosonsZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pPrincipleThrustValuePlotContainer->DrawHistograms(pProcess->GetEventType());
        pMajorThrustValuePlotContainer->DrawHistograms(pProcess->GetEventType());
        pMinorThrustValuePlotContainer->DrawHistograms(pProcess->GetEventType());
        pSphericityPlotContainer->DrawHistograms(pProcess->GetEventType());
        pAplanarityPlotContainer->DrawHistograms(pProcess->GetEventType());
        pInvariantMassWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pInvariantMassZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaStarWJetPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaStarZJetPlotContainer->DrawHistograms(pProcess->GetEventType());
        pHighestBTagWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pLowestBTagWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pHighestBTagZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pLowestBTagZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pHighestCTagWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pLowestCTagWPlotContainer->DrawHistograms(pProcess->GetEventType());
        pHighestCTagZPlotContainer->DrawHistograms(pProcess->GetEventType());
        pLowestCTagZPlotContainer->DrawHistograms(pProcess->GetEventType());

    }
    pNPfosPlotContainer->SavePlots();
    pNPfosBosonWPlotContainer->SavePlots();
    pNPfosBosonZPlotContainer->SavePlots();
    pTransverseMomentumPlotContainer->SavePlots();
    pTransverseMomentumBosonWPlotContainer->SavePlots();
    pTransverseMomentumBosonZPlotContainer->SavePlots();
    pTransverseEnergyPlotContainer->SavePlots();
    pTransverseEnergyBosonWPlotContainer->SavePlots();
    pTransverseEnergyBosonZPlotContainer->SavePlots();
    pCosThetaMissingPlotContainer->SavePlots();
    pRecoilMassPlotContainer->SavePlots();
    pY12PlotContainer->SavePlots();
    pY23PlotContainer->SavePlots();
    pY34PlotContainer->SavePlots();
    pY45PlotContainer->SavePlots();
    pY56PlotContainer->SavePlots();
    pY67PlotContainer->SavePlots();
    pInvariantMassSystemPlotContainer->SavePlots();
    pCosThetaStarWBosonsPlotContainer->SavePlots();
    pCosThetaStarZBosonsPlotContainer->SavePlots();
    pAcolinearityJetsWPlotContainer->SavePlots();
    pAcolinearityJetsZPlotContainer->SavePlots();
    pAcolinearityBosonsWPlotContainer->SavePlots();
    pAcolinearityBosonsZPlotContainer->SavePlots();
    pPrincipleThrustValuePlotContainer->SavePlots();
    pMajorThrustValuePlotContainer->SavePlots();
    pMinorThrustValuePlotContainer->SavePlots();
    pSphericityPlotContainer->SavePlots();
    pAplanarityPlotContainer->SavePlots();
    pInvariantMassWPlotContainer->SavePlots();
    pInvariantMassZPlotContainer->SavePlots();
    pCosThetaStarWJetPlotContainer->SavePlots();
    pCosThetaStarZJetPlotContainer->SavePlots();
    pHighestBTagWPlotContainer->SavePlots();
    pLowestBTagWPlotContainer->SavePlots();
    pHighestBTagZPlotContainer->SavePlots();
    pLowestBTagZPlotContainer->SavePlots();
    pHighestCTagWPlotContainer->SavePlots();
    pLowestCTagWPlotContainer->SavePlots();
    pHighestCTagZPlotContainer->SavePlots();
    pLowestCTagZPlotContainer->SavePlots();
}

//=====================================================================

MakeDerivedPlots::PlotContainer::PlotContainer(std::string variableName, int nBins, double xLow, double xHigh) :
    m_variableName(variableName),
    m_nBins(nBins),
    m_xLow(xLow),
    m_xHigh(xHigh),
    m_colourCounter(0)
{
    m_pTHStack = new THStack(this->RandomName().c_str(), variableName.c_str());
    m_pTCanvas = new TCanvas(this->RandomName().c_str(), variableName.c_str());
    m_pTCanvas->Divide(4,5);
    m_pTLegend = new TLegend(0.7,0.7,1.0,1.0);
    m_pTH1F = new TH1F(this->RandomName().c_str(), variableName.c_str(), nBins, xLow, xHigh);
    m_pTH1FSig = new TH1F(this->RandomName().c_str(), variableName.c_str(), nBins, xLow, xHigh);

    static const double redArray[] = {0.0, 0.00392156862745, 0.835294117647, 1.0, 0.619607843137, 0.0549019607843, 1.0, 0.0, 0.0, 0.58431372549, 1.0, 0.643137254902, 0.0, 0.56862745098, 0.38431372549, 0.419607843137, 0.0, 0.0, 0.41568627451, 0.0, 0.760784313725, 0.745098039216, 0.0, 0.372549019608, 1.0, 1.0, 1.0, 0.407843137255, 1.0, 0.588235294118, 0.596078431373, 0.654901960784, 0.00392156862745, 1.0, 0.996078431373, 0.741176470588, 0.00392156862745, 0.733333333333, 0.458823529412, 0.647058823529, 1.0, 0.466666666667, 0.478431372549, 0.149019607843, 0.0, 0.262745098039, 0.709803921569, 1.0, 1.0, 0.564705882353, 0.494117647059, 0.741176470588, 0.898039215686, 0.870588235294, 0.0, 0.0, 0.0, 0.0, 0.521568627451, 0.0, 0.470588235294, 0.0, 1.0, 0.909803921569};
    static const double greenArray[] = {0.0, 0.0, 1.0, 0.0, 0.0, 0.298039215686, 0.898039215686, 0.372549019608, 1.0, 0.0, 0.576470588235, 0.141176470588, 0.0823529411765, 0.81568627451, 0.0549019607843, 0.407843137255, 0.0, 0.490196078431, 0.509803921569, 0.682352941176, 0.549019607843, 0.6, 0.560784313725, 0.678431372549, 0.0, 0.0, 0.0078431372549, 0.239215686275, 0.454901960784, 0.541176470588, 1.0, 0.341176470588, 1.0, 0.933333333333, 0.537254901961, 0.776470588235, 0.81568627451, 0.533333333333, 0.266666666667, 1.0, 0.650980392157, 0.301960784314, 0.278431372549, 0.203921568627, 0.278431372549, 0.0, 0.0, 0.694117647059, 0.858823529412, 0.98431372549, 0.176470588235, 0.827450980392, 0.435294117647, 1.0, 1.0, 0.607843137255, 0.392156862745, 0.462745098039, 0.662745098039, 0.725490196078, 0.509803921569, 1.0, 0.43137254902, 0.36862745098};
    static const double blueArray[] = {0.0, 0.403921568627, 0.0, 0.337254901961, 0.556862745098, 0.63137254902, 0.0078431372549, 0.223529411765, 0.0, 0.227450980392, 0.494117647059, 0.0, 0.266666666667, 0.796078431373, 0.0, 0.509803921569, 1.0, 0.709803921569, 0.423529411765, 0.494117647059, 0.623529411765, 0.439215686275, 0.611764705882, 0.305882352941, 0.0, 0.964705882353, 0.61568627451, 0.23137254902, 0.639215686275, 0.909803921569, 0.321568627451, 0.250980392157, 0.996078431373, 0.909803921569, 0.0, 1.0, 1.0, 0.0, 0.694117647059, 0.823529411765, 0.996078431373, 0.0, 0.509803921569, 0.0, 0.329411764706, 0.172549019608, 1.0, 0.403921568627, 0.4, 0.572549019608, 0.823529411765, 0.576470588235, 0.996078431373, 0.454901960784, 0.470588235294, 1.0, 0.00392156862745, 1.0, 0.0, 0.0901960784314, 0.192156862745, 0.776470588235, 0.254901960784, 0.745098039216};

    static const int fillStyleArray[] = {3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001,3001};

    FloatVector red (redArray, redArray + sizeof(redArray) / sizeof(redArray[0]) );
    FloatVector green (greenArray, greenArray + sizeof(greenArray) / sizeof(greenArray[0]) );
    FloatVector blue (blueArray, blueArray + sizeof(blueArray) / sizeof(blueArray[0]) );
    IntVector fillStyle (fillStyleArray, fillStyleArray + sizeof(fillStyleArray) / sizeof(fillStyleArray[0]) );
 
    m_red = red;
    m_green = green;
    m_blue = blue;
    m_fillStyle = fillStyle;
}

//=====================================================================

std::string MakeDerivedPlots::PlotContainer::RandomName()
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

void MakeDerivedPlots::PlotContainer::Fill(double value, double weight)
{
    m_pTH1F->Fill(value, weight);
}

//=====================================================================

void MakeDerivedPlots::PlotContainer::DrawHistograms(std::string processName)
{
    m_pTCanvas->cd(m_colourCounter+1);
    Color_t color = TColor::GetColor(m_red.at(m_colourCounter), m_green.at(m_colourCounter), m_blue.at(m_colourCounter));
    m_colourCounter++;
    m_pTH1F->GetXaxis()->SetTitle(m_variableName.c_str());
    m_pTH1F->GetYaxis()->SetTitle("Entries");
    m_pTH1F->SetLineColor(color);
    m_pTH1F->SetMinimum(0.1);
    m_pTH1F->SetMaximum(2*m_pTH1F->GetBinContent(m_pTH1F->GetMaximumBin()));
    TLegend *pTLegend = new TLegend(0.7,0.7,1.0,1.0);

    if (processName == "ee_nunuqqqq")
    {
        m_pTH1FSig = (TH1F*)(m_pTH1F->Clone());
        m_pTH1FSig->SetLineColor(1);
        m_pTH1FSig->SetLineStyle(2);
        m_pTH1FSig->Scale(1/m_pTH1FSig->Integral());
    }
    else
    {
        m_pTH1FSig->Draw("same");
    }

    m_pTH1F->SetFillColor(color);
    m_pTH1F->SetFillStyle(m_fillStyle.at(m_colourCounter));

    TH1F *pCloneTH1F = (TH1F*)(m_pTH1F->Clone());
    pCloneTH1F->Scale(1/pCloneTH1F->Integral());
    pCloneTH1F->Draw("same");

    pTLegend->AddEntry(m_pTH1F, processName.c_str(), "f");
    pTLegend->Draw("same");

    m_pTHStack->Add(m_pTH1F);
    m_pTLegend->AddEntry(m_pTH1F, processName.c_str(), "f");
    m_pTH1F = new TH1F(this->RandomName().c_str(), m_variableName.c_str(), m_nBins, m_xLow, m_xHigh);
}

//=====================================================================

void MakeDerivedPlots::PlotContainer::SavePlots()
{
    std::string plotName = m_variableName + "_MultiPlot.C";
    gStyle->SetOptStat(0);
    m_pTCanvas->cd();
    TLegend *pTLegendClone = (TLegend*)(m_pTLegend->Clone());
    pTLegendClone->DrawBox(0,0,1,1);
    m_pTCanvas->SetLogy();
    m_pTCanvas->Update();
    m_pTCanvas->SaveAs(plotName.c_str());

    plotName = m_variableName + "_StackPlot.C";
    m_pTCanvas = new TCanvas(this->RandomName().c_str(), m_variableName.c_str());
    m_pTHStack->SetMinimum(0.1);
    m_pTHStack->Draw();
    m_pTHStack->GetXaxis()->SetTitle(m_variableName.c_str());
    m_pTHStack->GetYaxis()->SetTitle("Entries");
    m_pTLegend->Draw("same");
    m_pTCanvas->SetLogy();
    m_pTCanvas->Update();
    m_pTCanvas->SaveAs(plotName.c_str());
}

//=====================================================================

template <class T>
std::string MakeDerivedPlots::NumberToString(const T &number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
