#!/bin/bash
source /afs/cern.ch/eng/clic/software/DIRAC/bashrc
dirac-proxy-init

rm -rf ./lib/marlin_dll/
mkdir ./lib/marlin_dll/
cp ./lib/lib* ./lib/marlin_dll/

MarlinLibs="MarlinSelectionProcessor"

rm $MarlinLibs.tar
rm $MarlinLibs.tar.gz

tar -cvf $MarlinLibs.tar lib/marlin_dll/
gzip $MarlinLibs.tar

dirac-dms-remove-files /ilc/user/s/sgreen/SelectionProcessorTarBall/$MarlinLibs.tar.gz

dirac-dms-add-file /ilc/user/s/sgreen/SelectionProcessorTarBall/$MarlinLibs.tar.gz $MarlinLibs.tar.gz CERN-SRM

dirac-dms-replicate-lfn /ilc/user/s/sgreen/SelectionProcessorTarBall/$MarlinLibs.tar.gz DESY-SRM
dirac-dms-replicate-lfn /ilc/user/s/sgreen/SelectionProcessorTarBall/$MarlinLibs.tar.gz RAL-SRM
dirac-dms-replicate-lfn /ilc/user/s/sgreen/SelectionProcessorTarBall/$MarlinLibs.tar.gz CERN-DIP-4
dirac-dms-replicate-lfn /ilc/user/s/sgreen/SelectionProcessorTarBall/$MarlinLibs.tar.gz CERN-DST-EOS
dirac-dms-replicate-lfn /ilc/user/s/sgreen/SelectionProcessorTarBall/$MarlinLibs.tar.gz PNNL3-SRM

