/**
  *  @file   AnalysisScripts/include/MakePlots.h 
  * 
  *  @brief  Header file for the make plots class.
  * 
  *  $Log: $
  */

#ifndef MAKE_PLOTS_H
#define MAKE_PLOTS_H

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "TCanvas.h"
#include "TChain.h"
#include "TH1F.h"

#include "Process.h"

class MakePlots
{
    typedef std::vector<Process*> ProcessVector;

    public:
        /**
         *  @brief Constructor 
         */
        MakePlots(ProcessVector processVector);

        /**
         *  @brief Destructor 
         */
        ~MakePlots();

    private:
        /**
         *  @brief Make plot of WW invariant mass
         */
        void MakeWWPlot();

        ProcessVector m_processVector;
};

#endif
