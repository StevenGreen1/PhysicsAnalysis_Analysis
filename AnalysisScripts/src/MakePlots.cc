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
    m_processVector(processVector),
    m_intPlots(),
    m_intVariablesToRead(),
    m_floatPlots(),
    m_floatVariablesToRead()
{
    this->Register1DPlot("CosThetaMissing","float",200,-1.f,1.f);
    this->Register1DPlot("CosThetaMostEnergeticTrack","float",200,-1.f,1.f);
//    this->Register2DPlot("Blah1","int/float","Blah2","int/float",nBins1,lowBin1,highBin1,nBins2,lowBin2,highBin2);

    this->LoadData();

    for (Float1DPlotToPositionMap::iterator iter = m_floatPlots.begin(); iter != m_floatPlots.end(); iter++)
    {   
        int position = iter->second;
        TH1F *pTH1F = iter->first;
        TCanvas *pTCanvas = new TCanvas();
        pTH1F->Draw();
        std::string plotName = pTH1F->GetName() + this->NumberToString(position) + ".C";
        pTCanvas->SaveAs(plotName.c_str());
    }
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

//=====================================================================

void MakePlots::LoadData()
{
    for (ProcessVector::iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        Process *pProcess(*it);
        TChain *pTChain(pProcess->GetTChain());

        float weight(pProcess->GetProcessWeight());

        //const int position(it-m_processVector.begin() + 1);
        //pTH1F->SetLineColor(position);

        int intsToRead[m_intVariablesToRead.size()];
        float floatsToRead[m_floatVariablesToRead.size()];

        for (StringVector::iterator iter = m_intVariablesToRead.begin(); iter != m_intVariablesToRead.end(); iter++)
        {
            std::string variableName(*iter);
            int position(iter-m_intVariablesToRead.begin());
            pTChain->SetBranchAddress(variableName.c_str(), &intsToRead[position]);
        }

        for (StringVector::iterator iter = m_floatVariablesToRead.begin(); iter != m_floatVariablesToRead.end(); iter++)
        {
            std::string variableName(*iter);
            int position(iter-m_floatVariablesToRead.begin());
            pTChain->SetBranchAddress(variableName.c_str(), &floatsToRead[position]);
        }

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);

            for (Float1DPlotToPositionMap::iterator iter = m_floatPlots.begin(); iter != m_floatPlots.end(); iter++)
            {
                TH1F *pTH1F = iter->first;
                int position = iter->second;
                pTH1F->Fill(floatsToRead[position], weight);
            }

            for (Int1DPlotToPositionMap::iterator iter = m_intPlots.begin(); iter != m_intPlots.end(); iter++)
            {   
                TH1I *pTH1I = iter->first;
                int position = iter->second;
                pTH1I->Fill(intsToRead[position], weight);
            }
        }
    }
}

//=====================================================================

void MakePlots::Register1DPlot(std::string variableName, std::string objectType, int nBins, float lowBin, float highBin)
{
    std::cout << "Begin: MakePlots::Register1DPlot" << std::endl;
    if (objectType == "int")
    {
        this->RegisterIntToRead(variableName,nBins,lowBin,highBin);
    }
    else if (objectType == "float")
    {
        this->RegisterFloatToRead(variableName,nBins,lowBin,highBin);
    }
    std::cout << "End: MakePlots::Register1DPlot" << std::endl;
}

//=====================================================================

void MakePlots::RegisterIntToRead(std::string variableName, int nBins, float lowBin, float highBin)
{
    std::cout << "Begin: MakePlots::RegisterIntToRead" << std::endl;
    TH1I *pTH1I = new TH1I(variableName.c_str(), variableName.c_str(), nBins, lowBin, highBin);

    int positionInVector = std::find(m_intVariablesToRead.begin(), m_intVariablesToRead.end(), variableName) - m_intVariablesToRead.begin();
    int position(std::numeric_limits<int>::max());

    if (positionInVector != m_intVariablesToRead.size())
    {
        position = positionInVector;
    }
    else 
    {
        position = m_intVariablesToRead.size();
        m_intVariablesToRead.push_back(variableName);
    }

    m_intPlots.insert(std::make_pair(pTH1I,position));
    std::cout << "End: MakePlots::RegisterIntToRead" << std::endl;
}

//=====================================================================

void MakePlots::RegisterFloatToRead(const std::string &variableName, int nBins, float lowBin, float highBin)
{
    std::cout << "Begin: MakePlots::RegisterFloatToRead" << std::endl;
    
    int positionInVector = std::find(m_floatVariablesToRead.begin(), m_floatVariablesToRead.end(), variableName) - m_floatVariablesToRead.begin();
    int position(std::numeric_limits<int>::max());

    if (positionInVector != m_floatVariablesToRead.size())
    {   
        position = positionInVector;
    }
    else
    {   
        position = m_floatVariablesToRead.size();
        std::cout << position << std::endl;
        m_floatVariablesToRead.push_back(variableName);
    }

    std::cout << position << std::endl;

    const char* name = variableName.c_str();
    const char* title = variableName.c_str();
    TH1F *pTH1F = new TH1F(name, title, nBins, lowBin, highBin);

    m_floatPlots.insert(std::make_pair(pTH1F,position));
    std::cout << "End: MakePlots::RegisterFloatToRead" << std::endl;
}

//=====================================================================

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

template <class T>
std::string MakePlots::NumberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
