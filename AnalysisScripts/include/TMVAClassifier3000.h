/**
 *  @file   AnalysisScripts/include/TMVAClassifier3000.h 
 * 
 *  @brief  Header file for the TMVA classifier class.
 * 
 *  $Log: $
 */

#ifndef TMVA_CLASSIFIER_3000_H
#define TMVA_CLASSIFIER_3000_H

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "TChain.h"
#include "TFile.h"
#include "TString.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

#include "Process.h"

class TMVAClassifier3000
{
    typedef std::vector<const Process*> ProcessVector;

    public:
        /**
         *  @brief Constructor
         */
        TMVAClassifier3000(ProcessVector sigProcesses, ProcessVector bkgProcesses);

        /**
         *  @brief Default destructor
         */
        ~TMVAClassifier3000();

    private:
};

#endif
