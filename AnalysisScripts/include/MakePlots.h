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
#include "THStack.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"

#include "Process.h"

class MakePlots
{
    typedef std::vector<const Process*> ProcessVector;

    typedef std::vector<double> DoubleVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<std::string> StringVector;

    typedef std::map<TH1F*, int> Int1DPlotToPositionMap;
    typedef std::map<TH1F*, int> Double1DPlotToPositionMap;
    typedef std::map<TH2F*, std::pair<int,int> > Double2DPlotToPositionMap;
    typedef std::map<int, std::string> IntToStringMap;
    typedef std::map<TH1F*, const Process*> Double1DPlotToProcessMap;
    typedef std::map<TH2F*, const Process*> Double2DPlotToProcessMap;

    public:
        /**
         *  @brief Constructor 
         *
         *  @param processVector vector of processes to include in analysis
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
         *  @brief Make a 2D box plot histogram with two histograms (different process event types) on top of each other.  Must register 2D histograms to function properly
         *
         *  @param variableX x axis vairable name
         *  @param variableY y axis variable name
         *  @param process1 event type
         *  @param process2 event type
         */
         void Make2DBoxPlot(std::string variableX, std::string variableY, std::string process1, std::string process2);

        /**
         *  @brief Register the chosen 2D histogram for filling and the variables for loading
         *  @param variableNameX name of variable stored in root tree to plot on x axis
         *  @param variableNameY name of variable stored in root tree to plot on y axis
         *  @param nBinsX number of bins to use for x axis
         *  @param lowBinX low bin edge of x axis
         *  @param highBinX high bin edge of x axis
         *  @param nBinsY number of bins to use for y axis
         *  @param lowBinY low bin edge of y axis
         *  @param highBinY high bin edge of y axis
         */
        void Register2DPlot(const Process *pProcess, const std::string &variableNameX, const std::string &variableNameY, const int &nBinsX, const double &lowBinX, const double &highBinX, const int &nBinsY, const double &lowBinY, const double &highBinY);

        /**
         *  @brief Register the chosen 2D histogram for filling and the variables for loading.  From doublevector input plot at(0) vs at(1)
         *  @param variableNameX name of variable stored in root tree to plot on x axis
         *  @param nBinsX number of bins to use for x axis
         *  @param lowBinX low bin edge of x axis
         *  @param highBinX high bin edge of x axis
         */
        void Register2DVectorPlot(const Process *pProcess, const std::string &variableNameX, const int &nBinsX, const double &lowBinX, const double &highBinX);

        /**
         *  @brief Register the chosen 1D histogram for filling and the variables for loading
         *
         *  @param variableName name of variable stored in root tree
         *  @param objectType int or double variable
         *  @param nBins number of bins in histogram
         *  @param lowBin low bin edge of histogram
         *  @param highBin high bin edge of histogram 
         */
        void Register1DPlot(const Process *pProcess, const std::string &variableName, const std::string &objectType, const int &nBins, const double &lowBin, const double &highBin);


        /**
         *  @brief Register the chosen 1D integer histogram for filling and the variables for loading
         *
         *
         *  @param variableName name of variable stored in root tree
         *  @param nBins number of bins in histogram
         *  @param lowBin low bin edge of histogram
         *  @param highBin high bin edge of histogram 
         */
        void Register1DIntPlot(const Process *pProcess, const std::string &variableName, const int &nBins, const double &lowBin, const double &highBin);

        /**
         *  @brief Register the chosen 1D doubleing point histogram for filling and the variables for loading
         *
         *  @param variableName name of variable stored in root tree
         *  @param nBins number of bins in histogram
         *  @param lowBin low bin edge of histogram
         *  @param highBin high bin edge of histogram
         */
        void Register1DDoublePlot(const Process *pProcess, const std::string &variableName, const int &nBins, const double &lowBin, const double &highBin);

        /**
         *  @brief Register the chosen 1D integer histogram for filling and the variables for loading (stored as int vector)
         *
         *
         *  @param variableName name of variable stored in root tree
         *  @param nBins number of bins in histogram
         *  @param lowBin low bin edge of histogram
         *  @param highBin high bin edge of histogram 
         */
        void Register1DIntVectorPlot(const Process *pProcess, const std::string &variableName, const int &nBins, const double &lowBin, const double &highBin);

        /**
         *  @brief Register the chosen 1D doubleing point histogram for filling and the variables for loading (stored as double vector)
         *
         *  @param variableName name of variable stored in root tree
         *  @param nBins number of bins in histogram
         *  @param lowBin low bin edge of histogram
         *  @param highBin high bin edge of histogram
         */
        void Register1DDoubleVectorPlot(const Process *pProcess, const std::string &variableName, const int &nBins, const double &lowBin, const double &highBin);

        /**
         *  @brief Make random string for histogram name to prevent root troubles...
         */
        std::string RandomName();

        /**
         *  @brief Convert a number to a string 
         *
         *  @param number to convert
         */
        template <class T>
        std::string NumberToString(const T &number);

        ProcessVector              m_processVector;              ///< Vector of all processes

        Int1DPlotToPositionMap     m_1DIntPlots;                 ///< Map of 1D integer histograms to position
        StringVector               m_intVariablesToRead;         ///< Vector of all integer variables to read from tree
        Double1DPlotToProcessMap   m_int1DPlotToProcess;         ///< Map of 1D integer histograms to processes

        Double1DPlotToPositionMap  m_1DDoublePlots;              ///< Map of 1D doubleing point histograms to position
        StringVector               m_doubleVariablesToRead;      ///< Vector of all doubleing point variables to read from tree
        Double1DPlotToProcessMap   m_double1DPlotToProcess;      ///< Map of 1D doubleing point histograms to processes

        Int1DPlotToPositionMap     m_1DVecIntPlots;              ///< Map of 1D integer histograms to position (IntVector in tree)
        StringVector               m_vecIntVariablesToRead;      ///< Vector of all integer variables to read from tree (IntVector in tree)
        Double1DPlotToProcessMap   m_vecInt1DPlotToProcess;      ///< Map of 1D integer histograms to processes (IntVec in tree)

        Double1DPlotToPositionMap  m_1DVecDoublePlots;           ///< Map of 1D doubleing point histograms to position (DoubleVector in tree)
        StringVector               m_vecDoubleVariablesToRead;   ///< Vector of all doubleing point variables to read from tree (DoubleVector in tree)
        Double1DPlotToProcessMap   m_vecDouble1DPlotToProcess;   ///< Map of 1D doubleing point histograms to processes (DoubleVec in tree)

        Double2DPlotToPositionMap  m_2DDoublePlots;              ///< Map of all 2D doubleing point histograms to positions
        Double2DPlotToProcessMap   m_double2DPlotToProcess;      ///< Map of 2D doubleing point histograms to processes

        Double2DPlotToPositionMap  m_2DVecDoublePlots;           ///< Map of 2D doubleing point histograms to position (DoubleVector in tree)
        Double2DPlotToProcessMap   m_vecDouble2DPlotToProcess;   ///< Map of 2D doubleing point histograms to processes (DoubleVec in tree)

};

#endif
