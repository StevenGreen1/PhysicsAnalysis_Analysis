/**
  *  @file   AnalysisScripts/src/MakePlots.cc 
  * 
  *  @brief  Implementation of the make plots class.
  * 
  *  $Log: $
  */

#include "MakePlots.h"

//=====================================================================

MakePlots::MakePlots(const ProcessVector &processVector) :
    m_processVector(processVector),
    m_1DIntPlots(),
    m_intVariablesToRead(),
    m_1DFloatPlots(),
    m_floatVariablesToRead()
{
    for (ProcessVector::iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        Process *pProcess(*it);
        this->Register1DPlot(pProcess,"CosThetaMissing","float",200,-1.f,1.f);
        this->Register1DPlot(pProcess,"CosThetaMostEnergeticTrack","float",200,0.f,1.f);
        this->Register2DPlot(pProcess,"CosThetaMissing","CosThetaMostEnergeticTrack",200,-1.f,1.f,200,0.f,1.f);
    }

    this->LoadData();
//    this->WritePlots();
    this->WriteIndividualPlots();
/*
    for (Float1DPlotToPositionMap::iterator iter = m_1DFloatPlots.begin(); iter != m_1DFloatPlots.end(); iter++)
    {   
        int position = iter->second;
        TH1F *pTH1F = iter->first;
        TCanvas *pTCanvas = new TCanvas();
        pTH1F->Draw();
        std::string plotName = pTH1F->GetName() + this->NumberToString(position) + ".C";
        pTCanvas->SaveAs(plotName.c_str());
    }
*/

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

void MakePlots::WriteIndividualPlots()
{
    for (Int1DPlotToProcessMap::iterator iter = m_int1DPlotToProcess.begin(); iter != m_int1DPlotToProcess.end(); iter++)
    {
        TH1I *pTH1I = iter->first;
        const Process *pProcess = iter->second;
        std::string processName(pTH1I->GetName());
        std::string saveName = processName + "_" + pProcess->GetEventType() + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH1I->Draw();
        pTCanvas->SaveAs(saveName.c_str());
    }

    for (Float1DPlotToProcessMap::iterator iter = m_float1DPlotToProcess.begin(); iter != m_float1DPlotToProcess.end(); iter++)
    {
        TH1F *pTH1F = iter->first;
        const Process *pProcess = iter->second;
        std::string processName(pTH1F->GetName());
        std::string saveName = processName + "_" + pProcess->GetEventType() + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH1F->Draw();
        pTCanvas->SaveAs(saveName.c_str());
    }

    for (Float2DPlotToProcessMap::iterator iter = m_float2DPlotToProcess.begin(); iter != m_float2DPlotToProcess.end(); iter++)
    {
        TH2F *pTH2F = iter->first;
        const Process *pProcess = iter->second;
        std::string processName(pTH2F->GetName());
        std::string saveName = processName + "_" + pProcess->GetEventType() + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH2F->Draw("COLZ");
        pTCanvas->SaveAs(saveName.c_str());
    }
}

//=====================================================================

void MakePlots::LoadData()
{
    std::cout << "Begin: MakePlots::LoadData" << std::endl;

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

            for (Int1DPlotToPositionMap::iterator iter = m_1DIntPlots.begin(); iter != m_1DIntPlots.end(); iter++)
            {
                TH1I *pTH1I = iter->first;
                int position = iter->second;
                const Process *pActiveProcess = m_int1DPlotToProcess.at(pTH1I);
                if (&*pActiveProcess == &*pProcess)
                    pTH1I->Fill(intsToRead[position], weight);
            }

            for (Float1DPlotToPositionMap::iterator iter = m_1DFloatPlots.begin(); iter != m_1DFloatPlots.end(); iter++)
            {
                TH1F *pTH1F = iter->first;
                int position = iter->second;
                const Process *pActiveProcess = m_float1DPlotToProcess.at(pTH1F);
                if (&*pActiveProcess == &*pProcess)
                    pTH1F->Fill(floatsToRead[position], weight);
            }

            for (Float2DPlotToPositionMap::iterator iter = m_2DPlots.begin(); iter != m_2DPlots.end(); iter++)
            {
                TH2F *pTH2F(iter->first);
                int positionX(iter->second.first);
                int positionY(iter->second.second);
                const Process *pActiveProcess = m_float2DPlotToProcess.at(pTH2F);
                if (&*pActiveProcess == &*pProcess)
                    pTH2F->Fill(floatsToRead[positionX], floatsToRead[positionY], weight);
            }
        }
    }
    std::cout << "End: MakePlots::LoadData" << std::endl;
}

//=====================================================================

void MakePlots::Register2DPlot(const Process *pProcess, const std::string &variableNameX, const std::string &variableNameY, const int &nBinsX, const float &lowBinX, const float &highBinX, const int &nBinsY, const float &lowBinY, const float &highBinY)
{
    std::cout << "Begin: MakePlots::Register2DPlot" << std::endl;

    int positionInVectorX = std::find(m_floatVariablesToRead.begin(), m_floatVariablesToRead.end(), variableNameX) - m_floatVariablesToRead.begin();
    int positionInVectorY = std::find(m_floatVariablesToRead.begin(), m_floatVariablesToRead.end(), variableNameY) - m_floatVariablesToRead.begin();

    int positionX(std::numeric_limits<int>::max());
    int positionY(std::numeric_limits<int>::max());

    if (positionInVectorX != m_floatVariablesToRead.size())
    {
        positionX = positionInVectorX;
    }
    else
    {
        positionX = m_floatVariablesToRead.size();
        m_floatVariablesToRead.push_back(variableNameX);
    }

    if (positionInVectorY != m_floatVariablesToRead.size())
    {
        positionY = positionInVectorY;
    }
    else
    {
        positionY = m_floatVariablesToRead.size();
        m_floatVariablesToRead.push_back(variableNameY);
    }

    std::string plotName = variableNameX + "_" + variableNameY + "_" + pProcess->GetEventType();
    std::string plotTitle = variableNameX + " vs " + variableNameY + " For " + pProcess->GetEventType();
    const char* name(plotName.c_str());
    const char* title(plotTitle.c_str());
    TH2F *pTH2F = new TH2F(name, title, nBinsX, lowBinX, highBinX, nBinsY, lowBinY, highBinY);

    m_2DPlots.insert(std::make_pair(pTH2F,std::make_pair(positionX,positionY)));
    m_float2DPlotToProcess.insert(std::make_pair(pTH2F,pProcess));
    std::cout << "End: MakePlots::Register2DPlot" << std::endl;
}

//=====================================================================

void MakePlots::Register1DPlot(const Process *pProcess, const std::string &variableName, const std::string &objectType, const int &nBins, const float &lowBin, const float &highBin) 
{
    std::cout << "Begin: MakePlots::Register1DPlot" << std::endl;
    if (objectType == "int")
    {
        this->Register1DIntPlot(pProcess,variableName,nBins,lowBin,highBin);
    }
    else if (objectType == "float")
    {
        this->Register1DFloatPlot(pProcess,variableName,nBins,lowBin,highBin);
    }
    std::cout << "End: MakePlots::Register1DPlot" << std::endl;
}

//=====================================================================

void MakePlots::Register1DIntPlot(const Process *pProcess, const std::string &variableName, const int &nBins, const float &lowBin, const float &highBin)
{
    std::cout << "Begin: MakePlots::Register1DIntPlot" << std::endl;
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

    std::string plotName = variableName + "_" + pProcess->GetEventType();
    std::string plotTitle = variableName + " " + pProcess->GetEventType();
    const char* name(plotName.c_str());
    const char* title(plotTitle.c_str());
    TH1I *pTH1I = new TH1I(name, title, nBins, lowBin, highBin);

    m_1DIntPlots.insert(std::make_pair(pTH1I,position));
    m_int1DPlotToProcess.insert(std::make_pair(pTH1I,pProcess));
    std::cout << "End: MakePlots::Register1DIntPlot" << std::endl;
}

//=====================================================================

void MakePlots::Register1DFloatPlot(const Process *pProcess, const std::string &variableName, const int &nBins, const float &lowBin, const float &highBin)
{
    std::cout << "Begin: MakePlots::Register1DFloatPlot" << std::endl;
    int positionInVector = std::find(m_floatVariablesToRead.begin(), m_floatVariablesToRead.end(), variableName) - m_floatVariablesToRead.begin();
    int position(std::numeric_limits<int>::max());

    if (positionInVector != m_floatVariablesToRead.size())
    {   
        position = positionInVector;
    }
    else
    {   
        position = m_floatVariablesToRead.size();
        m_floatVariablesToRead.push_back(variableName);
    }

    std::string plotName = variableName + "_" + pProcess->GetEventType(); 
    std::string plotTitle = variableName + " " + pProcess->GetEventType(); 
    const char* name(plotName.c_str());
    const char* title(plotTitle.c_str());
    TH1F *pTH1F = new TH1F(name, title, nBins, lowBin, highBin);

    m_1DFloatPlots.insert(std::make_pair(pTH1F,position));
    m_float1DPlotToProcess.insert(std::make_pair(pTH1F,pProcess));
    std::cout << "End: MakePlots::Register1DFloatPlot" << std::endl;
}

//=====================================================================
/*
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
*/
//=====================================================================

template <class T>
std::string MakePlots::NumberToString(const T &number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
