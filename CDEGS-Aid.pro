QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    src/main.cpp \
    qcustomplot.cpp \
    ui/dialog_welcome.cpp \
    pugixml.cpp \
    src/xml_test.cpp \
    classes/project.cpp \
    classes/conductor.cpp

HEADERS += \
    qcustomplot.h \
    ui/dialog_welcome.h \
    pugiconfig.hpp \
    pugixml.hpp \
    classes/project.h \
    classes/conductor.h

OTHER_FILES +=

FORMS += \
    ui/dialog_welcome.ui

RESOURCES += \
    ressources.qrc

QMAKE_CXXFLAGS += -std=c++11
