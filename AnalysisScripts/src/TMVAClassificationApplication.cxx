/**
 *  @file   AnalysisScripts/src/TMVAClassificationApplication.cxx 
 * 
 *  @brief  Implementation of the TMVA classifier class.
 * 
 *  $Log: $
 */

#include "TMVAClassificationApplication.h"

//=====================================================================

int main(int argc, char **argv)
{
    typedef std::vector<const Process*> ProcessVector;

    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqqqq",22.16,1500,1400,3);
    //const Process *pProcess_CLIC_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","CLIC_ee_nunuqqqq",24.7,1500,1400,3); // <-CLIC

    // CLIC Backgrounds
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqqqq",115.3,1500,1400,3);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_llqqqq",71.7,1500,1400,3);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqqq",1328.1,1500,1400,3);

    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqq",933.9,1500,1400,3);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqq",4309.7,1500,1400,3);
    const Process *pProcess_ee_ll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_ll",2725.8,1500,1400,3);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qq",4009.5,1500,1400,3);

    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_EPA",287.1,1500,1400,3);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_BS",1160.7,1500,1400,3);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_EPA",286.9,1500,1400,3);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_BS",1156.3,1500,1400,3);

    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_EPA",32.6,1500,1400,3);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_BS",136.9,1500,1400,3);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_EPA",32.6,1500,1400,3);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_BS",136.4,1500,1400,3);

    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_EPA",753.0,1500,1400,3);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_BS",4034.8,1500,1400,3);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_EPA",4018.7,1500,1400,3);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_BS",4009.5,1500,1400,3);

    ProcessVector processes;

    processes.push_back(pProcess_ee_nunuqqqq);
//    processes.push_back(pProcess_CLIC_ee_nunuqqqq);

    processes.push_back(pProcess_ee_lnuqqqq);
    processes.push_back(pProcess_ee_llqqqq);
    processes.push_back(pProcess_ee_qqqq);

    processes.push_back(pProcess_ee_nunuqq);
    processes.push_back(pProcess_ee_lnuqq);
    processes.push_back(pProcess_ee_ll);
    processes.push_back(pProcess_ee_qq);

    processes.push_back(pProcess_egamma_qqqqe_EPA);
    processes.push_back(pProcess_egamma_qqqqe_BS);
    processes.push_back(pProcess_gammae_qqqqe_EPA);
    processes.push_back(pProcess_gammae_qqqqe_BS);

    processes.push_back(pProcess_egamma_qqqqnu_EPA);
    processes.push_back(pProcess_egamma_qqqqnu_BS);
    processes.push_back(pProcess_gammae_qqqqnu_EPA);
    processes.push_back(pProcess_gammae_qqqqnu_BS);

    processes.push_back(pProcess_gammagamma_qqqq_EPA_EPA);
    processes.push_back(pProcess_gammagamma_qqqq_EPA_BS);
    processes.push_back(pProcess_gammagamma_qqqq_BS_EPA);
    processes.push_back(pProcess_gammagamma_qqqq_BS_BS);

    TMVAClassificationApplication *pTMVAClassificationApplication = new TMVAClassificationApplication(processes);
}

//=====================================================================

TMVAClassificationApplication::TMVAClassificationApplication(ProcessVector processes)
{
    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

    Float_t tmvaReaderRecoilMass(std::numeric_limits<float>::max());
    Float_t tmvaReaderTransverseMomentum(std::numeric_limits<float>::max());
    Float_t tmvaReaderTransverseEnergy(std::numeric_limits<float>::max());
    Float_t tmvaReaderCosThetaMissing(std::numeric_limits<float>::max());
    Float_t tmvaReaderCosThetaMostEnergeticTrack(std::numeric_limits<float>::max());
    Float_t tmvaReadery34(std::numeric_limits<float>::max());
    Float_t tmvaReaderInvariantMassSystem(std::numeric_limits<float>::max());
    Float_t tmvaReaderCosThetaStarWBosons(std::numeric_limits<float>::max());
    Float_t tmvaReaderCosThetaStarZBosons(std::numeric_limits<float>::max());

    reader->AddVariable("RecoilMass", &tmvaReaderRecoilMass);
    reader->AddVariable("TransverseMomentum", &tmvaReaderTransverseMomentum);
    reader->AddVariable("TransverseEnergy", &tmvaReaderTransverseEnergy);
    reader->AddVariable("CosThetaMissing", &tmvaReaderCosThetaMissing);
    reader->AddVariable("CosThetaMostEnergeticTrack", &tmvaReaderCosThetaMostEnergeticTrack);
    reader->AddVariable("y34", &tmvaReadery34);
    reader->AddVariable("InvariantMassSystem", &tmvaReaderInvariantMassSystem);
    reader->AddVariable("CosThetaStarWBosons", &tmvaReaderCosThetaStarWBosons);
    reader->AddVariable("CosThetaStarZBosons", &tmvaReaderCosThetaStarZBosons);

    reader->BookMVA("BDT method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_BDT.weights.xml");

    for (ProcessVector::iterator itPro = processes.begin(); itPro != processes.end(); itPro++)
    {
        Int_t generatorSerialNumber(std::numeric_limits<int>::max());
        Double_t recoilMass(std::numeric_limits<float>::max());
        Double_t transverseMomentum(std::numeric_limits<float>::max());
        Double_t transverseEnergy(std::numeric_limits<float>::max());
        Double_t cosThetaMissing(std::numeric_limits<float>::max());
        Double_t cosThetaMostEnergeticTrack(std::numeric_limits<float>::max());
        Double_t energyAroundMostEnergeticTrack(std::numeric_limits<float>::max());
        Double_t y34(std::numeric_limits<float>::max());
        Double_t invariantMassSystem(std::numeric_limits<float>::max());
        Double_t cosThetaStarWBosons(std::numeric_limits<float>::max());
        Double_t cosThetaStarZBosons(std::numeric_limits<float>::max());
        Double_t bdt(std::numeric_limits<float>::max());
        IntVector *nParticlesJets(NULL);
        IntVector *nChargedParticlesJets(NULL);
        DoubleVector *cosThetaStarWJets(NULL);
        DoubleVector *cosThetaStarZJets(NULL);
        DoubleVector *energyJets(NULL);
        DoubleVector *invMassWVectors(NULL);
        DoubleVector *invMassZVectors(NULL);

        // To Save
        TTree *pTTree = new TTree("BDTTree", "BDTTree");
        pTTree->Branch("GeneratorSerialNumber", &generatorSerialNumber);
        pTTree->Branch("RecoilMass",&recoilMass);
        pTTree->Branch("TransverseMomentum",&transverseMomentum);
        pTTree->Branch("TransverseEnergy",&transverseEnergy);
        pTTree->Branch("CosThetaMissing",&cosThetaMissing);
        pTTree->Branch("CosThetaMostEnergeticTrack",&cosThetaMostEnergeticTrack);
        pTTree->Branch("EnergyAroundMostEnergeticTrack",&energyAroundMostEnergeticTrack);
        pTTree->Branch("y34",&y34);
        pTTree->Branch("InvariantMassSystem", &invariantMassSystem);
        pTTree->Branch("CosThetaStarWBosons", &cosThetaStarWBosons);
        pTTree->Branch("CosThetaStarZBosons", &cosThetaStarZBosons);
        pTTree->Branch("BDT", &bdt);
        pTTree->Branch("NParticlesJets",&nParticlesJets);
        pTTree->Branch("NChargedParticlesJets",&nChargedParticlesJets);
        pTTree->Branch("CosThetaStarWJets", &cosThetaStarWJets);
        pTTree->Branch("CosThetaStarZJets", &cosThetaStarZJets);
        pTTree->Branch("EnergyJets",&energyJets);
        pTTree->Branch("InvMassWVectors", &invMassWVectors);
        pTTree->Branch("InvMassZVectors", &invMassZVectors);

        const Process *pProcess(*itPro);
        TChain *pTChain = pProcess->GetTChain();

        // To Read
        pTChain->SetBranchAddress("RecoilMass",&recoilMass);
        pTChain->SetBranchAddress("TransverseMomentum",&transverseMomentum);
        pTChain->SetBranchAddress("TransverseEnergy",&transverseEnergy);
        pTChain->SetBranchAddress("CosThetaMissing",&cosThetaMissing);
        pTChain->SetBranchAddress("CosThetaMostEnergeticTrack",&cosThetaMostEnergeticTrack);
        pTChain->SetBranchAddress("EnergyAroundMostEnergeticTrack",&energyAroundMostEnergeticTrack);
        pTChain->SetBranchAddress("y34",&y34);
        pTChain->SetBranchAddress("InvariantMassSystem",&invariantMassSystem);
        pTChain->SetBranchAddress("CosThetaStarWBosons",&cosThetaStarWBosons);
        pTChain->SetBranchAddress("CosThetaStarZBosons",&cosThetaStarZBosons);
        pTChain->SetBranchAddress("NParticlesJets",&nParticlesJets);
        pTChain->SetBranchAddress("NChargedParticlesJets",&nChargedParticlesJets);
        pTChain->SetBranchAddress("CosThetaStarWJets",&cosThetaStarWJets);
        pTChain->SetBranchAddress("CosThetaStarZJets",&cosThetaStarZJets);
        pTChain->SetBranchAddress("EnergyJets",&energyJets);
        pTChain->SetBranchAddress("InvMassWVectors",&invMassWVectors);
        pTChain->SetBranchAddress("InvMassZVectors",&invMassZVectors);

        std::cout << "Number of TChain entries: " << pTChain->GetEntries() << std::endl;
        std::cout << "Number of TrainingTChain entries: " << pProcess->GetTrainingTChain()->GetEntries() << std::endl;

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);

            TFile *pTFileActive = pTChain->GetCurrentFile();
            std::string activeFileName(pTFileActive->GetName());

            if (pProcess->GetEventType() == "ee_nunuqqqq")
            {
                generatorSerialNumber = atoi(this->GetGeneratorSerialNumber(activeFileName).c_str());
            }
            else
            {
                generatorSerialNumber = -1;
            }

            tmvaReaderRecoilMass = recoilMass; 
            tmvaReaderTransverseMomentum = transverseMomentum;
            tmvaReaderTransverseEnergy = transverseEnergy;
            tmvaReaderCosThetaMissing = cosThetaMissing;
            tmvaReaderCosThetaMostEnergeticTrack = cosThetaMostEnergeticTrack;
            tmvaReadery34 = y34;
            tmvaReaderInvariantMassSystem = invariantMassSystem;
            tmvaReaderCosThetaStarWBosons = cosThetaStarWBosons;
            tmvaReaderCosThetaStarZBosons = cosThetaStarZBosons;
            bdt = reader->EvaluateMVA("BDT method");

            pTTree->Fill();
        }

        TString filename = "RootFiles_BDT_" + pProcess->GetEventType() + "_" + this->NumberToString(pProcess->GetEnergy()) + "GeV.root";
        TFile *pTFile = new TFile(filename, "recreate");
        pTTree->SetDirectory(pTFile);

        pTFile->cd();
        pTTree->Write();

        pTFile->Close();
        delete pTFile;
    }
}

//=====================================================================

std::string TMVAClassificationApplication::GetGeneratorSerialNumber(std::string filename)
{
    std::size_t position = filename.find("GenNumber");
    return filename.substr(position+10,3);
}

//=====================================================================

template <class T>
std::string TMVAClassificationApplication::NumberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

//=====================================================================
