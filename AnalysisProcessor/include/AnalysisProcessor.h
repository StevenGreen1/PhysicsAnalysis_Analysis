/**
 *  @file   AnalysisProcessor/include/AnalysisProcessor.h
 * 
 *  @brief  Header file for the analysis processor class 
 * 
 *  $Log: $
 */

#ifndef ANALYSIS_PROCESSOR_H
#define ANALYSIS_PROCESSOR_H 1

#include <iostream>
//#include <cmath>
//#include <cstdlib>
#include <string>

#include "EVENT/LCCollection.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"

//#include "lcio.h"

#include "marlin/Processor.h"
#include "marlin/VerbosityLevels.h"

#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TVector3.h"

#include "IsolatedLeptonPfoAnalysis.h"
#include "JetAnalysis.h"
#include "MCAnalysis.h"
#include "PartialJetAnalysis.h"
#include "RawPfoAnalysis.h"
#include "Variables.h"

//#include "UTIL/PIDHandler.h"

using namespace lcio;
using namespace marlin;

class TFile;
class TTree;

class AnalysisProcessor : public Processor 
{
    public:
        virtual Processor*  newProcessor() { return new AnalysisProcessor; }
        AnalysisProcessor();
  
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
        // Inputs
        double              m_eventEnergyMC;                           ///< MC Event Energy
        std::string         m_rootFile;                                ///< Root file output namne
        std::string         m_particleCollectionPFOs;                  ///< Raw PFO collection name
        std::string         m_particleCollectionMC;                    ///< MC particle collection
        std::string         m_particleCollectionIsolatedLeptonPFOs;    ///< Isolated lepton particle collection
        std::string         m_particleCollection6Jet;                  ///< Jet collection name when clustering into 6 jets 
        std::string         m_particleCollection4Jet;                  ///< Jet collection name when clustering into 4 jets
        std::string         m_particleCollection2Jet;                  ///< Jet collection name when clustering into 2 jets
        std::string         m_recoMCTruthLinkCollection;               ///< Reco to MC truth link collection name

        // Outputs
        Variables          *m_pVariables;                              ///< Variables class containing all variables of interest
        TFile              *m_pTFile;                                  ///< Root file for output
        TTree              *m_pTTree;                                  ///< Root tree for output 
        int                 m_nRun;                                    ///< Run number
        int                 m_nEvent;                                  ///< Event number
};

#endif // #ifndef ANALYSIS_PROCESSOR_H
