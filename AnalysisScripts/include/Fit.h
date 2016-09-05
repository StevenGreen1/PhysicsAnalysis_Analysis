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
        Fit(const ProcessVector &processVector);

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
         *  @brief Extract the generator serial number for a given file
         *
         *  @param filename to extract generator serial number from
         */
        std::string GetGeneratorSerialNumber(std::string filename);

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
        TH1F                 *m_pTH1F_DistributionJ_Sample; ///< 1D distribution of sigma against cos theta star jet(from W/Z)
        TH1F                 *m_pTH1F_DistributionW_Sample; ///< 1D distribution of sigma against cos theta star W/Z
        DoubleVector          m_Alpah4;
        DoubleVector          m_Alpah5;
        DoubleVector          m_NLLW;
        DoubleVector          m_NLLJ;

};

#endif
