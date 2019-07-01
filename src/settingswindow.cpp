#include <gtkmm.h>
#include <iostream>
#include "settingswindow.h"

using namespace std;

SettingsWindow::SettingsWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder): Gtk::Dialog(cobject)
{
    refBuilder->get_widget("CloseBtn", closeButton);
    refBuilder->get_widget("SaveBtn", saveButton);

    saveButton->signal_clicked().connect(sigc::mem_fun(this, &SettingsWindow::on_saveButton_clicked) );
    closeButton->signal_clicked().connect(sigc::mem_fun(this, &SettingsWindow::on_closeButton_clicked) );

    refBuilder->get_widget("Pick1CheckBox", startImmediatePickCheckBox);
    refBuilder->get_widget("Pick2CheckBox", copyToClipboardAfterPickCheckBox);
    refBuilder->get_widget("Pick3CheckBox", quitAfterPickCheckBox);
}

void SettingsWindow::SetMainWindow(MainWindow* _mainWindow)
{
    mainWindow = _mainWindow;
}

void SettingsWindow::SetConfig(Config* cfg)
{
    config = cfg;

    startImmediatePickCheckBox->set_active(config->ShouldStartImmediatePick());
    copyToClipboardAfterPickCheckBox->set_active(config->ShouldCopyAfterPick());
    quitAfterPickCheckBox->set_active(config->ShouldQuitAfterPick());
}

void SettingsWindow::on_saveButton_clicked()
{
    config->SetImmediatePick(startImmediatePickCheckBox->get_active());
    config->SetCopyAfterPick(copyToClipboardAfterPickCheckBox->get_active());
    config->SetQuitAfterPick(quitAfterPickCheckBox->get_active());

    response(Gtk::RESPONSE_ACCEPT);
}

void SettingsWindow::on_closeButton_clicked()
{
    response(Gtk::RESPONSE_CANCEL);
}
