
QT 			+= widgets core gui
LIBS 			+= -lserial -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio
QMAKE_CXXFLAGS 		+= -std=c++0x

greaterThan(QT_MAJOR_VERSION, 5) : QT += widgets

TARGET = Argus
TEMPLATE += app

SOURCES += \
	main.cpp \
	argus.cpp \
	eyeofargus.cpp \
	mindofargus.cpp

HEADERS += \
	argus.h \
	eyeofargus.h \
	mindofargus.h
