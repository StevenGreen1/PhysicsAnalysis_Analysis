#!/bin/bash

gcc_config_version=4.8.1
mpfr_config_version=3.1.2
gmp_config_version=5.1.1
LCGPLAT=x86_64-slc6-gcc48-opt
LCG_lib_name=lib64
LCG_arch=x86_64

LCG_contdir=/cvmfs/sft.cern.ch/lcg/external
LCG_gcc_home=${LCG_contdir}/gcc/${gcc_config_version}/${LCGPLAT}
LCG_mpfr_home=${LCG_contdir}/mpfr/${mpfr_config_version}/${LCGPLAT}
LCG_gmp_home=${LCG_contdir}/gmp/${gmp_config_version}/${LCGPLAT}

export PATH=${LCG_gcc_home}/bin:${PATH}
export COMPILER_PATH=${LCG_gcc_home}/lib/gcc/${LCG_arch}-unknown-linux-gnu/${gcc_config_version}

if [ ${LD_LIBRARY_PATH} ]
then
export LD_LIBRARY_PATH=${LCG_gcc_home}/${LCG_lib_name}:${LCG_mpfr_home}/lib:${LCG_gmp_home}/lib:${LD_LIBRARY_PATH}
else
export LD_LIBRARY_PATH=${LCG_gcc_home}/${LCG_lib_name}:${LCG_mpfr_home}/lib:${LCG_gmp_home}/lib
fi

export PATH=/cvmfs/sft.cern.ch/lcg/external/Python/2.7.4/x86_64-slc6-gcc48-opt/bin/:$PATH
export LD_LIBRARY_PATH=/cvmfs/sft.cern.ch/lcg/external/Python/2.7.4/x86_64-slc6-gcc48-opt/lib/:$LD_LIBRARY_PATH

source /usera/sg568/PhysicsAnalysis/Analysis/init_ilcsoft_cvmfs.sh 

/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin/PerfectAnalysis $1 $2 $3
