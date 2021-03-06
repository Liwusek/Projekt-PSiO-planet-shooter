TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "D:/SFML-2.5.1/include"

SOURCES += \
	background.cpp \
	bonus.cpp \
	bullet.cpp \
	main.cpp \
	platform.cpp \
	player.cpp \
	text.cpp

LIBS += -L"D:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
	background.h \
	bonus.h \
	bullet.h \
	platform.h \
	player.h \
	text.h
