CXX ?= g++
PROGRAM = picket
CXXFILES = $(wildcard src/*.cpp)
OBJS = $(CXXFILES:.cpp=.o)
CXXFLAGS = `pkg-config --cflags gtkmm-3.0`
LIBS = `pkg-config --libs gtkmm-3.0`
GLADES = $(wildcard ui/*.glade)
GLADES_HOME = $(addprefix $(HOME)/.picket/,$(GLADES))

all: $(PROGRAM)
	mkdir -p $(HOME)/.picket
	cp resources/formats $(HOME)/.picket
	cp resources/config.ini $(HOME)/.picket

%.o: %.cpp
	$(CXX) $^ -o $@ -I $(*D) -c $(CXXFLAGS)

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS) $(LIBS)

debug: CXXFLAGS += -g
debug: clean all

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: install
install: $(PROGRAM)
	mkdir -p /etc/picket
	cp $(GLADES) /etc/picket
	cp $(PROGRAM) /usr/bin
