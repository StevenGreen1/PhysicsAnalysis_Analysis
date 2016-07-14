/**
  *  @file   AnalysisScripts/include/MakePlots.h 
  * 
  *  @brief  Header file for the make plots class.
  * 
  *  $Log: $
  */

#ifndef MAKE_PLOTS_H
#define MAKE_PLOTS_H

#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH1I.h"

#include "Process.h"

class MakePlots
{
    typedef std::vector<Process*> ProcessVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<std::string> StringVector;
    typedef std::vector<TH1I*> IntPlotVector;
    typedef std::vector<TH1F*> FloatPlotVector;

    typedef std::map<TH1I*, int> Int1DPlotToPositionMap;
    typedef std::map<TH1F*, int> Float1DPlotToPositionMap;
    typedef std::map<int, std::string> IntToStringMap;

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

        void LoadData();

        void Register1DPlot(std::string variableName, std::string objectType, int nBins, float lowBin, float highBin);

        void RegisterIntToRead(std::string variableName, int nBins, float lowBin, float highBin);

        void RegisterFloatToRead(const std::string &variableName, int nBins, float lowBin, float highBin);

        template <class T>
        std::string NumberToString(T number);

        ProcessVector m_processVector;
        Int1DPlotToPositionMap m_intPlots;
        StringVector m_intVariablesToRead;
        Float1DPlotToPositionMap m_floatPlots;
        StringVector m_floatVariablesToRead;
};

#endif
