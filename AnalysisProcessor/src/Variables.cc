/**
 *  @file   SelectionProcessor/src/Variables.cc 
 * 
 *  @brief  Implementation of the variables class.
 * 
 *  $Log: $
 */

#include "Variables.h"

using namespace variables_namespace;

//===========================================================

Variables::Variables(const double eventEnergyMC) : 
    m_appropriateEvent(false),
    m_isEventWW(false),
    m_isEventWWMC(false),
    m_isEventZZ(false),
    m_isEventZZMC(false),
    m_nPfosBosonW1(std::numeric_limits<int>::max()),
    m_nPfosBosonW2(std::numeric_limits<int>::max()),
    m_nPfosBosonZ1(std::numeric_limits<int>::max()),
    m_nPfosBosonZ2(std::numeric_limits<int>::max()),
    m_highestEnergyPfoPDG(std::numeric_limits<int>::max()),
    m_nIsolatedLeptons(std::numeric_limits<int>::max()),
    m_highestEnergyIsolatedLeptonPDG(std::numeric_limits<int>::max()),
    m_secondHighestEnergyIsolatedLeptonPDG(std::numeric_limits<int>::max()),
    m_eventEnergyMC(eventEnergyMC),
    m_transverseMomentum(std::numeric_limits<double>::max()),
    m_transverseMomentumMC(std::numeric_limits<double>::max()),
    m_transverseEnergy(std::numeric_limits<double>::max()),
    m_transverseEnergyMC(std::numeric_limits<double>::max()),
    m_energyBosonW1(std::numeric_limits<double>::max()),
    m_energyBosonW2(std::numeric_limits<double>::max()),
    m_energyBosonZ1(std::numeric_limits<double>::max()),
    m_energyBosonZ2(std::numeric_limits<double>::max()),
    m_momentumBosonW1(std::numeric_limits<double>::max()),
    m_momentumBosonW2(std::numeric_limits<double>::max()),
    m_momentumBosonZ1(std::numeric_limits<double>::max()),
    m_momentumBosonZ2(std::numeric_limits<double>::max()),
    m_transverseMomentumBosonW1(std::numeric_limits<double>::max()),
    m_transverseMomentumBosonW2(std::numeric_limits<double>::max()),
    m_transverseMomentumBosonZ1(std::numeric_limits<double>::max()),
    m_transverseMomentumBosonZ2(std::numeric_limits<double>::max()),
    m_cosThetaBosonW1(std::numeric_limits<double>::max()),
    m_cosThetaBosonW2(std::numeric_limits<double>::max()),
    m_cosThetaBosonZ1(std::numeric_limits<double>::max()),
    m_cosThetaBosonZ2(std::numeric_limits<double>::max()),
    m_transverseEnergyBosonW1(std::numeric_limits<double>::max()),
    m_transverseEnergyBosonW2(std::numeric_limits<double>::max()),
    m_transverseEnergyBosonZ1(std::numeric_limits<double>::max()),
    m_transverseEnergyBosonZ2(std::numeric_limits<double>::max()),
    m_cosThetaMissing(std::numeric_limits<double>::max()),
    m_cosThetaMissingMC(std::numeric_limits<double>::max()),
    m_cosThetaMostEnergeticTrack(std::numeric_limits<double>::max()),
    m_recoilMass(std::numeric_limits<double>::max()),
    m_recoilMassMC(std::numeric_limits<double>::max()),
    m_energyAroundMostEnergeticPfo(std::numeric_limits<double>::max()),
    m_y12(std::numeric_limits<double>::max()),
    m_y23(std::numeric_limits<double>::max()),
    m_y34(std::numeric_limits<double>::max()),
    m_y45(std::numeric_limits<double>::max()),
    m_y56(std::numeric_limits<double>::max()),
    m_y67(std::numeric_limits<double>::max()),
    m_invariantMassSystem(std::numeric_limits<double>::max()),
    m_invariantMassSystemMC(std::numeric_limits<double>::max()),
    m_cosThetaStarWBosons(std::numeric_limits<double>::max()),
    m_cosThetaStarWBosonsMC(std::numeric_limits<double>::max()),
    m_cosThetaStarZBosons(std::numeric_limits<double>::max()),
    m_cosThetaStarZBosonsMC(std::numeric_limits<double>::max()),
    m_acolinearityJetsW1(std::numeric_limits<double>::max()),
    m_acolinearityJetsW2(std::numeric_limits<double>::max()),
    m_acolinearityJetsZ1(std::numeric_limits<double>::max()),
    m_acolinearityJetsZ2(std::numeric_limits<double>::max()),
    m_acolinearityBosonsW(std::numeric_limits<double>::max()),
    m_acolinearityBosonsZ(std::numeric_limits<double>::max()),
    m_principleThrustValue(std::numeric_limits<double>::max()),
    m_majorThrustValue(std::numeric_limits<double>::max()),
    m_minorThrustValue(std::numeric_limits<double>::max()),
    m_xThrustAxis(std::numeric_limits<double>::max()),
    m_yThrustAxis(std::numeric_limits<double>::max()),
    m_zThrustAxis(std::numeric_limits<double>::max()),
    m_sphericity(std::numeric_limits<double>::max()),
    m_aplanarity(std::numeric_limits<double>::max()),
    m_highestEnergyElectronE(std::numeric_limits<double>::max()),
    m_highestEnergyElectronP(std::numeric_limits<double>::max()),
    m_highestEnergyElectronPt(std::numeric_limits<double>::max()),
    m_highestEnergyElectronCosTheta(std::numeric_limits<double>::max()),
    m_highestEnergyMuonE(std::numeric_limits<double>::max()),
    m_highestEnergyMuonP(std::numeric_limits<double>::max()),
    m_highestEnergyMuonPt(std::numeric_limits<double>::max()),
    m_highestEnergyMuonCosTheta(std::numeric_limits<double>::max()),
    m_highestEnergyPhotonE(std::numeric_limits<double>::max()),
    m_highestEnergyPhotonP(std::numeric_limits<double>::max()),
    m_highestEnergyPhotonPt(std::numeric_limits<double>::max()),
    m_highestEnergyPhotonCosTheta(std::numeric_limits<double>::max()),
    m_highestEnergyPfoE(std::numeric_limits<double>::max()),
    m_highestEnergyPfoP(std::numeric_limits<double>::max()),
    m_highestEnergyPfoPt(std::numeric_limits<double>::max()),
    m_highestEnergyPfoCosTheta(std::numeric_limits<double>::max()),
    m_highestEnergyIsolatedLeptonE(std::numeric_limits<double>::max()),
    m_highestEnergyIsolatedLeptonP(std::numeric_limits<double>::max()),
    m_highestEnergyIsolatedLeptonPt(std::numeric_limits<double>::max()),
    m_highestEnergyIsolatedLeptonCosTheta(std::numeric_limits<double>::max()),
    m_secondHighestEnergyIsolatedLeptonE(std::numeric_limits<double>::max()),
    m_secondHighestEnergyIsolatedLeptonP(std::numeric_limits<double>::max()),
    m_secondHighestEnergyIsolatedLeptonPt(std::numeric_limits<double>::max()),
    m_secondHighestEnergyIsolatedLeptonCosTheta(std::numeric_limits<double>::max()),
    m_maxBTagForBosonW1(std::numeric_limits<double>::max()),
    m_minBTagForBosonW1(std::numeric_limits<double>::max()),
    m_maxBTagForBosonW2(std::numeric_limits<double>::max()),
    m_minBTagForBosonW2(std::numeric_limits<double>::max()),
    m_maxCTagForBosonW1(std::numeric_limits<double>::max()),
    m_minCTagForBosonW1(std::numeric_limits<double>::max()),
    m_maxCTagForBosonW2(std::numeric_limits<double>::max()),
    m_minCTagForBosonW2(std::numeric_limits<double>::max()),
    m_maxBTagForBosonZ1(std::numeric_limits<double>::max()),
    m_minBTagForBosonZ1(std::numeric_limits<double>::max()),
    m_maxBTagForBosonZ2(std::numeric_limits<double>::max()),
    m_minBTagForBosonZ2(std::numeric_limits<double>::max()),
    m_maxCTagForBosonZ1(std::numeric_limits<double>::max()),
    m_minCTagForBosonZ1(std::numeric_limits<double>::max()),
    m_maxCTagForBosonZ2(std::numeric_limits<double>::max()),
    m_minCTagForBosonZ2(std::numeric_limits<double>::max())
{
}

//===========================================================

Variables::~Variables()
{
}

//===========================================================

void Variables::SetBranches(TTree *pTTree)
{
    gInterpreter->EnableAutoLoading();

// Variables Of Interest
// Bools
    pTTree->Branch("IsAppropriateEvent", &m_appropriateEvent, "IsAppropriateEvent/O");
    pTTree->Branch("IsEventWW", &m_isEventWW, "IsEventWW/O");
    pTTree->Branch("IsMCEventWW", &m_isEventWWMC, "IsMCEventWW/O");
    pTTree->Branch("IsEventZZ", &m_isEventZZ, "IsEventZZ/O");
    pTTree->Branch("IsMCEventZZ", &m_isEventZZMC, "IsMCEventZZ/O");

// Ints
    pTTree->Branch("NPfosBosonW1", &m_nPfosBosonW1, "NPfosBosonW1/I");
    pTTree->Branch("NPfosBosonW2", &m_nPfosBosonW2, "NPfosBosonW2/I");
    pTTree->Branch("NPfosBosonZ1", &m_nPfosBosonZ1, "NPfosBosonZ1/I");
    pTTree->Branch("NPfosBosonZ2", &m_nPfosBosonZ2, "NPfosBosonZ2/I");
    m_combinationWJets.resize(4);
    pTTree->Branch("WBosonJet1Is", &m_combinationWJets.at(0), "WBosonJet1Is/I");
    pTTree->Branch("WBosonJet2Is", &m_combinationWJets.at(1), "WBosonJet2Is/I");
    pTTree->Branch("WBosonJet3Is", &m_combinationWJets.at(2), "WBosonJet3Is/I");
    pTTree->Branch("WBosonJet4Is", &m_combinationWJets.at(3), "WBosonJet4Is/I");
    m_combinationZJets.resize(4);
    pTTree->Branch("ZBosonJet1Is", &m_combinationZJets.at(0), "ZBosonJet1Is/I");
    pTTree->Branch("ZBosonJet2Is", &m_combinationZJets.at(1), "ZBosonJet2Is/I");
    pTTree->Branch("ZBosonJet3Is", &m_combinationZJets.at(2), "ZBosonJet3Is/I");
    pTTree->Branch("ZBosonJet4Is", &m_combinationZJets.at(3), "ZBosonJet4Is/I");
    m_combinationSynergyJets.resize(4);
    pTTree->Branch("SynergyBosonJet1Is", &m_combinationSynergyJets.at(0), "SynergyBosonJet1Is/I");
    pTTree->Branch("SynergyBosonJet2Is", &m_combinationSynergyJets.at(1), "SynergyBosonJet2Is/I");
    pTTree->Branch("SynergyBosonJet3Is", &m_combinationSynergyJets.at(2), "SynergyBosonJet3Is/I");
    pTTree->Branch("SynergyBosonJet4Is", &m_combinationSynergyJets.at(3), "SynergyBosonJet4Is/I");
    m_nParticlesJets.resize(4);
    pTTree->Branch("NParticlesJet1", &m_nParticlesJets.at(0), "NParticlesJet1/I");
    pTTree->Branch("NParticlesJet2", &m_nParticlesJets.at(1), "NParticlesJet2/I");
    pTTree->Branch("NParticlesJet3", &m_nParticlesJets.at(2), "NParticlesJet3/I");
    pTTree->Branch("NParticlesJet4", &m_nParticlesJets.at(3), "NParticlesJet4/I");
    m_nChargedParticlesJets.resize(4);
    pTTree->Branch("NChargedParticlesJet1", &m_nChargedParticlesJets.at(0), "NChargedParticlesJet1/I");
    pTTree->Branch("NChargedParticlesJet2", &m_nChargedParticlesJets.at(1), "NChargedParticlesJet2/I");
    pTTree->Branch("NChargedParticlesJet3", &m_nChargedParticlesJets.at(2), "NChargedParticlesJet3/I");
    pTTree->Branch("NChargedParticlesJet4", &m_nChargedParticlesJets.at(3), "NChargedParticlesJet4/I");
    pTTree->Branch("HighestEnergyPfoPDG", &m_highestEnergyPfoPDG, "HighestEnergyPfoPDG/I");
    pTTree->Branch("NumberOfIsolatedLeptons", &m_nIsolatedLeptons, "NumberOfIsolatedLeptons/I");
    pTTree->Branch("HighestEnergyIsolatedLeptonPDG", &m_highestEnergyIsolatedLeptonPDG, "HighestEnergyIsolatedLeptonPDG/I");
    pTTree->Branch("SecondHighestEnergyIsolatedLeptonPDG", &m_secondHighestEnergyIsolatedLeptonPDG, "SecondHighestEnergyIsolatedLeptonPDG/I");

// IntVectors
//    pTTree->Branch("NParticlesJets", &m_nParticlesJets);
//    pTTree->Branch("NChargedParticlesJets", &m_nChargedParticlesJets);

// Floats
    pTTree->Branch("MCEventEnergy", &m_eventEnergyMC, "MCEventEnergy/D");
    pTTree->Branch("TransverseMomentum", &m_transverseMomentum, "TransverseMomentum/D");
    pTTree->Branch("MCTransverseMomentum", &m_transverseMomentumMC, "MCTransverseMomentum/D");
    pTTree->Branch("TransverseEnergy", &m_transverseEnergy, "TransverseEnergy/D");
    pTTree->Branch("MCTransverseEnergy", &m_transverseEnergyMC, "MCTransverseEnergy/D");
    pTTree->Branch("EnergyBosonW1", &m_energyBosonW1, "EnergyBosonW1/D");
    pTTree->Branch("EnergyBosonW2", &m_energyBosonW2, "EnergyBosonW2/D");
    pTTree->Branch("EnergyBosonZ1", &m_energyBosonZ1, "EnergyBosonZ1/D");
    pTTree->Branch("EnergyBosonZ2", &m_energyBosonZ2, "EnergyBosonZ2/D");
    pTTree->Branch("MomentumBosonW1", &m_momentumBosonW1, "MomentumBosonW1/D");
    pTTree->Branch("MomentumBosonW2", &m_momentumBosonW2, "MomentumBosonW2/D");
    pTTree->Branch("MomentumBosonZ1", &m_momentumBosonZ1, "MomentumBosonZ1/D");
    pTTree->Branch("MomentumBosonZ2", &m_momentumBosonZ2, "MomentumBosonZ2/D");
    pTTree->Branch("TransverseMomentumBosonW1", &m_transverseMomentumBosonW1, "TransverseMomentumBosonW1/D");
    pTTree->Branch("TransverseMomentumBosonW2", &m_transverseMomentumBosonW2, "TransverseMomentumBosonW2/D");
    pTTree->Branch("TransverseMomentumBosonZ1", &m_transverseMomentumBosonZ1, "TransverseMomentumBosonZ1/D");
    pTTree->Branch("TransverseMomentumBosonZ2", &m_transverseMomentumBosonZ2, "TransverseMomentumBosonZ2/D");
    pTTree->Branch("CosThetaBosonW1", &m_cosThetaBosonW1, "CosThetaBosonW1/D");
    pTTree->Branch("CosThetaBosonW2", &m_cosThetaBosonW2, "CosThetaBosonW2/D");
    pTTree->Branch("CosThetaBosonZ1", &m_cosThetaBosonZ1, "CosThetaBosonZ1/D");
    pTTree->Branch("CosThetaBosonZ2", &m_cosThetaBosonZ2, "CosThetaBosonZ2/D");
    pTTree->Branch("TransverseEnergyBosonW1", &m_transverseEnergyBosonW1, "TransverseEnergyBosonW1/D");
    pTTree->Branch("TransverseEnergyBosonW2", &m_transverseEnergyBosonW2, "TransverseEnergyBosonW2/D");
    pTTree->Branch("TransverseEnergyBosonZ1", &m_transverseEnergyBosonZ1, "TransverseEnergyBosonZ1/D");
    pTTree->Branch("TransverseEnergyBosonZ2", &m_transverseEnergyBosonZ2, "TransverseEnergyBosonZ2/D");
    pTTree->Branch("CosThetaMissing", &m_cosThetaMissing, "CosThetaMissing/D");
    pTTree->Branch("MCCosThetaMissing", &m_cosThetaMissingMC, "MCCosThetaMissing/D");
    pTTree->Branch("CosThetaMostEnergeticTrack", &m_cosThetaMostEnergeticTrack, "CosThetaMostEnergeticTrack/D");
    pTTree->Branch("RecoilMass", &m_recoilMass, "RecoilMass/D");
    pTTree->Branch("MCRecoilMass", &m_recoilMassMC, "MCRecoilMass/D");
    pTTree->Branch("EnergyAroundMostEnergeticTrack", &m_energyAroundMostEnergeticPfo, "EnergyAroundMostEnergeticTrack/D");
    pTTree->Branch("y12", &m_y12, "y12/D");
    pTTree->Branch("y23", &m_y23, "y23/D");
    pTTree->Branch("y34", &m_y34, "y34/D");
    pTTree->Branch("y45", &m_y45, "y45/D");
    pTTree->Branch("y56", &m_y56, "y56/D");
    pTTree->Branch("y67", &m_y67, "y67/D");
    pTTree->Branch("InvariantMassSystem", &m_invariantMassSystem, "InvariantMassSystem/D");
    pTTree->Branch("MCInvariantMassSystem", &m_invariantMassSystemMC, "MCInvariantMassSystem/D");
    pTTree->Branch("CosThetaStarWBosons", &m_cosThetaStarWBosons, "CosThetaStarWBosons/D");
    pTTree->Branch("MCCosThetaStarWBosons", &m_cosThetaStarWBosonsMC, "MCCosThetaStarWBosons/D");
    pTTree->Branch("CosThetaStarZBosons", &m_cosThetaStarZBosons, "CosThetaStarZBosons/D");
    pTTree->Branch("MCCosThetaStarZBosons", &m_cosThetaStarZBosonsMC, "MCCosThetaStarZBosons/D");
    pTTree->Branch("AcolinearityJetsW1", &m_acolinearityJetsW1, "AcolinearityJetsW1/D");
    pTTree->Branch("AcolinearityJetsW2", &m_acolinearityJetsW2, "AcolinearityJetsW2/D");
    pTTree->Branch("AcolinearityJetsZ1", &m_acolinearityJetsZ1, "AcolinearityJetsZ1/D");
    pTTree->Branch("AcolinearityJetsZ2", &m_acolinearityJetsZ2, "AcolinearityJetsZ2/D");
    pTTree->Branch("AcolinearityBosonsW", &m_acolinearityBosonsW, "AcolinearityBosonsW/D");
    pTTree->Branch("AcolinearityBosonsZ", &m_acolinearityBosonsZ, "AcolinearityBosonsZ/D");
    pTTree->Branch("PrincipleThrustValue", &m_principleThrustValue, "PrincipleThrustValue/D");
    pTTree->Branch("MajorThrustValue", &m_majorThrustValue, "MajorThrustValue/D");
    pTTree->Branch("MinorThrustValue", &m_minorThrustValue, "MinorThrustValue/D");
    pTTree->Branch("XThrustAxis", &m_xThrustAxis, "XThrustAxis/D");
    pTTree->Branch("YThrustAxis", &m_yThrustAxis, "YThrustAxis/D");
    pTTree->Branch("ZThrustAxis", &m_zThrustAxis, "ZThrustAxis/D");
    pTTree->Branch("Sphericity", &m_sphericity, "Sphericity/D");
    pTTree->Branch("Aplanarity", &m_aplanarity, "Aplanarity/D");
    pTTree->Branch("HighestEnergyElectronEnergy", &m_highestEnergyElectronE, "HighestEnergyElectronEnergy/D");
    pTTree->Branch("HighestEnergyElectronMomentum", &m_highestEnergyElectronP, "HighestEnergyElectronMomentum/D");
    pTTree->Branch("HighestEnergyElectronTransverseMomentum", &m_highestEnergyElectronPt, "HighestEnergyElectronTransverseMomentum/D");
    pTTree->Branch("HighestEnergyElectronCosTheta", &m_highestEnergyElectronCosTheta, "HighestEnergyElectronCosTheta/D");
    pTTree->Branch("HighestEnergyMuonEnergy", &m_highestEnergyMuonE, "HighestEnergyMuonEnergy/D");
    pTTree->Branch("HighestEnergyMuonMomentum", &m_highestEnergyMuonP, "HighestEnergyMuonMomentum/D");
    pTTree->Branch("HighestEnergyMuonTransverseMomentum", &m_highestEnergyMuonPt, "HighestEnergyMuonTransverseMomentum/D");
    pTTree->Branch("HighestEnergyMuonCosTheta", &m_highestEnergyMuonCosTheta, "HighestEnergyMuonCosTheta/D");
    pTTree->Branch("HighestEnergyPhotonEnergy", &m_highestEnergyPhotonE, "HighestEnergyPhotonEnergy/D");
    pTTree->Branch("HighestEnergyPhotonMomentum", &m_highestEnergyPhotonP, "HighestEnergyPhotonMomentum/D");
    pTTree->Branch("HighestEnergyPhotonTransverseMomentum", &m_highestEnergyPhotonPt, "HighestEnergyPhotonTransverseMomentum/D");
    pTTree->Branch("HighestEnergyPhotonCosTheta", &m_highestEnergyPhotonCosTheta, "HighestEnergyPhotonCosTheta/D");
    pTTree->Branch("HighestEnergyPfoEnergy", &m_highestEnergyPfoE, "HighestEnergyPfoEnergy/D");
    pTTree->Branch("HighestEnergyPfoMomentum", &m_highestEnergyPfoP, "HighestEnergyPfoMomentum/D");
    pTTree->Branch("HighestEnergyPfoTransverseMomentum", &m_highestEnergyPfoPt, "HighestEnergyPfoTransverseMomentum/D");
    pTTree->Branch("HighestEnergyPfoCosTheta", &m_highestEnergyPfoCosTheta, "HighestEnergyPfoCosTheta/D");
    pTTree->Branch("HighestEnergyIsolatedLeptonEnergy", &m_highestEnergyIsolatedLeptonE, "HighestEnergyIsolatedLeptonEnergy/D");
    pTTree->Branch("HighestEnergyIsolatedLeptonMomentum", &m_highestEnergyIsolatedLeptonP, "HighestEnergyIsolatedLeptonMomentum/D");
    pTTree->Branch("HighestEnergyIsolatedLeptonTransverseMomentum", &m_highestEnergyIsolatedLeptonPt, "HighestEnergyIsolatedLeptonTransverseMomentum/D");
    pTTree->Branch("HighestEnergyIsolatedLeptonCosTheta", &m_highestEnergyIsolatedLeptonCosTheta, "HighestEnergyIsolatedLeptonCosTheta/D");
    pTTree->Branch("SecondHighestEnergyIsolatedLeptonEnergy", &m_secondHighestEnergyIsolatedLeptonE, "SecondHighestEnergyIsolatedLeptonEnergy/D");
    pTTree->Branch("SecondHighestEnergyIsolatedLeptonMomentum", &m_secondHighestEnergyIsolatedLeptonP, "SecondHighestEnergyIsolatedLeptonMomentum/D");
    pTTree->Branch("SecondHighestEnergyIsolatedLeptonTransverseMomentum", &m_secondHighestEnergyIsolatedLeptonPt, "SecondHighestEnergyIsolatedLeptonTransverseMomentum/D");
    pTTree->Branch("SecondHighestEnergyIsolatedLeptonCosTheta", &m_secondHighestEnergyIsolatedLeptonCosTheta, "SecondHighestEnergyIsolatedLeptonCosTheta/D");
    m_invariantMassWBosons.resize(2);
    pTTree->Branch("InvariantMassWBoson1", &m_invariantMassWBosons.at(0), "InvariantMassWBoson1/D");
    pTTree->Branch("InvariantMassWBoson2", &m_invariantMassWBosons.at(1), "InvariantMassWBoson2/D");
    m_invariantMassWBosonsMC.resize(2);
    pTTree->Branch("MCInvariantMassWBoson1", &m_invariantMassWBosonsMC.at(0), "MCInvariantMassWBoson1/D");
    pTTree->Branch("MCInvariantMassWBoson2", &m_invariantMassWBosonsMC.at(1), "MCInvariantMassWBoson2/D");
    m_invariantMassZBosons.resize(2);
    pTTree->Branch("InvariantMassZBoson1", &m_invariantMassZBosons.at(0), "InvariantMassZBoson1/D");
    pTTree->Branch("InvariantMassZBoson2", &m_invariantMassZBosons.at(1), "InvariantMassZBoson2/D");
    m_invariantMassZBosonsMC.resize(2);
    pTTree->Branch("MCInvariantMassZBoson1", &m_invariantMassZBosonsMC.at(0), "MCInvariantMassZBoson1/D");
    pTTree->Branch("MCInvariantMassZBoson2", &m_invariantMassZBosonsMC.at(1), "MCInvariantMassZBoson2/D");
    m_invariantMassSynergyBosons.resize(2);
    pTTree->Branch("InvariantMassSynergyBoson1", &m_invariantMassSynergyBosons.at(0), "InvariantMassSynergyBoson1/D");
    pTTree->Branch("InvariantMassSynergyBoson2", &m_invariantMassSynergyBosons.at(1), "InvariantMassSynergyBoson2/D");
    m_invariantMassesAllPairings.resize(6);
    pTTree->Branch("InvariantMassBoson1Pairing0123", &m_invariantMassesAllPairings.at(0), "InvariantMassBoson1Pairing0123/D");
    pTTree->Branch("InvariantMassBoson2Pairing0123", &m_invariantMassesAllPairings.at(1), "InvariantMassBoson2Pairing0123/D");
    pTTree->Branch("InvariantMassBoson1Pairing0213", &m_invariantMassesAllPairings.at(2), "InvariantMassBoson1Pairing0213/D");
    pTTree->Branch("InvariantMassBoson2Pairing0213", &m_invariantMassesAllPairings.at(3), "InvariantMassBoson2Pairing0213/D");
    pTTree->Branch("InvariantMassBoson1Pairing0312", &m_invariantMassesAllPairings.at(4), "InvariantMassBoson1Pairing0312/D");
    pTTree->Branch("InvariantMassBoson2Pairing0312", &m_invariantMassesAllPairings.at(5), "InvariantMassBoson2Pairing0312/D");
    m_energyJets.resize(4);
    pTTree->Branch("EnergyJet1", &m_energyJets.at(0), "EnergyJet1/D");
    pTTree->Branch("EnergyJet2", &m_energyJets.at(1), "EnergyJet2/D");
    pTTree->Branch("EnergyJet3", &m_energyJets.at(2), "EnergyJet3/D");
    pTTree->Branch("EnergyJet4", &m_energyJets.at(3), "EnergyJet4/D");
    m_momentumJets.resize(4);
    pTTree->Branch("MomentumJet1", &m_momentumJets.at(0), "MomentumJet1/D");
    pTTree->Branch("MomentumJet2", &m_momentumJets.at(1), "MomentumJet2/D");
    pTTree->Branch("MomentumJet3", &m_momentumJets.at(2), "MomentumJet3/D");
    pTTree->Branch("MomentumJet4", &m_momentumJets.at(3), "MomentumJet4/D");
    m_transverseMomentumJets.resize(4);
    pTTree->Branch("TransverseMomentumJet1", &m_transverseMomentumJets.at(0), "TransverseMomentumJet1/D");
    pTTree->Branch("TransverseMomentumJet2", &m_transverseMomentumJets.at(1), "TransverseMomentumJet2/D");
    pTTree->Branch("TransverseMomentumJet3", &m_transverseMomentumJets.at(2), "TransverseMomentumJet3/D");
    pTTree->Branch("TransverseMomentumJet4", &m_transverseMomentumJets.at(3), "TransverseMomentumJet4/D");
    m_cosThetaJets.resize(4);
    pTTree->Branch("CosThetaJet1", &m_cosThetaJets.at(0), "CosThetaJet1/D");
    pTTree->Branch("CosThetaJet2", &m_cosThetaJets.at(1), "CosThetaJet2/D");
    pTTree->Branch("CosThetaJet3", &m_cosThetaJets.at(2), "CosThetaJet3/D");
    pTTree->Branch("CosThetaJet4", &m_cosThetaJets.at(3), "CosThetaJet4/D");
    m_cosThetaStarWJets.resize(2);
    pTTree->Branch("CosThetaStarWJet1", &m_cosThetaStarWJets.at(0), "CosThetaStarWJet1/D");
    pTTree->Branch("CosThetaStarWJet2", &m_cosThetaStarWJets.at(1), "CosThetaStarWJet2/D");
    m_cosThetaStarZJets.resize(2);
    pTTree->Branch("CosThetaStarZJet1", &m_cosThetaStarZJets.at(0), "CosThetaStarZJet1/D");
    pTTree->Branch("CosThetaStarZJet2", &m_cosThetaStarZJets.at(1), "CosThetaStarZJet2/D");
    m_bTagForJets.resize(4);
    pTTree->Branch("BTagForJet1", &m_bTagForJets.at(0), "BTagForJet1/D");
    pTTree->Branch("BTagForJet2", &m_bTagForJets.at(1), "BTagForJet2/D");
    pTTree->Branch("BTagForJet3", &m_bTagForJets.at(2), "BTagForJet3/D");
    pTTree->Branch("BTagForJet4", &m_bTagForJets.at(3), "BTagForJet4/D");
    m_cTagForJets.resize(4);
    pTTree->Branch("CTagForJet1", &m_cTagForJets.at(0), "CTagForJet1/D");
    pTTree->Branch("CTagForJet2", &m_cTagForJets.at(1), "CTagForJet2/D");
    pTTree->Branch("CTagForJet3", &m_cTagForJets.at(2), "CTagForJet3/D");
    pTTree->Branch("CTagForJet4", &m_cTagForJets.at(3), "CTagForJet4/D");
    pTTree->Branch("MaxBTagForBosonW1", &m_maxBTagForBosonW1, "MaxBTagForBosonW1/D");
    pTTree->Branch("MinBTagForBosonW1", &m_minBTagForBosonW1, "MinBTagForBosonW1/D");
    pTTree->Branch("MaxBTagForBosonW2", &m_maxBTagForBosonW2, "MaxBTagForBosonW2/D");
    pTTree->Branch("MinBTagForBosonW2", &m_minBTagForBosonW2, "MinBTagForBosonW2/D");
    pTTree->Branch("MaxCTagForBosonW1", &m_maxCTagForBosonW1, "MaxCTagForBosonW1/D");
    pTTree->Branch("MinCTagForBosonW1", &m_minCTagForBosonW1, "MinCTagForBosonW1/D");
    pTTree->Branch("MaxCTagForBosonW2", &m_maxCTagForBosonW2, "MaxCTagForBosonW2/D");
    pTTree->Branch("MinCTagForBosonW2", &m_minCTagForBosonW2, "MinCTagForBosonW2/D");
    pTTree->Branch("MaxBTagForBosonZ1", &m_maxBTagForBosonZ1, "MaxBTagForBosonZ1/D");
    pTTree->Branch("MinBTagForBosonZ1", &m_minBTagForBosonZ1, "MinBTagForBosonZ1/D");
    pTTree->Branch("MaxBTagForBosonZ2", &m_maxBTagForBosonZ2, "MaxBTagForBosonZ2/D");
    pTTree->Branch("MinBTagForBosonZ2", &m_minBTagForBosonZ2, "MinBTagForBosonZ2/D");
    pTTree->Branch("MaxCTagForBosonZ1", &m_maxCTagForBosonZ1, "MaxCTagForBosonZ1/D");
    pTTree->Branch("MinCTagForBosonZ1", &m_minCTagForBosonZ1, "MinCTagForBosonZ1/D");
    pTTree->Branch("MaxCTagForBosonZ2", &m_maxCTagForBosonZ2, "MaxCTagForBosonZ2/D");
    pTTree->Branch("MinCTagForBosonZ2", &m_minCTagForBosonZ2, "MinCTagForBosonZ2/D");
    m_energyNeutrinos.resize(2);
    m_pxMomentumNeutrinos.resize(2);
    m_pyMomentumNeutrinos.resize(2);
    m_pzMomentumNeutrinos.resize(2);
    pTTree->Branch("NeutrinoEnergy1", &m_energyNeutrinos.at(0), "NeutrinoEnergy1/D");
    pTTree->Branch("NeutrinoPx1", &m_pxMomentumNeutrinos.at(0), "NeutrinoPx1/D");
    pTTree->Branch("NeutrinoPy1", &m_pyMomentumNeutrinos.at(0), "NeutrinoPy1/D");
    pTTree->Branch("NeutrinoPz1", &m_pzMomentumNeutrinos.at(0), "NeutrinoPz1/D");
    pTTree->Branch("NeutrinoEnergy2", &m_energyNeutrinos.at(1), "NeutrinoEnergy2/D");
    pTTree->Branch("NeutrinoPx2", &m_pxMomentumNeutrinos.at(1), "NeutrinoPx2/D");
    pTTree->Branch("NeutrinoPy2", &m_pyMomentumNeutrinos.at(1), "NeutrinoPy2/D");
    pTTree->Branch("NeutrinoPz2", &m_pzMomentumNeutrinos.at(1), "NeutrinoPz2/D");
    m_energyQuarks.resize(4);
    m_pxMomentumQuarks.resize(4);
    m_pyMomentumQuarks.resize(4);
    m_pzMomentumQuarks.resize(4);
    pTTree->Branch("QuarkEnergy1", &m_energyQuarks.at(0), "QuarkEnergy1/D");
    pTTree->Branch("QuarkPx1", &m_pxMomentumQuarks.at(0), "QuarkPx1/D");
    pTTree->Branch("QuarkPy1", &m_pyMomentumQuarks.at(0), "QuarkPy1/D");
    pTTree->Branch("QuarkPz1", &m_pzMomentumQuarks.at(0), "QuarkPz1/D");
    pTTree->Branch("QuarkEnergy2", &m_energyQuarks.at(1), "QuarkEnergy2/D");
    pTTree->Branch("QuarkPx2", &m_pxMomentumQuarks.at(1), "QuarkPx2/D");
    pTTree->Branch("QuarkPy2", &m_pyMomentumQuarks.at(1), "QuarkPy2/D");
    pTTree->Branch("QuarkPz2", &m_pzMomentumQuarks.at(1), "QuarkPz2/D");
    pTTree->Branch("QuarkEnergy3", &m_energyQuarks.at(2), "QuarkEnergy3/D");
    pTTree->Branch("QuarkPx3", &m_pxMomentumQuarks.at(2), "QuarkPx3/D");
    pTTree->Branch("QuarkPy3", &m_pyMomentumQuarks.at(2), "QuarkPy3/D");
    pTTree->Branch("QuarkPz3", &m_pzMomentumQuarks.at(2), "QuarkPz3/D");
    pTTree->Branch("QuarkEnergy4", &m_energyQuarks.at(3), "QuarkEnergy4/D");
    pTTree->Branch("QuarkPx4", &m_pxMomentumQuarks.at(3), "QuarkPx4/D");
    pTTree->Branch("QuarkPy4", &m_pyMomentumQuarks.at(3), "QuarkPy4/D");
    pTTree->Branch("QuarkPz4", &m_pzMomentumQuarks.at(3), "QuarkPz4/D");
    m_cheatedInvariantMasses.resize(2);
    pTTree->Branch("CheatedInvariantMass1", &m_cheatedInvariantMasses.at(0), "CheatedInvariantMass1/D");
    pTTree->Branch("CheatedInvariantMass2", &m_cheatedInvariantMasses.at(1), "CheatedInvariantMass2/D");
    m_cheatedMCInvariantMasses.resize(2);
    pTTree->Branch("CheatedMCInvariantMass1", &m_cheatedMCInvariantMasses.at(0), "CheatedMCInvariantMass1/D");
    pTTree->Branch("CheatedMCInvariantMass2", &m_cheatedMCInvariantMasses.at(1), "CheatedMCInvariantMass2/D");

//    pTTree->Branch("", &, "/D");
// DoubleVectors
//    pTTree->Branch("InvariantMassWBosons", &m_invariantMassWBosons);
//    pTTree->Branch("MCInvariantMassWBosons", &m_invariantMassWBosonsMC);
//    pTTree->Branch("InvariantMassZBosons", &m_invariantMassZBosons);
//    pTTree->Branch("MCInvariantMassZBosons", &m_invariantMassZBosonsMC);
//    pTTree->Branch("EnergyJets", &m_energyJets);
//    pTTree->Branch("CosThetaStarWJets", &m_cosThetaStarWJets);
//    pTTree->Branch("CosThetaStarZJets", &m_cosThetaStarZJets);
}

//===========================================================

void Variables::Print()
{
    std::cout << "m_appropriateEvent             : " << m_appropriateEvent << std::endl;
    std::cout << "m_isEventWW                    : " << m_isEventWW << std::endl;
    std::cout << "m_isEventWWMC                  : " << m_isEventWWMC << std::endl;
    std::cout << "m_isEventZZ                    : " << m_isEventZZ << std::endl;
    std::cout << "m_isEventZZMC                  : " << m_isEventZZMC << std::endl;

    for (IntVector::iterator iter = m_nParticlesJets.begin(); iter != m_nParticlesJets.end(); iter++)
    {
        std::cout << "m_nParticlesJets, position " << iter-m_nParticlesJets.begin() << " : " << *iter << std::endl;
    }

    for (IntVector::iterator iter = m_nChargedParticlesJets.begin(); iter != m_nChargedParticlesJets.end(); iter++)
    {
        std::cout << "m_nChargedParticlesJets, position " << iter-m_nChargedParticlesJets.begin() << " : " << *iter << std::endl;
    }

    std::cout << "m_transverseMomentum           : " << m_transverseMomentum << std::endl;
    std::cout << "m_transverseMomentumMC         : " << m_transverseMomentumMC << std::endl;
    std::cout << "m_transverseEnergy             : " << m_transverseEnergy << std::endl;
    std::cout << "m_transverseEnergyMC           : " << m_transverseEnergyMC << std::endl;
    std::cout << "m_cosThetaMissing              : " << m_cosThetaMissing << std::endl;
    std::cout << "m_cosThetaMissingMC            : " << m_cosThetaMissingMC << std::endl;
    std::cout << "m_cosThetaMostEnergeticTrack   : " << m_cosThetaMostEnergeticTrack << std::endl;
    std::cout << "m_recoilMass                   : " << m_recoilMass << std::endl;
    std::cout << "m_recoilMassMC                 : " << m_recoilMassMC << std::endl;
    std::cout << "m_energyAroundMostEnergeticPfo : " << m_energyAroundMostEnergeticPfo << std::endl;
    std::cout << "m_y34                          : " << m_y34 << std::endl;
    std::cout << "m_invariantMassSystem          : " << m_invariantMassSystem << std::endl;
    std::cout << "m_invariantMassSystemMC        : " << m_invariantMassSystemMC << std::endl;
    std::cout << "m_cosThetaStarWBosons          : " << m_cosThetaStarWBosons << std::endl;
    std::cout << "m_cosThetaStarWBosonsMC        : " << m_cosThetaStarWBosonsMC << std::endl;
    std::cout << "m_cosThetaStarZBosons          : " << m_cosThetaStarZBosons << std::endl;
    std::cout << "m_cosThetaStarZBosonsMC        : " << m_cosThetaStarZBosonsMC << std::endl;
//    std::cout << " : " <<  << std::endl;

    for (DoubleVector::iterator iter = m_energyJets.begin(); iter != m_energyJets.end(); iter++)
    {
        std::cout << "m_energyJets, position " << iter-m_energyJets.begin() << " : " << *iter << std::endl;
    }
}

//===========================================================

void Variables::Clear()
{
    m_appropriateEvent = false;
    m_isEventWW = false;
    m_isEventWWMC = false;
    m_isEventZZ = false;
    m_isEventZZMC = false;

    m_nPfosBosonW1 = std::numeric_limits<int>::max();
    m_nPfosBosonW2 = std::numeric_limits<int>::max();
    m_nPfosBosonZ1 = std::numeric_limits<int>::max();
    m_nPfosBosonZ2 = std::numeric_limits<int>::max();
    m_highestEnergyPfoPDG = std::numeric_limits<int>::max();
    m_highestEnergyIsolatedLeptonPDG = std::numeric_limits<int>::max();
    m_secondHighestEnergyIsolatedLeptonPDG = std::numeric_limits<int>::max();
    m_nIsolatedLeptons = std::numeric_limits<int>::max();

    m_combinationWJets.clear();
    m_combinationZJets.clear();
    m_combinationSynergyJets.clear();
    m_nParticlesJets.clear();
    m_nChargedParticlesJets.clear();

    m_transverseMomentum = std::numeric_limits<double>::max();
    m_transverseMomentumMC = std::numeric_limits<double>::max();
    m_transverseEnergy = std::numeric_limits<double>::max();
    m_transverseEnergyMC = std::numeric_limits<double>::max();
    m_energyBosonW1 = std::numeric_limits<double>::max();
    m_energyBosonW2 = std::numeric_limits<double>::max();
    m_energyBosonZ1 = std::numeric_limits<double>::max();
    m_energyBosonZ2 = std::numeric_limits<double>::max();
    m_momentumBosonW1 = std::numeric_limits<double>::max();
    m_momentumBosonW2 = std::numeric_limits<double>::max();
    m_momentumBosonZ1 = std::numeric_limits<double>::max();
    m_momentumBosonZ2 = std::numeric_limits<double>::max();
    m_transverseMomentumBosonW1 = std::numeric_limits<double>::max();
    m_transverseMomentumBosonW2 = std::numeric_limits<double>::max();
    m_transverseMomentumBosonZ1 = std::numeric_limits<double>::max();
    m_transverseMomentumBosonZ2 = std::numeric_limits<double>::max();
    m_cosThetaBosonW1 = std::numeric_limits<double>::max();
    m_cosThetaBosonW2 = std::numeric_limits<double>::max();
    m_cosThetaBosonZ1 = std::numeric_limits<double>::max();
    m_cosThetaBosonZ2 = std::numeric_limits<double>::max();
    m_transverseEnergyBosonW1 = std::numeric_limits<double>::max();
    m_transverseEnergyBosonW2 = std::numeric_limits<double>::max();
    m_transverseEnergyBosonZ1 = std::numeric_limits<double>::max();
    m_transverseEnergyBosonZ2 = std::numeric_limits<double>::max();
    m_cosThetaMissing = std::numeric_limits<double>::max();
    m_cosThetaMissingMC = std::numeric_limits<double>::max();
    m_cosThetaMostEnergeticTrack = std::numeric_limits<double>::max();
    m_recoilMass = std::numeric_limits<double>::max();
    m_recoilMassMC = std::numeric_limits<double>::max();
    m_energyAroundMostEnergeticPfo = std::numeric_limits<double>::max();
    m_y12 = std::numeric_limits<double>::max();
    m_y23 = std::numeric_limits<double>::max();
    m_y34 = std::numeric_limits<double>::max();
    m_y45 = std::numeric_limits<double>::max();
    m_y56 = std::numeric_limits<double>::max();
    m_y67 = std::numeric_limits<double>::max();
    m_invariantMassSystem = std::numeric_limits<double>::max();
    m_invariantMassSystemMC = std::numeric_limits<double>::max();
    m_cosThetaStarWBosons = std::numeric_limits<double>::max();
    m_cosThetaStarWBosonsMC = std::numeric_limits<double>::max();
    m_cosThetaStarZBosons = std::numeric_limits<double>::max();
    m_cosThetaStarZBosonsMC = std::numeric_limits<double>::max();
    m_acolinearityJetsW1 = std::numeric_limits<double>::max();
    m_acolinearityJetsW2 = std::numeric_limits<double>::max();
    m_acolinearityJetsZ1 = std::numeric_limits<double>::max();
    m_acolinearityJetsZ2 = std::numeric_limits<double>::max();
    m_acolinearityBosonsW = std::numeric_limits<double>::max();
    m_acolinearityBosonsZ = std::numeric_limits<double>::max();
    m_principleThrustValue = std::numeric_limits<double>::max();
    m_majorThrustValue = std::numeric_limits<double>::max();
    m_minorThrustValue = std::numeric_limits<double>::max();
    m_xThrustAxis = std::numeric_limits<double>::max();
    m_yThrustAxis = std::numeric_limits<double>::max();
    m_zThrustAxis = std::numeric_limits<double>::max();
    m_sphericity = std::numeric_limits<double>::max();
    m_aplanarity = std::numeric_limits<double>::max();
    m_highestEnergyElectronE = std::numeric_limits<double>::max();
    m_highestEnergyElectronP = std::numeric_limits<double>::max();
    m_highestEnergyElectronPt = std::numeric_limits<double>::max();
    m_highestEnergyElectronCosTheta = std::numeric_limits<double>::max();
    m_highestEnergyMuonE = std::numeric_limits<double>::max();
    m_highestEnergyMuonP = std::numeric_limits<double>::max();
    m_highestEnergyMuonPt = std::numeric_limits<double>::max();
    m_highestEnergyMuonCosTheta = std::numeric_limits<double>::max();
    m_highestEnergyPhotonE = std::numeric_limits<double>::max();
    m_highestEnergyPhotonP = std::numeric_limits<double>::max();
    m_highestEnergyPhotonPt = std::numeric_limits<double>::max();
    m_highestEnergyPhotonCosTheta = std::numeric_limits<double>::max();
    m_highestEnergyPfoE = std::numeric_limits<double>::max();
    m_highestEnergyPfoP = std::numeric_limits<double>::max();
    m_highestEnergyPfoPt = std::numeric_limits<double>::max();
    m_highestEnergyPfoCosTheta = std::numeric_limits<double>::max();
    m_highestEnergyIsolatedLeptonE = std::numeric_limits<double>::max();
    m_highestEnergyIsolatedLeptonP = std::numeric_limits<double>::max();
    m_highestEnergyIsolatedLeptonPt = std::numeric_limits<double>::max();
    m_highestEnergyIsolatedLeptonCosTheta = std::numeric_limits<double>::max();
    m_secondHighestEnergyIsolatedLeptonE = std::numeric_limits<double>::max();
    m_secondHighestEnergyIsolatedLeptonP = std::numeric_limits<double>::max();
    m_secondHighestEnergyIsolatedLeptonPt = std::numeric_limits<double>::max();
    m_secondHighestEnergyIsolatedLeptonCosTheta = std::numeric_limits<double>::max();
    m_maxBTagForBosonW1 = std::numeric_limits<double>::max();
    m_minBTagForBosonW1 = std::numeric_limits<double>::max();
    m_maxBTagForBosonW2 = std::numeric_limits<double>::max();
    m_minBTagForBosonW2 = std::numeric_limits<double>::max();
    m_maxCTagForBosonW1 = std::numeric_limits<double>::max();
    m_minCTagForBosonW1 = std::numeric_limits<double>::max();
    m_maxCTagForBosonW2 = std::numeric_limits<double>::max();
    m_minCTagForBosonW2 = std::numeric_limits<double>::max();
    m_maxBTagForBosonZ1 = std::numeric_limits<double>::max();
    m_minBTagForBosonZ1 = std::numeric_limits<double>::max();
    m_maxBTagForBosonZ2 = std::numeric_limits<double>::max();
    m_minBTagForBosonZ2 = std::numeric_limits<double>::max();
    m_maxCTagForBosonZ1 = std::numeric_limits<double>::max();
    m_minCTagForBosonZ1 = std::numeric_limits<double>::max();
    m_maxCTagForBosonZ2 = std::numeric_limits<double>::max();
    m_minCTagForBosonZ2 = std::numeric_limits<double>::max();

    m_invariantMassWBosons.clear();
    m_invariantMassWBosonsMC.clear();
    m_invariantMassZBosons.clear();
    m_invariantMassZBosonsMC.clear();
    m_invariantMassSynergyBosons.clear();
    m_invariantMassesAllPairings.clear();
    m_energyJets.clear();
    m_momentumJets.clear();
    m_transverseMomentumJets.clear();
    m_cosThetaJets.clear();
    m_cosThetaStarWJets.clear();
    m_cosThetaStarZJets.clear();
    m_bTagForJets.clear();
    m_cTagForJets.clear();
    m_energyNeutrinos.clear();
    m_pxMomentumNeutrinos.clear();
    m_pyMomentumNeutrinos.clear();
    m_pzMomentumNeutrinos.clear();
    m_energyQuarks.clear();
    m_pxMomentumQuarks.clear();
    m_pyMomentumQuarks.clear();
    m_pzMomentumQuarks.clear();
    m_cheatedInvariantMasses.clear();
    m_cheatedMCInvariantMasses.clear();

    m_mcParticleToQuarkMap.clear();
}

//===========================================================

void Variables::SetLCParameterInfo(const EVENT::LCParameters &lcParameters)
{
    m_principleThrustValue = lcParameters.getFloatVal("principleThrustValue");
    m_majorThrustValue = lcParameters.getFloatVal("majorThrustValue");
    m_minorThrustValue = lcParameters.getFloatVal("minorThrustValue");

    FloatVector thrustaxis;
    lcParameters.getFloatVals("principleThrustAxis", thrustaxis);

    if (thrustaxis.size() >=3)
    {
        m_xThrustAxis  = thrustaxis[0];
        m_yThrustAxis  = thrustaxis[1];
        m_zThrustAxis  = thrustaxis[2];
    }
    else
    {
        std::cout  << "Variables::SetLCParameterInfo thrustaxis less than 3 elements" << std::endl;
    }

    m_sphericity = lcParameters.getFloatVal("sphericity");
    m_aplanarity = lcParameters.getFloatVal("aplanarity");
}

//=========================================================== bool

void Variables::SetAppropriateEvent(bool appropriateEvent)
{
    m_appropriateEvent = appropriateEvent;
}

//===========================================================

bool Variables::GetAppropriateEvent() const 
{
    return m_appropriateEvent;
}

//===========================================================

void Variables::SetIsEventWW(bool isEventWW)
{
    m_isEventWW = isEventWW;
}

//===========================================================

bool Variables::GetIsEventWW() const 
{
    return m_isEventWW;
}

//===========================================================

void Variables::SetIsEventWWMC(bool isEventWWMC)
{
    m_isEventWWMC = isEventWWMC;
}

//===========================================================

bool Variables::GetIsEventWWMC() const
{
    return m_isEventWWMC;
}

//===========================================================

void Variables::SetIsEventZZ(bool isEventZZ)
{
    m_isEventZZ = isEventZZ;
}

//===========================================================

bool Variables::GetIsEventZZ() const 
{
    return m_isEventZZ;
}

//===========================================================

void Variables::SetIsEventZZMC(bool isEventZZMC)
{
    m_isEventZZMC = isEventZZMC;
}

//===========================================================

bool Variables::GetIsEventZZMC() const
{
    return m_isEventZZMC;
}

//=========================================================== Int

void Variables::SetNPfosBosonW1(int nPfosBosonW1)
{
    m_nPfosBosonW1 = nPfosBosonW1;
}

//===========================================================

int Variables::GetNPfosBosonW1() const
{
    return m_nPfosBosonW1;
}

//===========================================================

void Variables::SetNPfosBosonW2(int nPfosBosonW2)
{
    m_nPfosBosonW2 = nPfosBosonW2;
}

//===========================================================

int Variables::GetNPfosBosonW2() const
{
    return m_nPfosBosonW2;
}

//===========================================================

void Variables::SetNPfosBosonZ1(int nPfosBosonZ1)
{
    m_nPfosBosonZ1 = nPfosBosonZ1;
}

//===========================================================

int Variables::GetNPfosBosonZ1() const
{
    return m_nPfosBosonZ1;
}

//===========================================================

void Variables::SetNPfosBosonZ2(int nPfosBosonZ2)
{
    m_nPfosBosonZ2 = nPfosBosonZ2;
}

//===========================================================

int Variables::GetNPfosBosonZ2() const
{
    return m_nPfosBosonZ2;
}

//===========================================================

void Variables::SetHighestEnergyPfoPDG(int highestEnergyPfoPDG)
{
    m_highestEnergyPfoPDG = highestEnergyPfoPDG; 
}

//===========================================================

int Variables::GetHighestEnergyPfoPDG() const
{
    return m_highestEnergyPfoPDG;
}

//===========================================================

void Variables::SetNumberOfIsolatedLeptons(int nIsolatedLeptons)
{
    m_nIsolatedLeptons = nIsolatedLeptons;
}

//===========================================================

int Variables::GetNumberOfIsolatedLeptons() const
{
    return m_nIsolatedLeptons;
}

//===========================================================

void Variables::SetHighestEnergyIsolatedLeptonPDG(int highestEnergyIsolatedLeptonPDG)
{
    m_highestEnergyIsolatedLeptonPDG = highestEnergyIsolatedLeptonPDG;
}

//===========================================================

int Variables::GetHighestEnergyIsolatedLeptonPDG() const
{
    return m_highestEnergyIsolatedLeptonPDG;
}

//===========================================================

void Variables::SetSecondHighestEnergyIsolatedLeptonPDG(int secondHighestEnergyIsolatedLeptonPDG)
{
    m_secondHighestEnergyIsolatedLeptonPDG = secondHighestEnergyIsolatedLeptonPDG;
}

//===========================================================

int Variables::GetSecondHighestEnergyIsolatedLeptonPDG() const
{
    return m_secondHighestEnergyIsolatedLeptonPDG;
}

//=========================================================== IntVector

void Variables::SetJetCombinationW(IntVector combinationWJets)
{
    m_combinationWJets = combinationWJets;
}

//===========================================================

IntVector Variables::GetJetCombinationW() const
{
    return m_combinationWJets;
}

//===========================================================

void Variables::SetJetCombinationZ(IntVector combinationZJets)
{
    m_combinationZJets = combinationZJets;
}

//===========================================================

IntVector Variables::GetJetCombinationZ() const
{
    return m_combinationZJets;
}

//===========================================================

void Variables::SetJetCombinationSynergy(IntVector combinationSynergyJets)
{
    m_combinationSynergyJets = combinationSynergyJets;
}

//===========================================================

IntVector Variables::GetJetCombinationSynergy() const
{
    return m_combinationSynergyJets;
}

//===========================================================

void Variables::SetNParticlesJets(IntVector nParticlesJets)
{
    m_nParticlesJets = nParticlesJets;
}

//===========================================================

IntVector Variables::GetNParticlesJets() const
{
    return m_nParticlesJets;
}

//===========================================================

int Variables::GetLowestNParticlesJets() const
{
    int lowestNParticlesJets(std::numeric_limits<int>::max());

    for (IntVector::const_iterator iter = m_nParticlesJets.begin(); iter != m_nParticlesJets.end(); iter++)
    {
        const int nParticlesJet(*iter);
        if (nParticlesJet < lowestNParticlesJets)
        {
            lowestNParticlesJets = nParticlesJet;
        }
    }

    return lowestNParticlesJets;
}

//===========================================================

void Variables::SetNChargedParticlesJets(IntVector nChargedParticlesJets)
{
    m_nChargedParticlesJets = nChargedParticlesJets;
}

//===========================================================

IntVector Variables::GetNChargedParticlesJets() const 
{
    return m_nChargedParticlesJets;
}

//===========================================================

int Variables::GetLowestNChargedParticlesJets() const
{
    int lowestNChargedParticlesJets(std::numeric_limits<int>::max());

    for (IntVector::const_iterator iter = m_nChargedParticlesJets.begin(); iter != m_nChargedParticlesJets.end(); iter++)
    {
        const int nChargedParticlesJet(*iter);
        if (nChargedParticlesJet < lowestNChargedParticlesJets)
        {
            lowestNChargedParticlesJets = nChargedParticlesJet;
        }
    }

    return lowestNChargedParticlesJets;
}

//=========================================================== double

double Variables::GetEventEnergyMC() const
{
    return m_eventEnergyMC;
}

//===========================================================

void Variables::SetTransverseMomentum(double transverseMomentum)
{
    m_transverseMomentum = transverseMomentum;
}

//===========================================================

double Variables::GetTransverseMomentum() const 
{
    return m_transverseMomentum;
}

//===========================================================

void Variables::SetTransverseMomentumMC(double transverseMomentumMC)
{
    m_transverseMomentumMC = transverseMomentumMC;
}

//===========================================================

double Variables::GetTransverseMomentumMC() const
{
    return m_transverseMomentumMC;
}

//===========================================================

void Variables::SetTransverseEnergy(double transverseEnergy)
{
    m_transverseEnergy = transverseEnergy;
}

//===========================================================

double Variables::GetTransverseEnergy() const
{
    return m_transverseEnergy;
}

//===========================================================

void Variables::SetTransverseEnergyMC(double transverseEnergyMC)
{
    m_transverseEnergyMC = transverseEnergyMC;
}

//===========================================================

double Variables::GetTransverseEnergyMC() const
{
    return m_transverseEnergyMC;
}

//===========================================================

void Variables::SetEnergyBosonW1(double energyBosonW1)
{
    m_energyBosonW1 = energyBosonW1;
}

//===========================================================

double Variables::GetEnergyBosonW1() const
{
    return m_energyBosonW1;
}

//===========================================================

void Variables::SetEnergyBosonW2(double energyBosonW2)
{
    m_energyBosonW2 = energyBosonW2;
}

//===========================================================

double Variables::GetEnergyBosonW2() const
{
    return m_energyBosonW2;
}

//===========================================================

void Variables::SetEnergyBosonZ1(double energyBosonZ1)
{
    m_energyBosonZ1 = energyBosonZ1;
}

//===========================================================

double Variables::GetEnergyBosonZ1() const
{
    return m_energyBosonZ1;
}

//===========================================================

void Variables::SetEnergyBosonZ2(double energyBosonZ2)
{
    m_energyBosonZ2 = energyBosonZ2;
}

//===========================================================

double Variables::GetEnergyBosonZ2() const
{
    return m_energyBosonZ2;
}

//===========================================================

void Variables::SetMomentumBosonW1(double momentumBosonW1)
{   
    m_momentumBosonW1 = momentumBosonW1;
}

//===========================================================

double Variables::GetMomentumBosonW1() const
{
    return m_momentumBosonW1;
}

//===========================================================

void Variables::SetMomentumBosonW2(double momentumBosonW2)
{
    m_momentumBosonW2 = momentumBosonW2;
}

//===========================================================

double Variables::GetMomentumBosonW2() const
{
    return m_momentumBosonW2;
}

//===========================================================

void Variables::SetMomentumBosonZ1(double momentumBosonZ1)
{
    m_momentumBosonZ1 = momentumBosonZ1;
}

//===========================================================

double Variables::GetMomentumBosonZ1() const
{
    return m_momentumBosonZ1;
}

//===========================================================

void Variables::SetMomentumBosonZ2(double momentumBosonZ2)
{
    m_momentumBosonZ2 = momentumBosonZ2;
}

//===========================================================

double Variables::GetMomentumBosonZ2() const
{
    return m_momentumBosonZ2;
}

//===========================================================

void Variables::SetTransverseMomentumBosonW1(double transverseMomentumBosonW1)
{
    m_transverseMomentumBosonW1 = transverseMomentumBosonW1;
}

//===========================================================

double Variables::GetTransverseMomentumBosonW1() const
{
    return m_transverseMomentumBosonW1;
}

//===========================================================

void Variables::SetTransverseMomentumBosonW2(double transverseMomentumBosonW2)
{
    m_transverseMomentumBosonW2 = transverseMomentumBosonW2;
}

//===========================================================

double Variables::GetTransverseMomentumBosonW2() const
{
    return m_transverseMomentumBosonW2;
}

//===========================================================

void Variables::SetTransverseMomentumBosonZ1(double transverseMomentumBosonZ1)
{
    m_transverseMomentumBosonZ1 = transverseMomentumBosonZ1;
}

//===========================================================

double Variables::GetTransverseMomentumBosonZ1() const
{
    return m_transverseMomentumBosonZ1;
}

//===========================================================

void Variables::SetTransverseMomentumBosonZ2(double transverseMomentumBosonZ2)
{
    m_transverseMomentumBosonZ2 = transverseMomentumBosonZ2;
}

//===========================================================

double Variables::GetTransverseMomentumBosonZ2() const
{
    return m_transverseMomentumBosonZ2;
}

//===========================================================

void Variables::SetCosThetaBosonW1(double cosThetaBosonW1)
{   
    m_cosThetaBosonW1 = cosThetaBosonW1;
}

//===========================================================

double Variables::GetCosThetaBosonW1() const
{
    return m_cosThetaBosonW1;
}

//===========================================================

void Variables::SetCosThetaBosonW2(double cosThetaBosonW2)
{
    m_cosThetaBosonW2 = cosThetaBosonW2;
}

//===========================================================

double Variables::GetCosThetaBosonW2() const
{
    return m_cosThetaBosonW2;
}

//===========================================================

void Variables::SetCosThetaBosonZ1(double cosThetaBosonZ1)
{
    m_cosThetaBosonZ1 = cosThetaBosonZ1;
}

//===========================================================

double Variables::GetCosThetaBosonZ1() const
{
    return m_cosThetaBosonZ1;
}

//===========================================================

void Variables::SetCosThetaBosonZ2(double cosThetaBosonZ2)
{
    m_cosThetaBosonZ2 = cosThetaBosonZ2;
}

//===========================================================

double Variables::GetCosThetaBosonZ2() const
{
    return m_cosThetaBosonZ2;
}

//===========================================================

void Variables::SetTransverseEnergyBosonW1(double transverseEnergyBosonW1)
{
    m_transverseEnergyBosonW1 = transverseEnergyBosonW1;
}

//===========================================================

double Variables::GetTransverseEnergyBosonW1() const
{
    return m_transverseEnergyBosonW1;
}

//===========================================================

void Variables::SetTransverseEnergyBosonW2(double transverseEnergyBosonW2)
{
    m_transverseEnergyBosonW2 = transverseEnergyBosonW2;
}

//===========================================================

double Variables::GetTransverseEnergyBosonW2() const
{
    return m_transverseEnergyBosonW2;
}

//===========================================================

void Variables::SetTransverseEnergyBosonZ1(double transverseEnergyBosonZ1)
{
    m_transverseEnergyBosonZ1 = transverseEnergyBosonZ1;
}

//===========================================================

double Variables::GetTransverseEnergyBosonZ1() const
{
    return m_transverseEnergyBosonZ1;
}

//===========================================================

void Variables::SetTransverseEnergyBosonZ2(double transverseEnergyBosonZ2)
{
    m_transverseEnergyBosonZ2 = transverseEnergyBosonZ2;
}

//===========================================================

double Variables::GetTransverseEnergyBosonZ2() const
{
    return m_transverseEnergyBosonZ2;
}

//===========================================================

void Variables::SetCosThetaMissing(double cosThetaMissing)
{
    m_cosThetaMissing = cosThetaMissing;
}

//===========================================================

double Variables::GetCosThetaMissing() const 
{
    return m_cosThetaMissing;
}

//===========================================================

void Variables::SetCosThetaMissingMC(double cosThetaMissingMC)
{
    m_cosThetaMissingMC = cosThetaMissingMC;
}

//===========================================================

double Variables::GetCosThetaMissingMC() const
{
    return m_cosThetaMissingMC;
}

//===========================================================

void Variables::SetCosThetaMostEnergeticTrack(double cosThetaMostEnergeticTrack)
{
    m_cosThetaMostEnergeticTrack = cosThetaMostEnergeticTrack;
}

//===========================================================

double Variables::GetCosThetaMostEnergeticTrack() const 
{
    return m_cosThetaMostEnergeticTrack;
}

//===========================================================

void Variables::SetRecoilMass(double recoilMass)
{
    m_recoilMass = recoilMass;
}

//===========================================================

double Variables::GetRecoilMass() const 
{
    return m_recoilMass;
}

//===========================================================

void Variables::SetRecoilMassMC(double recoilMassMC)
{
    m_recoilMassMC = recoilMassMC;
}

//===========================================================

double Variables::GetRecoilMassMC() const
{
    return m_recoilMassMC;
}

//===========================================================

void Variables::SetEnergyAroundMostEnergeticPfo(double energyAroundMostEnergeticPfo)
{
    m_energyAroundMostEnergeticPfo = energyAroundMostEnergeticPfo;
}

//===========================================================

double Variables::GetEnergyAroundMostEnergeticPfo() const 
{
    return m_energyAroundMostEnergeticPfo;
}

//===========================================================

void Variables::SetY12(double y12)
{
    m_y12 = y12;
}

//===========================================================

double Variables::GetY12() const
{
    return m_y12;
}

//===========================================================

void Variables::SetY23(double y23)
{
    m_y23 = y23;
}

//===========================================================

double Variables::GetY23() const
{
    return m_y23;
}

//===========================================================

void Variables::SetY34(double y34)
{
    m_y34 = y34;
}

//===========================================================

double Variables::GetY34() const 
{
    return m_y34;
}

//===========================================================

void Variables::SetY45(double y45)
{
    m_y45 = y45;
}

//===========================================================

double Variables::GetY45() const
{
    return m_y45;
}

//===========================================================

void Variables::SetY56(double y56)
{
    m_y56 = y56;
}

//===========================================================

double Variables::GetY56() const
{
    return m_y56;
}

//===========================================================

void Variables::SetY67(double y67)
{
    m_y67 = y67;
}

//===========================================================

double Variables::GetY67() const
{
    return m_y67;
}

//===========================================================

void Variables::SetInvariantMassSystem(double invariantMassSystem)
{
    m_invariantMassSystem = invariantMassSystem;
}

//=========================================================== 

double Variables::GetInvariantMassSystem() const 
{
    return m_invariantMassSystem;
}

//===========================================================

void Variables::SetInvariantMassSystemMC(double invariantMassSystemMC)
{
    m_invariantMassSystemMC = invariantMassSystemMC;
}

//===========================================================

double Variables::GetInvariantMassSystemMC() const
{
    return m_invariantMassSystemMC;
}

//===========================================================

void Variables::SetCosThetaStarWBosons(double cosThetaStarWBosons)
{
    m_cosThetaStarWBosons = cosThetaStarWBosons;
}

//===========================================================

double Variables::GetCosThetaStarWBosons() const 
{
    return m_cosThetaStarWBosons;
}

//===========================================================

void Variables::SetCosThetaStarWBosonsMC(double cosThetaStarWBosonsMC)
{
    m_cosThetaStarWBosonsMC = cosThetaStarWBosonsMC;
}

//===========================================================

double Variables::GetCosThetaStarWBosonsMC() const
{
    return m_cosThetaStarWBosonsMC;
}

//===========================================================

void Variables::SetCosThetaStarZBosons(double cosThetaStarZBosons)
{
    m_cosThetaStarZBosons = cosThetaStarZBosons;
}

//===========================================================

double Variables::GetCosThetaStarZBosons() const 
{
    return m_cosThetaStarZBosons;
}

//===========================================================

void Variables::SetCosThetaStarZBosonsMC(double cosThetaStarZBosonsMC)
{
    m_cosThetaStarZBosonsMC = cosThetaStarZBosonsMC;
}

//===========================================================

double Variables::GetCosThetaStarZBosonsMC() const
{
    return m_cosThetaStarZBosonsMC;
}

//===========================================================

void Variables::SetAcolinearityJetsW1(double acolinearityJetsW1)
{
    m_acolinearityJetsW1 = acolinearityJetsW1;
}

//===========================================================

double Variables::GetAcolinearityJetsW1() const
{
    return m_acolinearityJetsW1;
}

//===========================================================

void Variables::SetAcolinearityJetsW2(double acolinearityJetsW2)
{
    m_acolinearityJetsW2 = acolinearityJetsW2;
}

//===========================================================

double Variables::GetAcolinearityJetsW2() const
{
    return m_acolinearityJetsW2;
}

//===========================================================

void Variables::SetAcolinearityJetsZ1(double acolinearityJetsZ1)
{
    m_acolinearityJetsZ1 = acolinearityJetsZ1;
}

//===========================================================

double Variables::GetAcolinearityJetsZ1() const
{
    return m_acolinearityJetsZ1;
}

//===========================================================

void Variables::SetAcolinearityJetsZ2(double acolinearityJetsZ2)
{
    m_acolinearityJetsZ2 = acolinearityJetsZ2;
}

//===========================================================

double Variables::GetAcolinearityJetsZ2() const
{
    return m_acolinearityJetsZ2;
}

//===========================================================

void Variables::SetAcolinearityBosonsW(double acolinearityBosonsW)
{
    m_acolinearityBosonsW = acolinearityBosonsW;
}

//===========================================================

double Variables::GetAcolinearityBosonsW() const
{
    return m_acolinearityBosonsW;
}

//===========================================================

void Variables::SetAcolinearityBosonsZ(double acolinearityBosonsZ)
{
    m_acolinearityBosonsZ = acolinearityBosonsZ;
}

//===========================================================

double Variables::GetAcolinearityBosonsZ() const
{
    return m_acolinearityBosonsZ;
}

//===========================================================

void Variables::SetHighestEnergyElectronEnergy(double highestEnergyElectronE)
{
    m_highestEnergyElectronE = highestEnergyElectronE;
}

//===========================================================

double Variables::GetHighestEnergyElectronEnergy() const
{
    return m_highestEnergyElectronE;
}

//===========================================================

void Variables::SetHighestEnergyElectronMomentum(double highestEnergyElectronP)
{
    m_highestEnergyElectronP = highestEnergyElectronP;
}

//===========================================================

double Variables::GetHighestEnergyElectronMomentum() const
{
    return m_highestEnergyElectronP;
}

//===========================================================

void Variables::SetHighestEnergyElectronTransverseMomentum(double highestEnergyElectronPt)
{
    m_highestEnergyElectronPt = highestEnergyElectronPt;
}

//===========================================================

double Variables::GetHighestEnergyElectronTransverseMomentum() const
{
    return m_highestEnergyElectronPt;
}

//===========================================================

void Variables::SetHighestEnergyElectronCosTheta(double highestEnergyElectronCosTheta)
{
    m_highestEnergyElectronCosTheta = highestEnergyElectronCosTheta;
}

//===========================================================

double Variables::GetHighestEnergyElectronCosTheta() const
{
    return m_highestEnergyElectronCosTheta;
}

//===========================================================

void Variables::SetHighestEnergyMuonEnergy(double highestEnergyMuonE)
{
    m_highestEnergyMuonE = highestEnergyMuonE;
}

//===========================================================

double Variables::GetHighestEnergyMuonEnergy() const
{
    return m_highestEnergyMuonE;
}

//===========================================================

void Variables::SetHighestEnergyMuonMomentum(double highestEnergyMuonP)
{
    m_highestEnergyMuonP = highestEnergyMuonP;
}

//===========================================================

double Variables::GetHighestEnergyMuonMomentum() const
{
    return m_highestEnergyMuonP;
}

//===========================================================

void Variables::SetHighestEnergyMuonTransverseMomentum(double highestEnergyMuonPt)
{
    m_highestEnergyMuonPt = highestEnergyMuonPt;
}

//===========================================================

double Variables::GetHighestEnergyMuonTransverseMomentum() const
{
    return m_highestEnergyMuonPt;
}

//===========================================================

void Variables::SetHighestEnergyMuonCosTheta(double highestEnergyMuonCosTheta)
{
    m_highestEnergyMuonCosTheta = highestEnergyMuonCosTheta;
}

//===========================================================

double Variables::GetHighestEnergyMuonCosTheta() const
{
    return m_highestEnergyMuonCosTheta;
}

//===========================================================

void Variables::SetHighestEnergyPhotonEnergy(double highestEnergyPhotonE)
{
    m_highestEnergyPhotonE = highestEnergyPhotonE;
}

//===========================================================

double Variables::GetHighestEnergyPhotonEnergy() const
{
    return m_highestEnergyPhotonE;
}

//===========================================================

void Variables::SetHighestEnergyPhotonMomentum(double highestEnergyPhotonP)
{
    m_highestEnergyPhotonP = highestEnergyPhotonP;
}

//===========================================================

double Variables::GetHighestEnergyPhotonMomentum() const
{
    return m_highestEnergyPhotonP;
}

//===========================================================

void Variables::SetHighestEnergyPhotonTransverseMomentum(double highestEnergyPhotonPt)
{
    m_highestEnergyPhotonPt = highestEnergyPhotonPt;
}

//===========================================================

double Variables::GetHighestEnergyPhotonTransverseMomentum() const
{
    return m_highestEnergyPhotonPt;
}

//===========================================================

void Variables::SetHighestEnergyPhotonCosTheta(double highestEnergyPhotonCosTheta)
{
    m_highestEnergyPhotonCosTheta = highestEnergyPhotonCosTheta;
}

//===========================================================

double Variables::GetHighestEnergyPhotonCosTheta() const
{
    return m_highestEnergyPhotonCosTheta;
}

//===========================================================

void Variables::SetHighestEnergyPfoEnergy(double highestEnergyPfoE)
{
    m_highestEnergyPfoE = highestEnergyPfoE;
}

//===========================================================

double Variables::GetHighestEnergyPfoEnergy() const
{
    return m_highestEnergyPfoE;
}

//===========================================================

void Variables::SetHighestEnergyPfoMomentum(double highestEnergyPfoP)
{
    m_highestEnergyPfoP = highestEnergyPfoP;
}

//===========================================================

double Variables::GetHighestEnergyPfoMomentum() const
{
    return m_highestEnergyPfoP;
}

//===========================================================

void Variables::SetHighestEnergyPfoTransverseMomentum(double highestEnergyPfoPt)
{
    m_highestEnergyPfoPt = highestEnergyPfoPt;
}

//===========================================================

double Variables::GetHighestEnergyPfoTransverseMomentum() const
{
    return m_highestEnergyPfoPt;
}

//===========================================================

void Variables::SetHighestEnergyPfoCosTheta(double highestEnergyPfoCosTheta)
{
    m_highestEnergyPfoCosTheta = highestEnergyPfoCosTheta;
}

//===========================================================

double Variables::GetHighestEnergyPfoCosTheta() const
{
    return m_highestEnergyPfoCosTheta;
}

//===========================================================

void Variables::SetHighestEnergyIsolatedLeptonEnergy(double highestEnergyIsolatedLeptonE)
{
    m_highestEnergyIsolatedLeptonE = highestEnergyIsolatedLeptonE;
}

//===========================================================

double Variables::GetHighestEnergyIsolatedLeptonEnergy() const
{
    return m_highestEnergyIsolatedLeptonE;
}

//===========================================================

void Variables::SetHighestEnergyIsolatedLeptonMomentum(double highestEnergyIsolatedLeptonP)
{
    m_highestEnergyIsolatedLeptonP = highestEnergyIsolatedLeptonP;
}

//===========================================================

double Variables::GetHighestEnergyIsolatedLeptonMomentum() const
{
    return m_highestEnergyIsolatedLeptonP;
}

//===========================================================

void Variables::SetHighestEnergyIsolatedLeptonTransverseMomentum(double highestEnergyIsolatedLeptonPt)
{
    m_highestEnergyIsolatedLeptonPt = highestEnergyIsolatedLeptonPt;
}

//===========================================================

double Variables::GetHighestEnergyIsolatedLeptonTransverseMomentum() const
{
    return m_highestEnergyIsolatedLeptonPt;
}

//===========================================================

void Variables::SetHighestEnergyIsolatedLeptonCosTheta(double highestEnergyIsolatedLeptonCosTheta)
{
    m_highestEnergyIsolatedLeptonCosTheta = highestEnergyIsolatedLeptonCosTheta;
}

//===========================================================

double Variables::GetHighestEnergyIsolatedLeptonCosTheta() const
{
    return m_highestEnergyIsolatedLeptonCosTheta;
}

//===========================================================

void Variables::SetSecondHighestEnergyIsolatedLeptonEnergy(double secondHighestEnergyIsolatedLeptonE)
{
    m_secondHighestEnergyIsolatedLeptonE = secondHighestEnergyIsolatedLeptonE;
}

//===========================================================

double Variables::GetSecondHighestEnergyIsolatedLeptonEnergy() const
{
    return m_secondHighestEnergyIsolatedLeptonE;
}

//===========================================================

void Variables::SetSecondHighestEnergyIsolatedLeptonMomentum(double secondHighestEnergyIsolatedLeptonP)
{
    m_secondHighestEnergyIsolatedLeptonP = secondHighestEnergyIsolatedLeptonP;
}

//===========================================================

double Variables::GetSecondHighestEnergyIsolatedLeptonMomentum() const
{
    return m_secondHighestEnergyIsolatedLeptonP;
}

//===========================================================

void Variables::SetSecondHighestEnergyIsolatedLeptonTransverseMomentum(double secondHighestEnergyIsolatedLeptonPt)
{
    m_secondHighestEnergyIsolatedLeptonPt = secondHighestEnergyIsolatedLeptonPt;
}

//===========================================================

double Variables::GetSecondHighestEnergyIsolatedLeptonTransverseMomentum() const
{
    return m_secondHighestEnergyIsolatedLeptonPt;
}

//===========================================================

void Variables::SetSecondHighestEnergyIsolatedLeptonCosTheta(double secondHighestEnergyIsolatedLeptonCosTheta)
{
    m_secondHighestEnergyIsolatedLeptonCosTheta = secondHighestEnergyIsolatedLeptonCosTheta;
}

//===========================================================

double Variables::GetSecondHighestEnergyIsolatedLeptonCosTheta() const
{
    return m_secondHighestEnergyIsolatedLeptonCosTheta;
}

//===========================================================

void Variables::SetMaxBTagForBosonW1(double maxBTagForBosonW1)
{
    m_maxBTagForBosonW1 = maxBTagForBosonW1;
}

//===========================================================

double Variables::GetMaxBTagForBosonW1() const
{
    return m_maxBTagForBosonW1;
}

//===========================================================

void Variables::SetMinBTagForBosonW1(double minBTagForBosonW1)
{
    m_minBTagForBosonW1 = minBTagForBosonW1;
}

//===========================================================

double Variables::GetMinBTagForBosonW1() const
{
    return m_minBTagForBosonW1;
}

//===========================================================

void Variables::SetMaxBTagForBosonW2(double maxBTagForBosonW2)
{
    m_maxBTagForBosonW2 = maxBTagForBosonW2;
}

//===========================================================

double Variables::GetMaxBTagForBosonW2() const
{
    return m_maxBTagForBosonW2;
}

//===========================================================

void Variables::SetMinBTagForBosonW2(double minBTagForBosonW2)
{
    m_minBTagForBosonW2 = minBTagForBosonW2;
}

//===========================================================

double Variables::GetMinBTagForBosonW2() const
{
    return m_minBTagForBosonW2;
}

//===========================================================

void Variables::SetMaxCTagForBosonW1(double maxCTagForBosonW1)
{
    m_maxCTagForBosonW1 = maxCTagForBosonW1;
}

//===========================================================

double Variables::GetMaxCTagForBosonW1() const
{
    return m_maxCTagForBosonW1;
}

//===========================================================

void Variables::SetMinCTagForBosonW1(double minCTagForBosonW1)
{
    m_minCTagForBosonW1 = minCTagForBosonW1;
}

//===========================================================

double Variables::GetMinCTagForBosonW1() const
{
    return m_minCTagForBosonW1;
}

//===========================================================

void Variables::SetMaxCTagForBosonW2(double maxCTagForBosonW2)
{
    m_maxCTagForBosonW2 = maxCTagForBosonW2;
}

//===========================================================

double Variables::GetMaxCTagForBosonW2() const
{
    return m_maxCTagForBosonW2;
}

//===========================================================

void Variables::SetMinCTagForBosonW2(double minCTagForBosonW2)
{
    m_minCTagForBosonW2 = minCTagForBosonW2;
}

//===========================================================

double Variables::GetMinCTagForBosonW2() const
{
    return m_minCTagForBosonW2;
}

//===========================================================

void Variables::SetMaxBTagForBosonZ1(double maxBTagForBosonZ1)
{
    m_maxBTagForBosonZ1 = maxBTagForBosonZ1;
}

//===========================================================

double Variables::GetMaxBTagForBosonZ1() const
{
    return m_maxBTagForBosonZ1;
}

//===========================================================

void Variables::SetMinBTagForBosonZ1(double minBTagForBosonZ1)
{
    m_minBTagForBosonZ1 = minBTagForBosonZ1;
}

//===========================================================

double Variables::GetMinBTagForBosonZ1() const
{
    return m_minBTagForBosonZ1;
}

//===========================================================

void Variables::SetMaxBTagForBosonZ2(double maxBTagForBosonZ2)
{
    m_maxBTagForBosonZ2 = maxBTagForBosonZ2;
}

//===========================================================

double Variables::GetMaxBTagForBosonZ2() const
{
    return m_maxBTagForBosonZ2;
}

//===========================================================

void Variables::SetMinBTagForBosonZ2(double minBTagForBosonZ2)
{
    m_minBTagForBosonZ2 = minBTagForBosonZ2;
}

//===========================================================

double Variables::GetMinBTagForBosonZ2() const
{
    return m_minBTagForBosonZ2;
}

//===========================================================

void Variables::SetMaxCTagForBosonZ1(double maxCTagForBosonZ1)
{
    m_maxCTagForBosonZ1 = maxCTagForBosonZ1;
}

//===========================================================

double Variables::GetMaxCTagForBosonZ1() const
{
    return m_maxCTagForBosonZ1;
}

//===========================================================

void Variables::SetMinCTagForBosonZ1(double minCTagForBosonZ1)
{
    m_minCTagForBosonZ1 = minCTagForBosonZ1;
}

//===========================================================

double Variables::GetMinCTagForBosonZ1() const
{
    return m_minCTagForBosonZ1;
}

//===========================================================

void Variables::SetMaxCTagForBosonZ2(double maxCTagForBosonZ2)
{
    m_maxCTagForBosonZ2 = maxCTagForBosonZ2;
}

//===========================================================

double Variables::GetMaxCTagForBosonZ2() const
{
    return m_maxCTagForBosonZ2;
}

//===========================================================

void Variables::SetMinCTagForBosonZ2(double minCTagForBosonZ2)
{
    m_minCTagForBosonZ2 = minCTagForBosonZ2;
}

//===========================================================

double Variables::GetMinCTagForBosonZ2() const
{
    return m_minCTagForBosonZ2;
}

//=========================================================== DoubleVector

void Variables::SetInvariantMassWBosons(DoubleVector invMassWBosons)
{
    m_invariantMassWBosons = invMassWBosons;
}

//===========================================================

DoubleVector Variables::GetInvariantMassWBosons() const 
{
    return m_invariantMassWBosons;
}

//===========================================================

void Variables::SetInvariantMassZBosons(DoubleVector invMassZBosons)
{
    m_invariantMassZBosons = invMassZBosons;
}

//===========================================================

DoubleVector Variables::GetInvariantMassZBosons() const 
{
    return m_invariantMassZBosons;
}

//===========================================================

void Variables::SetInvariantMassWBosonsMC(DoubleVector invariantMassWBosonsMC)
{
    m_invariantMassWBosonsMC = invariantMassWBosonsMC;
}

//===========================================================

DoubleVector Variables::GetInvariantMassWBosonsMC() const
{
    return m_invariantMassWBosonsMC;
}

//===========================================================

void Variables::SetInvariantMassZBosonsMC(DoubleVector invariantMassZBosonsMC)
{
    m_invariantMassZBosonsMC = invariantMassZBosonsMC;
}

//===========================================================

DoubleVector Variables::GetInvariantMassZBosonsMC() const
{
    return m_invariantMassZBosonsMC;
}

//===========================================================

void Variables::SetInvariantMassSynergyBosons(DoubleVector invariantMassSynergyBosons)
{
    m_invariantMassSynergyBosons = invariantMassSynergyBosons;
}

//===========================================================

DoubleVector Variables::GetInvariantMassSynergyBosons() const
{
    return m_invariantMassSynergyBosons;
}

//===========================================================

void Variables::SetAllInvariantMasses(DoubleVector invariantMassesAllPairings)
{
    m_invariantMassesAllPairings = invariantMassesAllPairings;
}

//===========================================================

DoubleVector Variables::GetAllInvariantMasses() const
{
    return m_invariantMassesAllPairings;
}

//===========================================================

void Variables::SetEnergyJets(DoubleVector energyJets)
{
    m_energyJets = energyJets;
}

//===========================================================

DoubleVector Variables::GetEnergyJets() const 
{
    return m_energyJets;
}

//===========================================================

void Variables::SetMomentumJets(DoubleVector momentumJets)
{
    m_momentumJets = momentumJets;
}

//===========================================================

DoubleVector Variables::GetMomentumJets() const
{
    return m_momentumJets;
}

//===========================================================

void Variables::SetTransverseMomentumJets(DoubleVector transverseMomentumJets)
{
    m_transverseMomentumJets = transverseMomentumJets;
}

//===========================================================

DoubleVector Variables::GetTransverseMomentumJets() const
{
    return m_transverseMomentumJets;
}

//===========================================================

void Variables::SetCosThetaJets(DoubleVector cosThetaJets)
{
    m_cosThetaJets = cosThetaJets;
}

//===========================================================

DoubleVector Variables::GetCosThetaJets() const
{
    return m_cosThetaJets;
}

//===========================================================

double Variables::GetLowestEnergyJet() const
{
    double lowestEnergyJet(std::numeric_limits<double>::max());

    for (DoubleVector::const_iterator iter = m_energyJets.begin(); iter != m_energyJets.end(); iter++)
    {
        const double energyJet(*iter);
        if (energyJet < lowestEnergyJet)
        {
            lowestEnergyJet = energyJet;
        }
    }

    return lowestEnergyJet;
}

//===========================================================

void Variables::SetCosThetaStarWJets(DoubleVector cosThetaStarWJets)
{
    m_cosThetaStarWJets = cosThetaStarWJets;
}

//===========================================================

DoubleVector Variables::GetCosThetaStarWJets() const 
{
    return m_cosThetaStarWJets;
}

//===========================================================

void Variables::SetCosThetaStarZJets(DoubleVector cosThetaStarZJets)
{
    m_cosThetaStarZJets = cosThetaStarZJets;
}

//===========================================================

DoubleVector Variables::GetCosThetaStarZJets() const 
{
    return m_cosThetaStarZJets;
}

//===========================================================

void Variables::SetBTagForJets(DoubleVector bTagForJets)
{
    m_bTagForJets = bTagForJets;
}

//===========================================================

DoubleVector Variables::GetBTagForJets() const
{
    return m_bTagForJets;
}

//===========================================================

void Variables::SetCTagForJets(DoubleVector cTagForJets)
{
    m_cTagForJets = cTagForJets;
}

//===========================================================

DoubleVector Variables::GetCTagForJets() const
{
    return m_cTagForJets;
}

//===========================================================

void Variables::SetEnergyNeutrinos(DoubleVector energyNeutrinos)
{
    m_energyNeutrinos = energyNeutrinos;
}

//===========================================================

DoubleVector Variables::GetEnergyNeutrinos() const
{
    return m_energyNeutrinos;
}

//===========================================================

void Variables::SetMomentumNeutrinos(DoubleVector pxMomentumNeutrinos, DoubleVector pyMomentumNeutrinos, DoubleVector pzMomentumNeutrinos)
{
    m_pxMomentumNeutrinos = pxMomentumNeutrinos;
    m_pyMomentumNeutrinos = pyMomentumNeutrinos;
    m_pzMomentumNeutrinos = pzMomentumNeutrinos;
}

//===========================================================

void Variables::SetEnergyQuarks(DoubleVector energyQuarks)
{
    m_energyQuarks = energyQuarks;
}

//===========================================================

DoubleVector Variables::GetEnergyQuarks() const
{
    return m_energyQuarks;
}

//===========================================================

void Variables::SetMomentumQuarks(DoubleVector pxMomentumQuarks, DoubleVector pyMomentumQuarks, DoubleVector pzMomentumQuarks)
{
    m_pxMomentumQuarks = pxMomentumQuarks;
    m_pyMomentumQuarks = pyMomentumQuarks;
    m_pzMomentumQuarks = pzMomentumQuarks;
}

//===========================================================

void Variables::SetCheatedInvariantMasses(DoubleVector cheatedInvariantMasses)
{
    m_cheatedInvariantMasses = cheatedInvariantMasses;
}

//===========================================================

DoubleVector Variables::GetCheatedInvariantMasses() const
{
    return m_cheatedInvariantMasses;
}

//===========================================================

void Variables::SetMCParticleToQuarkMap(MCParticleToMCParticleMap mcParticleToQuarkMap)
{
    m_mcParticleToQuarkMap = mcParticleToQuarkMap;
}

//===========================================================

void Variables::SetCheatedMCInvariantMasses(DoubleVector cheatedMCInvariantMasses)
{
    m_cheatedMCInvariantMasses = cheatedMCInvariantMasses;
}

//===========================================================

DoubleVector Variables::GetCheatedMCInvariantMasses() const
{
    return m_cheatedMCInvariantMasses;
}

//===========================================================

MCParticleToMCParticleMap Variables::GetMCParticleToQuarkMap() const
{
    return m_mcParticleToQuarkMap;
}

//===========================================================
