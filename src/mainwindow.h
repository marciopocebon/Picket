#pragma once

#include <gtkmm.h>
#include "colorpickerwindow.h"
#include "settingswindow.h"
#include "color.h"
#include "colorformatmanager.h"
#include "config.h"

class ColorPickerWindow;
class SettingsWindow;

class MainWindow : public Gtk::Window
{
    private:
    Color color;
    Config* config;
    ColorPickerWindow *colorPickerWindow;
    SettingsWindow *settingsWindow;
    void LoadConfiguration();
    void SaveConfiguration();

    protected:
    Glib::RefPtr<Gtk::Application> app;
    Gtk::ToolButton *exitBtn;
    Gtk::ToolButton *settingsBtn;
    Gtk::ToolButton *colorPickerBtn;
    Gtk::ToolButton *clipboardBtn;
    Gtk::Window *window;
    Gtk::DrawingArea *colorArea;
    Gtk::Scale *redScale;
    Gtk::Scale *greenScale;
    Gtk::Scale *blueScale;
    Gtk::Scale *alphaScale;
    Gtk::Label *hexColorLabel;
    Gtk::ComboBoxText *formatComboBox;
    ColorFormatManager colorFormatManager;

    public:
    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);

    void Show(int response);
    void SetApp(Glib::RefPtr<Gtk::Application> _app);
    void SetConfig(Config* cfg);
    void SetColorPickerWindow(ColorPickerWindow* _colorPickerWindow);
    void SetSettingsWindow(SettingsWindow* _settingsWindow);
    void SetPickedColor(Color pickedColor);
    void SyncColorWithScales();
    void PopulateComboWithFormats();
    void InitColorFormatManager();

    void on_hidden();
    bool on_colorArea_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    void on_exitButton_clicked();
    void on_settingsButton_clicked();
    void on_colorPickerButton_clicked();
    void on_clipboardButton_clicked();
    void on_color_changed();
    void on_format_changed();
};
