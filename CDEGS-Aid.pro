QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    src/main.cpp \
    lib/qcustomplot.cpp \
    ui/dialog_welcome.cpp \
    lib/pugixml.cpp \
    classes/project.cpp \
    classes/conductor.cpp \
    classes/settings.cpp \
    classes/viewsettings.cpp \
    classes/configuration.cpp \
    classes/building.cpp \
    classes/energization.cpp \
    classes/conductortype.cpp \
    classes/leadtype.cpp \
    classes/coating.cpp \
    classes/cabletype.cpp \
    util/apputils.cpp

HEADERS += \
    lib/qcustomplot.h \
    ui/dialog_welcome.h \
    lib/pugiconfig.hpp \
    lib/pugixml.hpp \
    classes/project.h \
    classes/conductor.h \
    classes/settings.h \
    classes/viewsettings.h \
    classes/configuration.h \
    classes/building.h \
    classes/energization.h \
    classes/conductortype.h \
    classes/leadtype.h \
    classes/coating.h \
    classes/cabletype.h \
    util/apputils.h

OTHER_FILES +=

FORMS += \
    ui/dialog_welcome.ui

RESOURCES += \
    ressources.qrc

QMAKE_CXXFLAGS += -std=c++11
