//
// Created by 86186 on 2024/2/15.
//

#include "PopupBox/SizeFixedDialog.h"

namespace TinyWidgetLibrary
{


	SizeFixedDialog::SizeFixedDialog(QWidget *parent)
		: QWidget(parent)
	{
		init();
	}

	SizeFixedDialog::~SizeFixedDialog()
	{
	}

	void SizeFixedDialog::setStartOpacity(qreal opacity)
	{
		m_startState->assignProperty(m_coverWidget, "opacity", opacity);
	}

	void SizeFixedDialog::setEndOpacity(qreal opacity)
	{
		m_endState->assignProperty(m_coverWidget, "margin_top", opacity);
	}

	void SizeFixedDialog::setStartMarginTop(qint32 margin_top_width)
	{
		m_startState->assignProperty(m_coverWidget, "opacity", margin_top_width);
	}

	void SizeFixedDialog::setEndMarginTop(qint32 margin_top_width)
	{
		m_endState->assignProperty(m_coverWidget, "margin_top", margin_top_width);
	}

	void SizeFixedDialog::setMarginWidth(qint32 margin_top_width, qint32 margin_bottom_width)
	{
		layout()->setContentsMargins(
				WIDGET_LEFT_MARGIN_WIDTH,
				margin_top_width,
				WIDGET_RIGHT_MARGIN_WIDTH,
				margin_bottom_width
				);
	}

	void SizeFixedDialog::addWidget(QWidget *widget)
	{
		QLayout *layout = m_targetWidget->layout();
		if (layout == nullptr) {
			layout = new QVBoxLayout(m_targetWidget);
			layout->setAlignment(widget, Qt::AlignCenter);
		}

		layout->addWidget(widget);
	}

	void SizeFixedDialog::shown()
	{
		m_coverWidget->setShowMode(true);
		m_coverWidget->makeOpaque();
		m_stackedLayout->setCurrentIndex(TARGET_WIDGET_INDEX);
	}

	void SizeFixedDialog::hidden()
	{
		m_coverWidget->makeTransparent();
	}

	void SizeFixedDialog::init()
	{
		m_stateMachine	= new QStateMachine(this);
		m_startState	= new QState;
		m_middleState	= new QState;
		m_endState		= new QState;

		auto *widget	= new QWidget(this);
		auto *layout	= new QVBoxLayout(this);
		auto *effect	= new QGraphicsDropShadowEffect;

		effect->setColor(QColor(0, 0, 0, 200));
		effect->setBlurRadius(64);
		effect->setOffset(0, 8);
		widget->setGraphicsEffect(effect);

		setLayout(layout);
		resize(400, 300);
		layout->addWidget(widget);
		layout->setAlignment(widget, Qt::AlignCenter);
		setMarginWidth(0, 100);

		m_stackedLayout	= new QStackedLayout(widget);
		m_targetWidget	= new TargetWidget();
		m_coverWidget	= new CoverWidget(this, m_targetWidget, widget);

		m_stackedLayout->addWidget(m_coverWidget);
		m_stackedLayout->addWidget(m_targetWidget);
		m_stackedLayout->setCurrentWidget(m_targetWidget);
		m_stackedLayout->setCurrentIndex(COVER_WIDGET_INDEX);
		widget->setLayout(m_stackedLayout);

		setAttribute(Qt::WA_DeleteOnClose);
		setWindowFlag(Qt::WindowType::FramelessWindowHint);

		m_stateMachine->addState(m_startState);
		m_stateMachine->addState(m_middleState);
		m_stateMachine->addState(m_endState);
		m_stateMachine->setInitialState(m_startState);

		m_startState->assignProperty(m_coverWidget, "opacity", 0.0);
		m_startState->assignProperty(m_coverWidget, "margin_top", 0.0);

		m_middleState->assignProperty(m_coverWidget, "opacity", 1.0);
		m_middleState->assignProperty(m_coverWidget, "margin_top", 50.0);

		m_endState->assignProperty(m_coverWidget, "opacity", 0.0);
		m_endState->assignProperty(m_coverWidget, "margin_top", 0.0);

		QSignalTransition* transition = nullptr;

		transition	= new QSignalTransition(this, &SizeFixedDialog::showTarget);
		transition->setTargetState(m_middleState);
		m_startState->addTransition(transition);

		transition	= new QSignalTransition(this, &SizeFixedDialog::hideTarget);
		transition->setTargetState(m_endState);
		m_middleState->addTransition(transition);

		connect(m_middleState, &QState::propertiesAssigned,
				this, &SizeFixedDialog::shown);

		connect(m_endState, &QState::propertiesAssigned,
				this, &SizeFixedDialog::hidden);

		QPropertyAnimation* animation = nullptr;

		animation	= new QPropertyAnimation(m_coverWidget, "opacity");
		animation->setDuration(400);
		m_stateMachine->addDefaultAnimation(animation);

		animation	= new QPropertyAnimation(m_coverWidget, "margin_top");
		animation->setDuration(400);
		m_stateMachine->addDefaultAnimation(animation);

		m_stateMachine->start();
		QCoreApplication::processEvents();

		resize(720, 480);
	}

	void SizeFixedDialog::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);

		QRect rect1 = rect();
		QPainter painter(this);

		painter.setBrush(QColor(43, 45, 48, 150));
		painter.setPen(Qt::NoPen);
		painter.drawRect(rect1);
	}

} // TinyWidgetLibrary