QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    src/main.cpp \
    qcustomplot.cpp \
    ui/dialog_welcome.cpp \
    pugixml.cpp \
    classes/project.cpp \
    classes/conductor.cpp \
    classes/saveutils.cpp \
    classes/settings.cpp \
    classes/viewsettings.cpp \
    classes/configuration.cpp \
    classes/building.cpp

HEADERS += \
    qcustomplot.h \
    ui/dialog_welcome.h \
    pugiconfig.hpp \
    pugixml.hpp \
    classes/project.h \
    classes/conductor.h \
    classes/saveutils.h \
    classes/settings.h \
    classes/viewsettings.h \
    classes/configuration.h \
    classes/building.h

OTHER_FILES +=

FORMS += \
    ui/dialog_welcome.ui

RESOURCES += \
    ressources.qrc

QMAKE_CXXFLAGS += -std=c++11
