/**
 *  @file   AnalysisScripts/src/Fitting3000.cxx
 * 
 *  @brief  Implementation of the fitting class
 * 
 *  $Log: $
 */

#include "Fit.h"

#include "TStyle.h"

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
    std::string inputDescriptor("TPFOs_kt_1p10");
    std::string inputPath("/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
//    std::string outputDescriptor("TPFOs_kt_1p10_Sigma_egamma_qqqqnu_BS_" + sigmaString + "_Sigma_gammae_qqqqnu_BS_" + sigmaString);
    std::string outputPath("/r06/lc/sg568/PhysicsAnalysis/Analysis/NuisanceFitting/3000GeV/");
    const int energy(3000);
    const int nBins(10);

/*
    NuisanceFit *pNuisanceFit = new NuisanceFit(inputDescriptor, inputPath, outputDescriptor, outputPath, energy, nBins, true);
    pNuisanceFit->AddNuisance("egamma_qqqqnu_BS", sigma);
    pNuisanceFit->AddNuisance("gammae_qqqqnu_BS", sigma);
    pNuisanceFit->Merge();
    delete pNuisanceFit;
*/

    Fit *pFit = new Fit(inputDescriptor, energy, nBins, inputPath, true);
    pFit->Merge();
    delete pFit;

/*
    Fit *pFit = new Fit("SPFOs_kt_0p50", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("SPFOs_kt_0p70", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("SPFOs_kt_0p90", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("SPFOs_kt_1p00", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("SPFOs_kt_1p10", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("TPFOs_kt_0p70", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("LPFOs_kt_0p70", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("TPFOs_kt_0p90", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("LPFOs_kt_0p90", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("TPFOs_kt_1p10", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("LPFOs_kt_1p10", 3000, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;
*/
}

//=====================================================================
