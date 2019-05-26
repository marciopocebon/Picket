#pragma once

#include <gtkmm.h>
#include "color.h"

class MainWindow : public Gtk::Window
{
    private:
    Color color;

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

    public:
    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    bool on_colorArea_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    void on_exitButton_clicked();
    void on_colorPickerButton_clicked();
    void on_clipboardButton_clicked();
    void on_hidden();
    void set_app(Glib::RefPtr<Gtk::Application> _app);
    void set_picked_color(Color pickedColor);
};
