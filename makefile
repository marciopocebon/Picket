CXX ?= g++
PROGRAM = picket
DESKTOP = $(PROGRAM).desktop
CXXFILES = $(wildcard src/*.cpp)
OBJS = $(CXXFILES:.cpp=.o)
CXXFLAGS = `pkg-config --cflags gtkmm-3.0`
LIBS = `pkg-config --libs gtkmm-3.0`
GLADES = $(wildcard ui/*.glade)
GLADES_HOME = $(addprefix $(HOME)/.picket/,$(GLADES))

all: $(PROGRAM)
	mkdir -p $(HOME)/.picket
	cp resources/formats $(HOME)/.picket

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
	cp resources/$(DESKTOP) /usr/share/applications

.PHONY: uninstall
uninstall: $(PROGRAM)
	rm -fr /etc/$(PROGRAM)
	rm -f /usr/bin/$(PROGRAM)
	rm -f /usr/share/applications/$(DESKTOP)
