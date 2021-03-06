#pragma once

#include <gtkmm.h>
#include "mainwindow.h"
#include "color.h"
#include "config.h"

class MainWindow;

class ColorPickerWindow : public Gtk::Window
{
private:
    int screenWidth = 0;
    int screenHeight = 0;
    int x = 0;
    int y = 0;
    int magnifierX = 0;
    int magnifierY = 0;

    Color color;
    Config* config;

    int minPixelSize = 2;
    int maxPixelSize = 15;
    int pixelSize = 8;
    int minPixelsPerRow = 1;
    int maxPixelsPerRow = 49;
    int pixelsPerRow = 13;
    int outterBounds = 50;
    int magnifierSize = pixelSize*pixelsPerRow;

    int halfMagnifierWidth() { return (pixelsPerRow-1)/2; };

    void ChangePixelsPerRow(int change);
    void ChangePixelSize(int change);
    void CalculateMagnifierSize();
    void Redraw();
    void FinishPick(bool takeColor);

protected:
    Glib::RefPtr<Gtk::Application> app;
    Gtk::Window *window;
    Gtk::DrawingArea *drawingArea;
    Glib::RefPtr<Gdk::Pixbuf> screenshot;
    MainWindow *mainWindow;

    void on_showed();
    bool on_key_pressed(GdkEventKey* event);
    bool on_button_pressed(GdkEventButton* button_event);
    bool on_my_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool on_my_motion_notify_event(GdkEventMotion* motion_event);
    bool on_scroll(GdkEventScroll* scroll_event);

    void GetPixelFromPixbuf(double x, double y, Glib::RefPtr<Gdk::Pixbuf> pixbuf, unsigned char *pixels);

public:
    ColorPickerWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    void SetApp(Glib::RefPtr<Gtk::Application> _app);
    void SetMainWindow(MainWindow* _mainWindow);
    void SetConfig(Config* cfg);
};
