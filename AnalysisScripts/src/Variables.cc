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

Variables::Variables() : 
    m_appropriateEvent(false),
    m_isEventWW(false),
    m_isEventWWMC(false),
    m_isEventZZ(false),
    m_isEventZZMC(false),
    m_nPfosBosonW1(std::numeric_limits<int>::max()),
    m_nPfosBosonW2(std::numeric_limits<int>::max()),
    m_nPfosBosonZ1(std::numeric_limits<int>::max()),
    m_nPfosBosonZ2(std::numeric_limits<int>::max()),
    m_combinationWJets1(std::numeric_limits<int>::max()),
    m_combinationWJets2(std::numeric_limits<int>::max()),
    m_combinationWJets3(std::numeric_limits<int>::max()),
    m_combinationWJets4(std::numeric_limits<int>::max()),
    m_combinationZJets1(std::numeric_limits<int>::max()),
    m_combinationZJets2(std::numeric_limits<int>::max()),
    m_combinationZJets3(std::numeric_limits<int>::max()),
    m_combinationZJets4(std::numeric_limits<int>::max()),
    m_nParticlesJets1(std::numeric_limits<int>::max()),
    m_nParticlesJets2(std::numeric_limits<int>::max()),
    m_nParticlesJets3(std::numeric_limits<int>::max()),
    m_nParticlesJets4(std::numeric_limits<int>::max()),
    m_nChargedParticlesJets1(std::numeric_limits<int>::max()),
    m_nChargedParticlesJets2(std::numeric_limits<int>::max()),
    m_nChargedParticlesJets3(std::numeric_limits<int>::max()),
    m_nChargedParticlesJets4(std::numeric_limits<int>::max()),
    m_highestEnergyPfoPDG(std::numeric_limits<int>::max()),
    m_nIsolatedLeptons(std::numeric_limits<int>::max()),
    m_highestEnergyIsolatedLeptonPDG(std::numeric_limits<int>::max()),
    m_secondHighestEnergyIsolatedLeptonPDG(std::numeric_limits<int>::max()),
    m_globalEventNumber(std::numeric_limits<int>::max()),
    m_transverseMomentum(std::numeric_limits<double>::max()),
    m_transverseMomentumBosonW1(std::numeric_limits<double>::max()),
    m_transverseMomentumBosonW2(std::numeric_limits<double>::max()),
    m_transverseMomentumBosonZ1(std::numeric_limits<double>::max()),
    m_transverseMomentumBosonZ2(std::numeric_limits<double>::max()),
    m_transverseMomentumMC(std::numeric_limits<double>::max()),
    m_transverseEnergy(std::numeric_limits<double>::max()),
    m_transverseEnergyBosonW1(std::numeric_limits<double>::max()),
    m_transverseEnergyBosonW2(std::numeric_limits<double>::max()),
    m_transverseEnergyBosonZ1(std::numeric_limits<double>::max()),
    m_transverseEnergyBosonZ2(std::numeric_limits<double>::max()),
    m_transverseEnergyMC(std::numeric_limits<double>::max()),
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
    m_invariantMassWBosons1(std::numeric_limits<double>::max()),
    m_invariantMassWBosons2(std::numeric_limits<double>::max()),
    m_invariantMassWBosonsMC1(std::numeric_limits<double>::max()),
    m_invariantMassWBosonsMC2(std::numeric_limits<double>::max()),
    m_invariantMassZBosons1(std::numeric_limits<double>::max()),
    m_invariantMassZBosons2(std::numeric_limits<double>::max()),
    m_invariantMassZBosonsMC1(std::numeric_limits<double>::max()),
    m_invariantMassZBosonsMC2(std::numeric_limits<double>::max()),
    m_energyJets1(std::numeric_limits<double>::max()),
    m_energyJets2(std::numeric_limits<double>::max()),
    m_energyJets3(std::numeric_limits<double>::max()),
    m_energyJets4(std::numeric_limits<double>::max()),
    m_cosThetaStarWJets1(std::numeric_limits<double>::max()),
    m_cosThetaStarWJets2(std::numeric_limits<double>::max()),
    m_cosThetaStarZJets1(std::numeric_limits<double>::max()),
    m_cosThetaStarZJets2(std::numeric_limits<double>::max()),
    m_bTagForJets1(std::numeric_limits<double>::max()),
    m_bTagForJets2(std::numeric_limits<double>::max()),
    m_bTagForJets3(std::numeric_limits<double>::max()),
    m_bTagForJets4(std::numeric_limits<double>::max()),
    m_cTagForJets1(std::numeric_limits<double>::max()),
    m_cTagForJets2(std::numeric_limits<double>::max()),
    m_cTagForJets3(std::numeric_limits<double>::max()),
    m_cTagForJets4(std::numeric_limits<double>::max()),
    m_bdt(std::numeric_limits<double>::max())
{
}

//===========================================================

Variables::~Variables()
{
}

//===========================================================

void Variables::SetBranchAddresses(TChain *pTChain, bool postMVA)
{
// Variables Of Interest
// Bools
    pTChain->SetBranchAddress("IsAppropriateEvent", &m_appropriateEvent);
    pTChain->SetBranchAddress("IsEventWW", &m_isEventWW);
    pTChain->SetBranchAddress("IsMCEventWW", &m_isEventWWMC);
    pTChain->SetBranchAddress("IsEventZZ", &m_isEventZZ);
    pTChain->SetBranchAddress("IsMCEventZZ", &m_isEventZZMC);

// Ints
    pTChain->SetBranchAddress("NPfosBosonW1", &m_nPfosBosonW1);
    pTChain->SetBranchAddress("NPfosBosonW2", &m_nPfosBosonW2);
    pTChain->SetBranchAddress("NPfosBosonZ1", &m_nPfosBosonZ1);
    pTChain->SetBranchAddress("NPfosBosonZ2", &m_nPfosBosonZ2);
    pTChain->SetBranchAddress("WBosonJet1Is", &m_combinationWJets1);
    pTChain->SetBranchAddress("WBosonJet2Is", &m_combinationWJets2);
    pTChain->SetBranchAddress("WBosonJet3Is", &m_combinationWJets3);
    pTChain->SetBranchAddress("WBosonJet4Is", &m_combinationWJets4);
    pTChain->SetBranchAddress("ZBosonJet1Is", &m_combinationZJets1);
    pTChain->SetBranchAddress("ZBosonJet2Is", &m_combinationZJets2);
    pTChain->SetBranchAddress("ZBosonJet3Is", &m_combinationZJets3);
    pTChain->SetBranchAddress("ZBosonJet4Is", &m_combinationZJets4);
    pTChain->SetBranchAddress("NParticlesJet1", &m_nParticlesJets1);
    pTChain->SetBranchAddress("NParticlesJet2", &m_nParticlesJets2);
    pTChain->SetBranchAddress("NParticlesJet3", &m_nParticlesJets3);
    pTChain->SetBranchAddress("NParticlesJet4", &m_nParticlesJets4);
    pTChain->SetBranchAddress("NChargedParticlesJet1", &m_nChargedParticlesJets1);
    pTChain->SetBranchAddress("NChargedParticlesJet2", &m_nChargedParticlesJets2);
    pTChain->SetBranchAddress("NChargedParticlesJet3", &m_nChargedParticlesJets3);
    pTChain->SetBranchAddress("NChargedParticlesJet4", &m_nChargedParticlesJets4);
    pTChain->SetBranchAddress("HighestEnergyPfoPDG", &m_highestEnergyPfoPDG);
    pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &m_nIsolatedLeptons);
    pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonPDG", &m_highestEnergyIsolatedLeptonPDG);
    pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonPDG", &m_secondHighestEnergyIsolatedLeptonPDG);

// Doubles
    pTChain->SetBranchAddress("TransverseMomentum", &m_transverseMomentum);
    pTChain->SetBranchAddress("TransverseMomentumBosonW1", &m_transverseMomentumBosonW1);
    pTChain->SetBranchAddress("TransverseMomentumBosonW2", &m_transverseMomentumBosonW2);
    pTChain->SetBranchAddress("TransverseMomentumBosonZ1", &m_transverseMomentumBosonZ1);
    pTChain->SetBranchAddress("TransverseMomentumBosonZ2", &m_transverseMomentumBosonZ2);
    pTChain->SetBranchAddress("MCTransverseMomentum", &m_transverseMomentumMC);
    pTChain->SetBranchAddress("TransverseEnergy", &m_transverseEnergy);
    pTChain->SetBranchAddress("TransverseEnergyBosonW1", &m_transverseEnergyBosonW1);
    pTChain->SetBranchAddress("TransverseEnergyBosonW2", &m_transverseEnergyBosonW2);
    pTChain->SetBranchAddress("TransverseEnergyBosonZ1", &m_transverseEnergyBosonZ1);
    pTChain->SetBranchAddress("TransverseEnergyBosonZ2", &m_transverseEnergyBosonZ2);
    pTChain->SetBranchAddress("MCTransverseEnergy", &m_transverseEnergyMC);
    pTChain->SetBranchAddress("CosThetaMissing", &m_cosThetaMissing);
    pTChain->SetBranchAddress("MCCosThetaMissing", &m_cosThetaMissingMC);
    pTChain->SetBranchAddress("CosThetaMostEnergeticTrack", &m_cosThetaMostEnergeticTrack);
    pTChain->SetBranchAddress("RecoilMass", &m_recoilMass);
    pTChain->SetBranchAddress("MCRecoilMass", &m_recoilMassMC);
    pTChain->SetBranchAddress("EnergyAroundMostEnergeticTrack", &m_energyAroundMostEnergeticPfo);
    pTChain->SetBranchAddress("y12", &m_y12);
    pTChain->SetBranchAddress("y23", &m_y23);
    pTChain->SetBranchAddress("y34", &m_y34);
    pTChain->SetBranchAddress("y45", &m_y45);
    pTChain->SetBranchAddress("y56", &m_y56);
    pTChain->SetBranchAddress("y67", &m_y67);
    pTChain->SetBranchAddress("InvariantMassSystem", &m_invariantMassSystem);
    pTChain->SetBranchAddress("MCInvariantMassSystem", &m_invariantMassSystemMC);
    pTChain->SetBranchAddress("CosThetaStarWBosons", &m_cosThetaStarWBosons);
    pTChain->SetBranchAddress("MCCosThetaStarWBosons", &m_cosThetaStarWBosonsMC);
    pTChain->SetBranchAddress("CosThetaStarZBosons", &m_cosThetaStarZBosons);
    pTChain->SetBranchAddress("MCCosThetaStarZBosons", &m_cosThetaStarZBosonsMC);
    pTChain->SetBranchAddress("AcolinearityJetsW1", &m_acolinearityJetsW1);
    pTChain->SetBranchAddress("AcolinearityJetsW2", &m_acolinearityJetsW2);
    pTChain->SetBranchAddress("AcolinearityJetsZ1", &m_acolinearityJetsZ1);
    pTChain->SetBranchAddress("AcolinearityJetsZ2", &m_acolinearityJetsZ2);
    pTChain->SetBranchAddress("AcolinearityBosonsW", &m_acolinearityBosonsW);
    pTChain->SetBranchAddress("AcolinearityBosonsZ", &m_acolinearityBosonsZ);
    pTChain->SetBranchAddress("PrincipleThrustValue", &m_principleThrustValue);
    pTChain->SetBranchAddress("MajorThrustValue", &m_majorThrustValue);
    pTChain->SetBranchAddress("MinorThrustValue", &m_minorThrustValue);
    pTChain->SetBranchAddress("XThrustAxis", &m_xThrustAxis);
    pTChain->SetBranchAddress("YThrustAxis", &m_yThrustAxis);
    pTChain->SetBranchAddress("ZThrustAxis", &m_zThrustAxis);
    pTChain->SetBranchAddress("Sphericity", &m_sphericity);
    pTChain->SetBranchAddress("Aplanarity", &m_aplanarity);
    pTChain->SetBranchAddress("HighestEnergyElectronEnergy", &m_highestEnergyElectronE);
    pTChain->SetBranchAddress("HighestEnergyElectronMomentum", &m_highestEnergyElectronP);
    pTChain->SetBranchAddress("HighestEnergyElectronTransverseMomentum", &m_highestEnergyElectronPt);
    pTChain->SetBranchAddress("HighestEnergyElectronCosTheta", &m_highestEnergyElectronCosTheta);
    pTChain->SetBranchAddress("HighestEnergyMuonEnergy", &m_highestEnergyMuonE);
    pTChain->SetBranchAddress("HighestEnergyMuonMomentum", &m_highestEnergyMuonP);
    pTChain->SetBranchAddress("HighestEnergyMuonTransverseMomentum", &m_highestEnergyMuonPt);
    pTChain->SetBranchAddress("HighestEnergyMuonCosTheta", &m_highestEnergyMuonCosTheta);
    pTChain->SetBranchAddress("HighestEnergyPhotonEnergy", &m_highestEnergyPhotonE);
    pTChain->SetBranchAddress("HighestEnergyPhotonMomentum", &m_highestEnergyPhotonP);
    pTChain->SetBranchAddress("HighestEnergyPhotonTransverseMomentum", &m_highestEnergyPhotonPt);
    pTChain->SetBranchAddress("HighestEnergyPhotonCosTheta", &m_highestEnergyPhotonCosTheta);
    pTChain->SetBranchAddress("HighestEnergyPfoEnergy", &m_highestEnergyPfoE);
    pTChain->SetBranchAddress("HighestEnergyPfoMomentum", &m_highestEnergyPfoP);
    pTChain->SetBranchAddress("HighestEnergyPfoTransverseMomentum", &m_highestEnergyPfoPt);
    pTChain->SetBranchAddress("HighestEnergyPfoCosTheta", &m_highestEnergyPfoCosTheta);
    pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonEnergy", &m_highestEnergyIsolatedLeptonE);
    pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonMomentum", &m_highestEnergyIsolatedLeptonP);
    pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonTransverseMomentum", &m_highestEnergyIsolatedLeptonPt);
    pTChain->SetBranchAddress("HighestEnergyIsolatedLeptonCosTheta", &m_highestEnergyIsolatedLeptonCosTheta);
    pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonEnergy", &m_secondHighestEnergyIsolatedLeptonE);
    pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonMomentum", &m_secondHighestEnergyIsolatedLeptonP);
    pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonTransverseMomentum", &m_secondHighestEnergyIsolatedLeptonPt);
    pTChain->SetBranchAddress("SecondHighestEnergyIsolatedLeptonCosTheta", &m_secondHighestEnergyIsolatedLeptonCosTheta);
    pTChain->SetBranchAddress("InvMassWVector1", &m_invariantMassWBosons1);
    pTChain->SetBranchAddress("InvMassWVector2", &m_invariantMassWBosons2);
    pTChain->SetBranchAddress("MCInvMassWVector1", &m_invariantMassWBosonsMC1);
    pTChain->SetBranchAddress("MCInvMassWVector2", &m_invariantMassWBosonsMC2);
    pTChain->SetBranchAddress("InvMassZVector1", &m_invariantMassZBosons1);
    pTChain->SetBranchAddress("InvMassZVector2", &m_invariantMassZBosons2);
    pTChain->SetBranchAddress("MCInvMassZVector1", &m_invariantMassZBosonsMC1);
    pTChain->SetBranchAddress("MCInvMassZVector2", &m_invariantMassZBosonsMC2);
    pTChain->SetBranchAddress("EnergyJet1", &m_energyJets1);
    pTChain->SetBranchAddress("EnergyJet2", &m_energyJets2);
    pTChain->SetBranchAddress("EnergyJet3", &m_energyJets3);
    pTChain->SetBranchAddress("EnergyJet4", &m_energyJets4);
    pTChain->SetBranchAddress("CosThetaStarWJet1", &m_cosThetaStarWJets1);
    pTChain->SetBranchAddress("CosThetaStarWJet2", &m_cosThetaStarWJets2);
    pTChain->SetBranchAddress("CosThetaStarZJet1", &m_cosThetaStarZJets1);
    pTChain->SetBranchAddress("CosThetaStarZJet2", &m_cosThetaStarZJets2);
    pTChain->SetBranchAddress("BTagForJet1", &m_bTagForJets1);
    pTChain->SetBranchAddress("BTagForJet2", &m_bTagForJets2);
    pTChain->SetBranchAddress("BTagForJet3", &m_bTagForJets3);
    pTChain->SetBranchAddress("BTagForJet4", &m_bTagForJets4);
    pTChain->SetBranchAddress("CTagForJet1", &m_cTagForJets1);
    pTChain->SetBranchAddress("CTagForJet2", &m_cTagForJets2);
    pTChain->SetBranchAddress("CTagForJet3", &m_cTagForJets3);
    pTChain->SetBranchAddress("CTagForJet4", &m_cTagForJets4);

    if (postMVA)
    {
        pTChain->SetBranchAddress("GlobalEventNumber", &m_globalEventNumber);
        pTChain->SetBranchAddress("BDT", &m_bdt);
    }
}

//===========================================================

void Variables::Print()
{
    std::cout << "m_appropriateEvent             : " << m_appropriateEvent << std::endl;
    std::cout << "m_isEventWW                    : " << m_isEventWW << std::endl;
    std::cout << "m_isEventWWMC                  : " << m_isEventWWMC << std::endl;
    std::cout << "m_isEventZZ                    : " << m_isEventZZ << std::endl;
    std::cout << "m_isEventZZMC                  : " << m_isEventZZMC << std::endl;
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
    m_combinationWJets1 = std::numeric_limits<int>::max();
    m_combinationWJets2 = std::numeric_limits<int>::max();
    m_combinationWJets3 = std::numeric_limits<int>::max();
    m_combinationWJets4 = std::numeric_limits<int>::max();
    m_combinationZJets1 = std::numeric_limits<int>::max();
    m_combinationZJets2 = std::numeric_limits<int>::max();
    m_combinationZJets3 = std::numeric_limits<int>::max();
    m_combinationZJets4 = std::numeric_limits<int>::max();
    m_nParticlesJets1 = std::numeric_limits<int>::max();
    m_nParticlesJets2 = std::numeric_limits<int>::max();
    m_nParticlesJets3 = std::numeric_limits<int>::max();
    m_nParticlesJets4 = std::numeric_limits<int>::max();
    m_nChargedParticlesJets1= std::numeric_limits<int>::max();
    m_nChargedParticlesJets2= std::numeric_limits<int>::max();
    m_nChargedParticlesJets3= std::numeric_limits<int>::max();
    m_nChargedParticlesJets4= std::numeric_limits<int>::max();
    m_highestEnergyPfoPDG = std::numeric_limits<int>::max();
    m_nIsolatedLeptons = std::numeric_limits<int>::max();
    m_highestEnergyIsolatedLeptonPDG = std::numeric_limits<int>::max();
    m_secondHighestEnergyIsolatedLeptonPDG = std::numeric_limits<int>::max();
    m_globalEventNumber = std::numeric_limits<int>::max();

    m_transverseMomentum = std::numeric_limits<double>::max();
    m_transverseMomentumBosonW1 = std::numeric_limits<double>::max();
    m_transverseMomentumBosonW2 = std::numeric_limits<double>::max();
    m_transverseMomentumBosonZ1 = std::numeric_limits<double>::max();
    m_transverseMomentumBosonZ2 = std::numeric_limits<double>::max();
    m_transverseMomentumMC = std::numeric_limits<double>::max();
    m_transverseEnergy = std::numeric_limits<double>::max();
    m_transverseEnergyBosonW1 = std::numeric_limits<double>::max();
    m_transverseEnergyBosonW2 = std::numeric_limits<double>::max();
    m_transverseEnergyBosonZ1 = std::numeric_limits<double>::max();
    m_transverseEnergyBosonZ2 = std::numeric_limits<double>::max();
    m_transverseEnergyMC = std::numeric_limits<double>::max();
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
    m_invariantMassWBosons1 = std::numeric_limits<double>::max();
    m_invariantMassWBosons2 = std::numeric_limits<double>::max();
    m_invariantMassWBosonsMC1 = std::numeric_limits<double>::max();
    m_invariantMassWBosonsMC2 = std::numeric_limits<double>::max();
    m_invariantMassZBosons1 = std::numeric_limits<double>::max();
    m_invariantMassZBosons2 = std::numeric_limits<double>::max();
    m_invariantMassZBosonsMC1 = std::numeric_limits<double>::max();
    m_invariantMassZBosonsMC2 = std::numeric_limits<double>::max();
    m_energyJets1 = std::numeric_limits<double>::max();
    m_energyJets2 = std::numeric_limits<double>::max();
    m_energyJets3 = std::numeric_limits<double>::max();
    m_energyJets4 = std::numeric_limits<double>::max();
    m_cosThetaStarWJets1 = std::numeric_limits<double>::max();
    m_cosThetaStarWJets2 = std::numeric_limits<double>::max();
    m_cosThetaStarZJets1 = std::numeric_limits<double>::max();
    m_cosThetaStarZJets2 = std::numeric_limits<double>::max();
    m_bTagForJets1 = std::numeric_limits<double>::max();
    m_bTagForJets2 = std::numeric_limits<double>::max();
    m_bTagForJets3 = std::numeric_limits<double>::max();
    m_bTagForJets4 = std::numeric_limits<double>::max();
    m_cTagForJets1 = std::numeric_limits<double>::max();
    m_cTagForJets2 = std::numeric_limits<double>::max();
    m_cTagForJets3 = std::numeric_limits<double>::max();
    m_cTagForJets4 = std::numeric_limits<double>::max();
    m_bdt = std::numeric_limits<double>::max();
}

//===========================================================

void Variables::SplitJetsForFlavourTaggingW(double &bTagW11, double &bTagW12, double &bTagW21, double &bTagW22, double &cTagW11, double &cTagW12, double &cTagW21, double &cTagW22) const
{
    if (m_combinationWJets1 == 0 and m_combinationWJets2 == 1 or m_combinationWJets1 == 1 and m_combinationWJets2 == 0)
    {
        bTagW11 = m_bTagForJets1;
        bTagW12 = m_bTagForJets2;
        bTagW21 = m_bTagForJets3;
        bTagW22 = m_bTagForJets4;
        cTagW11 = m_cTagForJets1;
        cTagW12 = m_cTagForJets2;
        cTagW21 = m_cTagForJets3;
        cTagW22 = m_cTagForJets4;
    }
    else if (m_combinationWJets1 == 0 and m_combinationWJets2 == 2 or m_combinationWJets1 == 2 and m_combinationWJets2 == 0)
    {
        bTagW11 = m_bTagForJets1;
        bTagW12 = m_bTagForJets3;
        bTagW21 = m_bTagForJets2;
        bTagW22 = m_bTagForJets4;
        cTagW11 = m_cTagForJets1;
        cTagW12 = m_cTagForJets3;
        cTagW21 = m_cTagForJets2;
        cTagW22 = m_cTagForJets4;
    }
    else if (m_combinationWJets1 == 0 and m_combinationWJets2 == 3 or m_combinationWJets1 == 3 and m_combinationWJets2 == 0)
    {
        bTagW11 = m_bTagForJets1;
        bTagW12 = m_bTagForJets4;
        bTagW21 = m_bTagForJets2;
        bTagW22 = m_bTagForJets3;
        cTagW11 = m_cTagForJets1;
        cTagW12 = m_cTagForJets4;
        cTagW21 = m_cTagForJets2;
        cTagW22 = m_cTagForJets3;
    }
}

//===========================================================

void Variables::FlavourTagSettingW(double &highestBTagW1, double &lowestBTagW1, double &highestBTagW2, double &lowestBTagW2, double &highestCTagW1, double &lowestCTagW1, double &highestCTagW2, double &lowestCTagW2) const
{
    double bTagW11(0.0), bTagW12(0.0), bTagW21(0.0), bTagW22(0.0), cTagW11(0.0), cTagW12(0.0), cTagW21(0.0), cTagW22(0.0);
    this->SplitJetsForFlavourTaggingW(bTagW11, bTagW12, bTagW21, bTagW22, cTagW11, cTagW12, cTagW21, cTagW22);

    if (bTagW11 > bTagW12)
    {
        highestBTagW1 = bTagW11;
        lowestBTagW1 = bTagW12;
    }
    else
    {
        highestBTagW1 = bTagW12;
        lowestBTagW1 = bTagW11;
    }

    if (bTagW21 > bTagW22)
    {
        highestBTagW2 = bTagW21;
        lowestBTagW2 = bTagW22;
    }
    else
    {
        highestBTagW2 = bTagW22;
        lowestBTagW2 = bTagW21;
    }

    if (cTagW11 > cTagW12)
    {
        highestCTagW1 = cTagW11;
        lowestCTagW1 = cTagW12;
    }
    else
    {
        highestCTagW1 = cTagW12;
        lowestCTagW1 = cTagW11;
    }

    if (cTagW21 > cTagW22)
    {
        highestCTagW2 = cTagW21;
        lowestCTagW2 = cTagW22;
    }
    else
    {
        highestCTagW2 = cTagW22;
        lowestCTagW2 = cTagW21;
    }
} 

//===========================================================

void Variables::SplitJetsForFlavourTaggingZ(double &bTagZ11, double &bTagZ12, double &bTagZ21, double &bTagZ22, double &cTagZ11, double &cTagZ12, double &cTagZ21, double &cTagZ22) const
{
    if (m_combinationZJets1 == 0 and m_combinationZJets2 == 1 or m_combinationZJets1 == 1 and m_combinationZJets2 == 0)
    {
        bTagZ11 = m_bTagForJets1;
        bTagZ12 = m_bTagForJets2;
        bTagZ21 = m_bTagForJets3;
        bTagZ22 = m_bTagForJets4;
        cTagZ11 = m_cTagForJets1;
        cTagZ12 = m_cTagForJets2;
        cTagZ21 = m_cTagForJets3;
        cTagZ22 = m_cTagForJets4;
    }
    else if (m_combinationZJets1 == 0 and m_combinationZJets2 == 2 or m_combinationZJets1 == 2 and m_combinationZJets2 == 0)
    {
        bTagZ11 = m_bTagForJets1;
        bTagZ12 = m_bTagForJets3;
        bTagZ21 = m_bTagForJets2;
        bTagZ22 = m_bTagForJets4;
        cTagZ11 = m_cTagForJets1;
        cTagZ12 = m_cTagForJets3;
        cTagZ21 = m_cTagForJets2;
        cTagZ22 = m_cTagForJets4;
    }
    else if (m_combinationZJets1 == 0 and m_combinationZJets2 == 3 or m_combinationZJets1 == 3 and m_combinationZJets2 == 0)
    {
        bTagZ11 = m_bTagForJets1;
        bTagZ12 = m_bTagForJets4;
        bTagZ21 = m_bTagForJets2;
        bTagZ22 = m_bTagForJets3;
        cTagZ11 = m_cTagForJets1;
        cTagZ12 = m_cTagForJets4;
        cTagZ21 = m_cTagForJets2;
        cTagZ22 = m_cTagForJets3;
    }
}

//===========================================================

void Variables::FlavourTagSettingZ(double &highestBTagZ1, double &lowestBTagZ1, double &highestBTagZ2, double &lowestBTagZ2, double &highestCTagZ1, double &lowestCTagZ1, double &highestCTagZ2, double &lowestCTagZ2) const
{
    double bTagZ11(0.0), bTagZ12(0.0), bTagZ21(0.0), bTagZ22(0.0), cTagZ11(0.0), cTagZ12(0.0), cTagZ21(0.0), cTagZ22(0.0);
    this->SplitJetsForFlavourTaggingZ(bTagZ11, bTagZ12, bTagZ21, bTagZ22, cTagZ11, cTagZ12, cTagZ21, cTagZ22);

    if (bTagZ11 > bTagZ12)
    {
        highestBTagZ1 = bTagZ11;
        lowestBTagZ1 = bTagZ12;
    }
    else
    {
        highestBTagZ1 = bTagZ12;
        lowestBTagZ1 = bTagZ11;
    }

    if (bTagZ21 > bTagZ22)
    {
        highestBTagZ2 = bTagZ21;
        lowestBTagZ2 = bTagZ22;
    }
    else
    {
        highestBTagZ2 = bTagZ22;
        lowestBTagZ2 = bTagZ21;
    }

    if (cTagZ11 > cTagZ12)
    {
        highestCTagZ1 = cTagZ11;
        lowestCTagZ1 = cTagZ12;
    }
    else
    {
        highestCTagZ1 = cTagZ12;
        lowestCTagZ1 = cTagZ11;
    }

    if (cTagZ21 > cTagZ22)
    {
        highestCTagZ2 = cTagZ21;
        lowestCTagZ2 = cTagZ22;
    }
    else
    {
        highestCTagZ2 = cTagZ22;
        lowestCTagZ2 = cTagZ21;
    }
}

//===========================================================

void Variables::SplitJetsForBosonEnergiesW(double &jetEW11, double &jetEW12, double &jetEW21, double &jetEW22) const
{
    if (m_combinationWJets1 == 0 and m_combinationWJets2 == 1 or m_combinationWJets1 == 1 and m_combinationWJets2 == 0)
    {
        jetEW11 = m_energyJets1; 
        jetEW12 = m_energyJets2; 
        jetEW21 = m_energyJets3; 
        jetEW22 = m_energyJets4; 
    }
    else if (m_combinationWJets1 == 0 and m_combinationWJets2 == 2 or m_combinationWJets1 == 2 and m_combinationWJets2 == 0)
    {
        jetEW11 = m_energyJets1;
        jetEW12 = m_energyJets3;
        jetEW21 = m_energyJets2;
        jetEW22 = m_energyJets4;
    }
    else if (m_combinationWJets1 == 0 and m_combinationWJets2 == 3 or m_combinationWJets1 == 3 and m_combinationWJets2 == 0)
    {
        jetEW11 = m_energyJets1;
        jetEW12 = m_energyJets4;
        jetEW21 = m_energyJets2;
        jetEW22 = m_energyJets3;
    }
}

//===========================================================

void Variables::SplitJetsForBosonEnergiesZ(double &jetEZ11, double &jetEZ12, double &jetEZ21, double &jetEZ22) const
{
    if (m_combinationZJets1 == 0 and m_combinationZJets2 == 1 or m_combinationZJets1 == 1 and m_combinationZJets2 == 0)
    {
        jetEZ11 = m_energyJets1;
        jetEZ12 = m_energyJets2;
        jetEZ21 = m_energyJets3;
        jetEZ22 = m_energyJets4;
    }
    else if (m_combinationZJets1 == 0 and m_combinationZJets2 == 2 or m_combinationZJets1 == 2 and m_combinationZJets2 == 0)
    {
        jetEZ11 = m_energyJets1;
        jetEZ12 = m_energyJets3;
        jetEZ21 = m_energyJets2;
        jetEZ22 = m_energyJets4;
    }
    else if (m_combinationZJets1 == 0 and m_combinationZJets2 == 3 or m_combinationZJets1 == 3 and m_combinationZJets2 == 0)
    {
        jetEZ11 = m_energyJets1;
        jetEZ12 = m_energyJets4;
        jetEZ21 = m_energyJets2;
        jetEZ22 = m_energyJets3;
    }
}

//===========================================================
