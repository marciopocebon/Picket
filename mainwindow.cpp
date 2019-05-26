#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include "colorpickerwindow.h"
#include "color.h"

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder): Gtk::Window(cobject)
{
    refBuilder->get_widget("ExitBtn", exitBtn);
    refBuilder->get_widget("ColorPickerBtn", colorPickerBtn);
    refBuilder->get_widget("ClipboardBtn", clipboardBtn);
    refBuilder->get_widget("ColorArea", colorArea);
    refBuilder->get_widget("RedScale", redScale);
    refBuilder->get_widget("GreenScale", greenScale);
    refBuilder->get_widget("BlueScale", blueScale);

    redScale->set_range(0, 256);
    blueScale->set_range(0, 256);
    greenScale->set_range(0, 256);
    colorArea->signal_draw().connect(sigc::mem_fun(this, &MainWindow::on_colorArea_draw));
    exitBtn->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_exitButton_clicked) );
    colorPickerBtn->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_colorPickerButton_clicked) );
    clipboardBtn->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_clipboardButton_clicked) );
    this->signal_hide().connect(sigc::mem_fun(this, &MainWindow::on_hidden));

    set_title("Picket");
    set_size_request(100, 350);
    color = Color(0,0,0);
}

void MainWindow::on_exitButton_clicked()
{
    app->quit();
}

void MainWindow::on_colorPickerButton_clicked()
{
    auto builder = Gtk::Builder::create_from_file("ColorPickerWindow.glade");
    ColorPickerWindow *colorPickerWindow;
    builder->get_widget_derived("ColorPickerWindow", colorPickerWindow);
    colorPickerWindow->set_app(app);
    colorPickerWindow->set_main_window(this);
    this->app->hold();
    this->hide();

    colorPickerWindow->show();
}

void MainWindow::on_clipboardButton_clicked()
{
	Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();
	// refClipboard->set_text("Hello");
}

void MainWindow::on_hidden()
{
    // std::cout << "Hidden" << std::endl;
}

void MainWindow::set_app(Glib::RefPtr<Gtk::Application> _app)
{
    this->app = _app;
}

void MainWindow::set_picked_color(Color pickedColor)
{
    //color.set(r,g,b);
    color = pickedColor;
    colorArea->queue_draw();
    redScale->set_value(color.GetRed());
    greenScale->set_value(color.GetGreen());
    blueScale->set_value(color.GetBlue());
    std::cout << "Color:" << color.GetHexString() << std::endl;
}

bool MainWindow::on_colorArea_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_source_rgba(color.GetRedAsDouble(), color.GetGreenAsDouble(), color.GetBlueAsDouble(), 1);
    cr->paint();
    return true;
}
