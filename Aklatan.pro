QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    common/dbmanager/dbmanager.cpp \
    common/search/searchwindow.cpp \
    common/settings/settingsmanager.cpp \
    common/setup/setupmanager.cpp \
    library-window/logbook/logbook.cpp \
    library-window/loginform/loginform.cpp \
    library-window/mainlibrarywindow/mainlibrarywindow.cpp \
    main.cpp \
    user-window/userlogin/userlogin.cpp \
    user-window/userwindow/userwindow.cpp

HEADERS += \
    common/dbmanager/dbmanager.h \
    common/search/searchwindow.h \
    common/settings/settingsmanager.h \
    common/setup/setupmanager.h \
    library-window/logbook/logbook.h \
    library-window/loginform/loginform.h \
    library-window/mainlibrarywindow/mainlibrarywindow.h \
    user-window/userlogin/userlogin.h \
    user-window/userwindow/userwindow.h

FORMS += \
    common/search/searchwindow.ui \
    common/settings/settingsmanager.ui \
    common/setup/setupmanager.ui \
    library-window/logbook/logbook.ui \
    library-window/loginform/loginform.ui \
    library-window/mainlibrarywindow/mainlibrarywindow.ui \
    user-window/userlogin/userlogin.ui \
    user-window/userwindow/userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
