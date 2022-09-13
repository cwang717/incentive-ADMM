CC=gcc
CXX=g++
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=-lglog

IDIR =../include

ODIR=obj
LDIR =../lib

_DEPS = common.h network.h od.h path.h link.h solver.h vehicle.h util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o network.o od.o path.o link.o util.o solver.o vehicle.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

main: $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^  $(LDLIBS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~