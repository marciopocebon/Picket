objects = main.o mainwindow.o colorpickerwindow.o color.o colorformatmanager.o

main : $(objects)
	g++ $(DEBUG) -o picket $(objects) `pkg-config gtkmm-3.0 --cflags --libs`

main.o : main.cpp
	g++ $(DEBUG) -I /home/andrija/Projects/GtkMM/Picket/ -c main.cpp `pkg-config gtkmm-3.0 --cflags --libs`

mainwindow.o : mainwindow.cpp
	g++ $(DEBUG) -I /home/andrija/Projects/GtkMM/Picket/ -c mainwindow.cpp `pkg-config gtkmm-3.0 --cflags --libs`

colorpickerwindow.o : colorpickerwindow.cpp
	g++ $(DEBUG) -I /home/andrija/Projects/GtkMM/Picket/ -c colorpickerwindow.cpp `pkg-config gtkmm-3.0 --cflags --libs`

color.o : color.cpp
	g++ $(DEBUG) -I /home/andrija/Projects/GtkMM/Picket/ -c color.cpp

colorformatmanager.o : colorformatmanager.cpp
	g++ $(DEBUG) -I /home/andrija/Projects/GtkMM/Picket/ -c colorformatmanager.cpp

clean :
	rm -f picket $(objects)

debug: DEBUG = -g

debug: clean main
