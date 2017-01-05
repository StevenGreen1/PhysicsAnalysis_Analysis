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

    Fit *pFit = new Fit("LPFOs_kt_0p90", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("LPFOs_kt_1p10", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("TPFOs_kt_0p90", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("TPFOs_kt_1p10", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

/*
    Fit *pFit = new Fit("SPFOs_kt_0p90", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("SPFOs_kt_1p00", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("SPFOs_kt_1p10", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("TPFOs_kt_0p70", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

    pFit = new Fit("LPFOs_kt_0p70", 1400, 10, "/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/");
    pFit->Merge();
    delete pFit;

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
*/
}

//=====================================================================
