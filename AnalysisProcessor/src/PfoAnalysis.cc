/**
 *  @file   SelectionProcessor/src/PfoAnalysis.cc
 *
 *  @brief  Implementation of the pfo analysis class.
 *
 *  $Log: $
 */

#include "PfoAnalysis.h"

//===========================================================

PfoAnalysis::PfoAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables):
    m_pVariables(variables)
{
    this->SetHighestEnergyPFOs(pLCCollection);
    this->Process();
}

//===========================================================

PfoAnalysis::~PfoAnalysis()
{
}

//===========================================================

void PfoAnalysis::Process()
{
    this->CalculateHighestEnergyElectronData();
    this->CalculateHighestEnergyMuonData();
    this->CalculateHighestEnergyPhotonData();
    this->CalculateHighestEnergyPfoData();
}

//===========================================================

void PfoAnalysis::SetHighestEnergyPFOs(const EVENT::LCCollection *pLCCollection)
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
            m_pHighestEnergyPFO = pReconstructedParticle;
        }

        if (std::abs(pReconstructedParticle->getType()) == 11)
        {
            if (pfoEnergy > highestEnergyElectron)
            {
                m_pHighestEnergyElectron = pReconstructedParticle;
            }
        }
        else if (std::abs(pReconstructedParticle->getType()) == 13)
        {
            if (pfoEnergy > highestEnergyMuon)
            {
                m_pHighestEnergyMuon = pReconstructedParticle;
            }
        }
        else if (std::abs(pReconstructedParticle->getType()) == 22)
        {
            if (pfoEnergy > highestEnergyPhoton)
            {
                m_pHighestEnergyPhoton = pReconstructedParticle;
            }
        }
    }
}

//===========================================================

void PfoAnalysis::CalculateHighestEnergyElectronData()
{
    const double highestEnergyElectronEnergy(m_pHighestEnergyElectron->getEnergy());
    m_pVariables->SetHighestEnergyElectronEnergy(highestEnergyElectronEnergy);

    const double highestEnergyElectronPx(pReconstructedParticle->getMomentum()[0]);
    const double highestEnergyElectronPy(pReconstructedParticle->getMomentum()[1]);
    const double highestEnergyElectronPz(pReconstructedParticle->getMomentum()[2]);
    const double highestEnergyElectronP(std::sqrt(highestEnergyElectronPx * highestEnergyElectronPx + highestEnergyElectronPy * highestEnergyElectronPy + highestEnergyElectronPz * highestEnergyElectronPz));
    m_pVariables->SetHighestEnergyElectronMomentum(highestEnergyElectronP);

    const double highestEnergyElectronTransverseMomentum(std::sqrt(highestEnergyElectronPx * highestEnergyElectronPx + highestEnergyElectronPy * highestEnergyElectronPy));
    m_pVariables->SetHighestEnergyElectronTransverseMomentum(highestEnergyElectronTransverseMomentum);

    const double highestEnergyElectronCosTheta(highestEnergyElectronPz/highestEnergyElectronP);
    m_pVariables->SetHighestEnergyElectronCosTheta(highestEnergyElectronCosTheta);
}

//===========================================================

void PfoAnalysis::CalculateHighestEnergyMuonData()
{
    const double highestEnergyMuonEnergy(m_pHighestEnergyMuon->getEnergy());
    m_pVariables->SetHighestEnergyMuonEnergy(highestEnergyMuonEnergy);

    const double highestEnergyMuonPx(pReconstructedParticle->getMomentum()[0]);
    const double highestEnergyMuonPy(pReconstructedParticle->getMomentum()[1]);
    const double highestEnergyMuonPz(pReconstructedParticle->getMomentum()[2]);
    const double highestEnergyMuonP(std::sqrt(highestEnergyMuonPx * highestEnergyMuonPx + highestEnergyMuonPy * highestEnergyMuonPy + highestEnergyMuonPz * highestEnergyMuonPz));
    m_pVariables->SetHighestEnergyMuonMomentum(highestEnergyMuonP);

    const double highestEnergyMuonTransverseMomentum(std::sqrt(highestEnergyMuonPx * highestEnergyMuonPx + highestEnergyMuonPy * highestEnergyMuonPy));
    m_pVariables->SetHighestEnergyMuonTransverseMomentum(highestEnergyMuonTransverseMomentum);

    const double highestEnergyMuonCosTheta(highestEnergyMuonPz/highestEnergyMuonP);
    m_pVariables->SetHighestEnergyMuonCosTheta(highestEnergyMuonCosTheta);
}

//===========================================================

void PfoAnalysis::CalculateHighestEnergyPhotonData()
{
    const double highestEnergyPhotonEnergy(m_pHighestEnergyPhoton->getEnergy());
    m_pVariables->SetHighestEnergyPhotonEnergy(highestEnergyPhotonEnergy);

    const double highestEnergyPhotonPx(pReconstructedParticle->getMomentum()[0]);
    const double highestEnergyPhotonPy(pReconstructedParticle->getMomentum()[1]);
    const double highestEnergyPhotonPz(pReconstructedParticle->getMomentum()[2]);
    const double highestEnergyPhotonP(std::sqrt(highestEnergyPhotonPx * highestEnergyPhotonPx + highestEnergyPhotonPy * highestEnergyPhotonPy + highestEnergyPhotonPz * highestEnergyPhotonPz));
    m_pVariables->SetHighestEnergyPhotonMomentum(highestEnergyPhotonP);

    const double highestEnergyPhotonTransverseMomentum(std::sqrt(highestEnergyPhotonPx * highestEnergyPhotonPx + highestEnergyPhotonPy * highestEnergyPhotonPy));
    m_pVariables->SetHighestEnergyPhotonTransverseMomentum(highestEnergyPhotonTransverseMomentum);

    const double highestEnergyPhotonCosTheta(highestEnergyPhotonPz/highestEnergyPhotonP);
    m_pVariables->SetHighestEnergyPhotonCosTheta(highestEnergyPhotonCosTheta);
}

//===========================================================

void PfoAnalysis::CalculateHighestEnergyPfoData()
{
    const double highestEnergyPfoEnergy(m_pHighestEnergyPfo->getEnergy());
    m_pVariables->SetHighestEnergyPfoEnergy(highestEnergyPfoEnergy);

    const double highestEnergyPfoPx(pReconstructedParticle->getMomentum()[0]);
    const double highestEnergyPfoPy(pReconstructedParticle->getMomentum()[1]);
    const double highestEnergyPfoPz(pReconstructedParticle->getMomentum()[2]);
    const double highestEnergyPfoP(std::sqrt(highestEnergyPfoPx * highestEnergyPfoPx + highestEnergyPfoPy * highestEnergyPfoPy + highestEnergyPfoPz * highestEnergyPfoPz));
    m_pVariables->SetHighestEnergyPfoMomentum(highestEnergyPfoP);

    const double highestEnergyPfoTransverseMomentum(std::sqrt(highestEnergyPfoPx * highestEnergyPfoPx + highestEnergyPfoPy * highestEnergyPfoPy));
    m_pVariables->SetHighestEnergyPfoTransverseMomentum(highestEnergyPfoTransverseMomentum);

    const double highestEnergyPfoCosTheta(highestEnergyPfoPz/highestEnergyPfoP);
    m_pVariables->SetHighestEnergyPfoCosTheta(highestEnergyPfoCosTheta);
}

//===========================================================

