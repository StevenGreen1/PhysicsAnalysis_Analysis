export ILCSOFT=/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02


#--------------------------------------------------------------------------------
#     LCCD
#--------------------------------------------------------------------------------
export LCCD="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/lccd/v01-02"


#--------------------------------------------------------------------------------
#     CondDBMySQL
#--------------------------------------------------------------------------------
export COND_DB_DEBUGLOG="/dev/stdout"
export CondDBMySQL="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/CondDBMySQL/CondDBMySQL_ILC-0-9-5"
export LD_LIBRARY_PATH="$CondDBMySQL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCIO
#--------------------------------------------------------------------------------
export LCIO="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/lcio/v02-03-03"
export PATH="$LCIO/tools:$LCIO/bin:$PATH"
export LD_LIBRARY_PATH="$LCIO/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CLHEP
#--------------------------------------------------------------------------------
export CLHEP="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/CLHEP/2.1.1.0"
export CLHEP_BASE_DIR="$CLHEP"
export CLHEP_INCLUDE_DIR="$CLHEP/include"
export PATH="$CLHEP_BASE_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$CLHEP_BASE_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     ROOT
#--------------------------------------------------------------------------------
export ROOTSYS="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/root/5.28.00f"
export PATH="$ROOTSYS/bin:$PATH"
export LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CMake
#--------------------------------------------------------------------------------
export PATH="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/CMake/2.8.5/bin:$PATH"


#--------------------------------------------------------------------------------
#     ILCUTIL
#--------------------------------------------------------------------------------
export ilcutil="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/ilcutil/v01-00"
export LD_LIBRARY_PATH="$ilcutil/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Marlin
#--------------------------------------------------------------------------------
export MARLIN="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/Marlin/v01-04"
export PATH="$MARLIN/bin:$PATH"
export MARLIN_DLL="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/MarlinReco/v01-06/lib/libMarlinReco.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/PandoraAnalysis/v00-04/lib/libPandoraAnalysis.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/MarlinPandora/v00-09-02/lib/libMarlinPandora.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/LCFIVertex/v00-06-01/lib/libLCFIVertex.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/CEDViewer/v01-06-01/lib/libCEDViewer.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/Overlay/v00-13/lib/libOverlay.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/FastJetClustering/v00-02/lib/libFastJetClustering.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/MarlinFastJet/v00-01/lib/libMarlinFastJet.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/LCTuple/v01-01/lib/libLCTuple.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/MarlinKinfit/v00-01-02/lib/libMarlinKinfit.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/MarlinTrkProcessors/v01-09/lib/libMarlinTrkProcessors.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/Clupatra/v00-09-01/lib/libClupatra.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/LCFIPlus/v00-05-02/lib/libLCFIPlus.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/ForwardTracking/v01-07/lib/libForwardTracking.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/MarlinTPC/v00-11/lib/libMarlinTPC.so:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/Garlic/v2.10.1/lib/libGarlic.so:$MARLIN_DLL"


#--------------------------------------------------------------------------------
#     RAIDA
#--------------------------------------------------------------------------------
export RAIDA_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/RAIDA/v01-06-02"
export PATH="$RAIDA_HOME/bin:$PATH"


#--------------------------------------------------------------------------------
#     GEAR
#--------------------------------------------------------------------------------
export GEAR="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/gear/v01-02-02"
export PATH="$GEAR/tools:$GEAR/bin:$PATH"
export LD_LIBRARY_PATH="$GEAR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GSL
#--------------------------------------------------------------------------------
export GSL_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/gsl/1.14"
export PATH="$GSL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$GSL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CED
#--------------------------------------------------------------------------------
export PATH="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/CED/v01-07/bin:$PATH"


#--------------------------------------------------------------------------------
#     Mokka
#--------------------------------------------------------------------------------
export MOKKA="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/Mokka/mokka-08-00-03"
export PATH="$MOKKA/bin:$PATH"


#--------------------------------------------------------------------------------
#     Geant4
#--------------------------------------------------------------------------------
export G4INSTALL="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/geant4/9.5.p02"
export G4ENV_INIT="$G4INSTALL/bin/geant4.sh"
export G4SYSTEM="Linux-g++"


#--------------------------------------------------------------------------------
#     QT
#--------------------------------------------------------------------------------
export QTDIR="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/QT/4.7.4"
export QMAKESPEC="$QTDIR/mkspecs/linux-g++"
export PATH="$QTDIR/bin:$PATH"
export LD_LIBRARY_PATH="$QTDIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MySQL
#--------------------------------------------------------------------------------
export MYSQL_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/mysql/5.0.45"
export MYSQL_LIBDIR="$MYSQL_HOME/lib64/mysql"
export MYSQL_PATH="$MYSQL_HOME"
export MYSQL="$MYSQL_HOME"
export PATH="$MYSQL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$MYSQL_HOME/lib64/mysql:$MYSQL_HOME/lib64:$MYSQL_HOME/lib/mysql:$MYSQL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CERNLIB
#--------------------------------------------------------------------------------
export CERN_ROOT="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/cernlib/2006"
export CERN="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/cernlib"
export CERN_LEVEL="2006"
export CVSCOSRC="$CERN_ROOT/src"
export PATH="$CERN_ROOT/bin:$PATH"


#--------------------------------------------------------------------------------
#     CEDViewer
#--------------------------------------------------------------------------------
export PATH="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/CEDViewer/v01-06-01/bin:$PATH"


#--------------------------------------------------------------------------------
#     FastJet
#--------------------------------------------------------------------------------
export FastJet_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/FastJet/2.4.2"
export PATH="$FastJet_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$FastJet_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     KalTest
#--------------------------------------------------------------------------------
export KALTEST="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/KalTest/v01-05-02"
export LD_LIBRARY_PATH="$KALTEST/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MarlinTPC
#--------------------------------------------------------------------------------
export MARLINTPC="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/MarlinTPC/v00-11"
export PATH="$MARLINTPC/bin:$PATH"


#--------------------------------------------------------------------------------
#     Druid
#--------------------------------------------------------------------------------
export DRUID="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/Druid/1.8"
export PATH="$DRUID/bin:$PATH"


#--------------------------------------------------------------------------------
#     Java
#--------------------------------------------------------------------------------
export JAVA_HOME="/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-16-02/java/1.6.0"
export JDK_HOME="$JAVA_HOME"
export PATH="$JDK_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$JDK_HOME/jre/lib/i386:$JDK_HOME/jre/lib/i386/client:$LD_LIBRARY_PATH"

# --- source GEANT4 INIT script ---
test -r ${G4ENV_INIT} && { cd $(dirname ${G4ENV_INIT}) ; . ./$(basename ${G4ENV_INIT}) ; cd $OLDPWD ; }
