QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

SOURCES += \
    src/main.cpp \
    qcustomplot.cpp \
    ui/dialog_welcome.cpp

HEADERS += \
    qcustomplot.h \
    ui/dialog_welcome.h

OTHER_FILES += \
    res/icon_nouveau.png \
    res/icon_ouvrir.png \
    res/icon_quit.png

FORMS += \
    ui/dialog_welcome.ui

RESOURCES += \
    ressources.qrc
