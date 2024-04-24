//
// Created by 86186 on 2024/2/3.
//

#ifndef TINYWIDGETLIBRARY_SWITCHBUTTON_H
#define TINYWIDGETLIBRARY_SWITCHBUTTON_H

#include "Helper/Button/CheckableButton.h"

namespace TinyWidgetLibrary
{
	class SwitchButton : public CheckableButton
	{
		Q_OBJECT

		Q_PROPERTY(qreal float_radius_scale READ getFloatRadiusScale WRITE setFloatRadiusScale)

		constexpr static int WIDGET_WIDTH	= 36;
		constexpr static int WIDGET_HEIGHT	= 20;
		constexpr static int WIDGET_MARGIN	= 1;
		constexpr static int SLIDER_RADIUS	= 8;

	public:

		explicit		 	SwitchButton(QWidget *parent = nullptr);

		virtual 			~SwitchButton();

		void 				setFloatRadiusScale(qreal scale);
		qreal 				getFloatRadiusScale() const;

		virtual QSize 		sizeHint() const Q_DECL_OVERRIDE;

		virtual QRectF 		getWidgetRect() const Q_DECL_OVERRIDE;

		virtual QMargins 	getMargins() const Q_DECL_OVERRIDE;

	private:

		void				init();

	protected:

		virtual void 		paintWidget(QPainter *painter, const QRectF& rect_f) Q_DECL_OVERRIDE;

		virtual void		mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

	private:

		qreal	m_floatRadiusScale;
	};

}

#endif //TINYWIDGETLIBRARY_SWITCHBUTTON_H
