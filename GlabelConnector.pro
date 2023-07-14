
QT += core gui
QT += network
QT += printsupport
QT += xml
QT += svg
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#TEMPLATE = subdirs
#TARGET = glabels_conn
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    apiclient.cpp \
    dialogprint.cpp \
    glabelsqt.cpp \
    importdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mergejson.cpp \
    printtask.cpp \
    productsmodel.cpp \
    raster.cpp

HEADERS += \
    apiclient.h \
    dialogprint.h \
    glabelsqt.h \
    importdialog.h \
    mainwindow.h \
    mergejson.h \
    printtask.h \
    productsmodel.h \
    raster.h

FORMS += \
    dialogprint.ui \
    importdialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    GlabelConnector_es_419.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    glabels-qt/glabels/cursors/32x32/cursor_barcode.png \
    glabels-qt/glabels/cursors/32x32/cursor_box.png \
    glabels-qt/glabels/cursors/32x32/cursor_ellipse.png \
    glabels-qt/glabels/cursors/32x32/cursor_image.png \
    glabels-qt/glabels/cursors/32x32/cursor_line.png \
    glabels-qt/glabels/cursors/32x32/cursor_text.png \
    glabels-qt/glabels/images/TemplateDesigner/ex-1layout.png \
    glabels-qt/glabels/images/TemplateDesigner/ex-2layouts.png \
    glabels-qt/glabels/images/TemplateDesigner/ex-cd-size.png \
    glabels-qt/glabels/images/TemplateDesigner/ex-ellipse-size.png \
    glabels-qt/glabels/images/TemplateDesigner/ex-rect-size.png \
    glabels-qt/glabels/images/TemplateDesigner/ex-round-size.png \
    glabels-qt/glabels/images/TemplateDesigner/wizard-banner.png \
    glabels-qt/glabels/images/checkerboard.png \
    glabels-qt/glabels/images/glabels-label-designer.png \
    glabels-qt/glabels/images/glabels-label-designer.svg \
    glabels-qt/glabels/images/glabels-logo.png \
    glabels-qt/glabels/windows-icon/build-windows-icon.sh \
    glabels-qt/glabels/windows-icon/glabels.ico \
    sticker32x25.glabels \
    templates/CMakeLists.txt \
    templates/LICENSE \
    templates/ascom-iso-templates.xml \
    templates/avery-iso-templates.xml \
    templates/avery-other-templates.xml \
    templates/avery-us-templates.xml \
    templates/begalabel-templates.xml \
    templates/brother-other-templates.xml \
    templates/cablelabel-templates.xml \
    templates/canon-other-templates.xml \
    templates/categories.xml \
    templates/databecker-iso-templates.xml \
    templates/dataline-iso-templates.xml \
    templates/decadry-iso-templates.xml \
    templates/desmat-templates.xml \
    templates/dymo-other-templates.xml \
    templates/endisch-templates.xml \
    templates/felga-templates.xml \
    templates/geha-iso-templates.xml \
    templates/glabels-3.0.dtd \
    templates/glabels-4.0.dtd \
    templates/hama-iso-templates.xml \
    templates/herma-iso-templates.xml \
    templates/hisago-templates.xml \
    templates/igepa-templates.xml \
    templates/jac-iso-templates.xml \
    templates/maco-us-templates.xml \
    templates/mayspies-templates.xml \
    templates/meritline-us-templates.xml \
    templates/microapp-templates.xml \
    templates/misc-iso-templates.xml \
    templates/misc-other-templates.xml \
    templates/misc-us-templates.xml \
    templates/online-templates.xml \
    templates/paper-sizes.xml \
    templates/pearl-iso-templates.xml \
    templates/rayfilm-templates.xml \
    templates/sheetlabels-us-templates.xml \
    templates/uline-us-templates.xml \
    templates/vendors.xml \
    templates/worldlabel-us-templates.xml \
    templates/zweckform-iso-templates.xml

RESOURCES += \
    res.qrc \
    res.qrc
#libs qt labels
unix:!macx: LIBS += -L$$PWD/glabels-qt/build/model/ -lModel

INCLUDEPATH += $$PWD/glabels-qt
DEPENDPATH += $$PWD/glabels-qt

INCLUDEPATH += $$PWD/glabels-qt/build
DEPENDPATH += $$PWD/glabels-qt/build

unix:!macx: LIBS += -lz
unix:!macx: LIBS += -lBarcode

unix:!macx: PRE_TARGETDEPS += $$PWD/glabels-qt/build/backends/barcode/libBarcode.a
unix:!macx: PRE_TARGETDEPS += $$PWD/glabels-qt/build/model/libModel.a

unix:!macx: LIBS += -L$$PWD/glabels-qt/build/backends/merge/ -lMerge


INCLUDEPATH += glabels-qt/backends
DEPENDPATH += glabels-qt/backends

unix:!macx: PRE_TARGETDEPS += $$PWD/glabels-qt/build/backends/merge/libMerge.a
unix:!macx: LIBS += -L$$PWD/glabels-qt/build/backends/barcode/ -lBarcode

INCLUDEPATH += $PWD/glabels-qt/backends
DEPENDPATH += glabels-qt/backends

unix:!macx: PRE_TARGETDEPS += $$PWD/glabels-qt/build/backends/barcode/libBarcode.a
unix:!macx: LIBS += -L$$PWD/glabels-qt/build/glbarcode/ -lglbarcode

INCLUDEPATH += $$PWD/glbarcode
DEPENDPATH += $$PWD/glbarcode

unix:!macx: PRE_TARGETDEPS += $$PWD/glabels-qt/build/glbarcode/libglbarcode.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../glabels-qt/bin/model/ -lModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../glabels-qt/bin/model/ -lModeld

INCLUDEPATH += $$PWD/../glabels-qt/model
DEPENDPATH += $$PWD/../glabels-qt/model

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../glabels-qt/bin/model/libModel.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../glabels-qt/bin/model/libModeld.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../glabels-qt/bin/model/Model.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../glabels-qt/bin/model/Modeld.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../glabels-qt/bin/backends/merge/ -lMerge
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../glabels-qt/bin/backends/merge/ -lMerged

INCLUDEPATH += $$PWD/../glabels-qt/backends/merge
DEPENDPATH += $$PWD/../glabels-qt/backends/merge

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../glabels-qt/bin/backends/barcode/ -lBarcode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../glabels-qt/bin/backends/barcode/ -lBarcoded

INCLUDEPATH += $$PWD/../glabels-qt/bin/backends/barcode
DEPENDPATH += $$PWD/../glabels-qt/bin/backends/barcode

win32: LIBS += -L$$PWD/../glabels-qt/bin/glbarcode/ -lglbarcode

INCLUDEPATH += $$PWD/../glabels-qt/glbarcode
DEPENDPATH += $$PWD/../glabels-qt/glbarcode
DESTDIR = $$PWD/bin
win32 {

QMAKE_POST_LINK =  windeployqt $$shell_path($$DESTDIR/$${TARGET}.exe)
}
