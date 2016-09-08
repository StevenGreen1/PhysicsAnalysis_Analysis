/**
 *  @file   AnalysisProcessor/src/AnalysisProcessor.cc
 * 
 *  @brief  Implementation of the analysis processor class
 * 
 *  $Log: $
 */

#include "AnalysisProcessor.h"

using namespace lcio ;
using namespace marlin ;

AnalysisProcessor analysisProcessor;

//===========================================================

AnalysisProcessor::AnalysisProcessor() : Processor("AnalysisProcessor") 
{
    _description = "Analysis processor for vector boson scattering physics analysis";

    registerProcessorParameter("RootFile",
                            "Name of the output root file",
                            m_rootFile,
                            std::string("AnalysisProcessor.root"));

    registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
                            "PFOCollectionName",
                            "Name of input PFO collection",
                            m_particleCollectionPFOs,
                            std::string());

    registerInputCollection(LCIO::MCPARTICLE,
                            "MCParticleCollection",
                            "Name of mc particle collections",
                            m_particleCollectionMC,
                            std::string());

    registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
                            "6JetCollectionName",
                            "Name of input 6 jet collection",
                            m_particleCollection6Jet,
                            std::string());

    registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
                            "4JetCollectionName",
                            "Name of input 4 jet collection",
                            m_particleCollection4Jet,
                            std::string());

    registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
                            "2JetCollectionName",
                            "Name of input 2 jet collection",
                            m_particleCollection2Jet,
                            std::string());
}

//===========================================================

void AnalysisProcessor::init() 
{ 
    m_pVariables = new Variables();

    m_nRun = 0;
    m_nEvent = 0;

    m_pTFile = new TFile(m_rootFile.c_str(), "recreate");

    m_pTTree = new TTree("AnalysisProcessorTree", "AnalysisProcessorTree");
    m_pTTree->SetDirectory(m_pTFile);
    m_pTTree->Branch("run", &m_nRun, "run/I");
    m_pTTree->Branch("event", &m_nEvent, "event/I");

    m_pVariables->SetBranches(m_pTTree);
}

//===========================================================

void AnalysisProcessor::processRunHeader(LCRunHeader* run) 
{ 
    m_nRun++;
} 

//===========================================================

void AnalysisProcessor::processEvent(LCEvent *pLCEvent) 
{ 
    m_pVariables->Clear();

    const LCParameters &lcParameters(pLCEvent->getCollection(m_particleCollectionPFOs)->parameters());
    m_pVariables->SetLCParameterInfo(lcParameters);

    if (m_nEvent%10 == 0)
    {
        std::cout << "Processing event number : " << m_nEvent << std::endl;
    }

    const EVENT::LCCollection *pLCCollection6Jet = NULL;
    const EVENT::LCCollection *pLCCollection4Jet = NULL;
    const EVENT::LCCollection *pLCCollection2Jet = NULL;

    try
    {
        pLCCollection6Jet = pLCEvent->getCollection(m_particleCollection6Jet);
        pLCCollection4Jet = pLCEvent->getCollection(m_particleCollection4Jet);
        pLCCollection2Jet = pLCEvent->getCollection(m_particleCollection2Jet);
    }
    catch (...)
    {
        streamlog_out(ERROR) << "Could not extract input particle collection: " << m_particleCollection6Jet << ", " << m_particleCollection4Jet << " or " << m_particleCollection2Jet << std::endl;
    }

    // Check clustering has produced correct number of jets
    if (pLCCollection6Jet != NULL or pLCCollection4Jet != NULL or pLCCollection2Jet != NULL)
    {
        try
        {
            if (pLCCollection6Jet->getNumberOfElements() != 6)
                throw pLCCollection6Jet->getNumberOfElements();
            if (pLCCollection4Jet->getNumberOfElements() != 4)
                throw pLCCollection4Jet->getNumberOfElements();
            if (pLCCollection2Jet->getNumberOfElements() != 2)
                throw pLCCollection2Jet->getNumberOfElements();
        }
        catch (int error)
        {
            streamlog_out(ERROR) << "Error in jet clustering.  " << error << " jets found.  Expecting 6, 4 or 2 jets." << std::endl;
        }
    }

    // Perform Full Jet Analysis
    JetAnalysis *pJetAnalysis = new JetAnalysis(pLCCollection4Jet, m_pVariables);

    // Perform Partial Jet Analysis on Differently Clustered Jets
    PartialJetAnalysis *pPartialJetAnalysis6Jet =  new PartialJetAnalysis(pLCCollection6Jet, m_pVariables, 6);
    PartialJetAnalysis *pPartialJetAnalysis2Jet =  new PartialJetAnalysis(pLCCollection2Jet, m_pVariables, 2);

    // Extract MC Information
    const EVENT::LCCollection *pLCMCCollection = NULL;

    try
    {
        pLCMCCollection = pLCEvent->getCollection(m_particleCollectionMC);
    }
    catch (...)
    {
        streamlog_out(ERROR) << "Could not extract input particle collection: " << m_particleCollectionMC << std::endl;
    }

    // Perform MC Analysis
    MCAnalysis *pMCAnalysis = new MCAnalysis(pLCMCCollection,m_pVariables);

    m_nEvent++;
//    m_pVariables->Print();
    m_pTTree->Fill();
}

//===========================================================

void AnalysisProcessor::check(LCEvent * pLCEvent)
{
}

//===========================================================

void AnalysisProcessor::end()
{
    m_pTFile->cd();
    m_pTTree->Write();

    m_pTFile->Close();
    delete m_pTFile;
}

//===========================================================
