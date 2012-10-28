SRCDIR = src
INCDIR = include
CPP = g++

CFLAGS = -O3 -ffinite-math-only -finline-small-functions -fmove-loop-invariants -foptimize-register-move -foptimize-sibling-calls -freorder-functions -funroll-all-loops -fdata-sections -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex
#CFLAGS = -O3 -ffinite-math-only -finline-small-functions -fmove-loop-invariants -foptimize-register-move -foptimize-sibling-calls -freorder-functions -funroll-all-loops -fdata-sections -w -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND
#CFLAGS = -O0 -g -Wall -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND

# Determine if operating system is 32-bit or 64-bit
TARGET_OS = $(shell uname -m)

# These are the definitions specific to 64-bit systems
ifeq ($(TARGET_OS),x86_64)

	LFLAGS = -Llib/x86_64 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=lib/x86_64

else

	LFLAGS = -Llib/i386 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=lib/i386

endif

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
