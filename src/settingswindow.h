#pragma once

#include <gtkmm.h>
#include "mainwindow.h"
#include "config.h"

class MainWindow;

class SettingsWindow : public Gtk::Dialog
{
private:
    Config* config;
    MainWindow* mainWindow;
    Gtk::Button *saveButton;
    Gtk::Button *closeButton;
    Gtk::CheckButton *startImmediatePickCheckBox;
    Gtk::CheckButton *copyToClipboardAfterPickCheckBox;
    Gtk::CheckButton *quitAfterPickCheckBox;

public:
    SettingsWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);

    void SetMainWindow(MainWindow* _mainWindow);
    void SetConfig(Config* cfg);

    void on_saveButton_clicked();
    void on_closeButton_clicked();
};
