########################################################
# cmake file for building PandoraAnalysis
# @author Jan Engels, DESY
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
########################################################

# project name
PROJECT( AnalysisProcessor )

# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 0 )
SET( ${PROJECT_NAME}_VERSION_MINOR 0 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )

### DEPENDENCIES ############################################################

FIND_PACKAGE( ILCUTIL COMPONENTS ILCSOFT_CMAKE_MODULES REQUIRED )

# load default settings from ILCSOFT_CMAKE_MODULES
INCLUDE( ilcsoft_default_settings )

FIND_PACKAGE( ROOT REQUIRED )
FIND_PACKAGE( Marlin 1.0 REQUIRED )
FIND_PACKAGE( MarlinUtil REQUIRED )
FIND_PACKAGE( LCIO REQUIRED )

FOREACH( pkg ROOT Marlin MarlinUtil LCIO )
    IF( ${pkg}_FOUND )
        INCLUDE_DIRECTORIES( ${${pkg}_INCLUDE_DIRS} )
        LINK_LIBRARIES( ${${pkg}_LIBRARIES} ) ### /afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-05/root/5.34.10/lib/libMinuit.so )
        ADD_DEFINITIONS ( ${${pkg}_DEFINITIONS} )
    ENDIF()
ENDFOREACH()

INCLUDE_DIRECTORIES(BEFORE ./include ) # use BEFORE to fix problem on mac osx (case insensitive filesystem)


### SOURCE ##################################################################

#include directories
INCLUDE_DIRECTORIES( ./include )
INSTALL_DIRECTORY( ./include DESTINATION . FILES_MATCHING PATTERN "*.h" )

AUX_SOURCE_DIRECTORY( ./src AnalysisProcessor_SRCS )

### LIBRARY #################################################################

# add library
ADD_SHARED_LIBRARY( AnalysisProcessor ${AnalysisProcessor_SRCS} )

### INSTALL #################################################################

# install library
INSTALL_SHARED_LIBRARY( AnalysisProcessor DESTINATION lib )

# install header files
INSTALL_DIRECTORY( ./include DESTINATION . )

# display some variables and write them to cache
DISPLAY_STD_VARIABLES()

### LIBRARY AND TOOLS #######################################################
#AUX_SOURCE_DIRECTORY( ./src AnalysisProcessor_SRCS )

#ADD_SHARED_LIBRARY( AnalysisProcessor ${AnalysisProcessor_SRCS} )

# install library
#INSTALL_SHARED_LIBRARY( AnalysisProcessor DESTINATION lib )

#INSTALL( TARGETS AnalysisProcessor DESTINATION bin PERMISSIONS
#    OWNER_READ OWNER_WRITE OWNER_EXECUTE
#    GROUP_READ GROUP_EXECUTE
#    WORLD_READ WORLD_EXECUTE )

