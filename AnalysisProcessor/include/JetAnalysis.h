/**
 *  @file   SelectionProcessor/include/JetAnalysis.h
 *
 *  @brief  Header file for the jet analysis class.
 *
 *  $Log: $
 */

#ifndef JET_ANALYSIS_H
#define JET_ANALYSIS_H 1

#include <cmath>
#include <map>
#include <string>
#include <vector>

#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/MCParticle.h"

#include "UTIL/LCRelationNavigator.h"
#include "UTIL/PIDHandler.h"

#include "TLorentzVector.h"

#include "Variables.h"

//namespace EVENT { class LCEvent; class MCParticle; class ReconstructedParticle; class ParticleID;}
//namespace UTIL {class PIDHandler;}

class JetAnalysis 
{
    typedef std::vector<const EVENT::ReconstructedParticle*> ParticleVector;
    typedef std::vector<const EVENT::MCParticle*> MCParticleVector;
    typedef std::map<const EVENT::ReconstructedParticle*, double> ParticleToFloatMap;
    typedef std::vector<double> DoubleVector;
    typedef std::map<const EVENT::MCParticle*, MCParticleVector*> MCParticleToMCParticleMap;
    typedef std::map<const EVENT::MCParticle*, float> MCParticleToFloatMap;
    typedef std::map<const EVENT::ReconstructedParticle*, std::map<const EVENT::MCParticle*, float> > ParticleToMCParticleToFloatMap;
    typedef std::map<const EVENT::ReconstructedParticle*, const EVENT::MCParticle*> ParticleToMCParticleMap;
//    typedef std::vector<int> IntVector;

    public:
        /**
         *  @brief Constructor
         *
         *  @param pLCCollection Jet collection
         *  @param variable class containing useful parameters
         *  @param pRecoMCTruthLinkCollection pointer to mc reco truth linker
         */
        JetAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables, const EVENT::LCCollection *pRecoMCTruthLinkCollection);

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
         *  @brief Cheat the jet pairing 
         */
        void CheatedJetPairing();

        /**
         *  @brief Pair up jets to MC quarks and populate particle to MC particle to weight map
         */
        void SetJetToMCRelations();

        /**
         *  @brief Logic to decide best jet pairing based on MC weight information
         */
        void SetBestCheatedPairing();

        /**
         *  @brief Pair up the jet to the two quarks contributing the largest weight
         *
         *  @param jets vector of jets to pair
         *  @param bestQuarks1 vector of highest contributing weight quark to jet
         *  @param bestQuarks2 vector of second highest contributing weight quark to jet
         */
        void SetJetBestQuarks(ParticleVector &jets, MCParticleVector &bestQuarks1, MCParticleVector &bestQuarks2) const;

        /**
         *  @brief Calculate the energy of the W/Z bosons
         */
        void CalculateBosonEnergies();

        /**
         *  @brief Calculate the number of PFOs in W/Z bosons
         */
        void CalculateBosonNPFOs();

        /**
         *  @brief Calculate number of Pfos in a particleVector of jets e.g. boson with two jets
         *
         *  @param nPfos number of Pfos to set
         */
        void CalculateNumberOfPfos(ParticleVector particleVector, int &nPfos);

        /**
         *  @brief Calculate flavour tagging variables for bosons
         */
        void CalculateFlavourTaggingInformation();

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
         *  @brief Calculate the invariant mass of all mc particles in mcParticleVector
         *
         *  @param mcParticleVector vector of pointers to lcio mc particles
         *  @param invariantMass invariant mass of the system of lcio mc particles in mcParticleVector
         */
        void FindMCInvariantMass(MCParticleVector &mcParticleVector, double &invariantMass) const;

        /**
         *  @brief Calculate the transverse energy of all particles in m_jets
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
         *  @brief Calculate the transverse momentum of all particles in m_jets
         */
        void CalculateTransverseMomentum();

        /**
         *  @brief Calculate the transverse momentum for the object defined by particleVector
         *
         *  @param particleVector vector of Pfos defining object
         *  @param transverseMomentum transverse momentum of objects in particleVector to set
         */
        void CalculateTransverseMomentumObject(ParticleVector particleVector, double &transverseMomentum);

        /**
         *  @brief Calculate the momenta of the reconstructed bosons
         */
        void CalculateBosonMomenta();

        /**
         *  @brief Calculate the momentum for the object defined by particleVector
         *
         *  @param particleVector vector of Pfos defining object
         *  @param momentum momentum of objects in particleVector to set
         */
        void CalculateMomentumObject(ParticleVector particleVector, double &momentum);

        /**
         *  @brief Calculate the costheta of the reconstructed bosons
         */
        void CalculateBosonCosTheta();

        /**
         *  @brief Calculate the cos theta for the object defined by particleVector
         *
         *  @param particleVector vector of Pfos defining object
         *  @param cosTheta cos theta of objects in particleVector to set
         */
        void CalculateCosThetaObject(ParticleVector particleVector, double &cosTheta);

        /**
         *  @brief Calculate the cosine theta of the missing momentum vector using m_jets
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
         *  @paran mostEnergeticTracksFromPfo vector of tracks associated to highest energy charged particle in the m_jets
         */
        void FindMostEnergeticTrack(EVENT::TrackVec &tracksMostEnergeticChargedPfo) const;

        /**
         *  @brief Calculate the recoil mass of the event (magnitude of missing momentum 4 vector, crossing angle accounted for)
         */ 
        void CalculateRecoilMass();

        /**
         *  @brief Find the energy in a cone around the most energetic charged Pfo in m_jets
         */
        void CalculateEnergyInConeAroundMostEnergeticPfo();

        /**
         *  @brief Find the most energetic Pfo in m_jets
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
         * @param tLorentzBoson energy 4 vector of all partilces in jetVector to set
         */
        void DefineEnergy4Vec(ParticleVector &jetVector, TLorentzVector &tLorentzBoson) const;

        ParticleVector                         m_jets;                   ///< Vector of 4 jets from fastjet
        Variables                             *m_pVariables;             ///< Variables of interest to set for analysis
        UTIL::LCRelationNavigator             *m_pRecoMCNavigator;       ///< The reco to mc linker
        ParticleVector                         m_wBoson1;                ///< First W candidate
        ParticleVector                         m_wBoson2;                ///< Second W candidate
        ParticleVector                         m_zBoson1;                ///< First Z candidate
        ParticleVector                         m_zBoson2;                ///< Second Z candidate
        ParticleVector                         m_synBoson1;              ///< Closest mass pairing boson candidate 1
        ParticleVector                         m_synBoson2;              ///< Closest mass pairing boson candidate 2
        ParticleToFloatMap                     m_particleToBTag;         ///< Jet to B tag value
        ParticleToFloatMap                     m_particleToCTag;         ///< Jet to C tag value
        ParticleToMCParticleToFloatMap         m_jetToQuarkToWeightMap;  ///< Map of jet to quark parent to weight 
        const double                           m_wBosonMass;             ///< W boson mass used for jet pairing
        const double                           m_zBosonMass;             ///< Z boson mass used for jet pairing
        const double                           m_crossingAngle;          ///< Crossing angle for CLIC ILD, radians 
        const double                           m_eventEnergyMC;          ///< MC event energy excluding beam effects
        const double                           m_coneAngle;              ///< Cone angle needed for cone energy measurement, degrees
        double                                 m_y34;                    ///< Jet clustering variable
};

#endif // #ifndef JET_ANALYSIS_H
