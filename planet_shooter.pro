TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "D:/SFML-2.5.1/include"

SOURCES += \
	background.cpp \
	bullet.cpp \
	button.cpp \
	functions.cpp \
	main.cpp \
	menu.cpp \
	platform.cpp \
	player.cpp

LIBS += -L"D:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
	background.h \
	bullet.h \
	button.h \
	functions.h \
	menu.h \
	platform.h \
	player.h
