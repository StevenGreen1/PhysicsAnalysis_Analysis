/**
 *  @file   AnalysisScripts/include/PreSelection.h
 * 
 *  @brief  Header file for the variables class.
 * 
 *  $Log: $
 */

#ifndef PRE_SELECTION_H
#define PRE_SELECTION_H 1

#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "TChain.h"
#include "TInterpreter.h"
#include "TTree.h"

#include "Process.h"

using namespace analysis_namespace;

class PreSelection
{
    typedef std::vector<const Process*> ProcessVector;

    public:
        /**
         *  @brief Constructor
         */
        PreSelection(const ProcessVector &processVector);

        /**
         *  @brief Destructor
         */
        ~PreSelection();

        /**
         *  @brief Apply preselection cut
         */
        void ApplyPreSelection();

        /**
         *  @brief Set transverse momentum cut
         *
         *  @param low transverse momentum cut
         *  @param high transverse momentum cut
         */
        void ApplyTransverseMomentumCut(double low, double high);

        /**
         *  @brief Set invariant mass cut
         *
         *  @param low invariant mass cut
         *  @param high invariant mass cut
         */
        void ApplyInvariantMassCut(double low, double high);

        /**
         *  @brief Set invariant mass boson cut
         *
         *  @param low invariant mass boson cut
         *  @param high invariant mass boson cut
         */
        void ApplyBosonInvariantMassCut(double low, double high);

        /**
         *  @brief Set b tag cut
         *
         *  @param low b tag cut
         *  @param high b tag cut
         */
        void ApplyBTagCut(double low, double high);

        /**
         *  @brief Set number of isolated leptons cut
         *
         *  @param low number of isolated leptons
         *  @param high number of isolated leptons
         */
        void ApplyNIsolatedLeptonCut(int low, int high);

        /**
         *  @brief Print to screen all bool, int, double and selected vector member variables
         */
        void Print();

        /**
         *  @brief Reset all variables for next event
         */
        void Clear();

        /**
         *  @brief Return m_nIsolatedLeptonsLow
         */
        int GetNumberOfIsolatedLeptonsLowCut() const;

        /**
         *  @brief Return m_nIsolatedLeptonsHigh
         */
        int GetNumberOfIsolatedLeptonsHighCut() const;

        /**
         *  @brief Return m_transverseMomentumLow
         */
        double GetTransverseMomentumLowCut() const;

        /**
         *  @brief Return m_transverseMomentumHigh
         */
        double GetTransverseMomentumHighCut() const;

        /**
         *  @brief Return m_invariantMassSystemLow
         */
        double GetInvariantMassSystemLowCut() const;

        /**
         *  @brief Return m_invariantMassSystemHigh
         */
        double GetInvariantMassSystemHighCut() const;

        /**
         *  @brief Return m_invariantMassBosonLow
         */
        double GetInvariantMassBosonLowCut() const;

        /**
         *  @brief Return m_invariantMassBosonHigh
         */
        double GetInvariantMassBosonHighCut() const;

        /**
         *  @brief Return m_bTagLow
         */
        double GetBTagLowCut() const;

        /**
         *  @brief Return m_bTagHigh
         */
        double GetBTagHighCut() const;

    private:
        ProcessVector m_processVector;            ///< Processes including TChains to apply cuts on
        int           m_nIsolatedLeptonsLow;      ///< Low number of isolated leptons cut
        int           m_nIsolatedLeptonsHigh;     ///< High number of isolated leptons cut
        double        m_transverseMomentumLow;    ///< Low transverse momentum cut
        double        m_transverseMomentumHigh;   ///< High transverse momentum cut
        double        m_invariantMassSystemLow;   ///< Low invariant mass cut
        double        m_invariantMassSystemHigh;  ///< High invariant mass cut
        double        m_invariantMassBosonLow;    ///< Low invariant mass boson cut
        double        m_invariantMassBosonHigh;   ///< High invariant mass boson cut
        double        m_bTagLow;                  ///< Low b tag cut
        double        m_bTagHigh;                 ///< High b tag cut

};

#endif // #ifndef PRE_SELECTION_H
