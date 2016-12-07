/**
 *  @file   AnalysisScripts/src/Fitting.cxx
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

    Fit *pFit = new Fit("SPFOs_kt_0p70", 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;
}

//=====================================================================
