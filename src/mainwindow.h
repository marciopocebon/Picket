#pragma once

#include <gtkmm.h>
#include "color.h"
#include "colorformatmanager.h"

class MainWindow : public Gtk::Window
{
    private:
    Color color;
    void InitColorFormatManager();

    protected:
    Glib::RefPtr<Gtk::Application> app;
    Gtk::ToolButton *exitBtn;
    Gtk::ToolButton *colorPickerBtn;
    Gtk::ToolButton *clipboardBtn;
    Gtk::Window *window;
    Gtk::DrawingArea *colorArea;
    Gtk::Scale *redScale;
    Gtk::Scale *greenScale;
    Gtk::Scale *blueScale;
    Gtk::Label *hexColorLabel;
    Gtk::ComboBoxText *formatComboBox;
    ColorFormatManager colorFormatManager;

    public:
    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);

    void SetApp(Glib::RefPtr<Gtk::Application> _app);
    void SetPickedColor(Color pickedColor);
    void SyncColorWithScales();
    void PopulateComboWithFormats();

    void on_hidden();
    bool on_colorArea_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    void on_exitButton_clicked();
    void on_colorPickerButton_clicked();
    void on_clipboardButton_clicked();
    void on_color_changed();
};
