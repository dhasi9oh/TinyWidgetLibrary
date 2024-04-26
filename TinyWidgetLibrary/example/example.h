#pragma once

#include "Progress/Slider.h"
#include "TextBox/TextBox.h"
#include "TextBox/ComboBox.h"

#include "PopupBox/FloatWindow.h"
#include "PopupBox/MessageBoxHint.h"
#include "PopupBox/SizeFixedDialog.h"

#include "Buttons/CheckableButton/SwitchButton.h"
#include "Buttons/CheckableButton/RadioButton.h"
#include "Buttons/CheckableButton/CheckButton.h"
#include "Buttons/CheckableButton/ToggleButton.h"
#include "Buttons/RectangleButton/StandardButton.h"

//消息弹出
int test1(int argc, char *argv[])
{
	//ptr在关闭时自动析构
	QApplication a(argc, argv);
	auto ptr = new TinyWidgetLibrary::MessageBoxHint;
	//设置方框的颜色
	//ptr->setFrameColor(QColor(255, 255, 255));
	ptr->setText("hello world!");
	ptr->show();
	return a.exec();
}

//滑块控件
int test2(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TinyWidgetLibrary::Slider w;
	TinyWidgetLibrary::Slider::Direction d;
	//控制方向
	//d = TinyWidgetLibrary::Slider::Direction::BottomToTop;
	d = TinyWidgetLibrary::Slider::Direction::LeftToRight;
	//d = TinyWidgetLibrary::Slider::Direction::RightToLeft;
	//d = TinyWidgetLibrary::Slider::Direction::TopToBottom;
	w.setDirection(d);
	// 控制范围
	//w.setMinimum(0);
	//w.setMaximum(1000);
	//控制进度条的颜色
	//w.setProgressColor(Qt::red);
	//控制滑块颜色
	//w.setCenterColor(Qt::black);
	w.show();
	return a.exec();
}

//多选按钮
int test3(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//这里的控件大多都需要一个父控件
	//Overlay类是附着在父控件上的
	// 如果没有父控件，则Overlay为一个窗口
	QWidget s;
	auto layout = new QVBoxLayout;
	TinyWidgetLibrary::CheckButton w1(&s);
	TinyWidgetLibrary::CheckButton w2(&s);
	TinyWidgetLibrary::CheckButton w3(&s);
	w1.setText("1");
	w2.setText("2");
	w2.setCheckedColor(QColor(78, 201, 176));
	w2.setCheckRippleColor(QColor(78, 201, 176));
	w2.setUncheckRippleColor(QColor(78, 201, 176));
	w3.setText("3");
	w3.setCheckedColor(QColor(255, 74, 64));
	w3.setCheckRippleColor(QColor(255, 74, 64));
	w3.setUncheckRippleColor(QColor(255, 74, 64));
	layout->addWidget(&w1);
	layout->addWidget(&w2);
	layout->addWidget(&w3);
	s.setLayout(layout);
	s.show();
	return a.exec();
}

//开关按钮
int test4(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QWidget s;
	auto layout = new QVBoxLayout;
	TinyWidgetLibrary::SwitchButton w1(&s);
	TinyWidgetLibrary::SwitchButton w2(&s);
	TinyWidgetLibrary::SwitchButton w3(&s);
	w1.setText("1");
	w2.setText("2");
	w2.setCheckedColor(QColor(78, 201, 176));
	w2.setCheckRippleColor(QColor(78, 201, 176));
	w2.setUncheckRippleColor(QColor(78, 201, 176));
	w3.setText("3");
	w3.setCheckedColor(QColor(255, 74, 64));
	w3.setCheckRippleColor(QColor(255, 74, 64));
	w3.setUncheckRippleColor(QColor(255, 74, 64));
	layout->addWidget(&w1);
	layout->addWidget(&w2);
	layout->addWidget(&w3);
	s.setLayout(layout);
	s.show();
	return a.exec();
}


//单选按钮
int test5(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QWidget s;
	auto layout = new QVBoxLayout;
	TinyWidgetLibrary::RadioButton w1(&s);
	TinyWidgetLibrary::RadioButton w2(&s);
	TinyWidgetLibrary::RadioButton w3(&s);
	w1.setText("1");
	w2.setText("2");
	w2.setCheckedColor(QColor(78, 201, 176));
	w2.setCheckRippleColor(QColor(78, 201, 176));
	w2.setUncheckRippleColor(QColor(78, 201, 176));
	w3.setText("3");
	w3.setCheckedColor(QColor(255, 74, 64));
	w3.setCheckRippleColor(QColor(255, 74, 64));
	w3.setUncheckRippleColor(QColor(255, 74, 64));
	layout->addWidget(&w1);
	layout->addWidget(&w2);
	layout->addWidget(&w3);
	s.setLayout(layout);
	s.show();
	return a.exec();
}

//toggle按钮
int test6(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QWidget w;
	TinyWidgetLibrary::ToggleButton s(&w);
	w.resize(640, 480);
	s.move(100, 100);
	s.setText("hello world!");
	w.show();
	return a.exec();
}

//标准按钮
int test7(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QWidget w;
	TinyWidgetLibrary::StandardButton s(&w);
	w.resize(640, 480);
	s.move(100, 100);
	s.setText("hello world!");
	s.setCirqueColor(Qt::white);
	//设置波纹颜色
	//ptr->setCirqueColor(Qt::red);
	w.show();
	return a.exec();
}

//文本框
int test8(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TinyWidgetLibrary::TextBox w;
	//设置占位文本
	//w.setPlaceholderText("hello world!");
	//设置获取焦点时占位文本颜色
	//w.setFocusInPlaceholderTextColor("hello world!");
	//设置失去焦点时占位文本颜色
	//w.setFocusOutPlaceholderTextColor("hello world!");
	w.show();
	return a.exec();
}

//可选文本框
int test9(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TinyWidgetLibrary::ComboBox w;
	//设置占位文本
	//w.setPlaceholderText("hello world!");
	//设置获取焦点时占位文本颜色
	//w.setFocusInPlaceholderTextColor("hello world!");
	//设置失去焦点时占位文本颜色
	//w.setFocusOutPlaceholderTextColor("hello world!");
	w.show();
	return a.exec();
}


int test10(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TinyWidgetLibrary::SizeFixedDialog w;
	w.show();
	//在调用show后在调用这个信号才会显示
	emit w.showTarget();
	return a.exec();
}