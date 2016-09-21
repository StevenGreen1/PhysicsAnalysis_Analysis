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

    const Process *pProcess_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqqqq",22.16,1500,1400,5);
    //const Process *pProcess_CLIC_ee_nunuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","CLIC_ee_nunuqqqq",24.7,1500,1400,3); // <-CLIC

    // CLIC Backgrounds
/*
    const Process *pProcess_ee_lnuqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqqqq",115.3,1500,1400,5);
    const Process *pProcess_ee_llqqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_llqqqq",71.7,1500,1400,5);
    const Process *pProcess_ee_qqqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqqq",1328.1,1500,1400,5);

    const Process *pProcess_ee_nunuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_nunuqq",933.9,1500,1400,5);
    const Process *pProcess_ee_lnuqq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_lnuqq",4309.7,1500,1400,5);
    const Process *pProcess_ee_qqll = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qqll",2725.8,1500,1400,5);
    const Process *pProcess_ee_qq = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","ee_qq",4009.5,1500,1400,5);

    const Process *pProcess_egamma_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_EPA",287.1,1500,1400,5);
    const Process *pProcess_egamma_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqe_BS",1160.7,1500,1400,5);
    const Process *pProcess_gammae_qqqqe_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_EPA",286.9,1500,1400,5);
    const Process *pProcess_gammae_qqqqe_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqe_BS",1156.3,1500,1400,5);

    const Process *pProcess_egamma_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_EPA",32.6,1500,1400,5);
    const Process *pProcess_egamma_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","egamma_qqqqnu_BS",136.9,1500,1400,5);
    const Process *pProcess_gammae_qqqqnu_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_EPA",32.6,1500,1400,5);
    const Process *pProcess_gammae_qqqqnu_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammae_qqqqnu_BS",136.4,1500,1400,5);

    const Process *pProcess_gammagamma_qqqq_EPA_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_EPA",753.0,1500,1400,5);
    const Process *pProcess_gammagamma_qqqq_EPA_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_EPA_BS",4034.8,1500,1400,5);
    const Process *pProcess_gammagamma_qqqq_BS_EPA = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_EPA",4018.7,1500,1400,5);
    const Process *pProcess_gammagamma_qqqq_BS_BS = new Process("PhysicsAnalysis","clic_ild_cdr","clic_ild_cdr_ggHadBkg","gammagamma_qqqq_BS_BS",4009.5,1500,1400,5);
*/
    ProcessVector processes;

    processes.push_back(pProcess_ee_nunuqqqq);

//    processes.push_back(pProcess_CLIC_ee_nunuqqqq);
/*
    processes.push_back(pProcess_ee_lnuqqqq);
    processes.push_back(pProcess_ee_llqqqq);
    processes.push_back(pProcess_ee_qqqq);

    processes.push_back(pProcess_ee_nunuqq);
    processes.push_back(pProcess_ee_lnuqq);
    processes.push_back(pProcess_ee_qqll);
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
*/
    TMVAClassificationApplication *pTMVAClassificationApplication = new TMVAClassificationApplication(processes);
}

//=====================================================================

TMVAClassificationApplication::TMVAClassificationApplication(ProcessVector processes)
{
    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

    Float_t nPFOs(std::numeric_limits<int>::max());
    Float_t invMassWVector1(std::numeric_limits<float>::max());
    Float_t invMassWVector2(std::numeric_limits<float>::max());
    Float_t invMassZVector1(std::numeric_limits<float>::max());
    Float_t invMassZVector2(std::numeric_limits<float>::max());
    Float_t transverseMomentum(std::numeric_limits<float>::max());
    Float_t transverseMomentumBosonW1(std::numeric_limits<float>::max());
    Float_t transverseMomentumBosonW2(std::numeric_limits<float>::max());
    Float_t transverseMomentumBosonZ1(std::numeric_limits<float>::max());
    Float_t transverseMomentumBosonZ2(std::numeric_limits<float>::max());
    Float_t transverseEnergy(std::numeric_limits<float>::max());
    Float_t transverseEnergyBosonW1(std::numeric_limits<float>::max());
    Float_t transverseEnergyBosonW2(std::numeric_limits<float>::max());
    Float_t transverseEnergyBosonZ1(std::numeric_limits<float>::max());
    Float_t transverseEnergyBosonZ2(std::numeric_limits<float>::max());
    Float_t cosThetaMissing(std::numeric_limits<float>::max());
    Float_t cosThetaMostEnergeticTrack(std::numeric_limits<float>::max());
    Float_t y12(std::numeric_limits<float>::max());
    Float_t y23(std::numeric_limits<float>::max());
    Float_t y34(std::numeric_limits<float>::max());
    Float_t y45(std::numeric_limits<float>::max());
    Float_t y56(std::numeric_limits<float>::max());
    Float_t y67(std::numeric_limits<float>::max());
    Float_t invariantMassSystem(std::numeric_limits<float>::max());
    Float_t cosThetaStarWBosons(std::numeric_limits<float>::max());
    Float_t cosThetaStarZBosons(std::numeric_limits<float>::max());
    Float_t cosThetaStarWJet1(std::numeric_limits<float>::max());
    Float_t cosThetaStarWJet2(std::numeric_limits<float>::max());
    Float_t cosThetaStarZJet1(std::numeric_limits<float>::max());
    Float_t cosThetaStarZJet2(std::numeric_limits<float>::max());
    Float_t acolinearityJetsW1(std::numeric_limits<float>::max());
    Float_t acolinearityJetsW2(std::numeric_limits<float>::max());
    Float_t acolinearityJetsZ1(std::numeric_limits<float>::max());
    Float_t acolinearityJetsZ2(std::numeric_limits<float>::max());
    Float_t acolinearityBosonsW(std::numeric_limits<float>::max());
    Float_t acolinearityBosonsZ(std::numeric_limits<float>::max());
    Float_t principleThrustValue(std::numeric_limits<float>::max());
    Float_t majorThrustValue(std::numeric_limits<float>::max());
    Float_t minorThrustValue(std::numeric_limits<float>::max());
    Float_t sphericity(std::numeric_limits<float>::max());
    Float_t aplanarity(std::numeric_limits<float>::max());

    reader->AddVariable("NPfos := NParticlesJet1+NParticlesJet2+NParticlesJet3+NParticlesJet4", &nPFOs);
    reader->AddVariable("InvMassWVector1", &invMassWVector1);
    reader->AddVariable("InvMassWVector2", &invMassWVector2);
    reader->AddVariable("InvMassZVector1", &invMassZVector1);
    reader->AddVariable("InvMassZVector2", &invMassZVector2);
    reader->AddVariable("TransverseMomentum", &transverseMomentum);
    reader->AddVariable("TransverseMomentumBosonW1", &transverseMomentumBosonW1);
    reader->AddVariable("TransverseMomentumBosonW2", &transverseMomentumBosonW2);
    reader->AddVariable("TransverseMomentumBosonZ1", &transverseMomentumBosonZ1);
    reader->AddVariable("TransverseMomentumBosonZ2", &transverseMomentumBosonZ2);
    reader->AddVariable("TransverseEnergy", &transverseEnergy);
    reader->AddVariable("TransverseEnergyBosonW1", &transverseEnergyBosonW1);
    reader->AddVariable("TransverseEnergyBosonW2", &transverseEnergyBosonW2);
    reader->AddVariable("TransverseEnergyBosonZ1", &transverseEnergyBosonZ1);
    reader->AddVariable("TransverseEnergyBosonZ2", &transverseEnergyBosonZ2);
    reader->AddVariable("CosThetaMissing", &cosThetaMissing);
    reader->AddVariable("CosThetaMostEnergeticTrack", &cosThetaMostEnergeticTrack);
    reader->AddVariable("y12", &y12);
    reader->AddVariable("y23", &y23);
    reader->AddVariable("y34", &y34);
    reader->AddVariable("y45", &y45);
    reader->AddVariable("y56", &y56);
    reader->AddVariable("y67", &y67);
    reader->AddVariable("InvariantMassSystem", &invariantMassSystem);
    reader->AddVariable("CosThetaStarWBosons", &cosThetaStarWBosons);
    reader->AddVariable("CosThetaStarZBosons", &cosThetaStarZBosons);
//    reader->AddVariable("CosThetaStarWJet1", &cosThetaStarWJet1);
//    reader->AddVariable("CosThetaStarWJet2", &cosThetaStarWJet2);
//    reader->AddVariable("CosThetaStarZJet1", &cosThetaStarZJet1);
//    reader->AddVariable("CosThetaStarZJet2", &cosThetaStarZJet2);
    reader->AddVariable("AcolinearityJetsW1", &acolinearityJetsW1);
    reader->AddVariable("AcolinearityJetsW2", &acolinearityJetsW2);
    reader->AddVariable("AcolinearityJetsZ1", &acolinearityJetsZ1);
    reader->AddVariable("AcolinearityJetsZ2", &acolinearityJetsZ2);
    reader->AddVariable("AcolinearityBosonsW", &acolinearityBosonsW);
    reader->AddVariable("AcolinearityBosonsZ", &acolinearityBosonsZ);
    reader->AddVariable("PrincipleThrustValue", &principleThrustValue);
    reader->AddVariable("MajorThrustValue", &majorThrustValue);
    reader->AddVariable("MinorThrustValue", &minorThrustValue);
    reader->AddVariable("Sphericity", &sphericity);
    reader->AddVariable("Aplanarity", &aplanarity);

    reader->BookMVA("BDT method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_BDT.weights.xml");
//    reader->BookMVA("Cuts method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_Cuts.weights.xml");
//    reader->BookMVA("Likelihood method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_Likelihood.weights.xml");
//    reader->BookMVA("PDERS method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_PDERS.weights.xml");
//    reader->BookMVA("KNN method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_KNN.weights.xml");
//    reader->BookMVA("CFMlpANN method", "/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/weights/TMVAClassification_CFMlpANN.weights.xml");

    for (ProcessVector::iterator itPro = processes.begin(); itPro != processes.end(); itPro++)
    {
        Int_t nPFOs_ToRead(std::numeric_limits<int>::max());
        Int_t nPFOsJet1_ToRead(std::numeric_limits<int>::max());
        Int_t nPFOsJet2_ToRead(std::numeric_limits<int>::max());
        Int_t nPFOsJet3_ToRead(std::numeric_limits<int>::max());
        Int_t nPFOsJet4_ToRead(std::numeric_limits<int>::max());
        Double_t invMassWVector1_ToRead(std::numeric_limits<double>::max());
        Double_t invMassWVector2_ToRead(std::numeric_limits<double>::max());
        Double_t invMassZVector1_ToRead(std::numeric_limits<double>::max());
        Double_t invMassZVector2_ToRead(std::numeric_limits<double>::max());
        Double_t transverseMomentum_ToRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonW1_ToRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonW2_ToRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonZ1_ToRead(std::numeric_limits<double>::max());
        Double_t transverseMomentumBosonZ2_ToRead(std::numeric_limits<double>::max());
        Double_t transverseEnergy_ToRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonW1_ToRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonW2_ToRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonZ1_ToRead(std::numeric_limits<double>::max());
        Double_t transverseEnergyBosonZ2_ToRead(std::numeric_limits<double>::max());
        Double_t cosThetaMissing_ToRead(std::numeric_limits<double>::max());
        Double_t cosThetaMostEnergeticTrack_ToRead(std::numeric_limits<double>::max());
        Double_t y12_ToRead(std::numeric_limits<double>::max());
        Double_t y23_ToRead(std::numeric_limits<double>::max());
        Double_t y34_ToRead(std::numeric_limits<double>::max());
        Double_t y45_ToRead(std::numeric_limits<double>::max());
        Double_t y56_ToRead(std::numeric_limits<double>::max());
        Double_t y67_ToRead(std::numeric_limits<double>::max());
        Double_t invariantMassSystem_ToRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWBosons_ToRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZBosons_ToRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWJet1_ToRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarWJet2_ToRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZJet1_ToRead(std::numeric_limits<double>::max());
        Double_t cosThetaStarZJet2_ToRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsW1_ToRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsW2_ToRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsZ1_ToRead(std::numeric_limits<double>::max());
        Double_t acolinearityJetsZ2_ToRead(std::numeric_limits<double>::max());
        Double_t acolinearityBosonsW_ToRead(std::numeric_limits<double>::max());
        Double_t acolinearityBosonsZ_ToRead(std::numeric_limits<double>::max());
        Double_t principleThrustValue_ToRead(std::numeric_limits<double>::max());
        Double_t majorThrustValue_ToRead(std::numeric_limits<double>::max());
        Double_t minorThrustValue_ToRead(std::numeric_limits<double>::max());
        Double_t sphericity_ToRead(std::numeric_limits<double>::max());
        Double_t aplanarity_ToRead(std::numeric_limits<double>::max());

        Int_t globalEventNumber(std::numeric_limits<int>::max());
        Double_t bdt(std::numeric_limits<double>::max());
        Double_t cuts(std::numeric_limits<double>::max());
        Double_t likelihood(std::numeric_limits<double>::max());
        Double_t pders(std::numeric_limits<double>::max());
        Double_t knn(std::numeric_limits<double>::max());
        Double_t cfmlpann(std::numeric_limits<double>::max());

        // To Save
        TTree *pTTree = new TTree("MVATree", "MVATree");
        pTTree->Branch("GlobalEventNumber", &globalEventNumber);
        pTTree->Branch("InvMassWVector1", &invMassWVector1_ToRead);
        pTTree->Branch("InvMassWVector2", &invMassWVector2_ToRead);
        pTTree->Branch("InvMassZVector1", &invMassZVector1_ToRead);
        pTTree->Branch("InvMassZVector2", &invMassZVector2_ToRead);
        pTTree->Branch("TransverseMomentum", &transverseMomentum_ToRead);
        pTTree->Branch("InvariantMassSystem", &invariantMassSystem_ToRead);
        pTTree->Branch("CosThetaStarWBosons", &cosThetaStarWBosons_ToRead);
        pTTree->Branch("CosThetaStarZBosons", &cosThetaStarZBosons_ToRead);
        pTTree->Branch("CosThetaStarWJet1", &cosThetaStarWJet1_ToRead);
        pTTree->Branch("CosThetaStarWJet2", &cosThetaStarWJet2_ToRead);
        pTTree->Branch("CosThetaStarZJet1", &cosThetaStarZJet1_ToRead);
        pTTree->Branch("CosThetaStarZJet2", &cosThetaStarZJet2_ToRead);
        pTTree->Branch("BDT", &bdt);
//        pTTree->Branch("Cuts", &cuts);
//        pTTree->Branch("Likelihood", &likelihood);
//        pTTree->Branch("PDERS", &pders);
//        pTTree->Branch("KNN", &knn);
//        pTTree->Branch("CFMlpANN", &cfmlpann);

        const Process *pProcess(*itPro);
        TChain *pTChain = pProcess->GetTChain();

        // To Read
        pTChain->SetBranchAddress("NParticlesJet1", &nPFOsJet1_ToRead);
        pTChain->SetBranchAddress("NParticlesJet2", &nPFOsJet2_ToRead);
        pTChain->SetBranchAddress("NParticlesJet3", &nPFOsJet3_ToRead);
        pTChain->SetBranchAddress("NParticlesJet4", &nPFOsJet4_ToRead);
        pTChain->SetBranchAddress("InvMassWVector1", &invMassWVector1_ToRead);
        pTChain->SetBranchAddress("InvMassWVector2", &invMassWVector2_ToRead);
        pTChain->SetBranchAddress("InvMassZVector1", &invMassZVector1_ToRead);
        pTChain->SetBranchAddress("InvMassZVector2", &invMassZVector2_ToRead);
        pTChain->SetBranchAddress("TransverseMomentum", &transverseMomentum_ToRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonW1", &transverseMomentumBosonW1_ToRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonW2", &transverseMomentumBosonW2_ToRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonZ1", &transverseMomentumBosonZ1_ToRead);
        pTChain->SetBranchAddress("TransverseMomentumBosonZ2", &transverseMomentumBosonZ2_ToRead);
        pTChain->SetBranchAddress("TransverseEnergy", &transverseEnergy_ToRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonW1", &transverseEnergyBosonW1_ToRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonW2", &transverseEnergyBosonW2_ToRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonZ1", &transverseEnergyBosonZ1_ToRead);
        pTChain->SetBranchAddress("TransverseEnergyBosonZ2", &transverseEnergyBosonZ2_ToRead);
        pTChain->SetBranchAddress("CosThetaMissing", &cosThetaMissing_ToRead);
        pTChain->SetBranchAddress("CosThetaMostEnergeticTrack", &cosThetaMostEnergeticTrack_ToRead);
        pTChain->SetBranchAddress("y12", &y12_ToRead);
        pTChain->SetBranchAddress("y23", &y23_ToRead);
        pTChain->SetBranchAddress("y34", &y34_ToRead);
        pTChain->SetBranchAddress("y45", &y45_ToRead);
        pTChain->SetBranchAddress("y56", &y56_ToRead);
        pTChain->SetBranchAddress("y67", &y67_ToRead);
        pTChain->SetBranchAddress("InvariantMassSystem", &invariantMassSystem_ToRead);
        pTChain->SetBranchAddress("CosThetaStarWBosons", &cosThetaStarWBosons_ToRead);
        pTChain->SetBranchAddress("CosThetaStarZBosons", &cosThetaStarZBosons_ToRead);
        pTChain->SetBranchAddress("CosThetaStarWJet1", &cosThetaStarWJet1_ToRead);
        pTChain->SetBranchAddress("CosThetaStarWJet2", &cosThetaStarWJet2_ToRead);
        pTChain->SetBranchAddress("CosThetaStarZJet1", &cosThetaStarZJet1_ToRead);
        pTChain->SetBranchAddress("CosThetaStarZJet2", &cosThetaStarZJet2_ToRead);
        pTChain->SetBranchAddress("AcolinearityJetsW1", &acolinearityJetsW1_ToRead);
        pTChain->SetBranchAddress("AcolinearityJetsW2", &acolinearityJetsW2_ToRead);
        pTChain->SetBranchAddress("AcolinearityJetsZ1", &acolinearityJetsZ1_ToRead);
        pTChain->SetBranchAddress("AcolinearityJetsZ2", &acolinearityJetsZ2_ToRead);
        pTChain->SetBranchAddress("AcolinearityBosonsW", &acolinearityBosonsW_ToRead);
        pTChain->SetBranchAddress("AcolinearityBosonsZ", &acolinearityBosonsZ_ToRead);
        pTChain->SetBranchAddress("PrincipleThrustValue", &principleThrustValue_ToRead);
        pTChain->SetBranchAddress("MajorThrustValue", &majorThrustValue_ToRead);
        pTChain->SetBranchAddress("MinorThrustValue", &minorThrustValue_ToRead);
        pTChain->SetBranchAddress("Sphericity", &sphericity_ToRead);
        pTChain->SetBranchAddress("Aplanarity", &aplanarity_ToRead);

        std::cout << "Number of TChain entries: " << pTChain->GetEntries() << std::endl;
        std::cout << "Number of TrainingTChain entries: " << pProcess->GetTrainingTChain()->GetEntries() << std::endl;

        int eventCounter(0), generatorSerialNumber(std::numeric_limits<int>::max());
        IntVector readInSGN;

        for (unsigned int event = 0; event < pTChain->GetEntries(); event++)
        {
            pTChain->GetEntry(event);
            nPFOs_ToRead = nPFOsJet1_ToRead + nPFOsJet2_ToRead + nPFOsJet3_ToRead + nPFOsJet4_ToRead;

            TFile *pTFileActive = pTChain->GetCurrentFile();
            std::string activeFileName(pTFileActive->GetName());

            if (pProcess->GetEventType() == "ee_nunuqqqq")
            {
                generatorSerialNumber = atoi(this->GetGeneratorSerialNumber(activeFileName).c_str());

                if (std::find(readInSGN.begin(), readInSGN.end(), generatorSerialNumber) == readInSGN.end())
                {
                    readInSGN.push_back(generatorSerialNumber);
                    eventCounter = 0;
                }
            }
            else
            {
                generatorSerialNumber = 0;
            }

            eventCounter++;

            //globalEventNumber = ((generatorSerialNumber-1) * 1e3) + eventCounter;
            globalEventNumber = (generatorSerialNumber * 1e3) + eventCounter;

            std::cout << "generatorSerialNumber : " << generatorSerialNumber << std::endl;
            std::cout << "eventCounter : " << eventCounter << std::endl;
            std::cout << "globalEventNumber : " << globalEventNumber<< std::endl;

            nPFOs = nPFOs_ToRead;
            invMassWVector1 = invMassWVector1_ToRead;
            invMassWVector2 = invMassWVector2_ToRead;
            invMassZVector1 = invMassZVector1_ToRead;
            invMassZVector2 = invMassZVector2_ToRead;
            transverseMomentum = transverseMomentum_ToRead;
            transverseMomentumBosonW1 = transverseMomentumBosonW1_ToRead;
            transverseMomentumBosonW2 = transverseMomentumBosonW2_ToRead;
            transverseMomentumBosonZ1 = transverseMomentumBosonZ1_ToRead;
            transverseMomentumBosonZ2 = transverseMomentumBosonZ2_ToRead;
            transverseEnergy = transverseEnergy_ToRead;
            transverseEnergyBosonW1 = transverseEnergyBosonW1_ToRead;
            transverseEnergyBosonW2 = transverseEnergyBosonW2_ToRead;
            transverseEnergyBosonZ1 = transverseEnergyBosonZ1_ToRead;
            transverseEnergyBosonZ2 = transverseEnergyBosonZ2_ToRead;
            cosThetaMissing = cosThetaMissing_ToRead;
            cosThetaMostEnergeticTrack = cosThetaMostEnergeticTrack_ToRead;
            y12 = y12_ToRead;
            y23 = y23_ToRead;
            y34 = y34_ToRead;
            y45 = y45_ToRead;
            y56 = y56_ToRead;
            y67 = y67_ToRead;
            invariantMassSystem = invariantMassSystem_ToRead;
            cosThetaStarWBosons = cosThetaStarWBosons_ToRead;
            cosThetaStarZBosons = cosThetaStarZBosons_ToRead;
            cosThetaStarWJet1 = cosThetaStarWJet1_ToRead;
            cosThetaStarWJet2 = cosThetaStarWJet2_ToRead;
            cosThetaStarZJet1 = cosThetaStarZJet1_ToRead;
            cosThetaStarZJet2 = cosThetaStarZJet2_ToRead;
            acolinearityJetsW1 = acolinearityJetsW1_ToRead;
            acolinearityJetsW2 = acolinearityJetsW2_ToRead;
            acolinearityJetsZ1 = acolinearityJetsZ1_ToRead;
            acolinearityJetsZ2 = acolinearityJetsZ2_ToRead;
            acolinearityBosonsW = acolinearityBosonsW_ToRead;
            acolinearityBosonsZ = acolinearityBosonsZ_ToRead;
            principleThrustValue = principleThrustValue_ToRead;
            majorThrustValue = majorThrustValue_ToRead;
            minorThrustValue = minorThrustValue_ToRead;
            sphericity = sphericity_ToRead;
            aplanarity = aplanarity_ToRead;

            bdt = reader->EvaluateMVA("BDT method");
//            cuts = reader->EvaluateMVA("Cuts method");
//            likelihood = reader->EvaluateMVA("Likelihood method");
//            pders = reader->EvaluateMVA("PDERS method");
//            knn = reader->EvaluateMVA("KNN method");
//            cfmlpann = reader->EvaluateMVA("CFMlpANN method");

//            pTTree->Fill();
        }

//        TString filename = "RootFiles_Multivariant_" + pProcess->GetEventType() + "_" + this->NumberToString(pProcess->GetEnergy()) + "GeV.root";
//        TFile *pTFile = new TFile(filename, "recreate");
//        pTTree->SetDirectory(pTFile);

//        pTFile->cd();
//        pTTree->Write();

//        pTFile->Close();
//        delete pTFile;
    }
}

//=====================================================================

std::string TMVAClassificationApplication::GetGeneratorSerialNumber(std::string filename)
{
    std::size_t position = filename.find("GenN");
    std::string substring = filename.substr(position+5);
    std::size_t position2 = substring.find("_");
    std::string substring2 = substring.substr(0,position2);
    return substring2;
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
