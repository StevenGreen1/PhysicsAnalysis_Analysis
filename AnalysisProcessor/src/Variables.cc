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
    m_highestEnergyPfoCosTheta(std::numeric_limits<double>::max())
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

// IntVectors
//    pTTree->Branch("NParticlesJets", &m_nParticlesJets);
//    pTTree->Branch("NChargedParticlesJets", &m_nChargedParticlesJets);

// Floats
    pTTree->Branch("TransverseMomentum", &m_transverseMomentum, "TransverseMomentum/D");
    pTTree->Branch("TransverseMomentumBosonW1", &m_transverseMomentumBosonW1, "TransverseMomentumBosonW1/D");
    pTTree->Branch("TransverseMomentumBosonW2", &m_transverseMomentumBosonW2, "TransverseMomentumBosonW2/D");
    pTTree->Branch("TransverseMomentumBosonZ1", &m_transverseMomentumBosonZ1, "TransverseMomentumBosonZ1/D");
    pTTree->Branch("TransverseMomentumBosonZ2", &m_transverseMomentumBosonZ2, "TransverseMomentumBosonZ2/D");
    pTTree->Branch("MCTransverseMomentum", &m_transverseMomentumMC, "MCTransverseMomentum/D");
    pTTree->Branch("TransverseEnergy", &m_transverseEnergy, "TransverseEnergy/D");
    pTTree->Branch("TransverseEnergyBosonW1", &m_transverseEnergyBosonW1, "TransverseEnergyBosonW1/D");
    pTTree->Branch("TransverseEnergyBosonW2", &m_transverseEnergyBosonW2, "TransverseEnergyBosonW2/D");
    pTTree->Branch("TransverseEnergyBosonZ1", &m_transverseEnergyBosonZ1, "TransverseEnergyBosonZ1/D");
    pTTree->Branch("TransverseEnergyBosonZ2", &m_transverseEnergyBosonZ2, "TransverseEnergyBosonZ2/D");
    pTTree->Branch("MCTransverseEnergy", &m_transverseEnergyMC, "MCTransverseEnergy/D");
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
    m_invariantMassWBosons.resize(2);
    pTTree->Branch("InvMassWVector1", &m_invariantMassWBosons.at(0), "InvMassWVector1/D");
    pTTree->Branch("InvMassWVector2", &m_invariantMassWBosons.at(1), "InvMassWVector2/D");
    m_invariantMassWBosonsMC.resize(2);
    pTTree->Branch("MCInvMassWVector1", &m_invariantMassWBosonsMC.at(0), "MCInvMassWVector1/D");
    pTTree->Branch("MCInvMassWVector2", &m_invariantMassWBosonsMC.at(1), "MCInvMassWVector2/D");
    m_invariantMassZBosons.resize(2);
    pTTree->Branch("InvMassZVector1", &m_invariantMassZBosons.at(0), "InvMassZVector1/D");
    pTTree->Branch("InvMassZVector2", &m_invariantMassZBosons.at(1), "InvMassZVector2/D");
    m_invariantMassZBosonsMC.resize(2);
    pTTree->Branch("MCInvMassZVector1", &m_invariantMassZBosonsMC.at(0), "MCInvMassZVector1/D");
    pTTree->Branch("MCInvMassZVector2", &m_invariantMassZBosonsMC.at(1), "MCInvMassZVector2/D");
    m_energyJets.resize(4);
    pTTree->Branch("EnergyJet1", &m_energyJets.at(0), "EnergyJet1/D");
    pTTree->Branch("EnergyJet2", &m_energyJets.at(1), "EnergyJet2/D");
    pTTree->Branch("EnergyJet3", &m_energyJets.at(2), "EnergyJet3/D");
    pTTree->Branch("EnergyJet4", &m_energyJets.at(3), "EnergyJet4/D");
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

// DoubleVectors
//    pTTree->Branch("InvMassWVectors", &m_invariantMassWBosons);
//    pTTree->Branch("MCInvMassWVectors", &m_invariantMassWBosonsMC);
//    pTTree->Branch("InvMassZVectors", &m_invariantMassZBosons);
//    pTTree->Branch("MCInvMassZVectors", &m_invariantMassZBosonsMC);
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

    m_combinationWJets.clear();
    m_combinationZJets.clear();
    m_nParticlesJets.clear();
    m_nChargedParticlesJets.clear();

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

    m_invariantMassWBosons.clear();
    m_invariantMassWBosonsMC.clear();
    m_invariantMassZBosons.clear();
    m_invariantMassZBosonsMC.clear();
    m_energyJets.clear();
    m_cosThetaStarWJets.clear();
    m_cosThetaStarZJets.clear();
    m_bTagForJets.clear();
    m_cTagForJets.clear();
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

//=========================================================== DoubleVector

void Variables::SetInvMassWVectors(DoubleVector invMassWVectors)
{
    m_invariantMassWBosons = invMassWVectors;
}

//===========================================================

DoubleVector Variables::GetInvMassWVectors() const 
{
    return m_invariantMassWBosons;
}

//===========================================================

void Variables::SetInvMassZVectors(DoubleVector invMassZVectors)
{
    m_invariantMassZBosons = invMassZVectors;
}

//===========================================================

DoubleVector Variables::GetInvMassZVectors() const 
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

