//
// Created by 86186 on 2024/2/9.
//
#include "Helper/Ripple/RoundRipple.h"

namespace TinyWidgetLibrary
{
	RoundRipple::RoundRipple(const QPoint &point, QWidget *parent)
		: m_radius(0)
		, m_opacity(0)
		, m_brush(QColor(0, 102, 180))
		, m_radiusAnimation(createAnimtion("radius"))
		, m_opacityAnimation(createAnimtion("opacity"))
		, Ripple(point, parent)
	{
		init();
	}

	RoundRipple::RoundRipple(const QPoint &point, Overlay *overlay, QWidget *parent)
		: m_radius(0)
		, m_opacity(0)
		, m_brush(QColor(0, 102, 180))
		, m_radiusAnimation(createAnimtion("radius"))
		, m_opacityAnimation(createAnimtion("opacity"))
		, Ripple(point, overlay, parent)
	{
		init();
	}

	RoundRipple::~RoundRipple()
	{
	}

	void RoundRipple::setRadius(qreal radius)
	{
		Q_ASSERT(m_overlay != nullptr);
		if (radius == m_radius) return;

		m_radius = radius;
		m_overlay->update();
	}

	qreal RoundRipple::getRadius() const
	{
		return m_radius;
	}

	void RoundRipple::setOpacity(qreal opacity)
	{
		Q_ASSERT(m_overlay != nullptr);
		if (opacity == m_opacity) return;

		m_opacity = opacity;
		m_overlay->update();
	}

	qreal RoundRipple::getOpacity() const
	{
		return m_opacity;
	}

	void RoundRipple::setColor(const QColor &color)
	{
		Q_ASSERT(m_overlay != nullptr);
		if (m_brush.color() == color) return;

		m_brush.setColor(color);
		m_overlay->update();
	}

	QColor RoundRipple::getColor() const
	{
		return m_brush.color();
	}

	void RoundRipple::setBrush(const QBrush &brush)
	{
		Q_ASSERT(m_overlay != nullptr);
		if (m_brush == brush) return;

		m_brush = brush;
		m_overlay->update();
	}

	QBrush RoundRipple::getBrush() const
	{
		return m_brush;
	}
	
	void RoundRipple::setRadiusAnimationStartValue(qreal value)
	{
		m_radiusAnimation->setStartValue(value);
	}

	void RoundRipple::setRadiusAnimationEndValue(qreal value)
	{
		m_radiusAnimation->setEndValue(value);
	}

	void RoundRipple::setOpacityAnimationStartValue(qreal value)
	{
		m_opacityAnimation->setStartValue(value);
	}

	void RoundRipple::setOpacityAnimationEndValue(qreal value)
	{
		m_opacityAnimation->setEndValue(value);
	}

	void RoundRipple::setAnimationDuration(int duration)
	{
		m_radiusAnimation->setDuration(duration);
		m_opacityAnimation->setDuration(duration);
	}

	void RoundRipple::init()
	{
		setOpacityAnimationStartValue(0.5);
		setOpacityAnimationEndValue(0);
		setRadiusAnimationStartValue(0);
		setRadiusAnimationEndValue(300);

		m_brush.setColor(QColor(0, 102, 180));
		m_brush.setStyle(Qt::SolidPattern);

		connect(this, &QAbstractAnimation::finished, this, &Ripple::destroy);
	}

	QPropertyAnimation *RoundRipple::createAnimtion(
			const QByteArray &name,
			qint32 duratino,
			const QEasingCurve &easingCurve)
	{
		auto* ptr = new QPropertyAnimation(this, name);
		ptr->setEasingCurve(easingCurve);
		ptr->setDuration(duratino);
		addAnimation(ptr);
		return ptr;
	}

	void RoundRipple::paintRipple(QPainter *painter)
	{
		painter->setOpacity(m_opacity);
		painter->setBrush(m_brush);
		painter->drawEllipse(m_center.toPointF(), m_radius, m_radius);
	}


}