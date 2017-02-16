/**
 *  @file   AnalysisScripts/include/Fit.h 
 * 
 *  @brief  Header file for the fit class.
 * 
 *  $Log: $
 */

#ifndef FIT_H
#define FIT_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "TApplication.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TFile.h"
#include "TH2F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TSystemDirectory.h"
#include "TTree.h"

class Fit
{
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;
    typedef std::vector<std::string> StringVector;

    public:
        /**
         *  @brief Constructor
         *
         *  @param descriptor string to read in filenames
         *  @param nBins used in fit
         *  @param inputPath
         *  @param background
         *
         */
        Fit(std::string descriptor, const int energy, const int nBins, std::string inputPath, bool background = false);

        /**
         *  @brief Default destructor
         */
        ~Fit();

        /**
         *  @brief Merge distributions to form chi2 together and calculate chi2
         *
         *  @param background does fit include backgrounds
         */
        void Merge();

        /**
         *  @breif Apply fluctuation of chi2 in fit
         */
        void FluctuateNominal();

    private:
        /**
         *  @brief Find all files with relevant description and add to read in list
         */
        void FindFiles();

        /**
         *  @brief Initialise observed histograms for reweighting
         */
        void InitialiseObserved();

        /**
         *  @brief Initialise expected histograms for reweighting
         */
        void InitialiseExpected();

        /**
         *  @brief Merge all files together for given alpha4 and alpha5.  If observed = true, fill observed distribution
         *
         *  @param alpha4 to use to fill 
         *  @param alpha5 to use to fill
         *  @param observed should fill observed distribution 
         */
        void MergeFiles(float alpha4, float alpha5, bool observed = false);

        /**
         *  @brief See if name is available name for root object and if not delete pre exisiting object so that it is a valid name choice
         *
         *  @param name of root object
         */
        TString SafeName(const TString &name);

        /**
         *  @brief Clear histograms for next chi2 calcaultion
         */
        void Clear();

        /**
         *  @brief Calculate chi2 for a given 1D distribution, observed, with zero alpha4 and alpha5 based on distribution, expected, with non-zero alpha4 and alpah5
         *
         *  @param pTH1F_Expected expected distribution with non zero alpha4 and alpha5
         *  @param pTH1F_Observed observed distribution with zero alpha4 and alphs5
         */
        double CalculateChi2In1D(TH1F *pTH1F_Expected, TH1F *pTH1F_Observed);

        /**
         *  @brief Calculate chi2 for a given 2D distribution, observed, with zero alpha4 and alpha5 based on distribution, expected, with non-zero alpha4 and alpah5
         *
         *  @param pTH2F_Expected expected distribution with non zero alpha4 and alpha5
         *  @param pTH2F_Observed observed distribution with zero alpha4 and alphs5
         */
        double CalculateChi2In2D(TH2F *pTH2F_Expected, TH2F *pTH2F_Observed);

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

        const std::string     m_descriptor;                                 ///< Optional string to attack to plots/filename etc
        const std::string     m_inputPath;                                  ///< Path to send results to
        const int             m_nBins;                                      ///< Number of bins to use in costheta*jet fit
        const int             m_energy;                                     ///< Energy
        const bool            m_background;                                 ///< Backgrounds
        bool                  m_fluctuateNominal;                           ///< Fluctuate the nominal (standard model) using Poisson statistics
        std::string           m_rootFileName;                               ///< Name of output results root file
        StringVector          m_filesToReadIn;                              ///< Vector of files to read in
        const bool            m_splitDistributions;                         ///< Make a separate W and Z distribution
        TFile                *m_pTFile;                                     ///< Root file for results
        TTree                *m_pTTree;                                     ///< Root tree for results
        double                m_alpha4;                                     ///< Alpha 4 value to save to tree 
        double                m_alpha5;                                     ///< Alpha 5 value to save to tree
        double                m_chi2CosThetaStarSynJets;                    ///< Chi2 from cos theta start synergy jets
        double                m_chi2CosThetaStarWSynJets;                   ///< Chi2 from cos theta start synergy jets assumed to be W
        double                m_chi2CosThetaStarZSynJets;                   ///< Chi2 from cos theta start synergy jets assumed to be Z
        double                m_chi2CosThetaStarSynBosons;                  ///< Chi2 from cos theta start synergy boson
        double                m_chi2CosThetaStarWSynBosons;                 ///< Chi2 from cos theta start synergy boson assumed to be W
        double                m_chi2CosThetaStarZSynBosons;                 ///< Chi2 from cos theta start synergy boson assumed to be Z
        double                m_chi2CosThetaStarSynJets_vs_Bosons;          ///< Chi2 from cos theta start synergy jets vs cos theta start synergy boson
        double                m_chi2CosThetaStarWSynJets_vs_Bosons;         ///< Chi2 from cos theta start synergy jets vs cos theta start synergy boson assumed to be W
        double                m_chi2CosThetaStarZSynJets_vs_Bosons;         ///< Chi2 from cos theta start synergy jets vs cos theta start synergy boson assumed to be Z
        TH1F                 *m_cosThetaStarSynJetsExpected;                ///< Distribution of cos theta star from jets from synergy boson, expected
        TH1F                 *m_cosThetaStarSynJetsObserved;                ///< Distribution of cos theta star from jets from synergy boson, observed
        TH1F                 *m_cosThetaStarWSynJetsExpected;               ///< Distribution of cos theta star from jets from synergy boson assumed to be W, expected
        TH1F                 *m_cosThetaStarWSynJetsObserved;               ///< Distribution of cos theta star from jets from synergy boson assumed to be W, observed
        TH1F                 *m_cosThetaStarZSynJetsExpected;               ///< Distribution of cos theta star from jets from synergy boson assumed to be Z, expected
        TH1F                 *m_cosThetaStarZSynJetsObserved;               ///< Distribution of cos theta star from jets from synergy boson assumed to be Z, observed
        TH1F                 *m_cosThetaStarSynBosonsExpected;              ///< Distribution of cos theta star from bosons from synergy boson, expected
        TH1F                 *m_cosThetaStarSynBosonsObserved;              ///< Distribution of cos theta star from bosons from synergy boson, observed
        TH1F                 *m_cosThetaStarWSynBosonsExpected;             ///< Distribution of cos theta star from bosons from synergy boson assumed to be W, expected
        TH1F                 *m_cosThetaStarWSynBosonsObserved;             ///< Distribution of cos theta star from bosons from synergy boson assumed to be W, observed
        TH1F                 *m_cosThetaStarZSynBosonsExpected;             ///< Distribution of cos theta star from bosons from synergy boson assumed to be Z, expected
        TH1F                 *m_cosThetaStarZSynBosonsObserved;             ///< Distribution of cos theta star from bosons from synergy boson assumed to be Z, observed
        TH2F                 *m_cosThetaStarSynJets_vs_BosonsExpected;      ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson, expected
        TH2F                 *m_cosThetaStarSynJets_vs_BosonsObserved;      ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson, observed
        TH2F                 *m_cosThetaStarWSynJets_vs_BosonsExpected;     ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson assumed to be W, expected
        TH2F                 *m_cosThetaStarWSynJets_vs_BosonsObserved;     ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson assumed to be W, observed
        TH2F                 *m_cosThetaStarZSynJets_vs_BosonsExpected;     ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson assumed to be Z, expected
        TH2F                 *m_cosThetaStarZSynJets_vs_BosonsObserved;     ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson assumed to be Z, observed
        FloatVector           m_red;                                        ///< Red RGB for plotting
        FloatVector           m_green;                                      ///< Green RGB for plotting
        FloatVector           m_blue;                                       ///< Blue RGB for plotting
        IntVector             m_fillStyle;                                  ///< Fill style for plotting
};

#endif
