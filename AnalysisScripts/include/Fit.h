/**
 *  @file   AnalysisScripts/include/Fit.h 
 * 
 *  @brief  Header file for the process class.
 * 
 *  $Log: $
 */

#ifndef FIT_H
#define FIT_H

#include <algorithm>
//#include <iostream>
//#include <limits>
//#include <sstream>
//#include <string>
#include <vector>

#include "TCanvas.h"
#include "TFile.h"
#include "TH2F.h"

#include "Process.h"

class Fit
{
    typedef std::vector<const Process*> ProcessVector;
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
         *  @brief Work out derivative of m_distribution 
         */
        void SetDerivative();

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

        ProcessVector         m_processVector;           ///< Vector of all processes
        TH2F                 *m_distribution;            ///< 2D distribution of sigma against cos theta star W/Z and cos theta star jet(from W/Z)
        TH2F                 *m_derivative;              ///< 2D distribution of derivate of m_distribution 
};

#endif
