/**
  *  @file   AnalysisScripts/src/MakeDerivedPlots.cc 
  * 
  *  @brief  Implementation of the make plots class.
  * 
  *  $Log: $
  */

#include "MakeDerivedPlots.h"

//=====================================================================

MakeDerivedPlots::MakeDerivedPlots(const ProcessVector &processVector, std::string descriptor, PreSelection *pPreSelection, PostMVASelection *pPostMVASelection) :
    m_pPreSelection(pPreSelection),
    m_processVector(processVector),
    m_descriptor(descriptor)
{
    // Event
    MakeDerivedPlots::PlotContainer *pNPfosPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "NPfos", 400, 0.0, 400.0);
    MakeDerivedPlots::PlotContainer *pTransverseMomentumPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "TransverseMomentum", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pCosThetaMissingPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "CosThetaMissing", 200, -1.0, 1.0);
    MakeDerivedPlots::PlotContainer *pRecoilMassPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "RecoilMass", 1400, -2000.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pY12PlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "Y12", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY23PlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "Y23", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY34PlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "Y34", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY45PlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "Y45", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY56PlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "Y56", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pY67PlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "Y67", 100, 0.0, 10.0);
    MakeDerivedPlots::PlotContainer *pInvariantMassSystemPlotContainer =  new MakeDerivedPlots::PlotContainer(m_descriptor, "InvariantMassSystem", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pPrincipleThrustValuePlotContainer =  new MakeDerivedPlots::PlotContainer(m_descriptor, "PrincipleThrustValue", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pMajorThrustValuePlotContainer =  new MakeDerivedPlots::PlotContainer(m_descriptor, "MajorThrustValue", 80, 0.0, 0.8);
    MakeDerivedPlots::PlotContainer *pMinorThrustValuePlotContainer =  new MakeDerivedPlots::PlotContainer(m_descriptor, "MinorThrustValue", 60, 0.0, 0.6);
    MakeDerivedPlots::PlotContainer *pSphericityPlotContainer =  new MakeDerivedPlots::PlotContainer(m_descriptor, "Sphericity", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pAplanarityPlotContainer =  new MakeDerivedPlots::PlotContainer(m_descriptor, "Aplanarity", 50, 0.0, 0.5);
    MakeDerivedPlots::PlotContainer *pNumberOfIsolatedLeptons = new MakeDerivedPlots::PlotContainer(m_descriptor, "NumberOfIsolatedLeptons", 5, 0, 5);
    MakeDerivedPlots::PlotContainer *pHighestEnergyIsolatedLeptonEnergy = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyIsolatedLeptonEnergy", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyIsolatedLeptonMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyIsolatedLeptonTransverseMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyIsolatedLeptonTransverseMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyIsolatedLeptonCosTheta", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyIsolatedLeptonCosTheta = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyIsolatedLeptonCosTheta", 100, 0, 1);
    MakeDerivedPlots::PlotContainer *pHighestEnergyPfoEnergy = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyPfoEnergy", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyPfoMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyPfoMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyPfoTransverseMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyPfoTransverseMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyPfoCosTheta = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyPfoCosTheta", 100, 0, 1);
    MakeDerivedPlots::PlotContainer *pHighestEnergyElectronEnergy = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyElectronEnergy", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyElectronMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyElectronMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyElectronTransverseMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyElectronTransverseMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyElectronCosTheta = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyElectronCosTheta", 100, 0, 1);
    MakeDerivedPlots::PlotContainer *pHighestEnergyMuonEnergy = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyMuonEnergy", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyMuonMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyMuonMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyMuonTransverseMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyMuonTransverseMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyMuonCosTheta = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyMuonCosTheta", 100, 0, 1);
    MakeDerivedPlots::PlotContainer *pHighestEnergyPhotonEnergy = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyPhotonEnergy", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyPhotonMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyPhotonMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyPhotonTransverseMomentum = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyPhotonTransverseMomentum", 700, 0, 700);
    MakeDerivedPlots::PlotContainer *pHighestEnergyPhotonCosTheta = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestEnergyPhotonCosTheta", 100, 0, 1);

    // Bosons
    MakeDerivedPlots::PlotContainer *pNPfosSynBosonPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "NPfosSynBoson", 200, 0.0, 200.0);
    MakeDerivedPlots::PlotContainer *pEnergySynBosonPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "EnergySynBoson", 1400, 0.0, 1400.0);
    MakeDerivedPlots::PlotContainer *pMomentumSynBosonPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "MomentumSynBoson", 1400, 0.0, 1400.0);
    MakeDerivedPlots::PlotContainer *pTransverseMomentumSynBosonPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "TransverseMomentumSynBoson", 1400, 0.0, 1400.0);
    MakeDerivedPlots::PlotContainer *pCosThetaSynBosonPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "CosThetaSynBoson", 200, -1.0, 1.0);
    MakeDerivedPlots::PlotContainer *pCosThetaStarSynBosonsPlotContainer =  new MakeDerivedPlots::PlotContainer(m_descriptor, "CosThetaStarSynBosons", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pAcolinearitySynBosonsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "AcolinearitySynBosons", 180, 0.0, 180.0);
    MakeDerivedPlots::PlotContainer *pInvariantMassSynBosonsPlotContainer =  new MakeDerivedPlots::PlotContainer(m_descriptor, "InvariantMassSynBosons", 2000, 0.0, 2000.0);
    MakeDerivedPlots::PlotContainer *pHighestBTagSynBosonsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestBTagSynBosons", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pLowestBTagSynBosonsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "LowestBTagSynBosons", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pHighestCTagSynBosonsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "HighestCTagSynBosons", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pLowestCTagSynBosonsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "LowestCTagSynBosons", 100, 0.0, 1.0);

    // Jets
    MakeDerivedPlots::PlotContainer *pAcolinearitySynJetsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "AcolinearitySynJets", 180, 0.0, 180.0);
    MakeDerivedPlots::PlotContainer *pCosThetaStarSynJetsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "CosThetaStarSynJets", 100, 0.0, 1.0);
    MakeDerivedPlots::PlotContainer *pEnergySynJetsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "EnergySynJets", 1400, 0.0, 1400.0);
    MakeDerivedPlots::PlotContainer *pMomentumSynJetsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "MomentumSynJets", 1400, 0.0, 1400.0);
    MakeDerivedPlots::PlotContainer *pTransverseMomentumSynJetsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "TransverseMomentumSynJets", 1400, 0.0, 1400.0);
    MakeDerivedPlots::PlotContainer *pCosThetaSynJetsPlotContainer = new MakeDerivedPlots::PlotContainer(m_descriptor, "CosThetaSynJets", 200, -1.0, 1.0);

    for (const auto &pProcess: m_processVector)
    {
        double weight(pProcess->GetProcessWeight());

        TChain *pTChain; 
        Variables *pVariables = new Variables();

        if (pPostMVASelection != NULL)
        {
            pTChain = pProcess->GetPostMVATChain(); 
            pVariables->SetBranchAddresses(pTChain, true);
        }
        else
        {
            pTChain = pProcess->GetTChain(); 
            pVariables->SetBranchAddresses(pTChain, false);
        }

        for (int entry = 0; entry < pTChain->GetEntries(); entry++)
        {
            pTChain->GetEntry(entry);

            if (pVariables->m_nIsolatedLeptons < m_pPreSelection->GetNumberOfIsolatedLeptonsLowCut() or m_pPreSelection->GetNumberOfIsolatedLeptonsHighCut() < pVariables->m_nIsolatedLeptons)
                continue;

            if (pVariables->m_transverseMomentum < m_pPreSelection->GetTransverseMomentumLowCut() or m_pPreSelection->GetTransverseMomentumHighCut() < pVariables->m_transverseMomentum)
                continue;

            if (pVariables->m_invariantMassSystem < m_pPreSelection->GetInvariantMassSystemLowCut() or m_pPreSelection->GetInvariantMassSystemHighCut() < pVariables->m_invariantMassSystem)
                continue;

            if (pVariables->m_invariantMassSynBosons1 < m_pPreSelection->GetInvariantMassBosonLowCut() or m_pPreSelection->GetInvariantMassBosonHighCut() < pVariables->m_invariantMassSynBosons1)
                continue;

            if (pVariables->m_invariantMassSynBosons2 < m_pPreSelection->GetInvariantMassBosonLowCut() or m_pPreSelection->GetInvariantMassBosonHighCut() < pVariables->m_invariantMassSynBosons2)
                continue;

            if (pPostMVASelection != NULL)
            {
                if (pVariables->m_bdt < pPostMVASelection->GetBDTLowCut() or pPostMVASelection->GetBDTHighCut() < pVariables->m_bdt)
                    continue;
            }

            // Event 
            pNPfosPlotContainer->Fill(pVariables->m_nParticlesJets1 + pVariables->m_nParticlesJets2 + pVariables->m_nParticlesJets3 + pVariables->m_nParticlesJets4, weight);
            pTransverseMomentumPlotContainer->Fill(pVariables->m_transverseMomentum, weight);
            pCosThetaMissingPlotContainer->Fill(pVariables->m_cosThetaMissing, weight);
            pRecoilMassPlotContainer->Fill(pVariables->m_recoilMass, weight);
            pY12PlotContainer->Fill(pVariables->m_y12, weight);
            pY23PlotContainer->Fill(pVariables->m_y23, weight);
            pY34PlotContainer->Fill(pVariables->m_y34, weight);
            pY45PlotContainer->Fill(pVariables->m_y45, weight);
            pY56PlotContainer->Fill(pVariables->m_y56, weight);
            pY67PlotContainer->Fill(pVariables->m_y67, weight);
            pInvariantMassSystemPlotContainer->Fill(pVariables->m_invariantMassSystem, weight);
            pPrincipleThrustValuePlotContainer->Fill(pVariables->m_principleThrustValue, weight);
            pMajorThrustValuePlotContainer->Fill(pVariables->m_majorThrustValue, weight);
            pMinorThrustValuePlotContainer->Fill(pVariables->m_minorThrustValue, weight);
            pSphericityPlotContainer->Fill(pVariables->m_sphericity, weight);
            pAplanarityPlotContainer->Fill(pVariables->m_aplanarity, weight);
            pNumberOfIsolatedLeptons->Fill(pVariables->m_nIsolatedLeptons, weight);
            pHighestEnergyIsolatedLeptonEnergy->Fill(pVariables->m_highestEnergyIsolatedLeptonE, weight);
            pHighestEnergyIsolatedLeptonMomentum->Fill(pVariables->m_highestEnergyIsolatedLeptonP, weight);
            pHighestEnergyIsolatedLeptonTransverseMomentum->Fill(pVariables->m_highestEnergyIsolatedLeptonPt, weight);
            pHighestEnergyIsolatedLeptonCosTheta->Fill(pVariables->m_highestEnergyIsolatedLeptonCosTheta, weight);
            pHighestEnergyPfoEnergy->Fill(pVariables->m_highestEnergyPfoE, weight);
            pHighestEnergyPfoMomentum->Fill(pVariables->m_highestEnergyPfoP, weight);
            pHighestEnergyPfoTransverseMomentum->Fill(pVariables->m_highestEnergyPfoPt, weight);
            pHighestEnergyPfoCosTheta->Fill(pVariables->m_highestEnergyPfoCosTheta, weight);
            pHighestEnergyElectronEnergy->Fill(pVariables->m_highestEnergyElectronE, weight);
            pHighestEnergyElectronMomentum->Fill(pVariables->m_highestEnergyElectronP, weight);
            pHighestEnergyElectronTransverseMomentum->Fill(pVariables->m_highestEnergyElectronPt, weight);
            pHighestEnergyElectronCosTheta->Fill(pVariables->m_highestEnergyElectronCosTheta, weight);
            pHighestEnergyMuonEnergy->Fill(pVariables->m_highestEnergyMuonE, weight);
            pHighestEnergyMuonMomentum->Fill(pVariables->m_highestEnergyMuonP, weight);
            pHighestEnergyMuonTransverseMomentum->Fill(pVariables->m_highestEnergyMuonPt, weight);
            pHighestEnergyMuonCosTheta->Fill(pVariables->m_highestEnergyMuonCosTheta, weight);
            pHighestEnergyPhotonEnergy->Fill(pVariables->m_highestEnergyPhotonE, weight);
            pHighestEnergyPhotonMomentum->Fill(pVariables->m_highestEnergyPhotonP, weight);
            pHighestEnergyPhotonTransverseMomentum->Fill(pVariables->m_highestEnergyPhotonPt, weight);
            pHighestEnergyPhotonCosTheta->Fill(pVariables->m_highestEnergyPhotonCosTheta, weight);

            // Bosons
            pNPfosSynBosonPlotContainer->Fill(pVariables->m_nPfosBosonSyn1, weight);
            pNPfosSynBosonPlotContainer->Fill(pVariables->m_nPfosBosonSyn2, weight);
            pEnergySynBosonPlotContainer->Fill(pVariables->m_energyBosonSyn1, weight);
            pEnergySynBosonPlotContainer->Fill(pVariables->m_energyBosonSyn2, weight);
            pMomentumSynBosonPlotContainer->Fill(pVariables->m_momentumBosonSyn1, weight);
            pMomentumSynBosonPlotContainer->Fill(pVariables->m_momentumBosonSyn2, weight);
            pTransverseMomentumSynBosonPlotContainer->Fill(pVariables->m_transverseMomentumBosonSyn1, weight);
            pTransverseMomentumSynBosonPlotContainer->Fill(pVariables->m_transverseMomentumBosonSyn2, weight);
            pCosThetaSynBosonPlotContainer->Fill(pVariables->m_cosThetaBosonSyn1, weight);
            pCosThetaSynBosonPlotContainer->Fill(pVariables->m_cosThetaBosonSyn2, weight);
            pCosThetaStarSynBosonsPlotContainer->Fill(pVariables->m_cosThetaStarSynBosons, weight);
            pAcolinearitySynBosonsPlotContainer->Fill(pVariables->m_acolinearityBosonsSyn, weight);
            pInvariantMassSynBosonsPlotContainer->Fill(pVariables->m_invariantMassSynBosons1, weight);
            pInvariantMassSynBosonsPlotContainer->Fill(pVariables->m_invariantMassSynBosons2, weight);
            pHighestBTagSynBosonsPlotContainer->Fill(pVariables->m_maxBTagForBosonSyn1, weight);
            pHighestBTagSynBosonsPlotContainer->Fill(pVariables->m_maxBTagForBosonSyn2, weight);
            pLowestBTagSynBosonsPlotContainer->Fill(pVariables->m_minBTagForBosonSyn1, weight);
            pLowestBTagSynBosonsPlotContainer->Fill(pVariables->m_minBTagForBosonSyn2, weight);
            pHighestCTagSynBosonsPlotContainer->Fill(pVariables->m_maxCTagForBosonSyn1, weight);
            pHighestCTagSynBosonsPlotContainer->Fill(pVariables->m_maxCTagForBosonSyn2, weight);
            pLowestCTagSynBosonsPlotContainer->Fill(pVariables->m_minCTagForBosonSyn1, weight);
            pLowestCTagSynBosonsPlotContainer->Fill(pVariables->m_minCTagForBosonSyn2, weight);

            // Jets
            pAcolinearitySynJetsPlotContainer->Fill(pVariables->m_acolinearityJetsSyn1, weight);
            pAcolinearitySynJetsPlotContainer->Fill(pVariables->m_acolinearityJetsSyn2, weight);
            pCosThetaStarSynJetsPlotContainer->Fill(pVariables->m_cosThetaStarSynJets1, weight);
            pCosThetaStarSynJetsPlotContainer->Fill(pVariables->m_cosThetaStarSynJets2, weight);
            pEnergySynJetsPlotContainer->Fill(pVariables->m_energyJets1, weight);
            pEnergySynJetsPlotContainer->Fill(pVariables->m_energyJets2, weight);
            pEnergySynJetsPlotContainer->Fill(pVariables->m_energyJets3, weight);
            pEnergySynJetsPlotContainer->Fill(pVariables->m_energyJets4, weight);
            pMomentumSynJetsPlotContainer->Fill(pVariables->m_momentumJets1, weight);
            pMomentumSynJetsPlotContainer->Fill(pVariables->m_momentumJets2, weight);
            pMomentumSynJetsPlotContainer->Fill(pVariables->m_momentumJets3, weight);
            pMomentumSynJetsPlotContainer->Fill(pVariables->m_momentumJets4, weight);
            pTransverseMomentumSynJetsPlotContainer->Fill(pVariables->m_transverseMomentumJets1, weight);
            pTransverseMomentumSynJetsPlotContainer->Fill(pVariables->m_transverseMomentumJets2, weight);
            pTransverseMomentumSynJetsPlotContainer->Fill(pVariables->m_transverseMomentumJets3, weight);
            pTransverseMomentumSynJetsPlotContainer->Fill(pVariables->m_transverseMomentumJets4, weight);
            pCosThetaSynJetsPlotContainer->Fill(pVariables->m_cosThetaJets1, weight);
            pCosThetaSynJetsPlotContainer->Fill(pVariables->m_cosThetaJets2, weight);
            pCosThetaSynJetsPlotContainer->Fill(pVariables->m_cosThetaJets3, weight);
            pCosThetaSynJetsPlotContainer->Fill(pVariables->m_cosThetaJets4, weight);
        }

        // Event
        pNPfosPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseMomentumPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaMissingPlotContainer->DrawHistograms(pProcess->GetEventType());
        pRecoilMassPlotContainer->DrawHistograms(pProcess->GetEventType());
        pY12PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY23PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY34PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY45PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY56PlotContainer->DrawHistograms(pProcess->GetEventType());
        pY67PlotContainer->DrawHistograms(pProcess->GetEventType());
        pInvariantMassSystemPlotContainer->DrawHistograms(pProcess->GetEventType());
        pPrincipleThrustValuePlotContainer->DrawHistograms(pProcess->GetEventType());
        pMajorThrustValuePlotContainer->DrawHistograms(pProcess->GetEventType());
        pMinorThrustValuePlotContainer->DrawHistograms(pProcess->GetEventType());
        pSphericityPlotContainer->DrawHistograms(pProcess->GetEventType());
        pAplanarityPlotContainer->DrawHistograms(pProcess->GetEventType());
        pNumberOfIsolatedLeptons->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyIsolatedLeptonEnergy->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyIsolatedLeptonMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyIsolatedLeptonTransverseMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyIsolatedLeptonCosTheta->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyPfoEnergy->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyPfoMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyPfoTransverseMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyPfoCosTheta->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyElectronEnergy->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyElectronMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyElectronTransverseMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyElectronCosTheta->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyMuonEnergy->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyMuonMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyMuonTransverseMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyMuonCosTheta->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyPhotonEnergy->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyPhotonMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyPhotonTransverseMomentum->DrawHistograms(pProcess->GetEventType());
        pHighestEnergyPhotonCosTheta->DrawHistograms(pProcess->GetEventType());

        // Bosons
        pNPfosSynBosonPlotContainer->DrawHistograms(pProcess->GetEventType());
        pEnergySynBosonPlotContainer->DrawHistograms(pProcess->GetEventType());
        pMomentumSynBosonPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseMomentumSynBosonPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaSynBosonPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaStarSynBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pAcolinearitySynBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pInvariantMassSynBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pHighestBTagSynBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pLowestBTagSynBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pHighestCTagSynBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pLowestCTagSynBosonsPlotContainer->DrawHistograms(pProcess->GetEventType());

        // Jets
        pAcolinearitySynJetsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaStarSynJetsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pEnergySynJetsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pMomentumSynJetsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pTransverseMomentumSynJetsPlotContainer->DrawHistograms(pProcess->GetEventType());
        pCosThetaSynJetsPlotContainer->DrawHistograms(pProcess->GetEventType());
    }

    // Event
    pNPfosPlotContainer->SavePlots();
    pTransverseMomentumPlotContainer->SavePlots();
    pCosThetaMissingPlotContainer->SavePlots();
    pRecoilMassPlotContainer->SavePlots();
    pY12PlotContainer->SavePlots();
    pY23PlotContainer->SavePlots();
    pY34PlotContainer->SavePlots();
    pY45PlotContainer->SavePlots();
    pY56PlotContainer->SavePlots();
    pY67PlotContainer->SavePlots();
    pInvariantMassSystemPlotContainer->SavePlots();
    pPrincipleThrustValuePlotContainer->SavePlots();
    pMajorThrustValuePlotContainer->SavePlots();
    pMinorThrustValuePlotContainer->SavePlots();
    pSphericityPlotContainer->SavePlots();
    pAplanarityPlotContainer->SavePlots();
    pNumberOfIsolatedLeptons->SavePlots();
    pHighestEnergyIsolatedLeptonEnergy->SavePlots();
    pHighestEnergyIsolatedLeptonMomentum->SavePlots();
    pHighestEnergyIsolatedLeptonTransverseMomentum->SavePlots();
    pHighestEnergyIsolatedLeptonCosTheta->SavePlots();
    pHighestEnergyPfoEnergy->SavePlots();
    pHighestEnergyPfoMomentum->SavePlots();
    pHighestEnergyPfoTransverseMomentum->SavePlots();
    pHighestEnergyPfoCosTheta->SavePlots();
    pHighestEnergyElectronEnergy->SavePlots();
    pHighestEnergyElectronMomentum->SavePlots();
    pHighestEnergyElectronTransverseMomentum->SavePlots();
    pHighestEnergyElectronCosTheta->SavePlots();
    pHighestEnergyMuonEnergy->SavePlots();
    pHighestEnergyMuonMomentum->SavePlots();
    pHighestEnergyMuonTransverseMomentum->SavePlots();
    pHighestEnergyMuonCosTheta->SavePlots();
    pHighestEnergyPhotonEnergy->SavePlots();
    pHighestEnergyPhotonMomentum->SavePlots();
    pHighestEnergyPhotonTransverseMomentum->SavePlots();
    pHighestEnergyPhotonCosTheta->SavePlots();

    // Bosons
    pNPfosSynBosonPlotContainer->SavePlots();
    pEnergySynBosonPlotContainer->SavePlots();
    pMomentumSynBosonPlotContainer->SavePlots();
    pTransverseMomentumSynBosonPlotContainer->SavePlots();
    pCosThetaSynBosonPlotContainer->SavePlots();
    pCosThetaStarSynBosonsPlotContainer->SavePlots();
    pAcolinearitySynBosonsPlotContainer->SavePlots();
    pInvariantMassSynBosonsPlotContainer->SavePlots();
    pHighestBTagSynBosonsPlotContainer->SavePlots();
    pLowestBTagSynBosonsPlotContainer->SavePlots();
    pHighestCTagSynBosonsPlotContainer->SavePlots();
    pLowestCTagSynBosonsPlotContainer->SavePlots();

    // Jets
    pAcolinearitySynJetsPlotContainer->SavePlots();
    pCosThetaStarSynJetsPlotContainer->SavePlots();
    pEnergySynJetsPlotContainer->SavePlots();
    pMomentumSynJetsPlotContainer->SavePlots();
    pTransverseMomentumSynJetsPlotContainer->SavePlots();
    pCosThetaSynJetsPlotContainer->SavePlots();
}

//=====================================================================

MakeDerivedPlots::PlotContainer::PlotContainer(std::string descriptor, std::string variableName, int nBins, double xLow, double xHigh) :
    m_variableName(variableName),
    m_descriptor(descriptor),
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

    if (m_pTH1F->GetEntries() > 0)
    {
        TH1F *pCloneTH1F = (TH1F*)(m_pTH1F->Clone());
        pCloneTH1F->Scale(1/pCloneTH1F->Integral());
        pCloneTH1F->Draw("same");

        pTLegend->AddEntry(m_pTH1F, processName.c_str(), "f");
        pTLegend->Draw("same");

        m_pTHStack->Add(m_pTH1F);
        m_pTLegend->AddEntry(m_pTH1F, processName.c_str(), "f");
    }
    m_pTH1F = new TH1F(this->RandomName().c_str(), m_variableName.c_str(), m_nBins, m_xLow, m_xHigh);
}

//=====================================================================

void MakeDerivedPlots::PlotContainer::SavePlots()
{
    std::string plotName = m_variableName + "_" + m_descriptor + "_MultiPlot.C";
    gStyle->SetOptStat(0);
    m_pTCanvas->cd();
    TLegend *pTLegendClone = (TLegend*)(m_pTLegend->Clone());
    pTLegendClone->DrawBox(0,0,1,1);
    m_pTCanvas->SetLogy();
    m_pTCanvas->Update();
    m_pTCanvas->SaveAs(plotName.c_str());

    plotName = m_variableName + "_" + m_descriptor + "_StackPlot.C";
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
