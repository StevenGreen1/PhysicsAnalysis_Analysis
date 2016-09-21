/**
 *  @file   AnalysisScripts/include/TMVAClassificationApplication.h 
 * 
 *  @brief  Header file for the TMVA classifier class.
 * 
 *  $Log: $
 */

#ifndef TMVA_CLASSIFICATION_APPLICATION_H
#define TMVA_CLASSIFICATION_APPLICATION_H

#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "TChain.h"
#include "TFile.h"
#include "TString.h"

#include "TMVA/Reader.h"
#include "TMVA/Tools.h"

#include "Process.h"

class TMVAClassificationApplication
{
    typedef std::vector<const Process*> ProcessVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;

    public:
        /**
         *  @brief Constructor
         */
        TMVAClassificationApplication(ProcessVector processes);

        /**
         *  @brief Default destructor
         */
        ~TMVAClassificationApplication();

    private:
        /**
         *  @brief Extract the generator serial number for a given file
         *
         *  @param filename to extract generator serial number from
         */
        std::string GetGeneratorSerialNumber(std::string filename);

        /**
         *  @brief Convert a number to a string
         *
         *  @param T number to convert to string
         */
        template <class T>
        std::string NumberToString(T Number);
};

#endif
