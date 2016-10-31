/**
  *  @file   AnalysisScripts/include/MakeDerivedPlots.h 
  * 
  *  @brief  Header file for the make plots class.
  * 
  *  $Log: $
  */

#ifndef MAKE_DERIVED_PLOTS_H
#define MAKE_DERIVED_PLOTS_H

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

#include "PostMVASelection.h"
#include "PreSelection.h"
#include "Process.h"
#include "Variables.h"

class MakeDerivedPlots
{
    typedef std::vector<std::shared_ptr<const Process> > ProcessVector;

    typedef std::vector<double> DoubleVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<std::string> StringVector;

    public:
        /**
         *  @brief Constructor 
         *
         *  @param processVector vector of processes to include in analysis
         *  @param pPreSelection pointer to class containing preselection information
         *  @param pPostMVASelection optional pointer to class containing post MVA selection information.  Applies the Will overwrite preselection pointer specifed in second argument
         */
        MakeDerivedPlots(const ProcessVector &processVector, PreSelection *pPreSelection, PostMVASelection *pPostMVASelection = NULL);

        /**
         *  @brief Destructor 
         */
        ~MakeDerivedPlots();

    private:
        /**
         *  @brief Convert number to string
         *
         *  @param number to convert
         */
        template <class T>
        std::string NumberToString(const T &number);

        class PlotContainer
        {
            public:
                /**
                 *  @brief Constructor
                 *
                 *  @param varibaleName variable name for plotting
                 *  @param nBins number of bins
                 *  @param xLow low bin edge
                 *  @param xHigh high bin edge
                 */
                PlotContainer(std::string varibaleName, int nBins, double xLow, double xHigh);

                /**
                 *  @brief Return random string for root ermmm features...
                */
                std::string RandomName();

                /**
                 *  @brief Fill histogram, apply weight
                 */
                void Fill(double value, double weight);

                /**
                 *  @brief Draw active hitogram on canvas and add it to stack plot
                 *
                 *  @param processName Active process name
                 */
                void DrawHistograms(std::string processName);

                /**
                 *  @brief Save the stack and multi plot
                 */
                void SavePlots();

            private:
                std::string   m_variableName; ///< Variable name
                THStack      *m_pTHStack;     ///< Stack plot to make
                TCanvas      *m_pTCanvas;     ///< Canvas to draw on
                TLegend      *m_pTLegend;     ///< Legend for plots
                TH1F         *m_pTH1FSig;     ///< Signal histogram of distribution of interest
                TH1F         *m_pTH1F;        ///< Active histogram of distribution of interest
                int           m_nBins;        ///< Number of bins for binning 
                double        m_xLow;         ///< Low bin edge for binning
                double        m_xHigh;        ///< High bin edge for binning
                int           m_colourCounter;///< Colour conuter for drawing plots
                FloatVector  m_red;           ///< RGB red for colours
                FloatVector  m_green;         ///< RGB green for colours
                FloatVector  m_blue;          ///< RGB blue for colours
                IntVector     m_fillStyle;    ///< Fill styles for plots
        };

        ProcessVector  m_processVector;       ///< Vector of all processes
        PreSelection  *m_pPreSelection;       ///< PreSelection class containing cuts
};

#endif
