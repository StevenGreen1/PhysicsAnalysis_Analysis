/**
 *  @file   AnalysisScripts/include/BuildDistributions.h 
 * 
 *  @brief  Header file for the build distributions class.
 * 
 *  $Log: $
 */

#ifndef BUILD_DISTRIBUTIONS_H
#define BUILD_DISTRIBUTIONS_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "TApplication.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TFile.h"
#include "TH2F.h"
#include "TH3F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

#include "EventNumbers.h"
#include "PostMVASelection.h"
#include "Process.h"
#include "CouplingAnalysis.h"

class BuildDistributions
{
    typedef std::vector<const Process*> ProcessVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;

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
        BuildDistributions(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis, int nEvtsStart, int nEvtsEnd, std::string descriptor = "", std::string outputPath = "");

        /**
         *  @brief Default destructor
         */
        ~BuildDistributions();

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

        /**
         *  @brief Quick MC analysis functinos for making plots
         */
        void MCBuildDistribution();
        void PairQuarks(TLorentzVector *quark1, TLorentzVector *quark2, TLorentzVector *quark3, TLorentzVector *quark4, double &cosThetaStar1, double &cosThetaStar2);
        void CalculateCosThetaStar(TLorentzVector *quark1, TLorentzVector *quark2, double &cosThetaStar);

        /**
         *  @brief Make plot of event weight for a single event vs alpha4 and alpha5
         *
         *  @param maxEventNumber
         *  @param backgrounds for stepping ranges
         */
        void EventWeightsForSingleEvent(int maxEventNumber, bool backgrounds);

    private:
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
         *  @brief Clear variables for next chi2 calcaultion
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

        /**
         *  @brief Helper pause function
         */
        void Pause();

        ProcessVector         m_processVector;                              ///< Vector of all processes
        PostMVASelection     *m_pPostMVASelection;                          ///< Container for all selection cuts
        CouplingAnalysis     *m_pCouplingAnalysis;                          ///< Coupling analysis to use in fit
        int                   m_nEvtsStart;                                 ///< Event number to start
        int                   m_nEvtsEnd;                                   ///< Event number to end
        const std::string     m_outputPath;                                 ///< Path to send results to
        const std::string     m_descriptor;                                 ///< Optional string to attack to plots/filename etc
        const std::string     m_rootFileName;                               ///< Name of output results root file
        const bool            m_splitDistributions;                         ///< Make a separate W and Z distribution
        int                   m_energy;                                     ///< Energy of distributions being fitted
        TFile                *m_pTFile;                                     ///< Root file for results
        TTree                *m_pTTree;                                     ///< Root tree for results
        int                   m_nBins;                                      ///< Number of bins to use in costheta*jet fit
        int                   m_nBinsMVV;                                   ///< Number of bins to use in MVV fit
        float                 m_lowMVV;                                     ///< Low bin edge of MVV fit
        float                 m_highMVV;                                    ///< High bin edge of MVV fit
        float                 m_wBosonMass;                                 ///< W Boson Mass
        float                 m_zBosonMass;                                 ///< Z Boson Mass
        TH2F                 *m_cosThetaStarSynJets;                        ///< Distribution of cos theta star from jets from synergy boson all 
        TH2F                 *m_cosThetaStarSynJetsRef;                     ///< Distribution of cos theta star from jets from synergy boson all ref 
        TH2F                 *m_cosThetaStarSynJetsBkg;                     ///< Distribution of cos theta star from jets from synergy boson for backgrounds, fill just once
        TH1F                 *m_cosThetaStarSynBosons;                      ///< Distribution of cos theta star from bosons from synergy boson all
        TH1F                 *m_cosThetaStarSynBosonsRef;                   ///< Distribution of cos theta star from bosons from synergy boson all ref
        TH1F                 *m_cosThetaStarSynBosonsBkg;                   ///< Distribution of cos theta star from bosons from synergy boson for backgrounds, fill just once
        TH1F                 *m_mVVSynBosons;                               ///< Distribution of invariant mass of system from synergy boson all
        TH1F                 *m_mVVSynBosonsRef;                            ///< Distribution of invariant mass of system from synergy boson all ref
        TH1F                 *m_mVVSynBosonsBkg;                            ///< Distribution of invariant mass of system from synergy boson for backgrounds, fill just once
};

#endif
