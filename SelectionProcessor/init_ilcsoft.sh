export ILCSOFT=/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08


#--------------------------------------------------------------------------------
#     LCCD
#--------------------------------------------------------------------------------
export LCCD="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/lccd/v01-03"


#--------------------------------------------------------------------------------
#     CondDBMySQL
#--------------------------------------------------------------------------------
export COND_DB_DEBUGLOG="/dev/stdout"
export CondDBMySQL="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/CondDBMySQL/CondDBMySQL_ILC-0-9-6"
export LD_LIBRARY_PATH="$CondDBMySQL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCIO
#--------------------------------------------------------------------------------
export LCIO="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/lcio/v02-06"
export PYTHONPATH="$LCIO/src/python:$LCIO/examples/python:$PYTHONPATH"
export PATH="$LCIO/tools:$LCIO/bin:$PATH"
export LD_LIBRARY_PATH="$LCIO/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     ROOT
#--------------------------------------------------------------------------------
export ROOTSYS="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/root/5.34.30"
export PYTHONPATH="$ROOTSYS/lib:$PYTHONPATH"
export PATH="$ROOTSYS/bin:$PATH"
export LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CMake
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/CMake/2.8.5/bin:$PATH"


#--------------------------------------------------------------------------------
#     ILCUTIL
#--------------------------------------------------------------------------------
export ilcutil="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/ilcutil/v01-02-01"
export LD_LIBRARY_PATH="$ilcutil/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Marlin
#--------------------------------------------------------------------------------
export MARLIN="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/Marlin/v01-07"
export PATH="$MARLIN/bin:$PATH"
export MARLIN_DLL="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/MarlinDD4hep/v00-01/lib/libMarlinDD4hep.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/DDMarlinPandora/v00-01/lib/libDDMarlinPandora.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/MarlinReco/v01-13/lib/libMarlinReco.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/PandoraAnalysis/v01-00-01/lib/libPandoraAnalysis.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/MarlinPandora/v02-00-00/lib/libMarlinPandora.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/LCFIVertex/v00-07/lib/libLCFIVertex.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/CEDViewer/v01-10/lib/libCEDViewer.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/Overlay/v00-14/lib/libOverlay.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/FastJetClustering/v00-02/lib/libFastJetClustering.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/MarlinFastJet/v00-02/lib/libMarlinFastJet.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/LCTuple/v01-04/lib/libLCTuple.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/MarlinKinfit/v00-01-05/lib/libMarlinKinfit.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/MarlinTrkProcessors/v02-01/lib/libMarlinTrkProcessors.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/ILDPerformance/v00-01/lib/libILDPerformance.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/Clupatra/v00-12/lib/libClupatra.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/Physsim/v00-02/lib/libPhyssim.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/FCalClusterer/v00-01/lib/libFCalClusterer.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/LCFIPlus/v00-05-03/lib/libLCFIPlus.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/ForwardTracking/v01-08/lib/libForwardTracking.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/MarlinTPC/v01-00/lib/libMarlinTPC.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/Garlic/v3.0.3/lib/libGarlic.so:$MARLIN_DLL"


#--------------------------------------------------------------------------------
#     CLHEP
#--------------------------------------------------------------------------------
export CLHEP="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/CLHEP/2.1.4.1"
export CLHEP_BASE_DIR="$CLHEP"
export CLHEP_INCLUDE_DIR="$CLHEP/include"
export PATH="$CLHEP_BASE_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$CLHEP_BASE_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     RAIDA
#--------------------------------------------------------------------------------
export RAIDA_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/RAIDA/v01-06-02"
export PATH="$RAIDA_HOME/bin:$PATH"


#--------------------------------------------------------------------------------
#     GEAR
#--------------------------------------------------------------------------------
export GEAR="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/gear/v01-04-02"
export PATH="$GEAR/tools:$GEAR/bin:$PATH"
export LD_LIBRARY_PATH="$GEAR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DD4hep
#--------------------------------------------------------------------------------
export DD4hepINSTALL="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/DD4hep/v00-14"
export DD4HEP="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/DD4hep/v00-14"
export PYTHONPATH="$DD4HEP/python:$DD4HEP/DDCore/python:$PYTHONPATH"
export PATH="$DD4HEP/bin:$PATH"
export LD_LIBRARY_PATH="$DD4HEP/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Geant4
#--------------------------------------------------------------------------------
export G4INSTALL="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/geant4/10.01"
export G4ENV_INIT="$G4INSTALL/bin/geant4.sh"
export G4SYSTEM="Linux-g++"


#--------------------------------------------------------------------------------
#     QT
#--------------------------------------------------------------------------------
export QTDIR="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/QT/4.7.4"
export QMAKESPEC="$QTDIR/mkspecs/linux-g++"
export PATH="$QTDIR/bin:$PATH"
export LD_LIBRARY_PATH="$QTDIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     XercesC
#--------------------------------------------------------------------------------
export XercesC_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/xercesc/3.1.2"
export PATH="$XercesC_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$XercesC_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Boost
#--------------------------------------------------------------------------------
export BOOST_ROOT="/afs/desy.de/project/ilcsoft/sw/boost/1.58.0"


#--------------------------------------------------------------------------------
#     GSL
#--------------------------------------------------------------------------------
export GSL_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/gsl/1.14"
export PATH="$GSL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$GSL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CED
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/CED/v01-09-01/bin:$PATH"


#--------------------------------------------------------------------------------
#     PandoraPFANew
#--------------------------------------------------------------------------------
export PANDORAPFANEW="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/PandoraPFANew/v02-00-00"
export LD_LIBRARY_PATH="$PANDORAPFANEW/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Mokka
#--------------------------------------------------------------------------------
export MOKKA="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/Mokka/mokka-08-05"
export PATH="$MOKKA/bin:$PATH"


#--------------------------------------------------------------------------------
#     MySQL
#--------------------------------------------------------------------------------
export MYSQL_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/mysql/5.0.45"
export MYSQL_LIBDIR="$MYSQL_HOME/lib64/mysql"
export MYSQL_PATH="$MYSQL_HOME"
export MYSQL="$MYSQL_HOME"
export PATH="$MYSQL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$MYSQL_HOME/lib64/mysql:$MYSQL_HOME/lib64:$MYSQL_HOME/lib/mysql:$MYSQL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CERNLIB
#--------------------------------------------------------------------------------
export CERN_ROOT="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/cernlib/2006"
export CERN="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/cernlib"
export CERN_LEVEL="2006"
export CVSCOSRC="$CERN_ROOT/src"
export PATH="$CERN_ROOT/bin:$PATH"


#--------------------------------------------------------------------------------
#     CEDViewer
#--------------------------------------------------------------------------------
export PATH="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/CEDViewer/v01-10/bin:$PATH"


#--------------------------------------------------------------------------------
#     FastJet
#--------------------------------------------------------------------------------
export FastJet_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/FastJet/3.1.2"
export PATH="$FastJet_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$FastJet_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     KalTest
#--------------------------------------------------------------------------------
export KALTEST="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/KalTest/v02-00"
export LD_LIBRARY_PATH="$KALTEST/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     aidaTT
#--------------------------------------------------------------------------------
export AIDATT="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/aidaTT/v00-02"
export PATH="$AIDATT/bin:$PATH"
export LD_LIBRARY_PATH="$AIDATT/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GBL
#--------------------------------------------------------------------------------
export GBL="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/GBL/V01-16-04"
export LD_LIBRARY_PATH="$GBL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MarlinTPC
#--------------------------------------------------------------------------------
export MARLINTPC="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/MarlinTPC/v01-00"
export PATH="$MARLINTPC/bin:$PATH"


#--------------------------------------------------------------------------------
#     Druid
#--------------------------------------------------------------------------------
export DRUID="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/Druid/2.2"
export PATH="$DRUID/bin:$PATH"


#--------------------------------------------------------------------------------
#     HepPDT
#--------------------------------------------------------------------------------
export HepPDT_HOME="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/heppdt/3.04.01"
export PATH="$HepPDT_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$HepPDT_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GDML
#--------------------------------------------------------------------------------
export GDML="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/gdml/ilcsoft-v01-17-07"
export LD_LIBRARY_PATH="$GDML/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCDD
#--------------------------------------------------------------------------------
export LCDD="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/lcdd/ilcsoft-v01-17-07"
export GDML_SCHEMA_DIR="$LCDD"
export LD_LIBRARY_PATH="$LCDD/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     SLIC
#--------------------------------------------------------------------------------
export SLIC="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/slic/ilcsoft-v01-17-07"
export PATH="$SLIC/build/bin:$PATH"
export LD_LIBRARY_PATH="$SLIC/build/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     SlicPandora
#--------------------------------------------------------------------------------
export SLICPANDORA="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/slicPandora/ilcsoft-v01-17-07"
export PATH="$SLICPANDORA/build/bin:$PATH"
export LD_LIBRARY_PATH="$SLICPANDORA/build/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     lcgeo
#--------------------------------------------------------------------------------
export lcgeo_DIR="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/lcgeo/v00-05"
export PATH="$lcgeo_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$lcgeo_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DD4hepExamples
#--------------------------------------------------------------------------------
export DD4hepExamples="/cvmfs/ilc.desy.de/sw/x86_64_gcc48_sl6/v01-17-08/DD4hepExamples/v00-14"
export PATH="$DD4hepExamples/bin:$PATH"
export LD_LIBRARY_PATH="$DD4hepExamples/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Java
#--------------------------------------------------------------------------------
export JAVA_HOME="/afs/desy.de/group/it/ilcsoft/java/1.6.0"
export JDK_HOME="$JAVA_HOME"
export PATH="$JDK_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$JDK_HOME/jre/lib/i386:$JDK_HOME/jre/lib/i386/client:$LD_LIBRARY_PATH"

# --- source GEANT4 INIT script ---
test -r ${G4ENV_INIT} && { cd $(dirname ${G4ENV_INIT}) ; . ./$(basename ${G4ENV_INIT}) ; cd $OLDPWD ; }

# ---  Workaraund for OpenGl bug on SL6  ---
export LIBGL_ALWAYS_INDIRECT=1
