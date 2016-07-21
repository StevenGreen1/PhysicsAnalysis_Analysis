/**
 *  @file   SelectionProcessor/src/SelectionProcessor.cc
 * 
 *  @brief  Implementation of the selection processor class
 * 
 *  $Log: $
 */

#include "SelectionProcessor.h"

using namespace lcio ;
using namespace marlin ;

SelectionProcessor selectionProcessor;

//===========================================================

SelectionProcessor::SelectionProcessor() : Processor("SelectionProcessor") 
{
    _description = "Selection processor for vector boson scattering physics analysis";

    registerProcessorParameter("RootFile",
                            "Name of the output root file",
                            m_rootFile,
                            std::string("SelectionProcessor.root"));

    registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
                            "CollectionName",
                            "Name of input jet collection",
                            m_jetParticleCollection,
                            std::string());

    registerInputCollection(LCIO::MCPARTICLE,
                            "MCParticleCollection",
                            "Name of mc particle collections",
                            m_mcParticleCollection,
                            std::string());
}

//===========================================================

void SelectionProcessor::init() 
{ 
    m_pVariables = new Variables();

    m_nRun = 0;
    m_nEvent = 0;

    m_pTFile = new TFile(m_rootFile.c_str(), "recreate");

    m_pTTree = new TTree("SelectionProcessorTree", "SelectionProcessorTree");
    m_pTTree->SetDirectory(m_pTFile);
    m_pTTree->Branch("run", &m_nRun, "run/I");
    m_pTTree->Branch("event", &m_nEvent, "event/I");

    m_pVariables->SetBranches(m_pTTree);
}

//===========================================================

void SelectionProcessor::processRunHeader(LCRunHeader* run) 
{ 
    m_nRun++;
} 

//===========================================================

void SelectionProcessor::processEvent(LCEvent * pLCEvent) 
{ 
    m_pVariables->Clear();

    // this gets called for every event 
    // usually the working horse ...

    if (m_nEvent%10 == 0)
    {
        std::cout << "Processing event number : " << m_nEvent << std::endl;
    }

    // Extract Jet Collection
    const EVENT::LCCollection *pLCCollection = NULL;

    try
    {
        pLCCollection = pLCEvent->getCollection(m_jetParticleCollection);
    }
    catch (...)
    {
        streamlog_out(ERROR) << "Could not extract input particle collection: " << m_jetParticleCollection << std::endl;
    }

    // Check clustering has produced 4 jets
    if (pLCCollection != NULL)
    {
        try
        {
            if (pLCCollection->getNumberOfElements() != 4)
                throw pLCCollection->getNumberOfElements();
        }
        catch (int error)
        {
            std::cout << "Error in jet clustering.  " << error << " jets found.  Expecting 4 jets." << std::endl;
        }
    }

    // Perform Jet Analysis
    JetAnalysis *pJetAnalysis = new JetAnalysis(pLCCollection,m_pVariables);


    // Extract MC Information

    const EVENT::LCCollection *pLCMCCollection = NULL;

    try
    {
        pLCMCCollection = pLCEvent->getCollection(m_mcParticleCollection);
    }
    catch (...)
    {
        streamlog_out(ERROR) << "Could not extract input particle collection: " << m_mcParticleCollection << std::endl;
    }

    // Perform MC Analysis
    MCAnalysis *pMCAnalysis = new MCAnalysis(pLCMCCollection,m_pVariables);

    m_nEvent++;

    m_pTTree->Fill();
}

//===========================================================

void SelectionProcessor::check(LCEvent * pLCEvent)
{
}

//===========================================================

void SelectionProcessor::end()
{
    m_pTFile->cd();
    m_pTTree->Write();

    m_pTFile->Close();
    delete m_pTFile;
}

//===========================================================
