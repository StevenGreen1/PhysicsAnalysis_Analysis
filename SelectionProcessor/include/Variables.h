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

        IntVector       m_NParticlesJets;                   ///< Number of particles in reconstructed jet - JetAnalysis
        IntVector       m_NChargedParticlesJets;            ///< Number of charged particles in reconstructed jet - JetAnalysis

        double           m_TransverseMomentum;               ///< Transverse momentum of reconstructed system - JetAnalysis
        double           m_MCTransverseMomentum;             ///< Transverse momentum of quark system - MCAnalysis
        double           m_TransverseEnergy;                 ///< Transverse energy of reconstructed system - JetAnalysis
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

        DoubleVector     m_InvMassWVectors;                  ///< Invariant mass of first and second pair of W paired jets - JetAnalysis
        DoubleVector     m_MCInvMassWVectors;                ///< Invariant mass of first and second pair of W paired quarks - MCAnalysis
        DoubleVector     m_InvMassZVectors;                  ///< Invariant mass of first and second pair of Z paired jets - JetAnalysis
        DoubleVector     m_MCInvMassZVectors;                ///< Invariant mass of first and second pair of Z paired quarks - MCAnalysis
        DoubleVector     m_EnergyJets;                       ///< Energy of reconstructed jets  - JetAnalysis
        DoubleVector     m_CosThetaStarWJets;                ///< Cosine of the polar angle of the q jets in the reference frome of the W bosons - JetAnalysis
        DoubleVector     m_CosThetaStarZJets;                ///< Cosine of the polar angle of the q jets in the reference frome of the Z bosons - JetAnalysis
};

#endif // #ifndef VARIABLES_H
