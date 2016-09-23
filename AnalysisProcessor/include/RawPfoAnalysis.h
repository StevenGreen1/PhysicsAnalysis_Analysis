/**
 *  @file   SelectionProcessor/include/RawPfoAnalysis.h
 *
 *  @brief  Header file for the raw pfo analysis class.
 *
 *  $Log: $
 */

#ifndef PFO_ANALYSIS_H
#define PFO_ANALYSIS_H 1

#include <cmath>
#include <string>
#include <vector>

#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "UTIL/PIDHandler.h"

#include "TLorentzVector.h"

#include "Variables.h"

class RawPfoAnalysis 
{
    public:
        /**
         *  @brief Constructor
         */
        RawPfoAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables);

        /**
         *  @brief Destructor
         */
        ~RawPfoAnalysis();

    private:
        /** 
         *   @brief Run the jet analysis process to set variables of interest
         */
        void Process();

        /**
         *  @brief Set highest energy electron, muon, photon and pfo
         *
         *  @param pLCCollection Collection of Pfos to read in
         */
        void SetHighestEnergyPFOs(const EVENT::LCCollection *pLCCollection);

        /**
         *  @brief Record data for highest energy electron
         */
        void CalculateHighestEnergyElectronData();

        /**
         *  @brief Record data for highest energy muon
         */
        void CalculateHighestEnergyMuonData();

        /**
         *  @brief Record data for highest energy photon
         */
        void CalculateHighestEnergyPhotonData();

        /**
         *  @brief Record data for highest energy pfo
         */
        void CalculateHighestEnergyPfoData();

        Variables                          *m_pVariables;               ///< Variables of interest to set for analysis
        const EVENT::ReconstructedParticle *m_pHighestEnergyElectron;   ///< Highest energy electron 
        const EVENT::ReconstructedParticle *m_pHighestEnergyMuon;       ///< Highest energy muon
        const EVENT::ReconstructedParticle *m_pHighestEnergyPhoton;     ///< Highest energy photon
        const EVENT::ReconstructedParticle *m_pHighestEnergyPfo;        ///< Highest energy pfo
};

#endif // #ifndef PFO_ANALYSIS_H
