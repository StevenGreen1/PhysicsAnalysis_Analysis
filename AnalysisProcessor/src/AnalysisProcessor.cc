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
                            "MCParticleCollectionName",
                            "Name of mc particle collections",
                            m_particleCollectionMC,
                            std::string());

    registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
                            "IsolatedPFOsCollectionName",
                            "Name of input isolated lepton PFO collection",
                            m_particleCollectionIsolatedLeptonPFOs,
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
    if (m_nEvent%10 == 0)
    {
        std::cout << "Processing event number : " << m_nEvent << std::endl;
    }


    m_pVariables->Clear();

    const LCParameters &lcParameters(pLCEvent->getCollection(m_particleCollectionPFOs)->parameters());
    m_pVariables->SetLCParameterInfo(lcParameters);

    // PFO Collection
    const EVENT::LCCollection *pLCCollectionPFOs = NULL;

    try
    {
        pLCCollectionPFOs = pLCEvent->getCollection(m_particleCollectionPFOs);
    }
    catch (...)
    {
        streamlog_out(ERROR) << "Could not extract input particle collection: " << m_particleCollectionPFOs << std::endl;
    }

    // Perform PFO Analysis
    if (pLCCollectionPFOs != NULL)
    {
        try
        {
            PfoAnalysis *pfoAnalysis = new PfoAnalysis(pLCCollectionPFOs, m_pVariables);
            delete pfoAnalysis;
        }
        catch (...)
        {
            streamlog_out(ERROR) << "Problem in Pfo Analysis involving collection: " << m_particleCollectionPFOs << std::endl;
        }
    }

    // Isolated Lepton PFO Collection
    const EVENT::LCCollection *pLCCollectionIsolatedLeptonPFOs = NULL;

    try
    {
        pLCCollectionIsolatedLeptonPFOs = pLCEvent->getCollection(m_particleCollectionIsolatedLeptonPFOs);
    }
    catch (...)
    {
        streamlog_out(ERROR) << "Could not extract input particle collection: " << m_particleCollectionIsolatedLeptonPFOs << std::endl;
    }

    // Perform Isolated Lepton PFO Analysis
    if (pLCCollectionIsolatedLeptonPFOs != NULL)
    {
        try
        {
            IsolatedLeptonPfoAnalysis *isolatedLeptonPfoAnalysis = new IsolatedLeptonPfoAnalysis(pLCCollectionIsolatedLeptonPFOs, m_pVariables);
            delete isolatedLeptonPfoAnalysis;
        }
        catch (...)
        {
            streamlog_out(ERROR) << "Problem in isolated lepton pfo analysis involving collection: " << m_particleCollectionIsolatedLeptonPFOs << std::endl;
        }
    }

    // Jet Clustered Collections
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

    // Perform Checks and Jet Analysis
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

            JetAnalysis *pJetAnalysis = new JetAnalysis(pLCCollection4Jet, m_pVariables);
            PartialJetAnalysis *pPartialJetAnalysis6Jet =  new PartialJetAnalysis(pLCCollection6Jet, m_pVariables, 6);
            PartialJetAnalysis *pPartialJetAnalysis2Jet =  new PartialJetAnalysis(pLCCollection2Jet, m_pVariables, 2);
            delete pJetAnalysis, pPartialJetAnalysis6Jet, pPartialJetAnalysis2Jet;
        }
        catch (int error)
        {
            streamlog_out(ERROR) << "Error in jet clusteringi or jet analyses.  " << error << " jets found.  Expecting 6, 4 or 2 jets." << std::endl;
        }
    }

    // MC Collection 
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
    if (pLCMCCollection != NULL)
    {
        try
        {
            MCAnalysis *pMCAnalysis = new MCAnalysis(pLCMCCollection,m_pVariables);
            delete pMCAnalysis;
        }
        catch (...)
        {
            streamlog_out(ERROR) << "Problem in MC analysis involving collection: " << m_particleCollectionMC << std::endl;
        }
    }

    m_nEvent++;
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
    delete m_pVariables;
}

//===========================================================
