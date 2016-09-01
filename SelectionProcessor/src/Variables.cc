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
    pTTree->Branch("NParticlesJet1", &m_NParticlesJets.at(0), "NParticlesJet1/I");
    pTTree->Branch("NParticlesJet2", &m_NParticlesJets.at(1), "NParticlesJet2/I");
    pTTree->Branch("NParticlesJet3", &m_NParticlesJets.at(2), "NParticlesJet3/I");
    pTTree->Branch("NParticlesJet4", &m_NParticlesJets.at(3), "NParticlesJet4/I");
    pTTree->Branch("NChargedParticlesJet1", &m_NChargedParticlesJets.at(0), "NParticlesJet1/I");
    pTTree->Branch("NChargedParticlesJet2", &m_NChargedParticlesJets.at(1), "NParticlesJet2/I");
    pTTree->Branch("NChargedParticlesJet3", &m_NChargedParticlesJets.at(2), "NParticlesJet3/I");
    pTTree->Branch("NChargedParticlesJet4", &m_NChargedParticlesJets.at(3), "NParticlesJet4/I");
    pTTree->Branch("NChargedParticlesJet4", &m_NChargedParticlesJets.at(3), "NParticlesJet4/I");
    pTTree->Branch("NPfosBosonW1", &m_nPfosBosonW1, "NPfosBosonW1/I");
    pTTree->Branch("NPfosBosonW2", &m_nPfosBosonW2, "NPfosBosonW2/I");
    pTTree->Branch("NPfosBosonZ1", &m_nPfosBosonZ1, "NPfosBosonZ1/I");
    pTTree->Branch("NPfosBosonZ2", &m_nPfosBosonZ2, "NPfosBosonZ2/I");

// Ints
// IntVectors
//    pTTree->Branch("NParticlesJets", &m_NParticlesJets);
//    pTTree->Branch("NChargedParticlesJets", &m_NChargedParticlesJets);

// Floats
    pTTree->Branch("TransverseMomentum", &m_TransverseMomentum, "TransverseMomentum/D");
    pTTree->Branch("TransverseMomentumBosonW1", &m_transverseMomentumBosonW1, "TransverseMomentumBosonW1/D");
    pTTree->Branch("TransverseMomentumBosonW2", &m_transverseMomentumBosonW2, "TransverseMomentumBosonW2/D");
    pTTree->Branch("TransverseMomentumBosonZ1", &m_transverseMomentumBosonZ1, "TransverseMomentumBosonZ1/D");
    pTTree->Branch("TransverseMomentumBosonZ2", &m_transverseMomentumBosonZ2, "TransverseMomentumBosonZ2/D");
    pTTree->Branch("MCTransverseMomentum", &m_MCTransverseMomentum, "MCTransverseMomentum/D");
    pTTree->Branch("TransverseEnergy", &m_TransverseEnergy, "TransverseEnergy/D");
    pTTree->Branch("TransverseEnergyBosonW1", &m_transverseEnergyBosonW1, "TransverseEnergyBosonW1/D");
    pTTree->Branch("TransverseEnergyBosonW2", &m_transverseEnergyBosonW2, "TransverseEnergyBosonW2/D");
    pTTree->Branch("TransverseEnergyBosonZ1", &m_transverseEnergyBosonZ1, "TransverseEnergyBosonZ1/D");
    pTTree->Branch("TransverseEnergyBosonZ2", &m_transverseEnergyBosonZ2, "TransverseEnergyBosonZ2/D");
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
    pTTree->Branch("InvMassWVector1", &m_InvMassWVectors.at(0), "InvMassWVector1/D");
    pTTree->Branch("InvMassWVector2", &m_InvMassWVectors.at(1), "InvMassWVector2/D");
    pTTree->Branch("MCInvMassWVector1", &m_MCInvMassWVectors.at(0), "MCInvMassWVector1/D");
    pTTree->Branch("MCInvMassWVector2", &m_MCInvMassWVectors.at(1), "MCInvMassWVector2/D");
    pTTree->Branch("InvMassZVector1", &m_InvMassZVectors.at(0), "InvMassZVector1/D");
    pTTree->Branch("InvMassZVector2", &m_InvMassZVectors.at(1), "InvMassZVector2/D");
    pTTree->Branch("MCInvMassZVector1", &m_MCInvMassZVectors.at(0), "MCInvMassZVector1/D");
    pTTree->Branch("MCInvMassZVector2", &m_MCInvMassZVectors.at(1), "MCInvMassZVector2/D");
    pTTree->Branch("EnergyJet1", &m_EnergyJets.at(0), "EnergyJet1/D");
    pTTree->Branch("EnergyJet2", &m_EnergyJets.at(1), "EnergyJet2/D");
    pTTree->Branch("EnergyJet3", &m_EnergyJets.at(2), "EnergyJet3/D");
    pTTree->Branch("EnergyJet4", &m_EnergyJets.at(3), "EnergyJet4/D");
    pTTree->Branch("CosThetaStarWJet1", &m_CosThetaStarWJets.at(0), "CosThetaStarWJet1/D");
    pTTree->Branch("CosThetaStarWJet2", &m_CosThetaStarWJets.at(1), "CosThetaStarWJet2/D");
    pTTree->Branch("CosThetaStarZJet1", &m_CosThetaStarZJets.at(0), "CosThetaStarZJet1/D");
    pTTree->Branch("CosThetaStarZJet2", &m_CosThetaStarZJets.at(1), "CosThetaStarZJet2/D");
    pTTree->Branch("AcolinearityJetsW1", &m_acolinearityJetsW1, "AcolinearityJetsW1/D");
    pTTree->Branch("AcolinearityJetsW2", &m_acolinearityJetsW2, "AcolinearityJetsW2/D");
    pTTree->Branch("AcolinearityJetsZ1", &m_acolinearityJetsZ1, "AcolinearityJetsZ1/D");
    pTTree->Branch("AcolinearityJetsZ2", &m_acolinearityJetsZ2, "AcolinearityJetsZ2/D");
    pTTree->Branch("AcolinearityBosonsW", &m_acolinearityBosonsW, "AcolinearityBosonsW/D");
    pTTree->Branch("AcolinearityBosonsZ", &m_acolinearityBosonsZ, "AcolinearityBosonsZ/D");
    pTTree->Branch("PrincipleThrustValue", &m_principleThrustValue, "PrincipleThrustValue/D");
    pTTree->Branch("MajorThrustValue", &m_majorThrustValue, "MajorThrustValue/D");
    pTTree->Branch("MinorThrustValue", &m_minorThrustValue, "MinorThrustValue/D");
    pTTree->Branch("XThrustAxis", &m_xThrustAxis, "XThrustAxis/D");
    pTTree->Branch("YThrustAxis", &m_yThrustAxis, "YThrustAxis/D");
    pTTree->Branch("ZThrustAxis", &m_zThrustAxis, "ZThrustAxis/D");
    pTTree->Branch("Sphericity", &m_sphericity, "Sphericity/D");
    pTTree->Branch("Aplanarity", &m_aplanarity, "Aplanarity/D");

// DoubleVectors
//    pTTree->Branch("InvMassWVectors", &m_InvMassWVectors);
//    pTTree->Branch("MCInvMassWVectors", &m_MCInvMassWVectors);
//    pTTree->Branch("InvMassZVectors", &m_InvMassZVectors);
//    pTTree->Branch("MCInvMassZVectors", &m_MCInvMassZVectors);
//    pTTree->Branch("EnergyJets", &m_EnergyJets);
//    pTTree->Branch("CosThetaStarWJets", &m_CosThetaStarWJets);
//    pTTree->Branch("CosThetaStarZJets", &m_CosThetaStarZJets);
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

//===========================================================

void Variables::SetLCParameterInfo(const EVENT::LCParameters &lcParameters)
{
    m_principleThrustValue = lcParameters.getFloatVal("principleThrustValue");
    m_majorThrustValue = lcParameters.getFloatVal("majorThrustValue");
    m_minorThrustValue = lcParameters.getFloatVal("minorThrustValue");

    FloatVector thrustaxis;
    lcParameters.getFloatVals("principleThrustAxis", thrustaxis);
    if (thrustaxis.size() >=3)
    {
        m_xThrustAxis  = thrustaxis[0];
        m_yThrustAxis  = thrustaxis[1];
        m_zThrustAxis  = thrustaxis[2];
    }
    else
    {
        std::cout  << "Variables::SetLCParameterInfo thrustaxis less than 3 elements" << std::endl;
    }

    m_sphericity = lcParameters.getFloatVal("sphericity");
    m_aplanarity = lcParameters.getFloatVal("aplanarity");
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

//=========================================================== Int

void Variables::SetNPfosBosonW1(int nPfosBosonW1)
{
    m_nPfosBosonW1 = nPfosBosonW1;
}

//===========================================================

int Variables::GetNPfosBosonW1() const
{
    return m_nPfosBosonW1;
}

//===========================================================

void Variables::SetNPfosBosonW2(int nPfosBosonW2)
{
    m_nPfosBosonW2 = nPfosBosonW2;
}

//===========================================================

int Variables::GetNPfosBosonW2() const
{
    return m_nPfosBosonW2;
}

//===========================================================

void Variables::SetNPfosBosonZ1(int nPfosBosonZ1)
{
    m_nPfosBosonZ1 = nPfosBosonZ1;
}

//===========================================================

int Variables::GetNPfosBosonZ1() const
{
    return m_nPfosBosonZ1;
}

//===========================================================

void Variables::SetNPfosBosonZ2(int nPfosBosonZ2)
{
    m_nPfosBosonZ2 = nPfosBosonZ2;
}

//===========================================================

int Variables::GetNPfosBosonZ2() const
{
    return m_nPfosBosonZ2;
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

void Variables::SetTransverseMomentumBosonW1(double transverseMomentumBosonW1)
{
    m_transverseMomentumBosonW1 = transverseMomentumBosonW1;
}

//===========================================================

double Variables::GetTransverseMomentumBosonW1() const
{
    return m_transverseMomentumBosonW1;
}

//===========================================================

void Variables::SetTransverseMomentumBosonW2(double transverseMomentumBosonW2)
{
    m_transverseMomentumBosonW2 = transverseMomentumBosonW2;
}

//===========================================================

double Variables::GetTransverseMomentumBosonW2() const
{
    return m_transverseMomentumBosonW2;
}

//===========================================================

void Variables::SetTransverseMomentumBosonZ1(double transverseMomentumBosonZ1)
{
    m_transverseMomentumBosonZ1 = transverseMomentumBosonZ1;
}

//===========================================================

double Variables::GetTransverseMomentumBosonZ1() const
{
    return m_transverseMomentumBosonZ1;
}

//===========================================================

void Variables::SetTransverseMomentumBosonZ2(double transverseMomentumBosonZ2)
{
    m_transverseMomentumBosonZ2 = transverseMomentumBosonZ2;
}

//===========================================================

double Variables::GetTransverseMomentumBosonZ2() const
{
    return m_transverseMomentumBosonZ2;
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

void Variables::SetTransverseEnergyBosonW1(double transverseEnergyBosonW1)
{
    m_transverseEnergyBosonW1 = transverseEnergyBosonW1;
}

//===========================================================

double Variables::GetTransverseEnergyBosonW1() const
{
    return m_transverseEnergyBosonW1;
}

//===========================================================

void Variables::SetTransverseEnergyBosonW2(double transverseEnergyBosonW2)
{
    m_transverseEnergyBosonW2 = transverseEnergyBosonW2;
}

//===========================================================

double Variables::GetTransverseEnergyBosonW2() const
{
    return m_transverseEnergyBosonW2;
}

//===========================================================

void Variables::SetTransverseEnergyBosonZ1(double transverseEnergyBosonZ1)
{
    m_transverseEnergyBosonZ1 = transverseEnergyBosonZ1;
}

//===========================================================

double Variables::GetTransverseEnergyBosonZ1() const
{
    return m_transverseEnergyBosonZ1;
}

//===========================================================

void Variables::SetTransverseEnergyBosonZ2(double transverseEnergyBosonZ2)
{
    m_transverseEnergyBosonZ2 = transverseEnergyBosonZ2;
}

//===========================================================

double Variables::GetTransverseEnergyBosonZ2() const
{
    return m_transverseEnergyBosonZ2;
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

//===========================================================

void Variables::SetAcolinearityJetsW1(double acolinearityJetsW1)
{
    m_acolinearityJetsW1 = acolinearityJetsW1;
}

//===========================================================

double Variables::GetAcolinearityJetsW1() const
{
    return m_acolinearityJetsW1;
}

//===========================================================

void Variables::SetAcolinearityJetsW2(double acolinearityJetsW2)
{
    m_acolinearityJetsW2 = acolinearityJetsW2;
}

//===========================================================

double Variables::GetAcolinearityJetsW2() const
{
    return m_acolinearityJetsW2;
}

//===========================================================

void Variables::SetAcolinearityJetsZ1(double acolinearityJetsZ1)
{
    m_acolinearityJetsZ1 = acolinearityJetsZ1;
}

//===========================================================

double Variables::GetAcolinearityJetsZ1() const
{
    return m_acolinearityJetsZ1;
}

//===========================================================

void Variables::SetAcolinearityJetsZ2(double acolinearityJetsZ2)
{
    m_acolinearityJetsZ2 = acolinearityJetsZ2;
}

//===========================================================

double Variables::GetAcolinearityJetsZ2() const
{
    return m_acolinearityJetsZ2;
}

//===========================================================

void Variables::SetAcolinearityBosonsW(double acolinearityBosonsW)
{
    m_acolinearityBosonsW = acolinearityBosonsW;
}

//===========================================================

double Variables::GetAcolinearityBosonsW() const
{
    return m_acolinearityBosonsW;
}

//===========================================================

void Variables::SetAcolinearityBosonsZ(double acolinearityBosonsZ)
{
    m_acolinearityBosonsZ = acolinearityBosonsZ;
}

//===========================================================

double Variables::GetAcolinearityBosonsZ() const
{
    return m_acolinearityBosonsZ;
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
