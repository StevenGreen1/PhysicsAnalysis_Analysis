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

PostMVASelection::PostMVASelection(const ProcessVector &processVector, PreSelection *pPreSelection) : 
    m_bdtLow(-std::numeric_limits<double>::max()),
    m_bdtHigh(std::numeric_limits<double>::max()),
    m_processVector(processVector),
    m_pPreSelection(pPreSelection)
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

    for (const auto &pProcess: m_processVector)
    {
        TChain *pTChain(pProcess->GetPostMVATChain());

        Int_t nIsolatedLeptons(std::numeric_limits<float>::max());
        Double_t transverseMomentum(std::numeric_limits<float>::max());
        Double_t invariantMassSystem(std::numeric_limits<float>::max());
        Double_t bdt(std::numeric_limits<double>::max());

        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("BDT", &bdt);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);

        int counter(0);

        for (unsigned int i = 0; i < pTChain->GetEntries(); i++)
        {
            pTChain->GetEntry(i);

            if (bdt < m_bdtLow or m_bdtHigh < bdt)
                continue;
            if (nIsolatedLeptons < m_pPreSelection->GetNumberOfIsolatedLeptonsLowCut() or m_pPreSelection->GetNumberOfIsolatedLeptonsHighCut() < nIsolatedLeptons)
                continue;
            if (transverseMomentum < m_pPreSelection->GetTransverseMomentumLowCut() or m_pPreSelection->GetTransverseMomentumHighCut() < transverseMomentum)
                continue;
            if (invariantMassSystem < m_pPreSelection->GetInvariantMassSystemLowCut() or m_pPreSelection->GetInvariantMassSystemHighCut() < invariantMassSystem)
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

void PostMVASelection::MakeWeightList(bool saveTxtFile)
{
    m_eventsNeedingWeights.clear();

    for (const auto &pProcess: m_processVector)
    {
        if (pProcess->GetEventType() != "ee_nunuqqqq")
            continue;

        TChain *pTChain(pProcess->GetPostMVATChain());

        Int_t globalEventNumber(std::numeric_limits<int>::max());
        Int_t nIsolatedLeptons(std::numeric_limits<int>::max());
        Double_t transverseMomentum(std::numeric_limits<double>::max());
        Double_t invariantMassSystem(std::numeric_limits<double>::max());
        Double_t bdt(std::numeric_limits<double>::max());

        pTChain->SetBranchAddress("GlobalEventNumber", &globalEventNumber);
        pTChain->SetBranchAddress("NumberOfIsolatedLeptons", &nIsolatedLeptons);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem);
        pTChain->SetBranchAddress("BDT", &bdt);

        for (unsigned int i = 0; i < pTChain->GetEntries(); i++)
        {
            pTChain->GetEntry(i);

            if (bdt < m_bdtLow or m_bdtHigh < bdt)
                continue;
            if (nIsolatedLeptons < m_pPreSelection->GetNumberOfIsolatedLeptonsLowCut() or m_pPreSelection->GetNumberOfIsolatedLeptonsHighCut() < nIsolatedLeptons)
                continue;
            if (transverseMomentum < m_pPreSelection->GetTransverseMomentumLowCut() or m_pPreSelection->GetTransverseMomentumHighCut() < transverseMomentum)
                continue;
            if (invariantMassSystem < m_pPreSelection->GetInvariantMassSystemLowCut() or m_pPreSelection->GetInvariantMassSystemHighCut() < invariantMassSystem)
                continue;

            m_eventsNeedingWeights.push_back(globalEventNumber);
        }
    }

    if (saveTxtFile)
        this->SaveEventsNeedingWeightingList();
}

//===========================================================

void PostMVASelection::SaveEventsNeedingWeightingList()
{
    IntVector generatorNumbersSaved;
    std::ofstream generatorNumbersFile;
    generatorNumbersFile.open("GeneratorNumbersToConcatenate.txt");
    EventNumbers *pEventNumbers = new EventNumbers();

    for (auto eventNumber: m_eventsNeedingWeights)
    {
        int generatorNumber(pEventNumbers->GetSimulationNumberFromGlobal(eventNumber));

        if (std::find(generatorNumbersSaved.begin(), generatorNumbersSaved.end(), generatorNumber) == generatorNumbersSaved.end())
        {
            generatorNumbersFile << generatorNumber << std::endl;
            generatorNumbersSaved.push_back(generatorNumber);
        }
    }
    generatorNumbersFile.close();
    delete pEventNumbers;
}

//===========================================================

IntVector PostMVASelection::GetEventsNeedingWeightsList() const
{
    return m_eventsNeedingWeights;
}

//===========================================================

PreSelection* PostMVASelection::GetPreSelection()
{
    return m_pPreSelection;
}

//===========================================================

double PostMVASelection::GetBDTLowCut() const
{
    return m_bdtLow;
}

//===========================================================

double PostMVASelection::GetBDTHighCut() const
{
    return m_bdtHigh;
}

//===========================================================

