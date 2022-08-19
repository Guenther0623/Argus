INCLUDEPATH += /usr/local/include/opencv4/
QT 			+= widgets core gui
LIBS 		+= -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_tracking

QMAKE_CXXFLAGS 		+= -std=c++0x

greaterThan(QT_MAJOR_VERSION, 5) : QT += widgets

TARGET = Argus
TEMPLATE += app

SOURCES += \
	main.cpp \
	argus.cpp \
	eyeofargus.cpp \
	mindofargus.cpp \
	qargusslider.cpp \
	qstatewatcher.cpp \
	headofargus.cpp \
	qargusbutton.cpp

HEADERS += \
	argus.h \
	eyeofargus.h \
	mindofargus.h \
	qargusslider.h \
	qstatewatcher.h \
	headofargus.h \
	qargusbutton.h
