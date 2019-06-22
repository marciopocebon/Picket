#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include "colorpickerwindow.h"
#include "color.h"
#include "config.h"
#include <fstream>
#include "INIReader.h"

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder): Gtk::Window(cobject)
{
    refBuilder->get_widget("ExitBtn", exitBtn);
    refBuilder->get_widget("ColorPickerBtn", colorPickerBtn);
    refBuilder->get_widget("ClipboardBtn", clipboardBtn);
    refBuilder->get_widget("ColorArea", colorArea);
    refBuilder->get_widget("RedScale", redScale);
    refBuilder->get_widget("GreenScale", greenScale);
    refBuilder->get_widget("BlueScale", blueScale);
    refBuilder->get_widget("HexColorLabel", hexColorLabel);
    refBuilder->get_widget("FormatComboBox", formatComboBox);

    redScale->set_range(0, 256);
    blueScale->set_range(0, 256);
    greenScale->set_range(0, 256);
    redScale->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_changed));
    blueScale->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_changed));
    greenScale->signal_value_changed().connect(sigc::mem_fun(this, &MainWindow::on_color_changed));
    colorArea->signal_draw().connect(sigc::mem_fun(this, &MainWindow::on_colorArea_draw));
    exitBtn->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_exitButton_clicked) );
    colorPickerBtn->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_colorPickerButton_clicked) );
    clipboardBtn->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_clipboardButton_clicked) );
    formatComboBox->signal_changed().connect(sigc::mem_fun(this, &MainWindow::on_format_changed));
    this->signal_hide().connect(sigc::mem_fun(this, &MainWindow::on_hidden));

    set_title("Picket");
    set_size_request(100, 350);
    color = Color(0,0,0);
    config = Config();

    LoadConfiguration();
    InitColorFormatManager();
    PopulateComboWithFormats();

    if(config.ShouldStartImmediatePick())
        on_colorPickerButton_clicked();
}

void MainWindow::LoadConfiguration()
{
    config.LoadConfiguration();
}

void MainWindow::SaveConfiguration()
{
    bool configurationSaved = config.SaveConfiguration();

    if(configurationSaved)
        cout << "Configuration saved!" << endl;
    else
        cout << "Error is saving configuration." << endl;
}

void MainWindow::SetApp(Glib::RefPtr<Gtk::Application> _app)
{
    this->app = _app;
}

void MainWindow::SetPickedColor(Color pickedColor)
{
    redScale->set_value(pickedColor.GetRed());
    greenScale->set_value(pickedColor.GetGreen());
    blueScale->set_value(pickedColor.GetBlue());

    SyncColorWithScales();
    colorArea->queue_draw();

    if(config.ShouldCopyAfterPick())
        on_clipboardButton_clicked();
}

void MainWindow::SyncColorWithScales()
{
    color.set(redScale->get_value(), greenScale->get_value(), blueScale->get_value());
}

void MainWindow::InitColorFormatManager()
{
    colorFormatManager = ColorFormatManager();
    colorFormatManager.LoadFormats((string)getenv("HOME")+"/.picket/formats");
}

void MainWindow::PopulateComboWithFormats()
{
    vector<string> formatKeys = colorFormatManager.GetFormatsKeys();
    for(string &value: formatKeys)
    {
        formatComboBox->append(value);
    }
    cout << "config.LastFormat:" << config.GetLastFormat() << endl;
    formatComboBox->set_active(config.GetLastFormat());
}

void MainWindow::Show()
{
    if(config.ShouldQuitAfterPick())
        on_exitButton_clicked();
    else
        show();
}

void MainWindow::on_color_changed()
{
    SyncColorWithScales();
    hexColorLabel->set_text(color.GetHexString());
    colorArea->queue_draw();
}

bool MainWindow::on_colorArea_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_source_rgba(color.GetRedAsDouble(), color.GetGreenAsDouble(), color.GetBlueAsDouble(), 1);
    cr->paint();
    return true;
}

void MainWindow::on_exitButton_clicked()
{
    SaveConfiguration();
    app->quit();
}

void MainWindow::on_colorPickerButton_clicked()
{
    auto builder = Gtk::Builder::create_from_file((string)getenv("HOME")+"/ColorPickerWindow.glade");
    ColorPickerWindow *colorPickerWindow;
    builder->get_widget_derived("ColorPickerWindow", colorPickerWindow);
    colorPickerWindow->SetApp(app);
    colorPickerWindow->SetMainWindow(this);
    colorPickerWindow->SetConfig(&config);
    this->app->hold();
    this->hide();

    colorPickerWindow->show();
}

void MainWindow::on_clipboardButton_clicked()
{
    colorFormatManager.SetVariables(color.GetVariables());
    string selectedFormat = formatComboBox->get_active_text();
    string format = colorFormatManager.GetFormat(selectedFormat);

    Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();
    refClipboard->set_text(format);

    auto Icon = Gio::ThemedIcon::create("colorpicker");
    auto Notification = Gio::Notification::create(format);
    Notification->set_body("Copied to clipboard.");
    Notification->set_icon (Icon);
    app->send_notification(Notification);
}

void MainWindow::on_hidden()
{
    // std::cout << "Hidden" << std::endl;
}


void MainWindow::on_format_changed()
{
    cout << "Format Changed! New Format: " << formatComboBox->get_active_text() << endl;
    cout << "Active Row number: " << formatComboBox->get_active_row_number() << endl;
    config.SetLastFormat(formatComboBox->get_active_row_number());
}
