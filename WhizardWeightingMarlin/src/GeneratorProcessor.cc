#include "GeneratorProcessor.h"
#include <iostream>

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>

#include "marlin/VerbosityLevels.h"

#include "TFile.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TVector3.h"

using namespace lcio ;
using namespace marlin ;

GeneratorProcessor generatorProcessor;

//===========================================================

GeneratorProcessor::GeneratorProcessor() : Processor("GeneratorProcessor") 
{
    _description = "Generator level study for vector boson scattering physics analysis";

    registerProcessorParameter("RootFile",
                            "Name of the output root file",
                            m_rootFile,
                            std::string("GeneratorAnalysis.root"));

    registerInputCollection( LCIO::MCPARTICLE,
            "CollectionName", 
            "Name of the MCParticle collection" ,
            m_CollectionName,
            std::string("MCParticle")
    );
}

//===========================================================

void GeneratorProcessor::init() 
{ 
    m_nRun = 0;
    m_nEvent = 0;

    m_pTFile = new TFile(m_rootFile.c_str(), "recreate");

    m_pTTree = new TTree("GeneratorAnalysisTree", "GeneratorAnalysisTree");
    m_pTTree->SetDirectory(m_pTFile);
    m_pTTree->Branch("run", &m_nRun, "run/I");
    m_pTTree->Branch("event", &m_nEvent, "event/I");

    const float bins[] = { 140, 160, 180, 200, 220, 240, 260, 280, 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400 };
    const unsigned int nBins = sizeof(bins)/sizeof(float) - 1;
    m_hWWInvMass = new TH1F("WWInvMass", "Invariant Mass of WW Pair in VBS", nBins, bins);

    m_wCosThetaStar = new TH1F("WCosThetaStar", "Cosine Theta of W Boson in WW Rest Frame", 10, 0, 1);

    m_CouplingAnalysis = new CouplingAnalysis();
}

//===========================================================

void GeneratorProcessor::processRunHeader(LCRunHeader* run) 
{ 
    m_nRun++;
} 

//===========================================================

void GeneratorProcessor::processEvent(LCEvent * evt) 
{ 
    // this gets called for every event 
    // usually the working horse ...

    std::cout << "Processing event number : " << m_nEvent << std::endl;

    LCCollection* pLCCollection = NULL;
    try
    {
        pLCCollection = evt->getCollection( m_CollectionName );
    }
    catch( lcio::DataNotAvailableException e )
    {
        streamlog_out(WARNING) << m_CollectionName << " pLCCollectionlection not available" << std::endl;
        pLCCollection = NULL;
    }

    if (pLCCollection != NULL)
    {
        unsigned int nMCP(pLCCollection->getNumberOfElements());

        std::cout << "The event weight is : " << evt->getWeight() << std::endl;

        MCParticle *u = NULL;
        MCParticle *d = NULL;
        MCParticle *au = NULL;
        MCParticle *ad = NULL;

        for(unsigned int i = 0; i < nMCP; i++)
        {
            MCParticle *pMCParticle = dynamic_cast<MCParticle*>(pLCCollection->getElementAt(i));
            const int pdg(pMCParticle->getPDG());

            if (i > 12) continue;

            if (std::abs(pdg) != 1 and std::abs(pdg) != 2 and std::abs(pdg) != 3 and std::abs(pdg) != 4 and std::abs(pdg) != 5)
                continue;

            MCParticle *pMCParticlePair = dynamic_cast<MCParticle*>(pLCCollection->getElementAt(i+1));
            const int pdgPair(pMCParticlePair->getPDG());

            if (pdg == 1 and (pdgPair != -2 and pdgPair != -4)) continue;
            if (pdg == -1 and (pdgPair != 2 and pdgPair != 4)) continue;

            if (pdg == 2 and (pdgPair != -1 and pdgPair != -3 and pdgPair != -5)) continue;
            if (pdg == -2 and (pdgPair != 1 and pdgPair != 3 and pdgPair != 5)) continue;

            if (pdg == 3 and (pdgPair != -2 and pdgPair != -4)) continue;
            if (pdg == -3 and (pdgPair != 2 and pdgPair != 4)) continue;

            if (pdg == 4 and (pdgPair != -1 and pdgPair != -3 and pdgPair != -5)) continue;
            if (pdg == -4 and (pdgPair != 1 and pdgPair != 3 and pdgPair != 5)) continue;

            if (pdg == 5 and (pdgPair != -2 and pdgPair != -4)) continue;
            if (pdg == -5 and (pdgPair != 2 and pdgPair != 4)) continue;

            if (pdg == 1 or pdg == 3 or pdg == 5)
            {
                u = pMCParticle;
                ad = pMCParticlePair;
            }
            else if (pdg == -1 or pdg == -3 or pdg == -5)
            {
                au = pMCParticle;
                d = pMCParticlePair;
            }
            else if (pdg == 2 or pdg == 4)
            {
                d = pMCParticle;
                au = pMCParticlePair;
            }
            else if (pdg == -2 or pdg == -4)
            {
                ad = pMCParticle;
                u = pMCParticlePair;
            }
            i++;
        }

        if (u != NULL and au != NULL and d != NULL and ad != NULL)
        {
            std::vector<MCParticle*> mcParticleVector;
            mcParticleVector.push_back(u);
            mcParticleVector.push_back(d);
            mcParticleVector.push_back(au);
            mcParticleVector.push_back(ad);
            float wwInvariantMass(-1.f);
            this->CalculateInvariantMass(mcParticleVector,wwInvariantMass);

            m_hWWInvMass->Fill(wwInvariantMass);
/*
            std::cout << "u  : " << u->getPDG() << std::endl;
            std::cout << "d  : " << d->getPDG() << std::endl;
            std::cout << "au : " << au->getPDG() << std::endl;
            std::cout << "ad : " << ad->getPDG() << std::endl;
*/
            const float wPluspx(u->getMomentum()[0] + ad->getMomentum()[0]);
            const float wPluspy(u->getMomentum()[1] + ad->getMomentum()[1]);
            const float wPlusupz(u->getMomentum()[2] + ad->getMomentum()[2]);
            const float wPlusuenergy(u->getEnergy() + ad->getEnergy());

            const float wMinuspx(d->getMomentum()[0] + au->getMomentum()[0]);
            const float wMinuspy(d->getMomentum()[1] + au->getMomentum()[1]);
            const float wMinuspz(d->getMomentum()[2] + au->getMomentum()[2]);
            const float wMinusenergy(d->getEnergy() + au->getEnergy());

            TLorentzVector wPlus(wPluspx,wPluspy,wPlusupz,wPlusuenergy);
            TLorentzVector wMinus(wMinuspx,wMinuspy,wMinuspz,wMinusenergy);

            float cosThetaStar(-1.f);
            this->CalculateWBosonPolarAngle(wPlus,wMinus,cosThetaStar);
            m_wCosThetaStar->Fill(cosThetaStar);
            std::cout << "WW invariant mass is : " << wwInvariantMass << std::endl;
            std::cout << "W Cos Theta Star is  : " << cosThetaStar << std::endl;
        }
    }

    float eventWeight(0.f);
    m_nEvent++;
    m_CouplingAnalysis->GetWeight(m_nEvent, 0.005, -0.005, eventWeight);

    std::cout << " m_CouplingAnalysis->GetWeight(m_nEvent, 0.005, -0.005, eventWeight) : " << eventWeight << std::endl;

    m_pTTree->Fill();
}

//===========================================================

void GeneratorProcessor::CalculateWBosonPolarAngle(TLorentzVector wPlus, TLorentzVector wMinus, float &cosThetaStar)
{
    TLorentzVector diBoson = wPlus + wMinus;
    TVector3 boostvector = -diBoson.BoostVector();
    wPlus.Boost(boostvector);
    cosThetaStar = std::fabs(wPlus.Vect().Dot(diBoson.Vect()) / (diBoson.Vect().Mag() * wPlus.Vect().Mag()));
}

//===========================================================

void GeneratorProcessor::CalculateInvariantMass(std::vector<MCParticle*> mcParticleVector, float &wwInvariantMass)
{
    float pxTot(0.f), pyTot(0.f), pzTot(0.f), energyTot(0.f);

    for (std::vector<MCParticle*>::iterator it = mcParticleVector.begin(); it != mcParticleVector.end(); it++)
    {
        MCParticle *pMCParticle = *it;
        const float px(pMCParticle->getMomentum()[0]);
        const float py(pMCParticle->getMomentum()[1]);
        const float pz(pMCParticle->getMomentum()[2]);
        const float energy(pMCParticle->getEnergy());

        pxTot += px;
        pyTot += py;
        pzTot += pz;
        energyTot += energy;
    }

    const float invaraintMass(std::sqrt(energyTot*energyTot - pxTot*pxTot - pyTot*pyTot - pzTot*pzTot));

    wwInvariantMass = invaraintMass;
}

//===========================================================

void GeneratorProcessor::check(LCEvent * evt) 
{ 
    // nothing to check here - could be used to fill checkplots in reconstruction processor
}

//===========================================================

void GeneratorProcessor::end()
{ 
    m_pTFile->cd();
    m_pTTree->Write();
    m_hWWInvMass->Write();
    m_wCosThetaStar->Write();

    m_pTFile->Close();
    delete m_pTFile;

    //   std::cout << "GeneratorProcessor::end()  " << name() << " processed " << m_nEvent << " events in " << m_nRun << " runs " << std::endl;
}
