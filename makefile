# 
# 

SISTEMA_OPERATIVO = $(shell uname -s)

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

CXX = g++
CXXFLAGS = -g $(ROOTCFLAGS)
DEPEND = $(CXX) -MM
DEL = rm -rf

STATIC := -static
LDFLAGS =  -O4 $(ROOTLIBS) -lMinuit $(LIBS)

SOURCES           := $(wildcard *.cc)
OBJECTS           := $(SOURCES:.cc=.o)
EXESRC            := $(wildcard *.cpp)
EXECUTABLES       := $(EXESRC:.cpp=.exe)
DEPS              := $(SOURCES:.cc=.ccd)
DEPEXE		  := $(EXESRC:.cpp=.d)
all: $(EXECUTABLES)

%.exe : %.cpp $(DEPS) $(OBJECTS) %.d   
	${CXX} $(CXXFLAGS) $< $(OBJECTS) $(LDFLAGS) -o $@ 

%.o : %.cc %.ccd
	@echo .o
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.ccd : %.cc
	@echo .xxd
	$(DEPEND) $(CXXFLAGS) $< > $@

%.d : 	%.cpp
	@echo .d 
	$(DEPEND) $(CXXFLAGS) $< > $@
	sed s/.o:/.exe:/g $@ >tmp.sed
	mv tmp.sed $@

clean: 	
	@echo cleaning...
	$(DEL) *.o
	$(DEL) *.d 
	$(DEL) *.ccd
	$(DEL) *.exe

try:
	@echo $@
	@echo $(EXECUTABLES)
	@echo CXXFLAGS
	@echo $(CXXFLAGS)
	@echo LIBS
	@echo $(LIBS)

include $(DEPS)
include $(DEPEXE)


