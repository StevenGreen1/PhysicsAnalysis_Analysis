export ILCSOFT=/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09


#--------------------------------------------------------------------------------
#     LCCD
#--------------------------------------------------------------------------------
export LCCD="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/lccd/v01-03"


#--------------------------------------------------------------------------------
#     CondDBMySQL
#--------------------------------------------------------------------------------
export COND_DB_DEBUGLOG="/dev/stdout"
export CondDBMySQL="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/CondDBMySQL/CondDBMySQL_ILC-0-9-6"
export LD_LIBRARY_PATH="$CondDBMySQL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCIO
#--------------------------------------------------------------------------------
export LCIO="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/lcio/v02-07"
export PYTHONPATH="$LCIO/src/python:$LCIO/examples/python:$PYTHONPATH"
export PATH="$LCIO/tools:$LCIO/bin:$PATH"
export LD_LIBRARY_PATH="$LCIO/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     ROOT
#--------------------------------------------------------------------------------
export ROOTSYS="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/root/5.34.30"
export PYTHONPATH="$ROOTSYS/lib:$PYTHONPATH"
export PATH="$ROOTSYS/bin:$PATH"
export LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Marlin
#--------------------------------------------------------------------------------
export MARLIN="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Marlin/v01-08"
export PATH="$MARLIN/bin:$PATH"
export MARLIN_DLL="/var/clus/usera/sg568/PhysicsAnalysis/Analysis/WhizardWeightingMarlin/lib/libGeneratorProcessor.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinDD4hep/v00-01/lib/libMarlinDD4hep.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/DDMarlinPandora/v00-03/lib/libDDMarlinPandora.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinReco/v01-14/lib/libMarlinReco.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/PandoraAnalysis/v01-02-00/lib/libPandoraAnalysis.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinPandora/v02-02-00/lib/libMarlinPandora.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/LCFIVertex/v00-07-01/lib/libLCFIVertex.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/CEDViewer/v01-11/lib/libCEDViewer.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Overlay/v00-14/lib/libOverlay.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/FastJetClustering/v00-02/lib/libFastJetClustering.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinFastJet/v00-02/lib/libMarlinFastJet.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/LCTuple/v01-05/lib/libLCTuple.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinKinfit/v00-02/lib/libMarlinKinfit.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinKinfitProcessors/v00-01/lib/libMarlinKinfitProcessors.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinTrkProcessors/v02-02/lib/libMarlinTrkProcessors.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/ILDPerformance/v00-02/lib/libILDPerformance.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Clupatra/v00-13/lib/libClupatra.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Physsim/v00-02/lib/libPhyssim.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/FCalClusterer/v00-02/lib/libFCalClusterer.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/LCFIPlus/v00-07/lib/libLCFIPlus.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/ForwardTracking/v01-09/lib/libForwardTracking.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinTPC/v01-01/lib/libMarlinTPC.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Garlic/v3.0.3/lib/libGarlic.so:$MARLIN_DLL"


#--------------------------------------------------------------------------------
#     CLHEP
#--------------------------------------------------------------------------------
export CLHEP="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/CLHEP/2.1.4.1"
export CLHEP_BASE_DIR="$CLHEP"
export CLHEP_INCLUDE_DIR="$CLHEP/include"
export PATH="$CLHEP_BASE_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$CLHEP_BASE_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     RAIDA
#--------------------------------------------------------------------------------
export RAIDA_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/RAIDA/v01-06-02"
export PATH="$RAIDA_HOME/bin:$PATH"


#--------------------------------------------------------------------------------
#     GEAR
#--------------------------------------------------------------------------------
export GEAR="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/gear/v01-05"
export PATH="$GEAR/tools:$GEAR/bin:$PATH"
export LD_LIBRARY_PATH="$GEAR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DD4hep
#--------------------------------------------------------------------------------
export DD4hepINSTALL="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/DD4hep/v00-15"
export DD4HEP="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/DD4hep/v00-15"
export PYTHONPATH="$DD4HEP/python:$DD4HEP/DDCore/python:$PYTHONPATH"
export PATH="$DD4HEP/bin:$PATH"
export LD_LIBRARY_PATH="$DD4HEP/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Geant4
#--------------------------------------------------------------------------------
export G4INSTALL="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/geant4/10.01"
export G4ENV_INIT="$G4INSTALL/bin/geant4.sh"
export G4SYSTEM="Linux-g++"


#--------------------------------------------------------------------------------
#     QT
#--------------------------------------------------------------------------------
export QTDIR="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/QT/4.7.4"
export QMAKESPEC="$QTDIR/mkspecs/linux-g++"
export PATH="$QTDIR/bin:$PATH"
export LD_LIBRARY_PATH="$QTDIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     XercesC
#--------------------------------------------------------------------------------
export XercesC_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/xercesc/3.1.2"
export PATH="$XercesC_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$XercesC_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Boost
#--------------------------------------------------------------------------------
export BOOST_ROOT="/afs/desy.de/project/ilcsoft/sw/boost/1.58.0"


#--------------------------------------------------------------------------------
#     GSL
#--------------------------------------------------------------------------------
export GSL_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/gsl/1.14"
export PATH="$GSL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$GSL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CED
#--------------------------------------------------------------------------------
export PATH="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/CED/v01-09-02/bin:$PATH"


#--------------------------------------------------------------------------------
#     PandoraPFANew
#--------------------------------------------------------------------------------
export PANDORAPFANEW="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/PandoraPFANew/v02-05-00"
export LD_LIBRARY_PATH="$PANDORAPFANEW/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Mokka
#--------------------------------------------------------------------------------
export MOKKA="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Mokka/mokka-08-05-01"
export PATH="$MOKKA/bin:$PATH"


#--------------------------------------------------------------------------------
#     MySQL
#--------------------------------------------------------------------------------
export MYSQL_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/mysql/5.0.45"
export MYSQL_LIBDIR="$MYSQL_HOME/lib64/mysql"
export MYSQL_PATH="$MYSQL_HOME"
export MYSQL="$MYSQL_HOME"
export PATH="$MYSQL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$MYSQL_HOME/lib64/mysql:$MYSQL_HOME/lib64:$MYSQL_HOME/lib/mysql:$MYSQL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CERNLIB
#--------------------------------------------------------------------------------
export CERN_ROOT="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/cernlib/2006"
export CERN="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/cernlib"
export CERN_LEVEL="2006"
export CVSCOSRC="$CERN_ROOT/src"
export PATH="$CERN_ROOT/bin:$PATH"


#--------------------------------------------------------------------------------
#     CEDViewer
#--------------------------------------------------------------------------------
export PATH="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/CEDViewer/v01-11/bin:$PATH"


#--------------------------------------------------------------------------------
#     FastJet
#--------------------------------------------------------------------------------
export FastJet_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/FastJet/3.1.2"
export PATH="$FastJet_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$FastJet_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     KalTest
#--------------------------------------------------------------------------------
export KALTEST="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/KalTest/v02-01"
export LD_LIBRARY_PATH="$KALTEST/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     aidaTT
#--------------------------------------------------------------------------------
export AIDATT="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/aidaTT/v00-03"
export PATH="$AIDATT/bin:$PATH"
export LD_LIBRARY_PATH="$AIDATT/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GBL
#--------------------------------------------------------------------------------
export GBL="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/GBL/V01-16-04"
export LD_LIBRARY_PATH="$GBL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MarlinTPC
#--------------------------------------------------------------------------------
export MARLINTPC="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/MarlinTPC/v01-01"
export PATH="$MARLINTPC/bin:$PATH"


#--------------------------------------------------------------------------------
#     Druid
#--------------------------------------------------------------------------------
export DRUID="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Druid/2.2"
export PATH="$DRUID/bin:$PATH"


#--------------------------------------------------------------------------------
#     HepPDT
#--------------------------------------------------------------------------------
export HepPDT_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/heppdt/3.04.01"
export PATH="$HepPDT_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$HepPDT_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GDML
#--------------------------------------------------------------------------------
export GDML="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/gdml/ilcsoft-v01-17-07"
export LD_LIBRARY_PATH="$GDML/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCDD
#--------------------------------------------------------------------------------
export LCDD="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/lcdd/ilcsoft-v01-17-07"
export GDML_SCHEMA_DIR="$LCDD"
export LD_LIBRARY_PATH="$LCDD/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     SLIC
#--------------------------------------------------------------------------------
export SLIC="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/slic/ilcsoft-v01-17-07"
export PATH="$SLIC/build/bin:$PATH"
export LD_LIBRARY_PATH="$SLIC/build/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     SlicPandora
#--------------------------------------------------------------------------------
export SLICPANDORA="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/slicPandora/ilcsoft-v01-17-07"
export PATH="$SLICPANDORA/build/bin:$PATH"
export LD_LIBRARY_PATH="$SLICPANDORA/build/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     lcgeo
#--------------------------------------------------------------------------------
export lcgeo_DIR="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/lcgeo/v00-07"
export PYTHONPATH="$lcgeo_DIR/lib/python:$PYTHONPATH"
export PATH="$lcgeo_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$lcgeo_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DD4hepExamples
#--------------------------------------------------------------------------------
export DD4hepExamples="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/DD4hepExamples/v00-15"
export PATH="$DD4hepExamples/bin:$PATH"
export LD_LIBRARY_PATH="$DD4hepExamples/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CMake
#--------------------------------------------------------------------------------
export PATH="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/CMake/2.8.5/bin:$PATH"


#--------------------------------------------------------------------------------
#     ILCUTIL
#--------------------------------------------------------------------------------
export ilcutil="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/ilcutil/v01-02-01"
export LD_LIBRARY_PATH="$ilcutil/lib:$LD_LIBRARY_PATH"

# --- source GEANT4 INIT script ---
test -r ${G4ENV_INIT} && { cd $(dirname ${G4ENV_INIT}) ; . ./$(basename ${G4ENV_INIT}) ; cd $OLDPWD ; }

# ---  Workaraund for OpenGl bug on SL6  ---
export LIBGL_ALWAYS_INDIRECT=1
