objects = main.o mainwindow.o colorpickerwindow.o color.o

main : $(objects)
	g++ -o picket $(objects) `pkg-config gtkmm-3.0 --cflags --libs`

main.o : main.cpp
	g++ -I /home/andrija/Projects/GtkMM/Picket/ -c main.cpp `pkg-config gtkmm-3.0 --cflags --libs`

mainwindow.o : mainwindow.cpp
	g++ -I /home/andrija/Projects/GtkMM/Picket/ -c mainwindow.cpp `pkg-config gtkmm-3.0 --cflags --libs`

colorpickerwindow.o : colorpickerwindow.cpp
	g++ -I /home/andrija/Projects/GtkMM/Picket/ -c colorpickerwindow.cpp `pkg-config gtkmm-3.0 --cflags --libs`

color.o : color.cpp
	g++ -I /home/andrija/Projects/GtkMM/Picket/ -c color.cpp

clean :
	rm -f picket $(objects)
