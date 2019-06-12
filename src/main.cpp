#include <gtkmm.h>
#include "mainwindow.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    auto builder = Gtk::Builder::create_from_file((string)getenv("HOME")+"/MainWindow.glade");

    MainWindow *window;
    builder->get_widget_derived("MainWindow", window);
    window->SetApp(app);

    return app->run(*window);
}
