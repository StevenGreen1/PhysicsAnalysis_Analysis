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
    m_wBosonMass(80.385f),
    m_zBosonMass(91.1876f),
    m_crossingAngle(0.01),
    m_eventEnergyMC(variables->GetEventEnergyMC()),
    m_coneAngle(10.0),
    m_y34(std::numeric_limits<double>::max())
{
    if (pLCCollection->getNumberOfElements() == 4)
    {
        m_jetVector.push_back(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(0)));
        m_jetVector.push_back(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(1)));
        m_jetVector.push_back(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(2)));
        m_jetVector.push_back(dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(3)));

        this->ProcessJets(pLCCollection);
        this->ProcessBosons();
    }
}

//===========================================================

JetAnalysis::~JetAnalysis()
{
    m_jetVector.clear();
    m_wVector1.clear();
    m_wVector2.clear();
    m_zVector1.clear();
    m_zVector2.clear();
    m_particleToBTag.clear();
    m_particleToCTag.clear();
}

//===========================================================

void JetAnalysis::ProcessJets(const EVENT::LCCollection *pLCCollection)
{
    this->CalculateJetClusteringVariableY34(pLCCollection);
    this->CalculateFlavourTagging(pLCCollection);
    this->JetVariables();
    this->JetPairing();
}

//===========================================================

void JetAnalysis::ProcessBosons()
{
    this->CalculateAcolinearities();
    this->CalculateBosonEnergies();
    this->CalculateBosonMomenta();
    this->CalculateTransverseMomentum();
    this->CalculateBosonCosTheta();
    this->CalculateTransverseEnergy();
    this->CalculateCosThetaMissingMomentum();
    this->CalculateCosThetaMostEnergeticTrack();
    this->CalculateRecoilMass();
    this->CalculateEnergyInConeAroundMostEnergeticPfo();
    this->CalculateBosonNPFOs();
    this->CalculateFlavourTaggingInformation();

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
    PIDHandler pidHandler(pLCCollection);
    const int algIndexYij(pidHandler.getAlgorithmID("yth"));
    const ParticleID &particleID(pidHandler.getParticleID(pLCCollection->getElementAt(0), algIndexYij));
    std::string stringY34("y34");
    std::string stringY45("y45");
    const double parameterY34(particleID.getParameters()[pidHandler.getParameterIndex(algIndexYij, stringY34)]);
    const double parameterY45(particleID.getParameters()[pidHandler.getParameterIndex(algIndexYij, stringY45)]);

    const double minusLogY34Separation((parameterY34 > std::numeric_limits<double>::epsilon()) ? - log10(parameterY34) : 0.0);
    const double minusLogY45Separation((parameterY45 > std::numeric_limits<double>::epsilon()) ? - log10(parameterY45) : 0.0);

    m_pVariables->SetY34(minusLogY34Separation);
    m_pVariables->SetY45(minusLogY45Separation);
    m_y34 = minusLogY34Separation;
}

//===========================================================

void JetAnalysis::CalculateFlavourTagging(const EVENT::LCCollection *pLCCollection)
{
    PIDHandler pidHandler(pLCCollection);

    const int lcfiplusAlgID(pidHandler.getAlgorithmID("lcfiplus"));
    const int bTagIndex(pidHandler.getParameterIndex(lcfiplusAlgID, "BTag"));
    const int cTagIndex(pidHandler.getParameterIndex(lcfiplusAlgID, "CTag"));

    DoubleVector bTagInfoJets;
    DoubleVector cTagInfoJets;

    for (ParticleVector::iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        const EVENT::ParticleID &particleID = pidHandler.getParticleID(const_cast<EVENT::ReconstructedParticle *>(pReconstructedParticle), lcfiplusAlgID);

        bTagInfoJets.push_back(particleID.getParameters().at(bTagIndex));
        cTagInfoJets.push_back(particleID.getParameters().at(cTagIndex));
        m_particleToBTag.insert(std::make_pair(pReconstructedParticle, particleID.getParameters().at(bTagIndex)));
        m_particleToCTag.insert(std::make_pair(pReconstructedParticle, particleID.getParameters().at(cTagIndex)));
    }

    m_pVariables->SetBTagForJets(bTagInfoJets);
    m_pVariables->SetCTagForJets(cTagInfoJets);
}

//===========================================================

void JetAnalysis::JetVariables()
{
    DoubleVector energyJets, momentumJets, transverseMomentumJets, cosThetaJets;
    IntVector nParticlesJets, nChargedParticlesJets;

    for (ParticleVector::iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        const double px(pReconstructedParticle->getMomentum()[0]);
        const double py(pReconstructedParticle->getMomentum()[1]);
        const double pz(pReconstructedParticle->getMomentum()[2]);
        const double energy(pReconstructedParticle->getEnergy());
        const double p(sqrt(px * px + py * py + pz * pz));
        const double pT(energy * sqrt(px*px + py*py) / p);
        const double cosTheta(pz/p);

        energyJets.push_back(energy);
        momentumJets.push_back(p);
        transverseMomentumJets.push_back(pT);
        cosThetaJets.push_back(cosTheta);

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
    m_pVariables->SetMomentumJets(momentumJets);
    m_pVariables->SetTransverseMomentumJets(transverseMomentumJets);
    m_pVariables->SetCosThetaJets(cosThetaJets);
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

    double bestWMetric(std::numeric_limits<double>::max()), bestZMetric(std::numeric_limits<double>::max());
    DoubleVector bestWMasses, bestZMasses;

    for (std::vector<IntVector>::iterator iter = combinations.begin(); iter != combinations.end(); iter++)
    {
        IntVector combination(*iter);

        ParticleVector trialPair1, trialPair2;
        trialPair1.push_back(m_jetVector.at(combination.at(0)));
        trialPair1.push_back(m_jetVector.at(combination.at(1)));
        trialPair2.push_back(m_jetVector.at(combination.at(2)));
        trialPair2.push_back(m_jetVector.at(combination.at(3)));

        double invariantMass1(0.0), invariantMass2(0.0);

        this->FindInvariantMass(trialPair1, invariantMass1);
        this->FindInvariantMass(trialPair2, invariantMass2);

        const double wMetric((fabs(invariantMass1-m_wBosonMass))*fabs(invariantMass2-m_wBosonMass));
        const double zMetric((fabs(invariantMass1-m_zBosonMass))*fabs(invariantMass2-m_zBosonMass));

        if (wMetric < bestWMetric)
        {
            bestWMasses.clear();
            m_pVariables->SetJetCombinationW(combination);

            if (invariantMass1 > invariantMass2)
            {
                m_wVector1 = trialPair1;
                m_wVector2 = trialPair2;
                bestWMasses.push_back(invariantMass1);
                bestWMasses.push_back(invariantMass2);
            }
            else
            {
                m_wVector1 = trialPair2;
                m_wVector2 = trialPair1;
                bestWMasses.push_back(invariantMass2);
                bestWMasses.push_back(invariantMass1);
            }

            bestWMetric = wMetric;
        }

        if (zMetric < bestZMetric)
        {
            bestZMasses.clear();
            m_pVariables->SetJetCombinationZ(combination);

            if (invariantMass1 > invariantMass2)
            {
                m_zVector1 = trialPair1;
                m_zVector2 = trialPair2;
                bestZMasses.push_back(invariantMass1);
                bestZMasses.push_back(invariantMass2);
            }
            else
            {
                m_zVector1 = trialPair2;
                m_zVector2 = trialPair1;
                bestZMasses.push_back(invariantMass2);
                bestZMasses.push_back(invariantMass1);
            }

            bestZMetric = zMetric;
        }
    }
    m_pVariables->SetInvMassWVectors(bestWMasses);
    m_pVariables->SetInvMassZVectors(bestZMasses);
}

//===========================================================

void JetAnalysis::CalculateBosonEnergies() 
{
    m_pVariables->SetEnergyBosonW1(m_wVector1.at(0)->getEnergy() + m_wVector1.at(1)->getEnergy());
    m_pVariables->SetEnergyBosonW2(m_wVector2.at(0)->getEnergy() + m_wVector2.at(1)->getEnergy());
    m_pVariables->SetEnergyBosonZ1(m_zVector1.at(0)->getEnergy() + m_zVector1.at(1)->getEnergy());
    m_pVariables->SetEnergyBosonZ2(m_zVector2.at(0)->getEnergy() + m_zVector2.at(1)->getEnergy());
}

//===========================================================

void JetAnalysis::CalculateBosonNPFOs() 
{
    int nPfosBosonW1(0), nPfosBosonW2(0), nPfosBosonZ1(0), nPfosBosonZ2(0);

    this->CalculateNumberOfPfos(m_wVector1, nPfosBosonW1);
    m_pVariables->SetNPfosBosonW1(nPfosBosonW1);

    this->CalculateNumberOfPfos(m_wVector2, nPfosBosonW2);
    m_pVariables->SetNPfosBosonW2(nPfosBosonW2);

    this->CalculateNumberOfPfos(m_zVector1, nPfosBosonZ1);
    m_pVariables->SetNPfosBosonZ1(nPfosBosonZ1);

    this->CalculateNumberOfPfos(m_zVector2, nPfosBosonZ2);
    m_pVariables->SetNPfosBosonZ2(nPfosBosonZ2);
}

//===========================================================

void JetAnalysis::CalculateNumberOfPfos(ParticleVector particleVector, int &nPfos)
{
    nPfos = 0;

    for (ParticleVector::iterator iter = particleVector.begin(); iter != particleVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        nPfos +=  pReconstructedParticle->getParticles().size();
    }
}

//===========================================================

void JetAnalysis::CalculateFlavourTaggingInformation() 
{
    const double bTagW1a(m_particleToBTag.at(m_wVector1.at(0)));
    const double bTagW1b(m_particleToBTag.at(m_wVector1.at(1)));
    const double bTagW2a(m_particleToBTag.at(m_wVector2.at(0)));
    const double bTagW2b(m_particleToBTag.at(m_wVector2.at(1)));
    const double cTagW1a(m_particleToCTag.at(m_wVector1.at(0)));
    const double cTagW1b(m_particleToCTag.at(m_wVector1.at(1)));
    const double cTagW2a(m_particleToCTag.at(m_wVector2.at(0)));
    const double cTagW2b(m_particleToCTag.at(m_wVector2.at(1)));

    const double bTagZ1a(m_particleToBTag.at(m_zVector1.at(0)));
    const double bTagZ1b(m_particleToBTag.at(m_zVector1.at(1)));
    const double bTagZ2a(m_particleToBTag.at(m_zVector2.at(0)));
    const double bTagZ2b(m_particleToBTag.at(m_zVector2.at(1)));
    const double cTagZ1a(m_particleToCTag.at(m_zVector1.at(0)));
    const double cTagZ1b(m_particleToCTag.at(m_zVector1.at(1)));
    const double cTagZ2a(m_particleToCTag.at(m_zVector2.at(0)));
    const double cTagZ2b(m_particleToCTag.at(m_zVector2.at(1)));

    if (bTagW1a > bTagW1b)
    {
        m_pVariables->SetMaxBTagForBosonW1(bTagW1a);
        m_pVariables->SetMinBTagForBosonW1(bTagW1b);
    }
    else
    {
        m_pVariables->SetMaxBTagForBosonW1(bTagW1b);
        m_pVariables->SetMinBTagForBosonW1(bTagW1a);
    }

    if (bTagW2a > bTagW2b)
    {
        m_pVariables->SetMaxBTagForBosonW2(bTagW2a);
        m_pVariables->SetMinBTagForBosonW2(bTagW2b);
    }
    else
    {
        m_pVariables->SetMaxBTagForBosonW2(bTagW2b);
        m_pVariables->SetMinBTagForBosonW2(bTagW2a);
    }

    if (cTagW1a > cTagW1b)
    {
        m_pVariables->SetMaxCTagForBosonW1(cTagW1a);
        m_pVariables->SetMinCTagForBosonW1(cTagW1b);
    }
    else
    {
        m_pVariables->SetMaxCTagForBosonW1(cTagW1b);
        m_pVariables->SetMinCTagForBosonW1(cTagW1a);
    }

    if (cTagW2a > cTagW2b)
    {
        m_pVariables->SetMaxCTagForBosonW2(cTagW2a);
        m_pVariables->SetMinCTagForBosonW2(cTagW2b);
    }
    else
    {
        m_pVariables->SetMaxCTagForBosonW2(cTagW2b);
        m_pVariables->SetMinCTagForBosonW2(cTagW2a);
    }

    if (bTagZ1a > bTagZ1b)
    {
        m_pVariables->SetMaxBTagForBosonZ1(bTagZ1a);
        m_pVariables->SetMinBTagForBosonZ1(bTagZ1b);
    }
    else
    {
        m_pVariables->SetMaxBTagForBosonZ1(bTagZ1b);
        m_pVariables->SetMinBTagForBosonZ1(bTagZ1a);
    }

    if (bTagZ2a > bTagZ2b)
    {
        m_pVariables->SetMaxBTagForBosonZ2(bTagZ2a);
        m_pVariables->SetMinBTagForBosonZ2(bTagZ2b);
    }
    else
    {
        m_pVariables->SetMaxBTagForBosonZ2(bTagZ2b);
        m_pVariables->SetMinBTagForBosonZ2(bTagZ2a);
    }

    if (cTagZ1a > cTagZ1b)
    {
        m_pVariables->SetMaxCTagForBosonZ1(cTagZ1a);
        m_pVariables->SetMinCTagForBosonZ1(cTagZ1b);
    }
    else
    {
        m_pVariables->SetMaxCTagForBosonZ1(cTagZ1b);
        m_pVariables->SetMinCTagForBosonZ1(cTagZ1a);
    }

    if (cTagZ2a > cTagZ2b)
    {
        m_pVariables->SetMaxCTagForBosonZ2(cTagZ2a);
        m_pVariables->SetMinCTagForBosonZ2(cTagZ2b);
    }
    else
    {
        m_pVariables->SetMaxCTagForBosonZ2(cTagZ2b);
        m_pVariables->SetMinCTagForBosonZ2(cTagZ2a);
    }
}

//===========================================================

void JetAnalysis::CalculateAcolinearities()
{
    double acolinearityJetsW1(std::numeric_limits<double>::max());
    this->CalculateAcolinearity(m_wVector1.at(0), m_wVector1.at(1), acolinearityJetsW1);
    m_pVariables->SetAcolinearityJetsW1(acolinearityJetsW1);

    double acolinearityJetsW2(std::numeric_limits<double>::max());
    this->CalculateAcolinearity(m_wVector2.at(0), m_wVector2.at(1), acolinearityJetsW2);
    m_pVariables->SetAcolinearityJetsW2(acolinearityJetsW2);

    double acolinearityJetsZ1(std::numeric_limits<double>::max());
    this->CalculateAcolinearity(m_zVector1.at(0), m_zVector1.at(1), acolinearityJetsZ1);
    m_pVariables->SetAcolinearityJetsZ1(acolinearityJetsZ1);

    double acolinearityJetsZ2(std::numeric_limits<double>::max());
    this->CalculateAcolinearity(m_zVector1.at(0), m_zVector1.at(1), acolinearityJetsZ2);
    m_pVariables->SetAcolinearityJetsZ2(acolinearityJetsZ2);

    double acolinearityBosonW(std::numeric_limits<double>::max());
    this->CalculateBosonAcolinearity(m_wVector1, m_wVector2, acolinearityBosonW);
    m_pVariables->SetAcolinearityBosonsW(acolinearityBosonW);

    double acolinearityBosonZ(std::numeric_limits<double>::max());
    this->CalculateBosonAcolinearity(m_zVector1, m_zVector2, acolinearityBosonZ);
    m_pVariables->SetAcolinearityBosonsZ(acolinearityBosonZ);
}

//===========================================================

void JetAnalysis::CalculateAcolinearity(const EVENT::ReconstructedParticle* pReconstructedParticle1, const EVENT::ReconstructedParticle* pReconstructedParticle2, double &acolinearity) const 
{
    const double px1(pReconstructedParticle1->getMomentum()[0]);
    const double py1(pReconstructedParticle1->getMomentum()[1]);
    const double pz1(pReconstructedParticle1->getMomentum()[2]);
    TVector3 p1(px1, py1, pz1);

    const double px2(pReconstructedParticle2->getMomentum()[0]);
    const double py2(pReconstructedParticle2->getMomentum()[1]);
    const double pz2(pReconstructedParticle2->getMomentum()[2]);
    TVector3 p2(px2, py2, pz2);

    const double openingAngle(acos(p1.Unit() * p2.Unit()) * 180.0 / M_PI);
    acolinearity = 180.0 - openingAngle;
}

//===========================================================

void JetAnalysis::CalculateBosonAcolinearity(ParticleVector particleVector1, ParticleVector particleVector2, double &acolinearity) const
{
    double px1(0.0), py1(0.0), pz1(0.0), px2(0.0), py2(0.0), pz2(0.0);

    for (ParticleVector::const_iterator iter = particleVector1.begin(); iter != particleVector1.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        px1 += pReconstructedParticle->getMomentum()[0];
        py1 += pReconstructedParticle->getMomentum()[1];
        pz1 += pReconstructedParticle->getMomentum()[2];
    }

    TVector3 p1(px1, py1, pz1);

    for (ParticleVector::const_iterator iter = particleVector2.begin(); iter != particleVector2.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        px2 += pReconstructedParticle->getMomentum()[0];
        py2 += pReconstructedParticle->getMomentum()[1];
        pz2 += pReconstructedParticle->getMomentum()[2];
    }

    TVector3 p2(px2, py2, pz2);

    const double openingAngle(acos(p1.Unit() * p2.Unit()) * 180.0 / M_PI);
    acolinearity = 180.0 - openingAngle;
}

//===========================================================

void JetAnalysis::FindInvariantMass(ParticleVector &jetVector, double &invariantMass) const
{
    double pxTot(0.0), pyTot(0.0), pzTot(0.0), energyTot(0.0);

    for (ParticleVector::iterator iter = jetVector.begin(); iter != jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        const double px(pReconstructedParticle->getMomentum()[0]);
        const double py(pReconstructedParticle->getMomentum()[1]);
        const double pz(pReconstructedParticle->getMomentum()[2]);
        const double energy(pReconstructedParticle->getEnergy());

        pxTot += px;
        pyTot += py;
        pzTot += pz;
        energyTot += energy;
    }

    invariantMass = sqrt(energyTot*energyTot - pxTot*pxTot - pyTot*pyTot - pzTot*pzTot);
}

//===========================================================

void JetAnalysis::CalculateTransverseEnergy()
{
    double px(0.0), py(0.0), pz(0.0), energy(0.0);

    for (ParticleVector::iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
        pz += pReconstructedParticle->getMomentum()[2];
        energy += pReconstructedParticle->getEnergy();
    }

    const double p(sqrt(px * px + py * py + pz * pz));
    const double transverseEnergy(energy * sqrt(px*px + py*py) / p);
    m_pVariables->SetTransverseEnergy(transverseEnergy);

    double transverseEnergyBosonW1(0.0), transverseEnergyBosonW2(0.0), transverseEnergyBosonZ1(0.0), transverseEnergyBosonZ2(0.0);

    this->CalculateTransverseEnergyObject(m_wVector1, transverseEnergyBosonW1);
    m_pVariables->SetTransverseEnergyBosonW1(transverseEnergyBosonW1);

    this->CalculateTransverseEnergyObject(m_wVector2, transverseEnergyBosonW2);
    m_pVariables->SetTransverseEnergyBosonW2(transverseEnergyBosonW2);

    this->CalculateTransverseEnergyObject(m_zVector1, transverseEnergyBosonZ1);
    m_pVariables->SetTransverseEnergyBosonZ1(transverseEnergyBosonZ1);

    this->CalculateTransverseEnergyObject(m_zVector2, transverseEnergyBosonZ2);
    m_pVariables->SetTransverseEnergyBosonZ2(transverseEnergyBosonZ2);
}

//===========================================================

void JetAnalysis::CalculateTransverseEnergyObject(ParticleVector particleVector, double &transverseEnergy)
{
    transverseEnergy = 0.0;
    double px(0.0), py(0.0), pz(0.0), energy(0.0);

    for (ParticleVector::iterator iter = particleVector.begin(); iter != particleVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
        pz += pReconstructedParticle->getMomentum()[2];
        energy += pReconstructedParticle->getEnergy();
    }

    const double p(sqrt(px * px + py * py + pz * pz));
    transverseEnergy += energy * sqrt(px*px + py*py) / p;
}

//===========================================================

void JetAnalysis::CalculateTransverseMomentum()
{
    double px(0.0), py(0.0);

    for (ParticleVector::iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
    }

    const double transverseMomentum(sqrt(px*px + py*py));
    m_pVariables->SetTransverseMomentum(transverseMomentum);

    double transverseMomentumBosonW1(0.0), transverseMomentumBosonW2(0.0), transverseMomentumBosonZ1(0.0), transverseMomentumBosonZ2(0.0);

    this->CalculateTransverseMomentumObject(m_wVector1, transverseMomentumBosonW1);
    m_pVariables->SetTransverseMomentumBosonW1(transverseMomentumBosonW1);

    this->CalculateTransverseMomentumObject(m_wVector2, transverseMomentumBosonW2);
    m_pVariables->SetTransverseMomentumBosonW2(transverseMomentumBosonW2);

    this->CalculateTransverseMomentumObject(m_zVector1, transverseMomentumBosonZ1);
    m_pVariables->SetTransverseMomentumBosonZ1(transverseMomentumBosonZ1);

    this->CalculateTransverseMomentumObject(m_zVector2, transverseMomentumBosonZ2);
    m_pVariables->SetTransverseMomentumBosonZ2(transverseMomentumBosonZ2);
}

//===========================================================

void JetAnalysis::CalculateTransverseMomentumObject(ParticleVector particleVector, double &transverseMomentum)
{
    transverseMomentum = 0.0;
    double px(0.0), py(0.0);

    for (ParticleVector::iterator iter = particleVector.begin(); iter != particleVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
    }

    transverseMomentum = sqrt(px*px + py*py);
}

//===========================================================

void JetAnalysis::CalculateBosonMomenta()
{
    double momentumBosonW1(0.0), momentumBosonW2(0.0), momentumBosonZ1(0.0), momentumBosonZ2(0.0);

    this->CalculateMomentumObject(m_wVector1, momentumBosonW1);
    m_pVariables->SetMomentumBosonW1(momentumBosonW1);

    this->CalculateMomentumObject(m_wVector2, momentumBosonW2);
    m_pVariables->SetMomentumBosonW2(momentumBosonW2);

    this->CalculateMomentumObject(m_zVector1, momentumBosonZ1);
    m_pVariables->SetMomentumBosonZ1(momentumBosonZ1);

    this->CalculateMomentumObject(m_zVector2, momentumBosonZ2);
    m_pVariables->SetMomentumBosonZ2(momentumBosonZ2);
}

//===========================================================

void JetAnalysis::CalculateMomentumObject(ParticleVector particleVector, double &momentum)
{   
    momentum = 0.0;
    double px(0.0), py(0.0), pz(0.0);
    
    for (ParticleVector::iterator iter = particleVector.begin(); iter != particleVector.end(); iter++)
    {   
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
        pz += pReconstructedParticle->getMomentum()[2];
    }
    
    momentum = sqrt(px*px + py*py + pz*pz);
}

//===========================================================

void JetAnalysis::CalculateBosonCosTheta()
{
    double cosThetaBosonW1(0.0), cosThetaBosonW2(0.0), cosThetaBosonZ1(0.0), cosThetaBosonZ2(0.0);
    
    this->CalculateCosThetaObject(m_wVector1, cosThetaBosonW1);
    m_pVariables->SetCosThetaBosonW1(cosThetaBosonW1);
    
    this->CalculateCosThetaObject(m_wVector2, cosThetaBosonW2);
    m_pVariables->SetCosThetaBosonW2(cosThetaBosonW2);
    
    this->CalculateCosThetaObject(m_zVector1, cosThetaBosonZ1);
    m_pVariables->SetCosThetaBosonZ1(cosThetaBosonZ1);
    
    this->CalculateCosThetaObject(m_zVector2, cosThetaBosonZ2);
    m_pVariables->SetCosThetaBosonZ2(cosThetaBosonZ2);
}

//===========================================================

void JetAnalysis::CalculateCosThetaObject(ParticleVector particleVector, double &cosTheta)
{
    cosTheta = 0.0;
    double px(0.0), py(0.0), pz(0.0);

    for (ParticleVector::iterator iter = particleVector.begin(); iter != particleVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
        pz += pReconstructedParticle->getMomentum()[2];
    }

    cosTheta = pz / sqrt(px*px + py*py + pz*pz);
}

//===========================================================

void JetAnalysis::CalculateCosThetaMissingMomentum() 
{
    double pxMis(0.0);
    double pyMis(0.0);
    double pzMis(0.0);
    this->FindMissingMomentum(pxMis, pyMis, pzMis);
    const double pMis(sqrt(pxMis * pxMis + pyMis * pyMis + pzMis * pzMis));
    m_pVariables->SetCosThetaMissing(pzMis / pMis);
}

//===========================================================

void JetAnalysis::FindMissingMomentum(double &pxMis, double &pyMis, double &pzMis) const
{
    for (ParticleVector::const_iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        pxMis -= pReconstructedParticle->getMomentum()[0];
        pyMis -= pReconstructedParticle->getMomentum()[1];
        pzMis -= pReconstructedParticle->getMomentum()[2];
    }
    const double xFromCrossingAngle(m_eventEnergyMC * sin(m_crossingAngle));
    pxMis + xFromCrossingAngle;
}

//===========================================================

void JetAnalysis::CalculateCosThetaMostEnergeticTrack()
{
    EVENT::TrackVec tracksMostEnergeticChargedPfo;
    this->FindMostEnergeticTrack(tracksMostEnergeticChargedPfo);
    double largestCosThetaTrack(0.0);

    for (EVENT::TrackVec::iterator iter = tracksMostEnergeticChargedPfo.begin(); iter != tracksMostEnergeticChargedPfo.end(); iter++)
    {
        EVENT::Track *pTrack(*iter);
        const double tanThetaTrack(1.0 / pTrack->getTanLambda());
        const double cosThetaTrack(cos(atan(tanThetaTrack)));

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

    for (ParticleVector::const_iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pReconstructedParticle->getParticles().begin(), pReconstructedParticle->getParticles().end());
    }

    double energyMostEnergeticChargedPfo(0.0);

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
    const double xFromCrossingAngle(m_eventEnergyMC * sin(m_crossingAngle));
    TLorentzVector pInit(xFromCrossingAngle,0,0,m_eventEnergyMC);
    double px(0.0), py(0.0), pz(0.0), E(0.0);

    for (ParticleVector::const_iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        px += pReconstructedParticle->getMomentum()[0];
        py += pReconstructedParticle->getMomentum()[1];
        pz += pReconstructedParticle->getMomentum()[2];
        E += pReconstructedParticle->getEnergy();
    }

    TLorentzVector pVis(px,py,pz,E);
    TLorentzVector pMis(pInit - pVis);
    double recoilMass(pMis.M()); // Invairant Mass/Magnitude
    m_pVariables->SetRecoilMass(recoilMass);
}

//===========================================================

void JetAnalysis::CalculateEnergyInConeAroundMostEnergeticPfo()
{
    const EVENT::ReconstructedParticle *pMostEnergeticChargedPfo(NULL);
    this->FindMostEnergeticChargedParticle(pMostEnergeticChargedPfo);

    ParticleVector *pReconstructedParticleVec = new ParticleVector();
    for (ParticleVector::const_iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pReconstructedParticle->getParticles().begin(), pReconstructedParticle->getParticles().end());
    }

    double energyAroundMostEnergeticChargedPfo(0.0);
    this->FindEnergyAroundPfo(pReconstructedParticleVec, pMostEnergeticChargedPfo, energyAroundMostEnergeticChargedPfo);
    m_pVariables->SetEnergyAroundMostEnergeticPfo(energyAroundMostEnergeticChargedPfo);
}

//===========================================================

void JetAnalysis::FindMostEnergeticChargedParticle(const EVENT::ReconstructedParticle *&pMostEnergeticChargedPfo) const
{
    ParticleVector *pReconstructedParticleVec = new ParticleVector();

    for (ParticleVector::const_iterator iter = m_jetVector.begin(); iter != m_jetVector.end(); iter++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*iter);
        pReconstructedParticleVec->insert(pReconstructedParticleVec->end(), pReconstructedParticle->getParticles().begin(), pReconstructedParticle->getParticles().end());
    }

    double energyMostEnergeticChargedPfo(0.0);

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

void JetAnalysis::FindEnergyAroundPfo(ParticleVector *pParticleVector, const EVENT::ReconstructedParticle *pMostEnergeticChargedPfo, double &energyAroundMostEnergeticChargedPfo) const
{
    energyAroundMostEnergeticChargedPfo = 0.0;
    double pfoX(0.0), pfoY(0.0), pfoZ(0.0);
    this->FindPfoPosition(pMostEnergeticChargedPfo, pfoX, pfoY, pfoZ);
    TVector3 pfoPosition(pfoX, pfoY, pfoZ);

    const double pfoPx(pMostEnergeticChargedPfo->getMomentum()[0]);
    const double pfoPy(pMostEnergeticChargedPfo->getMomentum()[1]);
    const double pfoPz(pMostEnergeticChargedPfo->getMomentum()[2]);

    TVector3 pfoP(pfoPx,pfoPy,pfoPz);
    TVector3 unitPfoP(pfoP.Unit());
    EVENT::ClusterVec clusters;

    EVENT::Cluster *pClusterOfInterest(NULL);

    for (ParticleVector::const_iterator partIt = pParticleVector->begin(); partIt != pParticleVector->end(); partIt++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle(*partIt);

        clusters.insert(clusters.end(), pReconstructedParticle->getClusters().begin(), pReconstructedParticle->getClusters().end());
    }

    for (EVENT::ClusterVec::const_iterator clusIt = clusters.begin(); clusIt != clusters.end(); clusIt++)
    {
        const EVENT::Cluster *pCluster(*clusIt);
        const double pfoXCandidate(pCluster->getPosition()[0]);
        const double pfoYCandidate(pCluster->getPosition()[1]);
        const double pfoZCandidate(pCluster->getPosition()[2]);
        TVector3 pfoPositionCandidate(pfoXCandidate,pfoYCandidate,pfoZCandidate);
        TVector3 pfoCentroidToPfoCandidate(pfoPositionCandidate - pfoPosition);
        TVector3 unitPfoCentroidToPfoCandidate(pfoCentroidToPfoCandidate.Unit());

        double cosTheta(std::numeric_limits<double>::max());
        double theta(std::numeric_limits<double>::max());

        if (fabs(unitPfoCentroidToPfoCandidate.x()) < std::numeric_limits<double>::epsilon() and fabs(unitPfoCentroidToPfoCandidate.y()) < std::numeric_limits<double>::epsilon() and fabs(unitPfoCentroidToPfoCandidate.z()) < std::numeric_limits<double>::epsilon())
        {
            cosTheta = 1.0;
            theta = 0.0;
        }
        else
        {
            cosTheta = unitPfoCentroidToPfoCandidate * unitPfoP; // Dot Product
            theta = acos(cosTheta) * 180.0 / M_PI;
        }

        if (m_coneAngle - theta > 0.0)
        {
            energyAroundMostEnergeticChargedPfo += pCluster->getEnergy();
        }
    }
}

//===========================================================

void JetAnalysis::FindPfoPosition(const EVENT::ReconstructedParticle *pReconstructedParticle, double &x, double &y, double &z) const
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    double pfoEnergy(0.0);

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
    if (!(m_pVariables->GetRecoilMass() >= 250 and m_pVariables->GetTransverseMomentum() >= 40 and m_pVariables->GetTransverseEnergy() >= 150 and fabs(m_pVariables->GetCosThetaMissing()) < 0.99f and fabs(m_pVariables->GetCosThetaMostEnergeticTrack()) < 0.99f and m_pVariables->GetEnergyAroundMostEnergeticPfo() >= 2 and m_pVariables->GetY34() < 3.5))
    {
        m_pVariables->SetAppropriateEvent(false);
        return;
    }

    if (m_pVariables->GetLowestEnergyJet() < 10.0)
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

    if (60 < m_pVariables->GetInvMassWVectors().at(0) and m_pVariables->GetInvMassWVectors().at(0) < 88 and 60 < m_pVariables->GetInvMassWVectors().at(1) and m_pVariables->GetInvMassWVectors().at(1) < 88)
    {
        m_pVariables->SetIsEventWW(true);
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
    double invariantMassSystem(std::numeric_limits<double>::max());
    this->FindInvariantMass(m_jetVector,invariantMassSystem);
    m_pVariables->SetInvariantMassSystem(invariantMassSystem);

    double cosThetaStarWBoson(0.0);
    this->CalculateCosThetaStar(m_wVector1,m_wVector2,cosThetaStarWBoson);
    m_pVariables->SetCosThetaStarWBosons(cosThetaStarWBoson);

    double cosThetaStarZBoson(0.0);
    this->CalculateCosThetaStar(m_zVector1,m_zVector2,cosThetaStarZBoson);
    m_pVariables->SetCosThetaStarZBosons(cosThetaStarZBoson);

    if (m_wVector1.size() != 2 or m_wVector2.size() != 2 or m_zVector1.size() != 2 or m_zVector2.size() != 2)
    {
        std::cout << "Problem with jet pairing.  Either more or less jets associated to bosons than 2.  Unable to work out cos theta star jets.  Returning now." << std::endl;
        return;
    }

    ParticleVector jetVectorQ1, jetVectorQ2;
    double cosThetaStarWJet(0.0), cosThetaStarZJet(0.0);
    DoubleVector cosThetaStarWJets, cosThetaStarZJets;

    jetVectorQ1.push_back(m_wVector1.at(0));
    jetVectorQ2.push_back(m_wVector1.at(1));
    this->CalculateCosThetaStar(jetVectorQ1,jetVectorQ2,cosThetaStarWJet);
    cosThetaStarWJets.push_back(cosThetaStarWJet);
    jetVectorQ1.clear();
    jetVectorQ2.clear();

    jetVectorQ1.push_back(m_wVector2.at(0));
    jetVectorQ2.push_back(m_wVector2.at(1));
    this->CalculateCosThetaStar(jetVectorQ1,jetVectorQ2,cosThetaStarWJet);
    cosThetaStarWJets.push_back(cosThetaStarWJet);
    jetVectorQ1.clear();
    jetVectorQ2.clear();

    jetVectorQ1.push_back(m_zVector1.at(0));
    jetVectorQ2.push_back(m_zVector1.at(1));
    this->CalculateCosThetaStar(jetVectorQ1,jetVectorQ2,cosThetaStarZJet);
    cosThetaStarZJets.push_back(cosThetaStarZJet);
    jetVectorQ1.clear();
    jetVectorQ2.clear();

    jetVectorQ1.push_back(m_zVector2.at(0));
    jetVectorQ2.push_back(m_zVector2.at(1));
    this->CalculateCosThetaStar(jetVectorQ1,jetVectorQ2,cosThetaStarZJet);
    cosThetaStarZJets.push_back(cosThetaStarZJet);
    jetVectorQ1.clear();
    jetVectorQ2.clear();

    m_pVariables->SetCosThetaStarWJets(cosThetaStarWJets);
    m_pVariables->SetCosThetaStarZJets(cosThetaStarZJets);
}

//===========================================================

void JetAnalysis::CalculateCosThetaStar(ParticleVector objectOfInterest, ParticleVector referenceFrameObjects, double &cosThetaStar) const 
{
    cosThetaStar = -1.0;
    TLorentzVector objectOfInterest4Vec, referenceFrameObjects4Vec;

    this->DefineEnergy4Vec(objectOfInterest, objectOfInterest4Vec);
    this->DefineEnergy4Vec(referenceFrameObjects, referenceFrameObjects4Vec);

    TLorentzVector diBoson = objectOfInterest4Vec + referenceFrameObjects4Vec;
    TVector3 boostvector = -diBoson.BoostVector();
    objectOfInterest4Vec.Boost(boostvector);
    cosThetaStar = fabs(objectOfInterest4Vec.Vect().Dot(diBoson.Vect()) / (objectOfInterest4Vec.Vect().Mag() * diBoson.Vect().Mag()));
}

//===========================================================

void JetAnalysis::DefineEnergy4Vec(ParticleVector &jetVector, TLorentzVector &tLorentzVector) const 
{
    double px(0.0), py(0.0), pz(0.0), E(0.0);

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
