/**
 *  @file   SelectionProcessor/include/MCAnalysis.h
 *
 *  @brief  Header file for the mc analysis class.
 *
 *  $Log: $
 */

#ifndef MC_ANALYSIS_H
#define MC_ANALYSIS_H 1

#include <string>
#include <vector>

#include "EVENT/LCCollection.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"

#include "TLorentzVector.h"

#include "Variables.h"

class MCAnalysis 
{
    typedef std::vector<const EVENT::ReconstructedParticle*> ParticleVector;
    typedef std::vector<const EVENT::MCParticle*> MCParticleVector;

    public:
        /**
         *  @brief Constructor
         */
        MCAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables);

        /**
         *  @brief Destructor
         */
        ~MCAnalysis();

    private:
        /** 
         *  @brief Run the mc analysis process to set variables of interest
         */
        void Process();

        /**
         *  @brief
         */
        void QuarkPairing();

        /**
         *  @brief Calculate the invariant mass of all particles in mcParticleVector
         *
         *  @param mcParticleVector vector of pointers to lcio mc particles
         *  @param invariantMass invariant mass of the system of lcio mc particles in mcParticleVector
         */
        void FindMCInvariantMass(MCParticleVector &mcParticleVector, double &invariantMass) const;

        /**
         *  @brief Calculate the transverse momentum of all particles in m_quarkMCParticleVector
         */
        void CalculateMCTransverseMomentum();

        /**
         *  @brief Calculate the transverse energy of all particles in m_quarkMCParticleVector
         */
        void CalculateMCTransverseEnergy();

        /**
         *  @brief Calculate the cosine theta of the missing momentum vector using m_JetVector
         */
        void CalculateMCCosThetaMissingMomentum();

        /**
         *  @brief Calculate the recoil mass of the event (magnitude of neutrino momentum 4 vector)
         */ 
        void CalculateMCRecoilMass();

        /**
         *  @brief Determine whether event is from WW pair
         */
        void IsMCEventWW();

        /**
         *  @brief Determine whether event is from ZZ pair
         */
        void IsMCEventZZ();

        /**
         *  @ brief Do some awesome physics with the output
         */
        void DefineMCVariablesOfInterest();

        /**
         * @brief Calculate the cosine of the polar angle of the object of interest in the reference frame defined by the object of interest and the reference frame objects
         *
         * @param objectOfInterest MCParticleVector defining energy 4 vector for direction in question
         * @param referenceFrameObjects MCParticleVector defining energy 4 vector for reference frame for polar angle calculation
         * @param cosThetaStar cosine of the polar angle of the objectOfInterest in a reference frame defined by objectOfInterest and referenceFrameObjects
         */
        void CalculateMCCosThetaStar(MCParticleVector objectOfInterest, MCParticleVector referenceFrameObjects, double &cosThetaStar) const;

        /**
         * @brief Calculate the energy 4 vector for a given vector of lcio particles
         *
         * @param mcParticleVector vector of lcio mc particles
         * @param tLorentzVector energy 4 vector of all particles in mcParticleVector to set
         */
        void DefineMCEnergy4Vec(MCParticleVector &mcParticleVector, TLorentzVector &tLorentzVector) const;

        Variables             *m_pVariables;                ///< Variables of interest to set for analysis
        MCParticleVector       m_neutrinoMCParticleVector;  ///< Vector of neutrino MC particles 
        MCParticleVector       m_quarkMCParticleVector;     ///< Vector of MC particles 
        MCParticleVector       m_mcWVector1;                ///< First W candidate
        MCParticleVector       m_mcWVector2;                ///< Second W candidate
        MCParticleVector       m_mcZVector1;                ///< First Z candidate
        MCParticleVector       m_mcZVector2;                ///< Second Z candidate
        const double           m_wBosonMass;                ///< W boson mass used for quark pairing
        const double           m_zBosonMass;                ///< Z boson mass used for quark pairing
        const double           m_crossingAngle;             ///< Crossing angle for CLIC ILD, radians
        const double           m_eventEnergyMC;             ///< MC event energy excluding beam effects
        double                 m_y34;                       ///< Jet clustering variable
};

#endif // #ifndef MC_ANALYSIS_H
