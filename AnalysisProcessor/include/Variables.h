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
#include <map>
#include <vector>

#include "EVENT/LCParameters.h"
#include "EVENT/MCParticle.h"

#include "TInterpreter.h"
#include "TTree.h"

namespace variables_namespace
{
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;
    typedef std::vector<const EVENT::MCParticle*> MCParticleVector;
    typedef std::map<const EVENT::MCParticle*, MCParticleVector*> MCParticleToMCParticleMap;
}

using namespace variables_namespace;

class Variables
{
    public:
        /**
         *  @brief Constructor
         *
         *  @param eventEnergyMC MC energy of event
         */
        Variables(const double eventEnergyMC);

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

        /**
         *  @brief Get m_isEventWW
         */
        bool GetIsEventWW() const;

        /**
         *  @brief Set m_isEventWWMC
         *
         *  @param isEventWWMC Are the invariant masses of the quarks close to the W boson mass
         */
        void SetIsEventWWMC(bool isEventWWMC);

        /**
         *  @brief Get m_isEventWWMC
         */
        bool GetIsEventWWMC() const;

        /**
         *  @brief Set m_isEventZZ
         *
         *  @param isEventZZ Are the invariant masses of the jets close to the Z boson mass
         */
        void SetIsEventZZ(bool isEventZZ);

        /**
         *  @brief Get m_isEventZZ
         */
        bool GetIsEventZZ() const;

        /**
         *  @brief Set m_isEventZZMC
         *
         *  @param isEventZZMC Are the invariant masses of the quarks close to the Z boson mass
         */
        void SetIsEventZZMC(bool isEventZZMC);

        /**
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

        /**
         *  @brief Get m_nPfosBosonW1
         */
        int GetNPfosBosonW1() const;

        /**
         *  @brief Set m_nPfosBosonW2
         *
         *  @param nPfosBosonW2 Number of pfos in W boson 2 in W pairing
         */
        void SetNPfosBosonW2(int nPfosBosonW2);

        /**
         *  @brief Get m_nPfosBosonW2
         */
        int GetNPfosBosonW2() const;

        /**
         *  @brief Set m_nPfosBosonZ1
         *
         *  @param nPfosBosonZ1 Number of pfos in Z boson 1 in Z pairing
         */
        void SetNPfosBosonZ1(int nPfosBosonZ1);

        /**
         *  @brief Get m_nPfosBosonZ1
         */
        int GetNPfosBosonZ1() const;

        /**
         *  @brief Set m_nPfosBosonZ2
         *
         *  @param nPfosBosonZ2 Number of pfos in Z boson 2 in Z pairing
         */
        void SetNPfosBosonZ2(int nPfosBosonZ2);

        /**
         *  @brief Get m_nPfosBosonZ2
         */
        int GetNPfosBosonZ2() const;

        /**
         *  @brief Set m_highestEnergyPfoPDG
         *
         *  @param highestEnergyPfoPDG PDG code of highest energy PFO in evnet 
         */
        void SetHighestEnergyPfoPDG(int highestEnergyPfoPDG);

        /**
         *  @brief Get m_highestEnergyPfoPDG
         */
        int GetHighestEnergyPfoPDG() const;

        /**
         *  @brief Set m_nIsolatedLeptons
         *
         *  @param nIsolatedLeptons Number of isolated leptons identified in isolated lepton finder
         */
        void SetNumberOfIsolatedLeptons(int nIsolatedLeptons);

        /**
         *  @brief Get m_nIsolatedLeptons
         */
        int GetNumberOfIsolatedLeptons() const;

        /**
         *  @brief Set m_highestEnergyIsolatedLeptonPDG
         *
         *  @param highestEnergyIsolatedLeptonPDG PDG of highest energy PFO from isolated lepton finder
         */
        void SetHighestEnergyIsolatedLeptonPDG(int highestEnergyIsolatedLeptonPDG);

        /**
         *  @brief Get m_highestEnergyIsolatedLeptonPDG
         */
        int GetHighestEnergyIsolatedLeptonPDG() const;

        /**
         *  @brief Set m_secondHighestEnergyIsolatedLeptonPDG
         *
         *  @param secondHighestEnergyIsolatedLeptonPDG PDG of second highest energy PFO from isolated lepton finder 
         */
        void SetSecondHighestEnergyIsolatedLeptonPDG(int secondHighestEnergyIsolatedLeptonPDG);

        /**
         *  @brief Get m_secondHighestEnergyIsolatedLeptonPDG
         */
        int GetSecondHighestEnergyIsolatedLeptonPDG() const;

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
         * @brief Get m_eventEnergyMC
         */ 
        double GetEventEnergyMC() const;

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
         *  @brief Set m_energyBosonW1
         *
         *  @param energyBosonW1 Energy of W Boson 1
         */
        void SetEnergyBosonW1(double energyBosonW1);

        /**
         *  @brief Get m_energyBosonW1
         */
        double GetEnergyBosonW1() const;

        /**
         *  @brief Set m_energyBosonW2
         *
         *  @param energyBosonW2 Energy of W Boson 2
         */
        void SetEnergyBosonW2(double energyBosonW2);

        /**
         *  @brief Get m_energyBosonW2
         */
        double GetEnergyBosonW2() const;

        /**
         *  @brief Set m_energyBosonZ1
         *
         *  @param energyBosonZ1 Energy of Z Boson 1
         */
        void SetEnergyBosonZ1(double energyBosonZ1);

        /**
         *  @brief Get m_energyBosonZ1
         */
        double GetEnergyBosonZ1() const;

        /**
         *  @brief Set m_energyBosonZ2
         *
         *  @param energyBosonZ2 Energy of Z Boson 2
         */
        void SetEnergyBosonZ2(double energyBosonZ2);

        /**
         *  @brief Get m_energyBosonZ2
         */
        double GetEnergyBosonZ2() const;

        /**                                                                                                                                                                 
         *  @brief Set m_momentumBosonW1
         *
         *  @param momentumBosonW1 Momentum of W Boson 1
         */
        void SetMomentumBosonW1(double momentumBosonW1);

        /**
         *  @brief Get m_momentumBosonW1
         */
        double GetMomentumBosonW1() const;

        /**
         *  @brief Set m_momentumBosonW2
         *
         *  @param momentumBosonW2 Momentum of W Boson 2
         */
        void SetMomentumBosonW2(double momentumBosonW2);

        /**
         *  @brief Get m_momentumBosonW2
         */
        double GetMomentumBosonW2() const;

        /**
         *  @brief Set m_momentumBosonZ1
         *
         *  @param momentumBosonZ1 Momentum of Z Boson 1
         */
        void SetMomentumBosonZ1(double momentumBosonZ1);

        /**
         *  @brief Get m_momentumBosonZ1
         */
        double GetMomentumBosonZ1() const;

        /**
         *  @brief Set m_momentumBosonZ2
         *
         *  @param momentumBosonZ2 Momentum of Z Boson 2
         */
        void SetMomentumBosonZ2(double momentumBosonZ2);

        /**
         *  @brief Get m_momentumBosonZ2
         */
        double GetMomentumBosonZ2() const;

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
         *  @brief Set m_cosThetaBosonW1
         *
         *  @param cosThetaBosonW1 CosTheta of W Boson 1
         */
        void SetCosThetaBosonW1(double cosThetaBosonW1);

        /**
         *  @brief Get m_cosThetaBosonW1
         */
        double GetCosThetaBosonW1() const;

        /**
         *  @brief Set m_cosThetaBosonW2
         *
         *  @param cosThetaBosonW2 CosTheta of W Boson 2
         */
        void SetCosThetaBosonW2(double cosThetaBosonW2);

        /**
         *  @brief Get m_cosThetaBosonW2
         */
        double GetCosThetaBosonW2() const;

        /**
         *  @brief Set m_cosThetaBosonZ1
         *
         *  @param cosThetaBosonZ1 CosTheta of Z Boson 1
         */
        void SetCosThetaBosonZ1(double cosThetaBosonZ1);

        /**
         *  @brief Get m_cosThetaBosonZ1
         */
        double GetCosThetaBosonZ1() const;

        /**
         *  @brief Set m_cosThetaBosonZ2
         *
         *  @param cosThetaBosonZ2 CosTheta of Z Boson 2
         */
        void SetCosThetaBosonZ2(double cosThetaBosonZ2);

        /**
         *  @brief Get m_cosThetaBosonZ2
         */
        double GetCosThetaBosonZ2() const;

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

        /**
         *  @brief Set m_highestEnergyIsolatedLeptonE
         *
         *  @param highestEnergyIsolatedLeptonE Energy of highest energy lepton from isolated lepton finding
         */
        void SetHighestEnergyIsolatedLeptonEnergy(double highestEnergyIsolatedLeptonE);

        /**
         *  @brief Get m_highestEnergyIsolatedLeptonE
         */
        double GetHighestEnergyIsolatedLeptonEnergy() const;

        /**
         *  @brief Set m_highestEnergyIsolatedLeptonP
         *
         *  @param highestEnergyIsolatedLeptonP Magnitude of momentum of highest energy lepton from isolated lepton finding
         */
        void SetHighestEnergyIsolatedLeptonMomentum(double highestEnergyIsolatedLeptonP);

        /**
         *  @brief Get m_highestEnergyIsolatedLeptonP
         */
        double GetHighestEnergyIsolatedLeptonMomentum() const;

        /**
         *  @brief Set m_highestEnergyIsolatedLeptonPt
         *
         *  @param highestEnergyIsolatedLeptonPt Transverse momentum of highest energy lepton from isolated lepton finding
         */
        void SetHighestEnergyIsolatedLeptonTransverseMomentum(double highestEnergyIsolatedLeptonPt);

        /**
         *  @brief Get m_highestEnergyIsolatedLeptonPt
         */
        double GetHighestEnergyIsolatedLeptonTransverseMomentum() const;

        /**
         *  @brief Set m_highestEnergyIsolatedLeptonCosTheta
         *
         *  @param highestEnergyIsolatedLeptonCosTheta Consine theta of highest energy lepton from isolated lepton finding 
         */
        void SetHighestEnergyIsolatedLeptonCosTheta(double highestEnergyIsolatedLeptonCosTheta);

        /**
         *  @brief Get m_highestEnergyIsolatedLeptonCosTheta
         */
        double GetHighestEnergyIsolatedLeptonCosTheta() const;

        /**
         *  @brief Set m_secondHighestEnergyIsolatedLeptonE
         *
         *  @param secondHighestEnergyIsolatedLeptonE Energy of highest energy lepton from isolated lepton finding
         */
        void SetSecondHighestEnergyIsolatedLeptonEnergy(double secondHighestEnergyIsolatedLeptonE);

        /**
         *  @brief Get m_secondHighestEnergyIsolatedLeptonE
         */
        double GetSecondHighestEnergyIsolatedLeptonEnergy() const;

        /**
         *  @brief Set m_secondHighestEnergyIsolatedLeptonP
         *
         *  @param secondHighestEnergyIsolatedLeptonP Magnitude of momentum of highest energy lepton from isolated lepton finding
         */
        void SetSecondHighestEnergyIsolatedLeptonMomentum(double secondHighestEnergyIsolatedLeptonP);

        /**
         *  @brief Get m_secondHighestEnergyIsolatedLeptonP
         */
        double GetSecondHighestEnergyIsolatedLeptonMomentum() const;

        /**
         *  @brief Set m_secondHighestEnergyIsolatedLeptonPt
         *
         *  @param secondHighestEnergyIsolatedLeptonPt Transverse momentum of highest energy lepton from isolated lepton finding
         */
        void SetSecondHighestEnergyIsolatedLeptonTransverseMomentum(double secondHighestEnergyIsolatedLeptonPt);

        /**
         *  @brief Get m_secondHighestEnergyIsolatedLeptonPt
         */
        double GetSecondHighestEnergyIsolatedLeptonTransverseMomentum() const;

        /**
         *  @brief Set m_secondHighestEnergyIsolatedLeptonCosTheta
         *
         *  @param secondHighestEnergyIsolatedLeptonCosTheta Consine theta of highest energy lepton from isolated lepton finding
         */
        void SetSecondHighestEnergyIsolatedLeptonCosTheta(double secondHighestEnergyIsolatedLeptonCosTheta);

        /**
         *  @brief Get m_secondHighestEnergyIsolatedLeptonCosTheta
         */
        double GetSecondHighestEnergyIsolatedLeptonCosTheta() const;

        /**
         *  @brief Set m_maxBTagForBosonW1
         *
         *  @param maxBTagForBosonW1 Max b tag for jets in W Boson 1
         */
        void SetMaxBTagForBosonW1(double maxBTagForBosonW1);

        /**
         *  @brief Get m_maxBTagForBosonW1
         */
        double GetMaxBTagForBosonW1() const;

        /**
         *  @brief Set m_minBTagForBosonW1
         *
         *  @param minBTagForBosonW1 Min b tag for jets in W Boson 1
         */
        void SetMinBTagForBosonW1(double minBTagForBosonW1);

        /**
         *  @brief Get m_minBTagForBosonW1
         */
        double GetMinBTagForBosonW1() const;

        /**
         *  @brief Set m_maxBTagForBosonW2
         *
         *  @param maxBTagForBosonW2 Max b tag for jets in W Boson 2
         */
        void SetMaxBTagForBosonW2(double maxBTagForBosonW2);

        /**
         *  @brief Get m_maxBTagForBosonW2
         */
        double GetMaxBTagForBosonW2() const;

        /**
         *  @brief Set m_minBTagForBosonW2
         *
         *  @param minBTagForBosonW2 Min b tag for jets in W Boson 2
         */
        void SetMinBTagForBosonW2(double minBTagForBosonW2);

        /**
         *  @brief Get m_minBTagForBosonW2
         */
        double GetMinBTagForBosonW2() const;

        /**
         *  @brief Set m_maxCTagForBosonW1
         *
         *  @param maxCTagForBosonW1 Max c tag for jets in W Boson 1
         */
        void SetMaxCTagForBosonW1(double maxCTagForBosonW1);

        /**
         *  @brief Get m_maxCTagForBosonW1
         */
        double GetMaxCTagForBosonW1() const;

        /**
         *  @brief Set m_minCTagForBosonW1
         *
         *  @param minCTagForBosonW1 Min c tag for jets in W Boson 1
         */
        void SetMinCTagForBosonW1(double minCTagForBosonW1);

        /**
         *  @brief Get m_minCTagForBosonW1
         */
        double GetMinCTagForBosonW1() const;

        /**
         *  @brief Set m_maxCTagForBosonW2
         *
         *  @param maxCTagForBosonW2 Max c tag for jets in W Boson 2
         */
        void SetMaxCTagForBosonW2(double maxCTagForBosonW2);

        /**
         *  @brief Get m_maxCTagForBosonW2
         */
        double GetMaxCTagForBosonW2() const;

        /**
         *  @brief Set m_minCTagForBosonW2
         *
         *  @param minCTagForBosonW2 Min c tag for jets in W Boson 2
         */
        void SetMinCTagForBosonW2(double minCTagForBosonW2);

        /**
         *  @brief Get m_minCTagForBosonW2
         */
        double GetMinCTagForBosonW2() const;

        /**
         *  @brief Set m_maxBTagForBosonZ1
         *
         *  @param maxBTagForBosonZ1 Max b tag for jets in Z Boson 1
         */
        void SetMaxBTagForBosonZ1(double maxBTagForBosonZ1);

        /**
         *  @brief Get m_maxBTagForBosonZ1
         */
        double GetMaxBTagForBosonZ1() const;

        /**
         *  @brief Set m_minBTagForBosonZ1
         *
         *  @param minBTagForBosonZ1 Min b tag for jets in Z Boson 1
         */
        void SetMinBTagForBosonZ1(double minBTagForBosonZ1);

        /**
         *  @brief Get m_minBTagForBosonZ1
         */
        double GetMinBTagForBosonZ1() const;

        /**
         *  @brief Set m_maxBTagForBosonZ2
         *
         *  @param maxBTagForBosonZ2 Max b tag for jets in Z Boson 2
         */
        void SetMaxBTagForBosonZ2(double maxBTagForBosonZ2);

        /**
         *  @brief Get m_maxBTagForBosonZ2
         */
        double GetMaxBTagForBosonZ2() const;

        /**
         *  @brief Set m_minBTagForBosonZ2
         *
         *  @param minBTagForBosonZ2 Min b tag for jets in Z Boson 2
         */
        void SetMinBTagForBosonZ2(double minBTagForBosonZ2);

        /**
         *  @brief Get m_minBTagForBosonZ2
         */
        double GetMinBTagForBosonZ2() const;

        /**
         *  @brief Set m_maxCTagForBosonZ1
         *
         *  @param maxCTagForBosonZ1 Max c tag for jets in Z Boson 1
         */
        void SetMaxCTagForBosonZ1(double maxCTagForBosonZ1);

        /**
         *  @brief Get m_maxCTagForBosonZ1
         */
        double GetMaxCTagForBosonZ1() const;

        /**
         *  @brief Set m_minCTagForBosonZ1
         *
         *  @param minCTagForBosonZ1 Min c tag for jets in Z Boson 1
         */
        void SetMinCTagForBosonZ1(double minCTagForBosonZ1);

        /**
         *  @brief Get m_minCTagForBosonZ1
         */
        double GetMinCTagForBosonZ1() const;

        /**
         *  @brief Set m_maxCTagForBosonZ2
         *
         *  @param maxCTagForBosonZ2 Max c tag for jets in Z Boson 2
         */
        void SetMaxCTagForBosonZ2(double maxCTagForBosonZ2);

        /**
         *  @brief Get m_maxCTagForBosonZ2
         */
        double GetMaxCTagForBosonZ2() const;

        /**
         *  @brief Set m_minCTagForBosonZ2
         *
         *  @param minCTagForBosonZ2 Min c tag for jets in Z Boson 2
         */
        void SetMinCTagForBosonZ2(double minCTagForBosonZ2);

        /**
         *  @brief Get m_minCTagForBosonZ2
         */
        double GetMinCTagForBosonZ2() const;

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
         *  @brief Set m_momentumJets
         *
         *  @param momentumJets Momentum of reconstructed jets
         */
        void SetMomentumJets(DoubleVector momentumJets);

        /**
         *  @brief Get m_momentumJets
         */
        DoubleVector GetMomentumJets() const;

        /**
         *  @brief Set m_transverseMomentumJets
         *
         *  @param transverseMomentumJets Transverse momentum of reconstructed jets
         */
        void SetTransverseMomentumJets(DoubleVector transverseMomentumJets);

        /**
         *  @brief Get m_transverseMomentumJets
         */
        DoubleVector GetTransverseMomentumJets() const;

        /**
         *  @brief Set m_cosThetaJets
         *
         *  @param cosThetaJets CosTheta of reconstructed jets
         */
        void SetCosThetaJets(DoubleVector cosThetaJets);

        /**
         *  @brief Get m_cosThetaJets
         */
        DoubleVector GetCosThetaJets() const;

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
         *  @brief Set m_energyNeutrinos
         *
         *  @param energyNeutrinos Energy of neutrinos
         */
        void SetEnergyNeutrinos(DoubleVector energyNeutrinos);

        /**
         *  @brief Get m_energyNeutrinos
         */
        DoubleVector GetEnergyNeutrinos() const;

        /**
         *  @brief Set m_pxMomentumNeutrinos, m_pyMomentumNeutrinos, m_pzMomentumNeutrinos
         *
         *  @param pxMomentumNeutrinos Px of neutrinos
         *  @param pyMomentumNeutrinos Py of neutrinos
         *  @param pzMomentumNeutrinos Pz of neutrinos
         */
        void SetMomentumNeutrinos(DoubleVector pxMomentumNeutrinos, DoubleVector pyMomentumNeutrinos, DoubleVector pzMomentumNeutrinos);

        /**
         *  @brief Set m_energyQuarks
         *
         *  @param energyQuarks Energy of neutrinos
         */
        void SetEnergyQuarks(DoubleVector energyQuarks);

        /**
         *  @brief Get m_energyQuarks
         */
        DoubleVector GetEnergyQuarks() const;

        /**
         *  @brief Set m_pxMomentumQuarks, m_pyMomentumQuarks, m_pzMomentumQuarks
         *
         *  @param pxMomentumQuarks Px of neutrinos
         *  @param pyMomentumQuarks Py of neutrinos
         *  @param pzMomentumQuarks Pz of neutrinos
         */
        void SetMomentumQuarks(DoubleVector pxMomentumQuarks, DoubleVector pyMomentumQuarks, DoubleVector pzMomentumQuarks);

        /**
         *  @brief Set m_mcParticleToQuarkMap
         *
         *  @param mcParticleToQuarkMap
         */
        void SetMCParticleToQuarkMap(MCParticleToMCParticleMap mcParticleToQuarkMap);

        /**
         *  @brief Get m_mcParticleToQuarkMap
         */
        MCParticleToMCParticleMap GetMCParticleToQuarkMap() const;

        /**
         *  @brief Set m_cheatedInvMasses
         *
         *  @param cheatedInvMasses chated invaraint masses
         */
        void SetCheatedInvMasses(DoubleVector cheatedInvMasses);

        /**
         *  @brief Get m_cheatedInvMasses
         */
        DoubleVector GetCheatedInvMasses() const;

    private:
        bool             m_appropriateEvent;                             ///< Does event pass a series of cuts suggesting it has a vvqqqq final state? - JetAnalysis
        bool             m_isEventWW;                                    ///< Are the invariant masses of the jets close to the W boson mass? - JetAnalysis
        bool             m_isEventWWMC;                                  ///< Are the invariant masses of the quark pairs close to the W boson mass? - MCAnalysis
        bool             m_isEventZZ;                                    ///< Are the invariant masses of the jets close to the Z boson mass? - JetAnalysis
        bool             m_isEventZZMC;                                  ///< Are the invariant masses of the quark pairs close to the Z boson mass? - MCAnalysis
        int              m_nPfosBosonW1;                                 ///< Number of pfos in W boson 1 in W pairing - JetAnalysis
        int              m_nPfosBosonW2;                                 ///< Number of pfos in W boson 2 in W pairing - JetAnalysis
        int              m_nPfosBosonZ1;                                 ///< Number of pfos in W boson 1 in Z pairing - JetAnalysis
        int              m_nPfosBosonZ2;                                 ///< Number of pfos in W boson 2 in Z pairing - JetAnalysis
        int              m_highestEnergyPfoPDG;                          ///< PDG of highest energy PFO - RawPfoAnalysis
        int              m_nIsolatedLeptons;                             ///< Number of isolated leptons identified in isolated lepton finder - IsolatedLeptonPfoAnalysis
        int              m_highestEnergyIsolatedLeptonPDG;               ///< PDG of highest energy PFO from isolated lepton finder - IsolatedLeptonPfoAnalysis
        int              m_secondHighestEnergyIsolatedLeptonPDG;         ///< PDG of second highest energy PFO from isolated lepton finder - IsolatedLeptonPfoAnalysis
        IntVector        m_combinationWJets;                             ///< Combination of jets to form W bosons - JetAnalysis
        IntVector        m_combinationZJets;                             ///< Combination of jets to form Z bosons - JetAnalysis
        IntVector        m_nParticlesJets;                               ///< Number of particles in reconstructed jet - JetAnalysis
        IntVector        m_nChargedParticlesJets;                        ///< Number of charged particles in reconstructed jet - JetAnalysis
        double           m_eventEnergyMC;                                ///< MC event energy
        double           m_transverseMomentum;                           ///< Transverse momentum of reconstructed system - JetAnalysis
        double           m_transverseMomentumMC;                         ///< Transverse momentum of quark system - MCAnalysis
        double           m_transverseEnergy;                             ///< Transverse energy of reconstructed system - JetAnalysis
        double           m_transverseEnergyMC;                           ///< Transverse energy of quark system - MCAnalysis
        double           m_energyBosonW1;                                ///< Energy of W boson 1 - JetAnalysis
        double           m_energyBosonW2;                                ///< Energy of W boson 2 - JetAnalysis
        double           m_energyBosonZ1;                                ///< Energy of Z boson 1 - JetAnalysis
        double           m_energyBosonZ2;                                ///< Energy of Z boson 2 - JetAnalysis
        double           m_momentumBosonW1;                              ///< Momentum of W boson 1 - JetAnalysis
        double           m_momentumBosonW2;                              ///< Momentum of W boson 2 - JetAnalysis
        double           m_momentumBosonZ1;                              ///< Momentum of Z boson 1 - JetAnalysis
        double           m_momentumBosonZ2;                              ///< Momentum of Z boson 2 - JetAnalysis
        double           m_transverseMomentumBosonW1;                    ///< Transverse momentum of W boson 1 in W pairing - JetAnalysis
        double           m_transverseMomentumBosonW2;                    ///< Transverse momentum of W boson 2 in W pairing - JetAnalysis
        double           m_transverseMomentumBosonZ1;                    ///< Transverse momentum of W boson 1 in Z pairing - JetAnalysis
        double           m_transverseMomentumBosonZ2;                    ///< Transverse momentum of W boson 2 in Z pairing - JetAnalysis
        double           m_cosThetaBosonW1;                              ///< CosTheta of W boson 1 - JetAnalysis
        double           m_cosThetaBosonW2;                              ///< CosTheta of W boson 2 - JetAnalysis
        double           m_cosThetaBosonZ1;                              ///< CosTheta of Z boson 1 - JetAnalysis
        double           m_cosThetaBosonZ2;                              ///< CosTheta of Z boson 2 - JetAnalysis
        double           m_transverseEnergyBosonW1;                      ///< Transverse energy of W boson 1 in W pairing - JetAnalysis
        double           m_transverseEnergyBosonW2;                      ///< Transverse energy of W boson 2 in W pairing - JetAnalysis
        double           m_transverseEnergyBosonZ1;                      ///< Transverse energy of Z boson 1 in Z pairing - JetAnalysis
        double           m_transverseEnergyBosonZ2;                      ///< Transverse energy of Z boson 2 in Z pairing - JetAnalysis
        double           m_cosThetaMissing;                              ///< Cosine theta of missing energy - JetAnalysis
        double           m_cosThetaMissingMC;                            ///< Cosine theta of neutrino energy - MCAnalysis
        double           m_cosThetaMostEnergeticTrack;                   ///< Cosine theta of highest energy track in system - JetAnalysis
        double           m_recoilMass;                                   ///< Recoil mass of reconstructed system - JetAnalysis
        double           m_recoilMassMC;                                 ///< Recoil mass of quark system - MCAnalysis
        double           m_energyAroundMostEnergeticPfo;                 ///< Energy in cone around most energetic pfo - JetAnalysis
        double           m_y12;                                          ///< Jet grouping parameter
        double           m_y23;                                          ///< Jet grouping parameter
        double           m_y34;                                          ///< Jet grouping parameter
        double           m_y45;                                          ///< Jet grouping parameter
        double           m_y56;                                          ///< Jet grouping parameter
        double           m_y67;                                          ///< Jet grouping parameter
        double           m_invariantMassSystem;                          ///< Invariant mass of the jet system - JetAnalysis
        double           m_invariantMassSystemMC;                        ///< Invariant mass of the quark system - MCAnalysis
        double           m_cosThetaStarWBosons;                          ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs - JetAnalysis
        double           m_cosThetaStarWBosonsMC;                        ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs - MCAnalysis
        double           m_cosThetaStarZBosons;                          ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs - JetAnalysis
        double           m_cosThetaStarZBosonsMC;                        ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs - MCAnalysis
        double           m_acolinearityJetsW1;                           ///< Acolinearity of the jets from boson 1 in W pairing - JetAnalysis
        double           m_acolinearityJetsW2;                           ///< Acolinearity of the jets from boson 2 in W pairing - JetAnalysis
        double           m_acolinearityJetsZ1;                           ///< Acolinearity of the jets from boson 1 in Z pairing - JetAnalysis
        double           m_acolinearityJetsZ2;                           ///< Acolinearity of the jets from boson 2 in Z pairing - JetAnalysis
        double           m_acolinearityBosonsW;                          ///< Acolinearity of the W bosons in W pairing - JetAnalysis- SelectionProcessor
        double           m_acolinearityBosonsZ;                          ///< Acolinearity of the W bosons in Z pairing - JetAnalysis- SelectionProcessor
        double           m_principleThrustValue;                         ///< Principle thrust value from ThrustReconstruction processor- SelectionProcessor
        double           m_majorThrustValue;                             ///< Major thrust value from ThrustReconstruction processor- SelectionProcessor
        double           m_minorThrustValue;                             ///< Minor thrust value from ThrustReconstruction processor - SelectionProcessor
        double           m_xThrustAxis;                                  ///< X Thrust axis value from ThrustReconstruction processor - SelectionProcessor
        double           m_yThrustAxis;                                  ///< Y Thrust axis value from ThrustReconstruction processor  - SelectionProcessor
        double           m_zThrustAxis;                                  ///< Z Thrust axis value from ThrustReconstruction processor - SelectionProcessor
        double           m_sphericity;                                   ///< Sphericity from Sphere processor - SelectionProcessor
        double           m_aplanarity;                                   ///< Aplnarity from Sphere processor - SelectionProcessor
        double           m_highestEnergyElectronE;                       ///< Energy of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyElectronP;                       ///< Magnitude of momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyElectronPt;                      ///< Transverse momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyElectronCosTheta;                ///< Consine theta of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyMuonE;                           ///< Energy of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyMuonP;                           ///< Magnitude of momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyMuonPt;                          ///< Transverse momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyMuonCosTheta;                    ///< Consine theta of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPhotonE;                         ///< Energy of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPhotonP;                         ///< Magnitude of momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPhotonPt;                        ///< Transverse momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPhotonCosTheta;                  ///< Consine theta of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPfoE;                            ///< Energy of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPfoP;                            ///< Magnitude of momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPfoPt;                           ///< Transverse momentum of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyPfoCosTheta;                     ///< Consine theta of highest energy electron - RawPfoAnalysis
        double           m_highestEnergyIsolatedLeptonE;                 ///< Energy of highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_highestEnergyIsolatedLeptonP;                 ///< Magnitude of momentum of highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_highestEnergyIsolatedLeptonPt;                ///< Transverse momentum of highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_highestEnergyIsolatedLeptonCosTheta;          ///< Consine theta of highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_secondHighestEnergyIsolatedLeptonE;           ///< Energy of second highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_secondHighestEnergyIsolatedLeptonP;           ///< Magnitude of momentum of second highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_secondHighestEnergyIsolatedLeptonPt;          ///< Transverse momentum of second highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_secondHighestEnergyIsolatedLeptonCosTheta;    ///< Consine theta of second highest energy lepton from isolated lepton finding - IsolatedLeptonPfoAnalysis
        double           m_maxBTagForBosonW1;                            ///< Max b tag for jets in W Boson 1 - JetAnalysis
        double           m_minBTagForBosonW1;                            ///< Min b tag for jets in W Boson 1 - JetAnalysis
        double           m_maxBTagForBosonW2;                            ///< Max b tag for jets in W Boson 2 - JetAnalysis
        double           m_minBTagForBosonW2;                            ///< Min b tag for jets in W Boson 2 - JetAnalysis
        double           m_maxCTagForBosonW1;                            ///< Max c tag for jets in W Boson 1 - JetAnalysis
        double           m_minCTagForBosonW1;                            ///< Min c tag for jets in W Boson 1 - JetAnalysis
        double           m_maxCTagForBosonW2;                            ///< Max c tag for jets in W Boson 2 - JetAnalysis
        double           m_minCTagForBosonW2;                            ///< Min c tag for jets in W Boson 2 - JetAnalysis
        double           m_maxBTagForBosonZ1;                            ///< Max b tag for jets in Z Boson 1 - JetAnalysis
        double           m_minBTagForBosonZ1;                            ///< Min b tag for jets in Z Boson 1 - JetAnalysis
        double           m_maxBTagForBosonZ2;                            ///< Max b tag for jets in Z Boson 2 - JetAnalysis
        double           m_minBTagForBosonZ2;                            ///< Min b tag for jets in Z Boson 2 - JetAnalysis
        double           m_maxCTagForBosonZ1;                            ///< Max c tag for jets in Z Boson 1 - JetAnalysis
        double           m_minCTagForBosonZ1;                            ///< Min c tag for jets in Z Boson 1 - JetAnalysis
        double           m_maxCTagForBosonZ2;                            ///< Max c tag for jets in Z Boson 2 - JetAnalysis
        double           m_minCTagForBosonZ2;                            ///< Min c tag for jets in Z Boson 2 - JetAnalysis
        DoubleVector     m_invariantMassWBosons;                         ///< Invariant mass of first and second pair of W paired jets - JetAnalysis
        DoubleVector     m_invariantMassWBosonsMC;                       ///< Invariant mass of first and second pair of W paired quarks - MCAnalysis
        DoubleVector     m_invariantMassZBosons;                         ///< Invariant mass of first and second pair of Z paired jets - JetAnalysis
        DoubleVector     m_invariantMassZBosonsMC;                       ///< Invariant mass of first and second pair of Z paired quarks - MCAnalysis
        DoubleVector     m_energyJets;                                   ///< Energy of reconstructed jets  - JetAnalysis
        DoubleVector     m_momentumJets;                                 ///< Momentum of reconstructed jets  - JetAnalysis
        DoubleVector     m_transverseMomentumJets;                       ///< Transverse momentum of reconstructed jets  - JetAnalysis
        DoubleVector     m_cosThetaJets;                                 ///< CosTheta of reconstructed jets  - JetAnalysis
        DoubleVector     m_cosThetaStarWJets;                            ///< Cosine of the polar angle of the q jets in the reference frome of the W bosons - JetAnalysis
        DoubleVector     m_cosThetaStarZJets;                            ///< Cosine of the polar angle of the q jets in the reference frome of the Z bosons - JetAnalysis
        DoubleVector     m_bTagForJets;                                  ///< B tag value for the jets in the event - JetAnalysis
        DoubleVector     m_cTagForJets;                                  ///< C tag value for the jets in the event - JetAnalysis
        DoubleVector     m_energyNeutrinos;                              ///< Energy of neutrinos
        DoubleVector     m_pxMomentumNeutrinos;                          ///< Px of neutrinos
        DoubleVector     m_pyMomentumNeutrinos;                          ///< Py of neutrinos
        DoubleVector     m_pzMomentumNeutrinos;                          ///< Pz of neutrinos
        DoubleVector     m_energyQuarks;                                 ///< Energy of quarks
        DoubleVector     m_pxMomentumQuarks;                             ///< Px of quarks
        DoubleVector     m_pyMomentumQuarks;                             ///< Py of quarks
        DoubleVector     m_pzMomentumQuarks;                             ///< Pz of quarks
        DoubleVector     m_cheatedInvMasses;                             ///< Cheated inv masses
        MCParticleToMCParticleMap m_mcParticleToQuarkMap;                ///< Map of MC particles to quarks
};

#endif // #ifndef VARIABLES_H
