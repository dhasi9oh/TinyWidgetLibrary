//
// Created by 86186 on 2024/2/5.
//
#include "Buttons/CheckableButton/RadioButton.h"
#include "Helper/Ripple/RoundRipple.h"

namespace TinyWidgetLibrary
{


	RadioButton::RadioButton(QWidget *parent)
		: CheckableButton(parent)
	{
		init();
	}

	RadioButton::~RadioButton()
	{
	}

	void RadioButton::init()
	{
		setAttribute(Qt::WA_Hover);
		setAutoExclusive(true);
		setCheckedStateValue(1.5);
		setCheckRippleColor(QColor(0, 102, 180));
		setUncheckRippleColor(QColor(70, 109, 190));
		
		m_checkedTransitionAnimation->setDuration(250);
		m_uncheckedTransitionAnimation->setDuration(250);
	}

	QSize RadioButton::sizeHint() const
	{
		int l = WIDGET_LENGTH + 2 * WIDGET_MARGIN + 8;

		if (text().isEmpty()) {
			return QSize(l, l);
		}

		int w = fontMetrics().size(Qt::TextShowMnemonic, text()).width();
		return QSize(w + l + CHARACTER_INTERVAL + END_INTERVAL, l);
	}

	QMargins RadioButton::getMargins() const
	{
		return QMargins(
				WIDGET_MARGIN,
				WIDGET_MARGIN,
				WIDGET_MARGIN,
				WIDGET_MARGIN);
	}

	QRectF RadioButton::getWidgetRect() const
	{
		QRectF rect_angle = QRectF(
				0,
				(height() - WIDGET_LENGTH) * 0.5 - WIDGET_MARGIN,
				WIDGET_LENGTH + 2 * WIDGET_MARGIN,
				WIDGET_LENGTH + 2 * WIDGET_MARGIN);

		return rect_angle;
	}

	void RadioButton::paintWidget(QPainter *painter, const QRectF &rect_f)
	{
		qreal frame_radius	= WIDGET_LENGTH * 0.5;
		qreal radius		= m_scale * WIDGET_LENGTH * 0.5;
		QRectF angle		= rect_f.marginsRemoved(getMargins());
		QPointF center		= angle.center();

		if (radius < frame_radius) {
			painter->setPen(m_frameColor);
			painter->setBrush(m_backgroundColor);
			painter->drawEllipse(center, frame_radius, frame_radius);

			painter->setPen(Qt::NoPen);
			painter->setBrush(m_triggerColor);
			painter->drawEllipse(center, radius, radius);
		}
		else {
			qreal r = radius - frame_radius;

			painter->setPen(m_triggerColor);
			painter->setBrush(m_triggerColor);
			painter->drawEllipse(center, frame_radius, frame_radius);

			painter->setPen(Qt::NoPen);
			painter->setBrush(QColorConstants::White);
			painter->drawEllipse(center, r, r);
		}
	}

	void RadioButton::mousePressEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);

		if (!isEnabled()) return;

		QPoint pos = QPoint(
				WIDGET_MARGIN + WIDGET_LENGTH * 0.5 - RIPPLE_WIDGET_EXTEND,
				height() * 0.5 - RIPPLE_WIDGET_EXTEND
		);

		RoundRipple* ripple = new RoundRipple(pos);

		ripple->setOverlay(m_overlay);
		ripple->setColor(isChecked() ? m_checkRippleColor : m_uncheckRippleColor);
		ripple->setRadiusAnimationEndValue(18);
		ripple->setOpacityAnimationStartValue(0.8);

		m_overlay->addRipple(ripple);

		QAbstractButton::mousePressEvent(event);
	}
}