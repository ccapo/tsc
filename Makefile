SRCDIR = src
INCDIR = include
LFLAGS = -Llib/i386 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=lib/i386
#LFLAGS = -Llib/x86_64 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=lib/x86_64
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
