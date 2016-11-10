/**
 *  @file   AnalysisScripts/include/PostMVASelection.h
 * 
 *  @brief  Header file for the post MVA selection class.
 * 
 *  $Log: $
 */

#ifndef POST_MVA_SELECTION_H
#define POST_MVA_SELECTION_H 1

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "TChain.h"
#include "TInterpreter.h"
#include "TTree.h"

#include "EventNumbers.h"
#include "PreSelection.h"
#include "Process.h"

using namespace analysis_namespace;

class PostMVASelection
{
    typedef std::vector<const Process*> ProcessVector;

    public:
        /**
         *  @brief Constructor
         */
        PostMVASelection(const ProcessVector &processVector, PreSelection *pPreSelection);

        /**
         *  @brief Destructor
         */
        ~PostMVASelection();

        /**
         *  @brief Apply preselection cut
         */
        void ApplyPostMVASelection();

        /**
         *  @brief Set bdt cut
         *
         *  @param low bdt cut
         *  @param high bdt cut
         */
        void ApplyBDTCut(double low, double high);

        /**
         *  @brief Save list of generator numbers requiring concatenation of weight information
         */
        void SaveEventsNeedingWeightingList();

        /**
         *  @brief Make a list of global event numbers for events passing the event selection
         *
         *  @param saveTxtFile for running condor jobs
         */
        void MakeWeightList(bool saveTxtFile = false);
 
        /**
         *  @brief Get list of global event numbers for events passing the event selection
         */
        IntVector GetEventsNeedingWeightsList() const;

        /**
         *  @brief Return m_pPreSelection
         */
        PreSelection* GetPreSelection();

        /**
         *  @brief Return m_bdtLow
         */
        double GetBDTLowCut() const;

        /**
         *  @brief Return m_bdtHigh
         */
        double GetBDTHighCut() const;

    private:
        PreSelection *m_pPreSelection;            ///< PreSelection object containing preselection cuts <- Can and should move to private variable
        ProcessVector m_processVector;            ///< Processes including TChains to apply cuts on
        IntVector     m_eventsNeedingWeights;     ///< List of global event numbers requiring weights

        double        m_bdtLow;                   ///< Low bdt cut
        double        m_bdtHigh;                  ///< High bdt cut

};

#endif // #ifndef POST_MVA_SELECTION_H
