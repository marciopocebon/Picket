#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include "colorpickerwindow.h"

ColorPickerWindow::ColorPickerWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder): Gtk::Window(cobject)
{
    color = Color(0,0,0);
    this->fullscreen();
    this->signal_show().connect(sigc::mem_fun(this, &ColorPickerWindow::on_showed));
    this->signal_key_press_event().connect(sigc::mem_fun(this, &ColorPickerWindow::on_key_pressed), false);
    this->signal_button_press_event().connect(sigc::mem_fun(this, &ColorPickerWindow::on_button_pressed));
    this->signal_scroll_event().connect(sigc::mem_fun(this, &ColorPickerWindow::on_scroll));

    this->set_events(Gdk::EXPOSURE_MASK | Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK | Gdk::BUTTON_MOTION_MASK |
            Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON2_MOTION_MASK | Gdk::BUTTON3_MOTION_MASK | Gdk::BUTTON_PRESS_MASK |
            Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK | Gdk::ENTER_NOTIFY_MASK |
            Gdk::FOCUS_CHANGE_MASK | Gdk::STRUCTURE_MASK | Gdk::PROPERTY_CHANGE_MASK | Gdk::VISIBILITY_NOTIFY_MASK |
            Gdk::PROXIMITY_IN_MASK | Gdk::PROXIMITY_OUT_MASK | Gdk::SUBSTRUCTURE_MASK | Gdk::SCROLL_MASK | Gdk::TOUCH_MASK |
            Gdk::SMOOTH_SCROLL_MASK | Gdk::TOUCHPAD_GESTURE_MASK);

    refBuilder->get_widget("DrawingArea", drawingArea);
    drawingArea->signal_draw().connect(sigc::mem_fun(this, &ColorPickerWindow::on_my_draw));
    drawingArea->signal_motion_notify_event().connect(sigc::mem_fun(this, &ColorPickerWindow::on_my_motion_notify_event));
    drawingArea->add_events(Gdk::KEY_PRESS_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK);
}

void ColorPickerWindow::SetApp(Glib::RefPtr<Gtk::Application> _app)
{
    app = _app;
}

void ColorPickerWindow::SetMainWindow(MainWindow* _mainWindow)
{
    mainWindow = _mainWindow;
}

void ColorPickerWindow::SetConfig(Config* cfg)
{
    config = cfg;
    pixelSize = config->GetPixelSize();
    pixelsPerRow = config->GetPixelsPerRow();
    CalculateMagnifierSize();
}

void ColorPickerWindow::on_showed()
{
    //Take screenshot
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    auto root = Gdk::Window::get_default_root_window();
    screenWidth = root->get_width();
    screenHeight = root->get_height();
    screenshot = Gdk::Pixbuf::create(root, 0, 0, screenWidth, screenHeight);

      // Grab and hide cursor
    this->set_modal(true);
    auto display = this->get_display();
    auto window = this->get_window();
    auto screen = this->get_screen();
    auto grabSuccess = display->get_default_seat()->grab(window, Gdk::SEAT_CAPABILITY_ALL, true  ,Gdk::Cursor::create(display, Gdk::BLANK_CURSOR));

    // set initial X and Y
    auto device = display->get_default_seat()->get_pointer();
    int initialX = 0;
    int initialY = 0;
    device->get_position(screen, initialX, initialY);
    x = initialX;
    y = initialY;
}

void ColorPickerWindow::TranslateToInnerBounds()
{
    auto xMinInner = pixelsPerRow/2;
    auto xMaxInner = screenWidth - pixelsPerRow;

    if(x > xMinInner && x < xMaxInner)
        xn = x-pixelsPerRow/2;
    else if(x < xMinInner)
        xn = xMinInner;
    else if(x > xMaxInner)
        xn = xMaxInner;

    auto yMinInner = pixelsPerRow/2;
    auto yMaxInner = screenHeight - pixelsPerRow;

    if(y > yMinInner && y < yMaxInner)
        yn = y-pixelsPerRow/2;
    else if(y < yMinInner)
        yn = yMinInner;
    else if(y > yMaxInner)
        yn = yMaxInner;
}

bool ColorPickerWindow::on_my_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    // fill with screenshot
    Gdk::Cairo::set_source_pixbuf(cr, screenshot, 0, 0);
    cr->paint();

    TranslateToInnerBounds();

    // draw magnifier
    Glib::RefPtr<Gdk::Pixbuf> subImage =  Gdk::Pixbuf::create_subpixbuf(screenshot, xn, yn, pixelsPerRow, pixelsPerRow);
    Glib::RefPtr<Gdk::Pixbuf> scaledImage = subImage->scale_simple(magnifierSize, magnifierSize, Gdk::INTERP_NEAREST);
    Gdk::Cairo::set_source_pixbuf(cr, scaledImage, x-magnifierSize/2, y-magnifierSize/2);
    cr->rectangle(x-magnifierSize/2,y-magnifierSize/2,magnifierSize,magnifierSize);
    cr->fill();

    // draw outline
    cr->set_line_width(1);
    cr->set_source_rgba(0.3,0.3,0.3,1);
    cr->rectangle(x-magnifierSize/2-1,y-magnifierSize/2-1,magnifierSize+2,magnifierSize+2);
    cr->stroke();

    cr->set_line_width(2);
    cr->set_source_rgba(1,1,1,1);
    cr->rectangle(x-magnifierSize/2,y-magnifierSize/2,magnifierSize,magnifierSize);
    cr->stroke();

    // draw chosen color
    cr->set_line_width(1);
    cr->set_source_rgba(0.3,0.3,0.3,1);
    cr->rectangle(x-pixelSize/2-1,y-pixelSize/2-1,pixelSize+2,pixelSize+2);
    cr->stroke();

    cr->set_line_width(2);
    cr->set_source_rgba(1,1,1,1);
    cr->rectangle(x-pixelSize/2,y-pixelSize/2,pixelSize,pixelSize);
    cr->stroke();

    cr->set_source_rgba(color.GetRedAsDouble(), color.GetGreenAsDouble(), color.GetBlueAsDouble(), 1);
    cr->rectangle(x-pixelSize/2,y-pixelSize/2,pixelSize,pixelSize);
    cr->fill();

    // draw color text
    Cairo::TextExtents extents;
    cr->select_font_face("Monospace", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD);
    cr->set_font_size(25);
    cr->get_text_extents(color.GetHexString(), extents);

    // draw color info
    cr->set_source_rgba(color.GetRedAsDouble(), color.GetGreenAsDouble(), color.GetBlueAsDouble(), 1);
    cr->rectangle(x-extents.width/2-25,y+magnifierSize/2+25,extents.width+50,extents.height+15);
    cr->fill();

    auto contrastColor = color.GetContrastColor();
    cr->set_source_rgba(contrastColor.GetRedAsDouble(),contrastColor.GetGreenAsDouble(),contrastColor.GetBlueAsDouble(),1);
    cr->move_to(x-extents.width/2,y+magnifierSize/2+50);
    cr->show_text(color.GetHexString());

    return true;
}

bool ColorPickerWindow::on_my_motion_notify_event(GdkEventMotion* motion_event)
{
    x = motion_event->x_root;
    y = motion_event->y_root;

    GetPixelFromPixbuf(x, y, screenshot, screenshot->get_pixels());
    Redraw();

    return true;
}

bool ColorPickerWindow::on_key_pressed(GdkEventKey* event)
{
    // move mouse pointer
    auto display = this->get_display();
    auto device = display->get_default_seat()->get_pointer();

    switch(event->keyval)
    {
        case GDK_KEY_w:
        case GDK_KEY_Up:
            device->warp(this->get_screen(),x,y-1);
            break;
        case GDK_KEY_s:
        case GDK_KEY_Down:
            device->warp(this->get_screen(),x,y+1);
            break;
        case GDK_KEY_a:
        case GDK_KEY_Left:
            device->warp(this->get_screen(),x-1,y);
            break;
        case GDK_KEY_d:
        case GDK_KEY_Right:
            device->warp(this->get_screen(),x+1,y);
            break;
        case GDK_KEY_e:
        case GDK_KEY_KP_Add:
            ChangePixelsPerRow(2);
            break;
        case GDK_KEY_q:
        case GDK_KEY_KP_Subtract:
            ChangePixelsPerRow(-2);
            break;
        case GDK_KEY_space:
        case GDK_KEY_Return:
            FinishPick(true);
            break;
        case GDK_KEY_Escape:
            FinishPick(false);
            break;
        default:
            break;
    }

    Redraw();
    return true;
}

bool ColorPickerWindow::on_button_pressed(GdkEventButton* button_event)
{
    if(button_event->button == 1)
    {
        FinishPick(true);
    }

    return true;
}

bool ColorPickerWindow::on_scroll(GdkEventScroll* scroll_event)
{
    if(scroll_event->direction == GDK_SCROLL_UP)
        ChangePixelSize(1);
    else if(scroll_event->direction == GDK_SCROLL_DOWN)
        ChangePixelSize(-1);

    Redraw();
    return true;
}

void ColorPickerWindow::GetPixelFromPixbuf(double x, double y, Glib::RefPtr<Gdk::Pixbuf> pixbuf, unsigned char *pixels)
{
    guchar *p;
    p = pixels + ((int)y) * pixbuf->get_rowstride() + ((int)x) * pixbuf->get_n_channels();

    color.SetRGB((p[0]<<8) / 256, (p[1]<<8) / 256, (p[2]<<8) / 256);
}

void ColorPickerWindow::ChangePixelsPerRow(int change)
{
    auto newPixelsPerRow = pixelsPerRow + change;
    if(newPixelsPerRow > maxPixelsPerRow)
        pixelsPerRow = maxPixelsPerRow;
    else if(newPixelsPerRow < minPixelsPerRow)
        pixelsPerRow = minPixelsPerRow;
    else
        pixelsPerRow = newPixelsPerRow;

    CalculateMagnifierSize();
}

void ColorPickerWindow::ChangePixelSize(int change)
{
    auto newPixelSize = pixelSize + change;
    if(newPixelSize > maxPixelSize)
        pixelSize = maxPixelSize;
    else if(newPixelSize < minPixelSize)
        pixelSize = minPixelSize;
    else
        pixelSize = newPixelSize;

    CalculateMagnifierSize();
}

void ColorPickerWindow::CalculateMagnifierSize()
{
    magnifierSize = pixelSize*pixelsPerRow;
}

void ColorPickerWindow::Redraw()
{
    drawingArea->queue_draw();
}


void ColorPickerWindow::FinishPick(bool takeColor)
{
    config->SetPixelSize(pixelSize);
    config->SetPixelsPerRow(pixelsPerRow);

    if(takeColor)
    {
        mainWindow->SetPickedColor(color);
        mainWindow->Show(Gtk::RESPONSE_ACCEPT);
    }
    else
    {
        mainWindow->Show(Gtk::RESPONSE_CANCEL);
    }

    app->hold();
    hide();
}
