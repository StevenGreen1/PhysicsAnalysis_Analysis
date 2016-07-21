/**
 *  @file   SelectionProcessor/src/MCAnalysis.cc
 *
 *  @brief  Implementation of the mc analysis class.
 *
 *  $Log: $
 */

#include "MCAnalysis.h"

//===========================================================

MCAnalysis::MCAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables):
    m_pVariables(variables),
    m_WBosonMass(80.385f),
    m_ZBosonMass(91.1876f),
    m_EventMCEnergy(1400.f),
    m_y34(std::numeric_limits<float>::max())
{
    for (unsigned int i = 6; i < 12; i++)
    {
        const EVENT::MCParticle *pMCParticle(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(i)));
        if (std::abs(pMCParticle->getPDG()) == 12)
        {
            m_NeutrinoMCParticleVector.push_back(pMCParticle);
        }
        else if (0 < std::abs(pMCParticle->getPDG()) and std::abs(pMCParticle->getPDG()) <= 5)
        {
            m_QuarkMCParticleVector.push_back(pMCParticle);
        }
    }

    if (m_NeutrinoMCParticleVector.size() == 2 and m_QuarkMCParticleVector == 4)
    {
        this->Process();
    }
}

//===========================================================

MCAnalysis::~MCAnalysis()
{
}

//===========================================================

void MCAnalysis::Process()
{
    this->QuarkPairing();

    this->CalculateMCTransverseMomentum();
    this->CalculateMCTransverseEnergy();
    this->CalculateMCCosThetaMissingMomentum();
    this->CalculateMCRecoilMass();
    this->IsEventWW();
    this->IsEventZZ();
    this->DefineVariablesOfInterest();
}

//===========================================================

void MCAnalysis::QuarkPairing()
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
        trialPair1.push_back(m_QuarkMCParticleVector.at(combination.at(0)));
        trialPair1.push_back(m_QuarkMCParticleVector.at(combination.at(1)));
        trialPair2.push_back(m_QuarkMCParticleVector.at(combination.at(2)));
        trialPair2.push_back(m_QuarkMCParticleVector.at(combination.at(3)));

        float invariantMass1(0.f), invariantMass2(0.f);

        this->FindMCInvariantMass(trialPair1, invariantMass1);
        this->FindMCInvariantMass(trialPair2, invariantMass2);

        const float wMetric((std::fabs(invariantMass1-m_WBosonMass))*std::fabs(invariantMass2-m_WBosonMass));
        const float zMetric((std::fabs(invariantMass1-m_ZBosonMass))*std::fabs(invariantMass2-m_ZBosonMass));

        if (wMetric < bestWMetric)
        {
            m_MCWVector1 = trialPair1;
            m_MCWVector2 = trialPair2;
            bestWMasses.clear();
            bestWMasses.push_back(invariantMass1);
            bestWMasses.push_back(invariantMass2);
            bestWMetric = wMetric;
        }

        if (zMetric < bestZMetric)
        {
            m_MCZVector1 = trialPair1;
            m_MCZVector2 = trialPair2;
            bestZMasses.clear();
            bestZMasses.push_back(invariantMass1);
            bestZMasses.push_back(invariantMass2);
            bestZMetric = zMetric;
        }
    }

    m_pVariables->SetMCInvMassWVectors(bestWMasses);
    m_pVariables->SetMCInvMassZVectors(bestZMasses);
}

//===========================================================

void MCAnalysis::FindMCInvariantMass(MCParticleVector &mcParticleVector, float &invariantMass) const
{
    float pxTot(0.f), pyTot(0.f), pzTot(0.f), energyTot(0.f);

    for (MCParticleVector::iterator iter = mcParticleVector.begin(); iter != mcParticleVector.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        const float px(pMCParticle->getMomentum()[0]);
        const float py(pMCParticle->getMomentum()[1]);
        const float pz(pMCParticle->getMomentum()[2]);
        const float energy(pMCParticle->getEnergy());

        pxTot += px;
        pyTot += py;
        pzTot += pz;
        energyTot += energy;
    }

    invariantMass = std::sqrt(energyTot*energyTot - pxTot*pxTot - pyTot*pyTot - pzTot*pzTot);
}

//===========================================================

void MCAnalysis::CalculateMCTransverseMomentum()
{
    float transverseMomentum(0.f);
    for (MCParticleVector::iterator iter = m_QuarkMCParticleVector.begin(); iter != m_QuarkMCParticleVector.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        const float px(pMCParticle->getMomentum()[0]);
        const float py(pMCParticle->getMomentum()[1]);
        const float pz(pMCParticle->getMomentum()[2]);
        const float p(std::sqrt(px * px + py * py + pz * pz));
        const float energy(pMCParticle->getEnergy());
        transverseMomentum += energy * std::sqrt(px*px + py*py) / p;
    }
    m_pVariables->SetMCTransverseMomentum(transverseMomentum);
}

//===========================================================

void MCAnalysis::CalculateMCTransverseEnergy()
{
    float transverseEnergy(0.f);
    for (MCParticleVector::iterator iter = m_QuarkMCParticleVector.begin(); iter != m_QuarkMCParticleVector.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        const float px(pMCParticle->getMomentum()[0]);
        const float py(pMCParticle->getMomentum()[1]);

        transverseEnergy += std::sqrt(px*px + py*py);
    }
    m_pVariables->SetMCTransverseEnergy(transverseEnergy);
}

//===========================================================

void MCAnalysis::CalculateMCCosThetaMissingMomentum()
{
    float pxMis(0.f), pyMis(0.f), pzMis(0.f);

    for (MCParticleVector::iterator iter = m_NeutrinoMCParticleVector.begin(); iter != m_NeutrinoMCParticleVector.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        pxMis += pMCParticle->getMomentum()[0];
        pyMis += pMCParticle->getMomentum()[1];
        pzMis += pMCParticle->getMomentum()[2];
    }

    const float pMis(std::sqrt(pxMis * pxMis + pyMis * pyMis + pzMis * pzMis));
    m_pVariables->SetMCCosThetaMissing(pzMis / pMis);
}

//===========================================================

void MCAnalysis::CalculateMCRecoilMass()
{
    const float xFromCrossingAngle(m_EventMCEnergy * sin(m_CrossingAngle));
    TLorentzVector pInit(xFromCrossingAngle,0,0,m_EventMCEnergy);
    float px(0.f), py(0.f), pz(0.f), E(0.f);

    for (MCParticleVector::const_iterator iter = m_QuarkMCParticleVector.begin(); iter != m_QuarkMCParticleVector.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        px += pMCParticle->getMomentum()[0];
        py += pMCParticle->getMomentum()[1];
        pz += pMCParticle->getMomentum()[2];
        E += pMCParticle->getEnergy();
    }

    TLorentzVector pVis(px,py,pz,E);
    TLorentzVector pMis(pInit - pVis);
    float recoilMass(pMis.M()); // Invairant Mass/Magnitude
    m_pVariables->SetMCRecoilMass(recoilMass);
}

//===========================================================

void MCAnalysis::IsMCEventWW()
{
    if (m_pVariables->GetMCInvMassWVectors().size() != 2)
    {
        m_pVariables->SetIsMCEventWW(false);
        return;
    }

    if (60 < m_pVariables->GetMCInvMassWVectors().at(0) and m_pVariables->GetMCInvMassWVectors().at(0) < 88 and 60 < m_pVariables->GetMCInvMassWVectors().at(1) and m_pVariables->GetMCInvMassWVectors().at(1) < 88)
    {
        m_pVariables->SetIsMCEventWW(true);
    }

    return;
}

//===========================================================

void MCAnalysis::IsMCEventZZ()
{
    if (m_pVariables->GetMCInvMassZVectors().size() != 2)
    {
        m_pVariables->SetIsMCEventZZ(false);
        return;
    }

    if (85 < m_pVariables->GetMCInvMassZVectors().at(0) and m_pVariables->GetMCInvMassZVectors().at(0) < 100 and 85 < m_pVariables->GetMCInvMassZVectors().at(1) and m_pVariables->GetMCInvMassZVectors().at(1) < 100)
    {
        m_pVariables->SetIsMCEventZZ(true);
    }

    return;
}

//===========================================================

void MCAnalysis::DefineVariablesOfInterest()
{
    float invariantMassQuarkSystem(std::numeric_limits<float>::max());
    this->FindMCInvariantMass(m_QuarkMCParticleVector,invariantMassQuarkSystem);
    m_pVariables->SetMCInvariantMassSystem(invariantMassSystem);











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

void MCAnalysis::CalculateCosThetaStar(ParticleVector objectOfInterest, ParticleVector referenceFrameObjects, float &cosThetaStar) const 
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

void MCAnalysis::DefineEnergy4Vec(ParticleVector &jetVector, TLorentzVector &tLorentzVector) const 
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
