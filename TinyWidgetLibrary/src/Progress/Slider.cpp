//
// Created by 86186 on 2024/2/12.
//
#include "Progress/Slider.h"

namespace TinyWidgetLibrary
{
	Slider::Slider(QWidget *parent)
		: QAbstractSlider(parent)
	{
		init();
	}

	Slider::~Slider()
	{
	}

	void Slider::setDirection(Slider::Direction direction)
	{
		if (m_direction == direction) return;

		auto l = qobject_cast<QBoxLayout*>(layout());

		if (l == nullptr) return;

		switch (direction) {
			case Direction::TopToBottom: {
				setOrientation(Qt::Vertical);
				setInvertedAppearance(true);
				l->setDirection(QBoxLayout::TopToBottom);
				break;
			}
			case Direction::BottomToTop: {
				setOrientation(Qt::Vertical);
				setInvertedAppearance(false);
				l->setDirection(QBoxLayout::BottomToTop);
				break;
			}
			case Direction::LeftToRight: {
				setOrientation(Qt::Horizontal);
				setInvertedAppearance(false);
				l->setDirection(QBoxLayout::LeftToRight);
				break;
			}
			case Direction::RightToLeft: {
				setOrientation(Qt::Horizontal);
				setInvertedAppearance(true);
				l->setDirection(QBoxLayout::RightToLeft);
				break;
			}
			default:
				break;
		}

		m_direction = direction;
		onSliderMoved(sliderPosition());
	}

	Slider::Direction Slider::getDirection() const
	{
		return m_direction;
	}

	void Slider::setCenterColor(const QColor &color)
	{
		if (m_sliderWidget != nullptr)
			m_sliderWidget->setCenterColor(color);
	}

	QColor Slider::getCenterColor() const
	{
		return m_sliderWidget->getCenterColor();
	}

	void Slider::setProgressColor(const QColor &color)
	{
		m_progressColor = color;
		update();
	}

	QColor Slider::getProgressColor() const
	{
		return m_progressColor;
	}

	bool Slider::event(QEvent *event)
	{
		switch (event->type()) {
			case QEvent::HoverEnter: {
				emit m_floatWindow->showTarget();
				break;
			}
			case QEvent::HoverLeave: {
				emit m_floatWindow->hideTarget();
				break;
			}
			case QEvent::Resize: {
				onSliderMoved(sliderPosition());
				break;
			}
			default:
				break;
		}

		return QAbstractSlider::event(event);
	}

	void Slider::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);

		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		painter.setRenderHint(QPainter::Antialiasing);

		qint32 w = width();
		qint32 h = height();
		QColor fill_color = m_progressColor;
		QColor unfill_color(200, 200, 200);

		qint32 x, y;
		qint32 w1, h1;
		qint32 w2, h2;

		if (orientation() == Qt::Horizontal) {
			x = SLIDER_MARGIN;
			y = (h - PROGRESS_HEIGHT) / 2;
			w1 = w - 2 * SLIDER_MARGIN;
			w2 = sliderPosition() * (w - 2 * SLIDER_MARGIN) / maximum();
			h1 = PROGRESS_HEIGHT;
			h2 = PROGRESS_HEIGHT;
			if (invertedAppearance()) {
				w2 = w - 2 * SLIDER_MARGIN - w2;
				qSwap(fill_color, unfill_color);
			}
		}
		else {
			x = (w - PROGRESS_HEIGHT) / 2;
			y = SLIDER_MARGIN;
			w1 = PROGRESS_HEIGHT;
			w2 = PROGRESS_HEIGHT;
			h1 = h  - 2 * SLIDER_MARGIN;
			h2 = (h - 2 * SLIDER_MARGIN) * (1 - sliderPosition() * 1.0 / maximum());
			if (!invertedAppearance()) {
				qSwap(fill_color, unfill_color);
			}
			else {
				h2 = h - 2 * SLIDER_MARGIN - h2;
			}
		}

		qint32 r = PROGRESS_HEIGHT / 2;

		painter.setBrush(unfill_color);
		painter.drawRoundedRect(x, y, w1, h1, r, r);

		painter.setBrush(fill_color);
		painter.drawRoundedRect(x, y, w2, h2, r, r);
	}

	void Slider::mouseMoveEvent(QMouseEvent *event)
	{
		if (isSliderDown()) {
			qint32 value;

			if (orientation() == Qt::Horizontal) {
				value = maximum() * event->pos().x() * 1.0 / (width() - SLIDER_LENGTH);
			}
			else {
				value = maximum() * (height() - event->pos().y()) * 1.0 / height();
			}

			if (invertedAppearance()) {
				value = maximum() - value;
			}

			setSliderPosition(value);
		}

		QAbstractSlider::mouseMoveEvent(event);
	}

	void Slider::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton) {
			setSliderDown(true);
		}

		QAbstractSlider::mousePressEvent(event);
	}

	void Slider::mouseReleaseEvent(QMouseEvent *event)
	{
		QAbstractSlider::mouseReleaseEvent(event);

		if (event->button() == Qt::LeftButton) {
			setSliderDown(false);
		}
	}

	void Slider::init()
	{
		auto layout		= new QBoxLayout(QBoxLayout::LeftToRight);
		m_progressColor = QColor(0, 102, 180);
		m_sliderWidget	= new SliderWidget(this);
		m_floatWindow	= new FloatWindow(m_sliderWidget);
		m_leftSpacer	= new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Preferred);
		m_rightSpacer	= new QSpacerItem(200, 0, QSizePolicy::Expanding, QSizePolicy::Preferred);
		m_label			= new QLabel(m_floatWindow);

		setLayout(layout);
		setAttribute(Qt::WA_Hover);
		setDirection(Direction::LeftToRight);
		setWindowFlag(Qt::FramelessWindowHint);

		layout->setContentsMargins(0, 0, 0, 0);
		layout->setSpacing(0);
		layout->addItem(m_leftSpacer);
		layout->addWidget(m_sliderWidget, 0, Qt::AlignCenter);
		layout->addItem(m_rightSpacer);

		QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setHeightForWidth(m_sliderWidget->sizePolicy().hasHeightForWidth());
		m_sliderWidget->setSizePolicy(sizePolicy1);
		m_sliderWidget->setFixedSize(QSize(FLOAT_WINDOW_LENGTH, FLOAT_WINDOW_LENGTH));

		m_label->setNum(value());
		m_label->setAlignment(Qt::AlignCenter);
		m_label->setStyleSheet("QLabel{color:rgb(0, 102, 180);}");
		m_label->setFixedSize(QSize(FLOAT_WINDOW_LENGTH, FLOAT_WINDOW_LENGTH));

		m_floatWindow->setShowSize(QSize(FLOAT_WINDOW_LENGTH, FLOAT_WINDOW_LENGTH));
		m_floatWindow->addWidget(m_label);

		connect(this, &QAbstractSlider::sliderMoved, [&](int pos) { m_label->setNum(pos); });
		connect(this, &QAbstractSlider::sliderMoved, this, &Slider::onSliderMoved);

		setFixedSize(200, 100);
		m_floatWindow->show();
	}

	void Slider::onSliderMoved(qint32 position)
	{
		qint32 h1 = height();
		qint32 w1 = position * (width() - SLIDER_LENGTH) / maximum();
		qint32 h2 = position * (height() - SLIDER_LENGTH) / maximum();
		qint32 w2 = width();

		switch (m_direction) {
			case Direction::TopToBottom:
			case Direction::BottomToTop: {
				m_leftSpacer->changeSize(w2, h2,
						QSizePolicy::Preferred, QSizePolicy::Fixed);
				m_rightSpacer->changeSize(w2, height() - h2 + SLIDER_LENGTH,
						QSizePolicy::Preferred, QSizePolicy::Expanding);
				break;
			}
			case Direction::LeftToRight:
			case Direction::RightToLeft: {
				m_leftSpacer->changeSize(w1, h1,
						QSizePolicy::Fixed, QSizePolicy::Preferred);
				m_rightSpacer->changeSize(width() - w1 - SLIDER_LENGTH, h1,
						QSizePolicy::Expanding, QSizePolicy::Preferred);
				break;
			}
			default:
				break;
		}

		layout()->invalidate();
	}

}