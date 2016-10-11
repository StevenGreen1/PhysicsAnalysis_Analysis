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
#include <string>
#include <vector>

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TFile.h"
#include "TH2F.h"
#include "TLegend.h"

#include "PostMVASelection.h"
#include "Process.h"
#include "CouplingAnalysis.h"

class Fit
{
    typedef std::vector<const Process*> ProcessVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<double> DoubleVector;
    typedef std::vector<std::string> StringVector;
    typedef std::map<int, TH1F*> IntHistMap;
    typedef std::map<int, std::map<int, TH1F*> > IntIntHistMap;

    public:
        /**
         *  @brief Constructor
         *
         *  @param processVector vector of processes to include in analysis
         */
        Fit(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis);

        /**
         *  @brief Default destructor
         */
        ~Fit();

    private:
        /**
         *  @brief Fill distribution of intertest
         */
        void FillDistribution();

        /**
         *  @brief Calculate negative log likelihood for a given distribution for non-zero alpha4 and alpha5 based on distribution with zero alpha4 and alpah5
         *
         *  @param pTH1F distribution with non zero alpha4 and alpha5
         *  @param pTH1FRef reference distribution to base log likelihood from
         */
        double CalculateLogLikelihood(TH1F *pTH1F, TH1F *pTH1FRef);

        /**
         *  @brief Save distribution to root macro
         */
        void SaveDistribution();

        /**
         *  @brief Analyse distributions and look at negative log likelihoods
         */
        void AnalyseDistribution();

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
        int                   m_alpha4IntMin;                   ///< Minimum integer step for alpha 4 sensitivity
        int                   m_alpha4IntMax;                   ///< Maximum integer step for alpha 4 sensitivity
        float                 m_alpha4Step;                     ///< Step in alpha 4 per integer move
        int                   m_alpha5IntMin;                   ///< Minimum integer step for alpha 5 sensitivity
        int                   m_alpha5IntMax;                   ///< Maximum integer step for alpha 5 sensitivity
        float                 m_alpha5Step;                     ///< Step in alpha 5 per integer move
        TH1F                 *m_pTH1FCosThetaStarWJetsRef;      ///< Distribution of cos theta star from jets (from W/Z bosons)
        TH1F                 *m_pTH1FCosThetaStarWRef;          ///< Distribution of cos theta star from W/Z bosons
        IntIntHistMap         m_alphaIntToCosThetaStarW;        ///< Map of alpha4 and alpha5 int to histogram of cos theta star for W bosons with weights given by alpha4 and alpha5 int multiplied by step
        IntIntHistMap         m_alphaIntToCosThetaStarWJets;    ///< Map of alpha4 and alpha5 int to histogram of cos theta star for W boson jets with weights given by alpha4 and alpha5 int multiplied by step
        DoubleVector          m_alpha4;                         ///< Vector of alpha4 values to use for plotting
        DoubleVector          m_alpha5;                         ///< Vector of alpha5 values to use for plotting
        DoubleVector          m_nllCosThetaStarWJets;           ///< Vector of negative log likelihood values to use for plotting
        std::string           m_rootFileName;                   ///< Name of output results root file
        TFile                *m_pTFile;                         ///< Root file for results
};

#endif
