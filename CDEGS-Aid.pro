QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    src/main.cpp \
    lib/qcustomplot.cpp \
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
    util/apputils.cpp \
    classes/component.cpp \
    ui/cdegs_main.cpp \
    ui/project_widget.cpp \
    ui/configuration_widget.cpp \
    ui/project_tab_widget.cpp \
    ui/style_dialog.cpp \
    ui/configuration_chooser_dialog.cpp \
    ui/multi_conductor_dialog.cpp

HEADERS += \
    lib/qcustomplot.h \
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
    util/apputils.h \
    classes/component.h \
    ui/cdegs_main.h \
    ui/project_widget.h \
    ui/configuration_widget.h \
    ui/project_tab_widget.h \
    classes/structs.h \
    ui/style_dialog.h \
    ui/configuration_chooser_dialog.h \
    ui/multi_conductor_dialog.h

OTHER_FILES +=

FORMS += \
    ui/cdegs_main.ui \
    ui/project_widget.ui \
    ui/configuration_widget.ui \
    ui/project_tab_widget.ui \
    ui/style_dialog.ui \
    ui/configuration_chooser_dialog.ui \
    ui/multi_conductor_dialog.ui

RESOURCES += \
    ressources.qrc

QMAKE_CXXFLAGS += -std=c++11
