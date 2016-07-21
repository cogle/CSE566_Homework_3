
CXX        = mpic++

LIBS      = -lX11 -lm

CFLAGS    = 
LDFLAGS   = -L/usr/X11R6/lib $(LIBS)
FLAGS     = -O2 -fopenmp

PROGRAM   = a.out			# name of the binary
SRCS      = Gal.cpp derivs.cpp diffeq.cpp modeldata.cpp point.cpp derivs_client.cpp

default: all

all: $(PROGRAM) 

$(PROGRAM): $(SRCS)
	$(CXX) $(FLAGS) $(SRCS) $(CFLAGS) $(LDFLAGS)

openmpi:
	mpic++ $(SRCS) $(CFLAGS) $(LDFLAGS) -o a2.out

clean:
	/bin/rm -f $(PROGRAM)
