/**
  *  @file   AnalysisScripts/src/MakePlots.cc 
  * 
  *  @brief  Implementation of the make plots class.
  * 
  *  $Log: $
  */

#include "MakePlots.h"

//=====================================================================

MakePlots::MakePlots(ProcessVector processVector) :
    m_processVector(processVector)
{
}

//=====================================================================

void MakePlots::MakeWWPlot()
{
    TH1F *pTH1F = new TH1F("wwMass","wwMass",1000,0,1000);
    
}

//=====================================================================

