#ifndef JETSTOPFOS_h
#define JETSTOPFOS_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>

using namespace lcio;
using namespace marlin;

class JetsToPFOs : public Processor 
{
    public:
        virtual Processor*  newProcessor() { return new JetsToPFOs; }
   
        /**
         *  @brief Constructor
         */
        JetsToPFOs();
  
        /**
         * @brief Called at the begin of the job before anything is read.
         *        Use to initialize the processor, e.g. book histograms.
         */
        virtual void init() ;
  
        /** 
         *  @brief Called for every run.
         */
        virtual void processRunHeader( LCRunHeader* run ) ;
  
        /**
         *  @brief Called for every event - the working horse.
         */
        virtual void processEvent( LCEvent * evt ) ; 
  
        /**
         *  @brief Called for every event - the working horse.
         */
        virtual void check( LCEvent * evt ) ; 
  
        /**
         *  @brief Called after data processing for clean up.
         */
         virtual void end() ;
    
    private:
        std::vector<std::string> m_inputJetCollectionNames;    ///< Input jet collection names
        std::vector<std::string> m_outputPFOCollectionNames;   ///< Output PFO collection names
        int m_nRun;                                            ///< Run number
        int m_nEvt;                                            ///< Event number
};

#endif
