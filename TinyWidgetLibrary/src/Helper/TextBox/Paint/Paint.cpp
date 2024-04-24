//
// Created by 86186 on 2024/3/5.
//
#include "Helper/TextBox/Paint/Paint.h"

namespace TinyWidgetLibrary
{

	Paint::Paint(PaintWidget *source, QObject *parent)
			: QObject(parent)
			, m_source(source)
	{
		m_color				= QColor(0, 102, 180);
		m_frameColor		= QColor(0, 102, 180);
		m_backgroundColor	= Qt::white;
	}

	Paint::~Paint()
	{
	}

	void Paint::setSource(PaintWidget *source)
	{
		m_source = source;
	}

	QColor Paint::getColor() const
	{
		return m_color;
	}

	void Paint::setColor(const QColor &color)
	{
		m_color = color;
		m_source->update();
	}

	QColor Paint::getFrameColor() const
	{
		return m_frameColor;
	}

	void Paint::setFrameColor(const QColor &color)
	{
		m_frameColor = color;
		m_source->update();
	}

	QColor Paint::getBackgroundColor() const
	{
		return m_backgroundColor;
	}

	void Paint::setBackgroundColor(const QColor &color)
	{
		m_backgroundColor = color;
		m_source->update();
	}


}