//
// Created by 86186 on 2024/2/22.
//

#include "Helper/SliderWidget/SliderWidget.h"

namespace TinyWidgetLibrary
{
	SliderWidget::SliderWidget(QWidget *parent)
		: QWidget(parent)
		, m_scale(0.0)
	{
		init();
	}

	SliderWidget::~SliderWidget()
	{
	}

	void SliderWidget::setScale(qreal scale)
	{
		m_scale = scale;
		update();
	}

	qreal SliderWidget::getScale() const
	{
		return m_scale;
	}

	void SliderWidget::setCenterColor(const QColor &color)
	{
		m_centerColor = color;
		update();
	}

	QColor SliderWidget::getCenterColor() const
	{
		return m_centerColor;
	}

	void SliderWidget::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);

		QRectF r	= rect();
		qreal rx	= r.width() * m_scale * 0.5;
		qreal ry	= r.height() * m_scale * 0.5;
		QPainter painter(this);

		painter.setPen(Qt::NoPen);
		painter.setRenderHint(QPainter::Antialiasing);

		painter.setBrush(Qt::white);
		painter.drawEllipse(r);

		painter.setBrush(m_centerColor);
		painter.drawEllipse(r.center(), rx, ry);
	}

	void SliderWidget::init()
	{
		setAttribute(Qt::WA_Hover);
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlag(Qt::FramelessWindowHint);

		m_centerColor	= QColor(0, 102, 180);
		m_stateMachine	= new QStateMachine(this);
		m_startState	= new QState;
		m_endState		= new QState;

		m_stateMachine->addState(m_startState);
		m_stateMachine->addState(m_endState);
		m_stateMachine->setInitialState(m_startState);

		QEventTransition *transition = nullptr;

		transition = new QEventTransition(this, QEvent::HoverEnter);
		transition->setTargetState(m_endState);
		m_startState->addTransition(transition);

		transition = new QEventTransition(this, QEvent::HoverLeave);
		transition->setTargetState(m_startState);
		m_endState->addTransition(transition);

		auto *animation = new QPropertyAnimation(this, "scale");
        animation->setDuration(250);
		m_stateMachine->addDefaultAnimation(animation);

		m_startState->assignProperty(this, "scale", 0.6);
		m_endState->assignProperty(this, "scale", 0.75);

		m_stateMachine->start();
		QApplication::processEvents();
	}

} // TinyWidgetLibrary