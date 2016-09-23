/**
 *  @file   SelectionProcessor/src/RawPfoAnalysis.cc
 *
 *  @brief  Implementation of the pfo analysis class.
 *
 *  $Log: $
 */

#include "RawPfoAnalysis.h"

//===========================================================

RawPfoAnalysis::RawPfoAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables):
    m_pVariables(variables),
    m_pHighestEnergyElectron(NULL),
    m_pHighestEnergyMuon(NULL),
    m_pHighestEnergyPhoton(NULL),
    m_pHighestEnergyPfo(NULL)
{
    this->SetHighestEnergyPFOs(pLCCollection);
    this->Process();
}

//===========================================================

RawPfoAnalysis::~RawPfoAnalysis()
{
}

//===========================================================

void RawPfoAnalysis::Process()
{
    if (m_pHighestEnergyElectron != NULL)
        this->CalculateHighestEnergyElectronData();

    if (m_pHighestEnergyMuon != NULL)
        this->CalculateHighestEnergyMuonData();

    if (m_pHighestEnergyPhoton != NULL)
       this->CalculateHighestEnergyPhotonData();

    if (m_pHighestEnergyPfo != NULL)
        this->CalculateHighestEnergyPfoData();
}

//===========================================================

void RawPfoAnalysis::SetHighestEnergyPFOs(const EVENT::LCCollection *pLCCollection)
{
    double highestEnergyElectron(-std::numeric_limits<double>::max());
    double highestEnergyMuon(-std::numeric_limits<double>::max());
    double highestEnergyPhoton(-std::numeric_limits<double>::max());
    double highestEnergyPfo(-std::numeric_limits<double>::max());

    for (unsigned int entry = 0; entry < pLCCollection->getNumberOfElements(); entry++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(entry));
        const double pfoEnergy(pReconstructedParticle->getEnergy());

        if (pfoEnergy > highestEnergyPfo)
        {
            highestEnergyPfo = pfoEnergy;
            m_pHighestEnergyPfo = pReconstructedParticle;
        }

        if (std::abs(pReconstructedParticle->getType()) == 11)
        {
            if (pfoEnergy > highestEnergyElectron)
            {
                highestEnergyElectron = pfoEnergy;
                m_pHighestEnergyElectron = pReconstructedParticle;
            }
        }
        else if (std::abs(pReconstructedParticle->getType()) == 13)
        {
            if (pfoEnergy > highestEnergyMuon)
            {
                highestEnergyMuon = pfoEnergy;
                m_pHighestEnergyMuon = pReconstructedParticle;
            }
        }
        else if (std::abs(pReconstructedParticle->getType()) == 22)
        {
            if (pfoEnergy > highestEnergyPhoton)
            {
                highestEnergyPhoton = pfoEnergy;
                m_pHighestEnergyPhoton = pReconstructedParticle;
            }
        }
    }
}

//===========================================================

void RawPfoAnalysis::CalculateHighestEnergyElectronData()
{
    const double highestEnergyElectronEnergy(m_pHighestEnergyElectron->getEnergy());
    m_pVariables->SetHighestEnergyElectronEnergy(highestEnergyElectronEnergy);

    const double highestEnergyElectronPx(m_pHighestEnergyElectron->getMomentum()[0]);
    const double highestEnergyElectronPy(m_pHighestEnergyElectron->getMomentum()[1]);
    const double highestEnergyElectronPz(m_pHighestEnergyElectron->getMomentum()[2]);
    const double highestEnergyElectronP(std::sqrt(highestEnergyElectronPx * highestEnergyElectronPx + highestEnergyElectronPy * highestEnergyElectronPy + highestEnergyElectronPz * highestEnergyElectronPz));
    m_pVariables->SetHighestEnergyElectronMomentum(highestEnergyElectronP);

    const double highestEnergyElectronTransverseMomentum(std::sqrt(highestEnergyElectronPx * highestEnergyElectronPx + highestEnergyElectronPy * highestEnergyElectronPy));
    m_pVariables->SetHighestEnergyElectronTransverseMomentum(highestEnergyElectronTransverseMomentum);

    const double highestEnergyElectronCosTheta(highestEnergyElectronPz/highestEnergyElectronP);
    m_pVariables->SetHighestEnergyElectronCosTheta(highestEnergyElectronCosTheta);
}

//===========================================================

void RawPfoAnalysis::CalculateHighestEnergyMuonData()
{
    const double highestEnergyMuonEnergy(m_pHighestEnergyMuon->getEnergy());
    m_pVariables->SetHighestEnergyMuonEnergy(highestEnergyMuonEnergy);

    const double highestEnergyMuonPx(m_pHighestEnergyMuon->getMomentum()[0]);
    const double highestEnergyMuonPy(m_pHighestEnergyMuon->getMomentum()[1]);
    const double highestEnergyMuonPz(m_pHighestEnergyMuon->getMomentum()[2]);
    const double highestEnergyMuonP(std::sqrt(highestEnergyMuonPx * highestEnergyMuonPx + highestEnergyMuonPy * highestEnergyMuonPy + highestEnergyMuonPz * highestEnergyMuonPz));
    m_pVariables->SetHighestEnergyMuonMomentum(highestEnergyMuonP);

    const double highestEnergyMuonTransverseMomentum(std::sqrt(highestEnergyMuonPx * highestEnergyMuonPx + highestEnergyMuonPy * highestEnergyMuonPy));
    m_pVariables->SetHighestEnergyMuonTransverseMomentum(highestEnergyMuonTransverseMomentum);

    const double highestEnergyMuonCosTheta(highestEnergyMuonPz/highestEnergyMuonP);
    m_pVariables->SetHighestEnergyMuonCosTheta(highestEnergyMuonCosTheta);
}

//===========================================================

void RawPfoAnalysis::CalculateHighestEnergyPhotonData()
{
    const double highestEnergyPhotonEnergy(m_pHighestEnergyPhoton->getEnergy());
    m_pVariables->SetHighestEnergyPhotonEnergy(highestEnergyPhotonEnergy);

    const double highestEnergyPhotonPx(m_pHighestEnergyPhoton->getMomentum()[0]);
    const double highestEnergyPhotonPy(m_pHighestEnergyPhoton->getMomentum()[1]);
    const double highestEnergyPhotonPz(m_pHighestEnergyPhoton->getMomentum()[2]);
    const double highestEnergyPhotonP(std::sqrt(highestEnergyPhotonPx * highestEnergyPhotonPx + highestEnergyPhotonPy * highestEnergyPhotonPy + highestEnergyPhotonPz * highestEnergyPhotonPz));
    m_pVariables->SetHighestEnergyPhotonMomentum(highestEnergyPhotonP);

    const double highestEnergyPhotonTransverseMomentum(std::sqrt(highestEnergyPhotonPx * highestEnergyPhotonPx + highestEnergyPhotonPy * highestEnergyPhotonPy));
    m_pVariables->SetHighestEnergyPhotonTransverseMomentum(highestEnergyPhotonTransverseMomentum);

    const double highestEnergyPhotonCosTheta(highestEnergyPhotonPz/highestEnergyPhotonP);
    m_pVariables->SetHighestEnergyPhotonCosTheta(highestEnergyPhotonCosTheta);
}

//===========================================================

void RawPfoAnalysis::CalculateHighestEnergyPfoData()
{
    const double highestEnergyPfoEnergy(m_pHighestEnergyPfo->getEnergy());
    m_pVariables->SetHighestEnergyPfoEnergy(highestEnergyPfoEnergy);

    const double highestEnergyPfoPx(m_pHighestEnergyPfo->getMomentum()[0]);
    const double highestEnergyPfoPy(m_pHighestEnergyPfo->getMomentum()[1]);
    const double highestEnergyPfoPz(m_pHighestEnergyPfo->getMomentum()[2]);
    const double highestEnergyPfoP(std::sqrt(highestEnergyPfoPx * highestEnergyPfoPx + highestEnergyPfoPy * highestEnergyPfoPy + highestEnergyPfoPz * highestEnergyPfoPz));
    m_pVariables->SetHighestEnergyPfoMomentum(highestEnergyPfoP);

    const double highestEnergyPfoTransverseMomentum(std::sqrt(highestEnergyPfoPx * highestEnergyPfoPx + highestEnergyPfoPy * highestEnergyPfoPy));
    m_pVariables->SetHighestEnergyPfoTransverseMomentum(highestEnergyPfoTransverseMomentum);

    const double highestEnergyPfoCosTheta(highestEnergyPfoPz/highestEnergyPfoP);
    m_pVariables->SetHighestEnergyPfoCosTheta(highestEnergyPfoCosTheta);

    const int highestEnergyPfoPDG(m_pHighestEnergyPfo->getType());
    m_pVariables->SetHighestEnergyPfoPDG(highestEnergyPfoPDG);
}

//===========================================================

