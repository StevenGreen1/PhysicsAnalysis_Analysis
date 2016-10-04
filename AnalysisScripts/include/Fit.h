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
//#include <iostream>
//#include <limits>
//#include <sstream>
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

    public:
        /**
         *  @brief Constructor
         *
         *  @param processVector vector of processes to include in analysis
         */
        Fit(const ProcessVector &processVector, PostMVASelection *pPostMVASelection);

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
         *  @param pTH1F_Distribution distribution with non zero alpha4 and alpha5
         *  @param pTH1F_Distribution_Sample distribution to base log likelihood from
         *  @param nll negative log likelihood to set
         */
        void CalculateLogLikelihood1D(TH1F *pTH1F_Distribution, TH1F *pTH1F_Distribution_Sample, double &nll);

        /**
         *  @brief Save distribution to root macro
         */
        void SaveDistribution();

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

        ProcessVector         m_processVector;              ///< Vector of all processes
        PostMVASelection     *m_pPostMVASelection;          ///< Container for all selection cuts
        int                   m_a4IntMin;                   ///< Minimum integer step for alpha 4 sensitivity
        int                   m_a4IntMax;                   ///< Maximum integer step for alpha 4 sensitivity
        float                 m_a4Step;                     ///< Step in alpha 4 per integer move
        int                   m_a5IntMin;                   ///< Minimum integer step for alpha 5 sensitivity
        int                   m_a5IntMax;                   ///< Maximum integer step for alpha 5 sensitivity
        float                 m_a5Step;                     ///< Step in alpha 5 per integer move
        TH1F                 *m_pTH1F_DistributionJ_Sample; ///< 1D distribution of sigma against cos theta star jet(from W/Z)
        TH1F                 *m_pTH1F_DistributionW_Sample; ///< 1D distribution of sigma against cos theta star W/Z
        DoubleVector          m_Alpah4;
        DoubleVector          m_Alpah5;
        DoubleVector          m_NLLW;
        DoubleVector          m_NLLJ;

};

#endif
