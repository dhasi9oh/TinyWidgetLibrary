#include "PopupBox/MessageBoxHint.h"
//
// Created by 86186 on 2024/2/20.
//

#include "PopupBox/MessageBoxHint.h"

namespace TinyWidgetLibrary
{

	MessageBoxHint::MessageBoxHint(QWidget *parent)
		: QDialog(parent)
		, b_closing(false)
	{
		init();
	}

	MessageBoxHint::~MessageBoxHint()
	{
	}

	QLabel *MessageBoxHint::getLabelPtr()
	{
		return m_label;
	}

	QColor MessageBoxHint::getFrameColor() const
	{
		return m_frameColor;
	}

	void MessageBoxHint::setFrameColor(const QColor& color)
	{
		m_frameColor = color;
		update();
	}

	qreal MessageBoxHint::getOpacity() const
	{
		return windowOpacity();
	}

	void MessageBoxHint::setOpacity(qreal opacity)
	{
		setWindowOpacity(opacity);
		update();
	}

	void MessageBoxHint::setX(qint32 x)
	{
		move(x, y());
	}

	void MessageBoxHint::setY(qint32 y)
	{
		move(x(), y);
	}

	void MessageBoxHint::setText(const QString &text)
	{
		m_label->setText(text);
	}

	QSize MessageBoxHint::sizeHint() const
	{
		if (m_label->text().isEmpty()) {
			return QSize(WIDGET_DEFAULT_WIDTH, WIDGET_DEFAULT_HEIGHT);
		}

		QSize size = fontMetrics().size(Qt::TextShowMnemonic, m_label->text());
		qint32 h = size.height();
		qint32 w = size.width() + 20;

		w = qMax(w, WIDGET_DEFAULT_WIDTH);
		h = qMax(h, WIDGET_DEFAULT_HEIGHT);

		return QSize(w, h);
	}

	void MessageBoxHint::showEvent(QShowEvent *event)
	{
		updateStartPos();
		QDialog::showEvent(event);

		emit readyShow();
	}

	void MessageBoxHint::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);

		QPen pen(m_frameColor);
		pen.setWidth(2);

		QPainter painter(this);
		painter.setPen(pen);
		painter.setBrush(QColor(247, 247, 247));
		painter.drawRect(rect());
	}

	void MessageBoxHint::init()
	{
		setWindowOpacity(0.0);
		setAttribute(Qt::WA_DeleteOnClose);
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlag(Qt::WindowType::FramelessWindowHint);

		m_frameColor	= QColor(0, 102, 180);
		m_widget		= new QWidget;
		auto vlayout	= new QVBoxLayout;

		setLayout(vlayout);
		vlayout->addWidget(m_widget);

		auto hlayout	= new QHBoxLayout;
		m_label			= new QLabel(m_widget);
		m_button		= new QPushButton(m_widget);

		QSizePolicy size_policy(QSizePolicy::Maximum, QSizePolicy::Maximum);
		size_policy.setHeightForWidth(m_button->sizePolicy().hasHeightForWidth());

		QPalette pe;
		pe.setColor(QPalette::WindowText,QColor(0, 102, 180));
		m_label->setPalette(pe);

		QString qss = "QPushButton {\n"
					 "\tborder: none;\n"
					 "\tborder-radius: 8px;\n"
					 "\tbackground: transparent;\n"
					 "\ticon: url(:/img/guanbi.png);\n"
					 "}\n"
					 "\n"
					 "QPushButton:hover {\n"
					 "\tbackground: rgb(199, 64, 48);\n"
					 "\ticon: url(:/img/guanbi_.png);\n"
					 "}\n"
					 "\n"
					 "QPushButton:pressed {\n"
					 "\tbackground: rgb(199, 80, 60);\n"
					 "\ticon: url(:/img/guanbi_.png);\n"
					 "}";

		m_button->setStyleSheet(qss);
		m_button->setIconSize(QSize(20, 20));
		m_button->setSizePolicy(size_policy);
		m_button->setMaximumSize(50, 50);
		m_widget->setWindowOpacity(0.0);
		m_widget->setLayout(hlayout);
		hlayout->addWidget(m_label);
		hlayout->addWidget(m_button);
		hlayout->setContentsMargins(10, 0, 0, 0);

		QGraphicsDropShadowEffect *effect = nullptr;
		effect = new QGraphicsDropShadowEffect;
		effect->setColor(QColor(0, 0, 0, 200));
		effect->setBlurRadius(36);
		effect->setOffset(0, 8);
		setGraphicsEffect(effect);

		m_timer			= new QTimer(this);
		m_machine		= new QStateMachine(this);
		m_startState	= new QState;
		m_middleState	= new QState;
        m_endState		= new QState;

		m_machine->addState(m_startState);
		m_machine->addState(m_middleState);
		m_machine->addState(m_endState);
		m_machine->setInitialState(m_startState);

		QSignalTransition *transition = nullptr;

		transition = new QSignalTransition(this, &MessageBoxHint::readyShow);
		transition->setTargetState(m_middleState);
		m_startState->addTransition(transition);

		transition = new QSignalTransition(this, &MessageBoxHint::readyHide);
		transition->setTargetState(m_endState);
		m_middleState->addTransition(transition);

		QPropertyAnimation *animation = nullptr;

		animation = new QPropertyAnimation(this, "opacity");
		animation->setDuration(400);
		m_machine->addDefaultAnimation(animation);

		animation = new QPropertyAnimation(this, "window_x");
		animation->setDuration(400);
		m_machine->addDefaultAnimation(animation);

		animation = new QPropertyAnimation(this, "window_y");
		animation->setDuration(400);
		m_machine->addDefaultAnimation(animation);

		m_timer->setInterval(5000);

		connect(m_middleState, &QState::propertiesAssigned,
				[&] { m_timer->start(); });

		connect(m_timer, &QTimer::timeout,
				this, &MessageBoxHint::triggerReadyHide);

		connect(m_button, &QPushButton::clicked,
				this, &MessageBoxHint::triggerReadyHide);

		connect(m_endState, &QState::propertiesAssigned,
				this, &MessageBoxHint::close);

		m_startState->assignProperty(this, "opacity", 0.0);
		m_startState->assignProperty(this, "window_y", 0);

		m_middleState->assignProperty(this, "opacity", 1.0);
		m_middleState->assignProperty(this, "window_y", 100);

		m_endState->assignProperty(this, "opacity", 0.0);
		m_endState->assignProperty(this, "window_y", 200);

		m_machine->start();
		QCoreApplication::processEvents();
	}

	void MessageBoxHint::updateStartPos()
	{
		QScreen *ptr	= QApplication::primaryScreen();
		qint32 window_x = (ptr->size().width() - QWidget::width()) / 2;

		m_startState->assignProperty(this, "window_x", window_x);
		m_middleState->assignProperty(this, "window_x", window_x);
		m_endState->assignProperty(this, "window_x", window_x);
		move(window_x, y());
	}

	void MessageBoxHint::triggerReadyHide()
	{
		if (!b_closing) {
			b_closing = true;
			emit readyHide();
		}
	}

}