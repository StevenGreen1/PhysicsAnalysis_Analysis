#!/bin/bash
source /afs/cern.ch/eng/clic/software/DIRAC/bashrc
dirac-proxy-init

ToTarBall="lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_1p00"

rm $ToTarBall.tar
rm $ToTarBall.tar.gz

#pcla> cd lcfiweights_1400GeV_SelectedPFOs_kt_algorithm_2jets_0p70/
#2jets_c0_bdt.class.C      2jets_c0.root             2jets_c1_bdt.weights.xml  2jets_c2_bdt.class.C      2jets_c2.root             2jets_c3_bdt.weights.xml  MarlinSteering.xml
#2jets_c0_bdt.weights.xml  2jets_c1_bdt.class.C      2jets_c1.root             2jets_c2_bdt.weights.xml  2jets_c3_bdt.class.C      2jets_c3.root

tar -cvf $ToTarBall.tar ${ToTarBall}/2jets*
gzip $ToTarBall.tar

dirac-dms-remove-files /ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/$ToTarBall.tar.gz

dirac-dms-add-file /ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/$ToTarBall.tar.gz $ToTarBall.tar.gz CERN-SRM

mkdir UploadedTarball
mv $ToTarBall.tar.gz UploadedTarball

dirac-dms-replicate-lfn /ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/$ToTarBall.tar.gz DESY-SRM
dirac-dms-replicate-lfn /ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/$ToTarBall.tar.gz RAL-SRM
dirac-dms-replicate-lfn /ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/$ToTarBall.tar.gz CERN-DIP-4
dirac-dms-replicate-lfn /ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/$ToTarBall.tar.gz CERN-DST-EOS
dirac-dms-replicate-lfn /ilc/user/s/sgreen/PhysicsAnalysis/LcfiWeights/$ToTarBall.tar.gz PNNL3-SRM

