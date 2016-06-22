#include "SelectionProcessor.h"
#include <iostream>

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>

#include "marlin/VerbosityLevels.h"

#include "TFile.h"
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

    registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
                            "CollectionName",
                            "Name of input jet collection",
                            m_CollectionName,
                            std::string());

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

    m_WBosonMass = 80.385;
    m_ZBosonMass = 91.1876;

    m_pTFile = new TFile(m_rootFile.c_str(), "recreate");

    m_pTTree = new TTree("SelectionProcessorTree", "SelectionProcessorTree");
    m_pTTree->SetDirectory(m_pTFile);
    m_pTTree->Branch("run", &m_nRun, "run/I");
    m_pTTree->Branch("event", &m_nEvent, "event/I");

    m_pTTree->Branch("IsEventWW", &m_IsEventWW, "IsEventWW/O");
    m_pTTree->Branch("IsEventZZ", &m_IsEventZZ, "IsEventZZ/O");

    m_pTTree->Branch("InvMassWVector1", &m_InvMassWVector1, "InvMassWVector1/F");
    m_pTTree->Branch("InvMassWVector2", &m_InvMassWVector2, "InvMassWVector2/F");
    m_pTTree->Branch("InvMassZVector1", &m_InvMassZVector1, "InvMassZVector1/F");
    m_pTTree->Branch("InvMassZVector2", &m_InvMassZVector2, "InvMassZVector2/F");
    m_pTTree->Branch("TransverseMomentum", &m_TransverseMomentum, "TransverseMomentum/F");
    m_pTTree->Branch("TransverseEnergy", &m_TransverseEnergy, "TransverseEnergy/F");
    m_pTTree->Branch("CosThetaMissing", &m_CosThetaMissing, "CosThetaMissing/F");
    m_pTTree->Branch("CosThetaMostEnergeticTrack", &m_CosThetaMostEnergeticTrack, "CosThetaMostEnergeticTrack/F");
    m_pTTree->Branch("RecoilMass", &m_RecoilMass, "RecoilMass/F");
    m_pTTree->Branch("EnergyAroundMostEnergeticTrack", &m_EnergyAroundMostEnergeticPfo, "EnergyAroundMostEnergeticTrack/F");
    m_pTTree->Branch("y34", &m_y34, "y34/F");

    m_pTTree->Branch("EnergyJets", &m_EnergyJets);
    m_pTTree->Branch("NParticlesJets", &m_NParticlesJets);
    m_pTTree->Branch("NChargedParticlesJets", &m_NChargedParticlesJets);
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


    try 
    {
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

            const EVENT::ReconstructedParticle *pJet1 = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(0));
            const EVENT::ReconstructedParticle *pJet2 = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(1));
            const EVENT::ReconstructedParticle *pJet3 = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(2));
            const EVENT::ReconstructedParticle *pJet4 = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(3));

            for (unsigned int i = 0; i < pLCCollection->getNumberOfElements(); i++)
            {
                const EVENT::ReconstructedParticle *pJet = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(i));

                if (pJet == NULL)
                {
                    throw EVENT::Exception("Collection type mismatch");
                }

                int nParticles(0), nChargedParticles(0);
                float energy(0.f);
                this->JetVariables(pJet, energy, nParticles, nChargedParticles);
                m_EnergyJets.push_back(energy);
                m_NParticlesJets.push_back(nParticles);
                m_NChargedParticlesJets.push_back(nChargedParticles);

                m_JetVector.push_back(pJet);
            }

            this->JetPairing(m_JetVector,"ww");
            this->JetPairing(m_JetVector,"zz");

            this->CalculateTransverseMomentum(m_JetVector, m_TransverseMomentum);
            this->CalculateTransverseEnergy(m_JetVector, m_TransverseEnergy);
            this->CalculateCosThetaMissingMomentum(m_JetVector, m_CosThetaMissing);
            this->FindCosThetaMostEnergeticTrack(m_JetVector, m_CosThetaMostEnergeticTrack);
            this->FindRecoilMass(m_JetVector, m_RecoilMass);
            this->FindEnergyInConeAroundMostEnergeticPfo(m_JetVector, m_EnergyAroundMostEnergeticPfo);
            this->FindJetClusteringVariableY34(pLCCollection, m_y34);

            this->IsEventWW();
            this->IsEventZZ();

            this->DoSomethingWithOutputIfHere();
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

    m_pTFile->Close();
    delete m_pTFile;

    //   std::cout << "SelectionProcessor::end()  " << name() << " processed " << m_nEvent << " events in " << m_nRun << " runs " << std::endl;
}

//===========================================================

void SelectionProcessor::Clear()
{
    m_JetVector.clear();
    m_WVector1.clear();
    m_WVector2.clear();
    m_ZVector1.clear();
    m_ZVector2.clear();

    m_IsEventWW = false;
    m_IsEventZZ = false;

    m_InvMassWVector1 = 0.f;
    m_InvMassWVector2 = 0.f;
    m_InvMassZVector1 = 0.f;
    m_InvMassZVector2 = 0.f;
    m_TransverseMomentum = 0.f;
    m_TransverseEnergy = 0.f;
    m_CosThetaMissing = 0.f;
    m_CosThetaMostEnergeticTrack = 0.f;
    m_RecoilMass = 0.f;
    m_EnergyAroundMostEnergeticPfo = 0.f;
    m_y34 = 0.f;
    
    m_EnergyJets.clear();
    m_NParticlesJets.clear();
    m_NChargedParticlesJets.clear();
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

    invariantMass = std::sqrt(energyTot*energyTot - pxTot*pxTot - pyTot*pyTot - pzTot*pzTot);
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
        transverseMomentum += energy * std::sqrt(px*px + py*py) / p;
    }
}

//===========================================================

void SelectionProcessor::CalculateTransverseEnergy(JetVector &jetVector, float &transverseEnergy) const 
{
    transverseEnergy = 0.f;
    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*it);
        const float px(pReconstructedParticle->getMomentum()[0]);
        const float py(pReconstructedParticle->getMomentum()[1]);

        transverseEnergy += std::sqrt(px*px + py*py);
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
    EVENT::TrackVec mostEnergeticTracksFromPfo;
    this->FindMostEnergeticTrack(jetVector,mostEnergeticTracksFromPfo);
    float largestCosThetaTrack(0.f);

    for (EVENT::TrackVec::iterator it = mostEnergeticTracksFromPfo.begin(); it != mostEnergeticTracksFromPfo.end(); it++)
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

void SelectionProcessor::FindMostEnergeticTrack(JetVector &jetVector, EVENT::TrackVec &mostEnergeticTracksFromPfo) const
{
    JetVector *pReconstructedParticleVec = new JetVector();

    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pJet(*it);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pJet->getParticles().begin(), pJet->getParticles().end());
    }

    float energyMostEnergeticChargedPfo(0.f);

    for (JetVector::iterator it = pReconstructedParticleVec->begin(); it != pReconstructedParticleVec->end(); it++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*it);

        if (!pReconstructedParticle->getTracks().empty() and pReconstructedParticle->getEnergy() > energyMostEnergeticChargedPfo)
        {
            mostEnergeticTracksFromPfo = pReconstructedParticle->getTracks();
            energyMostEnergeticChargedPfo = pReconstructedParticle->getEnergy();
        }
    }
}

//===========================================================

void SelectionProcessor::FindMostEnergeticChargedParticle(JetVector &jetVector, const EVENT::ReconstructedParticle *&pMostEnergeticChargedPfo) const
{
    JetVector *pReconstructedParticleVec = new JetVector();

    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pJet(*it);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pJet->getParticles().begin(), pJet->getParticles().end());
    }

    float energyMostEnergeticChargedPfo(0.f);

    for (JetVector::iterator it = pReconstructedParticleVec->begin(); it != pReconstructedParticleVec->end(); it++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*it);

        if (!pReconstructedParticle->getTracks().empty() and pReconstructedParticle->getEnergy() > energyMostEnergeticChargedPfo)
        {
            pMostEnergeticChargedPfo = pReconstructedParticle;
            energyMostEnergeticChargedPfo = pReconstructedParticle->getEnergy();
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
        const EVENT::ReconstructedParticle* pReconstructedParticle(*it);
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

void SelectionProcessor::FindEnergyInConeAroundMostEnergeticPfo(JetVector &jetVector, float &energyAroundMostEnergeticChargedPfo) const
{
    const EVENT::ReconstructedParticle *pMostEnergeticChargedPfo(NULL);
    this->FindMostEnergeticChargedParticle(jetVector, pMostEnergeticChargedPfo);

    JetVector *pReconstructedParticleVec = new JetVector();
    for (JetVector::iterator it = jetVector.begin(); it != jetVector.end(); it++)
    {
        const EVENT::ReconstructedParticle* pJet(*it);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pJet->getParticles().begin(), pJet->getParticles().end());
    }

    this->FindEnergyAroundPfo(pReconstructedParticleVec, pMostEnergeticChargedPfo, energyAroundMostEnergeticChargedPfo);
}

//===========================================================

void SelectionProcessor::FindEnergyAroundPfo(JetVector *pParticleVector, const EVENT::ReconstructedParticle *pMostEnergeticChargedPfo, float &energyAroundMostEnergeticChargedPfo) const
{
    float pfoX(0.f), pfoY(0.f), pfoZ(0.f);

    this->GetPfoPosition(pMostEnergeticChargedPfo, pfoX, pfoY, pfoZ);

    TVector3 pfoPosition(pfoX, pfoY, pfoZ);

    const float pfoPx(pMostEnergeticChargedPfo->getMomentum()[0]);
    const float pfoPy(pMostEnergeticChargedPfo->getMomentum()[1]);
    const float pfoPz(pMostEnergeticChargedPfo->getMomentum()[2]);

    TVector3 pfoP(pfoPx,pfoPy,pfoPz);
    TVector3 unitPfoP(pfoP.Unit());

    std::cout << "pfoX : " << pfoX << std::endl;
    std::cout << "pfoY : " << pfoY << std::endl;
    std::cout << "pfoZ : " << pfoZ << std::endl;
    std::cout << "pfoPx : " << pfoPx << std::endl;
    std::cout << "pfoPy : " << pfoPy << std::endl;
    std::cout << "pfoPz : " << pfoPz << std::endl;

/*
    // This would work better if the CLIC samples had the track states

    // There is one track state at the distance of closest approach
    TrackStateVec trackStateVec = pTrack->getTrackStates();

    for (TrackStateVec::iterator it = trackStateVec.begin(); it < trackStateVec.end(); it++)
    {
        TrackState *pTrackState(*it);
        std::cout << "Track state number : " << it - trackStateVec.begin() << std::endl;
        std::cout << "pTrackState->getLocation() : " << pTrackState->getLocation() << std::endl;
    }


    // CLIC samples do not record the track state, so must use an alternative
    const TrackState *const pTrackState = pTrack->getTrackState(TrackState::AtCalorimeter);
    energyAroundTrack = 0.f;

    if (!pTrackState)
        return;

    const float bField(4.f); // Along Z direction, taken from CLIC gear file
    const float pt(bField * 2.99792e-4 / std::fabs(pTrackState->getOmega()));

    const float pxHat(std::cos(pTrackState->getPhi()));
    const float pyHat(std::sin(pTrackState->getPhi()));
    const float pzHat(pTrackState->getTanLambda());

    TVector3 p(pxHat,pyHat,pzHat);

    const float xs(pTrackState->getReferencePoint()[0]);
    const float ys(pTrackState->getReferencePoint()[1]);
    const float zs(pTrackState->getReferencePoint()[2]);

    TVector3 trackAtCalorimeter(xs,ys,zs);
*/
    EVENT::ClusterVec clusters;

    for (JetVector::iterator partIt = pParticleVector->begin(); partIt != pParticleVector->end(); partIt++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*partIt);
        clusters.insert(clusters.end(), pReconstructedParticle->getClusters().begin(), pReconstructedParticle->getClusters().end());
    }

    for (EVENT::ClusterVec::const_iterator clusIt = clusters.begin(); clusIt != clusters.end(); clusIt++)
    {
        const EVENT::Cluster *pCluster(*clusIt);
        const float pfoXCandidate( pCluster->getPosition()[0]);
        const float pfoYCandidate( pCluster->getPosition()[1]);
        const float pfoZCandidate( pCluster->getPosition()[2]);
        TVector3 pfoPositionCandidate(pfoXCandidate,pfoYCandidate,pfoZCandidate);
        TVector3 pfoCentroidToPfoCandidate(pfoPositionCandidate - pfoPosition);
        TVector3 unitPfoCentroidToPfoCandidate(pfoCentroidToPfoCandidate.Unit());

        float cosTheta(std::numeric_limits<float>::max());
        float theta(std::numeric_limits<float>::max());

        if (std::fabs(unitPfoCentroidToPfoCandidate.x()) < std::numeric_limits<float>::min() and std::fabs(unitPfoCentroidToPfoCandidate.y()) < std::numeric_limits<float>::min() and std::fabs(unitPfoCentroidToPfoCandidate.z()) < std::numeric_limits<float>::min())
        {
            cosTheta = 1.f;
            theta = 0.f;
        }
        else
        {
            cosTheta = unitPfoCentroidToPfoCandidate * unitPfoP; // Dot Product
            theta = acos(cosTheta) * 180 / M_PI;
        }

        if (m_ConeAngle - theta > 0.f)
        {
            energyAroundMostEnergeticChargedPfo += pCluster->getEnergy();
        }
    }
}

//===========================================================

void SelectionProcessor::GetPfoPosition(const EVENT::ReconstructedParticle *pReconstructedParticle, float &x, float &y, float &z) const
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
    float pfoEnergy(0.f);

    for (EVENT::ClusterVec::const_iterator clusIt = pReconstructedParticle->getClusters().begin(); clusIt != pReconstructedParticle->getClusters().end(); clusIt++)
    {
        const EVENT::Cluster *pCluster(*clusIt);
        x += pCluster->getPosition()[0] * pCluster->getEnergy();       
        y += pCluster->getPosition()[1] * pCluster->getEnergy();       
        z += pCluster->getPosition()[2] * pCluster->getEnergy();       
        pfoEnergy += pCluster->getEnergy();
    }

    x /= pfoEnergy;
    y /= pfoEnergy;
    z /= pfoEnergy;
}

//===========================================================

void SelectionProcessor::FindJetClusteringVariableY34(const LCCollection *pLCCollection, float &y34) const 
{
    std::string stringY34("y_{n-1,n}");
    std::string stringY45("y_{n,n+1}");
    const float parameterY34(pLCCollection->getParameters().getFloatVal(stringY34));
    const float minusLogYSeparation( (parameterY34 > std::numeric_limits<double>::epsilon()) ? - std::log10(parameterY34) : 0.f);
    y34 = minusLogYSeparation;

    std::cout << "y34 : " << y34 << ", y45 : " << -std::log10(pLCCollection->getParameters().getFloatVal(stringY45)) << std::endl;
}

//===========================================================

void SelectionProcessor::JetVariables(const EVENT::ReconstructedParticle *pJet, float &energy, int &numberOfParticles, int &numberOfChargedParticles) const
{
    energy = pJet->getEnergy();
    numberOfParticles = pJet->getParticles().size();
    
    JetVector *pReconstructedParticleVec = new JetVector();
    pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pJet->getParticles().begin(), pJet->getParticles().end());

    for (JetVector::iterator it = pReconstructedParticleVec->begin(); it != pReconstructedParticleVec->end(); it++)
    {
        numberOfChargedParticles += (*it)->getTracks().size();
    }
}

//===========================================================

void SelectionProcessor::JetPairing(JetVector &wCandidates, std::string type)
{
    float targetMass(0.f);

    std::cout << type << std::endl;

    if (type == "ww")
    {
        targetMass = m_WBosonMass;
    }
    else if (type == "zz")
    {
        targetMass = m_ZBosonMass;
    }
    else
    {
        std::cout << "Please select valid type for jet pairing (zz or ww)." << std::endl;
        return;
    }

    std::vector<IntVector > combinations;
    static const int array1[] = {0,1,2,3};
    IntVector combination1 (array1, array1 + sizeof(array1) / sizeof(array1[0]));
    combinations.push_back(combination1);
    static const int array2[] = {0,2,1,3};
    IntVector combination2 (array2, array2 + sizeof(array2) / sizeof(array2[0]));
    combinations.push_back(combination2);
    static const int array3[] = {0,3,1,2};
    IntVector combination3 (array3, array3 + sizeof(array3) / sizeof(array3[0]));
    combinations.push_back(combination3);

    float bestMetric(std::numeric_limits<float>::max());

    for (std::vector<IntVector>::iterator it = combinations.begin(); it != combinations.end(); it++)
    {
        IntVector combination(*it);

        JetVector trialPair1, trialPair2;
        trialPair1.push_back(wCandidates.at(combination.at(0)));
        trialPair1.push_back(wCandidates.at(combination.at(1)));
        trialPair2.push_back(wCandidates.at(combination.at(2)));
        trialPair2.push_back(wCandidates.at(combination.at(3)));

        float invariantMass1(0.f), invariantMass2(0.f);

        this->CalculateInvariantMass(trialPair1, invariantMass1);
        this->CalculateInvariantMass(trialPair2, invariantMass2);

        const float metric((std::fabs(invariantMass1-targetMass))*std::fabs(invariantMass2-targetMass));

        if (metric < bestMetric)
        {
            if (type == "ww")
            {
                m_WVector1 = trialPair1;
                m_InvMassWVector1 = invariantMass1;
                m_WVector2 = trialPair2;
                m_InvMassWVector2 = invariantMass2;
            }
            else if (type == "zz")
            {
                m_ZVector1 = trialPair1;
                m_InvMassZVector1 = invariantMass1;
                m_ZVector2 = trialPair2;
                m_InvMassZVector2 = invariantMass2;
            }
        }
    }
}

//===========================================================
/*
void SelectionProcessor::CalculateWBosonPolarAngle(TLorentzVector wPlus, TLorentzVector wMinus, float &cosThetaStar)
{
    TLorentzVector diBoson = wPlus + wMinus;
    TVector3 boostvector = -diBoson.BoostVector();
    wPlus.Boost(boostvector);
    cosThetaStar = std::fabs(wPlus.Vect().Dot(diBoson.Vect()) / (diBoson.Vect().Mag() * wPlus.Vect().Mag()));
}
*/
//===========================================================
