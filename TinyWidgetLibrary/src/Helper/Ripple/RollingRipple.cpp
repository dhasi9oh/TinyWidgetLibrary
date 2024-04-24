//
// Created by 86186 on 2024/2/11.
//
#include "Helper/Ripple/RollingRipple.h"
#include "Helper/Ripple/Overlay.h"


namespace TinyWidgetLibrary
{
	RollingRipple::RollingRipple(const QPoint &point, QWidget *parent)
			: m_scale(0)
			, m_cirqueColor(QColor(0, 102, 180))
			, m_scaleAnimation(createAnimtion("scale"))
			, m_opacityAnimation(createAnimtion("opacity"))
			, Ripple(point, parent)
	{
		init();
	}

	RollingRipple::RollingRipple(const QPoint &point, Overlay *overlay, QWidget *parent)
			: m_scale(0)
			, m_cirqueColor(QColor(0, 102, 180))
			, m_scaleAnimation(createAnimtion("scale"))
			, m_opacityAnimation(createAnimtion("opacity"))
			, Ripple(point, overlay, parent)
	{
		init();
	}

	RollingRipple::~RollingRipple()
	{
	}

	void RollingRipple::setScale(qreal scale)
	{
		Q_ASSERT(m_overlay != nullptr);
		if (fabs(m_scale - scale) < 0.00001) return;

		m_scale = scale;
		m_overlay->update();
	}

	qreal RollingRipple::getScale() const
	{
		return m_scale;
	}

	void RollingRipple::setOpacity(qreal opacity)
	{
		Q_ASSERT(m_overlay != nullptr);
		if (opacity == m_opacity) return;

		m_opacity = opacity;
		m_overlay->update();
	}

	qreal RollingRipple::getOpacity() const
	{
		return m_opacity;
	}

	void RollingRipple::setCirqueColor(const QColor &color)
	{
		Q_ASSERT(m_overlay != nullptr);
		if (m_cirqueColor == color) return;

		m_cirqueColor = color;
		m_overlay->update();
	}

	QColor RollingRipple::getCirqueColor() const
	{
		return m_cirqueColor;
	}

	void RollingRipple::setScaleAnimationStartValue(qreal value)
	{
		m_scaleAnimation->setStartValue(value);
	}

	void RollingRipple::setScaleAnimationEndValue(qreal value)
	{
		m_scaleAnimation->setEndValue(value);
	}

	void RollingRipple::setOpacityAnimationStartValue(qreal value)
	{
		m_opacityAnimation->setStartValue(value);
	}

	void RollingRipple::setOpacityAnimationEndValue(qreal value)
	{
		m_opacityAnimation->setEndValue(value);
	}

	void RollingRipple::init()
	{
		setCirqueColor(QColor(255, 255, 255, 0.4 * 255));
		setScaleAnimationStartValue(0);
		setScaleAnimationEndValue(2);
		setOpacityAnimationStartValue(0.5);
		setOpacityAnimationEndValue(0);

		connect(this, &QAbstractAnimation::finished, this, &Ripple::destroy);
	}

	void RollingRipple::paintRipple(QPainter *painter)
	{
		QMargins margins	= QMargins(
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND);
		QRect rect 			= m_overlay->rect().marginsRemoved(margins);
		qreal radius 		= qSqrt(qPow(rect.width(), 2) + qPow(rect.height(), 2)) * m_scale / 2;
		qreal inner_radius 	= 0.9 * radius;
		QPen pen			= QPen(m_cirqueColor, inner_radius);

		painter->setPen(pen);
		painter->setOpacity(m_opacity);

		if (b_use) painter->setClipPath(m_path);

		painter->drawEllipse(rect.center().toPointF(), radius, radius);
	}

	QPropertyAnimation *
	RollingRipple::createAnimtion(const QByteArray &name, qint32 duratino, const QEasingCurve &easingCurve)
	{
		auto* ptr = new QPropertyAnimation(this, name);
		ptr->setEasingCurve(easingCurve);
		ptr->setDuration(duratino);
		addAnimation(ptr);
		return ptr;
	}

}