CXX ?= g++
PROGRAM = picket
CXXFILES = $(wildcard src/*.cpp)
OBJS = $(CXXFILES:.cpp=.o)
CXXFLAGS = `pkg-config --cflags gtkmm-3.0`
LIBS = `pkg-config --libs gtkmm-3.0`
GLADES = $(wildcard *.glade)
GLADES_HOME = $(addprefix $(HOME)/,$(GLADES))

all: $(PROGRAM)
	cp $(GLADES) $(HOME)
	mkdir -p $(HOME)/.picket
	cp formats $(HOME)/.picket

%.o: %.cpp
	$(CXX) $^ -o $@ -I $(*D) -c $(CXXFLAGS)

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS) $(LIBS)

debug: CXXFLAGS += -g
debug: clean all

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(GLADES_HOME)

.PHONY: install
install: $(PROGRAM)
	cp $(PROGRAM) /usr/bin
