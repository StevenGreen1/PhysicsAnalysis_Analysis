/**
 *  @file   AnalysisScripts/src/Fitting3000.cxx
 * 
 *  @brief  Implementation of the fitting class
 * 
 *  $Log: $
 */

#include "Fit.h"
#include "NuisanceFit.h"

#include "TStyle.h"

//=====================================================================

template <class T>
std::string NumberToString(T number);

//=====================================================================

int main(int argc, char **argv)
{
    srand(time(0));
    gStyle->SetOptStat(0);
/*
    const double sigma(atof(argv[1]));
    std::string sigmaString(argv[1]);
    std::replace(sigmaString.begin(), sigmaString.end(), '.', 'p');
*/
    const int energy(3000);
    const int nBins(10);
    std::string inputDescriptor("TPFOs_kt_1p10");
//    std::string inputPathOptimisation("/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/Optimisation/3000GeV/");
    std::string inputPathFinal("/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    std::string outputDescriptor("TPFOs_kt_1p10");
//    std::string outputDescriptor("TPFOs_kt_1p10_Sigma_egamma_qqqqnu_BS_" + sigmaString + "_Sigma_gammae_qqqqnu_BS_" + sigmaString);
    std::string outputPath("/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/FinalPlot/" + NumberToString(energy) + "GeV/");
//    std::string outputPath("/r06/lc/sg568/PhysicsAnalysis/Analysis/NuisanceFitting/3000GeV/");

/*
    NuisanceFit *pNuisanceFit = new NuisanceFit(inputDescriptor, inputPathFinal, outputDescriptor, outputPath, energy, nBins, true);
    pNuisanceFit->AddNuisance("egamma_qqqqnu_BS", sigma);
    pNuisanceFit->AddNuisance("gammae_qqqqnu_BS", sigma);
    pNuisanceFit->Merge();
    delete pNuisanceFit;
*/

    Fit *pFit = new Fit(inputDescriptor, inputPathFinal, outputDescriptor, outputPath, energy, nBins, true); // True is add backgrounds Analysis
//    Fit *pFit = new Fit(inputDescriptor, inputPathFinal, outputDescriptor, outputPath, energy, nBins, false); // PerfectAnalysis
    pFit->Merge();
    delete pFit;
}

//=====================================================================

template <class T>
std::string NumberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================

