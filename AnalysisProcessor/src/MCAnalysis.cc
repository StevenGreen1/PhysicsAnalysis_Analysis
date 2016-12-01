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
    m_wBosonMass(80.385f),
    m_zBosonMass(91.1876f),
    m_crossingAngle(0.01),
    m_eventEnergyMC(variables->GetEventEnergyMC()),
    m_y34(std::numeric_limits<double>::max())
{
    for (unsigned int i = 6; i < 12; i++)
    {
        const EVENT::MCParticle *pMCParticle(dynamic_cast<EVENT::MCParticle*>(pLCCollection->getElementAt(i)));
        if (std::abs(pMCParticle->getPDG()) == 12 or std::abs(pMCParticle->getPDG()) == 14 or std::abs(pMCParticle->getPDG()) == 16)
        {
            m_neutrinos.push_back(pMCParticle);
        }
        else if (0 < std::abs(pMCParticle->getPDG()) and std::abs(pMCParticle->getPDG()) <= 5)
        {
            m_quarks.push_back(pMCParticle);
        }
    }

    if (m_neutrinos.size() == 2 and m_quarks.size() == 4)
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
    this->SetMCQuarkMap();
    this->QuarkPairing();
    this->QuarkVariables();
    this->NeutrinoVariables();

    this->CalculateMCTransverseMomentum();
    this->CalculateMCTransverseEnergy();
    this->CalculateMCCosThetaMissingMomentum();
    this->CalculateMCRecoilMass();
    this->IsMCEventWW();
    this->IsMCEventZZ();
    this->DefineMCVariablesOfInterest();
}

//===========================================================

void MCAnalysis::SetMCQuarkMap()
{
    for (MCParticleVector::const_iterator iter = m_quarks.begin(); iter != m_quarks.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        this->MapMCParticleVector(pMCParticle, pMCParticle);
    }

    m_pVariables->SetMCParticleToQuarkMap(m_mcParticleToQuarkMap);
}

//===========================================================

void MCAnalysis::MapMCParticleVector(const EVENT::MCParticle *pMCParticle, const EVENT::MCParticle *pMCQuark)
{
    LcioMCParticleVector mcParticleDaughters(pMCParticle->getDaughters());

    for (LcioMCParticleVector::iterator mcParticleDaughter = mcParticleDaughters.begin(); mcParticleDaughter != mcParticleDaughters.end(); mcParticleDaughter++)
    {
        EVENT::MCParticle *pMCParticleDaughter(*mcParticleDaughter);

        if (m_mcParticleToQuarkMap.find(pMCParticleDaughter) == m_mcParticleToQuarkMap.end()) 
        {
            MCParticleVector *pMCParticleVector = new MCParticleVector();
            pMCParticleVector->push_back(pMCQuark);
            m_mcParticleToQuarkMap.insert(std::make_pair(pMCParticleDaughter, pMCParticleVector));
        }
        else 
        {
            if (std::find(m_mcParticleToQuarkMap.at(pMCParticleDaughter)->begin(), m_mcParticleToQuarkMap.at(pMCParticleDaughter)->end(), pMCQuark) == m_mcParticleToQuarkMap.at(pMCParticleDaughter)->end())
                m_mcParticleToQuarkMap.at(pMCParticleDaughter)->push_back(pMCQuark);
        }

        if (pMCParticleDaughter->getDaughters().size() > 0)
            this->MapMCParticleVector(pMCParticleDaughter, pMCQuark);
    }
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

    double bestWMetric(std::numeric_limits<double>::max()), bestZMetric(std::numeric_limits<double>::max()), bestSynMetric(std::numeric_limits<double>::max());
    DoubleVector bestWMasses, bestZMasses, bestSynMasses, allMasses;

    for (std::vector<IntVector>::iterator iter = combinations.begin(); iter != combinations.end(); iter++)
    {
        IntVector combination(*iter);

        MCParticleVector trialPair1, trialPair2;
        trialPair1.push_back(m_quarks.at(combination.at(0)));
        trialPair1.push_back(m_quarks.at(combination.at(1)));
        trialPair2.push_back(m_quarks.at(combination.at(2)));
        trialPair2.push_back(m_quarks.at(combination.at(3)));

        double invariantMass1(0.0), invariantMass2(0.0);

        this->FindMCInvariantMass(trialPair1, invariantMass1);
        this->FindMCInvariantMass(trialPair2, invariantMass2);

        allMasses.push_back(invariantMass1);
        allMasses.push_back(invariantMass2);

        const double wMetric(std::sqrt((invariantMass1-m_wBosonMass)*(invariantMass1-m_wBosonMass) + (invariantMass2-m_wBosonMass)*(invariantMass2-m_wBosonMass)));
        const double zMetric(std::sqrt((invariantMass1-m_zBosonMass)*(invariantMass1-m_zBosonMass) + (invariantMass2-m_zBosonMass)*(invariantMass2-m_zBosonMass)));
        const double synMetric(std::sqrt((invariantMass1-invariantMass2)*(invariantMass1-invariantMass2)));

        if (wMetric < bestWMetric)
        {
            bestWMasses.clear();
            bestWMetric = wMetric;
            m_pVariables->SetQuarkCombinationW(combination);

            if (invariantMass1 > invariantMass2)
            {
                m_mcWBoson1 = trialPair1;
                m_mcWBoson2 = trialPair2;
                bestWMasses.push_back(invariantMass1);
                bestWMasses.push_back(invariantMass2);
            }
            else
            {
                m_mcWBoson1 = trialPair2;
                m_mcWBoson2 = trialPair1;
                bestWMasses.push_back(invariantMass2);
                bestWMasses.push_back(invariantMass1);
            }
        }

        if (zMetric < bestZMetric)
        {
            bestZMasses.clear();
            bestZMetric = zMetric;
            m_pVariables->SetQuarkCombinationZ(combination);

            if (invariantMass1 > invariantMass2)
            {
                m_mcZBoson1 = trialPair1;
                m_mcZBoson2 = trialPair2;
                bestZMasses.push_back(invariantMass1);
                bestZMasses.push_back(invariantMass2);
            }
            else
            {
                m_mcZBoson1 = trialPair2;
                m_mcZBoson2 = trialPair1;
                bestZMasses.push_back(invariantMass2);
                bestZMasses.push_back(invariantMass1);
            }
        }

        if (synMetric < bestSynMetric)
        {
            bestSynMasses.clear();
            bestSynMetric = synMetric;
            m_pVariables->SetQuarkCombinationSyn(combination);

            if (invariantMass1 > invariantMass2)
            {
                m_mcSynBoson1 = trialPair1;
                m_mcSynBoson2 = trialPair2;
                bestSynMasses.push_back(invariantMass1);
                bestSynMasses.push_back(invariantMass2);
            }
            else
            {
                m_mcSynBoson1 = trialPair2;
                m_mcSynBoson2 = trialPair1;
                bestSynMasses.push_back(invariantMass2);
                bestSynMasses.push_back(invariantMass1);
            }
        }
    }

    m_pVariables->SetAllInvariantMassesMC(allMasses);
    m_pVariables->SetInvariantMassWBosonsMC(bestWMasses);
    m_pVariables->SetInvariantMassZBosonsMC(bestZMasses);
    m_pVariables->SetInvariantMassSynBosonsMC(bestSynMasses);
}

//===========================================================

void MCAnalysis::QuarkVariables()
{
    DoubleVector energyQuarks, pxMomentumQuarks, pyMomentumQuarks, pzMomentumQuarks;

    for (MCParticleVector::iterator iter = m_quarks.begin(); iter != m_quarks.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        const double px(pMCParticle->getMomentum()[0]);
        const double py(pMCParticle->getMomentum()[1]);
        const double pz(pMCParticle->getMomentum()[2]);
        const double energy(pMCParticle->getEnergy());

        energyQuarks.push_back(energy);
        pxMomentumQuarks.push_back(px);
        pyMomentumQuarks.push_back(py);
        pzMomentumQuarks.push_back(pz);
    }

    m_pVariables->SetEnergyQuarks(energyQuarks);
    m_pVariables->SetMomentumQuarks(pxMomentumQuarks, pyMomentumQuarks, pzMomentumQuarks);
}

//===========================================================

void MCAnalysis::NeutrinoVariables()
{
    DoubleVector energyNeutrinos, pxMomentumNeutrinos, pyMomentumNeutrinos, pzMomentumNeutrinos;

    for (MCParticleVector::iterator iter = m_neutrinos.begin(); iter != m_neutrinos.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        const double px(pMCParticle->getMomentum()[0]);
        const double py(pMCParticle->getMomentum()[1]);
        const double pz(pMCParticle->getMomentum()[2]);
        const double energy(pMCParticle->getEnergy());

        energyNeutrinos.push_back(energy);
        pxMomentumNeutrinos.push_back(px);
        pyMomentumNeutrinos.push_back(py);
        pzMomentumNeutrinos.push_back(pz);
    }

    m_pVariables->SetEnergyNeutrinos(energyNeutrinos);
    m_pVariables->SetMomentumNeutrinos(pxMomentumNeutrinos, pyMomentumNeutrinos, pzMomentumNeutrinos);
}

//===========================================================

void MCAnalysis::FindMCInvariantMass(MCParticleVector &mcParticleVector, double &invariantMass) const
{
    double pxTot(0.0), pyTot(0.0), pzTot(0.0), energyTot(0.0);

    for (MCParticleVector::iterator iter = mcParticleVector.begin(); iter != mcParticleVector.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        const double px(pMCParticle->getMomentum()[0]);
        const double py(pMCParticle->getMomentum()[1]);
        const double pz(pMCParticle->getMomentum()[2]);
        const double energy(pMCParticle->getEnergy());

        pxTot += px;
        pyTot += py;
        pzTot += pz;
        energyTot += energy;
    }

    invariantMass = sqrt(energyTot*energyTot - pxTot*pxTot - pyTot*pyTot - pzTot*pzTot);
}

//===========================================================

void MCAnalysis::CalculateMCTransverseMomentum()
{
    double transverseMomentum(0.0);
    for (MCParticleVector::iterator iter = m_quarks.begin(); iter != m_quarks.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        const double px(pMCParticle->getMomentum()[0]);
        const double py(pMCParticle->getMomentum()[1]);
        const double pz(pMCParticle->getMomentum()[2]);
        const double p(sqrt(px * px + py * py + pz * pz));
        const double energy(pMCParticle->getEnergy());
        transverseMomentum += energy * sqrt(px*px + py*py) / p;
    }
    m_pVariables->SetTransverseMomentumMC(transverseMomentum);
}

//===========================================================

void MCAnalysis::CalculateMCTransverseEnergy()
{
    double transverseEnergy(0.0);
    for (MCParticleVector::iterator iter = m_quarks.begin(); iter != m_quarks.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        const double px(pMCParticle->getMomentum()[0]);
        const double py(pMCParticle->getMomentum()[1]);

        transverseEnergy += sqrt(px*px + py*py);
    }
    m_pVariables->SetTransverseEnergyMC(transverseEnergy);
}

//===========================================================

void MCAnalysis::CalculateMCCosThetaMissingMomentum()
{
    double pxMis(0.0), pyMis(0.0), pzMis(0.0);

    for (MCParticleVector::iterator iter = m_neutrinos.begin(); iter != m_neutrinos.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        pxMis += pMCParticle->getMomentum()[0];
        pyMis += pMCParticle->getMomentum()[1];
        pzMis += pMCParticle->getMomentum()[2];
    }

    const double pMis(sqrt(pxMis * pxMis + pyMis * pyMis + pzMis * pzMis));
    m_pVariables->SetCosThetaMissingMC(pzMis / pMis);
}

//===========================================================

void MCAnalysis::CalculateMCRecoilMass()
{
    const double xFromCrossingAngle(m_eventEnergyMC * sin(m_crossingAngle));
    TLorentzVector pInit(xFromCrossingAngle,0,0,m_eventEnergyMC);
    double px(0.0), py(0.0), pz(0.0), E(0.0);

    for (MCParticleVector::const_iterator iter = m_quarks.begin(); iter != m_quarks.end(); iter++)
    {
        const EVENT::MCParticle* pMCParticle(*iter);
        px += pMCParticle->getMomentum()[0];
        py += pMCParticle->getMomentum()[1];
        pz += pMCParticle->getMomentum()[2];
        E += pMCParticle->getEnergy();
    }

    TLorentzVector pVis(px,py,pz,E);
    TLorentzVector pMis(pInit - pVis);
    double recoilMass(pMis.M()); // Invairant Mass/Magnitude
    m_pVariables->SetRecoilMassMC(recoilMass);
}

//===========================================================

void MCAnalysis::IsMCEventWW()
{
    if (m_pVariables->GetInvariantMassWBosonsMC().size() != 2)
    {
        m_pVariables->SetIsEventWWMC(false);
        return;
    }

    if (60 < m_pVariables->GetInvariantMassWBosonsMC().at(0) and m_pVariables->GetInvariantMassWBosonsMC().at(0) < 88 and 60 < m_pVariables->GetInvariantMassWBosonsMC().at(1) and m_pVariables->GetInvariantMassWBosonsMC().at(1) < 88)
    {
        m_pVariables->SetIsEventWWMC(true);
    }

    return;
}

//===========================================================

void MCAnalysis::IsMCEventZZ()
{
    if (m_pVariables->GetInvariantMassZBosonsMC().size() != 2)
    {
        m_pVariables->SetIsEventZZMC(false);
        return;
    }

    if (85 < m_pVariables->GetInvariantMassZBosonsMC().at(0) and m_pVariables->GetInvariantMassZBosonsMC().at(0) < 100 and 85 < m_pVariables->GetInvariantMassZBosonsMC().at(1) and m_pVariables->GetInvariantMassZBosonsMC().at(1) < 100)
    {
        m_pVariables->SetIsEventZZMC(true);
    }

    return;
}

//===========================================================

void MCAnalysis::DefineMCVariablesOfInterest()
{
    double invariantMassQuarkSystem(std::numeric_limits<double>::max());
    this->FindMCInvariantMass(m_quarks,invariantMassQuarkSystem);
    m_pVariables->SetInvariantMassSystemMC(invariantMassQuarkSystem);

    double mcCosThetaStarWBoson(std::numeric_limits<double>::max());
    this->CalculateMCCosThetaStar(m_mcWBoson1,m_mcWBoson2,mcCosThetaStarWBoson);
    m_pVariables->SetCosThetaStarWBosonsMC(mcCosThetaStarWBoson);

    double mcCosThetaStarZBoson(std::numeric_limits<double>::max());
    this->CalculateMCCosThetaStar(m_mcZBoson1,m_mcZBoson2,mcCosThetaStarZBoson);
    m_pVariables->SetCosThetaStarZBosonsMC(mcCosThetaStarZBoson);

    double mcCosThetaStarSynBoson(std::numeric_limits<double>::max());
    this->CalculateMCCosThetaStar(m_mcSynBoson1,m_mcSynBoson2,mcCosThetaStarSynBoson);
    m_pVariables->SetCosThetaStarSynBosonsMC(mcCosThetaStarSynBoson);
}

//===========================================================

void MCAnalysis::CalculateMCCosThetaStar(MCParticleVector objectOfInterest, MCParticleVector referenceFrameObjects, double &cosThetaStar) const 
{
    cosThetaStar = -1.0;
    TLorentzVector objectOfInterest4Vec, referenceFrameObjects4Vec;

    this->DefineMCEnergy4Vec(objectOfInterest, objectOfInterest4Vec);
    this->DefineMCEnergy4Vec(referenceFrameObjects, referenceFrameObjects4Vec);

    TLorentzVector diBoson = objectOfInterest4Vec + referenceFrameObjects4Vec;
    TVector3 boostvector = -diBoson.BoostVector();
    objectOfInterest4Vec.Boost(boostvector);
    cosThetaStar = fabs(objectOfInterest4Vec.Vect().Dot(diBoson.Vect()) / (objectOfInterest4Vec.Vect().Mag() * diBoson.Vect().Mag()));
}

//===========================================================

void MCAnalysis::DefineMCEnergy4Vec(MCParticleVector &mcParticleVector, TLorentzVector &tLorentzVector) const 
{
    double px(0.0), py(0.0), pz(0.0), E(0.0);

    for (MCParticleVector::const_iterator iter = mcParticleVector.begin(); iter != mcParticleVector.end(); iter++)
    {
        const EVENT::MCParticle *pMCParticle(*iter);
        px += pMCParticle->getMomentum()[0];
        py += pMCParticle->getMomentum()[1];
        pz += pMCParticle->getMomentum()[2];
        E += pMCParticle->getEnergy();
    }

    tLorentzVector.SetPx(px);
    tLorentzVector.SetPy(py);
    tLorentzVector.SetPz(pz);
    tLorentzVector.SetE(E);
}

//===========================================================
