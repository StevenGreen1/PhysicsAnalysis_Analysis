/**
 *  @file   AnalysisScripts/include/NuisanceFit.h 
 * 
 *  @brief  Header file for the fit class.
 * 
 *  $Log: $
 */

#ifndef NUISANCE_FIT_H
#define NUISANCE_FIT_H

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "TApplication.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TFile.h"
#include "TH2F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TSystemDirectory.h"
#include "TTree.h"

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

class NuisanceFit
{
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;
    typedef std::vector<std::string> StringVector;
    typedef std::map<std::string, TH1F*> OneDHistogramMap;
    typedef std::map<std::string, TH2F*> TwoDHistogramMap;
    typedef std::map<std::string, double> StringToDoubleMap;

    public:
        /**
         *  @brief Constructor
         *
         *  @param inputDescriptor string to read in filenames
         *  @param inputPath string to read in filenames
         *  @param outputDescriptor string to save root file
         *  @param outputPath string to save root file
         *  @param nBins used in fit
         *  @param inputPath
         *  @param background
         *
         */
        NuisanceFit(std::string inputDescriptor, std::string inputPath, std::string outputDescriptor, std::string outputPath, const int energy, const int nBins, bool background = false);

        /**
         *  @brief Default destructor
         */
        ~NuisanceFit();

        /**
         *  @brief Merge distributions to form chi2 together and calculate chi2
         *
         *  @param background does fit include backgrounds
         */
        void Merge();

        /**
         *  @breif Apply background nuisance analysis 
         *
         *  @param processName background 
         *  @param sigma for background
         */
        void AddNuisance(std::string processName, double sigma);

    private:
        /**
         *  @brief Find all files with relevant description and add to read in list
         */
        void FindFiles();

        /**
         *  @brief Initialise reference histograms for reweighting
         */
        void InitialiseReference();

        /**
         *  @brief Initialise histograms for reweighting
         */
        void Initialise();

        /**
         *  @brief Clear reference variables for next chi2 calcaultion
         */
        void ClearReference();

        /**
         *  @brief Clear histograms for next chi2 calcaultion
         */
        void Clear();

        /**
         *  @brief Merge all files together for given alpha4 and alpha5.  If reference = true, fill reference distribution
         *
         *  @param alpha4 to use to fill 
         *  @param alpha5 to use to fill
         *  @param reference should fill reference distribution 
         */
        void MergeFiles(float alpha4, float alpha5, bool reference = false);

        /**
         *  @breif Calculate the nuisance chi sqaured value using MINUIT for a given alpha4 and alpha5 based on the input histograms
         */
        double CalculateNuisanceChi2MINUITIn1D();

        /**
         *  @breif Return chi2 based on the m_cosThetaStarSynJets and m_cosThetaStarSynJetsRef histograms having fluctuated certain background processes by Gaussian with widths given by param
         *
         *  @param Gaussian widths for backgrounds 
         */
        double GetChi2In1D(const double *param);

        /**
         *  @brief Calculate the nuisance chi sqaured value for a given alpha4 and alpha5 based on the input histograms
         *
         *  @param hists Map of event type to histogram of distribution of interest for fit
         *  @param hists Map of event type to reference histogram of distribution of interest for fit
         */
        double CalculateNuisanceChi2In1D(OneDHistogramMap hists, OneDHistogramMap histsRef);

        /**
         *  @brief See if name is available name for root object and if not delete pre exisiting object so that it is a valid name choice
         *
         *  @param name of root object
         */
        TString SafeName(const TString &name);

        /**
         *  @brief Calculate negative log likelihood for a given distribution for non-zero alpha4 and alpha5 based on distribution with zero alpha4 and alpah5
         *
         *  @param pTH1F distribution with non zero alpha4 and alpha5
         *  @param pTH1FRef reference distribution to base log likelihood from
         */
        double CalculateChi2In1D(TH1F *pTH1F, TH1F *pTH1FRef);

        /**
         *  @brief Calculate negative log likelihood for a given 2D distribution for non-zero alpha4 and alpha5 based on distribution with zero alpha4 and alpah5
         *
         *  @param pTH2F distribution with non zero alpha4 and alpha5
         *  @param pTH2FRef reference distribution to base log likelihood from
         */
        double CalculateChi2In2D(TH2F *pTH2F, TH2F *pTH2FRef);

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

        const std::string     m_inputDescriptor;                            ///< Descriptor to read in file names
        const std::string     m_inputPath;                                  ///< Path to read in file names
        const std::string     m_outputDescriptor;                           ///< Descriptor to save output
        const std::string     m_outputPath;                                 ///< Path to save output
        const int             m_nBins;                                      ///< Number of bins to use in costheta*jet fit
        const int             m_energy;                                     ///< Energy
        const bool            m_background;                                 ///< Backgrounds
        StringVector          m_processNames;                               ///< Vector of all processes
        StringToDoubleMap     m_nuisanceBackgrounds;                        ///< Nuisance backgrounds and sigmas for those distributions 
        bool                  m_fluctuateNominal;                           ///< Fluctuate the nominal (standard model) using Poisson statistics
        const std::string     m_rootFileName;                               ///< Name of output results root file
        StringVector          m_filesToReadIn;                              ///< Vector of files to read in
        TFile                *m_pTFile;                                     ///< Root file for results
        TTree                *m_pTTree;                                     ///< Root tree for results
        double                m_alpha4;                                     ///< Alpha 4 value to save to tree 
        double                m_alpha5;                                     ///< Alpha 5 value to save to tree
        double                m_chi2CosThetaStarSynJets;                    ///< Chi2 from cos theta start synergy jets
        double                m_chi2CosThetaStarSynBosons;                  ///< Chi2 from cos theta start synergy boson
        double                m_chi2CosThetaStarSynJets_vs_Bosons;          ///< Chi2 from cos theta start synergy jets vs cos theta start synergy boson
        OneDHistogramMap      m_cosThetaStarSynJets;                        ///< Distribution of cos theta star from jets from synergy boson all, map of process to histogram
        OneDHistogramMap      m_cosThetaStarSynJetsRef;                     ///< Distribution of cos theta star from jets from synergy boson all ref, map of process to histogram
        OneDHistogramMap      m_cosThetaStarSynBosons;                      ///< Distribution of cos theta star from bosons from synergy boson all, map of process to histogram
        OneDHistogramMap      m_cosThetaStarSynBosonsRef;                   ///< Distribution of cos theta star from bosons from synergy boson all ref, map of process to histogram
        TwoDHistogramMap      m_cosThetaStarSynJets_vs_Bosons;              ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson all, map of process to histogram
        TwoDHistogramMap      m_cosThetaStarSynJets_vs_BosonsRef;           ///< Distribution of cos theta star from jets vs cos theta star from bosons from synergy boson all ref, map of process to histogram
};

#endif
