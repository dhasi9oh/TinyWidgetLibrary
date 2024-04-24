//
// Created by 86186 on 2024/3/7.
//

#ifndef TINYWIDGETLIBRARY_RISEPAINT_H
#define TINYWIDGETLIBRARY_RISEPAINT_H

#include "Helper/TextBox/Paint/Paint.h"

namespace TinyWidgetLibrary
{
	class Paint;
	class PaintWidget;

	class RisePaint : public Paint
	{
		Q_OBJECT

	public:

		explicit RisePaint(PaintWidget *source, QObject *parent = nullptr);

		virtual ~RisePaint();

		virtual void operator()(QPainter* painter);
	};

} // TinyWidgetLibrary

#endif //TINYWIDGETLIBRARY_RISEPAINT_H
