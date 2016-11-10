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
#include <memory>
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
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

#include "EventNumbers.h"
#include "PostMVASelection.h"
#include "Process.h"
#include "CouplingAnalysis.h"

class Fit
{
    typedef std::vector<const Process*> ProcessVector;
    typedef std::vector<int> IntVector;
    typedef std::vector<float> FloatVector;
    typedef std::vector<double> DoubleVector;

    public:
        /**
         *  @brief Constructor
         *
         *  @param processVector vector of processes to include in analysis
         *  @param pCouplingAnalysis pointer to coupling analysis class for weight information
         *  @param descriptor Optional string to attach to filenames
         */
        Fit(const ProcessVector &processVector, CouplingAnalysis *pCouplingAnalysis, std::string descriptor = "");

        /**
         *  @brief Default destructor
         */
        ~Fit();

        /**
         *  @brief Set numbers of bins to use in fit
         *
         *  @param nBins number of bins to use in fit
         */
        void SetNBins(const int &nBins);

        /**
         *  @brief Set numbers of bins to use in fit
         *  
         *  @param nEvents maximum number of signal events to use
         */
        void SetNEvents(const int &nEvents);

        /**
         *  @brief Set option for Minuit fit i.e. histogram to get chi2 from to fit
         *
         *  @param option
         */
        void SetOption(const int &option);

        /**
         *  @brief Perform Minuit for for alpha4/alpha5 sensitivity
         */
        void MinuitFit();

        /**
         *  @brief Perform simple scan of alpha4/alpha5 to get chi2
         */
        void MyFit();

    private:
        /**
         *  @brief Work out chi2 for given sensitive distribution options
         *
         *  @param par[0] = alpha4  
         *  @param par[1] = alpha5
         */
        double Chi2(const double *par);
        double Chi2_CTSWJets_vs_CTSWBosons(const double *par);
        double Chi2_CTSZJets_vs_CTSZBosons(const double *par);
        double Chi2_CTSWJets(const double *par);
        double Chi2_CTSZJets(const double *par);
        double Chi2_CTSWBosons(const double *par);
        double Chi2_CTSZBosons(const double *par);

        /**
         *  @brief Initialise histograms for reweighting
         */
        void Initialise();

        /**
         *  @brief See if name is available name for root object and if not delete pre exisiting object so that it is a valid name choice
         *
         *  @param name of root object
         */
        TString SafeName(const TString &name);

        /**
         *  @brief Clear variables for next chi2 calcaultion
         */
        void Clear();

        /**
         *  @brief Fill distribution of intertest
         *
         *  @param alpha4
         *  @param alpha5
         */
        void FillDistribution(const double alpha4, const double alpha5);

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

        ProcessVector         m_processVector;                  ///< Vector of all processes
        PostMVASelection     *m_pPostMVASelection;              ///< Container for all selection cuts
        CouplingAnalysis     *m_pCouplingAnalysis;              ///< Coupling analysis to use in fit
        const std::string     m_rootFileName;                   ///< Name of output results root file
        TFile                *m_pTFile;                         ///< Root file for results
        TTree                *m_pTTree;                         ///< Root tree for results
        const std::string     m_descriptor;                     ///< Optional string to attack to plots/filename etc 
        int                   m_nBins;                          ///< Number of bins to use in costheta*jet fit
        int                   m_nEvents;                        ///< Maximum number of events to use in fit
        int                   m_option;                         ///< Int determining distribution of interest to use in fit
        float                 m_wBosonMass;                     ///< W Boson Mass
        float                 m_zBosonMass;                     ///< Z Boson Mass
        double                m_alpha4;                         ///< Alpha 4 value to save to tree 
        double                m_alpha5;                         ///< Alpha 5 value to save to tree
        double                m_chi2_CTSWJets_vs_CTSWBosons;    ///< Chi2 from cos theta start W jets vs cos theta start W bosons
        double                m_chi2_CTSZJets_vs_CTSZBosons;    ///< Chi2 from cos theta start Z jets vs cos theta start Z bosons
        double                m_chi2_CTSWJets;                  ///< Chi2 from cos theta start W jets
        double                m_chi2_CTSZJets;                  ///< Chi2 from cos theta start Z jets
        double                m_chi2_CTSWBosons;                ///< Chi2 from cos theta start W bosons
        double                m_chi2_CTSZBosons;                ///< Chi2 from cos theta start Z bosons
        TH1F                 *m_pTH1F_CTSWJetsRef;              ///< Distribution of cos theta star from jets from W boson
        TH1F                 *m_pTH1F_CTSZJetsRef;              ///< Distribution of cos theta star from jets from Z boson
        TH1F                 *m_pTH1F_CTSWBosonsRef;            ///< Distribution of cos theta star from W boson
        TH1F                 *m_pTH1F_CTSZBosonsRef;            ///< Distribution of cos theta star from Z boson
        TH2F                 *m_pTH2F_CTSWJets_vs_CTSWBosonsRef;///< Distribution of cos theta star from jets vs cos theta star from W boson
        TH2F                 *m_pTH2F_CTSZJets_vs_CTSZBosonsRef;///< Distribution of cos theta star from jets vs cos theta star from Z boson
        TH1F                 *m_pTH1F_CTSWJets;                 ///< Distribution of cos theta star from jets from W boson with non zero alpha4/alpha5
        TH1F                 *m_pTH1F_CTSZJets;                 ///< Distribution of cos theta star from jets from Z boson with non zero alpha4/alpha5
        TH1F                 *m_pTH1F_CTSWBosons;               ///< Distribution of cos theta star from W boson with non zero alpha4/alpha5
        TH1F                 *m_pTH1F_CTSZBosons;               ///< Distribution of cos theta star from Z boson with non zero alpha4/alpha5
        TH2F                 *m_pTH2F_CTSWJets_vs_CTSWBosons;   ///< Distribution of cos theta star from jets vs cos theta star from W boson with non zero alpha4/alpha5
        TH2F                 *m_pTH2F_CTSZJets_vs_CTSZBosons;   ///< Distribution of cos theta star from jets vs cos theta star from Z boson with non zero alpha4/alpha5
        FloatVector           m_red;                            ///< Red RGB for plotting
        FloatVector           m_green;                          ///< Green RGB for plotting
        FloatVector           m_blue;                           ///< Blue RGB for plotting
        IntVector             m_fillStyle;                      ///< Fill style for plotting
};

#endif
