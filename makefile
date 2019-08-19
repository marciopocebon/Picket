CXX     ?= g++
PROGRAM  = picket
DESKTOP  = $(PROGRAM).desktop
ICON     = $(PROGRAM).svg
CXXFILES = $(wildcard src/*.cpp)
OBJS     = $(CXXFILES:.cpp=.o)
CXXFLAGS = `pkg-config --cflags gtkmm-3.0`
LIBS     = `pkg-config --libs gtkmm-3.0`
GLADES   = $(wildcard ui/*.glade)
PREFIX   = /usr

all: $(PROGRAM)

%.o: %.cpp
	$(CXX) $^ -o $@ -I $(*D) -c $(CXXFLAGS)

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS) $(LIBS)

debug: CXXFLAGS += -g
debug: clean all

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(PROGRAM)

.PHONY: install
install: $(PROGRAM)
	install -d $(DESTDIR)$(PREFIX)/share/$(PROGRAM)
	install -d $(DESTDIR)$(PREFIX)/share/applications
	install -d $(DESTDIR)$(PREFIX)/share/pixmaps

	install -D -m 0755 $(PROGRAM)           $(DESTDIR)$(PREFIX)/bin/$(PROGRAM)
	install -D -m 0644 $(GLADES)            $(DESTDIR)$(PREFIX)/share/$(PROGRAM)/
	install -D -m 0644 resources/$(DESKTOP) $(DESTDIR)$(PREFIX)/share/applications/
	install -D -m 0644 resources/$(ICON)    $(DESTDIR)$(PREFIX)/share/pixmaps/

.PHONY: uninstall
uninstall: $(PROGRAM)
	rm -fr $(DESTDIR)$(PREFIX)/share/$(PROGRAM)
	rm -f  $(DESTDIR)$(PREFIX)/bin/$(PROGRAM)
	rm -f  $(DESTDIR)$(PREFIX)/share/applications/$(DESKTOP)
	rm -f  $(DESTDIR)$(PREFIX)/share/pixmaps/$(ICON)
