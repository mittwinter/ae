TARGETS = tlsf.o
SUBDIRS = 
INCLUDES = 

all: $(TARGETS)
	for d in $(SUBDIRS); do \
		cd $$d && $(MAKE); \
	done

CXX = g++
CXXFLAGS = $(INCLUDES) -O2 -g -Wall -pedantic -Wextra -Wall \
           -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wno-long-long -Wstrict-aliasing=2 \
           -DTLSF_USE_LOCKS=0 -DUSE_MMAP=0 -DUSE_SBRK=0 #-Werror
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
