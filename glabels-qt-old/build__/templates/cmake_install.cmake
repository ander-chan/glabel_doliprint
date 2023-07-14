# Install script for directory: /home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glabels-qt/templates" TYPE FILE FILES
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/glabels-3.0.dtd"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/glabels-4.0.dtd"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glabels-qt/templates" TYPE FILE FILES
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/ascom-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/avery-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/avery-other-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/avery-us-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/begalabel-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/brother-other-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/cablelabel-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/canon-other-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/databecker-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/dataline-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/decadry-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/desmat-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/dymo-other-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/endisch-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/felga-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/geha-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/hama-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/herma-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/hisago-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/igepa-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/jac-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/maco-us-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/mayspies-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/meritline-us-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/microapp-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/misc-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/misc-other-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/misc-us-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/online-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/pearl-iso-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/rayfilm-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/sheetlabels-us-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/uline-us-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/worldlabel-us-templates.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/zweckform-iso-templates.xml"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glabels-qt/templates" TYPE FILE FILES
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/categories.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/paper-sizes.xml"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/templates/vendors.xml"
    )
endif()

