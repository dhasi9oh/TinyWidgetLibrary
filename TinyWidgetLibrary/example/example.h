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

//��Ϣ����
int test1(int argc, char *argv[])
{
	//ptr�ڹر�ʱ�Զ�����
	QApplication a(argc, argv);
	auto ptr = new TinyWidgetLibrary::MessageBoxHint;
	//���÷������ɫ
	//ptr->setFrameColor(QColor(255, 255, 255));
	ptr->setText("hello world!");
	ptr->show();
	return a.exec();
}

//����ؼ�
int test2(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TinyWidgetLibrary::Slider w;
	TinyWidgetLibrary::Slider::Direction d;
	//���Ʒ���
	//d = TinyWidgetLibrary::Slider::Direction::BottomToTop;
	d = TinyWidgetLibrary::Slider::Direction::LeftToRight;
	//d = TinyWidgetLibrary::Slider::Direction::RightToLeft;
	//d = TinyWidgetLibrary::Slider::Direction::TopToBottom;
	w.setDirection(d);
	// ���Ʒ�Χ
	//w.setMinimum(0);
	//w.setMaximum(1000);
	//���ƽ���������ɫ
	//w.setProgressColor(Qt::red);
	//���ƻ�����ɫ
	//w.setCenterColor(Qt::black);
	w.show();
	return a.exec();
}

//��ѡ��ť
int test3(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//����Ŀؼ���඼��Ҫһ�����ؼ�
	//Overlay���Ǹ����ڸ��ؼ��ϵ�
	// ���û�и��ؼ�����OverlayΪһ������
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

//���ذ�ť
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


//��ѡ��ť
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

//toggle��ť
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

//��׼��ť
int test7(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QWidget w;
	TinyWidgetLibrary::StandardButton s(&w);
	w.resize(640, 480);
	s.move(100, 100);
	s.setText("hello world!");
	s.setCirqueColor(Qt::white);
	//���ò�����ɫ
	//ptr->setCirqueColor(Qt::red);
	w.show();
	return a.exec();
}

//�ı���
int test8(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TinyWidgetLibrary::TextBox w;
	//����ռλ�ı�
	//w.setPlaceholderText("hello world!");
	//���û�ȡ����ʱռλ�ı���ɫ
	//w.setFocusInPlaceholderTextColor("hello world!");
	//����ʧȥ����ʱռλ�ı���ɫ
	//w.setFocusOutPlaceholderTextColor("hello world!");
	w.show();
	return a.exec();
}

//��ѡ�ı���
int test9(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TinyWidgetLibrary::ComboBox w;
	//����ռλ�ı�
	//w.setPlaceholderText("hello world!");
	//���û�ȡ����ʱռλ�ı���ɫ
	//w.setFocusInPlaceholderTextColor("hello world!");
	//����ʧȥ����ʱռλ�ı���ɫ
	//w.setFocusOutPlaceholderTextColor("hello world!");
	w.show();
	return a.exec();
}


int test10(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TinyWidgetLibrary::SizeFixedDialog w;
	w.show();
	//�ڵ���show���ڵ�������źŲŻ���ʾ
	emit w.showTarget();
	return a.exec();
}