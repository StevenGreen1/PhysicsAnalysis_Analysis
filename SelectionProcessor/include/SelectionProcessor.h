/**
 *  @file   SelectionProcessor/include/SelectionProcessor.h
 * 
 *  @brief  Header file for the selection processor class 
 * 
 *  $Log: $
 */

#ifndef SELECTION_PROCESSOR_H
#define SELECTION_PROCESSOR_H 1

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

#include "JetAnalysis.h"
#include "Variables.h"

//#include "UTIL/PIDHandler.h"

using namespace lcio;
using namespace marlin;

class TFile;
class TTree;

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
        // Inputs
        std::string         m_jetParticleCollection;   ///< Pfo collection name
        std::string         m_mcParticleCollection;    ///< MC particle collectioni
        std::string         m_rootFile;                ///< Root file output namne

        // Outputs
        Variables          *m_pVariables;              ///< Variables class containing all variables of interest
        TFile              *m_pTFile;                  ///< Root file for output
        TTree              *m_pTTree;                  ///< Root tree for output 
        int                 m_nRun;                    ///< Run number
        int                 m_nEvent;                  ///< Event number
};

#endif // #ifndef SELECTION_PROCESSOR_H
