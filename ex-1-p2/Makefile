TARGETS = bench bench_tlsf
SUBDIRS = contrib/tlsf
INCLUDES = -I./contrib/tlsf/

all: $(TARGETS)
	for d in $(SUBDIRS); do \
		cd $$d && $(MAKE); \
	done

bench: bench.o \
	tlsf_util.o \
	contrib/tlsf/tlsf.o

bench_tlsf: bench_tlsf.o \
	tlsf_util.o \
	contrib/tlsf/tlsf.o

CXX = g++
CXXFLAGS = $(INCLUDES) -O2 -g -Wall -pedantic #-Werror
LDFLAGS = 

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
