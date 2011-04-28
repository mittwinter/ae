targets = bench bench-const bench-sf bench-std

all: $(targets)

bench: bench.o
bench-const: bench-const.o
bench-sf: bench-sf.o
bench-std: bench-std.o

CXX = g++
CXXFLAGS = -O2 -g -Wall -pedantic #-Werror
LDFLAGS = 

%: %.o
	$(LINK.cc) $^ -o $@

%.o: %.cpp %.hpp
	$(COMPILE.cc) $(filter %.cpp,$<) -o $@

%.hpp:
	

clean:
	rm -f *.o gui/*.o protocol/*.o protocol/generator/*.o protocol/parser/*.o server/*.o posix/*.o p2p/*.o

distclean: clean
	rm -f $(targets)
	( cd gui && $(MAKE) distclean )
	( cd server && $(MAKE) distclean )
