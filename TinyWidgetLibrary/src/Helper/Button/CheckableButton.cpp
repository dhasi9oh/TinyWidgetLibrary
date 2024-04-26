//
// Created by 86186 on 2024/2/4.
//
#include "Helper/Button/CheckableButton.h"


namespace TinyWidgetLibrary
{
	CheckableButton::CheckableButton(QWidget *parent)
		: OverlayAbstractButton(parent)
	{
		init();
	}

	CheckableButton::~CheckableButton()
	{
	}

	void CheckableButton::setTextAlignment(CheckableButton::EAlignment alignment)
	{
		m_alignment = alignment;
		update();
	}

	CheckableButton::EAlignment CheckableButton::getTextAlignment() const
	{
		return m_alignment;
	}

	void CheckableButton::setScale(qreal scale)
	{
		m_scale = scale;
		update();
	}

	qreal CheckableButton::getScale() const
	{
		return m_scale;
	}

	void CheckableButton::setTextColor(const QColor &color)
	{
		m_textColor = color;
		update();
	}

	QColor CheckableButton::getTextColor() const
	{
		return m_textColor;
	}

	void CheckableButton::setFrameColor(const QColor &color)
	{
		m_frameColor = color;
		update();
	}

	QColor CheckableButton::getFrameColor() const
	{
		return m_frameColor;
	}
	void CheckableButton::setHoverColor(const QColor &color)
	{
		m_hoverColor = color;
		update();
	}

	QColor CheckableButton::getHoverColor() const
	{
		return m_hoverColor;
	}

	void CheckableButton::setCheckedColor(const QColor &color)
	{
		m_checkedColor = color;
		m_triggerColor = color;
		update();
	}

	QColor CheckableButton::getCheckedColor() const
	{
		return m_checkedColor;
	}

	void CheckableButton::setUncheckedColor(const QColor &color)
	{
		m_uncheckedColor = color;
		update();
	}

	QColor CheckableButton::getUncheckedColor() const
	{
		return m_uncheckedColor;
	}

	void CheckableButton::setDisableCheckedColor(const QColor &color)
	{
		m_disableCheckedColor = color;
		update();
	}

	QColor CheckableButton::getDisableCheckedColor() const
	{
		return m_disableCheckedColor;
	}

	void CheckableButton::setDisableUncheckedColor(const QColor &color)
	{
		m_disableUncheckedColor = color;
		update();
	}

	QColor CheckableButton::getDisableUncheckedColor() const
	{
		return m_disableUncheckedColor;
	}

	void CheckableButton::setCheckRippleColor(const QColor &color)
	{
		m_checkRippleColor = color;
	}

	void CheckableButton::setUncheckRippleColor(const QColor &color)
	{
		m_uncheckRippleColor = color;
	}

	void CheckableButton::setCheckedStateValue(qreal value)
	{
		m_checkedState->assignProperty(this, "scale", value);
	}

	void CheckableButton::setUncheckedStateValue(qreal value)
	{
		m_uncheckedState->assignProperty(this, "scale", value);
	}

	void CheckableButton::setDisableCheckedStateValue(qreal value)
	{
		m_disableCheckedState->assignProperty(this, "scale", value);
	}

	void CheckableButton::setDisableUncheckedStateValue(qreal value)
	{
		m_disableUncheckedState->assignProperty(this, "scale", value);
	}

	bool CheckableButton::event(QEvent *event)
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

	void CheckableButton::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);
		
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		int margin_right 	= getMargins().right();
		QRectF	rect		= getWidgetRect();
		qint32  w			= rect.width();
		QSize	size		= geometry().size();
		QRectF	rectangle	= QRectF(
				w + margin_right + CHARACTER_INTERVAL,
				0,
				size.width() - w - margin_right,
				size.height()
				);

		paintWidget(&painter, rect);

		QPen pen;
		pen.setColor(isEnabled() ? m_textColor : m_unEnbledTextColor);
		painter.setPen(pen);

		if (m_alignment == EAlignment::Left) {
			painter.drawText(rectangle, Qt::AlignLeft | Qt::AlignVCenter, text());
		}
		else {
			painter.drawText(rectangle, Qt::AlignRight | Qt::AlignVCenter, text());
		}
	}

	void CheckableButton::init()
	{
		m_scale					= 0.0;
		m_stateMachine			= new QStateMachine(this);
		m_checkedState			= new QState;
		m_uncheckedState		= new QState;
		m_disableCheckedState	= new QState;
		m_disableUncheckedState = new QState;
		m_checkedTransition 	= new QSignalTransition(this, &QAbstractButton::toggled);
		m_uncheckedTransition 	= new QSignalTransition(this, &QAbstractButton::toggled);
		m_alignment				= EAlignment::Left;
		m_textColor				= Qt::black;
		m_unEnbledTextColor		= QColor(150, 150, 150);
		m_frameColor			= QColor(130, 130, 130);
		m_hoverColor			= QColor(236, 236, 236);
		m_triggerColor			= QColor(0, 102, 180);
		m_backgroundColor		= QColor(247, 247, 247);
		m_checkedColor			= QColor(0, 102, 180);
		m_uncheckedColor		= QColor(247, 247, 247);
		m_disableCheckedColor	= QColor(165, 165, 165);
		m_disableUncheckedColor	= QColor(230, 230, 230);

		setCheckable(true);

		m_stateMachine->addState(m_checkedState);
		m_stateMachine->addState(m_uncheckedState);
		m_stateMachine->addState(m_disableCheckedState);
		m_stateMachine->addState(m_disableUncheckedState);
		m_stateMachine->setInitialState(m_uncheckedState);

		m_checkedTransition->setTargetState(m_uncheckedState);
		m_checkedState->addTransition(m_checkedTransition);

		m_checkedTransitionAnimation = new QPropertyAnimation(this, "scale");
		m_checkedTransitionAnimation->setDuration(200);
		m_checkedTransition->addAnimation(m_checkedTransitionAnimation);

		m_uncheckedTransition->setTargetState(m_checkedState);
		m_uncheckedState->addTransition(m_uncheckedTransition);

		m_uncheckedTransitionAnimation = new QPropertyAnimation(this, "scale");
		m_uncheckedTransitionAnimation->setDuration(200);
		m_uncheckedTransition->addAnimation(m_uncheckedTransitionAnimation);

		QAbstractTransition* ptr = nullptr;

		ptr = new QSignalTransition(this, &QAbstractButton::toggled);
		ptr->setTargetState(m_disableCheckedState);
		m_disableUncheckedState->addTransition(ptr);

		ptr = new QSignalTransition(this, &QAbstractButton::toggled);
		ptr->setTargetState(m_disableUncheckedState);
		m_disableCheckedState->addTransition(ptr);

		ptr = new QEventTransition(this, QEvent::EnabledChange);
		ptr->setTargetState(m_disableCheckedState);
		m_checkedState->addTransition(ptr);

		ptr = new QEventTransition(this, QEvent::EnabledChange);
		ptr->setTargetState(m_disableUncheckedState);
		m_uncheckedState->addTransition(ptr);

		ptr = new QEventTransition(this, QEvent::EnabledChange);
		ptr->setTargetState(m_checkedState);
		m_disableCheckedState->addTransition(ptr);

		ptr = new QEventTransition(this, QEvent::EnabledChange);
		ptr->setTargetState(m_uncheckedState);
		m_disableUncheckedState->addTransition(ptr);

		m_checkedState->assignProperty(this, "scale", 1.0);
		m_uncheckedState->assignProperty(this, "scale", 0.0);
		m_disableCheckedState->assignProperty(this, "scale", 1.5);
		m_disableUncheckedState->assignProperty(this, "scale", 0.0);

		m_stateMachine->start();
		QCoreApplication::processEvents();
	}

}