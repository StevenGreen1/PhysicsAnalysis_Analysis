/**
 *  @file   SelectionProcessor/src/PreSelection.cc 
 * 
 *  @brief  Implementation of the variables class.
 * 
 *  $Log: $
 */

#include "PreSelection.h"

using namespace analysis_namespace;

//===========================================================

PreSelection::PreSelection(const ProcessVector &processVector) : 
    m_nIsolatedLeptonsLow(-std::numeric_limits<int>::max()),
    m_nIsolatedLeptonsHigh(std::numeric_limits<int>::max()),
    m_transverseMomentumLow(-std::numeric_limits<double>::max()),
    m_transverseMomentumHigh(std::numeric_limits<double>::max()),
    m_invariantMassSystemLow(-std::numeric_limits<double>::max()),
    m_invariantMassSystemHigh(std::numeric_limits<double>::max()),
    m_invariantMassBosonLow(-std::numeric_limits<double>::max()),
    m_invariantMassBosonHigh(std::numeric_limits<double>::max()),
    m_bTagLow(-std::numeric_limits<double>::max()),
    m_bTagHigh(std::numeric_limits<double>::max()),
    m_processVector(processVector)
{
}

//===========================================================

PreSelection::~PreSelection()
{
}

//===========================================================

void PreSelection::ApplyPreSelection()
{
    std::cout << "Process & NEvts & PreSelection NEvts & PreSelection Normalised NEvts \\\\" << std::endl;

    for (const auto &pProcess: m_processVector)
    {
        TChain *pTChain(pProcess->GetFullTChain());
        double weight(pProcess->GetFullProcessWeight());

        int nIsolatedLeptons(std::numeric_limits<int>::max());
        double transverseMomentum(std::numeric_limits<double>::max());
        double invariantMassSystem(std::numeric_limits<double>::max());
/*
        double bTag1(std::numeric_limits<double>::max());
        double bTag2(std::numeric_limits<double>::max());
        double bTag3(std::numeric_limits<double>::max());
        double bTag4(std::numeric_limits<double>::max());
        double invMassW1(std::numeric_limits<double>::max());
        double invMassW2(std::numeric_limits<double>::max());
        double invMassZ1(std::numeric_limits<double>::max());
        double invMassZ2(std::numeric_limits<double>::max());
*/
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
/*
        pTChain->SetBranchAddress("BTagForJet1", &bTag1);
        pTChain->SetBranchAddress("BTagForJet2", &bTag2);
        pTChain->SetBranchAddress("BTagForJet3", &bTag3);
        pTChain->SetBranchAddress("BTagForJet4", &bTag4);
        pTChain->SetBranchAddress("InvariantMassWBoson1", &invMassW1);
        pTChain->SetBranchAddress("InvariantMassWBoson2", &invMassW2);
        pTChain->SetBranchAddress("InvariantMassZBoson1", &invMassZ1);
        pTChain->SetBranchAddress("InvariantMassZBoson2", &invMassZ2);
*/
        int counter(0);

        for (unsigned int i = 0; i < pTChain->GetEntries(); i++)
        {
            pTChain->GetEntry(i);

            if (nIsolatedLeptons < m_nIsolatedLeptonsLow or m_nIsolatedLeptonsHigh < nIsolatedLeptons)
                continue;

            if (transverseMomentum < m_transverseMomentumLow  or m_transverseMomentumHigh < transverseMomentum)
                continue;

            if (invariantMassSystem < m_invariantMassSystemLow or m_invariantMassSystemHigh < invariantMassSystem)
                continue;
/*
            if (bTag1 < m_bTagLow or m_bTagHigh < bTag1 or bTag2 < m_bTagLow or m_bTagHigh < bTag2 or bTag3 < m_bTagLow or m_bTagHigh < bTag3 or bTag4 < m_bTagLow or m_bTagHigh < bTag4)
                continue;

            if (invMassW1 < m_invariantMassBosonLow or m_invariantMassBosonHigh < invMassW1)
                continue;

            if (invMassW2 < m_invariantMassBosonLow or m_invariantMassBosonHigh < invMassW2)
                continue;

            if (invMassZ1 < m_invariantMassBosonLow or m_invariantMassBosonHigh < invMassZ1)
                continue;

            if (invMassZ2 < m_invariantMassBosonLow or m_invariantMassBosonHigh < invMassZ2)
                continue;
*/
            counter++;
        }

        std::string evtType(pProcess->GetEventType());
        std::cout << std::setprecision(4) << evtType << " " << pTChain->GetEntries() << " " << counter << " " << (double)(counter)*weight << std::endl;
    }
}

//===========================================================

void PreSelection::ApplyTransverseMomentumCut(double low, double high)
{
    m_transverseMomentumLow = low;
    m_transverseMomentumHigh = high;
}

//===========================================================

void PreSelection::ApplyInvariantMassCut(double low, double high)
{
    m_invariantMassSystemLow = low;
    m_invariantMassSystemHigh = high;
}

//===========================================================

void PreSelection::ApplyBosonInvariantMassCut(double low, double high)
{
    m_invariantMassBosonLow = low;
    m_invariantMassBosonHigh = high;
}

//===========================================================

void PreSelection::ApplyBTagCut(double low, double high)
{
    m_bTagLow = low;
    m_bTagHigh = high;
}

//===========================================================

void PreSelection::ApplyNIsolatedLeptonCut(int low, int high)
{
    m_nIsolatedLeptonsLow = low;
    m_nIsolatedLeptonsHigh = high;
}

//===========================================================

void PreSelection::Print()
{
    std::cout << "m_transverseMomentumLow        : " << m_transverseMomentumLow << std::endl;
    std::cout << "m_transverseMomentumHigh       : " << m_transverseMomentumHigh << std::endl;
    std::cout << "m_invariantMassSystemLow       : " << m_invariantMassSystemLow << std::endl;
    std::cout << "m_invariantMassSystemHigh      : " << m_invariantMassSystemHigh << std::endl;
//    std::cout << " : " <<  << std::endl;
}

//===========================================================

void PreSelection::Clear()
{
    m_transverseMomentumLow = -std::numeric_limits<double>::max();
    m_transverseMomentumHigh = std::numeric_limits<double>::max();
    m_invariantMassSystemLow = -std::numeric_limits<double>::max();
    m_invariantMassSystemHigh = std::numeric_limits<double>::max();
}

//===========================================================

int PreSelection::GetNumberOfIsolatedLeptonsLowCut() const
{
    return m_nIsolatedLeptonsLow;
}

//===========================================================

int PreSelection::GetNumberOfIsolatedLeptonsHighCut() const
{
    return m_nIsolatedLeptonsHigh;
}

//===========================================================

double PreSelection::GetTransverseMomentumLowCut() const
{
    return m_transverseMomentumLow;
}

//===========================================================

double PreSelection::GetTransverseMomentumHighCut() const
{
    return m_transverseMomentumHigh;
}

//===========================================================

double PreSelection::GetInvariantMassSystemLowCut() const
{
    return m_invariantMassSystemLow;
}

//===========================================================

double PreSelection::GetInvariantMassSystemHighCut() const
{
    return m_invariantMassSystemHigh;
}

//===========================================================

double PreSelection::GetInvariantMassBosonLowCut() const
{
    return m_invariantMassBosonLow;
}

//===========================================================

double PreSelection::GetInvariantMassBosonHighCut() const
{
    return m_invariantMassBosonHigh;
}

//===========================================================

double PreSelection::GetBTagLowCut() const
{
    return m_bTagLow;
}

//===========================================================

double PreSelection::GetBTagHighCut() const
{
    return m_bTagHigh;
}

//===========================================================

