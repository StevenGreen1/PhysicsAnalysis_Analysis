/**
 *  @file   AnalysisScripts/include/PostMVASelection.h
 * 
 *  @brief  Header file for the post MVA selection class.
 * 
 *  $Log: $
 */

#ifndef POST_MVA_SELECTION_H
#define POST_MVA_SELECTION_H 1

#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "TChain.h"
#include "TInterpreter.h"
#include "TTree.h"

#include "Process.h"

using namespace analysis_namespace;

class PostMVASelection
{
    typedef std::vector<const Process*> ProcessVector;

    public:
        /**
         *  @brief Constructor
         */
        PostMVASelection(const ProcessVector &processVector);

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

        double        m_bdtLow;                   ///< Low bdt cut
        double        m_bdtHigh;                  ///< High bdt cut

    private:
        ProcessVector m_processVector;            ///< Processes including TChains to apply cuts on
};

#endif // #ifndef POST_MVA_SELECTION_H
