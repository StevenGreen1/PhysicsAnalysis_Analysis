/**
 *  @file   SelectionProcessor/include/Variables.h
 * 
 *  @brief  Header file for the variables class.
 * 
 *  $Log: $
 */

#ifndef VARIABLES_H
#define VARIABLES_H 1

#include <iostream>
#include <limits>
#include <vector>

#include "EVENT/LCParameters.h"

#include "TInterpreter.h"
#include "TTree.h"

namespace variables_namespace
{
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;
}

using namespace variables_namespace;

class Variables
{
    public:
        /**
         *  @brief Constructor
         */
        Variables();

        /**
         *  @brief Destructor
         */
        ~Variables();

        /**
         *  @brief Set branch addresses for interesting variables
         *
         *  @param pTTree root tree to write variables to
         */
        void SetBranches(TTree *pTTree);

        /**
         *  @brief Print to screen all bool, int, double and selected vector member variables
         */
        void Print();

        /**
         *  @brief Reset all variables for next event
         */
        void Clear();


        /**
         *  @brief Set all parameters related to the LCParameters object for the event
         */
        void SetLCParameterInfo(const EVENT::LCParameters &lcParameters);

// Bools

        /**
         *  @brief Set m_appropriateEvent
         *
         *  @param appropriateEvent Does event mass cuts to suggest vvqqqq final state
         */
        void SetAppropriateEvent(bool appropriateEvent);

        /**
         *  @brief Get m_appropriateEvent
         */
        bool GetAppropriateEvent() const;

        /**
         *  @brief Set m_isEventWW
         *
         *  @param isEventWW Are the invariant masses of the jets close to the W boson mass
         */
        void SetIsEventWW(bool isEventWW);

        /*
         *  @brief Get m_isEventWW
         */
        bool GetIsEventWW() const;

        /**
         *  @brief Set m_isEventWWMC
         *
         *  @param isEventWWMC Are the invariant masses of the quarks close to the W boson mass
         */
        void SetIsEventWWMC(bool isEventWWMC);

        /*
         *  @brief Get m_isEventWWMC
         */
        bool GetIsEventWWMC() const;

        /**
         *  @brief Set m_isEventZZ
         *
         *  @param isEventZZ Are the invariant masses of the jets close to the Z boson mass
         */
        void SetIsEventZZ(bool isEventZZ);

        /*
         *  @brief Get m_isEventZZ
         */
        bool GetIsEventZZ() const;

        /**
         *  @brief Set m_isEventZZMC
         *
         *  @param isEventZZMC Are the invariant masses of the quarks close to the Z boson mass
         */
        void SetIsEventZZMC(bool isEventZZMC);

        /*
         *  @brief Get m_isEventZZMC
         */
        bool GetIsEventZZMC() const;

// Ints

        /**
         *  @brief Set m_nPfosBosonW1
         *
         *  @param nPfosBosonW1 Number of pfos in W boson 1 in W pairing 
         */
        void SetNPfosBosonW1(int nPfosBosonW1);

        /*
         *  @brief Get m_nPfosBosonW1
         */
        int GetNPfosBosonW1() const;

        /**
         *  @brief Set m_nPfosBosonW2
         *
         *  @param nPfosBosonW2 Number of pfos in W boson 2 in W pairing
         */
        void SetNPfosBosonW2(int nPfosBosonW2);

        /*
         *  @brief Get m_nPfosBosonW2
         */
        int GetNPfosBosonW2() const;

        /**
         *  @brief Set m_nPfosBosonZ1
         *
         *  @param nPfosBosonZ1 Number of pfos in Z boson 1 in Z pairing
         */
        void SetNPfosBosonZ1(int nPfosBosonZ1);

        /*
         *  @brief Get m_nPfosBosonZ1
         */
        int GetNPfosBosonZ1() const;

        /**
         *  @brief Set m_nPfosBosonZ2
         *
         *  @param nPfosBosonZ2 Number of pfos in Z boson 2 in Z pairing
         */
        void SetNPfosBosonZ2(int nPfosBosonZ2);

        /*
         *  @brief Get m_nPfosBosonZ2
         */
        int GetNPfosBosonZ2() const;

// IntVectors

        /**
         *  @brief Set m_combinationWJets
         *
         *  @param combinationWJets The combination of jets to form W bosons
         */
        void SetJetCombinationW(IntVector combinationWJets);

        /**
         *  @brief Get m_combinationWJets
         */
        IntVector GetJetCombinationW() const;

        /**
         *  @brief Set m_combinationZJets
         *
         *  @param combinationZJets The combination of jets to form Z bosons
         */
        void SetJetCombinationZ(IntVector combinationZJets);

        /**
         *  @brief Get m_combinationZJets
         */
        IntVector GetJetCombinationZ() const;

        /**
         *  @brief Set m_nParticlesJets
         *
         *  @param nParticlesJets The number of particles in jets
         */
        void SetNParticlesJets(IntVector nParticlesJets);

        /**
         *  @brief Get m_nParticlesJets
         */
        IntVector GetNParticlesJets() const;

        /**
         *  @brief Get lowest number in m_nParticlesJets
         */
        int GetLowestNParticlesJets() const;

        /**
         *  @brief Set m_nChargedParticlesJets
         *
         *  @param nChargedParticlesJets The number of charged particles in jets
         */
        void SetNChargedParticlesJets(IntVector nChargedParticlesJets);

        /**
         *  @brief Get m_nChargedParticlesJets
         */
        IntVector GetNChargedParticlesJets() const;

        /**
         *  @brief Get lowest number in m_nChargedParticlesJets
         */
        int GetLowestNChargedParticlesJets() const;

// Floats

        /**
         *  @brief Set m_transverseMomentum
         *
         *  @param transverseMomentum Transverse momentum of reconstructed system
         */
        void SetTransverseMomentum(double transverseMomentum);

        /**
         *  @brief Get m_transverseMomentum
         */
        double GetTransverseMomentum() const;

        /**
         *  @brief Set m_transverseMomentumBosonW1
         *
         *  @param transverseMomentum Transverse momentum of W boson 1 in W pairing 
         */
        void SetTransverseMomentumBosonW1(double transverseMomentumBosonW1);

        /**
         *  @brief Get m_transverseMomentumBosonW1
         */
        double GetTransverseMomentumBosonW1() const;

        /**
         *  @brief Set m_transverseMomentumBosonW2
         *
         *  @param transverseMomentum Transverse momentum of W boson 2 in W pairing
         */
        void SetTransverseMomentumBosonW2(double transverseMomentumBosonW2);

        /**
         *  @brief Get m_transverseMomentumBosonW2
         */
        double GetTransverseMomentumBosonW2() const;

        /**
         *  @brief Set m_transverseMomentumBosonZ1
         *
         *  @param transverseMomentum Transverse momentum of Z boson 1 in Z pairing
         */
        void SetTransverseMomentumBosonZ1(double transverseMomentumBosonZ1);

        /**
         *  @brief Get m_transverseMomentumBosonZ1
         */
        double GetTransverseMomentumBosonZ1() const;

        /**
         *  @brief Set m_transverseMomentumBosonZ2
         *
         *  @param transverseMomentum Transverse momentum of Z boson 2 in Z pairing
         */
        void SetTransverseMomentumBosonZ2(double transverseMomentumBosonZ2);

        /**
         *  @brief Get m_transverseMomentumBosonZ2
         */
        double GetTransverseMomentumBosonZ2() const;

        /**
         *  @brief Set m_transverseMomentumMC
         *
         *  @param transverseMomentumMC Transverse momentum of quark system
         */
        void SetTransverseMomentumMC(double transverseMomentumMC);

        /**
         *  @brief Get m_transverseMomentumMC
         */
        double GetTransverseMomentumMC() const;

        /**
         *  @brief Set m_transverseEnergy
         *
         *  @param transverseEnergy Transverse energy of reconstructed system
         */
        void SetTransverseEnergy(double transverseEnergy);

        /**
         *  @brief Set m_transverseEnergyBosonW1
         *
         *  @param transverseEnergyBosonW1 Transverse energy of W boson 1 in W pairing
         */
        void SetTransverseEnergyBosonW1(double transverseEnergyBosonW1);

        /**
         *  @brief Get m_transverseEnergyBosonW1
         */
        double GetTransverseEnergyBosonW1() const;

        /**
         *  @brief Set m_transverseEnergyBosonW2
         *
         *  @param transverseEnergyBosonW2 Transverse energy of W boson 2 in W pairing
         */
        void SetTransverseEnergyBosonW2(double transverseEnergyBosonW2);

        /**
         *  @brief Get m_transverseEnergyBosonW2
         */
        double GetTransverseEnergyBosonW2() const;

        /**
         *  @brief Set m_transverseEnergyBosonZ1
         *
         *  @param transverseEnergyBosonZ1 Transverse energy of Z boson 1 in Z pairing
         */
        void SetTransverseEnergyBosonZ1(double transverseEnergyBosonZ1);

        /**
         *  @brief Get m_transverseEnergyBosonZ1
         */
        double GetTransverseEnergyBosonZ1() const;

        /**
         *  @brief Set m_transverseEnergyBosonZ2
         *
         *  @param transverseEnergyBosonZ2 Transverse energy of Z boson 2 in Z pairing
         */
        void SetTransverseEnergyBosonZ2(double transverseEnergyBosonZ2);

        /**
         *  @brief Get m_transverseEnergyBosonZ2
         */
        double GetTransverseEnergyBosonZ2() const;

        /**
         *  @brief Get m_transverseEnergy
         */
        double GetTransverseEnergy() const;

        /**
         *  @brief Set m_transverseEnergyMC
         *
         *  @param transverseEnergyMC Transverse energy of quark system
         */
        void SetTransverseEnergyMC(double transverseEnergyMC);

        /**
         *  @brief Get m_transverseEnergyMC
         */
        double GetTransverseEnergyMC() const;

        /**
         *  @brief Set m_cosThetaMissing
         *
         *  @param cosThetaMissing Cosine theta of missing energy
         */
        void SetCosThetaMissing(double cosThetaMissing);

        /**
         *  @brief Get m_cosThetaMissing
         */
        double GetCosThetaMissing() const;

        /**
         *  @brief Set m_cosThetaMissingMC
         *
         *  @param cosThetaMissingMC Cosine theta of neutrino energy
         */
        void SetCosThetaMissingMC(double cosThetaMissingMC);

        /**
         *  @brief Get m_cosThetaMissingMC
         */
        double GetCosThetaMissingMC() const;

        /**
         *  @brief Set m_cosThetaMostEnergeticTrack 
         *
         *  @param cosThetaMostEnergeticTrack Cosine theta of highest energy track in system
         */
        void SetCosThetaMostEnergeticTrack(double cosThetaMostEnergeticTrack);

        /** 
         *  @brief Get m_cosThetaMostEnergeticTrack
         */
        double GetCosThetaMostEnergeticTrack() const;

        /**
         *  @brief Set m_recoilMass
         *
         *  @param recoilMass Recoil mass of reconstructed system
         */
        void SetRecoilMass(double recoilMass);

        /**
         *  @brief Get m_recoilMass
         */
        double GetRecoilMass() const;

        /**
         *  @brief Set m_recoilMassMC
         *
         *  @param recoilMassMC Recoil mass of quark system
         */
        void SetRecoilMassMC(double recoilMassMC);

        /**
         *  @brief Get m_recoilMassMC
         */
        double GetRecoilMassMC() const;

        /**
         *  @brief Set m_energyAroundMostEnergeticPfo
         *
         *  @param energyAroundMostEnergeticPfo Energy in cone around most energetic pfo
         */
        void SetEnergyAroundMostEnergeticPfo(double energyAroundMostEnergeticPfo);

        /**
         *  @brief Get m_energyAroundMostEnergeticPfo
         */
        double GetEnergyAroundMostEnergeticPfo() const;

        /**
         *  @brief Set m_y12
         *
         *  @param y12 Jet grouping parameter
         */
        void SetY12(double y12);

        /**
         *  @brief Get m_y12
         */
        double GetY12() const;

        /**
         *  @brief Set m_y23
         *
         *  @param y23 Jet grouping parameter
         */
        void SetY23(double y23);

        /**
         *  @brief Get m_y23
         */
        double GetY23() const;

        /**
         *  @brief Set m_y34
         *
         *  @param y34 Jet grouping parameter
         */
        void SetY34(double y34);

        /**
         *  @brief Get m_y34
         */
        double GetY34() const;

        /**
         *  @brief Set m_y45
         *
         *  @param y45 Jet grouping parameter
         */
        void SetY45(double y45);

        /**
         *  @brief Get m_y45
         */
        double GetY45() const;

        /**
         *  @brief Set m_y56
         *
         *  @param y56 Jet grouping parameter
         */
        void SetY56(double y56);

        /**
         *  @brief Get m_y56
         */
        double GetY56() const;

        /**
         *  @brief Set m_y67
         *
         *  @param y67 Jet grouping parameter
         */
        void SetY67(double y67);

        /**
         *  @brief Get m_y67
         */
        double GetY67() const;

        /**
         *  @brief Set m_invariantMassSystem
         *
         *  @param invariantMassSystem Invariant mass of the jet system
         */
        void SetInvariantMassSystem(double invariantMassSystem);

        /**
         *  @brief Get m_invariantMassSystem
         */
        double GetInvariantMassSystem() const;

        /**
         *  @brief Set m_invariantMassSystemMC
         *
         *  @param invariantMassSystemMC Invariant mass of the quark system
         */
        void SetInvariantMassSystemMC(double invariantMassSystemMC);

        /**
         *  @brief Get m_invariantMassSystemMC
         */
        double GetInvariantMassSystemMC() const;

        /**
         *  @brief Set m_cosThetaStarWBosons
         *
         *  @param cosThetaStarWBosons Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs
         */
        void SetCosThetaStarWBosons(double cosThetaStarWBosons);

        /**
         *  @brief Get m_cosThetaStarWBosons
         */
        double GetCosThetaStarWBosons() const;

        /**
         *  @brief Set m_cosThetaStarWBosonsMC
         *
         *  @param cosThetaStarWBosonsMC Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs
         */
        void SetCosThetaStarWBosonsMC(double cosThetaStarWBosonsMC);

        /**
         *  @brief Get m_cosThetaStarWBosonsMC
         */
        double GetCosThetaStarWBosonsMC() const;

        /**
         *  @brief Set m_cosThetaStarZBosons
         *
         *  @param cosThetaStarZBosons Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs
         */
        void SetCosThetaStarZBosons(double cosThetaStarZBosons);

        /**
         *  @brief Get m_cosThetaStarZBosons
         */
        double GetCosThetaStarZBosons() const;

        /**
         *  @brief Set m_cosThetaStarZBosonsMC
         *
         *  @param cosThetaStarZBosonsMC Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs
         */
        void SetCosThetaStarZBosonsMC(double cosThetaStarZBosonsMC);

        /**
         *  @brief Get m_cosThetaStarZBosonsMC
         */
        double GetCosThetaStarZBosonsMC() const;

        /**
         *  @brief Set m_acolinearityJetsW1
         *
         *  @param acolinearityJetsW1 Acolinearity of the jets from boson 1 in W pairing
         */
        void SetAcolinearityJetsW1(double acolinearityJetsW1);

        /**
         *  @brief Get m_acolinearityJetsW1
         */
        double GetAcolinearityJetsW1() const;

        /**
         *  @brief Set m_acolinearityJetsW2
         *
         *  @param acolinearityJetsW2 Acolinearity of the jets from boson 2 in W pairing
         */
        void SetAcolinearityJetsW2(double acolinearityJetsW2);

        /**
         *  @brief Get m_acolinearityJetsW2
         */
        double GetAcolinearityJetsW2() const;

        /**
         *  @brief Set m_acolinearityJetsZ1
         *
         *  @param acolinearityJetsZ1 Acolinearity of the jets from boson 1 in Z pairing
         */
        void SetAcolinearityJetsZ1(double acolinearityJetsZ1);

        /**
         *  @brief Get m_acolinearityJetsZ1
         */
        double GetAcolinearityJetsZ1() const;

        /**
         *  @brief Set m_acolinearityJetsZ2
         *
         *  @param acolinearityJetsZ2 Acolinearity of the jets from boson 2 in Z pairing
         */
        void SetAcolinearityJetsZ2(double acolinearityJetsZ2);

        /**
         *  @brief Get m_acolinearityJetsZ2
         */
        double GetAcolinearityJetsZ2() const;

        /**
         *  @brief Set m_acolinearityBosonsW
         *
         *  @param acolinearityBosonsW Acolinearity of the W bosons in W pairing
         */
        void SetAcolinearityBosonsW(double acolinearityBosonsW);

        /**
         *  @brief Get m_acolinearityBosonsW
         */
        double GetAcolinearityBosonsW() const;

        /**
         *  @brief Set m_acolinearityBosonsZ
         *
         *  @param acolinearityBosonsZ Acolinearity of the Z bosons in Z pairing
         */
        void SetAcolinearityBosonsZ(double acolinearityBosonsZ);

        /**
         *  @brief Get m_acolinearityBosonsZ
         */
        double GetAcolinearityBosonsZ() const;

        /**
         *  @brief Set m_highestEnergyElectronE
         *
         *  @param highestEnergyElectronE Energy of highest energy electron
         */
        void SetHighestEnergyElectronEnergy(double highestEnergyElectronE);

        /**
         *  @brief Get m_highestEnergyElectronE
         */
        double GetHighestEnergyElectronEnergy() const;

        /**
         *  @brief Set m_highestEnergyElectronP
         *
         *  @param highestEnergyElectronP Magnitude of momentum of highest energy electron
         */
        void SetHighestEnergyElectronMomentum(double highestEnergyElectronP);

        /**
         *  @brief Get m_highestEnergyElectronP
         */
        double GetHighestEnergyElectronMomentum() const;

        /**
         *  @brief Set m_highestEnergyElectronPt
         *
         *  @param highestEnergyElectronPt Transverse momentum of highest energy electron
         */
        void SetHighestEnergyElectronTransverseMomentum(double highestEnergyElectronPt);

        /**
         *  @brief Get m_highestEnergyElectronPt
         */
        double GetHighestEnergyElectronTransverseMomentum() const;

        /**
         *  @brief Set m_highestEnergyElectronCosTheta
         *
         *  @param highestEnergyElectronCosTheta Consine theta of highest energy electron
         */
        void SetHighestEnergyElectronCosTheta(double highestEnergyElectronCosTheta);

        /**
         *  @brief Get m_highestEnergyElectronCosTheta
         */
        double GetHighestEnergyElectronCosTheta() const;

        /**
         *  @brief Set m_highestEnergyMuonE
         *
         *  @param highestEnergyMuonE Energy of highest energy muon
         */
        void SetHighestEnergyMuonEnergy(double highestEnergyMuonE);

        /**
         *  @brief Get m_highestEnergyMuonE
         */
        double GetHighestEnergyMuonEnergy() const;

        /**
         *  @brief Set m_highestEnergyMuonP
         *
         *  @param highestEnergyMuonP Magnitude of momentum of highest energy muon
         */
        void SetHighestEnergyMuonMomentum(double highestEnergyMuonP);

        /**
         *  @brief Get m_highestEnergyMuonP
         */
        double GetHighestEnergyMuonMomentum() const;

        /**
         *  @brief Set m_highestEnergyMuonPt
         *
         *  @param highestEnergyMuonPt Transverse momentum of highest energy muon
         */
        void SetHighestEnergyMuonTransverseMomentum(double highestEnergyMuonPt);

        /**
         *  @brief Get m_highestEnergyMuonPt
         */
        double GetHighestEnergyMuonTransverseMomentum() const;

        /**
         *  @brief Set m_highestEnergyMuonCosTheta
         *
         *  @param highestEnergyMuonCosTheta Consine theta of highest energy muon
         */
        void SetHighestEnergyMuonCosTheta(double highestEnergyMuonCosTheta);

        /**
         *  @brief Get m_highestEnergyMuonCosTheta
         */
        double GetHighestEnergyMuonCosTheta() const;

        /**
         *  @brief Set m_highestEnergyPhotonE
         *
         *  @param highestEnergyPhotonE Energy of highest energy photon
         */
        void SetHighestEnergyPhotonEnergy(double highestEnergyPhotonE);

        /**
         *  @brief Get m_highestEnergyPhotonE
         */
        double GetHighestEnergyPhotonEnergy() const;

        /**
         *  @brief Set m_highestEnergyPhotonP
         *
         *  @param highestEnergyPhotonP Magnitude of momentum of highest energy photon
         */
        void SetHighestEnergyPhotonMomentum(double highestEnergyPhotonP);

        /**
         *  @brief Get m_highestEnergyPhotonP
         */
        double GetHighestEnergyPhotonMomentum() const;

        /**
         *  @brief Set m_highestEnergyPhotonPt
         *
         *  @param highestEnergyPhotonPt Transverse momentum of highest energy photon
         */
        void SetHighestEnergyPhotonTransverseMomentum(double highestEnergyPhotonPt);

        /**
         *  @brief Get m_highestEnergyPhotonPt
         */
        double GetHighestEnergyPhotonTransverseMomentum() const;

        /**
         *  @brief Set m_highestEnergyPhotonCosTheta
         *
         *  @param highestEnergyPhotonCosTheta Consine theta of highest energy photon
         */
        void SetHighestEnergyPhotonCosTheta(double highestEnergyPhotonCosTheta);

        /**
         *  @brief Get m_highestEnergyPhotonCosTheta
         */
        double GetHighestEnergyPhotonCosTheta() const;

        /**
         *  @brief Set m_highestEnergyPfoE
         *
         *  @param highestEnergyPfoE Energy of highest energy pfo
         */
        void SetHighestEnergyPfoEnergy(double highestEnergyPfoE);

        /**
         *  @brief Get m_highestEnergyPfoE
         */
        double GetHighestEnergyPfoEnergy() const;

        /**
         *  @brief Set m_highestEnergyPfoP
         *
         *  @param highestEnergyPfoP Magnitude of momentum of highest energy pfo
         */
        void SetHighestEnergyPfoMomentum(double highestEnergyPfoP);

        /**
         *  @brief Get m_highestEnergyPfoP
         */
        double GetHighestEnergyPfoMomentum() const;

        /**
         *  @brief Set m_highestEnergyPfoPt
         *
         *  @param highestEnergyPfoPt Transverse momentum of highest energy pfo
         */
        void SetHighestEnergyPfoTransverseMomentum(double highestEnergyPfoPt);

        /**
         *  @brief Get m_highestEnergyPfoPt
         */
        double GetHighestEnergyPfoTransverseMomentum() const;

        /**
         *  @brief Set m_highestEnergyPfoCosTheta
         *
         *  @param highestEnergyPfoCosTheta Consine theta of highest energy pfo
         */
        void SetHighestEnergyPfoCosTheta(double highestEnergyPfoCosTheta);

        /**
         *  @brief Get m_highestEnergyPfoCosTheta
         */
        double GetHighestEnergyPfoCosTheta() const;

// DoubleVectors

        /**
         *  @brief Set m_invariantMassWBosons
         *
         *  @param invMassWVectors Invariant mass of first and second pair of W paired jets
         */
        void SetInvMassWVectors(DoubleVector invMassWVectors);

        /**
         *  @brief Get m_invariantMassWBosons
         */
        DoubleVector GetInvMassWVectors() const;

        /**
         *  @brief Set m_invariantMassZBosons 
         *
         *  @param invMassZVectors Invariant mass of first and second pair of Z paired jets
         */
        void SetInvMassZVectors(DoubleVector invMassZVectors);

        /**
         *  @brief Get m_invariantMassZBosons
         */
        DoubleVector GetInvMassZVectors() const;

        /**
         *  @brief Set m_invariantMassWBosonsMC
         *
         *  @param invariantMassWBosonsMC Invariant mass of first and second pair of W paired quarks
         */
        void SetInvariantMassWBosonsMC(DoubleVector invariantMassWBosonsMC);

        /**
         *  @brief Get m_invariantMassWBosonsMC
         */
        DoubleVector GetInvariantMassWBosonsMC() const;

        /**
         *  @brief Set m_invariantMassZBosonsMC
         *
         *  @param invariantMassZBosonsMC Invariant mass of first and second pair of Z paired quarks
         */
        void SetInvariantMassZBosonsMC(DoubleVector invariantMassZBosonsMC);

        /**
         *  @brief Get m_invariantMassZBosonsMC
         */
        DoubleVector GetInvariantMassZBosonsMC() const;

        /**
         *  @brief Set m_energyJets
         *
         *  @param energyJets Energy of reconstructed jets
         */
        void SetEnergyJets(DoubleVector energyJets);

        /**
         *  @brief Get m_energyJets
         */
        DoubleVector GetEnergyJets() const;

        /**
         *  @brief Get lowest number in m_energyJets
         */
        double GetLowestEnergyJet() const;

        /**
         *  @brief Set m_cosThetaStarWJets
         *
         *  @param cosThetaStarWJets Cosine of the polar angle of the q jets in the reference frome of the W bosons
         */
        void SetCosThetaStarWJets(DoubleVector cosThetaStarWJets);

        /**
         *  @brief Get m_cosThetaStarWJets
         */
        DoubleVector GetCosThetaStarWJets() const;

        /**
         *  @brief Set m_cosThetaStarZJets
         *
         *  @param cosThetaStarZJets Cosine of the polar angle of the q jets in the reference frome of the Z bosons
         */
        void SetCosThetaStarZJets(DoubleVector cosThetaStarZJets);

        /**
         *  @brief Get m_cosThetaStarZJets
         */
        DoubleVector GetCosThetaStarZJets() const;

        /**
         *  @brief Set m_bTagForJets
         *
         *  @param bTagForJets vector of b tag values for the event 
         */
        void SetBTagForJets(DoubleVector bTagForJets);

        /**
         *  @brief Get m_bTagForJets
         */
        DoubleVector GetBTagForJets() const;

        /**
         *  @brief Set m_cTagForJets
         *
         *  @param cTagForJets vector of c tag values for the event
         */
        void SetCTagForJets(DoubleVector cTagForJets);

        /**
         *  @brief Get m_cTagForJets
         */
        DoubleVector GetCTagForJets() const;

        /**
         *  @brief Set
         *
         *  @param
         */
//        void Set(DoubleVector );

        /**
         *  @brief Get
         */
//        DoubleVector Get();

    private:
        bool             m_appropriateEvent;                 ///< Does event pass a series of cuts suggesting it has a vvqqqq final state? - JetAnalysis
        bool             m_isEventWW;                        ///< Are the invariant masses of the jets close to the W boson mass? - JetAnalysis
        bool             m_isEventWWMC;                      ///< Are the invariant masses of the quark pairs close to the W boson mass? - MCAnalysis
        bool             m_isEventZZ;                        ///< Are the invariant masses of the jets close to the Z boson mass? - JetAnalysis
        bool             m_isEventZZMC;                      ///< Are the invariant masses of the quark pairs close to the Z boson mass? - MCAnalysis
        int              m_nPfosBosonW1;                     ///< Number of pfos in W boson 1 in W pairing - JetAnalysis
        int              m_nPfosBosonW2;                     ///< Number of pfos in W boson 2 in W pairing - JetAnalysis
        int              m_nPfosBosonZ1;                     ///< Number of pfos in W boson 1 in Z pairing - JetAnalysis
        int              m_nPfosBosonZ2;                     ///< Number of pfos in W boson 2 in Z pairing - JetAnalysis
        IntVector        m_combinationWJets;                 ///< Combination of jets to form W bosons - JetAnalysis
        IntVector        m_combinationZJets;                 ///< Combination of jets to form Z bosons - JetAnalysis
        IntVector        m_nParticlesJets;                   ///< Number of particles in reconstructed jet - JetAnalysis
        IntVector        m_nChargedParticlesJets;            ///< Number of charged particles in reconstructed jet - JetAnalysis
        double           m_transverseMomentum;               ///< Transverse momentum of reconstructed system - JetAnalysis
        double           m_transverseMomentumBosonW1;        ///< Transverse momentum of W boson 1 in W pairing - JetAnalysis
        double           m_transverseMomentumBosonW2;        ///< Transverse momentum of W boson 2 in W pairing - JetAnalysis
        double           m_transverseMomentumBosonZ1;        ///< Transverse momentum of W boson 1 in Z pairing - JetAnalysis
        double           m_transverseMomentumBosonZ2;        ///< Transverse momentum of W boson 2 in Z pairing - JetAnalysis
        double           m_transverseMomentumMC;             ///< Transverse momentum of quark system - MCAnalysis
        double           m_transverseEnergy;                 ///< Transverse energy of reconstructed system - JetAnalysis
        double           m_transverseEnergyBosonW1;          ///< Transverse energy of W boson 1 in W pairing - JetAnalysis
        double           m_transverseEnergyBosonW2;          ///< Transverse energy of W boson 2 in W pairing - JetAnalysis
        double           m_transverseEnergyBosonZ1;          ///< Transverse energy of Z boson 1 in Z pairing - JetAnalysis
        double           m_transverseEnergyBosonZ2;          ///< Transverse energy of Z boson 2 in Z pairing - JetAnalysis
        double           m_transverseEnergyMC;               ///< Transverse energy of quark system - MCAnalysis
        double           m_cosThetaMissing;                  ///< Cosine theta of missing energy - JetAnalysis
        double           m_cosThetaMissingMC;                ///< Cosine theta of neutrino energy - MCAnalysis
        double           m_cosThetaMostEnergeticTrack;       ///< Cosine theta of highest energy track in system - JetAnalysis
        double           m_recoilMass;                       ///< Recoil mass of reconstructed system - JetAnalysis
        double           m_recoilMassMC;                     ///< Recoil mass of quark system - MCAnalysis
        double           m_energyAroundMostEnergeticPfo;     ///< Energy in cone around most energetic pfo - JetAnalysis
        double           m_y12;                              ///< Jet grouping parameter
        double           m_y23;                              ///< Jet grouping parameter
        double           m_y34;                              ///< Jet grouping parameter
        double           m_y45;                              ///< Jet grouping parameter
        double           m_y56;                              ///< Jet grouping parameter
        double           m_y67;                              ///< Jet grouping parameter
        double           m_invariantMassSystem;              ///< Invariant mass of the jet system - JetAnalysis
        double           m_invariantMassSystemMC;            ///< Invariant mass of the quark system - MCAnalysis
        double           m_cosThetaStarWBosons;              ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs - JetAnalysis
        double           m_cosThetaStarWBosonsMC;            ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs - MCAnalysis
        double           m_cosThetaStarZBosons;              ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs - JetAnalysis
        double           m_cosThetaStarZBosonsMC;            ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs - MCAnalysis
        double           m_acolinearityJetsW1;               ///< Acolinearity of the jets from boson 1 in W pairing - JetAnalysis
        double           m_acolinearityJetsW2;               ///< Acolinearity of the jets from boson 2 in W pairing - JetAnalysis
        double           m_acolinearityJetsZ1;               ///< Acolinearity of the jets from boson 1 in Z pairing - JetAnalysis
        double           m_acolinearityJetsZ2;               ///< Acolinearity of the jets from boson 2 in Z pairing - JetAnalysis
        double           m_acolinearityBosonsW;              ///< Acolinearity of the W bosons in W pairing - JetAnalysis- SelectionProcessor
        double           m_acolinearityBosonsZ;              ///< Acolinearity of the W bosons in Z pairing - JetAnalysis- SelectionProcessor
        double           m_principleThrustValue;             ///< Principle thrust value from ThrustReconstruction processor- SelectionProcessor
        double           m_majorThrustValue;                 ///< Major thrust value from ThrustReconstruction processor- SelectionProcessor
        double           m_minorThrustValue;                 ///< Minor thrust value from ThrustReconstruction processor - SelectionProcessor
        double           m_xThrustAxis;                      ///< X Thrust axis value from ThrustReconstruction processor - SelectionProcessor
        double           m_yThrustAxis;                      ///< Y Thrust axis value from ThrustReconstruction processor  - SelectionProcessor
        double           m_zThrustAxis;                      ///< Z Thrust axis value from ThrustReconstruction processor - SelectionProcessor
        double           m_sphericity;                       ///< Sphericity from Sphere processor - SelectionProcessor
        double           m_aplanarity;                       ///< Aplnarity from Sphere processor - SelectionProcessor
        double           m_highestEnergyElectronE;           ///< Energy of highest energy electron - PfoAnalysis
        double           m_highestEnergyElectronP;           ///< Magnitude of momentum of highest energy electron - PfoAnalysis
        double           m_highestEnergyElectronPt;          ///< Transverse momentum of highest energy electron - PfoAnalysis
        double           m_highestEnergyElectronCosTheta;    ///< Consine theta of highest energy electron - PfoAnalysis
        double           m_highestEnergyMuonE;               ///< Energy of highest energy electron - PfoAnalysis
        double           m_highestEnergyMuonP;               ///< Magnitude of momentum of highest energy electron - PfoAnalysis
        double           m_highestEnergyMuonPt;              ///< Transverse momentum of highest energy electron - PfoAnalysis
        double           m_highestEnergyMuonCosTheta;        ///< Consine theta of highest energy electron - PfoAnalysis
        double           m_highestEnergyPhotonE;             ///< Energy of highest energy electron - PfoAnalysis
        double           m_highestEnergyPhotonP;             ///< Magnitude of momentum of highest energy electron - PfoAnalysis
        double           m_highestEnergyPhotonPt;            ///< Transverse momentum of highest energy electron - PfoAnalysis
        double           m_highestEnergyPhotonCosTheta;      ///< Consine theta of highest energy electron - PfoAnalysis
        double           m_highestEnergyPfoE;                ///< Energy of highest energy electron - PfoAnalysis
        double           m_highestEnergyPfoP;                ///< Magnitude of momentum of highest energy electron - PfoAnalysis
        double           m_highestEnergyPfoPt;               ///< Transverse momentum of highest energy electron - PfoAnalysis
        double           m_highestEnergyPfoCosTheta;         ///< Consine theta of highest energy electron - PfoAnalysis
        DoubleVector     m_invariantMassWBosons;             ///< Invariant mass of first and second pair of W paired jets - JetAnalysis
        DoubleVector     m_invariantMassWBosonsMC;           ///< Invariant mass of first and second pair of W paired quarks - MCAnalysis
        DoubleVector     m_invariantMassZBosons;             ///< Invariant mass of first and second pair of Z paired jets - JetAnalysis
        DoubleVector     m_invariantMassZBosonsMC;           ///< Invariant mass of first and second pair of Z paired quarks - MCAnalysis
        DoubleVector     m_energyJets;                       ///< Energy of reconstructed jets  - JetAnalysis
        DoubleVector     m_cosThetaStarWJets;                ///< Cosine of the polar angle of the q jets in the reference frome of the W bosons - JetAnalysis
        DoubleVector     m_cosThetaStarZJets;                ///< Cosine of the polar angle of the q jets in the reference frome of the Z bosons - JetAnalysis
        DoubleVector     m_bTagForJets;                      ///< B tag value for the jets in the event
        DoubleVector     m_cTagForJets;                      ///< C tag value for the jets in the event
};

#endif // #ifndef VARIABLES_H
