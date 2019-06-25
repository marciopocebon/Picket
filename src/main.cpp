#include <gtkmm.h>
#include <unistd.h>
#include "mainwindow.h"
#include "colorpickerwindow.h"
#include "config.h"

Config config;
MainWindow *window;
ColorPickerWindow *colorPickerWindow;

int main(int argc, char *argv[])
{
    config = Config();
    config.LoadConfiguration();

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    auto mainWinBuilder = Gtk::Builder::create_from_file((string)getenv("HOME")+"/MainWindow.glade");
    auto colorPicketWinBuilder = Gtk::Builder::create_from_file((string)getenv("HOME")+"/ColorPickerWindow.glade");

    mainWinBuilder->get_widget_derived("MainWindow", window);
    window->SetApp(app);
    window->SetConfig(&config);
    window->InitColorFormatManager();
    window->PopulateComboWithFormats();

    colorPicketWinBuilder->get_widget_derived("ColorPickerWindow", colorPickerWindow);
    colorPickerWindow->SetApp(app);
    colorPickerWindow->SetMainWindow(window);
    colorPickerWindow->SetConfig(&config);

    if(config.ShouldStartImmediatePick())
        app->run(*colorPickerWindow);
    else
        app->run(*window);

    return 0;
}
