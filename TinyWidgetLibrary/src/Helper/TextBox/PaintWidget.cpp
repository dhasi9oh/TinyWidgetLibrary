//
// Created by 86186 on 2024/2/2.
//
#include "Helper/TextBox/PaintWidget.h"

void init();

namespace TinyWidgetLibrary
{

	PaintWidget::PaintWidget(QWidget *source, QWidget* parent)
			: QWidget(parent)
			, m_target(source)
	{
		init();
	}

	PaintWidget::~PaintWidget()
	{
	}

	qreal PaintWidget::getScale() const
	{
		return m_scale;
	}

	void PaintWidget::setScale(qreal scale)
	{
		m_scale = scale;
		update();
	}

	void PaintWidget::setTarget(QWidget *target)
	{
		m_target = target;
	}

	QWidget *PaintWidget::getTarget() const
	{
		return m_target;
	}

	void PaintWidget::setPaint(Paint *paint)
	{
		if (m_paint != nullptr) m_paint->deleteLater();

		m_paint = paint;
		m_paint->setSource(this);
		m_paint->setParent(this);
		update();
	}

	QColor PaintWidget::getFocusInFontColor() const
	{
		return m_focusInColor;
	}

	void PaintWidget::setFocusInFontColor(QColor color)
	{
		QPalette palette = m_target->palette();
		palette.setColor(QPalette::PlaceholderText, color);
		m_target->setPalette(palette);
		m_focusInColor = color;
		update();
	}

	QColor PaintWidget::getFocusOutFontColor() const
	{
		return m_focusOutColor;
	}

	void PaintWidget::setFocusOutFontColor(QColor color)
	{
		QPalette palette = m_target->palette();
		palette.setColor(QPalette::PlaceholderText, color);
		m_target->setPalette(palette);
		m_focusOutColor = color;
		update();
	}

	QColor PaintWidget::getFrameColor() const
	{
		return m_paint->getFrameColor();
	}

	void PaintWidget::setFrameColor(QColor color)
	{
		m_paint->setFrameColor(color);
	}

	QColor PaintWidget::getTargetColor() const
	{
		return m_paint->getColor();
	}

	void PaintWidget::setTargetColor(QColor color)
	{
		m_paint->setColor(color);
	}

	QColor PaintWidget::getBackgroundColor() const
	{
		return m_paint->getBackgroundColor();
	}

	void PaintWidget::setBackgroundColor(QColor color)
	{
		m_paint->setBackgroundColor(color);
	}

	bool PaintWidget::eventFilter(QObject *watched, QEvent *event)
	{
		if (watched == m_target) {
			switch (event->type()) {
				case QEvent::FocusIn: {
					setFocusInFontColor(m_focusInColor);
					break;
				}
				case QEvent::FocusOut: {
					setFocusOutFontColor(m_focusOutColor);
					break;
				}
				default:
					break;
			}
		}

		return QObject::eventFilter(watched, event);
	}

	void PaintWidget::paintEvent(QPaintEvent *event)
	{
		QWidget::paintEvent(event);
		QPainter painter(this);
		(*m_paint)(&painter);
	}

	void PaintWidget::init()
	{
		m_scale			= 0.0;
		m_startState	= new QState;
		m_endState		= new QState;
		m_stateMachine 	= new QStateMachine(this);
		m_paint			= new RisePaint(this, this);
		m_focusInColor	= Qt::white;
		m_focusOutColor	= QColor(0, 102, 180);

		m_stateMachine->addState(m_startState);
		m_stateMachine->addState(m_endState);
		m_stateMachine->setInitialState(m_startState);

		QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		policy.setVerticalStretch(0);
		policy.setHorizontalStretch(0);
		policy.setHeightForWidth(m_target->sizePolicy().hasHeightForWidth());
		m_target->setParent(this);
		m_target->setStyleSheet(default_qss);
		m_target->setSizePolicy(policy);
		m_target->installEventFilter(this);

		auto layout = new QVBoxLayout(this);
		layout->setSpacing(0);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_target);

		QEventTransition * transition = nullptr;

		transition = new QEventTransition(m_target, QEvent::FocusIn);
		transition->setTargetState(m_endState);
		m_startState->addTransition(transition);

		transition = new QEventTransition(m_target, QEvent::FocusOut);
		transition->setTargetState(m_startState);
		m_endState->addTransition(transition);

		QPropertyAnimation * animation = nullptr;

		animation = new QPropertyAnimation(this, "scale", this);
		animation->setDuration(200);
		m_stateMachine->addDefaultAnimation(animation);

		m_startState->assignProperty(this, "scale", 0.0);
		m_endState->assignProperty(this, "scale", 1.0);

		m_stateMachine->start();
		QCoreApplication::processEvents();
	}

}