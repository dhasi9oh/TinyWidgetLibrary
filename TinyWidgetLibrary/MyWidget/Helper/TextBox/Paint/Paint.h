//
// Created by 86186 on 2024/3/5.
//

#ifndef TINYWIDGETLIBRARY_PAINT_H
#define TINYWIDGETLIBRARY_PAINT_H

#include <qwidget.h>
#include <qpainter.h>

#include "Helper/TextBox/PaintWidget.h"

namespace TinyWidgetLibrary
{
	class PaintWidget;

	class Paint : public QObject
	{
		Q_OBJECT

	public:

		explicit 	Paint(PaintWidget *source, QObject *parent = nullptr);
		virtual		~Paint();

		void		setSource(PaintWidget* source);

		QColor		getColor() const;
		void		setColor(const QColor& color);

		QColor		getFrameColor() const;
		void		setFrameColor(const QColor& color);

		QColor		getBackgroundColor() const;
		void		setBackgroundColor(const QColor& color);

		virtual void operator()(QPainter* painter) = 0;

	protected:

		PaintWidget	*m_source;
		QColor		m_color;
		QColor		m_frameColor;
		QColor		m_backgroundColor;

	};

} // TinyWidgetLibrary

#include "PaintSub/RisePaint.h"

#endif //TINYWIDGETLIBRARY_PAINT_H
