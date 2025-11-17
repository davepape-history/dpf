CAVEDIR = /usr/local/CAVE
CAVELIBDIR = $(CAVEDIR)/lib
CAVEINCDIR = $(CAVEDIR)/include
SNDINCDIR = /usr/local/audio
SNDLIBDIR = /usr/local/audio

OPTorDEBUG = -O

CFLAGS = -I$(CAVEINCDIR) -I$(SNDINCDIR) $(OPTorDEBUG) \
		-DOPENGL -UIRISGL  -o32  -mips2
C++FLAGS = $(CFLAGS)
LFLAGS = $(OPTorDEBUG) -o32

LIBS = -L$(CAVELIBDIR) -lpfcave_ogl \
	-lpfdu -lpfutil -lpf -lfpe \
	-L$(SNDLIBDIR) -lsnd \
	-lGL -lGLU -lXi -lX11 -lm -limage


LIBOBJS = dpfGrabber.o dpfSpriteGroup.o dpfAvatar.o \
	dpfCubicCurve.o dpfHermiteCurve.o dpfBezierCurve.o \
	dpfBsplineCurve.o dpfCatmullRomCurve.o \
	dpfVolume.o \
	dpfBox.o dpfSphere.o dpfCylinder.o dpfPoint.o dpfInfiniteVolume.o \
	dpfSound.o dpfLocalSound.o dpfStack.o


libdpf.a: $(LIBOBJS)
	rm -f libdpf.a
	ar ru libdpf.a $(LIBOBJS)

depend:
	makedepend $(CFLAGS) *.cxx


demoHermite: demoHermite.o libdpf.a
	$(C++) $(LFLAGS) demoHermite.o -o demoHermite -L. -ldpf \
		-L/usr/local/CAVE/lib -lcave_ogl -lGL -lX11 -lXi -lpf -lm -lfpe



# DO NOT DELETE

