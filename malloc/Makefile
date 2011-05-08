TARGETS = bench_malloc bench_vector
SUBDIRS = 
INCLUDES = 

all: $(TARGETS)
	for d in $(SUBDIRS); do \
		cd $$d && $(MAKE); \
	done

bench_malloc: bench_malloc.o
bench_vector: bench_vector.o

CXX = g++
CXXFLAGS = $(INCLUDES) -O2 -g -Wall -pedantic #-Werror
LDFLAGS = -lrt

%: %.o
	$(LINK.cc) $^ -o $@

%.o: %.cpp %.hpp
	$(COMPILE.cc) $(filter %.cpp,$<) -o $@

%.o: %.c %.h
	$(COMPILE.cc) $(filter %.c,$<) -o $@

%.hpp:
	

%.h:
	

clean:
	rm -f *.o
	for d in $(SUBDIRS); do \
		cd $$d && $(MAKE) clean; \
	done

distclean: clean
	rm -f $(TARGETS)
	for d in $(SUBDIRS); do \
		cd $$d && $(MAKE) distclean; \
	done
