CAVEDIR = /usr/local/CAVE
CAVELIBDIR = $(CAVEDIR)/lib
CAVEINCDIR = $(CAVEDIR)/include
SNDINCDIR = /usr/local/CAVE/include
SNDLIBDIR = /usr/local/CAVE/lib

OPTorDEBUG = -O

CFLAGS = -I.. -I$(CAVEINCDIR) -I$(SNDINCDIR) $(OPTorDEBUG) \
		-DOPENGL -UIRISGL  -32
C++FLAGS = $(CFLAGS)
LFLAGS = $(OPTorDEBUG)

LIBS = -L.. -ldpf \
	-L$(CAVELIBDIR) -lpfcave_ogl \
	-L$(SNDLIBDIR) -lsnd \
	-lpfdu_ogl -lpfutil_ogl -lpf_ogl -lfpe \
	-lGL -lXi -lX11 -lm -limage




sound: sound.o ../libdpf.a
	$(C++) $(LFLAGS) sound.o -o sound $(LIBS)

wandsound: wandsound.o ../libdpf.a
	$(C++) $(LFLAGS) wandsound.o -o wandsound $(LIBS)

hermite: hermite.o ../libdpf.a
	$(C++) $(LFLAGS) hermite.o -o hermite $(LIBS)

