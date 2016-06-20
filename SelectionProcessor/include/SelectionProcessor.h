#ifndef SelectionProcessor_h
#define SelectionProcessor_h 1

#include "marlin/Processor.h"
#include "lcio.h"

#include "EVENT/MCParticle.h"

#include "CouplingAnalysis.h"

#include <cmath>
#include <cstdlib>
#include <string>

using namespace lcio;
using namespace marlin;

class TFile;
class TH1F;
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
        /**
         * @brief Reset member variables for next event run
         */
        void Clear();

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
        void DoSomethingWithOutputIfHere();

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
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet
         * @paran mostEnergeticTracksFromPFO vector of tracks associated to highest energy charged particle in the jet vector
         */
        void FindMostEnergeticTrack(JetVector &jetVector, EVENT::TrackVec &mostEnergeticTracksFromPFO) const;

        /**
         * @brief Find the recoil mass of the event (magnitude of missing momentum 4 vector)
         *
         * @param jetVector defining the visible momentum for the event 
         * @param recoilMass recoil mass of the system
         */
        void FindRecoilMass(JetVector &jetVector, float &recoilMass) const;

        /**
         * @brief Find the energy in a cone around the track(s) from the most energetic PFOs
         *
         * @param jetVector vector of pointers to lcio particles corresponding to quark jets from fastjet
         * @param mostEnergeticTracksFromPFO track(s) from the most energetic PFO in the event
         * @param energyAroundTrack energy in cone surrounding most energetic track
         */
        void FindEnergyInConeAroundMostEnergeticTrack(JetVector &jetVector, EVENT::TrackVec &mostEnergeticTracksFromPFO, float &energyAroundTrack) const;

        /**
         * @brief Find the energy in a cone surrounding a given track
         *
         * @param particleVector vector of all lcio particles in an event
         * @param track to use as base for cone search
         * @param energyAroundTrack energy surrounding track in question
         */
        void FindEnergyAroundTrack(JetVector &particleVector, EVENT::Track &track, float &energyAroundTrack) const;


        /**
         * @brief Find the jet clustering variable y34
         *
         * @param pLCCollection Collection of PFOs to read in
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
        void JetVariables(const EVENT::ReconstructedParticle *pJet, float energy, int numberOfParticles, int numberOfChargedParticles) const


    /*
     * @brief Calculate the cosine of the W boson polar angle in the reference frame of the WW pair
     *
     * @ wPlus energy 4 vector for w+ 
     * @ wMinus energy 4 vector for w-
     * @ cosThetaStar cosine of the W boson polar angle in the reference frame of the WW pair
     */
    void CalculateWBosonPolarAngle(TLorentzVector wPlus, TLorentzVector wMinus, float &cosThetaStar);

    /**
     * @brief Set the quark mc particles in ww vector boson scattering
     *
     * @param pMCParticle target quark
     * @param u up quark type in process
     * @param d down quark type in process
     * @param au anti-up quark type in process
     * @param ad anti-down quark type in process
     */
    void SetQuarks(MCParticle *pMCParticle, MCParticle *&u, MCParticle *&d, MCParticle *&au, MCParticle *&ad) const;

    typedef std::vector<const EVENT::ReconstructedParticle*> JetVector;

    JetVector           m_JetVector;                            ///< 
    JetVector           m_WPlusVector;                          ///< 
    JetVector           m_WMinusVector;                         ///< 
    JetVector           m_FirstZVector;                         ///< 
    JetVector           m_SecondZVector;                        ///< 
    bool                m_IsEventWW;                            ///<
    bool                m_IsEventZZ;                            ///<

    std::string         m_CollectionName;                       ///< PFO collection name
    std::string         m_rootFile;                             ///< Root file output namne
    float               m_EventMCEnergy                         ///< MC event energy excluding beam effects
    float               m_ConeAngle;                            ///< Cone angle needed for cone energy measurement 

    TFile              *m_pTFile;                               ///<
    TTree              *m_pTTree;                               ///<
    TH1F               *m_hWWInvMass;                           ///<
    TH1F               *m_wCosThetaStar;                        ///<
    TH1F               *m_wCosThetaStar2;                       ///<
    TH1F               *m_wCosThetaStar3;                       ///<
    int                 m_nRun;                                 ///<
    int                 m_nEvent;                               ///<
    CouplingAnalysis   *m_CouplingAnalysis;                     ///<

} ;

#endif
