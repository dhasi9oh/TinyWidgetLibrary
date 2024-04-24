//
// Created by 86186 on 2024/2/7.
//
#include "Buttons/CheckableButton/ToggleButton.h"

namespace TinyWidgetLibrary
{
	ToggleButton::ToggleButton(QWidget *parent)
		: OverlayAbstractButton(parent)
	{
		init();
	}

	ToggleButton::~ToggleButton()
	{
	}

	void ToggleButton::setScale(qreal scale)
	{
		m_scale = scale;
		update();
	}

	qreal ToggleButton::getScale() const
	{
		return m_scale;
	}

	void ToggleButton::setCheckedTextColor(const QColor &color)
	{
		m_checkedTextColor = color;
		update();
	}

	QColor ToggleButton::getCheckedTextColor() const
	{
		return m_checkedTextColor;
	}

	void ToggleButton::setUnCheckedTextColor(const QColor &color)
	{
		m_uncheckedTextColor = color;
	}

	QColor ToggleButton::getUnCheckedTextColor() const
	{
		return m_uncheckedTextColor;
	}

	void ToggleButton::setUnEnabledCheckedTextColor(const QColor &color)
	{
		m_unEnabledCheckedTextColor = color;
		update();
	}

	QColor ToggleButton::getUnEnabledCheckedTextColor() const
	{
		return m_unEnabledCheckedTextColor;
	}

	void ToggleButton::setFrameColor(const QColor &color)
	{
		m_frameColor = color;
	}

	QColor ToggleButton::getFrameColor() const
	{
		return m_frameColor;
	}

	void ToggleButton::setUnEnabledFrameColor(const QColor &color)
	{
		m_disableFrameColor = color;
		update();
	}

	QColor ToggleButton::getUnEnabledFrameColor() const
	{
		return m_disableFrameColor;
	}

	void ToggleButton::setHoverColor(const QColor &color)
	{
		m_hoverColor = color;
		update();
	}

	QColor ToggleButton::getHoverColor() const
	{
		return m_hoverColor;
	}

	void ToggleButton::setTriggerdColor(const QColor &color)
	{
		m_triggerColor = color;
	}

	QColor ToggleButton::getTriggerdColor() const
	{
		return m_triggerColor;
	}

	void ToggleButton::setCheckedColor(const QColor &color)
	{
		m_checkedColor = color;
		update();
	}

	QColor ToggleButton::getCheckedColor() const
	{
		return m_checkedColor;
	}

	void ToggleButton::setUnCheckedColor(const QColor &color)
	{
		m_uncheckedColor = color;
		update();
	}

	QColor ToggleButton::getUnCheckedColor() const
	{
		return m_uncheckedColor;
	}

	void ToggleButton::setUnEnabledCheckedColor(const QColor &color)
	{
		m_disableCheckedColor = color;
		update();
	}

	QColor ToggleButton::getUnEnabledCheckedColor() const
	{
		return m_disableCheckedColor;
	}

	void ToggleButton::setUnEnabledUnCheckedColor(const QColor &color)
	{
		m_disableUncheckedColor = color;
		update();
	}

	QColor ToggleButton::getUnEnabledUnCheckedColor() const
	{
		return m_disableUncheckedColor;
	}

	QRectF ToggleButton::getWidgetRect() const
	{
		return rect();
	}

	QMargins ToggleButton::getMargins() const
	{
		return QMargins(
				WIDGET_MARGIN,
				WIDGET_MARGIN,
				WIDGET_MARGIN,
				WIDGET_MARGIN
				);
	}

	bool ToggleButton::event(QEvent *event)
	{
		switch (event->type())
		{
			case QEvent::HoverEnter: {
				if (isEnabled()) {
					m_backgroundColor = m_hoverColor;
					update();
				}
				break;
			}
			case QEvent::HoverLeave: {
				if (isEnabled()) {
					m_backgroundColor = m_uncheckedColor;
					update();
				}
				break;
			}
			case QEvent::EnabledChange: {
				if (isEnabled()) {
					m_triggerColor		= m_checkedColor;
					m_backgroundColor	= m_uncheckedColor;
				}
				else {
					m_triggerColor 		= m_disableCheckedColor;
					m_backgroundColor	= m_disableUncheckedColor;
				}
				update();
				break;
			}
			default: break;
		}

		return OverlayAbstractButton::event(event);
	}

	void ToggleButton::mousePressEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);

		if (!isEnabled()) return;

		QPoint pos = m_overlay->rect().center();

		QPainterPath path;
		RoundRipple* ripple = new RoundRipple(pos);
		QMargins margins	= QMargins(
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND,
				-RIPPLE_WIDGET_EXTEND);

		path.addRoundedRect(
				m_overlay->rect().marginsRemoved(margins),
				RECT_ANGLE_RADIUS,
				RECT_ANGLE_RADIUS);
		ripple->setUseClipPath(true);
		ripple->setClipPath(path);
		ripple->setOverlay(m_overlay);
		ripple->setColor(isChecked() ? m_checkedColor : m_uncheckedColor);
		ripple->setRadiusAnimationEndValue(qMax(height(), width()) * 0.4);
		ripple->setOpacityAnimationStartValue(0.8);

		m_overlay->addRipple(ripple);

		QAbstractButton::mousePressEvent(event);
	}

	void ToggleButton::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);

		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		QRectF rect = getWidgetRect().marginsRemoved(getMargins());

		paintWidget(&painter, rect);

		QPen pen;
		if (isEnabled()) {
			pen.setColor(isChecked() ? m_checkedTextColor : m_uncheckedTextColor);
		}
		else {
			pen.setColor(isChecked() ? m_unEnabledCheckedTextColor : m_unEnabledUncheckedTextColor);
		}

		painter.setPen(pen);
		painter.drawText(rect, Qt::AlignCenter, text());
	}

	void ToggleButton::paintWidget(QPainter *painter, const QRectF &rect_f)
	{
		painter->setPen(QPen(isEnabled() ? m_frameColor : m_disableFrameColor, 1));
		painter->setBrush(m_triggerColor);
		painter->drawRoundedRect(rect_f, RECT_ANGLE_RADIUS, RECT_ANGLE_RADIUS);

		QRectF angle 	= rect_f.marginsRemoved(QMargins(1, 1, 1, 1));
		qreal r			= qSqrt((qPow(angle.width(), 2) + qPow(angle.height(), 2))) * m_scale / 2;

		painter->setPen(QPen(m_backgroundColor, 1));
		painter->setBrush(m_backgroundColor);
		painter->drawEllipse(angle.center(), r, r);
	}

	void ToggleButton::init()
	{
		QFont font;
		font.setBold(true);
		font.setPointSize(10);
		setFont(font);

		m_scale = 1.0;
		m_checkedTextColor				= QColorConstants::White;
		m_uncheckedTextColor 			= QColor(0, 102, 180);
		m_unEnabledCheckedTextColor		= QColor(225, 225, 225);
		m_unEnabledUncheckedTextColor	= QColor(150, 150, 150);
		m_frameColor					= QColor(0, 102, 180);
		m_disableFrameColor				= QColor(180, 180, 180);
		m_hoverColor					= QColor(236, 236, 236);
		m_triggerColor					= QColor(0, 102, 180);
		m_backgroundColor				= QColor(247, 247, 247);
		m_checkedColor					= QColor(0, 102, 180);
		m_uncheckedColor				= QColor(247, 247, 247);
		m_disableCheckedColor			= QColor(180, 180, 180);
		m_disableUncheckedColor			= QColor(230, 230, 230);
		m_stateMachine					= new QStateMachine(this);
		m_checkedState					= new QState;
		m_unCheckedState				= new QState;

		setCheckable(true);

		m_stateMachine->addState(m_checkedState);
		m_stateMachine->addState(m_unCheckedState);
		m_stateMachine->setInitialState(m_unCheckedState);

		QSignalTransition* transition_ptr	= nullptr;
		QPropertyAnimation* animation_ptr	= nullptr;

		transition_ptr	= new QSignalTransition(this, &QAbstractButton::toggled);
		transition_ptr->setTargetState(m_unCheckedState);
		m_checkedState->addTransition(transition_ptr);

		animation_ptr	= new QPropertyAnimation(this, "scale");
		animation_ptr->setDuration(200);
		transition_ptr->addAnimation(animation_ptr);

		transition_ptr	= new QSignalTransition(this, &QAbstractButton::toggled);
		transition_ptr->setTargetState(m_checkedState);
		m_unCheckedState->addTransition(transition_ptr);

		animation_ptr	= new QPropertyAnimation(this, "scale");
		animation_ptr->setDuration(200);
		transition_ptr->addAnimation(animation_ptr);

		m_checkedState->assignProperty(this, "scale", 0.0);
		m_unCheckedState->assignProperty(this, "scale", 1.0);

		m_stateMachine->start();
		QCoreApplication::processEvents();
	}

}
