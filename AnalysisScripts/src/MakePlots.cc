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
    this->MakeWWPlot();
}

//=====================================================================
/*
 run             = 1
 event           = 1
 IsAppropriateEvent = 1
 IsEventWW       = 0
 IsEventZZ       = 0
 InvMassWVector1 = 22.5413
 InvMassWVector2 = 101.806
 InvMassZVector1 = 22.5413
 InvMassZVector2 = 101.806
 TransverseMomentum = 175.965
 TransverseEnergy = 174.605
 CosThetaMissing = 0.968488
 CosThetaMostEnergeticTrack = 0.962086
 RecoilMass      = 960.908
 EnergyAroundMostEnergeticTrack = 52.9911
 y34             = 2.65941
 NParticlesJets  = (vector<int>*)0x216ec80
 NChargedParticlesJets = (vector<int>*)0x23b8900
 InvariantMassSystem = 297.647
*/

void MakePlots::MakeWWPlot()
{
    TCanvas *pTCanvas = new TCanvas();

    for (ProcessVector::iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        TH1F *pTH1F = new TH1F("wwMass","wwMass",1000,0,1000);
        Process *pProcess(*it);
        TChain *pTChain(pProcess->GetTChain());

        const int position(it-m_processVector.begin() + 1);
        pTH1F->SetLineColor(position);
        pTH1F->SetFillColor(position);

        float invMass(0.f);
        bool isAppropriateEvent(false);
        bool isWWEvent(false);

        pTChain->SetBranchAddress("InvariantMassSystem",&invMass);
        pTChain->SetBranchAddress("IsAppropriateEvent",&isAppropriateEvent);
        pTChain->SetBranchAddress("IsEventWW",&isWWEvent);

        for (unsigned int i = 0; i < pTChain->GetEntries(); i++)
        {
            pTChain->GetEntry(i);

            if (isAppropriateEvent and isWWEvent)
            {
                pTH1F->Fill(invMass,pProcess->GetProcessWeight());
            }
        }
        pTCanvas->cd();
        pTH1F->Draw();
    }

    pTCanvas->SaveAs("WWInvMass.png");
}

//=====================================================================

