# Picket

![MainWindow](/resources/MainWindow.png)

Screen color picker for linux with magnifier and custom/user defined formats.

## Features

* [Magnifier](#Magnifier): Zoom in on particular pixels
* [Precision](#Precision): Pixel precision selection
* [CustomFormat](#CustomFormat): Custom color format output
* [Variables](#Variables): Multiple variables for format output creation
* [Settings](#Settings): Usefull settings like start immediate pick and quit after pick

### Magnifier

![Magnifier](/resources/Magnifier.gif)

### Custom Format

All the formats are stored in the directory {home}/.picket in the file formats.txt  
Lines that do not start with a `[` character are ignored and can be used like comments  
Color Formats consist of two components:  
1. [xxxx] - A unique indetifier  
2. xxxxxx... - The actual string that will be copied to the clipboard  
Example  
> [RGB]$r$, $g$, $b$

### Variables

* $r$ - Red 0-255
* $g$ - Green 0-255
* $b$ - Blue 0-255
* $a$ - Aplha 0-255
* $r_d$ - Red as dougle 0.0 - 1.0
* $g_d$ - Green as dougle 0.0 - 1.0
* $b_d$ - Blue as dougle 0.0 - 1.0
* $a_d$ - Alpha as dougle 0.0 - 1.0
* $r_hex$ - Red as hex 00 - FF
* $g_hex$ - Green as hex 00 - FF
* $b_hex$ - Blue as hex 00 - FF
* $a_hex$ - Alpha as hex 00 - FF
* $h$ - Hue
* $s$ - Saturation
* $l$ - Lightness
* $s_d$ - Saturation as double
* $l_d$ - Lightness as double

## Install

Clone the repository to your local machine.
Execute `make` to build the program and `sudo make install` to install it on your machine.

```shell
  git clone https://github.com/rajter/Picket.git
  cd Picket
  make
  sudo make install
```
### Prerequisites

* [GCC](https://gcc.gnu.org/) - GNU Compiler
* [Gtkmm](https://www.gtkmm.org/en/) Gtkmm - GTK+ wrapper for c++

## Built With

* [mINI](https://github.com/pulzed/mINI) - tiny, header only C++ library for manipulating INI files
* [Glade](https://glade.gnome.org/) - Glade user interface designer

## Authors

* **Andrija Rajter** - *Initial work* - [rajter](https://github.com/rajter)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
