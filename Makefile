CFLAGS =	-O2 -g -Wall -fmessage-length=0

CSRCS = main.c \
	tutorial/start.c \
	tutorial/PtWidget.c \
	net/HttpClient.c

OBJS =

LIBS = -lpthread \
	-ldl

GTKFLAGS = `pkg-config --cflags --libs gtk+-2.0`

TARGET =	HelloGtk

$(TARGET): $(CSRCS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $(TARGET) $(CSRCS) $(LIBS) $(GTKFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
