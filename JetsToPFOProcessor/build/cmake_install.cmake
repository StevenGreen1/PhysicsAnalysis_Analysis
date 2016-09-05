# Install script for directory: /var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJetsToPFOs.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJetsToPFOs.so.0.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJetsToPFOs.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "/var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Marlin/v01-08/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/lcio/v02-07/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/gear/v01-05/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/CLHEP/2.1.4.1/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/ilcutil/v01-02-01/lib")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "/var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor/build/lib/libJetsToPFOs.so.0.1.0"
    "/var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor/build/lib/libJetsToPFOs.so.0.1"
    "/var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor/build/lib/libJetsToPFOs.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJetsToPFOs.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJetsToPFOs.so.0.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJetsToPFOs.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Marlin/v01-08/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/lcio/v02-07/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/gear/v01-05/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/CLHEP/2.1.4.1/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/ilcutil/v01-02-01/lib::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
           NEW_RPATH "/var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/Marlin/v01-08/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/lcio/v02-07/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/gear/v01-05/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-09/CLHEP/2.1.4.1/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/ilcutil/v01-02-01/lib")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/var/clus/usera/sg568/PhysicsAnalysis/Analysis/JetsToPFOProcessor/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
