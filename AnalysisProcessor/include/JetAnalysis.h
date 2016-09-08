/**
 *  @file   SelectionProcessor/include/JetAnalysis.h
 *
 *  @brief  Header file for the jet analysis class.
 *
 *  $Log: $
 */

#ifndef JET_ANALYSIS_H
#define JET_ANALYSIS_H 1

#include <string>
#include <vector>

#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "UTIL/PIDHandler.h"

#include "TLorentzVector.h"

#include "Variables.h"

//namespace EVENT { class LCEvent; class MCParticle; class ReconstructedParticle; class ParticleID;}
//namespace UTIL {class PIDHandler;}

class JetAnalysis 
{
    typedef std::vector<const EVENT::ReconstructedParticle*> ParticleVector;
//    typedef std::vector<double> DoubleVector;
//    typedef std::vector<int> IntVector;

    public:
        /**
         *  @brief Constructor
         */
        JetAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables);

        /**
         *  @brief Destructor
         */
        ~JetAnalysis();

    private:
        /**
         *  @brief Run analysis of jets to set variables of interest
         *
         *  @param pLCCollection collection of jets to process
         */
        void ProcessJets(const EVENT::LCCollection *pLCCollection);

        /** 
         *   @brief Run analysis of bosons to set variables of interest
         */
        void ProcessBosons();

        /**
         *  @brief Find the jet clustering variable y34
         *
         *  @param pLCCollection Collection of Pfos to read in
         *  @param y34 jet clustering variable of choice
         */
        void CalculateJetClusteringVariableY34(const EVENT::LCCollection *pLCCollection);

        /**
         *  @brief Find the flavour tagging information for the jets 
         *
         *  @param pLCCollection  collection of jets to process
         */
        void CalculateFlavourTagging(const EVENT::LCCollection *pLCCollection);

        /**
         *  @brief Set the basic jet variables including energy, number of particles and number of charged particles
         */
        void JetVariables();

        /**
         *  @brief Find best pairing of lcio particles to form either two W bosons or two Z bosons
         */
        void JetPairing();

        /**
         *  @brief Calculate number of Pfos in a particleVector of jets e.g. boson with two jets
         *
         *  @param nPfos number of Pfos to set
         */
        void CalculateNumberOfPfos(ParticleVector particleVector, int &nPfos);

        /**
         *  @brief Calculate the acolinearity of the jets from the W/Z bosons and the acolinearity of the W/Z boson itself
         */
        void CalculateAcolinearities();

        /**
         *  @brief Calculate the acolinearity of a pair of LCIO particles such as the jets from the decay of W/Z bosons
         *
         *  @param reconstructedParticle1 pfo to use in acolinearity calculation 
         *  @param reconstructedParticle2 pfo to use in acolinearity calculation
         *  @param acolinearity to set
         */
        void CalculateAcolinearity(const EVENT::ReconstructedParticle* pReconstructedParticle1, const EVENT::ReconstructedParticle* pReconstructedParticle2, double &acolinearity) const;

        /**
         *  @brief Calculate the acolinearity of a pair of objects defined by particle vectors such as the W/Z boson
         *
         *  @param particleVector1 pfos to use in acolinearity calculation
         *  @param particleVector2 pfos to use in acolinearity calculation
         *  @param acolinearity to set
         */
        void CalculateBosonAcolinearity(ParticleVector particleVector1, ParticleVector particleVector2, double &acolinearity) const;

        /**
         *  @brief Calculate the invariant mass of all particles in jetVector
         *
         *  @param particleVector vector of pointers to lcio particles 
         *  @param invariantMass invariant mass of the system of lcio particles in particleVector
         */
        void FindInvariantMass(ParticleVector &particleVector, double &invariantMass) const;

        /**
         *  @brief Calculate the transverse energy of all particles in m_JetVector
         */
        void CalculateTransverseEnergy();

        /**
         *  @brief Calculate the transverse energy for the object defined by particleVector
         *
         *  @param particleVector vector of Pfos defining object
         *  @param transverseEnergy transverse energy of objects in particleVector to set
         */
        void CalculateTransverseEnergyObject(ParticleVector particleVector, double &transverseEnergy);

        /**
         *  @brief Calculate the transverse momentum of all particles in m_JetVector
         */
        void CalculateTransverseMomentum();

        /**
         *  @brief Calculate the transverse momentum for the object defined by particleVector
         *
         *  @param particleVector vector of Pfos defining object
         *  @param transverseEnergy transverse momentum of objects in particleVector to set
         */
        void CalculateTransverseMomentumObject(ParticleVector particleVector, double &transverseMomentum);

        /**
         *  @brief Calculate the cosine theta of the missing momentum vector using m_JetVector
         */
        void CalculateCosThetaMissingMomentum();

        /**
         *  @brief Find the missing momentum of the event (crossing angle accounted for)
         *
         *  @param pxMis missing momentum in x direction
         *  @param pyMis missing momentum in y direction
         *  @param pzMis missing momentum in z direction
         */
        void FindMissingMomentum(double &pxMis, double &pyMis, double &pzMis) const;

        /**
         *  @brief Calculate the cosine theta of the track assocaited to the particle with the largest energy in the jet vector
         */
        void CalculateCosThetaMostEnergeticTrack();

        /**
         *  @brief Find the tracks assocaited to the particle with the largest energy in the jet vector
         *
         *  @paran mostEnergeticTracksFromPfo vector of tracks associated to highest energy charged particle in the m_JetVector
         */
        void FindMostEnergeticTrack(EVENT::TrackVec &tracksMostEnergeticChargedPfo) const;

        /**
         *  @brief Calculate the recoil mass of the event (magnitude of missing momentum 4 vector, crossing angle accounted for)
         */ 
        void CalculateRecoilMass();

        /**
         *  @brief Find the energy in a cone around the most energetic charged Pfo in m_JetVector
         */
        void CalculateEnergyInConeAroundMostEnergeticPfo();

        /**
         *  @brief Find the most energetic Pfo in m_JetVector
         *
         *  @param pMostEnergeticChargedPfo Most energetic charged Pfo
         */
        void FindMostEnergeticChargedParticle(const EVENT::ReconstructedParticle *&pMostEnergeticChargedPfo) const;

        /**
         *  @brief Find the energy in a cone surrounding a given track
         *
         *  @param particleVector vector of all lcio particles in an event (not quark jets, but their constituents)
         *  @param pMostEnergeticChargedPfo to use as base for cone search
         *  @param energyAroundMostEnergeticChargedPfo energy surrounding Pfo in question
         */
        void FindEnergyAroundPfo(ParticleVector *pParticleVector, const EVENT::ReconstructedParticle *pMostEnergeticChargedPfo, double &energyAroundMostEnergeticChargedPfo) const;

        /**
         *  @brief Find the position of a pfo from the energy weighted cluster position (no pfo position or calo hit position stored to use as better option...)
         *
         *  @param reconstructedParticle pfo to find the position of
         *  @param x position of pfo
         *  @param y position of pfo
         *  @param z position of pfo
         */
        void FindPfoPosition(const EVENT::ReconstructedParticle *pReconstructedParticle, double &x, double &y, double &z) const;

        /**
         *  @brief Check to see if event has features indicating qqqqvv final state
         */
        void IsEventAppropriate();

        /**
         *  @brief Determine whether event is from WW pair
         */
        void IsEventWW();

        /**
         *  @brief Determine whether event is from ZZ pair
         */
        void IsEventZZ();

        /**
         *  @ brief Do some awesome physics with the output
         */
        void DefineVariablesOfInterest();

        /**
         * @brief Calculate the cosine of the polar angle of the object of interest in the reference frame defined by the object of interest and the reference frame objects
         *
         * @param objectOfInterest ParticleVector defining energy 4 vector for direction in question 
         * @param referenceFrameObjects ParticleVector defining energy 4 vector for reference frame for polar angle calculation
         * @param cosThetaStar cosine of the polar angle of the objectOfInterest in a reference frame defined by objectOfInterest and referenceFrameObjects
         */
        void CalculateCosThetaStar(ParticleVector objectOfInterest, ParticleVector referenceFrameObjects, double &cosThetaStar) const;

        /**
         * @brief Calculate the energy 4 vector for a given vector of lcio particles
         *
         * @param jetVector vector of lcio particles
         * @param tLorentzVector energy 4 vector of all partilces in jetVector to set
         */
        void DefineEnergy4Vec(ParticleVector &jetVector, TLorentzVector &tLorentzVector) const;

        ParticleVector        m_JetVector;         ///< Vector of 4 jets from fastjet
        Variables            *m_pVariables;        ///< Variables of interest to set for analysis
        ParticleVector        m_WVector1;          ///< First W candidate
        ParticleVector        m_WVector2;          ///< Second W candidate
        ParticleVector        m_ZVector1;          ///< First Z candidate
        ParticleVector        m_ZVector2;          ///< Second Z candidate
        const double          m_WBosonMass;        ///< W boson mass used for jet pairing
        const double          m_ZBosonMass;        ///< Z boson mass used for jet pairing
        const double          m_CrossingAngle;     ///< Crossing angle for CLIC ILD, radians 
        const double          m_EventMCEnergy;     ///< MC event energy excluding beam effects
        const double          m_ConeAngle;         ///< Cone angle needed for cone energy measurement, degrees
        double                m_y34;               ///< Jet clustering variable
};

#endif // #ifndef JET_ANALYSIS_H
