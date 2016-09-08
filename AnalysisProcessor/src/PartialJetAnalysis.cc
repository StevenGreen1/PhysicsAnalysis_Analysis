/**
 *  @file   SelectionProcessor/src/PartialJetAnalysis.cc
 *
 *  @brief  Implementation of the partial jet analysis class.
 *
 *  $Log: $
 */

#include "PartialJetAnalysis.h"

//===========================================================

PartialJetAnalysis::PartialJetAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables, const int nJets):
    m_NJets(nJets),
    m_pVariables(variables)
{
    this->CalculateJetClusteringVariableYij(pLCCollection);
    this->Process();
}

//===========================================================

PartialJetAnalysis::~PartialJetAnalysis()
{
}

//===========================================================

void PartialJetAnalysis::Process()
{
}

//===========================================================

void PartialJetAnalysis::CalculateJetClusteringVariableYij(const EVENT::LCCollection *pLCCollection)
{
    PIDHandler pidHandler(pLCCollection);
    const int algIndexYij(pidHandler.getAlgorithmID("yth"));
    const ParticleID &particleID(pidHandler.getParticleID(pLCCollection->getElementAt(0), algIndexYij));

    if (m_NJets == 2)
    {
        std::string stringY12("y12");
        std::string stringY23("y23");
        const double parameterY12(particleID.getParameters()[pidHandler.getParameterIndex(algIndexYij, stringY12)]);
        const double parameterY23(particleID.getParameters()[pidHandler.getParameterIndex(algIndexYij, stringY23)]);

        const double minusLogY12Separation((parameterY12 > std::numeric_limits<double>::epsilon()) ? - log10(parameterY12) : 0.0);
        const double minusLogY23Separation((parameterY23 > std::numeric_limits<double>::epsilon()) ? - log10(parameterY23) : 0.0);

        m_pVariables->SetY12(minusLogY12Separation);
        m_pVariables->SetY23(minusLogY23Separation);
    }
    else if (m_NJets == 4)
    {
        std::string stringY34("y34");
        std::string stringY45("y45");
        const double parameterY34(particleID.getParameters()[pidHandler.getParameterIndex(algIndexYij, stringY34)]);
        const double parameterY45(particleID.getParameters()[pidHandler.getParameterIndex(algIndexYij, stringY45)]);

        const double minusLogY34Separation((parameterY34 > std::numeric_limits<double>::epsilon()) ? - log10(parameterY34) : 0.0);
        const double minusLogY45Separation((parameterY45 > std::numeric_limits<double>::epsilon()) ? - log10(parameterY45) : 0.0);

        m_pVariables->SetY34(minusLogY34Separation);
        m_pVariables->SetY45(minusLogY45Separation);
    }
    else if (m_NJets == 6)
    {
        std::string stringY56("y56");
        std::string stringY67("y67");
        const double parameterY56(particleID.getParameters()[pidHandler.getParameterIndex(algIndexYij, stringY56)]);
        const double parameterY67(particleID.getParameters()[pidHandler.getParameterIndex(algIndexYij, stringY67)]);

        const double minusLogY56Separation((parameterY56 > std::numeric_limits<double>::epsilon()) ? - log10(parameterY56) : 0.0);
        const double minusLogY67Separation((parameterY67 > std::numeric_limits<double>::epsilon()) ? - log10(parameterY67) : 0.0);

        m_pVariables->SetY56(minusLogY56Separation);
        m_pVariables->SetY67(minusLogY67Separation);
    }
}

//===========================================================

