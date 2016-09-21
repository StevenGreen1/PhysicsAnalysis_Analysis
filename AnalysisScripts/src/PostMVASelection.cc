/**
 *  @file   SelectionProcessor/src/PostMVASelection.cc 
 * 
 *  @brief  Implementation of the variables class.
 * 
 *  $Log: $
 */

#include "PostMVASelection.h"

using namespace analysis_namespace;

//===========================================================

PostMVASelection::PostMVASelection(const ProcessVector &processVector) : 
    m_bdtLow(-std::numeric_limits<double>::max()),
    m_bdtHigh(std::numeric_limits<double>::max()),
    m_processVector(processVector)
{
}

//===========================================================

PostMVASelection::~PostMVASelection()
{
}

//===========================================================

void PostMVASelection::ApplyPostMVASelection()
{
    std::cout << "Process & NEvts & PostMVASelection NEvts & PostMVASelection Normalised NEvts \\\\" << std::endl;

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it++)
    {
        const Process *pProcess(*it);
        TChain *pTChain(pProcess->GetPostMVATChain());

        double bdt(std::numeric_limits<double>::max());

        pTChain->SetBranchAddress("BDT", &bdt);

        int counter(0);

        for (unsigned int i = 0; i < pTChain->GetEntries(); i++)
        {
            pTChain->GetEntry(i);

            if (bdt < m_bdtLow  or m_bdtHigh < bdt)
                continue;

            counter++;
        }

        double crossSection(pProcess->GetCrossSection());
        double luminosity(pProcess->GetLuminosity());
        double eventWeight(crossSection*luminosity/(double)(pTChain->GetEntries()));
        std::string evtType(pProcess->GetEventType());

        std::cout << std::setprecision(4) << evtType << " " << pTChain->GetEntries() << " " << counter << " " << (double)(counter)*eventWeight << std::endl;
    }
}

//===========================================================

void PostMVASelection::ApplyBDTCut(double low, double high)
{
    m_bdtLow = low;
    m_bdtHigh = high;
}

//===========================================================

