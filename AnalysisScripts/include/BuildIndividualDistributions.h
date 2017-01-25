/**
 *  @file   AnalysisScripts/include/BuildIndividualDistributions.h 
 * 
 *  @brief  Header file for the build distributions class.
 * 
 *  $Log: $
 */

#ifndef BUILD_INDIVIDUAL_DISTRIBUTIONS_H
#define BUILD_INDIVIDUAL_DISTRIBUTIONS_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"

#include "EventNumbers.h"
#include "PostMVASelection.h"
#include "Process.h"
#include "CouplingAnalysis.h"

class BuildIndividualDistributions
{
    typedef std::vector<const Process*> ProcessVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;
    typedef std::map<std::string, TH1F*> OneDHistogramMap;
    typedef std::map<std::string, TH2F*> TwoDHistogramMap;

    public:
        /**
         *  @brief Constructor
         *
         *  @param processVector vector of processes to include in analysis
         *  @param pCouplingAnalysis pointer to coupling analysis class for weight information
         *  @param descriptor Optional string to attach to filenames
         *  @param nEvtsStart
         *
         */
        BuildIndividualDistributions(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis, int nEvtsStart, int nEvtsEnd, std::string descriptor = "", std::string outputPath = "");

        /**
         *  @brief Default destructor
         */
        ~BuildIndividualDistributions();

        /**
         *  @brief Set numbers of bins to use in fit
         *
         *  @param nBins number of bins to use in fit
         */
        void SetNBins(const int &nBins);

        /**
         *  @brief Perform simple scan of alpha4/alpha5 to make distributions for chi2 calculation
         *
         *  @param backgrounds does distribution scan including background
         */
        void BuildDistribution(bool backgrounds = false);

    private:
        /**
         *  @brief Initialise reference histograms for reweighting
         */
        void InitialiseReference();

        /**
         *  @brief Initialise histograms for reweighting
         */
        void Initialise();

        /**
         *  @brief See if name is available name for root object and if not delete pre exisiting object so that it is a valid name choice
         *
         *  @param name of root object
         */
        TString SafeName(const TString &name);

        /**
         *  @brief Clear reference histograms for next chi2 calcaultion
         */
        void ClearReference();

        /**
         *  @brief Clear histograms for next chi2 calcaultion
         */
        void Clear();

        /**
         *  @brief Fill distribution of intertest for alpha4 = alpha5 = 0
         */
        void FillReferenceDistribution();

        /**
         *  @brief Fill distribution of intertest
         *
         *  @param alpha4
         *  @param alpha5
         */
        void FillDistribution(const double alpha4, const double alpha5);

        /**
         *  @brief Make random string for histogram name to prevent root troubles...
         */
        std::string RandomName();

        /**
         *  @brief Convert a number to a string
         *
         *  @param T number to convert to string
         */
        template <class T>
        std::string NumberToString(T Number);

        ProcessVector         m_processVector;                              ///< Vector of all processes
        PostMVASelection     *m_pPostMVASelection;                          ///< Container for all selection cuts
        CouplingAnalysis     *m_pCouplingAnalysis;                          ///< Coupling analysis to use in fit
        int                   m_nEvtsStart;                                 ///< Event number to start
        int                   m_nEvtsEnd;                                   ///< Event number to end
        const std::string     m_outputPath;                                 ///< Path to send results to
        const std::string     m_descriptor;                                 ///< Optional string to attack to plots/filename etc
        const std::string     m_rootFileName;                               ///< Name of output results root file
        int                   m_energy;                                     ///< Energy of distributions being fitted
        TFile                *m_pTFile;                                     ///< Root file for results
        TTree                *m_pTTree;                                     ///< Root tree for results
        int                   m_nBins;                                      ///< Number of bins to use in costheta*jet fit
        OneDHistogramMap        m_cosThetaStarSynJets;                      ///< Distribution of cos theta star from jets from synergy boson all, map of process to histogram 
        OneDHistogramMap        m_cosThetaStarSynJetsRef;                   ///< Distribution of cos theta star from jets from synergy boson all ref, map of process to histogram 
        OneDHistogramMap        m_cosThetaStarSynBosons;                    ///< Distribution of cos theta star from bosons from synergy boson all, map of process to histogram
        OneDHistogramMap        m_cosThetaStarSynBosonsRef;                 ///< Distribution of cos theta star from bosons from synergy boson all ref, map of process to histogram
        TwoDHistogramMap        m_cosThetaStarSynJets_vs_Bosons;            ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson all, map of process to histogram
        TwoDHistogramMap        m_cosThetaStarSynJets_vs_BosonsRef;         ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson all ref, map of process to histogram
};

#endif
