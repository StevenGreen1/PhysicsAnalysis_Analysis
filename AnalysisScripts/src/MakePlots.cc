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
    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);
        this->Register1DPlot(pProcess,"CosThetaMissing","float",200,-1.f,1.f);
        this->Register1DPlot(pProcess,"CosThetaMostEnergeticTrack","float",200,0.f,1.f);
        this->Register1DPlot(pProcess,"TransverseMomentum","float",2000,0.f,2000.f);
        this->Register1DPlot(pProcess,"TransverseEnergy","float",2000,0.f,2000.f);
        this->Register1DPlot(pProcess,"RecoilMass","float",200,0.f,2000.f);
        this->Register1DPlot(pProcess,"InvariantMassSystem","float",200,0.f,2000.f);
        this->Register1DPlot(pProcess,"y34","float",100,0.f,10.f);
        this->Register1DPlot(pProcess,"EnergyAroundMostEnergeticTrack","float",1000,0.f,1000.f);
        this->Register2DPlot(pProcess,"CosThetaMissing","CosThetaMostEnergeticTrack",200,-1.f,1.f,200,0.f,1.f);
        this->Register2DPlot(pProcess,"InvMassWVector1","InvMassWVector2",125,0.f,500.f,125,0.f,500.f);
        this->Register2DPlot(pProcess,"InvMassZVector1","InvMassZVector2",125,0.f,500.f,125,0.f,500.f);
    }

    this->LoadData();
    this->WritePlots();
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

void MakePlots::WritePlots()
{
    std::cout << "Begin: MakePlots::WritePlots" << std::endl;
    static const float redArray[] = {1,0.593,0,1,0.275};
    std::vector<float> red (redArray, redArray + sizeof(redArray) / sizeof(redArray[0]) );
    static const float greenArray[] = {0,0.980,0,0.24362,0};
    std::vector<float> green (greenArray, greenArray + sizeof(greenArray) / sizeof(greenArray[0]) );
    static const float blueArray[] = {0,0.593,1,0.588,0.510};
    std::vector<float> blue (blueArray, blueArray + sizeof(blueArray) / sizeof(blueArray[0]) );

    static const int fillStyleArray[] = {3001,3002,3006,3007,3016,3017};
    std::vector<int> fillStyle (fillStyleArray, fillStyleArray + sizeof(fillStyleArray) / sizeof(fillStyleArray[0]) );

    StringVector plottedVariableNames;

    for (Int1DPlotToProcessMap::iterator iterI = m_int1DPlotToProcess.begin(); iterI != m_int1DPlotToProcess.end(); iterI++)
    {
        TH1I *pTH1IOrig = iterI->first;
        TH1I *pTH1I = (TH1I*)(iterI->first->Clone());
        const Process *pActiveProcess = iterI->second;
        const int position(m_1DIntPlots.at(pTH1IOrig));
        std::string targetVariableName(m_intVariablesToRead.at(position));

        if (std::find(plottedVariableNames.begin(), plottedVariableNames.end(), targetVariableName) != plottedVariableNames.end())
            continue;

        plottedVariableNames.push_back(targetVariableName);

        TCanvas *pTCanvas = new TCanvas(targetVariableName.c_str(),targetVariableName.c_str());
        TLegend *pTLegend = new TLegend(0.5,0.7,0.9,0.9);
        int colourCounter(0);

        for (Int1DPlotToProcessMap::iterator iterJ = iterI; iterJ != m_int1DPlotToProcess.end(); iterJ++)
        {
            TH1I *pTH1IJOrig = iterI->first;
            TH1I *pTH1IJ = (TH1I*)(iterI->first->Clone());
            pTH1IJ->SetName(this->RandomName().c_str());
            const Process *pActiveProcessJ = iterJ->second;
            const int positionJ(m_1DIntPlots.at(pTH1IJOrig));
            std::string variableName(m_intVariablesToRead.at(positionJ));

            if (targetVariableName == variableName)
            {
                Color_t pTColor = TColor::GetColor(red.at(colourCounter), green.at(colourCounter), blue.at(colourCounter));        
                colourCounter++;
                pTH1IJ->SetLineColor(pTColor);
                pTH1IJ->SetFillColor(pTColor);
                pTH1IJ->SetFillStyle(fillStyle.at(colourCounter));
                pTH1IJ->SetMinimum(0);
                pTH1IJ->SetMaximum(2*pTH1IJ->GetBinContent(pTH1IJ->GetMaximumBin()));
                pTH1IJ->SetFillStyle(3001);
                pTH1IJ->Draw("same");
                std::string processName(pActiveProcessJ->GetEventType());
                pTLegend->AddEntry(pTH1IJ,processName.c_str(),"f");
            }
        }
        std::string plotName = targetVariableName + "_MultiPlot.C";
        gStyle->SetOptStat(0);
        pTLegend->Draw("same");
        pTCanvas->Update();
        pTCanvas->SaveAs(plotName.c_str());
    }

    for (Float1DPlotToProcessMap::iterator iterI = m_float1DPlotToProcess.begin(); iterI != m_float1DPlotToProcess.end(); iterI++)
    {
        TH1F *pTH1FOrig = iterI->first;
        TH1F *pTH1F = (TH1F*)(iterI->first->Clone());
        const Process *pActiveProcess = iterI->second;
        const int position(m_1DFloatPlots.at(pTH1FOrig));
        std::string targetVariableName(m_floatVariablesToRead.at(position));

        if (std::find(plottedVariableNames.begin(), plottedVariableNames.end(), targetVariableName) != plottedVariableNames.end())
            continue;

        plottedVariableNames.push_back(targetVariableName);

        TCanvas *pTCanvas = new TCanvas(targetVariableName.c_str(),targetVariableName.c_str());
        TLegend *pTLegend = new TLegend(0.5,0.7,0.9,0.9);
        int colourCounter(0);

        for (Float1DPlotToProcessMap::iterator iterJ = iterI; iterJ != m_float1DPlotToProcess.end(); iterJ++)
        {
            TH1F *pTH1FJOrig = iterJ->first;
            TH1F *pTH1FJ = (TH1F*)(iterJ->first->Clone());
            pTH1FJ->SetName(this->RandomName().c_str());
            const Process *pActiveProcessJ = iterJ->second;
            const int positionJ(m_1DFloatPlots.at(pTH1FJOrig));
            std::string variableName(m_floatVariablesToRead.at(positionJ));

            if (targetVariableName == variableName)
            {
                Color_t pTColor = TColor::GetColor(red.at(colourCounter), green.at(colourCounter), blue.at(colourCounter));
                colourCounter++;
                pTH1FJ->SetLineColor(pTColor);
                pTH1FJ->SetFillColor(pTColor);
                pTH1FJ->SetFillStyle(fillStyle.at(colourCounter));
                pTH1FJ->SetMinimum(0);
                pTH1FJ->SetMaximum(2*pTH1FJ->GetBinContent(pTH1FJ->GetMaximumBin()));
                pTH1FJ->Draw("same");
                std::string processName(pActiveProcessJ->GetEventType());
                pTLegend->AddEntry(pTH1FJ,processName.c_str(),"f");
            }
        }
        std::string plotName = targetVariableName + "_MultiPlot.C";
        gStyle->SetOptStat(0);
        pTLegend->Draw("same");
        pTCanvas->Update();
        pTCanvas->SaveAs(plotName.c_str());
    }

    std::cout << "End: MakePlots::WritePlots" << std::endl;
}

//=====================================================================

void MakePlots::WriteIndividualPlots()
{
    std::cout << "Begin: MakePlots::WriteIndividualPlots" << std::endl;
    for (Int1DPlotToProcessMap::iterator iter = m_int1DPlotToProcess.begin(); iter != m_int1DPlotToProcess.end(); iter++)
    {
        TH1I *pTH1I = (TH1I*)(iter->first->Clone());
        const Process *pProcess = iter->second;
        std::string processName = pTH1I->GetName();
        std::string saveName = processName + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH1I->Draw();
        pTCanvas->SaveAs(saveName.c_str());
        pTH1I->SetName(this->RandomName().c_str());
    }

    for (Float1DPlotToProcessMap::iterator iter = m_float1DPlotToProcess.begin(); iter != m_float1DPlotToProcess.end(); iter++)
    {
        TH1F *pTH1F = (TH1F*)(iter->first->Clone());
        const Process *pProcess = iter->second;
        std::string processName = pTH1F->GetName();
        std::string saveName = processName + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH1F->Draw();
        pTCanvas->SaveAs(saveName.c_str());
        pTH1F->SetName(this->RandomName().c_str());
    }

    for (Float2DPlotToProcessMap::iterator iter = m_float2DPlotToProcess.begin(); iter != m_float2DPlotToProcess.end(); iter++)
    {
        TH2F *pTH2F = (TH2F*)(iter->first->Clone());
        const Process *pProcess = iter->second;
        std::string processName = pTH2F->GetName();
        std::string saveName = processName + ".C";
        TCanvas *pTCanvas = new TCanvas();
        pTH2F->Draw("COLZ");
        pTCanvas->SaveAs(saveName.c_str());
        pTH2F->SetName(this->RandomName().c_str());
    }
    std::cout << "End: MakePlots::WriteIndividualPlots" << std::endl;
}

//=====================================================================

void MakePlots::LoadData()
{
    std::cout << "Begin: MakePlots::LoadData" << std::endl;

    for (ProcessVector::const_iterator it = m_processVector.begin(); it != m_processVector.end(); it ++)
    {
        const Process *pProcess(*it);
        TChain *pTChain(pProcess->GetTChain());

        float weight(pProcess->GetProcessWeight());

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
    int positionX(std::numeric_limits<int>::max());

    if (positionInVectorX != m_floatVariablesToRead.size())
    {
        positionX = positionInVectorX;
    }
    else
    {
        positionX = m_floatVariablesToRead.size();
        m_floatVariablesToRead.push_back(variableNameX);
    }

    int positionInVectorY = std::find(m_floatVariablesToRead.begin(), m_floatVariablesToRead.end(), variableNameY) - m_floatVariablesToRead.begin();
    int positionY(std::numeric_limits<int>::max());

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

std::string MakePlots::RandomName()
{
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int strLen = sizeof(alphabet)-1;
    char genRandom;
    std::string str;
    for(int i=0; i < 10; i++)
    {
        genRandom = alphabet[rand()%strLen];
        str += genRandom;
    }
    return str;
}

//=====================================================================

template <class T>
std::string MakePlots::NumberToString(const T &number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
