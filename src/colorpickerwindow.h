#pragma once

#include <gtkmm.h>
#include "mainwindow.h"
#include "color.h"

class ColorPickerWindow : public Gtk::Window
{
private:
    int screenWidth = 0;
    int screenHeight = 0;
    int x = 0;
    int y = 0;
    int xn = 0;
    int yn = 0;

    Color color;

    int minPixelSize = 2;
    int maxPixelSize = 15;
    int pixelSize = 8;
    int minPixelsPerRow = 1;
    int maxPixelsPerRow = 31;
    int pixelsPerRow = 13;
    int magnifierSize = pixelSize*pixelsPerRow;

    void TranslateToInnerBounds();
    void ChangePixelsPerRow(int change);
    void ChangePixelSize(int change);
    void CalculateMagnifierSize();
    void Redraw();

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

public:
    ColorPickerWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    void SetApp(Glib::RefPtr<Gtk::Application> _app);
    void SetMainWindow(MainWindow* _mainWindow);
    void GetPixelFromPixbuf(double x, double y, Glib::RefPtr<Gdk::Pixbuf> pixbuf, unsigned char *pixels);
};
