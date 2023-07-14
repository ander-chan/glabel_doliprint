# Install script for directory: /home/ander/Descargas/glabels-qt-glabels-3.99-master564/translations

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glabels-qt/translations" TYPE FILE FILES "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_C.qm")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glabels-qt/translations" TYPE FILE FILES "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_C.qm")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glabels-qt/translations" TYPE FILE FILES
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_ar.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_bs.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_ca.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_cs.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_da.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_de.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_el.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_en_GB.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_eo.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_es.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_fi.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_fr.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_gl.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_hu.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_id.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_it.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_ja.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_ko.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_lv.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_nb.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_nl.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_oc.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_pt_BR.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_pt.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_ro.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_ru.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_sk.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_sl.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_sr@latin.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_sr.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_sv.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_tr.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_uk.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_zh_CN.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_zh_HK.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/glabels_zh_TW.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_ar.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_bs.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_ca.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_cs.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_da.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_de.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_el.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_en_GB.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_eo.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_es.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_fi.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_fr.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_gl.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_hu.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_id.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_it.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_ja.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_ko.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_lv.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_nb.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_nl.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_oc.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_pt_BR.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_pt.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_ro.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_ru.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_sk.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_sl.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_sr@latin.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_sr.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_sv.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_tr.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_uk.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_zh_CN.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_zh_HK.qm"
    "/home/ander/Descargas/glabels-qt-glabels-3.99-master564/build/translations/templates_zh_TW.qm"
    )
endif()

