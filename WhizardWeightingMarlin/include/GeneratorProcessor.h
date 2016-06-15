#ifndef GeneratorProcessor_h
#define GeneratorProcessor_h 1

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

class GeneratorProcessor : public Processor 
{
    public:
    virtual Processor*  newProcessor() { return new GeneratorProcessor; }
    GeneratorProcessor();
  
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
    /*
     * @brief Calculate the invariant mass of all particles in mcParticleVector
     *
     * @param mcParticleVector vector of MCParticle pointers
     * @param wwInvariantMass invariant mass of system
     */
    void CalculateInvariantMass(std::vector<MCParticle*> mcParticleVector, float &wwInvariantMass);

    /*
     * @brief Calculate the cosine of the W boson polar angle in the reference frame of the WW pair
     *
     * @ wPlus energy 4 vector for w+ 
     * @ wMinus energy 4 vector for w-
     * @ cosThetaStar cosine of the W boson polar angle in the reference frame of the WW pair
     */
    void CalculateWBosonPolarAngle(TLorentzVector wPlus, TLorentzVector wMinus, float &cosThetaStar);
 
    std::string         m_CollectionName;                       ///<
    std::string         m_rootFile;                             ///<
    TFile              *m_pTFile;                               ///<
    TTree              *m_pTTree;                               ///<
    TH1F               *m_hWWInvMass;                           ///<
    TH1F               *m_wCosThetaStar;                        ///<
    int                 m_nRun;                                 ///<
    int                 m_nEvent;                               ///<
    CouplingAnalysis   *m_CouplingAnalysis;                     ///<

} ;

#endif
