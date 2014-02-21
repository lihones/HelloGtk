CFLAGS =	-O2 -g -Wall -fmessage-length=0

CURR_PATH = $(shell pwd)
	
CXXSRCS = main.cpp \
	browser/app/Application.cpp \
	browser/display/PtBitmap.cpp \
	browser/display/PtDisplay.cpp \
	browser/display/PtEvent.cpp \
	browser/display/PtFont.cpp \
	browser/display/PtGc.cpp \
	browser/display/PtWindow.cpp \
	browser/display/impl/BitmapImpl.cpp \
	browser/display/impl/DisplayImpl.cpp \
	browser/display/impl/EventImpl.cpp \
	browser/display/impl/FontImpl.cpp \
	browser/display/impl/GcImpl.cpp \
	browser/display/impl/WindowImpl.cpp \
	browser/platform/gtk/display/impl/GtkBitmapImpl.cpp \
	browser/platform/gtk/display/impl/GtkDisplayImpl.cpp \
	browser/platform/gtk/display/impl/GtkEventImpl.cpp \
	browser/platform/gtk/display/impl/GtkFontImpl.cpp \
	browser/platform/gtk/display/impl/GtkGcImpl.cpp \
	browser/platform/gtk/display/impl/GtkWindowImpl.cpp

CSRCS = tutorial/start.c \
	tutorial/PtWidget.c \
	tutorial/listview.c \
	tutorial/controller.c \
	primary/xwindow/x_main.c

OBJS =

INCLUDES = -I$(CURR_PATH)

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
