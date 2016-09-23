/**
 *  @file   SelectionProcessor/include/IsolatedLeptonPfoAnalysis.h
 *
 *  @brief  Header file for the isolated lepton pfo analysis class.
 *
 *  $Log: $
 */

#ifndef ISOLATED_LEPTON_PFO_ANALYSIS_H
#define ISOLATED_LEPTON_PFO_ANALYSIS_H 1

#include <cmath>
#include <string>
#include <vector>

#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "UTIL/PIDHandler.h"

#include "TLorentzVector.h"

#include "Variables.h"

class IsolatedLeptonPfoAnalysis 
{
    typedef std::vector<const EVENT::ReconstructedParticle*> ParticleVector;

    public:
        /**
         *  @brief Constructor
         */
        IsolatedLeptonPfoAnalysis(const EVENT::LCCollection *pLCCollection, Variables *&variables);

        /**
         *  @brief Destructor
         */
        ~IsolatedLeptonPfoAnalysis();

    private:
        /** 
         *   @brief Run the jet analysis process to set variables of interest
         */
        void Process();

        /**
         *  @brief Set number of isolated leptons
         */
        void CalculateNumberOfIsolatedLeptons();

        /**
         *  @brief Determine first and second highest energy leptons in isolated lepton collection and save variables
         */
        void DistinguishHighestEnergyIsolatedLeptons();

        /**
         *  @brief Calculate and store information regarding highest energy isolated lepton
         */
        void CalculateHighestEnergyIsolatedLeptonData();

        /**
         *  @brief Calculate and store information regarding second highest energy isolated lepton
         */
        void CalculateSecondHighestEnergyIsolatedLeptonData();

        Variables                          *m_pVariables;                         ///< Variables of interest to set for analysis
        ParticleVector                      m_isolatedLeptons;                    ///< Vector of isolated lepton PFOs
        int                                 m_nIsolatedLeptons;                   ///< Number of isolated leptons
        const EVENT::ReconstructedParticle *m_pHighestEnergyIsolatedLepton;       ///< Highest energy isolated lepton
        const EVENT::ReconstructedParticle *m_pSecondHighestEnergyIsolatedLepton; ///< Second highest energy isolated lepton 
};

#endif // #ifndef ISOLATED_LEPTON_PFO_ANALYSIS_H
