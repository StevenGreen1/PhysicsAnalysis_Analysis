/**
 *  @file   SelectionProcessor/src/Variables.cc 
 * 
 *  @brief  Implementation of the variables class.
 * 
 *  $Log: $
 */

#include "Variables.h"

using namespace variables_namespace;

//===========================================================

Variables::Variables()
{
}

//===========================================================

Variables::~Variables()
{
}

//===========================================================

void Variables::SetBranches(TTree *pTTree)
{
// Variables Of Interest
// Bools
    pTTree->Branch("IsAppropriateEvent", &m_AppropriateEvent, "IsAppropriateEvent/O");
    pTTree->Branch("IsEventWW", &m_IsEventWW, "IsEventWW/O");
    pTTree->Branch("IsEventZZ", &m_IsEventZZ, "IsEventZZ/O");

// Ints
// IntVectors
    pTTree->Branch("NParticlesJets", &m_NParticlesJets);
    pTTree->Branch("NChargedParticlesJets", &m_NChargedParticlesJets);

// Floats
    pTTree->Branch("TransverseMomentum", &m_TransverseMomentum, "TransverseMomentum/F");
    pTTree->Branch("TransverseEnergy", &m_TransverseEnergy, "TransverseEnergy/F");
    pTTree->Branch("CosThetaMissing", &m_CosThetaMissing, "CosThetaMissing/F");
    pTTree->Branch("CosThetaMostEnergeticTrack", &m_CosThetaMostEnergeticTrack, "CosThetaMostEnergeticTrack/F");
    pTTree->Branch("RecoilMass", &m_RecoilMass, "RecoilMass/F");
    pTTree->Branch("EnergyAroundMostEnergeticTrack", &m_EnergyAroundMostEnergeticPfo, "EnergyAroundMostEnergeticTrack/F");
    pTTree->Branch("y34", &m_y34, "y34/F");
    pTTree->Branch("InvariantMassSystem", &m_InvariantMassSystem, "InvariantMassSystem/F");
    pTTree->Branch("CosThetaStarWBosons", &m_CosThetaStarWBosons, "CosThetaStarWBosons/F");
    pTTree->Branch("CosThetaStarZBosons", &m_CosThetaStarZBosons, "CosThetaStarZBosons/F");

// FloatVectors
    pTTree->Branch("InvMassWVectors", &m_InvMassWVectors);
    pTTree->Branch("InvMassZVectors", &m_InvMassZVectors);
    pTTree->Branch("EnergyJets", &m_EnergyJets);
    pTTree->Branch("CosThetaStarWJets", &m_CosThetaStarWJets);
    pTTree->Branch("CosThetaStarZJets", &m_CosThetaStarZJets);
}

//===========================================================

void Variables::Print()
{
    std::cout << "m_AppropriateEvent             : " << m_AppropriateEvent << std::endl;
    std::cout << "m_IsEventWW                    : " << m_IsEventWW << std::endl;
    std::cout << "m_IsEventZZ                    : " << m_IsEventZZ << std::endl;

    for (IntVector::iterator iter = m_NParticlesJets.begin(); iter != m_NParticlesJets.end(); iter++)
    {
        std::cout << "m_NParticlesJets, position " << iter-m_NParticlesJets.begin() << " : " << *iter << std::endl;
    }

    for (IntVector::iterator iter = m_NChargedParticlesJets.begin(); iter != m_NChargedParticlesJets.end(); iter++)
    {
        std::cout << "m_NChargedParticlesJets, position " << iter-m_NChargedParticlesJets.begin() << " : " << *iter << std::endl;
    }

    std::cout << "m_TransverseMomentum           : " << m_TransverseMomentum << std::endl;
    std::cout << "m_TransverseEnergy             : " << m_TransverseEnergy << std::endl;
    std::cout << "m_CosThetaMissing              : " << m_CosThetaMissing << std::endl;
    std::cout << "m_CosThetaMostEnergeticTrack   : " << m_CosThetaMostEnergeticTrack << std::endl;
    std::cout << "m_RecoilMass                   : " << m_RecoilMass << std::endl;
    std::cout << "m_EnergyAroundMostEnergeticPfo : " << m_EnergyAroundMostEnergeticPfo << std::endl;
    std::cout << "m_y34                          : " << m_y34 << std::endl;
    std::cout << "m_InvariantMassSystem          : " << m_InvariantMassSystem << std::endl;
    std::cout << "m_CosThetaStarWBosons          : " << m_CosThetaStarWBosons << std::endl;
    std::cout << "m_CosThetaStarZBosons          : " << m_CosThetaStarZBosons << std::endl;
//    std::cout << " : " <<  << std::endl;

    for (FloatVector::iterator iter = m_EnergyJets.begin(); iter != m_EnergyJets.end(); iter++)
    {
        std::cout << "m_EnergyJets, position " << iter-m_EnergyJets.begin() << " : " << *iter << std::endl;
    }
}

//===========================================================

void Variables::Clear()
{
    m_AppropriateEvent = false;
    m_IsEventWW = false;
    m_IsEventZZ = false;

    m_NParticlesJets.clear();
    m_NChargedParticlesJets.clear();

    m_TransverseMomentum = std::numeric_limits<float>::max();
    m_TransverseEnergy = std::numeric_limits<float>::max();
    m_CosThetaMissing = std::numeric_limits<float>::max();
    m_CosThetaMostEnergeticTrack = std::numeric_limits<float>::max();
    m_RecoilMass = std::numeric_limits<float>::max();
    m_EnergyAroundMostEnergeticPfo = std::numeric_limits<float>::max();
    m_y34 = std::numeric_limits<float>::max();
    m_InvariantMassSystem = std::numeric_limits<float>::max();
    m_CosThetaStarWBosons = std::numeric_limits<float>::max();
    m_CosThetaStarZBosons = std::numeric_limits<float>::max();

    m_InvMassWVectors.clear();
    m_InvMassZVectors.clear();
    m_EnergyJets.clear();
    m_CosThetaStarWJets.clear();
    m_CosThetaStarZJets.clear();
}

//=========================================================== bool

void Variables::SetAppropriateEvent(bool appropriateEvent)
{
    m_AppropriateEvent = appropriateEvent;
}

//===========================================================

bool Variables::GetAppropriateEvent() const 
{
    return m_AppropriateEvent;
}

//===========================================================

void Variables::SetIsEventWW(bool isEventWW)
{
    m_IsEventWW = isEventWW;
}

//===========================================================

bool Variables::GetIsEventWW() const 
{
    return m_IsEventWW;
}

//===========================================================

void Variables::SetIsMCEventWW(bool isMCEventWW)
{
    m_IsMCEventWW = isMCEventWW;
}

//===========================================================

bool Variables::GetIsMCEventWW() const
{
    return m_IsMCEventWW;
}

//===========================================================

void Variables::SetIsEventZZ(bool isEventZZ)
{
    m_IsEventZZ = isEventZZ;
}

//===========================================================

bool Variables::GetIsEventZZ() const 
{
    return m_IsEventZZ;
}

//===========================================================

void Variables::SetIsMCEventZZ(bool isMCEventZZ)
{
    m_IsMCEventZZ = isMCEventZZ;
}

//===========================================================

bool Variables::GetIsMCEventZZ() const
{
    return m_IsMCEventZZ;
}

//=========================================================== IntVector

void Variables::SetNParticlesJets(IntVector nParticlesJets)
{
    m_NParticlesJets = nParticlesJets;
}

//===========================================================

IntVector Variables::GetNParticlesJets() const
{
    return m_NParticlesJets;
}

//===========================================================

int Variables::GetLowestNParticlesJets() const
{
    int lowestNParticlesJets(std::numeric_limits<int>::max());

    for (IntVector::const_iterator iter = m_NParticlesJets.begin(); iter != m_NParticlesJets.end(); iter++)
    {
        const int nParticlesJet(*iter);
        if (nParticlesJet < lowestNParticlesJets)
        {
            lowestNParticlesJets = nParticlesJet;
        }
    }

    return lowestNParticlesJets;
}

//===========================================================

void Variables::SetNChargedParticlesJets(IntVector nChargedParticlesJets)
{
    m_NChargedParticlesJets = nChargedParticlesJets;
}

//===========================================================

IntVector Variables::GetNChargedParticlesJets() const 
{
    return m_NChargedParticlesJets;
}

//===========================================================

int Variables::GetLowestNChargedParticlesJets() const
{
    int lowestNChargedParticlesJets(std::numeric_limits<int>::max());

    for (IntVector::const_iterator iter = m_NChargedParticlesJets.begin(); iter != m_NChargedParticlesJets.end(); iter++)
    {
        const int nChargedParticlesJet(*iter);
        if (nChargedParticlesJet < lowestNChargedParticlesJets)
        {
            lowestNChargedParticlesJets = nChargedParticlesJet;
        }
    }

    return lowestNChargedParticlesJets;
}

//=========================================================== float

void Variables::SetTransverseMomentum(float transverseMomentum)
{
    m_TransverseMomentum = transverseMomentum;
}

//===========================================================

float Variables::GetTransverseMomentum() const 
{
    return m_TransverseMomentum;
}

//===========================================================

void Variables::SetMCTransverseMomentum(float mcTransverseMomentum)
{
    m_MCTransverseMomentum = mcTransverseMomentum;
}

//===========================================================

float Variables::GetMCTransverseMomentum() const
{
    return m_MCTransverseMomentum;
}

//===========================================================

void Variables::SetTransverseEnergy(float transverseEnergy)
{
    m_TransverseEnergy = transverseEnergy;
}

//===========================================================

float Variables::GetTransverseEnergy() const 
{
    return m_TransverseEnergy;
}

//===========================================================

void Variables::SetMCTransverseEnergy(float mcTransverseEnergy)
{
    m_MCTransverseEnergy = mcTransverseEnergy;
}

//===========================================================

float Variables::GetMCTransverseEnergy() const
{
    return m_MCTransverseEnergy;
}

//===========================================================

void Variables::SetCosThetaMissing(float cosThetaMissing)
{
    m_CosThetaMissing = cosThetaMissing;
}

//===========================================================

float Variables::GetCosThetaMissing() const 
{
    return m_CosThetaMissing;
}

//===========================================================

void Variables::SetMCCosThetaMissing(float mcCosThetaMissing)
{
    m_MCCosThetaMissing = mcCosThetaMissing;
}

//===========================================================

float Variables::GetMCCosThetaMissing() const
{
    return m_MCCosThetaMissing;
}

//===========================================================

void Variables::SetCosThetaMostEnergeticTrack(float cosThetaMostEnergeticTrack)
{
    m_CosThetaMostEnergeticTrack = cosThetaMostEnergeticTrack;
}

//===========================================================

float Variables::GetCosThetaMostEnergeticTrack() const 
{
    return m_CosThetaMostEnergeticTrack;
}

//===========================================================

void Variables::SetRecoilMass(float recoilMass)
{
    m_RecoilMass = recoilMass;
}

//===========================================================

float Variables::GetRecoilMass() const 
{
    return m_RecoilMass;
}

//===========================================================

void Variables::SetMCRecoilMass(float mcRecoilMass)
{
    m_MCRecoilMass = mcRecoilMass;
}

//===========================================================

float Variables::GetMCRecoilMass() const
{
    return m_MCRecoilMass;
}

//===========================================================

void Variables::SetEnergyAroundMostEnergeticPfo(float energyAroundMostEnergeticPfo)
{
    m_EnergyAroundMostEnergeticPfo = energyAroundMostEnergeticPfo;
}

//===========================================================

float Variables::GetEnergyAroundMostEnergeticPfo() const 
{
    return m_EnergyAroundMostEnergeticPfo;
}

//===========================================================

void Variables::SetY34(float y34)
{
    m_y34 = y34;
}

//===========================================================

float Variables::GetY34() const 
{
    return m_y34;
}

//===========================================================

void Variables::SetInvariantMassSystem(float invariantMassSystem)
{
    m_InvariantMassSystem = invariantMassSystem;
}

//=========================================================== 

float Variables::GetInvariantMassSystem() const 
{
    return m_InvariantMassSystem;
}

//===========================================================

void Variables::SetMCInvariantMassSystem(float mcInvariantMassSystem)
{
    m_MCInvariantMassSystem = mcInvariantMassSystem;
}

//===========================================================

float Variables::GetMCInvariantMassSystem() const
{
    return m_MCInvariantMassSystem;
}

//===========================================================

void Variables::SetCosThetaStarWBosons(float cosThetaStarWBosons)
{
    m_CosThetaStarWBosons = cosThetaStarWBosons;
}

//===========================================================

float Variables::GetCosThetaStarWBosons() const 
{
    return m_CosThetaStarWBosons;
}

//===========================================================

void Variables::SetCosThetaStarZBosons(float cosThetaStarZBosons)
{
    m_CosThetaStarZBosons = cosThetaStarZBosons;
}

//===========================================================

float Variables::GetCosThetaStarZBosons() const 
{
    return m_CosThetaStarZBosons;
}

//=========================================================== FloatVector

void Variables::SetInvMassWVectors(FloatVector invMassWVectors)
{
    m_InvMassWVectors = invMassWVectors;
}

//===========================================================

FloatVector Variables::GetInvMassWVectors() const 
{
    return m_InvMassWVectors;
}

//===========================================================

void Variables::SetInvMassZVectors(FloatVector invMassZVectors)
{
    m_InvMassZVectors = invMassZVectors;
}

//===========================================================

FloatVector Variables::GetInvMassZVectors() const 
{
    return m_InvMassZVectors;
}

//===========================================================

void Variables::SetMCInvMassWVectors(FloatVector mcInvMassWVectors)
{
    m_MCInvMassWVectors = mcInvMassWVectors;
}

//===========================================================

FloatVector Variables::GetMCInvMassWVectors() const
{
    return m_MCInvMassWVectors;
}

//===========================================================

void Variables::SetMCInvMassZVectors(FloatVector mcInvMassZVectors)
{
    m_MCInvMassZVectors = mcInvMassZVectors;
}

//===========================================================

FloatVector Variables::GetMCInvMassZVectors() const
{
    return m_MCInvMassZVectors;
}

//===========================================================

void Variables::SetEnergyJets(FloatVector energyJets)
{
    m_EnergyJets = energyJets;
}

//===========================================================

FloatVector Variables::GetEnergyJets() const 
{
    return m_EnergyJets;
}

//===========================================================

float Variables::GetLowestEnergyJet() const
{
    float lowestEnergyJet(std::numeric_limits<float>::max());

    for (FloatVector::const_iterator iter = m_EnergyJets.begin(); iter != m_EnergyJets.end(); iter++)
    {
        const float energyJet(*iter);
        if (energyJet < lowestEnergyJet)
        {
            lowestEnergyJet = energyJet;
        }
    }

    return lowestEnergyJet;
}

//===========================================================

void Variables::SetCosThetaStarWJets(FloatVector cosThetaStarWJets)
{
    m_CosThetaStarWJets = cosThetaStarWJets;
}

//===========================================================

FloatVector Variables::GetCosThetaStarWJets() const 
{
    return m_CosThetaStarWJets;
}

//===========================================================

void Variables::SetCosThetaStarZJets(FloatVector cosThetaStarZJets)
{
    m_CosThetaStarZJets = cosThetaStarZJets;
}

//===========================================================

FloatVector Variables::GetCosThetaStarZJets() const 
{
    return m_CosThetaStarZJets;
}

//===========================================================
