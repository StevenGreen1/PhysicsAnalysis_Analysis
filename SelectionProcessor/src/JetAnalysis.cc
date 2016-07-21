/**
 *  @file   SelectionProcessor/src/JetAnalysis.cc
 *
 *  @brief  Implementation of the jet analysis class.
 *
 *  $Log: $
 */

#include "JetAnalysis.h"

//===========================================================

JetAnalysis::JetAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables):
    m_pVariables(variables),
    m_WBosonMass(80.385f),
    m_ZBosonMass(91.1876f),
    m_CrossingAngle(0.01),
    m_EventMCEnergy(1400.f),
    m_ConeAngle(10.f),
    m_y34(std::numeric_limits<float>::max())
{
    m_JetVector.push_back(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(0)));
    m_JetVector.push_back(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(1)));
    m_JetVector.push_back(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(2)));
    m_JetVector.push_back(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(3)));

    this->CalculateJetClusteringVariableY34(pLCCollection); // Must set before process as selection of WW and ZZ events uses y34
    this->Process();
}

//===========================================================

JetAnalysis::~JetAnalysis()
{
}

//===========================================================

void JetAnalysis::Process()
{
    this->JetVariables();
    this->JetPairing();

    this->CalculateTransverseMomentum();
    this->CalculateTransverseEnergy();
    this->CalculateCosThetaMissingMomentum();
    this->CalculateCosThetaMostEnergeticTrack();
    this->CalculateRecoilMass();
    this->CalculateEnergyInConeAroundMostEnergeticPfo();

    this->IsEventAppropriate();
    if (m_pVariables->GetAppropriateEvent())
    {
        this->IsEventWW();
        this->IsEventZZ();
    }

    this->DefineVariablesOfInterest();
}

//===========================================================

void JetAnalysis::CalculateJetClusteringVariableY34(const EVENT::LCCollection *pLCCollection)
{
    std::string stringY34("y_{n-1,n}");
    std::string stringY45("y_{n,n+1}");
    const float parameterY34(pLCCollection->getParameters().getFloatVal(stringY34));
    const float minusLogYSeparation((parameterY34 > std::numeric_limits<double>::epsilon()) ? - std::log10(parameterY34) : 0.f);
    m_pVariables->SetY34(minusLogYSeparation);
}

//===========================================================

void JetAnalysis::JetVariables()
{
    FloatVector energyJets;
    IntVector nParticlesJets;
    IntVector nChargedParticlesJets;

    for (ParticleVector::iterator iter = m_JetVector.begin(); iter != m_JetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        energyJets.push_back(pReconstructedParticle->getEnergy());
        nParticlesJets.push_back(pReconstructedParticle->getParticles().size());

        int numberOfChargedParticles(0);

        ParticleVector *pReconstructedParticleVec = new ParticleVector();

        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pReconstructedParticle->getParticles().begin(), pReconstructedParticle->getParticles().end());

        for (ParticleVector::iterator iterPart = pReconstructedParticleVec->begin(); iterPart != pReconstructedParticleVec->end(); iterPart++)
        {
            numberOfChargedParticles += (*iterPart)->getTracks().size();
        }
        nChargedParticlesJets.push_back(numberOfChargedParticles);
    }

    m_pVariables->SetEnergyJets(energyJets);
    m_pVariables->SetNParticlesJets(nParticlesJets);
    m_pVariables->SetNChargedParticlesJets(nChargedParticlesJets);
}

//===========================================================

void JetAnalysis::JetPairing()
{
    std::vector<IntVector> combinations;
    static const int array1[] = {0,1,2,3};
    IntVector combination1 (array1, array1 + sizeof(array1) / sizeof(array1[0]));
    combinations.push_back(combination1);
    static const int array2[] = {0,2,1,3};
    IntVector combination2 (array2, array2 + sizeof(array2) / sizeof(array2[0]));
    combinations.push_back(combination2);
    static const int array3[] = {0,3,1,2};
    IntVector combination3 (array3, array3 + sizeof(array3) / sizeof(array3[0]));
    combinations.push_back(combination3);

    float bestWMetric(std::numeric_limits<float>::max()), bestZMetric(std::numeric_limits<float>::max());
    FloatVector bestWMasses, bestZMasses;

    for (std::vector<IntVector>::iterator iter = combinations.begin(); iter != combinations.end(); iter++)
    {
        IntVector combination(*iter);

        ParticleVector trialPair1, trialPair2;
        trialPair1.push_back(m_JetVector.at(combination.at(0)));
        trialPair1.push_back(m_JetVector.at(combination.at(1)));
        trialPair2.push_back(m_JetVector.at(combination.at(2)));
        trialPair2.push_back(m_JetVector.at(combination.at(3)));

        float invariantMass1(0.f), invariantMass2(0.f);

        this->FindInvariantMass(trialPair1, invariantMass1);
        this->FindInvariantMass(trialPair2, invariantMass2);

        const float wMetric((std::fabs(invariantMass1-m_WBosonMass))*std::fabs(invariantMass2-m_WBosonMass));
        const float zMetric((std::fabs(invariantMass1-m_ZBosonMass))*std::fabs(invariantMass2-m_ZBosonMass));

        if (wMetric < bestWMetric)
        {
            m_WVector1 = trialPair1;
            m_WVector2 = trialPair2;
            bestWMasses.clear();
            bestWMasses.push_back(invariantMass1);
            bestWMasses.push_back(invariantMass2);
            bestWMetric = wMetric;
        }

        if (zMetric < bestZMetric)
        {
            m_ZVector1 = trialPair1;
            m_ZVector2 = trialPair2;
            bestZMasses.clear();
            bestZMasses.push_back(invariantMass1);
            bestZMasses.push_back(invariantMass2);
            bestZMetric = zMetric;
        }
    }

    m_pVariables->SetInvMassWVectors(bestWMasses);
    m_pVariables->SetInvMassZVectors(bestZMasses);
}

//===========================================================

void JetAnalysis::FindInvariantMass(ParticleVector &jetVector, float &invariantMass) const
{
    float pxTot(0.f), pyTot(0.f), pzTot(0.f), energyTot(0.f);

    for (ParticleVector::iterator iter = jetVector.begin(); iter != jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
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

void JetAnalysis::CalculateTransverseMomentum()
{
    float transverseMomentum(0.f);
    for (ParticleVector::iterator iter = m_JetVector.begin(); iter != m_JetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        const float px(pReconstructedParticle->getMomentum()[0]);
        const float py(pReconstructedParticle->getMomentum()[1]);
        const float pz(pReconstructedParticle->getMomentum()[2]);
        const float p(std::sqrt(px * px + py * py + pz * pz));
        const float energy(pReconstructedParticle->getEnergy());
        transverseMomentum += energy * std::sqrt(px*px + py*py) / p;
    }
    m_pVariables->SetTransverseMomentum(transverseMomentum);
}

//===========================================================

void JetAnalysis::CalculateTransverseEnergy()
{
    float transverseEnergy(0.f);
    for (ParticleVector::iterator iter = m_JetVector.begin(); iter != m_JetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        const float px(pReconstructedParticle->getMomentum()[0]);
        const float py(pReconstructedParticle->getMomentum()[1]);

        transverseEnergy += std::sqrt(px*px + py*py);
    }
    m_pVariables->SetTransverseEnergy(transverseEnergy);
}

//===========================================================

void JetAnalysis::CalculateCosThetaMissingMomentum() 
{
    float pxMis(0.f);
    float pyMis(0.f);
    float pzMis(0.f);
    this->FindMissingMomentum(pxMis, pyMis, pzMis);
    const float pMis(std::sqrt(pxMis * pxMis + pyMis * pyMis + pzMis * pzMis));
    m_pVariables->SetCosThetaMissing(pzMis / pMis);
}

//===========================================================

void JetAnalysis::FindMissingMomentum(float &pxMis, float &pyMis, float &pzMis) const
{
    for (ParticleVector::const_iterator iter = m_JetVector.begin(); iter != m_JetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        pxMis -= pReconstructedParticle->getMomentum()[0];
        pyMis -= pReconstructedParticle->getMomentum()[1];
        pzMis -= pReconstructedParticle->getMomentum()[2];
    }
    const float xFromCrossingAngle(m_EventMCEnergy * sin(m_CrossingAngle));
    pxMis + xFromCrossingAngle;
}

//===========================================================

void JetAnalysis::CalculateCosThetaMostEnergeticTrack()
{
    EVENT::TrackVec tracksMostEnergeticChargedPfo;
    this->FindMostEnergeticTrack(tracksMostEnergeticChargedPfo);
    float largestCosThetaTrack(0.f);

    for (EVENT::TrackVec::iterator iter = tracksMostEnergeticChargedPfo.begin(); iter != tracksMostEnergeticChargedPfo.end(); iter++)
    {
        EVENT::Track *pTrack(*iter);
        const float tanThetaTrack(1.f / pTrack->getTanLambda());
        const float cosThetaTrack(cos(atan(tanThetaTrack)));

        if (cosThetaTrack > largestCosThetaTrack)
        {
            largestCosThetaTrack = cosThetaTrack;
        }
    }
    m_pVariables->SetCosThetaMostEnergeticTrack(largestCosThetaTrack);
}

//===========================================================

void JetAnalysis::FindMostEnergeticTrack(EVENT::TrackVec &tracksMostEnergeticChargedPfo) const
{
    ParticleVector *pReconstructedParticleVec = new ParticleVector();

    for (ParticleVector::const_iterator iter = m_JetVector.begin(); iter != m_JetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pReconstructedParticle->getParticles().begin(), pReconstructedParticle->getParticles().end());
    }

    float energyMostEnergeticChargedPfo(0.f);

    for (ParticleVector::const_iterator iter = pReconstructedParticleVec->begin(); iter != pReconstructedParticleVec->end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);

        if (!pReconstructedParticle->getTracks().empty() and pReconstructedParticle->getEnergy() > energyMostEnergeticChargedPfo)
        {
            tracksMostEnergeticChargedPfo = pReconstructedParticle->getTracks();
            energyMostEnergeticChargedPfo = pReconstructedParticle->getEnergy();
        }
    }
}

//===========================================================

void JetAnalysis::CalculateRecoilMass()
{
    const float xFromCrossingAngle(m_EventMCEnergy * sin(m_CrossingAngle));
    TLorentzVector pInit(xFromCrossingAngle,0,0,m_EventMCEnergy);
    float px(0.f), py(0.f), pz(0.f), E(0.f);

    for (ParticleVector::const_iterator iter = m_JetVector.begin(); iter != m_JetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
        pz += pReconstructedParticle->getMomentum()[2];
        E += pReconstructedParticle->getEnergy();
    }

    TLorentzVector pVis(px,py,pz,E);
    TLorentzVector pMis(pInit - pVis);
    float recoilMass(pMis.M()); // Invairant Mass/Magnitude
    m_pVariables->SetRecoilMass(recoilMass);
}

//===========================================================

void JetAnalysis::CalculateEnergyInConeAroundMostEnergeticPfo()
{
    const EVENT::ReconstructedParticle *pMostEnergeticChargedPfo(NULL);
    this->FindMostEnergeticChargedParticle(pMostEnergeticChargedPfo);

    ParticleVector *pReconstructedParticleVec = new ParticleVector();
    for (ParticleVector::const_iterator iter = m_JetVector.begin(); iter != m_JetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pReconstructedParticle->getParticles().begin(), pReconstructedParticle->getParticles().end());
    }

    float energyAroundMostEnergeticChargedPfo(0.f);
    this->FindEnergyAroundPfo(pReconstructedParticleVec, pMostEnergeticChargedPfo, energyAroundMostEnergeticChargedPfo);
    m_pVariables->SetEnergyAroundMostEnergeticPfo(energyAroundMostEnergeticChargedPfo);
}

//===========================================================

void JetAnalysis::FindMostEnergeticChargedParticle(const EVENT::ReconstructedParticle *&pMostEnergeticChargedPfo) const
{
    ParticleVector *pReconstructedParticleVec = new ParticleVector();

    for (ParticleVector::const_iterator iter = m_JetVector.begin(); iter != m_JetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pReconstructedParticle->getParticles().begin(), pReconstructedParticle->getParticles().end());
    }

    float energyMostEnergeticChargedPfo(0.f);

    for (ParticleVector::iterator iter = pReconstructedParticleVec->begin(); iter != pReconstructedParticleVec->end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);

        if (!pReconstructedParticle->getTracks().empty() and pReconstructedParticle->getEnergy() > energyMostEnergeticChargedPfo)
        {
            pMostEnergeticChargedPfo = pReconstructedParticle;
            energyMostEnergeticChargedPfo = pReconstructedParticle->getEnergy();
        }
    }
}

//===========================================================

void JetAnalysis::FindEnergyAroundPfo(ParticleVector *pParticleVector, const EVENT::ReconstructedParticle *pMostEnergeticChargedPfo, float &energyAroundMostEnergeticChargedPfo) const
{
    energyAroundMostEnergeticChargedPfo = 0.f;
    float pfoX(0.f), pfoY(0.f), pfoZ(0.f);
    this->FindPfoPosition(pMostEnergeticChargedPfo, pfoX, pfoY, pfoZ);
    TVector3 pfoPosition(pfoX, pfoY, pfoZ);

    const float pfoPx(pMostEnergeticChargedPfo->getMomentum()[0]);
    const float pfoPy(pMostEnergeticChargedPfo->getMomentum()[1]);
    const float pfoPz(pMostEnergeticChargedPfo->getMomentum()[2]);

    TVector3 pfoP(pfoPx,pfoPy,pfoPz);
    TVector3 unitPfoP(pfoP.Unit());
    EVENT::ClusterVec clusters;

    for (ParticleVector::const_iterator partIt = pParticleVector->begin(); partIt != pParticleVector->end(); partIt++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*partIt);
        clusters.insert(clusters.end(), pReconstructedParticle->getClusters().begin(), pReconstructedParticle->getClusters().end());
    }

    for (EVENT::ClusterVec::const_iterator clusIt = clusters.begin(); clusIt != clusters.end(); clusIt++)
    {
        const EVENT::Cluster *pCluster(*clusIt);
        const float pfoXCandidate(pCluster->getPosition()[0]);
        const float pfoYCandidate(pCluster->getPosition()[1]);
        const float pfoZCandidate(pCluster->getPosition()[2]);
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

void JetAnalysis::FindPfoPosition(const EVENT::ReconstructedParticle *pReconstructedParticle, float &x, float &y, float &z) const
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

void JetAnalysis::IsEventAppropriate()
{
    std::cout << "1) Checking event" << std::endl;
    m_pVariables->Print();

    if (!(m_pVariables->GetRecoilMass() >= 250 and m_pVariables->GetTransverseMomentum() >= 40 and m_pVariables->GetTransverseEnergy() >= 150 and std::fabs(m_pVariables->GetCosThetaMissing()) < 0.99f and std::fabs(m_pVariables->GetCosThetaMostEnergeticTrack()) < 0.99f and m_pVariables->GetEnergyAroundMostEnergeticPfo() >= 2 and m_pVariables->GetY34() < 3.5))
    {
        m_pVariables->SetAppropriateEvent(false);
        return;
    }

    std::cout << "2) Checking event" << std::endl;
    if (m_pVariables->GetLowestEnergyJet() < 10.f)
    {
        m_pVariables->SetAppropriateEvent(false);
        return;
    }

    if (m_pVariables->GetLowestNParticlesJets() < 3)
    {
        m_pVariables->SetAppropriateEvent(false);
        return;
    }

    if (m_pVariables->GetLowestNChargedParticlesJets() < 3)
    {
        m_pVariables->SetAppropriateEvent(false);
        return;
    }

    m_pVariables->SetAppropriateEvent(true);
    return;
}

//===========================================================

void JetAnalysis::IsEventWW()
{
    if (m_pVariables->GetInvMassWVectors().size() != 2)
    {
        m_pVariables->SetIsEventWW(false);
        return;
    }

    std::cout << "W Vector Right Size" << std::endl;
    std::cout << "m_pVariables->GetInvMassWVectors().at(0) : " << m_pVariables->GetInvMassWVectors().at(0) << std::endl;
    std::cout << "m_pVariables->GetInvMassWVectors().at(1) : " << m_pVariables->GetInvMassWVectors().at(1) << std::endl;


    if (60 < m_pVariables->GetInvMassWVectors().at(0) and m_pVariables->GetInvMassWVectors().at(0) < 88 and 60 < m_pVariables->GetInvMassWVectors().at(1) and m_pVariables->GetInvMassWVectors().at(1) < 88)
    {
        m_pVariables->SetIsEventWW(true);
        std::cout << "Good WW Event" << std::endl;
    }

    return;
}

//===========================================================

void JetAnalysis::IsEventZZ()
{
    if (m_pVariables->GetInvMassZVectors().size() != 2)
    {
        m_pVariables->SetIsEventZZ(false);
        return;
    }

    if (85 < m_pVariables->GetInvMassZVectors().at(0) and m_pVariables->GetInvMassZVectors().at(0) < 100 and 85 < m_pVariables->GetInvMassZVectors().at(1) and m_pVariables->GetInvMassZVectors().at(1) < 100)
    {
        m_pVariables->SetIsEventZZ(true);
    }

    return;
}

//===========================================================

void JetAnalysis::DefineVariablesOfInterest()
{
    float invariantMassSystem(std::numeric_limits<float>::max());
    this->FindInvariantMass(m_JetVector,invariantMassSystem);
    m_pVariables->SetInvariantMassSystem(invariantMassSystem);

    float cosThetaStarWBoson(0.f);
    this->CalculateCosThetaStar(m_WVector1,m_WVector2,cosThetaStarWBoson);
    m_pVariables->SetCosThetaStarWBosons(cosThetaStarWBoson);

    float cosThetaStarZBoson(0.f);
    this->CalculateCosThetaStar(m_ZVector1,m_ZVector2,cosThetaStarZBoson);
    m_pVariables->SetCosThetaStarZBosons(cosThetaStarZBoson);

    if (m_WVector1.size() != 2 or m_WVector2.size() != 2 or m_ZVector1.size() != 2 or m_ZVector2.size() != 2)
    {
        std::cout << "Problem with jet pairing.  Either more or less jets associated to bosons than 2.  Unable to work out cos theta star jets.  Returning now." << std::endl;
        return;
    }

    ParticleVector jetVectorQ1, jetVectorQ2;
    float cosThetaStarWJet(0.f), cosThetaStarZJet(0.f);
    FloatVector cosThetaStarWJets, cosThetaStarZJets;

    jetVectorQ1.push_back(m_WVector1.at(0));
    jetVectorQ2.push_back(m_WVector1.at(1));
    this->CalculateCosThetaStar(jetVectorQ1,jetVectorQ2,cosThetaStarWJet);
    cosThetaStarWJets.push_back(cosThetaStarWJet);
    jetVectorQ1.clear();
    jetVectorQ2.clear();

    jetVectorQ1.push_back(m_WVector2.at(0));
    jetVectorQ2.push_back(m_WVector2.at(1));
    this->CalculateCosThetaStar(jetVectorQ1,jetVectorQ2,cosThetaStarWJet);
    cosThetaStarWJets.push_back(cosThetaStarWJet);
    jetVectorQ1.clear();
    jetVectorQ2.clear();

    jetVectorQ1.push_back(m_ZVector1.at(0));
    jetVectorQ2.push_back(m_ZVector1.at(1));
    this->CalculateCosThetaStar(jetVectorQ1,jetVectorQ2,cosThetaStarZJet);
    cosThetaStarZJets.push_back(cosThetaStarZJet);
    jetVectorQ1.clear();
    jetVectorQ2.clear();

    jetVectorQ1.push_back(m_ZVector2.at(0));
    jetVectorQ2.push_back(m_ZVector2.at(1));
    this->CalculateCosThetaStar(jetVectorQ1,jetVectorQ2,cosThetaStarZJet);
    cosThetaStarZJets.push_back(cosThetaStarZJet);
    jetVectorQ1.clear();
    jetVectorQ2.clear();

    m_pVariables->SetCosThetaStarWJets(cosThetaStarWJets);
    m_pVariables->SetCosThetaStarZJets(cosThetaStarZJets);
}

//===========================================================

void JetAnalysis::CalculateCosThetaStar(ParticleVector objectOfInterest, ParticleVector referenceFrameObjects, float &cosThetaStar) const 
{
    cosThetaStar = -1.f;
    TLorentzVector objectOfInterest4Vec, referenceFrameObjects4Vec;

    this->DefineEnergy4Vec(objectOfInterest, objectOfInterest4Vec);
    this->DefineEnergy4Vec(referenceFrameObjects, referenceFrameObjects4Vec);

    TLorentzVector diBoson = objectOfInterest4Vec + referenceFrameObjects4Vec;
    TVector3 boostvector = -diBoson.BoostVector();
    objectOfInterest4Vec.Boost(boostvector);
    cosThetaStar = std::fabs(objectOfInterest4Vec.Vect().Dot(diBoson.Vect()) / (objectOfInterest4Vec.Vect().Mag() * diBoson.Vect().Mag()));
}

//===========================================================

void JetAnalysis::DefineEnergy4Vec(ParticleVector &jetVector, TLorentzVector &tLorentzVector) const 
{
    float px(0.f), py(0.f), pz(0.f), E(0.f);

    for (ParticleVector::const_iterator iter = jetVector.begin(); iter != jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
        pz += pReconstructedParticle->getMomentum()[2];
        E += pReconstructedParticle->getEnergy();
    }

    tLorentzVector.SetPx(px);
    tLorentzVector.SetPy(py);
    tLorentzVector.SetPz(pz);
    tLorentzVector.SetE(E);
}

//===========================================================
