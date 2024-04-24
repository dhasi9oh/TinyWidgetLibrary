
#include <iostream>
#include <qapplication.h>
#include "Buttons/CheckableButton/SwitchButton.h"
#include "Buttons/CheckableButton/RadioButton.h"
#include "Buttons/CheckableButton/CheckButton.h"
#include "Buttons/CheckableButton/ToggleButton.h"
#include "Buttons/RectangleButton/StandardButton.h"

#include "PopupBox/SizeFixedDialog.h"
#include "PopupBox/FloatWindow.h"
#include "PopupBox/MessageBoxHint.h"

#include "Progress/Slider.h"
#include "TextBox/TextBox.h"

#include <qdialog.h>
#include <qslider.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	auto ptr = new TinyWidgetLibrary::MessageBoxHint;
	ptr->show();
    return a.exec();
}