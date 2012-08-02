SRCDIR = src
INCDIR = include
LIBDIR = lib
CPP = icpc
# Background music not uploaded, need to determine licensing permissions
CFLAGS = -xHOST -O3 -Wall -ip -ipo -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex -DNOSOUND
#CFLAGS = -O3 -Wall -I$(INCDIR)/tsc -I$(INCDIR)/tcod -I$(INCDIR)/fmodex
UPX = ./dependencies/upx-3.08/linux-i386/upx -qq
.SUFFIXES: .o .hpp .cpp

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

OBJS = $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp))

all: tsc

tsc: $(SRCDIR) $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o $@ -L$(LIBDIR) -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=$(LIBDIR)
	rm -f $(OBJS)
	$(UPX) $@

clean:
	rm -f tsc
