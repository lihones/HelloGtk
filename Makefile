CFLAGS =	-O2 -g -Wall -fmessage-length=0

CURR_PATH = $(shell pwd)
	
CXXSRCS = main.cpp \
	browser/app/Application.cpp \
	browser/af/AfContext.cpp \
	browser/af/AfProxy.cpp \
	browser/af/AfFactory.cpp \
	browser/af/AfWindow.cpp \
	browser/af/AfGc.cpp \
	browser/af/impl/gtk/AfGtkContext.cpp \
	browser/af/impl/gtk/AfGtkNative.cpp \
	browser/af/impl/gtk/AfGtkWindow.cpp \
	browser/af/impl/gtk/AfGtkGc.cpp

CSRCS = tutorial/start.c \
	tutorial/PtWidget.c \
	tutorial/listview.c \
	tutorial/controller.c \
	primary/xwindow/x_main.c

OBJS =

INCLUDES = -I$(CURR_PATH) -I$(CURR_PATH)/browser/af

LIBS = -lpthread \
	-ldl \
	-lX11

GTKFLAGS = `pkg-config --cflags --libs gtk+-2.0`

TARGET =	HelloGtk

$(TARGET): $(CXXSRCS) $(CSRCS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(CXXSRCS) $(CSRCS) $(INCLUDES) $(LIBS) $(GTKFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
