//
// Created by 86186 on 2024/2/4.
//
#include "Buttons/CheckableButton/CheckButton.h"
#include "Helper/Ripple/RoundRipple.h"

#include <qpropertyanimation.h>


namespace TinyWidgetLibrary
{
	CheckButton::CheckButton(QWidget *parent)
		: CheckableButton(parent)
	{
		init();
	}

	CheckButton::~CheckButton()
	{
	}

	void CheckButton::init()
	{
		setAttribute(Qt::WA_Hover);
		setCheckedStateValue(1.5);
		setCheckRippleColor(QColor(0, 102, 180));
		setUncheckRippleColor(QColor(70, 109, 190));

		m_checkedTransitionAnimation->setDuration(360);
		m_uncheckedTransitionAnimation->setDuration(360);
	}

	QSize CheckButton::sizeHint() const
	{
		int l = WIDGET_LENGTH + 2 * WIDGET_MARGIN;

		if (text().isEmpty()) {
			return QSize(l, l);
		}

		int w = fontMetrics().size(Qt::TextShowMnemonic, text()).width();
		return QSize(w + l + CHARACTER_INTERVAL + END_INTERVAL, l);
	}

	QMargins CheckButton::getMargins() const
	{
		return QMargins(
				WIDGET_MARGIN,
				WIDGET_MARGIN,
				WIDGET_MARGIN,
				WIDGET_MARGIN);
	}

	QRectF CheckButton::getWidgetRect() const
	{
		QRectF rect_f = QRectF(
				0,
				(height() - WIDGET_LENGTH) * 0.5 - WIDGET_MARGIN,
				WIDGET_LENGTH + 2 * WIDGET_MARGIN,
				WIDGET_LENGTH + 2 * WIDGET_MARGIN);

		return rect_f;
	}

	void CheckButton::paintWidget(QPainter *painter, const QRectF &rect_f)
	{
		qreal frame_radius	= WIDGET_LENGTH * 0.25;
		qreal radius		= m_scale * WIDGET_LENGTH * 0.5;
		QRectF angle		= rect_f.marginsRemoved(getMargins());

		painter->setPen(m_frameColor);
		painter->setBrush(m_backgroundColor);
		painter->drawRoundedRect(angle, frame_radius, frame_radius);

		painter->setBrush(m_triggerColor);

		if (radius * 2 < WIDGET_LENGTH) {
			painter->setPen(Qt::NoPen);
            painter->drawEllipse(angle.center(), radius, radius);
		}
		else {
			qreal r = WIDGET_LENGTH * 1.75 - radius * 2.0;

			painter->setPen(m_triggerColor);
			painter->drawRoundedRect(angle, r, r);

			if (qFabs(m_scale - 1.5) < 0.00001) {
				int h = height() * 0.5;

				painter->setPen(QPen(QColorConstants::White, 1));
				painter->drawLine(
						 WIDGET_MARGIN + WIDGET_LENGTH * 0.2,
						h,
						WIDGET_MARGIN + WIDGET_LENGTH * 0.4,
						WIDGET_MARGIN + h + WIDGET_LENGTH * 0.2
						);

				painter->drawLine(
						WIDGET_MARGIN + WIDGET_LENGTH * 0.4,
						WIDGET_MARGIN + h + WIDGET_LENGTH * 0.2,
						WIDGET_MARGIN + WIDGET_LENGTH * 0.85,
						h - WIDGET_LENGTH * 0.2
						);
			}
		}
	}

	void CheckButton::mousePressEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);

		if (!isEnabled()) return;

		QPoint pos = QPoint(
				WIDGET_MARGIN + WIDGET_LENGTH * 0.5 - RIPPLE_WIDGET_EXTEND,
				height() * 0.5 - RIPPLE_WIDGET_EXTEND
				);

		qDebug() << mapToGlobal(QPointF(0, 0)) << m_overlay->mapToGlobal(QPointF(0, 0));
		qDebug() << size() << m_overlay->size();

		RoundRipple* ripple = new RoundRipple(pos);

		ripple->setOverlay(m_overlay);
		ripple->setColor(isChecked() ? m_checkRippleColor : m_uncheckRippleColor);
		ripple->setRadiusAnimationEndValue(18);
		ripple->setOpacityAnimationStartValue(0.8);

		m_overlay->addRipple(ripple);

		QAbstractButton::mousePressEvent(event);
	}

}