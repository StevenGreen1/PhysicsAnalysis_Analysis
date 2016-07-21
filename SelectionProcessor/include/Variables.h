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

#include "TTree.h"

namespace variables_namespace
{
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
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
         *  @brief Print to screen all bool, int, float and selected vector member variables
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
        void SetTransverseMomentum(float transverseMomentum);

        /**
         *  @brief Get m_TransverseMomentum
         */
        float GetTransverseMomentum() const;

        /**
         *  @brief Set m_MCTransverseMomentum
         *
         *  @param mcTransverseMomentum Transverse momentum of quark system
         */
        void SetMCTransverseMomentum(float mcTransverseMomentum);

        /**
         *  @brief Get m_MCTransverseMomentum
         */
        float GetMCTransverseMomentum() const;

        /**
         *  @brief Set m_TransverseEnergy
         *
         *  @param transverseEnergy Transverse energy of reconstructed system
         */
        void SetTransverseEnergy(float transverseEnergy);

        /**
         *  @brief Get m_TransverseEnergy
         */
        float GetTransverseEnergy() const;

        /**
         *  @brief Set m_MCTransverseEnergy
         *
         *  @param mcTransverseEnergy Transverse energy of quark system
         */
        void SetMCTransverseEnergy(float mcTransverseEnergy);

        /**
         *  @brief Get m_MCTransverseEnergy
         */
        float GetMCTransverseEnergy() const;

        /**
         *  @brief Set m_CosThetaMissing
         *
         *  @param cosThetaMissing Cosine theta of missing energy
         */
        void SetCosThetaMissing(float cosThetaMissing);

        /**
         *  @brief Get m_CosThetaMissing
         */
        float GetCosThetaMissing() const;

        /**
         *  @brief Set m_MCCosThetaMissing
         *
         *  @param mcCosThetaMissing Cosine theta of neutrino energy
         */
        void SetMCCosThetaMissing(float mcCosThetaMissing);

        /**
         *  @brief Get m_MCCosThetaMissing
         */
        float GetMCCosThetaMissing() const;

        /**
         *  @brief Set m_CosThetaMostEnergeticTrack 
         *
         *  @param cosThetaMostEnergeticTrack Cosine theta of highest energy track in system
         */
        void SetCosThetaMostEnergeticTrack(float cosThetaMostEnergeticTrack);

        /** 
         *  @brief Get m_CosThetaMostEnergeticTrack
         */
        float GetCosThetaMostEnergeticTrack() const;

        /**
         *  @brief Set m_RecoilMass
         *
         *  @param recoilMass Recoil mass of reconstructed system
         */
        void SetRecoilMass(float recoilMass);

        /**
         *  @brief Get m_RecoilMass
         */
        float GetRecoilMass() const;

        /**
         *  @brief Set m_MCRecoilMass
         *
         *  @param mcRecoilMass Recoil mass of quark system
         */
        void SetMCRecoilMass(float mcRecoilMass);

        /**
         *  @brief Get m_MCRecoilMass
         */
        float GetMCRecoilMass() const;

        /**
         *  @brief Set m_EnergyAroundMostEnergeticPfo
         *
         *  @param energyAroundMostEnergeticPfo Energy in cone around most energetic pfo
         */
        void SetEnergyAroundMostEnergeticPfo(float energyAroundMostEnergeticPfo);

        /**
         *  @brief Get m_EnergyAroundMostEnergeticPfo
         */
        float GetEnergyAroundMostEnergeticPfo() const;

        /**
         *  @brief Set m_y34
         *
         *  @param y34 Jet grouping parameter
         */
        void SetY34(float y34);

        /**
         *  @brief Get m_y34
         */
        float GetY34() const;

        /**
         *  @brief Set m_InvariantMassSystem
         *
         *  @param invariantMassSystem Invariant mass of the jet system
         */
        void SetInvariantMassSystem(float invariantMassSystem);

        /**
         *  @brief Get m_InvariantMassSystem
         */
        float GetInvariantMassSystem() const;

        /**
         *  @brief Set m_MCInvariantMassSystem
         *
         *  @param mcInvariantMassSystem Invariant mass of the quark system
         */
        void SetMCInvariantMassSystem(float mcInvariantMassSystem);

        /**
         *  @brief Get m_MCInvariantMassSystem
         */
        float GetMCInvariantMassSystem() const;

        /**
         *  @brief Set m_CosThetaStarWBosons
         *
         *  @param cosThetaStarWBosons Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs
         */
        void SetCosThetaStarWBosons(float cosThetaStarWBosons);

        /**
         *  @brief Get m_CosThetaStarWBosons
         */
        float GetCosThetaStarWBosons() const;

        /**
         *  @brief Set m_MCCosThetaStarWBosons
         *
         *  @param mcCosThetaStarWBosons Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs
         */
        void SetMCCosThetaStarWBosons(float mcCosThetaStarWBosons);

        /**
         *  @brief Get m_MCCosThetaStarWBosons
         */
        float GetMCCosThetaStarWBosons() const;

        /**
         *  @brief Set m_CosThetaStarZBosons
         *
         *  @param cosThetaStarZBosons Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs
         */
        void SetCosThetaStarZBosons(float cosThetaStarZBosons);

        /**
         *  @brief Get m_CosThetaStarZBosons
         */
        float GetCosThetaStarZBosons() const;

        /**
         *  @brief Set m_MCCosThetaStarZBosons
         *
         *  @param mcCosThetaStarZBosons Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs
         */
        void SetMCCosThetaStarZBosons(float mcCosThetaStarZBosons);

        /**
         *  @brief Get m_MCCosThetaStarZBosons
         */
        float GetMCCosThetaStarZBosons() const;

// FloatVectors

        /**
         *  @brief Set m_InvMassWVectors
         *
         *  @param invMassWVectors Invariant mass of first and second pair of W paired jets
         */
        void SetInvMassWVectors(FloatVector invMassWVectors);

        /**
         *  @brief Get m_InvMassWVectors
         */
        FloatVector GetInvMassWVectors() const;

        /**
         *  @brief Set m_InvMassZVectors 
         *
         *  @param invMassZVectors Invariant mass of first and second pair of Z paired jets
         */
        void SetInvMassZVectors(FloatVector invMassZVectors);

        /**
         *  @brief Get m_InvMassZVectors
         */
        FloatVector GetInvMassZVectors() const;

        /**
         *  @brief Set m_MCInvMassWVectors
         *
         *  @param invMassWVectors Invariant mass of first and second pair of W paired quarks
         */
        void SetMCInvMassWVectors(FloatVector mcInvMassWVectors);

        /**
         *  @brief Get m_MCInvMassWVectors
         */
        FloatVector GetMCInvMassWVectors() const;

        /**
         *  @brief Set m_MCInvMassZVectors
         *
         *  @param mcInvMassZVectors Invariant mass of first and second pair of Z paired quarks
         */
        void SetMCInvMassZVectors(FloatVector mcInvMassZVectors);

        /**
         *  @brief Get m_MCInvMassZVectors
         */
        FloatVector GetMCInvMassZVectors() const;

        /**
         *  @brief Set m_EnergyJets
         *
         *  @param energyJets Energy of reconstructed jets
         */
        void SetEnergyJets(FloatVector energyJets);

        /**
         *  @brief Get m_EnergyJets
         */
        FloatVector GetEnergyJets() const;

        /**
         *  @brief Get lowest number in m_EnergyJets
         */
        float GetLowestEnergyJet() const;

        /**
         *  @brief Set m_CosThetaStarWJets
         *
         *  @param cosThetaStarWJets Cosine of the polar angle of the q jets in the reference frome of the W bosons
         */
        void SetCosThetaStarWJets(FloatVector cosThetaStarWJets);

        /**
         *  @brief Get m_CosThetaStarWJets
         */
        FloatVector GetCosThetaStarWJets() const;

        /**
         *  @brief Set m_CosThetaStarZJets
         *
         *  @param cosThetaStarZJets Cosine of the polar angle of the q jets in the reference frome of the Z bosons
         */
        void SetCosThetaStarZJets(FloatVector cosThetaStarZJets);

        /**
         *  @brief Get m_CosThetaStarZJets
         */
        FloatVector GetCosThetaStarZJets() const;

        /**
         *  @brief Set
         *
         *  @param
         */
//        void Set(FloatVector );

        /**
         *  @brief Get
         */
//        FloatVector Get();

    private:
        bool            m_AppropriateEvent;                 ///< Does event pass a series of cuts suggesting it has a vvqqqq final state? - JetAnalysis
        bool            m_IsEventWW;                        ///< Are the invariant masses of the jets close to the W boson mass? - JetAnalysis
        bool            m_IsMCEventWW;                      ///< Are the invariant masses of the quark pairs close to the W boson mass? - MCAnalysis
        bool            m_IsEventZZ;                        ///< Are the invariant masses of the jets close to the Z boson mass? - JetAnalysis
        bool            m_IsMCEventZZ;                      ///< Are the invariant masses of the quark pairs close to the Z boson mass? - MCAnalysis

        IntVector       m_NParticlesJets;                   ///< Number of particles in reconstructed jet - JetAnalysis
        IntVector       m_NChargedParticlesJets;            ///< Number of charged particles in reconstructed jet - JetAnalysis

        float           m_TransverseMomentum;               ///< Transverse momentum of reconstructed system - JetAnalysis
        float           m_MCTransverseMomentum;             ///< Transverse momentum of quark system - MCAnalysis
        float           m_TransverseEnergy;                 ///< Transverse energy of reconstructed system - JetAnalysis
        float           m_MCTransverseEnergy;               ///< Transverse energy of quark system - MCAnalysis
        float           m_CosThetaMissing;                  ///< Cosine theta of missing energy - JetAnalysis
        float           m_MCCosThetaMissing;                ///< Cosine theta of neutrino energy - MCAnalysis
        float           m_CosThetaMostEnergeticTrack;       ///< Cosine theta of highest energy track in system - JetAnalysis
        float           m_RecoilMass;                       ///< Recoil mass of reconstructed system - JetAnalysis
        float           m_MCRecoilMass;                     ///< Recoil mass of quark system - MCAnalysis
        float           m_EnergyAroundMostEnergeticPfo;     ///< Energy in cone around most energetic pfo - JetAnalysis
        float           m_y34;                              ///< Jet grouping parameter
        float           m_InvariantMassSystem;              ///< Invariant mass of the jet system - JetAnalysis
        float           m_MCInvariantMassSystem;            ///< Invariant mass of the quark system - MCAnalysis
        float           m_CosThetaStarWBosons;              ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs - JetAnalysis
        float           m_MCCosThetaStarWBosons;            ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs - MCAnalysis
        float           m_CosThetaStarZBosons;              ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs - JetAnalysis
        float           m_MCCosThetaStarZBosons;            ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs - MCAnalysis

        FloatVector     m_InvMassWVectors;                  ///< Invariant mass of first and second pair of W paired jets - JetAnalysis
        FloatVector     m_InvMassZVectors;                  ///< Invariant mass of first and second pair of Z paired jets - JetAnalysis
        FloatVector     m_MCInvMassWVectors;                ///< Invariant mass of first and second pair of W paired quarks - MCAnalysis
        FloatVector     m_MCInvMassZVectors;                ///< Invariant mass of first and second pair of Z paired quarks - MCAnalysis
        FloatVector     m_EnergyJets;                       ///< Energy of reconstructed jets  - JetAnalysis
        FloatVector     m_CosThetaStarWJets;                ///< Cosine of the polar angle of the q jets in the reference frome of the W bosons - JetAnalysis
        FloatVector     m_CosThetaStarZJets;                ///< Cosine of the polar angle of the q jets in the reference frome of the Z bosons - JetAnalysis
};

#endif // #ifndef VARIABLES_H
