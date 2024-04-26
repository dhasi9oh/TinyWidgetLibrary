//
// Created by 86186 on 2024/2/10.
//
#include "Buttons/RectangleButton/StandardButton.h"
#include "Helper/Ripple/RollingRipple.h"

namespace TinyWidgetLibrary
{

	StandardButton::StandardButton(QWidget *parent)
		: RectangleButton(parent)
	{
		init();
	}

	StandardButton::~StandardButton()
	{
	}

	void StandardButton::mousePressEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);

		if (!isEnabled()) return;

		QMargins margins		= QMargins(
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND);

		QPainterPath path;
		QRect r					= m_overlay->rect().marginsRemoved(margins);
		RollingRipple* ripple 	= new RollingRipple(r.center(), m_overlay, this);

		path.addRoundedRect(r, RECT_ANGLE_RADIUS, RECT_ANGLE_RADIUS);
		ripple->setCirqueColor(m_cirqueColor);
		ripple->setUseClipPath(true);
		ripple->setClipPath(path);

		m_overlay->addRipple(ripple);

		QAbstractButton::mousePressEvent(event);
	}

	void StandardButton::paintWidget(QPainter *painter, const QRectF &rect_f)
	{
		painter->setPen(QPen(m_frameColor, 1));
		painter->setBrush(m_backgroundColor);
		painter->drawRoundedRect(rect_f, RECT_ANGLE_RADIUS, RECT_ANGLE_RADIUS);
	}

	void StandardButton::init()
	{
		m_cirqueColor = QColor(59, 189, 245, 0.9 * 255);
	}

	void StandardButton::setCirqueColor(const QColor &color)
	{
		m_cirqueColor = color;
	}

	QColor StandardButton::getCirqueColor() const
	{
		return m_cirqueColor;
	}

}