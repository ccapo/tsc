SRCDIR = src
INCDIR = include
#LFLAGS = -Llib -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=lib
LFLAGS = -Llib64 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=lib64
CPP = g++
CFLAGS = -O3 -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex
#CFLAGS = -O3 -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND
#CFLAGS = -O0 -g -Wall -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND

.SUFFIXES: .o .hpp .cpp

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

OBJS = $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp))

all: tsc

tsc: $(SRCDIR) $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS)
	rm -f $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f tsc
