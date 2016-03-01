# Install script for directory: C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/DCMTK")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dcmtk/ofstd" TYPE FILE FILES
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofalgo.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofaptr.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofbmanip.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofcast.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofcmdln.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofconapp.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofcond.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofconfig.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofconsol.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofcrc32.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofdate.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofdatime.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofdefine.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/offile.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/offname.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofglobal.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/oflist.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofmap.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofoset.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofset.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofsetit.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofstack.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofstd.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofstdinc.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofstream.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofstring.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofthread.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/oftime.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/oftimer.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/oftypes.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofuoset.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/ofstd/include/dcmtk/ofstd/ofvector.h"
    )
endif()

