QT += widgets

LIBS += -lws2_32

# Define your sources
SOURCES += \
    AExercitiu.cpp \
    CExercitiuBlocuri.cpp \
    CExercitiuGrila.cpp \
    CExercitiuText.cpp \
    CLectie.cpp \
    ILectie.cpp \
    ServerConnection.cpp \
    ServerMessageContainer.cpp \
    StartMenuWindow.cpp \
    climbaj.cpp \
    iexercitiu.cpp \
    main.cpp \
    mainwindow.cpp \
    TCPClient.cpp \
    Utils.cpp #\
    payment.cpp
    startmenuwindow.cpp
    startmenuwindow.cpp

    #ServerConnection.cpp

HEADERS += \
    AExercitiu.h \
    CExercitiuBlocuri.h \
    CExercitiuGrila.h \
    CExercitiuText.h \
    CLectie.h \
    ILectie.h \
    ServerMessageContainer.h \
    climbaj.h \
    iexercitiu.h \
    mainwindow.h \
    TCPClient.h \
    Utils.h \
    ServerConnection.h \
    startmenuwindow.h

FORMS += \
    mainwindow.ui \
    startmenuwindow.ui

RESOURCES += \
    images.qrc

# Define your target
#TARGET = SimpleLogin
TARGET = CODE_BUDDY

# Set compiler options
CONFIG += c++17

# Define the target properties
macx: {
    #QMAKE_MACOSX_BUNDLE_GUI_IDENTIFIER = com.example.SimpleLogin
    QMAKE_MACOSX_BUNDLE_GUI_IDENTIFIER = com.example.CODE_BUDDY
    QMAKE_MACOSX_BUNDLE = true
    QMAKE_MACOSX_BUNDLE_VERSION = 0.1
    QMAKE_MACOSX_BUNDLE_SHORT_VERSION_STRING = 0.1
}

win32 {
    CONFIG += console
}

# Specify install paths
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows
INSTALLS += target
