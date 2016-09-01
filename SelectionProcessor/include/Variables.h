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

#include "TInterpreter.h"
#include "TTree.h"

namespace variables_namespace
{
    typedef std::vector<int> IntVector;
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

// Bools

        /**
         *  @brief Set m_AppropriateEvent
         *
         *  @param appropriateEvent Does event mass cuts to suggest vvqqqq final state
         */
        void SetAppropriateEvent(bool appropriateEvent);

        /**
         *  @brief Get m_AppropriateEvent
         */
        bool GetAppropriateEvent() const;

        /**
         *  @brief Set m_IsEventWW
         *
         *  @param isEventWW Are the invariant masses of the jets close to the W boson mass
         */
        void SetIsEventWW(bool isEventWW);

        /*
         *  @brief Get m_IsEventWW
         */
        bool GetIsEventWW() const;

        /**
         *  @brief Set m_IsMCEventWW
         *
         *  @param isMCEventWW Are the invariant masses of the quarks close to the W boson mass
         */
        void SetIsMCEventWW(bool isMCEventWW);

        /*
         *  @brief Get m_IsMCEventWW
         */
        bool GetIsMCEventWW() const;

        /**
         *  @brief Set m_IsEventZZ
         *
         *  @param isEventZZ Are the invariant masses of the jets close to the Z boson mass
         */
        void SetIsEventZZ(bool isEventZZ);

        /*
         *  @brief Get m_IsEventZZ
         */
        bool GetIsEventZZ() const;

        /**
         *  @brief Set m_IsMCEventZZ
         *
         *  @param isMCEventZZ Are the invariant masses of the quarks close to the Z boson mass
         */
        void SetIsMCEventZZ(bool isMCEventZZ);

        /*
         *  @brief Get m_IsMCEventZZ
         */
        bool GetIsMCEventZZ() const;

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
         *  @brief Set m_NParticlesJets
         *
         *  @param nParticlesJets The number of particles in jets
         */
        void SetNParticlesJets(IntVector nParticlesJets);

        /**
         *  @brief Get m_NParticlesJets
         */
        IntVector GetNParticlesJets() const;

        /**
         *  @brief Get lowest number in m_NParticlesJets
         */
        int GetLowestNParticlesJets() const;

        /**
         *  @brief Set m_NChargedParticlesJets
         *
         *  @param nChargedParticlesJets The number of charged particles in jets
         */
        void SetNChargedParticlesJets(IntVector nChargedParticlesJets);

        /**
         *  @brief Get m_NChargedParticlesJets
         */
        IntVector GetNChargedParticlesJets() const;

        /**
         *  @brief Get lowest number in m_NChargedParticlesJets
         */
        int GetLowestNChargedParticlesJets() const;

// Floats

        /**
         *  @brief Set m_TransverseMomentum
         *
         *  @param transverseMomentum Transverse momentum of reconstructed system
         */
        void SetTransverseMomentum(double transverseMomentum);

        /**
         *  @brief Get m_TransverseMomentum
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
         *  @brief Set m_MCTransverseMomentum
         *
         *  @param mcTransverseMomentum Transverse momentum of quark system
         */
        void SetMCTransverseMomentum(double mcTransverseMomentum);

        /**
         *  @brief Get m_MCTransverseMomentum
         */
        double GetMCTransverseMomentum() const;

        /**
         *  @brief Set m_TransverseEnergy
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
         *  @brief Get m_TransverseEnergy
         */
        double GetTransverseEnergy() const;

        /**
         *  @brief Set m_MCTransverseEnergy
         *
         *  @param mcTransverseEnergy Transverse energy of quark system
         */
        void SetMCTransverseEnergy(double mcTransverseEnergy);

        /**
         *  @brief Get m_MCTransverseEnergy
         */
        double GetMCTransverseEnergy() const;

        /**
         *  @brief Set m_CosThetaMissing
         *
         *  @param cosThetaMissing Cosine theta of missing energy
         */
        void SetCosThetaMissing(double cosThetaMissing);

        /**
         *  @brief Get m_CosThetaMissing
         */
        double GetCosThetaMissing() const;

        /**
         *  @brief Set m_MCCosThetaMissing
         *
         *  @param mcCosThetaMissing Cosine theta of neutrino energy
         */
        void SetMCCosThetaMissing(double mcCosThetaMissing);

        /**
         *  @brief Get m_MCCosThetaMissing
         */
        double GetMCCosThetaMissing() const;

        /**
         *  @brief Set m_CosThetaMostEnergeticTrack 
         *
         *  @param cosThetaMostEnergeticTrack Cosine theta of highest energy track in system
         */
        void SetCosThetaMostEnergeticTrack(double cosThetaMostEnergeticTrack);

        /** 
         *  @brief Get m_CosThetaMostEnergeticTrack
         */
        double GetCosThetaMostEnergeticTrack() const;

        /**
         *  @brief Set m_RecoilMass
         *
         *  @param recoilMass Recoil mass of reconstructed system
         */
        void SetRecoilMass(double recoilMass);

        /**
         *  @brief Get m_RecoilMass
         */
        double GetRecoilMass() const;

        /**
         *  @brief Set m_MCRecoilMass
         *
         *  @param mcRecoilMass Recoil mass of quark system
         */
        void SetMCRecoilMass(double mcRecoilMass);

        /**
         *  @brief Get m_MCRecoilMass
         */
        double GetMCRecoilMass() const;

        /**
         *  @brief Set m_EnergyAroundMostEnergeticPfo
         *
         *  @param energyAroundMostEnergeticPfo Energy in cone around most energetic pfo
         */
        void SetEnergyAroundMostEnergeticPfo(double energyAroundMostEnergeticPfo);

        /**
         *  @brief Get m_EnergyAroundMostEnergeticPfo
         */
        double GetEnergyAroundMostEnergeticPfo() const;

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
         *  @brief Set m_InvariantMassSystem
         *
         *  @param invariantMassSystem Invariant mass of the jet system
         */
        void SetInvariantMassSystem(double invariantMassSystem);

        /**
         *  @brief Get m_InvariantMassSystem
         */
        double GetInvariantMassSystem() const;

        /**
         *  @brief Set m_MCInvariantMassSystem
         *
         *  @param mcInvariantMassSystem Invariant mass of the quark system
         */
        void SetMCInvariantMassSystem(double mcInvariantMassSystem);

        /**
         *  @brief Get m_MCInvariantMassSystem
         */
        double GetMCInvariantMassSystem() const;

        /**
         *  @brief Set m_CosThetaStarWBosons
         *
         *  @param cosThetaStarWBosons Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs
         */
        void SetCosThetaStarWBosons(double cosThetaStarWBosons);

        /**
         *  @brief Get m_CosThetaStarWBosons
         */
        double GetCosThetaStarWBosons() const;

        /**
         *  @brief Set m_MCCosThetaStarWBosons
         *
         *  @param mcCosThetaStarWBosons Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs
         */
        void SetMCCosThetaStarWBosons(double mcCosThetaStarWBosons);

        /**
         *  @brief Get m_MCCosThetaStarWBosons
         */
        double GetMCCosThetaStarWBosons() const;

        /**
         *  @brief Set m_CosThetaStarZBosons
         *
         *  @param cosThetaStarZBosons Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs
         */
        void SetCosThetaStarZBosons(double cosThetaStarZBosons);

        /**
         *  @brief Get m_CosThetaStarZBosons
         */
        double GetCosThetaStarZBosons() const;

        /**
         *  @brief Set m_MCCosThetaStarZBosons
         *
         *  @param mcCosThetaStarZBosons Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs
         */
        void SetMCCosThetaStarZBosons(double mcCosThetaStarZBosons);

        /**
         *  @brief Get m_MCCosThetaStarZBosons
         */
        double GetMCCosThetaStarZBosons() const;
/////
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

// DoubleVectors

        /**
         *  @brief Set m_InvMassWVectors
         *
         *  @param invMassWVectors Invariant mass of first and second pair of W paired jets
         */
        void SetInvMassWVectors(DoubleVector invMassWVectors);

        /**
         *  @brief Get m_InvMassWVectors
         */
        DoubleVector GetInvMassWVectors() const;

        /**
         *  @brief Set m_InvMassZVectors 
         *
         *  @param invMassZVectors Invariant mass of first and second pair of Z paired jets
         */
        void SetInvMassZVectors(DoubleVector invMassZVectors);

        /**
         *  @brief Get m_InvMassZVectors
         */
        DoubleVector GetInvMassZVectors() const;

        /**
         *  @brief Set m_MCInvMassWVectors
         *
         *  @param invMassWVectors Invariant mass of first and second pair of W paired quarks
         */
        void SetMCInvMassWVectors(DoubleVector mcInvMassWVectors);

        /**
         *  @brief Get m_MCInvMassWVectors
         */
        DoubleVector GetMCInvMassWVectors() const;

        /**
         *  @brief Set m_MCInvMassZVectors
         *
         *  @param mcInvMassZVectors Invariant mass of first and second pair of Z paired quarks
         */
        void SetMCInvMassZVectors(DoubleVector mcInvMassZVectors);

        /**
         *  @brief Get m_MCInvMassZVectors
         */
        DoubleVector GetMCInvMassZVectors() const;

        /**
         *  @brief Set m_EnergyJets
         *
         *  @param energyJets Energy of reconstructed jets
         */
        void SetEnergyJets(DoubleVector energyJets);

        /**
         *  @brief Get m_EnergyJets
         */
        DoubleVector GetEnergyJets() const;

        /**
         *  @brief Get lowest number in m_EnergyJets
         */
        double GetLowestEnergyJet() const;

        /**
         *  @brief Set m_CosThetaStarWJets
         *
         *  @param cosThetaStarWJets Cosine of the polar angle of the q jets in the reference frome of the W bosons
         */
        void SetCosThetaStarWJets(DoubleVector cosThetaStarWJets);

        /**
         *  @brief Get m_CosThetaStarWJets
         */
        DoubleVector GetCosThetaStarWJets() const;

        /**
         *  @brief Set m_CosThetaStarZJets
         *
         *  @param cosThetaStarZJets Cosine of the polar angle of the q jets in the reference frome of the Z bosons
         */
        void SetCosThetaStarZJets(DoubleVector cosThetaStarZJets);

        /**
         *  @brief Get m_CosThetaStarZJets
         */
        DoubleVector GetCosThetaStarZJets() const;

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
        bool            m_AppropriateEvent;                 ///< Does event pass a series of cuts suggesting it has a vvqqqq final state? - JetAnalysis
        bool            m_IsEventWW;                        ///< Are the invariant masses of the jets close to the W boson mass? - JetAnalysis
        bool            m_IsMCEventWW;                      ///< Are the invariant masses of the quark pairs close to the W boson mass? - MCAnalysis
        bool            m_IsEventZZ;                        ///< Are the invariant masses of the jets close to the Z boson mass? - JetAnalysis
        bool            m_IsMCEventZZ;                      ///< Are the invariant masses of the quark pairs close to the Z boson mass? - MCAnalysis
        int             m_nPfosBosonW1;                     ///< Number of pfos in W boson 1 in W pairing - JetAnalysis
        int             m_nPfosBosonW2;                     ///< Number of pfos in W boson 2 in W pairing - JetAnalysis
        int             m_nPfosBosonZ1;                     ///< Number of pfos in W boson 1 in Z pairing - JetAnalysis
        int             m_nPfosBosonZ2;                     ///< Number of pfos in W boson 2 in Z pairing - JetAnalysis
        IntVector       m_NParticlesJets;                   ///< Number of particles in reconstructed jet - JetAnalysis
        IntVector       m_NChargedParticlesJets;            ///< Number of charged particles in reconstructed jet - JetAnalysis

        double           m_TransverseMomentum;               ///< Transverse momentum of reconstructed system - JetAnalysis
        double           m_transverseMomentumBosonW1;        ///< Transverse momentum of W boson 1 in W pairing - JetAnalysis
        double           m_transverseMomentumBosonW2;        ///< Transverse momentum of W boson 2 in W pairing - JetAnalysis
        double           m_transverseMomentumBosonZ1;        ///< Transverse momentum of W boson 1 in Z pairing - JetAnalysis
        double           m_transverseMomentumBosonZ2;        ///< Transverse momentum of W boson 2 in Z pairing - JetAnalysis
        double           m_MCTransverseMomentum;             ///< Transverse momentum of quark system - MCAnalysis
        double           m_TransverseEnergy;                 ///< Transverse energy of reconstructed system - JetAnalysis
        double           m_transverseEnergyBosonW1;          ///< Transverse energy of W boson 1 in W pairing - JetAnalysis
        double           m_transverseEnergyBosonW2;          ///< Transverse energy of W boson 2 in W pairing - JetAnalysis
        double           m_transverseEnergyBosonZ1;          ///< Transverse energy of Z boson 1 in Z pairing - JetAnalysis
        double           m_transverseEnergyBosonZ2;          ///< Transverse energy of Z boson 2 in Z pairing - JetAnalysis
        double           m_MCTransverseEnergy;               ///< Transverse energy of quark system - MCAnalysis
        double           m_CosThetaMissing;                  ///< Cosine theta of missing energy - JetAnalysis
        double           m_MCCosThetaMissing;                ///< Cosine theta of neutrino energy - MCAnalysis
        double           m_CosThetaMostEnergeticTrack;       ///< Cosine theta of highest energy track in system - JetAnalysis
        double           m_RecoilMass;                       ///< Recoil mass of reconstructed system - JetAnalysis
        double           m_MCRecoilMass;                     ///< Recoil mass of quark system - MCAnalysis
        double           m_EnergyAroundMostEnergeticPfo;     ///< Energy in cone around most energetic pfo - JetAnalysis
        double           m_y34;                              ///< Jet grouping parameter
        double           m_InvariantMassSystem;              ///< Invariant mass of the jet system - JetAnalysis
        double           m_MCInvariantMassSystem;            ///< Invariant mass of the quark system - MCAnalysis
        double           m_CosThetaStarWBosons;              ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs - JetAnalysis
        double           m_MCCosThetaStarWBosons;            ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs - MCAnalysis
        double           m_CosThetaStarZBosons;              ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs - JetAnalysis
        double           m_MCCosThetaStarZBosons;            ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs - MCAnalysis
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
        DoubleVector     m_InvMassWVectors;                  ///< Invariant mass of first and second pair of W paired jets - JetAnalysis
        DoubleVector     m_MCInvMassWVectors;                ///< Invariant mass of first and second pair of W paired quarks - MCAnalysis
        DoubleVector     m_InvMassZVectors;                  ///< Invariant mass of first and second pair of Z paired jets - JetAnalysis
        DoubleVector     m_MCInvMassZVectors;                ///< Invariant mass of first and second pair of Z paired quarks - MCAnalysis
        DoubleVector     m_EnergyJets;                       ///< Energy of reconstructed jets  - JetAnalysis
        DoubleVector     m_CosThetaStarWJets;                ///< Cosine of the polar angle of the q jets in the reference frome of the W bosons - JetAnalysis
        DoubleVector     m_CosThetaStarZJets;                ///< Cosine of the polar angle of the q jets in the reference frome of the Z bosons - JetAnalysis
};

#endif // #ifndef VARIABLES_H
