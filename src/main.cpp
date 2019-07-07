#include <gtkmm.h>
#include <unistd.h>
#include "mainwindow.h"
#include "colorpickerwindow.h"
#include "settingswindow.h"
#include "config.h"

Config config;
MainWindow *window;
ColorPickerWindow *colorPickerWindow;
SettingsWindow *settingsWindow;

int main(int argc, char *argv[])
{
    config = Config();
    config.LoadConfiguration();

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    auto mainWinBuilder = Gtk::Builder::create_from_file("/etc/picket/MainWindow.glade");
    auto colorPickerWinBuilder = Gtk::Builder::create_from_file("/etc/picket/ColorPickerWindow.glade");
    auto settingWindowBuilder = Gtk::Builder::create_from_file("/etc/picket/SettingsWindow.glade");

    mainWinBuilder->get_widget_derived("MainWindow", window);
    colorPickerWinBuilder->get_widget_derived("ColorPickerWindow", colorPickerWindow);
    settingWindowBuilder->get_widget_derived("SettingsWindow", settingsWindow);

    window->SetApp(app);
    window->SetConfig(&config);
    window->InitColorFormatManager();
    window->PopulateComboWithFormats();
    window->SetColorPickerWindow(colorPickerWindow);

    colorPickerWindow->SetApp(app);
    colorPickerWindow->SetMainWindow(window);
    colorPickerWindow->SetConfig(&config);

    settingsWindow->SetConfig(&config);
    window->SetSettingsWindow(settingsWindow);

    if(config.ShouldStartImmediatePick())
        app->run(*colorPickerWindow);
    else
        app->run(*window);

    return 0;
}
