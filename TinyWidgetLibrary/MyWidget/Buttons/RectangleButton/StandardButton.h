//
// Created by 86186 on 2024/2/3.
//

#ifndef TINYWIDGETLIBRARY_STANDARDBUTTON_H
#define TINYWIDGETLIBRARY_STANDARDBUTTON_H

#include "Helper/Button/RectangleButton.h"
#include "Helper/Ripple/RoundRipple.h"

namespace TinyWidgetLibrary
{

	class StandardButton : public RectangleButton
	{
		Q_OBJECT

		constexpr static int RECT_ANGLE_RADIUS 	= 8;

	public:

		explicit		StandardButton(QWidget *parent = nullptr);

		virtual			~StandardButton();

		void			setCirqueColor(const QColor& color);
		QColor			getCirqueColor() const;

	protected:

		virtual void 	mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

		virtual void 	paintWidget(QPainter *painter, const QRectF& rect_f) Q_DECL_OVERRIDE;

	private:

		void			init();

	private:

		QColor		m_cirqueColor;

	};

}

#endif //TINYWIDGETLIBRARY_STANDARDBUTTON_H
