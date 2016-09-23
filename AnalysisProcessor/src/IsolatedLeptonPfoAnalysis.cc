/**
 *  @file   SelectionProcessor/src/IsolatedLeptonPfoAnalysis.cc
 *
 *  @brief  Implementation of the isolated pfo analysis class.
 *
 *  $Log: $
 */

#include "IsolatedLeptonPfoAnalysis.h"

//===========================================================

IsolatedLeptonPfoAnalysis::IsolatedLeptonPfoAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables):
    m_pVariables(variables),
    m_nIsolatedLeptons(std::numeric_limits<int>::max()),
    m_pHighestEnergyIsolatedLepton(NULL),
    m_pSecondHighestEnergyIsolatedLepton(NULL)
{
    m_isolatedLeptons.clear();

    for (unsigned int entry = 0; entry < pLCCollection->getNumberOfElements(); entry++)
    {
        const EVENT::ReconstructedParticle *pReconstructedParticle = dynamic_cast<EVENT::ReconstructedParticle*>(pLCCollection->getElementAt(entry));
        m_isolatedLeptons.push_back(pReconstructedParticle);
    }

    this->Process();
}

//===========================================================

IsolatedLeptonPfoAnalysis::~IsolatedLeptonPfoAnalysis()
{
}

//===========================================================

void IsolatedLeptonPfoAnalysis::Process()
{
    this->CalculateNumberOfIsolatedLeptons();

    if (m_nIsolatedLeptons == 0)
        return;

    this->DistinguishHighestEnergyIsolatedLeptons();
}

//===========================================================

void IsolatedLeptonPfoAnalysis::CalculateNumberOfIsolatedLeptons()
{
    m_nIsolatedLeptons = m_isolatedLeptons.size();
    m_pVariables->SetNumberOfIsolatedLeptons(m_nIsolatedLeptons);
}

//===========================================================

void IsolatedLeptonPfoAnalysis::DistinguishHighestEnergyIsolatedLeptons()
{
    if (m_nIsolatedLeptons == 1)
    {
        m_pHighestEnergyIsolatedLepton = m_isolatedLeptons.at(0);

        this->CalculateHighestEnergyIsolatedLeptonData();
    }
    else
    {
        double highestEnergyLeptonEnergy(-std::numeric_limits<float>::max());
        double secondHighestEnergyLeptonEnergy(-std::numeric_limits<float>::max());

        for (ParticleVector::iterator iter = m_isolatedLeptons.begin(); iter != m_isolatedLeptons.end(); iter++)
        {
            const EVENT::ReconstructedParticle* pReconstructedParticle(*iter);
            const double pfoEnergy(pReconstructedParticle->getEnergy());

            if (pfoEnergy > highestEnergyLeptonEnergy)
            {
                highestEnergyLeptonEnergy = pfoEnergy;
                m_pHighestEnergyIsolatedLepton = pReconstructedParticle;
            }
            else if (pfoEnergy > secondHighestEnergyLeptonEnergy)
            {
                secondHighestEnergyLeptonEnergy = pfoEnergy;
                m_pSecondHighestEnergyIsolatedLepton = pReconstructedParticle;
            }
        }

        this->CalculateHighestEnergyIsolatedLeptonData();
        this->CalculateSecondHighestEnergyIsolatedLeptonData();
    }
}

//===========================================================

void IsolatedLeptonPfoAnalysis::CalculateHighestEnergyIsolatedLeptonData()
{
    if (m_pHighestEnergyIsolatedLepton == NULL)
        return;

    const double highestEnergyIsolatedLeptonEnergy(m_pHighestEnergyIsolatedLepton->getEnergy());
    m_pVariables->SetHighestEnergyIsolatedLeptonEnergy(highestEnergyIsolatedLeptonEnergy);

    const double highestEnergyIsolatedLeptonPx(m_pHighestEnergyIsolatedLepton->getMomentum()[0]);
    const double highestEnergyIsolatedLeptonPy(m_pHighestEnergyIsolatedLepton->getMomentum()[1]);
    const double highestEnergyIsolatedLeptonPz(m_pHighestEnergyIsolatedLepton->getMomentum()[2]);
    const double highestEnergyIsolatedLeptonP(std::sqrt(highestEnergyIsolatedLeptonPx * highestEnergyIsolatedLeptonPx + highestEnergyIsolatedLeptonPy * highestEnergyIsolatedLeptonPy + highestEnergyIsolatedLeptonPz * highestEnergyIsolatedLeptonPz));
    m_pVariables->SetHighestEnergyIsolatedLeptonMomentum(highestEnergyIsolatedLeptonP);

    const double highestEnergyIsolatedLeptonTransverseMomentum(std::sqrt(highestEnergyIsolatedLeptonPx * highestEnergyIsolatedLeptonPx + highestEnergyIsolatedLeptonPy * highestEnergyIsolatedLeptonPy));
    m_pVariables->SetHighestEnergyIsolatedLeptonTransverseMomentum(highestEnergyIsolatedLeptonTransverseMomentum);

    const double highestEnergyIsolatedLeptonCosTheta(highestEnergyIsolatedLeptonPz/highestEnergyIsolatedLeptonP);
    m_pVariables->SetHighestEnergyIsolatedLeptonCosTheta(highestEnergyIsolatedLeptonCosTheta);

    const int highestEnergyIsolatedLeptonPDG(m_pHighestEnergyIsolatedLepton->getType());
    m_pVariables->SetHighestEnergyIsolatedLeptonPDG(highestEnergyIsolatedLeptonPDG);
}

//===========================================================

void IsolatedLeptonPfoAnalysis::CalculateSecondHighestEnergyIsolatedLeptonData()
{
    if (m_pSecondHighestEnergyIsolatedLepton == NULL)
        return;

    const double secondHighestEnergyIsolatedLeptonEnergy(m_pSecondHighestEnergyIsolatedLepton->getEnergy());
    m_pVariables->SetSecondHighestEnergyIsolatedLeptonEnergy(secondHighestEnergyIsolatedLeptonEnergy);

    const double secondHighestEnergyIsolatedLeptonPx(m_pSecondHighestEnergyIsolatedLepton->getMomentum()[0]);
    const double secondHighestEnergyIsolatedLeptonPy(m_pSecondHighestEnergyIsolatedLepton->getMomentum()[1]);
    const double secondHighestEnergyIsolatedLeptonPz(m_pSecondHighestEnergyIsolatedLepton->getMomentum()[2]);
    const double secondHighestEnergyIsolatedLeptonP(std::sqrt(secondHighestEnergyIsolatedLeptonPx * secondHighestEnergyIsolatedLeptonPx + secondHighestEnergyIsolatedLeptonPy * secondHighestEnergyIsolatedLeptonPy + secondHighestEnergyIsolatedLeptonPz * secondHighestEnergyIsolatedLeptonPz));
    m_pVariables->SetSecondHighestEnergyIsolatedLeptonMomentum(secondHighestEnergyIsolatedLeptonP);
    
    const double secondHighestEnergyIsolatedLeptonTransverseMomentum(std::sqrt(secondHighestEnergyIsolatedLeptonPx * secondHighestEnergyIsolatedLeptonPx + secondHighestEnergyIsolatedLeptonPy * secondHighestEnergyIsolatedLeptonPy));
    m_pVariables->SetSecondHighestEnergyIsolatedLeptonTransverseMomentum(secondHighestEnergyIsolatedLeptonTransverseMomentum);
    
    const double secondHighestEnergyIsolatedLeptonCosTheta(secondHighestEnergyIsolatedLeptonPz/secondHighestEnergyIsolatedLeptonP);
    m_pVariables->SetSecondHighestEnergyIsolatedLeptonCosTheta(secondHighestEnergyIsolatedLeptonCosTheta);

    const int secondHighestEnergyIsolatedLeptonPDG(m_pSecondHighestEnergyIsolatedLepton->getType());
    m_pVariables->SetSecondHighestEnergyIsolatedLeptonPDG(secondHighestEnergyIsolatedLeptonPDG);
}


//===========================================================
