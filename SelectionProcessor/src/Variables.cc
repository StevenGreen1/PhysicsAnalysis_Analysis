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
    gInterpreter->EnableAutoLoading();

// Variables Of Interest
// Bools
    pTTree->Branch("IsAppropriateEvent", &m_AppropriateEvent, "IsAppropriateEvent/O");
    pTTree->Branch("IsEventWW", &m_IsEventWW, "IsEventWW/O");
    pTTree->Branch("IsMCEventWW", &m_IsMCEventWW, "IsMCEventWW/O");
    pTTree->Branch("IsEventZZ", &m_IsEventZZ, "IsEventZZ/O");
    pTTree->Branch("IsMCEventZZ", &m_IsMCEventZZ, "IsMCEventZZ/O");

// Ints
// IntVectors
    pTTree->Branch("NParticlesJets", &m_NParticlesJets);
    pTTree->Branch("NChargedParticlesJets", &m_NChargedParticlesJets);

// Floats
    pTTree->Branch("TransverseMomentum", &m_TransverseMomentum, "TransverseMomentum/D");
    pTTree->Branch("MCTransverseMomentum", &m_MCTransverseMomentum, "MCTransverseMomentum/D");
    pTTree->Branch("TransverseEnergy", &m_TransverseEnergy, "TransverseEnergy/D");
    pTTree->Branch("MCTransverseEnergy", &m_MCTransverseEnergy, "MCTransverseEnergy/D");
    pTTree->Branch("CosThetaMissing", &m_CosThetaMissing, "CosThetaMissing/D");
    pTTree->Branch("MCCosThetaMissing", &m_MCCosThetaMissing, "MCCosThetaMissing/D");
    pTTree->Branch("CosThetaMostEnergeticTrack", &m_CosThetaMostEnergeticTrack, "CosThetaMostEnergeticTrack/D");
    pTTree->Branch("RecoilMass", &m_RecoilMass, "RecoilMass/D");
    pTTree->Branch("MCRecoilMass", &m_MCRecoilMass, "MCRecoilMass/D");
    pTTree->Branch("EnergyAroundMostEnergeticTrack", &m_EnergyAroundMostEnergeticPfo, "EnergyAroundMostEnergeticTrack/D");
    pTTree->Branch("y34", &m_y34, "y34/D");
    pTTree->Branch("InvariantMassSystem", &m_InvariantMassSystem, "InvariantMassSystem/D");
    pTTree->Branch("MCInvariantMassSystem", &m_MCInvariantMassSystem, "MCInvariantMassSystem/D");
    pTTree->Branch("CosThetaStarWBosons", &m_CosThetaStarWBosons, "CosThetaStarWBosons/D");
    pTTree->Branch("MCCosThetaStarWBosons", &m_MCCosThetaStarWBosons, "MCCosThetaStarWBosons/D");
    pTTree->Branch("CosThetaStarZBosons", &m_CosThetaStarZBosons, "CosThetaStarZBosons/D");
    pTTree->Branch("MCCosThetaStarZBosons", &m_MCCosThetaStarZBosons, "MCCosThetaStarZBosons/D");

// DoubleVectors
    pTTree->Branch("InvMassWVectors", &m_InvMassWVectors);
    pTTree->Branch("MCInvMassWVectors", &m_MCInvMassWVectors);
    pTTree->Branch("InvMassZVectors", &m_InvMassZVectors);
    pTTree->Branch("MCInvMassZVectors", &m_MCInvMassZVectors);
    pTTree->Branch("EnergyJets", &m_EnergyJets);
    pTTree->Branch("CosThetaStarWJets", &m_CosThetaStarWJets);
    pTTree->Branch("CosThetaStarZJets", &m_CosThetaStarZJets);
}

//===========================================================

void Variables::Print()
{
    std::cout << "m_AppropriateEvent             : " << m_AppropriateEvent << std::endl;
    std::cout << "m_IsEventWW                    : " << m_IsEventWW << std::endl;
    std::cout << "m_IsMCEventWW                  : " << m_IsMCEventWW << std::endl;
    std::cout << "m_IsEventZZ                    : " << m_IsEventZZ << std::endl;
    std::cout << "m_IsMCEventZZ                  : " << m_IsMCEventZZ << std::endl;

    for (IntVector::iterator iter = m_NParticlesJets.begin(); iter != m_NParticlesJets.end(); iter++)
    {
        std::cout << "m_NParticlesJets, position " << iter-m_NParticlesJets.begin() << " : " << *iter << std::endl;
    }

    for (IntVector::iterator iter = m_NChargedParticlesJets.begin(); iter != m_NChargedParticlesJets.end(); iter++)
    {
        std::cout << "m_NChargedParticlesJets, position " << iter-m_NChargedParticlesJets.begin() << " : " << *iter << std::endl;
    }

    std::cout << "m_TransverseMomentum           : " << m_TransverseMomentum << std::endl;
    std::cout << "m_MCTransverseMomentum         : " << m_MCTransverseMomentum << std::endl;
    std::cout << "m_TransverseEnergy             : " << m_TransverseEnergy << std::endl;
    std::cout << "m_MCTransverseEnergy           : " << m_MCTransverseEnergy << std::endl;
    std::cout << "m_CosThetaMissing              : " << m_CosThetaMissing << std::endl;
    std::cout << "m_MCCosThetaMissing            : " << m_MCCosThetaMissing << std::endl;
    std::cout << "m_CosThetaMostEnergeticTrack   : " << m_CosThetaMostEnergeticTrack << std::endl;
    std::cout << "m_RecoilMass                   : " << m_RecoilMass << std::endl;
    std::cout << "m_MCRecoilMass                 : " << m_MCRecoilMass << std::endl;
    std::cout << "m_EnergyAroundMostEnergeticPfo : " << m_EnergyAroundMostEnergeticPfo << std::endl;
    std::cout << "m_y34                          : " << m_y34 << std::endl;
    std::cout << "m_InvariantMassSystem          : " << m_InvariantMassSystem << std::endl;
    std::cout << "m_MCInvariantMassSystem        : " << m_MCInvariantMassSystem << std::endl;
    std::cout << "m_CosThetaStarWBosons          : " << m_CosThetaStarWBosons << std::endl;
    std::cout << "m_MCCosThetaStarWBosons        : " << m_MCCosThetaStarWBosons << std::endl;
    std::cout << "m_CosThetaStarZBosons          : " << m_CosThetaStarZBosons << std::endl;
    std::cout << "m_MCCosThetaStarZBosons        : " << m_MCCosThetaStarZBosons << std::endl;
//    std::cout << " : " <<  << std::endl;

    for (DoubleVector::iterator iter = m_EnergyJets.begin(); iter != m_EnergyJets.end(); iter++)
    {
        std::cout << "m_EnergyJets, position " << iter-m_EnergyJets.begin() << " : " << *iter << std::endl;
    }
}

//===========================================================

void Variables::Clear()
{
    m_AppropriateEvent = false;
    m_IsEventWW = false;
    m_IsMCEventWW = false;
    m_IsEventZZ = false;
    m_IsMCEventZZ = false;

    m_NParticlesJets.clear();
    m_NChargedParticlesJets.clear();

    m_TransverseMomentum = std::numeric_limits<double>::max();
    m_MCTransverseMomentum = std::numeric_limits<double>::max();
    m_TransverseEnergy = std::numeric_limits<double>::max();
    m_MCTransverseEnergy = std::numeric_limits<double>::max();
    m_CosThetaMissing = std::numeric_limits<double>::max();
    m_MCCosThetaMissing = std::numeric_limits<double>::max();
    m_CosThetaMostEnergeticTrack = std::numeric_limits<double>::max();
    m_RecoilMass = std::numeric_limits<double>::max();
    m_MCRecoilMass = std::numeric_limits<double>::max();
    m_EnergyAroundMostEnergeticPfo = std::numeric_limits<double>::max();
    m_y34 = std::numeric_limits<double>::max();
    m_InvariantMassSystem = std::numeric_limits<double>::max();
    m_MCInvariantMassSystem = std::numeric_limits<double>::max();
    m_CosThetaStarWBosons = std::numeric_limits<double>::max();
    m_MCCosThetaStarWBosons = std::numeric_limits<double>::max();
    m_CosThetaStarZBosons = std::numeric_limits<double>::max();
    m_MCCosThetaStarZBosons = std::numeric_limits<double>::max();

    m_InvMassWVectors.clear();
    m_MCInvMassWVectors.clear();
    m_InvMassZVectors.clear();
    m_MCInvMassZVectors.clear();
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

//=========================================================== double

void Variables::SetTransverseMomentum(double transverseMomentum)
{
    m_TransverseMomentum = transverseMomentum;
}

//===========================================================

double Variables::GetTransverseMomentum() const 
{
    return m_TransverseMomentum;
}

//===========================================================

void Variables::SetMCTransverseMomentum(double mcTransverseMomentum)
{
    m_MCTransverseMomentum = mcTransverseMomentum;
}

//===========================================================

double Variables::GetMCTransverseMomentum() const
{
    return m_MCTransverseMomentum;
}

//===========================================================

void Variables::SetTransverseEnergy(double transverseEnergy)
{
    m_TransverseEnergy = transverseEnergy;
}

//===========================================================

double Variables::GetTransverseEnergy() const 
{
    return m_TransverseEnergy;
}

//===========================================================

void Variables::SetMCTransverseEnergy(double mcTransverseEnergy)
{
    m_MCTransverseEnergy = mcTransverseEnergy;
}

//===========================================================

double Variables::GetMCTransverseEnergy() const
{
    return m_MCTransverseEnergy;
}

//===========================================================

void Variables::SetCosThetaMissing(double cosThetaMissing)
{
    m_CosThetaMissing = cosThetaMissing;
}

//===========================================================

double Variables::GetCosThetaMissing() const 
{
    return m_CosThetaMissing;
}

//===========================================================

void Variables::SetMCCosThetaMissing(double mcCosThetaMissing)
{
    m_MCCosThetaMissing = mcCosThetaMissing;
}

//===========================================================

double Variables::GetMCCosThetaMissing() const
{
    return m_MCCosThetaMissing;
}

//===========================================================

void Variables::SetCosThetaMostEnergeticTrack(double cosThetaMostEnergeticTrack)
{
    m_CosThetaMostEnergeticTrack = cosThetaMostEnergeticTrack;
}

//===========================================================

double Variables::GetCosThetaMostEnergeticTrack() const 
{
    return m_CosThetaMostEnergeticTrack;
}

//===========================================================

void Variables::SetRecoilMass(double recoilMass)
{
    m_RecoilMass = recoilMass;
}

//===========================================================

double Variables::GetRecoilMass() const 
{
    return m_RecoilMass;
}

//===========================================================

void Variables::SetMCRecoilMass(double mcRecoilMass)
{
    m_MCRecoilMass = mcRecoilMass;
}

//===========================================================

double Variables::GetMCRecoilMass() const
{
    return m_MCRecoilMass;
}

//===========================================================

void Variables::SetEnergyAroundMostEnergeticPfo(double energyAroundMostEnergeticPfo)
{
    m_EnergyAroundMostEnergeticPfo = energyAroundMostEnergeticPfo;
}

//===========================================================

double Variables::GetEnergyAroundMostEnergeticPfo() const 
{
    return m_EnergyAroundMostEnergeticPfo;
}

//===========================================================

void Variables::SetY34(double y34)
{
    m_y34 = y34;
}

//===========================================================

double Variables::GetY34() const 
{
    return m_y34;
}

//===========================================================

void Variables::SetInvariantMassSystem(double invariantMassSystem)
{
    m_InvariantMassSystem = invariantMassSystem;
}

//=========================================================== 

double Variables::GetInvariantMassSystem() const 
{
    return m_InvariantMassSystem;
}

//===========================================================

void Variables::SetMCInvariantMassSystem(double mcInvariantMassSystem)
{
    m_MCInvariantMassSystem = mcInvariantMassSystem;
}

//===========================================================

double Variables::GetMCInvariantMassSystem() const
{
    return m_MCInvariantMassSystem;
}

//===========================================================

void Variables::SetCosThetaStarWBosons(double cosThetaStarWBosons)
{
    m_CosThetaStarWBosons = cosThetaStarWBosons;
}

//===========================================================

double Variables::GetCosThetaStarWBosons() const 
{
    return m_CosThetaStarWBosons;
}

//===========================================================

void Variables::SetMCCosThetaStarWBosons(double mcCosThetaStarWBosons)
{
    m_MCCosThetaStarWBosons = mcCosThetaStarWBosons;
}

//===========================================================

double Variables::GetMCCosThetaStarWBosons() const
{
    return m_MCCosThetaStarWBosons;
}

//===========================================================

void Variables::SetCosThetaStarZBosons(double cosThetaStarZBosons)
{
    m_CosThetaStarZBosons = cosThetaStarZBosons;
}

//===========================================================

double Variables::GetCosThetaStarZBosons() const 
{
    return m_CosThetaStarZBosons;
}

//===========================================================

void Variables::SetMCCosThetaStarZBosons(double mcCosThetaStarZBosons)
{
    m_MCCosThetaStarZBosons = mcCosThetaStarZBosons;
}

//===========================================================

double Variables::GetMCCosThetaStarZBosons() const
{
    return m_MCCosThetaStarZBosons;
}

//=========================================================== DoubleVector

void Variables::SetInvMassWVectors(DoubleVector invMassWVectors)
{
    m_InvMassWVectors = invMassWVectors;
}

//===========================================================

DoubleVector Variables::GetInvMassWVectors() const 
{
    return m_InvMassWVectors;
}

//===========================================================

void Variables::SetInvMassZVectors(DoubleVector invMassZVectors)
{
    m_InvMassZVectors = invMassZVectors;
}

//===========================================================

DoubleVector Variables::GetInvMassZVectors() const 
{
    return m_InvMassZVectors;
}

//===========================================================

void Variables::SetMCInvMassWVectors(DoubleVector mcInvMassWVectors)
{
    m_MCInvMassWVectors = mcInvMassWVectors;
}

//===========================================================

DoubleVector Variables::GetMCInvMassWVectors() const
{
    return m_MCInvMassWVectors;
}

//===========================================================

void Variables::SetMCInvMassZVectors(DoubleVector mcInvMassZVectors)
{
    m_MCInvMassZVectors = mcInvMassZVectors;
}

//===========================================================

DoubleVector Variables::GetMCInvMassZVectors() const
{
    return m_MCInvMassZVectors;
}

//===========================================================

void Variables::SetEnergyJets(DoubleVector energyJets)
{
    m_EnergyJets = energyJets;
}

//===========================================================

DoubleVector Variables::GetEnergyJets() const 
{
    return m_EnergyJets;
}

//===========================================================

double Variables::GetLowestEnergyJet() const
{
    double lowestEnergyJet(std::numeric_limits<double>::max());

    for (DoubleVector::const_iterator iter = m_EnergyJets.begin(); iter != m_EnergyJets.end(); iter++)
    {
        const double energyJet(*iter);
        if (energyJet < lowestEnergyJet)
        {
            lowestEnergyJet = energyJet;
        }
    }

    return lowestEnergyJet;
}

//===========================================================

void Variables::SetCosThetaStarWJets(DoubleVector cosThetaStarWJets)
{
    m_CosThetaStarWJets = cosThetaStarWJets;
}

//===========================================================

DoubleVector Variables::GetCosThetaStarWJets() const 
{
    return m_CosThetaStarWJets;
}

//===========================================================

void Variables::SetCosThetaStarZJets(DoubleVector cosThetaStarZJets)
{
    m_CosThetaStarZJets = cosThetaStarZJets;
}

//===========================================================

DoubleVector Variables::GetCosThetaStarZJets() const 
{
    return m_CosThetaStarZJets;
}

//===========================================================
