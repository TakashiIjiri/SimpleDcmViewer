# Install script for directory: C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dcmtk/dcmdata/libi2d" TYPE FILE FILES
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d/i2d.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d/i2dbmps.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d/i2dimgs.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d/i2djpgs.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d/i2doutpl.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d/i2dplnsc.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d/i2dplsc.h"
    "C:/Users/takashi/Desktop/dcmtk-3.6.0/dcmdata/include/dcmtk/dcmdata/libi2d/i2dplvlp.h"
    )
endif()

