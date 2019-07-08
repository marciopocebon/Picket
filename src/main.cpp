#include <gtkmm.h>
#include <unistd.h>
#include <sys/stat.h>
#include "mainwindow.h"
#include "colorpickerwindow.h"
#include "settingswindow.h"
#include "config.h"

using namespace std;

Config config;
MainWindow *window;
ColorPickerWindow *colorPickerWindow;
SettingsWindow *settingsWindow;
string userDirectory = (string)getenv("HOME")+"/.picket";

int DirectoryExists(string path)
{
    struct stat info;

    int statRC = stat( path.c_str(), &info );
    if( statRC != 0 )
    {
        if (errno == ENOENT)  { return 0; } // something along the path does not exist
        if (errno == ENOTDIR) { return 0; } // something in path prefix is not a dir
        return -1;
    }

    return ( info.st_mode & S_IFDIR ) ? 1 : 0;
}

bool CreateUserDirectory()
{
    if (mkdir(userDirectory.c_str(), 0777) == -1)
    {
        cerr << "Error in creating user directory:  " << strerror(errno) << endl;
        return false;
    }
    else
    {
        return true;
    }
}

int main(int argc, char *argv[])
{
    if(!DirectoryExists(userDirectory))
        CreateUserDirectory();

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
