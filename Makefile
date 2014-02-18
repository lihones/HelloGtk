CFLAGS =	-O2 -g -Wall -fmessage-length=0

CSRCS = main.c \
	tutorial/start.c \
	tutorial/PtWidget.c \
	tutorial/listview.c \
	tutorial/controller.c \
	primary/xwindow/x_main.c

OBJS =

LIBS = -lpthread \
	-ldl \
	-lX11

GTKFLAGS = `pkg-config --cflags --libs gtk+-2.0`

TARGET =	HelloGtk

$(TARGET): $(CSRCS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $(TARGET) $(CSRCS) $(LIBS) $(GTKFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
