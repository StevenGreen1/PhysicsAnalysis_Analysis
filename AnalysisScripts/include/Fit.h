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
#include <memory>
#include <string>
#include <vector>

#include "TApplication.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TGraph2D.h"
#include "TFile.h"
#include "TH2F.h"
#include "THStack.h"
#include "TLegend.h"

#include "EventNumbers.h"
#include "PostMVASelection.h"
#include "Process.h"
#include "CouplingAnalysis.h"

class Fit
{
    typedef std::vector<std::shared_ptr<const Process> > ProcessVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;
    typedef std::vector<std::string> StringVector;
    typedef std::map<int, TH1F*> IntHistMap;
    typedef std::map<int, std::map<int, std::shared_ptr<TH1F> > > IntIntHistMap;
    typedef std::map<int, std::map<int, std::shared_ptr<TH2F> > > IntInt2DHistMap;
    typedef std::map<float, std::map<float, float> > FloatFloatFloatMap;
    typedef std::map<std::string, std::shared_ptr<TH1F> > StringHistMap;

    public:
        /**
         *  @brief Constructor
         *
         *  @param processVector vector of processes to include in analysis
         *  @param pCouplingAnalysis pointer to coupling analysis class for weight information
         *  @param descriptor Optional string to attach to filenames
         */
        Fit(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis, std::string descriptor = "");

        /**
         *  @brief Default destructor
         */
        ~Fit();

    private:
        /**
         *  @brief Initialise histograms for reweighting
         */
        void Initialise();

        /**
         *  @brief Clear variables for next run
         */
        void Clear();

        /**
         *  @brief Delete pointers in map
         */
        template <class Map>
        void DeletePointersInMap(Map map);

        /**
         *  @brief Fill distribution of intertest
         */
        void FillDistribution();

        /**
         *  @brief Analyse distributions and look at negative log likelihoods
         */
        void AnalyseDistribution();

        /**
         *  @brief Analyse distributions and look at negative log likelihoods for cos theta star W jets
         *
         *  @param pTH1FRef Reference distribution for log likelihood
         *  @param mapAlphaIntToHist Map of alpha ints to histograms with weights
         *  @param mapAlphaToNLL Map of alpha float values to NLL
         */
        void AnalyseCTSJets(std::shared_ptr<TH1F> pTH1FRef, IntIntHistMap &mapAlphaIntToHist, FloatFloatFloatMap &mapAlphaToNLL);

        /**
         *  @brief Make stack process plots for cos theta star W jets
         */
        void MakeStackCTSWJets();

        /**
         *  @brief Analyse distributions and look at negative log likelihoods for cos theta star W bosons
         */
        void AnalyseCTSWBosons();

        /**
         *  @brief Analyse distributions and look at negative log likelihoods for cos theta star W jets vs cos theta star W bosons
         *
         *  @param pTH2FRef Reference distribution for log likelihood
         *  @param mapAlphaIntToHist Map of alpha ints to histograms with weights
         *  @param mapAlphaToNLL Map of alpha float values to NLL
         */
        void AnalyseCTSJets_vs_CTSBosons(std::shared_ptr<TH2F> pTH2FRef, IntInt2DHistMap &mapAlphaIntToHist, FloatFloatFloatMap &mapAlphaToNLL);

        /**
         *  @brief Calculate negative log likelihood for a given distribution for non-zero alpha4 and alpha5 based on distribution with zero alpha4 and alpah5
         *
         *  @param pTH1F distribution with non zero alpha4 and alpha5
         *  @param pTH1FRef reference distribution to base log likelihood from
         */
        double CalculateLogLikelihood1D(std::shared_ptr<TH1F> pTH1F, std::shared_ptr<TH1F> pTH1FRef);

        /**
         *  @brief Calculate negative log likelihood for a given 2D distribution for non-zero alpha4 and alpha5 based on distribution with zero alpha4 and alpah5
         *
         *  @param pTH2F distribution with non zero alpha4 and alpha5
         *  @param pTH2FRef reference distribution to base log likelihood from
         */
        double CalculateLogLikelihood2D(std::shared_ptr<TH2F> pTH2F, std::shared_ptr<TH2F> pTH2FRef);

        /**
         *  @brief Save distribution to root macro
         */
        void SaveDistribution();

        /**
         *  @brief Populate TGraph using map
         *
         *  @param tGraph2D to populate
         *  @param floatFloatFloatMap map contains data to put into graph
         */
        void PopulateLogLikelihoodGraph(TGraph2D &tGraph2D, FloatFloatFloatMap &floatFloatFloatMap);

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

        ProcessVector         m_processVector;                  ///< Vector of all processes
        PostMVASelection     *m_pPostMVASelection;              ///< Container for all selection cuts
        CouplingAnalysis     *m_pCouplingAnalysis;              ///< Coupling analysis to use in fit
        std::string           m_rootFileName;                   ///< Name of output results root file
        TFile                *m_pTFile;                         ///< Root file for results
        const std::string     m_descriptor;                     ///< Optional string to attack to plots/filename etc 

        int                   m_alpha4IntMinGlobal;             ///< Minimum integer step for alpha 4 sensitivity
        int                   m_alpha4IntMaxGlobal;             ///< Maximum integer step for alpha 4 sensitivity
        float                 m_alpha4StepGlobal;               ///< Step in alpha 4 per integer move
        int                   m_alpha5IntMinGlobal;             ///< Minimum integer step for alpha 5 sensitivity
        int                   m_alpha5IntMaxGlobal;             ///< Maximum integer step for alpha 5 sensitivity
        float                 m_alpha5StepGlobal;               ///< Step in alpha 5 per integer move
        int                   m_alpha4IntMin;                   ///< Minimum integer step for alpha 4 sensitivity for a run
        int                   m_alpha4IntMax;                   ///< Maximum integer step for alpha 4 sensitivity for a run
        float                 m_alpha4Step;                     ///< Step in alpha 4 per integer move for a run
        int                   m_alpha5IntMin;                   ///< Minimum integer step for alpha 5 sensitivity for a run
        int                   m_alpha5IntMax;                   ///< Maximum integer step for alpha 5 sensitivity for a run
        float                 m_alpha5Step;                     ///< Step in alpha 5 per integer move for a run

        float                 m_wBosonMass;                     ///< W Boson Mass
        float                 m_zBosonMass;                     ///< Z Boson Mass

        const int             m_binsInFit;                      ///< Number of bins to use in costheta*jet fit
        std::shared_ptr<TH1F> m_pTH1F_CTSWJetsRef;              ///< Distribution of cos theta star from jets from W boson
        std::shared_ptr<TH1F> m_pTH1F_CTSZJetsRef;              ///< Distribution of cos theta star from jets from Z boson
        std::shared_ptr<TH1F> m_pTH1F_CTSWBosonsRef;            ///< Distribution of cos theta star from W boson
        std::shared_ptr<TH1F> m_pTH1F_CTSZBosonsRef;            ///< Distribution of cos theta star from Z boson
        std::shared_ptr<TH2F> m_pTH2F_CTSWJets_vs_CTSWBosonsRef;///< Distribution of cos theta star from jets vs cos theta star from W boson
        std::shared_ptr<TH2F> m_pTH2F_CTSZJets_vs_CTSZBosonsRef;///< Distribution of cos theta star from jets vs cos theta star from Z boson

        IntIntHistMap         m_mapAlphaIntToCTSWJets;                 ///< Map of alpha4 and alpha5 int to histogram of cos theta star for W boson jets with weights given by alpha4 and alpha5 int multiplied by step
        IntIntHistMap         m_mapAlphaIntToCTSZJets;                 ///< Map of alpha4 and alpha5 int to histogram of cos theta star for Z boson jets with weights given by alpha4 and alpha5 int multiplied by step
        IntIntHistMap         m_mapAlphaIntToCTSWBosons;               ///< Map of alpha4 and alpha5 int to histogram of cos theta star for W bosons with weights given by alpha4 and alpha5 int multiplied by step
        IntIntHistMap         m_mapAlphaIntToCTSZBosons;               ///< Map of alpha4 and alpha5 int to histogram of cos theta star for Z bosons with weights given by alpha4 and alpha5 int multiplied by step
        IntInt2DHistMap       m_mapAlphaIntToCTSWJets_vs_CTSWBosons;   ///< Map of alpha4 and alpha5 int to histogram of cos theta star for W boson jets vs cos theta star for W boson with weights given by alpha4 and alpha5 int multiplied by step
        IntInt2DHistMap       m_mapAlphaIntToCTSZJets_vs_CTSZBosons;   ///< Map of alpha4 and alpha5 int to histogram of cos theta star for Z boson jets vs cos theta star for W boson with weights given by alpha4 and alpha5 int multiplied by step
        StringHistMap         m_eventTypeToCTSJets;             ///< Process name to histogram of cos theta star for W boson jets 

        FloatFloatFloatMap    m_nllCTSWJets;                    ///< Map of alpha4 to alpha5 to negative log likelihood, used for plotting for W bosons
        FloatFloatFloatMap    m_nllCTSZJets;                    ///< Map of alpha4 to alpha5 to negative log likelihood, used for plotting for Z bosons
        FloatFloatFloatMap    m_nllCTSWJets_vs_CTSWBosons;      ///< Map of alpha4 to alpha5 to negative log likelihood, used for plotting for W bosons
        FloatFloatFloatMap    m_nllCTSZJets_vs_CTSZBosons;      ///< Map of alpha4 to alpha5 to negative log likelihood, used for plotting for Z bosons

        FloatVector           m_red;                            ///< Red RGB for plotting
        FloatVector           m_green;                          ///< Green RGB for plotting
        FloatVector           m_blue;                           ///< Blue RGB for plotting
        IntVector             m_fillStyle;                      ///< Fill style for plotting
};

#endif
