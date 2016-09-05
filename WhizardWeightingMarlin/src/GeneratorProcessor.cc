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
    m_wCosThetaStar2 = new TH1F("WCosThetaStar2", "Cosine Theta of W Boson in WW Rest Frame", 10, 0, 1);
    m_wCosThetaStar3 = new TH1F("WCosThetaStar3", "Cosine Theta of W Boson in WW Rest Frame", 10, 0, 1);

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
//        unsigned int nMCP(pLCCollection->getNumberOfElements());

        MCParticle *u = NULL;
        MCParticle *d = NULL;
        MCParticle *au = NULL;
        MCParticle *ad = NULL;

        MCParticle *pMCParticle1 = dynamic_cast<MCParticle*>(pLCCollection->getElementAt(8));
        MCParticle *pMCParticle2 = dynamic_cast<MCParticle*>(pLCCollection->getElementAt(9));
        MCParticle *pMCParticle3 = dynamic_cast<MCParticle*>(pLCCollection->getElementAt(10));
        MCParticle *pMCParticle4 = dynamic_cast<MCParticle*>(pLCCollection->getElementAt(11));

        this->SetQuarks(pMCParticle1,u,d,au,ad);
        this->SetQuarks(pMCParticle2,u,d,au,ad);
        this->SetQuarks(pMCParticle3,u,d,au,ad);
        this->SetQuarks(pMCParticle4,u,d,au,ad);

        if (u == NULL)
        {
            std::cout << "Up quark is null and not set properly" << std::endl;
        }

        if (au == NULL)
        {
            std::cout << "Anti-up quark is null and not set properly" << std::endl;
        }
        if (d == NULL)
        {
            std::cout << "Down quark is null and not set properly" << std::endl;
        }
        if (ad == NULL)
        {
            std::cout << "Anti-down quark is null and not set properly" << std::endl;
        }

        std::cout << "u  : " << u->getPDG() << std::endl;
        std::cout << "d  : " << d->getPDG() << std::endl;
        std::cout << "au : " << au->getPDG() << std::endl;
        std::cout << "ad : " << ad->getPDG() << std::endl;

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

            float eventWeight(0.f);
            float eventWeight2(0.f);
            float eventWeight3(0.f);
            m_CouplingAnalysis->GetWeight(m_nEvent, 0.000, 0.000, eventWeight);
            m_CouplingAnalysis->GetWeight(m_nEvent, 0.095, 0.000, eventWeight2);
            m_CouplingAnalysis->GetWeight(m_nEvent, 0.000, 0.095, eventWeight3);

            m_wCosThetaStar->Fill(cosThetaStar, eventWeight);
            m_wCosThetaStar2->Fill(cosThetaStar, eventWeight2);
            m_wCosThetaStar3->Fill(cosThetaStar, eventWeight3);
            std::cout << "WW invariant mass is : " << wwInvariantMass << std::endl;
            std::cout << "W Cos Theta Star is  : " << cosThetaStar << std::endl;
            std::cout << "Event weight (0,0)           : " << eventWeight << std::endl;
            std::cout << "Event weight (0.02,0.0) : " << eventWeight2 << std::endl;
            std::cout << "Event weight (0.0,0.02) : " << eventWeight3 << std::endl;
        }
    }

    m_nEvent++;

    m_pTTree->Fill();
}

//===========================================================

void GeneratorProcessor::SetQuarks(MCParticle *pMCParticle, MCParticle *&u, MCParticle *&d, MCParticle *&au, MCParticle *&ad) const 
{
    const int pdg(pMCParticle->getPDG());

    std::cout << "Setting quark pdg : " << pdg << std::endl;

    if (pdg == 1 or pdg == 3 or pdg == 5) 
    {
         u = pMCParticle;
    }
    else if (pdg == -1 or pdg == -3 or pdg == -5) 
    {
        au = pMCParticle;
    }
    else if (pdg == 2 or pdg == 4 or pdg == 6) 
    {
        d = pMCParticle;
    }
    else if (pdg == -2 or pdg == -4 or pdg == -6) 
    {
        ad = pMCParticle;
    }
    return;
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
    m_wCosThetaStar2->Write();
    m_wCosThetaStar3->Write();

    m_pTFile->Close();
    delete m_pTFile;

    //   std::cout << "GeneratorProcessor::end()  " << name() << " processed " << m_nEvent << " events in " << m_nRun << " runs " << std::endl;
}
