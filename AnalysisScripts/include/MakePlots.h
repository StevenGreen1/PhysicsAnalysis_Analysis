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
#include "TColor.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"

#include "Process.h"

class MakePlots
{
    typedef std::vector<const Process*> ProcessVector;

    typedef std::vector<float> FloatVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<std::string> StringVector;

    typedef std::map<TH1I*, int> Int1DPlotToPositionMap;
    typedef std::map<TH1F*, int> Float1DPlotToPositionMap;
    typedef std::map<TH2F*, std::pair<int,int> > Float2DPlotToPositionMap;
    typedef std::map<int, std::string> IntToStringMap;
    typedef std::map<TH1I*, const Process*> Int1DPlotToProcessMap;
    typedef std::map<TH1F*, const Process*> Float1DPlotToProcessMap;
    typedef std::map<TH2F*, const Process*> Float2DPlotToProcessMap;

    public:
        /**
         *  @brief Constructor 
         */
        MakePlots(const ProcessVector &processVector);

        /**
         *  @brief Destructor 
         */
        ~MakePlots();

    private:
        /**
         *  @brief Write combined process plots in .C format
         */
        void WritePlots();

        /**
         *  @brief Write all individual plots that have been registered in .C format
         */
        void WriteIndividualPlots();

        /**
         *  @brief Load all data from processes in m_processVector and fill requested histograms
         */
        void LoadData();

        /**
         *  @brief Register the chosen 2D histogram for filling and the variables for loading
         *  @param variableNameX name of variable stored in root tree to plot on x axis
         *  @param variableNameY name of variable stored in root tree to plot on y axis
         *  @param nBinsX number of bins to use for x axis
         *  @param lowBinX low bin edge of x axis
         *  @param highBinX hight bin edge of x axis
         *  @param nBinsY number of bins to use for y axis
         *  @param lowBinY low bin edge of y axis
         *  @param highBinY hight bin edge of y axis
         */
        void Register2DPlot(const Process *pProcess, const std::string &variableNameX, const std::string &variableNameY, const int &nBinsX, const float &lowBinX, const float &highBinX, const int &nBinsY, const float &lowBinY, const float &highBinY);

        /**
         *  @brief Register the chosen 1D histogram for filling and the variables for loading
         *
         *  @param variableName name of variable stored in root tree
         *  @param objectType int or float variable
         *  @param nBins number of bins in histogram
         *  @param lowBin low bin edge of histogram
         *  @param highBin high bin edge of histogram 
         */
        void Register1DPlot(const Process *pProcess, const std::string &variableName, const std::string &objectType, const int &nBins, const float &lowBin, const float &highBin);


        /**
         *  @brief Register the chosen 1D integer histogram for filling and the variables for loading
         *
         *
         *  @param variableName name of variable stored in root tree
         *  @param nBins number of bins in histogram
         *  @param lowBin low bin edge of histogram
         *  @param highBin high bin edge of histogram 
         */
        void Register1DIntPlot(const Process *pProcess, const std::string &variableName, const int &nBins, const float &lowBin, const float &highBin);

        /**
         *  @brief Register the chosen 1D floating point histogram for filling and the variables for loading
         *
         *  @param variableName name of variable stored in root tree
         *  @param nBins number of bins in histogram
         *  @param lowBin low bin edge of histogram
         *  @param highBin high bin edge of histogram
         */
        void Register1DFloatPlot(const Process *pProcess, const std::string &variableName, const int &nBins, const float &lowBin, const float &highBin);

        /**
         *  @brief Make random string for histogram name
         */
        std::string RandomName();

        /**
         *  @brief Convert a number to a string 
         *
         *  @param number to convert
         */
        template <class T>
        std::string NumberToString(const T &number);

        ProcessVector m_processVector;
        Int1DPlotToPositionMap m_1DIntPlots;
        StringVector m_intVariablesToRead;
        Float1DPlotToPositionMap m_1DFloatPlots;
        StringVector m_floatVariablesToRead;
        Float2DPlotToPositionMap m_2DPlots;

        Int1DPlotToProcessMap m_int1DPlotToProcess;
        Float1DPlotToProcessMap m_float1DPlotToProcess;
        Float2DPlotToProcessMap m_float2DPlotToProcess;

};

#endif
