//
// Created by 86186 on 2024/2/15.
//

#include "PopupBox/FloatWindow.h"

namespace TinyWidgetLibrary
{
	FloatWindow::FloatWindow(QWidget *parent)
		: PointFixedWidget(parent)
	{
		init();
	}

	FloatWindow::~FloatWindow()
	{
	}

	void FloatWindow::setWindowSize(QSize size)
	{
		setSize(size);
	}

	void FloatWindow::setShowSize(QSize size)
	{
		m_targetSize = size;
		m_middleState->assignProperty(this, "window_size", size);

		auto orientation = getOrientation();
		if (orientation == PointFixedWidget::Orientation::TOP
		|| orientation == PointFixedWidget::Orientation::BOTTOM) {
			m_startState->assignProperty(this, "window_size", QSize(size.width(), 0));
			m_endState->assignProperty(this, "window_size", QSize(size.width(), 0));
		}
		else {
			m_startState->assignProperty(this, "window_size", QSize(0, size.height()));
			m_endState->assignProperty(this, "window_size", QSize(0, size.height()));
		}

		m_stateMachine->start();
		QCoreApplication::processEvents();
	}

	void FloatWindow::addWidget(QWidget *widget)
	{
		if (widget == nullptr) return;

		widget->setParent(this);
		widget->adjustSize();
		widget->move(0, 0);
		setShowSize(widget->size());
	}

	void FloatWindow::init()
	{
		setAttribute(Qt::WA_TranslucentBackground);
		setFixedSize(QSize(0, 0));

		m_stateMachine	= new QStateMachine(this);
		m_startState	= new QState;
		m_middleState	= new QState;
		m_endState		= new QState;

		m_stateMachine->addState(m_startState);
		m_stateMachine->addState(m_middleState);
		m_stateMachine->addState(m_endState);
		m_stateMachine->setInitialState(m_startState);

		QSignalTransition *ptr = nullptr;

		ptr = new QSignalTransition(this, &FloatWindow::showTarget);
		ptr->setTargetState(m_middleState);
		m_startState->addTransition(ptr);
		
		ptr = new QSignalTransition(this, &FloatWindow::hideTarget);
		ptr->setTargetState(m_endState);
		m_middleState->addTransition(ptr);

		ptr = new QSignalTransition(this, &FloatWindow::showTarget);
		ptr->setTargetState(m_middleState);
		m_endState->addTransition(ptr);

		QPropertyAnimation *animation = nullptr;

		animation = new QPropertyAnimation(this, "window_size");
		animation->setDuration(300);
		m_stateMachine->addDefaultAnimation(animation);

		m_startState->assignProperty(this, "window_size", QSize(0, 0));
		m_middleState->assignProperty(this, "window_size", QSize(0, 0));
		m_endState->assignProperty(this, "window_size", QSize(0, 0));
	}

} // TinyWidgetLibrary