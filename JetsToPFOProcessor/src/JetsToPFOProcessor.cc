#include "JetsToPFOProcessor.h"
#include <iostream>

#include <EVENT/LCCollection.h>
#include <EVENT/ReconstructedParticle.h>

#include <IMPL/LCCollectionVec.h>

#include "marlin/VerbosityLevels.h"

using namespace lcio;
using namespace marlin;

JetsToPFOs jetsToPFOs ;

//----------------------------------------------------------------------------

JetsToPFOs::JetsToPFOs() : Processor("JetsToPFOs") 
{
    // modify processor description
    _description = "JetsToPFOs reads in the LCIO FastJetCollection and outputs a collection of constituent PFOs" ;

    StringVec inputJetCollectionNames;
    registerOptionalParameter("JetInputCollectionNames",
                             "Name of input jet collections",
                             m_inputJetCollectionNames,
                             inputJetCollectionNames);

    StringVec outputPFOCollectionNames;
    registerOptionalParameter("PFOCollectionNames",
                             "Name of output recoconstructed particles collections",
                             m_outputPFOCollectionNames,
                             outputPFOCollectionNames);
}

//----------------------------------------------------------------------------

void JetsToPFOs::init() 
{ 
    streamlog_out(DEBUG) << "   init called  " << std::endl ;

    m_nRun = 0;
    m_nEvt = 0;
}

//----------------------------------------------------------------------------

void JetsToPFOs::processRunHeader( LCRunHeader* run) { 

    m_nRun++ ;
} 

//----------------------------------------------------------------------------

void JetsToPFOs::processEvent( LCEvent *pLCEvent ) 
{ 
    if (m_nEvt % 500 == 0)
    {
        streamlog_out(MESSAGE) << "Run " << m_nRun << ", JetsToPFOs::processEvent: " << m_nEvt << std::endl;
    }

    if (m_inputJetCollectionNames.size() != m_outputPFOCollectionNames.size())
    {
        streamlog_out(MESSAGE) << "JetsToPFOs::processEvent - Fatal Error: The number of input and output collections should be the same." << std::endl;
        return;
    }

    for(int i = 0; i < m_inputJetCollectionNames.size(); i++)
    {
        const std::string &jetCollectionName(m_inputJetCollectionNames.at(i));
        const LCCollection *pJetsCollection(pLCEvent->getCollection(jetCollectionName));

        if (!pJetsCollection)
            continue;

        LCCollectionVec *pLCCollectionVec = new LCCollectionVec(LCIO::RECONSTRUCTEDPARTICLE);
        pLCCollectionVec->setSubset(true); // MAGIC line

        for (int j = 0; j < pJetsCollection->getNumberOfElements(); j++)
        {
            const ReconstructedParticle* pJet(dynamic_cast<ReconstructedParticle*>(pJetsCollection->getElementAt(j)));
            for (ReconstructedParticleVec::const_iterator iter = pJet->getParticles().begin(), iterEnd = pJet->getParticles().end(); iter != iterEnd; ++iter)
            {
                pLCCollectionVec->addElement(*iter);
            }
        }

        const std::string &recoParticleCollectionName(m_outputPFOCollectionNames.at(i));
        pLCEvent->addCollection(pLCCollectionVec, recoParticleCollectionName);
    }

    m_nEvt++;
}

//----------------------------------------------------------------------------

void JetsToPFOs::check( LCEvent * evt ) 
{ 
}

//----------------------------------------------------------------------------

void JetsToPFOs::end()
{ 
}

