
GPP=g++ -Wall -std=c++17
#LAUDIO=../libportaudio.a -lasound -ljack -pthread
#LMAD=../libmad/*.o 
#LPIXTERMLIBS=-pthread -lgdk_pixbuf_xlib-2.0 -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfontconfig -lfreetype  -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfontconfig -lfreetype -lX11
#LPIXTERM=-L ../../PixelTerm -lPixelTerm $(LPIXTERMLIBS)
IRPI_WS281X= ../rpi_ws281x
LRPI_WS281X= dma.o mailbox.o pcm.o pwm.o rpihw.o ws2811.o
INCLUDE= $(IRPI_WS281X)
LIBS= -lpthread -lm
OBJS= $(LRPI_WS281X:%.o=$(IRPI_WS281X)/%.o)
CFLAGS= $(INCLUDE:%=-I %) -Wno-psabi -o3 #-I ../libmad/ -I ../../PixelTerm

all: program

run: delprogram program
	sudo ./program

program: main.o LEDController.o Globals.o
	$(GPP) $(CFLAGS) $^ $(OBJS) $(LIBS) $(LPIXTERM) -o $@
	
main.o: main.cpp LEDController.h Globals.h
	$(GPP) $(CFLAGS) $< -c -o $@

LEDController.o: LEDController.cpp LEDController.h Globals.h
	$(GPP) $(CFLAGS) $< -c -o $@ 

Globals.o: Globals.cpp Globals.h
	$(GPP) $(CFLAGS) $< -c -o $@

force: clean all

delprogram:
	rm program -f

clean: delprogram 
	rm *.o -f
