#include "SelectionProcessor.h"
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

SelectionProcessor generatorProcessor;

//===========================================================

SelectionProcessor::SelectionProcessor() : Processor("SelectionProcessor") 
{
    _description = "Selection processor for vector boson scattering physics analysis";

    registerProcessorParameter("RootFile",
                            "Name of the output root file",
                            m_rootFile,
                            std::string("SelectionProcessor.root"));

    registerInputCollection( LCIO::MCPARTICLE,
                            "CollectionName", 
                            "Name of the MCParticle collection" ,
                            m_CollectionName,
                            std::string("MCParticle"));

    registerProcessorParameter("MCEventEnergy",
                            "MC Event Energy (excluding beam effects)",
                            m_EventMCEnergy,
                            float(1400.f));

    registerProcessorParameter("ConeAngle",
                            "Cone Angle in Degrees",
                            m_ConeAngle,
                            float(10.f));
}

//===========================================================

void SelectionProcessor::init() 
{ 
    m_nRun = 0;
    m_nEvent = 0;

    m_pTFile = new TFile(m_rootFile.c_str(), "recreate");

    m_pTTree = new TTree("SelectionProcessorTree", "SelectionProcessorTree");
    m_pTTree->SetDirectory(m_pTFile);
    m_pTTree->Branch("run", &m_nRun, "run/I");
    m_pTTree->Branch("event", &m_nEvent, "event/I");
}

//===========================================================

void SelectionProcessor::processRunHeader(LCRunHeader* run) 
{ 
    m_nRun++;
} 

//===========================================================

void SelectionProcessor::processEvent(LCEvent * pLCEvent) 
{ 
    // this gets called for every event 
    // usually the working horse ...
    std::cout << "Processing event number : " << m_nEvent << std::endl;

    this->Clear();

    LCCollection* pLCCollection = NULL;
    try
    {
        pLCCollection = pLCEvent->getCollection( m_CollectionName );
    }
    catch( lcio::DataNotAvailableException e )
    {
        streamlog_out(WARNING) << m_CollectionName << " pLCCollectionlection not available" << std::endl;
        pLCCollection = NULL;
    }

    if (pLCCollection != NULL)
    {
//        unsigned int nMCP(pLCCollection->getNumberOfElements());


    try
    {
        const EVENT::ReconstructedParticle *pJet1 = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(0));
        const EVENT::ReconstructedParticle *pJet2 = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(1));
        const EVENT::ReconstructedParticle *pJet3 = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(2));
        const EVENT::ReconstructedParticle *pJet4 = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(3));

        for (unsigned int i = 0; i < pLCCollection->getNumberOfElements(); ++i)
        {
            const EVENT::ReconstructedParticle *pJet = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(i));

            if (pJet == NULL)
            {
                throw EVENT::Exception("Collection type mismatch");
            }

            m_JetVector.push_back(pJet);
        }

        this->IsEventWW();
        this->IsEventZZ();

        this->DoSomethingWithOutputIfHere();

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

        }
    }

    catch (...)
    {
        streamlog_out(ERROR) << "Could not extract input particle collection: " << m_CollectionName << std::endl;
    }

    m_nEvent++;

    m_pTTree->Fill();
}

//===========================================================

void SelectionProcessor::check(LCEvent * pLCEvent)
{
    // nothing to check here - could be used to fill checkplots in reconstruction processor
}

//===========================================================

void SelectionProcessor::end()
{
    m_pTFile->cd();
    m_pTTree->Write();
    m_hWWInvMass->Write();

    m_pTFile->Close();
    delete m_pTFile;

    //   std::cout << "SelectionProcessor::end()  " << name() << " processed " << m_nEvent << " events in " << m_nRun << " runs " << std::endl;
}

//===========================================================

void SelectionProcessor::Clear();
{
    m_JetVector.clear();
    m_WPlusVector.clear();
    m_WMinusVector.clear();
    m_FirstZVector.clear();
    m_SecondZVector.clear();
    m_IsEventWW = false;
    m_IsEventZZ = false;
}

//===========================================================

void SelectionProcessor::IsEventWW()
{
   
}

//===========================================================

void SelectionProcessor::IsEventZZ()
{
}

//===========================================================

void SelectionProcessor::DoSomethingWithOutputIfHere()
{
}

//===========================================================

void SelectionProcessor::CalculateInvariantMass(JetVector &jetVector, float &invariantMass) const
{
    float pxTot(0.f), pyTot(0.f), pzTot(0.f), energyTot(0.f);

    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*it);
        const float px(pReconstructedParticle->getMomentum()[0]);
        const float py(pReconstructedParticle->getMomentum()[1]);
        const float pz(pReconstructedParticle->getMomentum()[2]);
        const float energy(pReconstructedParticle->getEnergy());

        pxTot += px;
        pyTot += py;
        pzTot += pz;
        energyTot += energy;
    }

    invaraintMass = std::sqrt(energyTot*energyTot - pxTot*pxTot - pyTot*pyTot - pzTot*pzTot);
}

//===========================================================

void SelectionProcessor::CalculateTransverseMomentum(JetVector &jetVector, float &transverseMomentum) const
{
    transverseMomentum = 0.f;
    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*it);
        const float px(pReconstructedParticle->getMomentum()[0]);
        const float py(pReconstructedParticle->getMomentum()[1]);
        const float pz(pReconstructedParticle->getMomentum()[2]);
        const float p(std::sqrt(px * px + py * py + pz * pz));
        const float energy(pReconstructedParticle->getEnergy());
        energyMomentum += energy * std::sqrt(px*px + py*py) / p;
    }
}

//===========================================================

void SelectionProcessor::CalculateTransverseEnergy(JetVector &jetVector, float &transverseEnergy) const 
{
    energyMomentum = 0.f;
    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*it);
        const float px(pReconstructedParticle->getMomentum()[0]);
        const float py(pReconstructedParticle->getMomentum()[1]);

        transverseMomentum += std::sqrt(px*px + py*py);
    }
}

//===========================================================

void SelectionProcessor::CalculateCosThetaMissingMomentum(JetVector &jetVector, float &cosTheta) const
{
    float pxMis(0.f);
    float pyMis(0.f);
    float pzMis(0.f);
    this->CalculateMissingMomentum(jetVector, pxMis, pyMis, pzMis);
    const float pMis(std::sqrt(pxMis * pxMis + pyMis * pyMis + pzMis * pzMis));
    cosTheta = pzMis / pMis;
}

//===========================================================

void SelectionProcessor::CalculateMissingMomentum(JetVector &jetVector, float &pxMis, float &pyMis, float &pzMis) const
{
    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*it);
        pxMis -= pReconstructedParticle->getMomentum()[0];
        pyMis -= pReconstructedParticle->getMomentum()[1];
        pzMis -= pReconstructedParticle->getMomentum()[2];
    }
}

//===========================================================

void SelectionProcessor::FindCosThetaMostEnergeticTrack(JetVector &jetVector, float &cosTheta) const
{
    EVENT::TrackVec &mostEnergeticTracksFromPFO(NULL);
    this->FindMostEnergeticTrack(jetVector,mostEnergeticTracksFromPFO);
    float largestCosThetaTrack(0.f);

    for (EVENT::TrackVec::iterator it = mostEnergeticTracksFromPFO.begin(); it != &mostEnergeticTracksFromPFO.end(); it++)
    {
        EVENT::Track *pTrack(*it);
        const float tanThetaTrack(1.f / pTrack->getTanLambda());
        const float cosThetaTrack(cos(atan(tanThetaTrack)));

        if (cosThetaTrack > largestCosThetaTrack)
        {
            largestCosThetaTrack = cosThetaTrack;
        }
    }
    cosTheta = largestCosThetaTrack;
}

//===========================================================

void SelectionProcessor::FindMostEnergeticTrack(JetVector &jetVector, EVENT::TrackVec &mostEnergeticTracksFromPFO) const
{
    JetVector *pReconstructedParticleVec = new JetVector();

    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pJet(*it);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pJet->getParticles.begin(), pJet->getParticles.end());
    }

    float mostEnergeticChargedParticle(0.f);

    for (JetVector::iterator it = pReconstructedParticleVec->begin(); it != pReconstructedParticleVec->end(); it++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*it);

        if (!pReconstructedParticle->getTracks().empty() and pReconstructedParticle->getEnergy() > mostEnergeticChargedParticle)
        {
            mostEnergeticTracksFromPFO = pReconstructedParticle->getTracks();
        }
    }
}

//===========================================================

void SelectionProcessor::FindRecoilMass(JetVector &jetVector, float &recoilMass) const
{
    TLorentzVector pInit(0,0,0,m_EventMCEnergy);
    float px(0.f), py(0.f), pz(0.f), E(0.f);

    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
        pz += pReconstructedParticle->getMomentum()[2];
        E += pReconstructedParticle->getEnergy();
    }

    TLorentzVector pVis(px,py,pz,E);
    TLorentzVector pMis(pInit - pVis);
    recoilMass = pMis.M(); // Invairant Mass/Magnitude
}

//===========================================================

void SelectionProcessor::FindEnergyInConeAroundMostEnergeticTrack(JetVector &jetVector, EVENT::TrackVec &mostEnergeticTracksFromPFO, float &energyAroundTrack) const
{
    JetVector *pReconstructedParticleVec = new JetVector();

    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pJet(*it);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pJet->getParticles.begin(), pJet->getParticles.end());
    }

    for (EVENT::TrackVec::iterator it = mostEnergeticTracksFromPFO.begin(); it != mostEnergeticTracksFromPFO.end(); it++)
    {
        EVENT::Track *pTrack(*it);
        this->FindEnergyAroundTrack(pReconstructedParticleVec, pTrack, energyAroundTrack);
    }
}

//===========================================================

void SelectionProcessor::FindEnergyAroundTrack(JetVector &particleVector, EVENT::Track &track, float &energyAroundTrack) const
{
    const TrackState *const pTrackState = track.getTrackState(TrackState::AtLastHit);
    energyAroundTrack = 0.f;

    if (!pTrackState)
        return

    const double pt(m_bField * 2.99792e-4 / std::fabs(pTrackState->getOmega()));
/*
    const float px(pt * std::cos(pTrackState->getPhi()));
    const float py(pt * std::sin(pTrackState->getPhi()));
    const float pz(pt * pTrackState->getTanLambda());
*/
    const float pxHat(std::cos(pTrackState->getPhi()));
    const float pyHat(std::sin(pTrackState->getPhi()));
    const float pzHat(pTrackState->getTanLambda());

    TVector3 p(pxHat,pyHat,pzHat);

    const float xs(pTrackState->getReferencePoint()[0]);
    const float ys(pTrackState->getReferencePoint()[1]);
    const float zs(pTrackState->getReferencePoint()[2]);

    TVector3 trackAtCalorimeter(xs,ys,zs);

    for (JetVector::iterator partIt = particleVector.begin(); partIt != particleVector.end(); partIt++)
    {
        const EVENT::ReconstructedParticle *pJet(*partIt);
        for (EVENT::ClusterVec::iterator clusIt = pJet->getClusters().begin(); clusIt != pJet->getClusters().end(); clusIt++)
        {
            const EVENT::Cluster pCluster(*clusIt);
            for (EVENT::CalorimeterHitVec::iterator caloIt = pCluster->getCalorimeterHits().begin(); caloIt != pCluster->getCalorimeterHits().end(); caloIt++)
            {
                const EVENT::CalorimeterHit *pCaloHit(*caloIt);
                const float xCaloHit(pCaloHit->getPosition[0]);
                const float yCaloHit(pCaloHit->getPosition[1]);
                const float zCaloHit(pCaloHit->getPosition[2]);
                TVector3 caloHit(xCaloHit,yCaloHit,zCaloHit);
                TVector3 trackCalorimeterToCaloHit(caloHit-trackAtCalorimeter);
                const float cosTheta(trackCalorimeterToCaloHit * p / p.Mag()); // Dot Product
                const float theta(acos(cosTheta) * 180 / PI);

                if (m_ConeAngle - theta > 0.f)
                {
                    energyAroundTrack += pCaloHit->getEnergy();
                }
            }
        }
    }
}

//===========================================================

void SelectionProcessor::FindJetClusteringVariableY34(const LCCollection *pLCCollection, float &y34) const 
{
    PIDHandler pidHandler(pLCCollection);
    const int algorithmID(pidHandle.getAlgorithmID("yth"));
    const ParticleID &particleID(pidHandle.getParticleID(pLCCollection->getElementAt(0), algorithmID));
    const float ySeparation(particleID.getParameters()[pidHandler.getParameterIndex(algorithmID, "y34")];
    const float minusLogYSeparation( (ySeparation > std::numeric_limits<double>::epsilon()) ? - std::log10(ySeparation) : 0.f);
    y34 = minusLogYSeparation;
}

//===========================================================

void SelectionProcessor::JetVariables(const EVENT::ReconstructedParticle *pJet, float energy, int numberOfParticles, int numberOfChargedParticles) const
{
    energy = pJet->getEnergy();
    numberOfParticles = pJet->getParticles().size()
    numberOfChargedParticles = pJet->getTrackVec().size();
}

//===========================================================

void SelectionProcessor::JetPairing(JetVector &jetVector)
{
    JetVector           m_JetVector;                            ///<
    JetVector           m_WPlusVector;                          ///<
    JetVector           m_WMinusVector;                         ///<
    JetVector           m_FirstZVector;                         ///<
    JetVector           m_SecondZVector;                        ///<
    bool                m_IsEventWW;                            ///<
    bool                m_IsEventZZ;                            ///<


}


void SelectionProcessor::WWPairing(JetVector &wCandidates)
{
    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pJet(*it);
}








void SelectionProcessor::CalculateWBosonPolarAngle(TLorentzVector wPlus, TLorentzVector wMinus, float &cosThetaStar)
{
    TLorentzVector diBoson = wPlus + wMinus;
    TVector3 boostvector = -diBoson.BoostVector();
    wPlus.Boost(boostvector);
    cosThetaStar = std::fabs(wPlus.Vect().Dot(diBoson.Vect()) / (diBoson.Vect().Mag() * wPlus.Vect().Mag()));
}

//===========================================================
