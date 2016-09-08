/**
 *  @file   SelectionProcessor/include/PartialJetAnalysis.h
 *
 *  @brief  Header file for the partial jet analysis class.
 *
 *  $Log: $
 */

#ifndef PARTIAL_JET_ANALYSIS_H
#define PARTIAL_JET_ANALYSIS_H 1

#include <string>
#include <vector>

#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "UTIL/PIDHandler.h"

#include "TLorentzVector.h"

#include "Variables.h"

class PartialJetAnalysis 
{
    public:
        /**
         *  @brief Constructor
         */
        PartialJetAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables, int nJets);

        /**
         *  @brief Destructor
         */
        ~PartialJetAnalysis();

    private:
        /** 
         *   @brief Run the jet analysis process to set variables of interest
         */
        void Process();

        /**
         *  @brief Find the jet clustering variable yij
         *
         *  @param pLCCollection Collection of Pfos to read in
         *  @param yij jet clustering variable of choice
         */
        void CalculateJetClusteringVariableYij(const EVENT::LCCollection *pLCCollection);

        const int             m_NJets;             ///< Number of jets used in jet clustering
        Variables            *m_pVariables;        ///< Variables of interest to set for analysis
};

#endif // #ifndef PARTIAL_JET_ANALYSIS_H
