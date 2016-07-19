#ifndef SelectionProcessor_h
#define SelectionProcessor_h 1

#include "marlin/Processor.h"
#include "lcio.h"

#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"

#include "UTIL/PIDHandler.h"

#include <cmath>
#include <cstdlib>
#include <string>

using namespace lcio;
using namespace marlin;

class TFile;
class TTree;
class TLorentzVector;
class TVector3;

class SelectionProcessor : public Processor 
{
    public:
        virtual Processor*  newProcessor() { return new SelectionProcessor; }
        SelectionProcessor();
  
        /* 
         * Called at the begin of the job before anything is read.
         * Use to initialize the processor, e.g. book histograms.
         */
        virtual void init();
  
        /*
         * Called for every run.
         */
        virtual void processRunHeader( LCRunHeader *run );
  
        /*
         * Called for every event - the working horse.
         */
        virtual void processEvent( LCEvent *evt ); 
  
        virtual void check( LCEvent *evt ); 
  
        /*
         * Called after data processing for clean up.
         */
        virtual void end();
    
    private:
        typedef std::vector<const EVENT::ReconstructedParticle*> JetVector;
        typedef std::vector<float> FloatVector;
        typedef std::vector<int> IntVector;

        /**
         * @brief Reset member variables for next event run
         */
        void Clear();

        /**
         * @brief Check to see if event has features indicating qqqqvv final state
         */
        void IsEventAppropriate();

        /**
         * @brief Determine whether event is from WW pair
         */
        void IsEventWW();

        /**
         * @brief Determine whether event is from ZZ pair
         */
        void IsEventZZ();

        /**
         * @ brief Do some awesome physics with the output
         */
        void DefineVariablesOfInterest();

        /**
         * @brief Calculate the invariant mass of all particles in jetVector
         *
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet 
         * @param invariantMass invariant mass of the lcio particles in jetVector
         */
        void CalculateInvariantMass(JetVector &jetVector, float &invariantMass) const;

        /**
         * @brief Calculate the transverse momentum of all particles in jetVector
         *
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet
         * @param transverseMomentum transverse momentum of the lcio particles in jetVector
         */
        void CalculateTransverseMomentum(JetVector &jetVector, float &transverseMomentum) const;

        /**
         * @brief Calculate the transverse energy of all particles in jetVector
         *
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet
         * @param transverseEnergy transverse momentum of the lcio particles in jetVector
         */
        void CalculateTransverseEnergy(JetVector &jetVector, float &transversEnergy) const;

        /**
         * @brief Calculate the cosine theta of the missing momentum vector
         *
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet
         * @param cosTheta cosine theta of the missing momentum vector
         */
        void CalculateCosThetaMissingMomentum(JetVector &jetVector, float &cosTheta) const;

        /**
         * @brief Calcualte the missing momentum of the event (ASSUMING NO CROSSING ANGLE - TODO : Check this)
         *
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet
         * @param pxMis missing momentum in x direction
         * @param pyMis missing momentum in y direction
         * @param pzMis missing momentum in z direction
         */
        void CalculateMissingMomentum(JetVector &jetVector, float &pxMis, float &pyMis, float &pzMis) const;

        /**
         * @brief Calculate the cosine theta of the track assocaited to the particle with the largest energy in the jet vector
         *
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet
         * @param cosTheta cosine theta of track assocaited to the particle with the largest energy
         */
        void FindCosThetaMostEnergeticTrack(JetVector &jetVector, float &cosTheta) const;

        /**
         * @brief Find the tracks assocaited to the particle with the largest energy in the jet vector 
         *
         * @param jetVector vector of pointers to lcio particles (coming from quark jets from fastjet)
         * @paran mostEnergeticTracksFromPfo vector of tracks associated to highest energy charged particle in the jet vector
         */
        void FindMostEnergeticTrack(JetVector &jetVector, EVENT::TrackVec &mostEnergeticTracksFromPfo) const;

        /**
         * @brief Find the most energetic Pfo in the jet vector
         *
         * @param jetVector vector of pointers to lcio particles (coming from quark jets from fastjet)
         * @param pMostEnergeticChargedPfo Most energetic charged Pfo
         */
        void FindMostEnergeticChargedParticle(JetVector &jetVector, const EVENT::ReconstructedParticle *&pMostEnergeticChargedPfo) const;

        /**
         * @brief Find the recoil mass of the event (magnitude of missing momentum 4 vector)
         *
         * @param jetVector defining the visible momentum for the event 
         * @param recoilMass recoil mass of the system
         */
        void FindRecoilMass(JetVector &jetVector, float &recoilMass) const;

        /**
         * @brief Find the energy in a cone around the most energetic charged Pfo 
         *
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet
         * @param energyAroundMostEnergeticChargedPfo energy in a cone surrounding the most energetic Pfo in the event
         */
        void FindEnergyInConeAroundMostEnergeticPfo(JetVector &jetVector, float &energyAroundMostEnergeticChargedPfo) const;

        /**
         * @brief Find the energy in a cone surrounding a given track
         *
         * @param particleVector vector of all lcio particles in an event (not quark jets, but their constituents)
         * @param pMostEnergeticChargedPfo to use as base for cone search
         * @param energyAroundMostEnergeticChargedPfo energy surrounding Pfo in question
         */
        void FindEnergyAroundPfo(JetVector *pParticleVector, const EVENT::ReconstructedParticle *pMostEnergeticChargedPfo, float &energyAroundMostEnergeticChargedPfo) const;

        /**
         * @brief Find the position of a pfo from the energy weighted cluster position (no pfo position or calo hit position stored to use as better option...)
         *
         * @param reconstructedParticle pfo to find the position of
         * @param x position of particle
         * @param y position of particle
         * @param z position of particle
         */
        void GetPfoPosition(const EVENT::ReconstructedParticle *pReconstructedParticle, float &x, float &y, float &z) const;

        /**
         * @brief Find the jet clustering variable y34
         *
         * @param pLCCollection Collection of Pfos to read in
         * @param y34 jet clustering variable of choice
         */
        void FindJetClusteringVariableY34(const LCCollection *pLCCollection, float &y34) const;

        /**
         * @brief Set the basic jet variables
         *
         * @param energy in jet
         * @param numberOfParticles in jet
         * @param numberOfChargedParticles
         */
        void JetVariables(const EVENT::ReconstructedParticle *pJet, float &energy, int &numberOfParticles, int &numberOfChargedParticles) const;

        /**
         * @brief Find best pairing of lcio particles to form either two W bosons or two Z bosons
         *
         * @param wCandidates candidate particles to be used for forming bosons
         * @param type wither ww or zz to pair up W or Z bosons
         */
        void JetPairing(JetVector &wCandidates, std::string type);

        /**
         * @brief Calculate the cosine of the polar angle of the object of interest in the reference frame defined by the object of interest and the reference frame objects
         *
         * @param objectOfInterest energy 4 vector defining polar angle in question
         * @param referenceFrameObjects energy 4 vector to define reference frame for polar angle
         * @param cosThetaStar cosine of the polar angle of the objectOfInterest in a reference frame defined by objectOfInterest and referenceFrameObjects
         */
        void CalculateCosThetaStar(JetVector objectOfInterest, JetVector referenceFrameObjects, float &cosThetaStar) const;

        /**
         * @brief Calculate the energy 4 vector for a given vector of lcio particles
         *
         * @param jetVector vector of lcio particles
         * @param pTLorentzVector energy 4 vector to set
         */
        void DefineEnergy4Vec(JetVector &jetVector, TLorentzVector &tLorentzVector) const;

        // Tools
        JetVector           m_JetVector;                            ///< Vector of all LCIO reconstructed particles in event (4 as from fastjet)
        JetVector           m_WVector1;                             ///< First possible w candidate (2 particles from m_JetVector)
        JetVector           m_WVector2;                             ///< Second possible w candidate (2 particles from m_JetVector)
        JetVector           m_ZVector1;                             ///< First possible z candidate (2 particles from m_JetVector)
        JetVector           m_ZVector2;                             ///< Second possible z candidate (2 particles from m_JetVector)

        // Variables of interest
        bool                m_AppropriateEvent;                     ///< Check to see if events appears to have qqqqvv final state
        bool                m_IsEventWW;                            ///< If event appropriate see if qqqq in qqqqvv from ww
        bool                m_IsEventZZ;                            ///< If event appropriate see if qqqq in qqqqvv from zz
        float               m_InvMassWVector1;                      ///< Invariant mass of W candidate jets 1
        float               m_InvMassWVector2;                      ///< Invariant mass of W candidate jets 2
        float               m_InvMassZVector1;                      ///< Invariant mass of Z candidate jets 1
        float               m_InvMassZVector2;                      ///< Invariant mass of Z candidate jets 2
        float               m_TransverseMomentum;                   ///< Transverse momentum
        float               m_TransverseEnergy;                     ///< Transverse energy
        float               m_CosThetaMissing;                      ///< Cosine theta of missing momentum
        float               m_CosThetaMostEnergeticTrack;           ///< Cosine theta of the most energetic track
        float               m_RecoilMass;                           ///< Recoil mass
        float               m_EnergyAroundMostEnergeticPfo;         ///< Energy in a cone surround most energetic pfo
        float               m_y34;                                  ///< Jet clustering parameter
        FloatVector         m_EnergyJets;                           ///< Vector of energies of the jets
        IntVector           m_NParticlesJets;                       ///< Vector of number of particles in the jets
        IntVector           m_NChargedParticlesJets;                ///< Vector of number of charged particles in the jets 

        // Variables Used in Anomalous Coupling Study
        float               m_InvariantMassSystem;                  ///< Invariant mass of the full system
        FloatVector         m_CosThetaStarWBosons;                  ///< Cosine of the polar angle of the W bosons in the reference frame of the WW boson pairs
        FloatVector         m_CosThetaStarZBosons;                  ///< Cosine of the polar angle of the Z bosons in the reference frame of the ZZ boson pairs
        FloatVector         m_CosThetaStarWJets;                    ///< Cosine of the polar angle of the q jets in the reference frome of the W bosons
        FloatVector         m_CosThetaStarZJets;                    ///< Cosine of the polar angle of the q jets in the reference frome of the Z bosons

        // Reference variables
        float               m_WBosonMass;                           ///< W boson mass from pdg
        float               m_ZBosonMass;                           ///< Z boson mass from pdg

        // Inputs
        std::string         m_jetCollectionName;                    ///< Pfo collection name
        std::string         m_mcParticleCollection;                 ///< MC particle collectioni
        std::string         m_rootFile;                             ///< Root file output namne
        float               m_EventMCEnergy;                        ///< MC event energy excluding beam effects
        float               m_ConeAngle;                            ///< Cone angle needed for cone energy measurement 

        TFile              *m_pTFile;                               ///< Root file for output
        TTree              *m_pTTree;                               ///< Root tree for output 
        int                 m_nRun;                                 ///< Run number
        int                 m_nEvent;                               ///< Event number
} ;

#endif
