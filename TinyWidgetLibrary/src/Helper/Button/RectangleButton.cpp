
// Created by 86186 on 2024/2/7.
//
#include "Helper/Button/RectangleButton.h"

namespace TinyWidgetLibrary
{
	RectangleButton::RectangleButton(QWidget *parent)
		: OverlayAbstractButton(parent)
	{
		init();
	}

	RectangleButton::~RectangleButton()
	{
	}

	void RectangleButton::init()
	{
		m_textColor					= QColorConstants::White;
		m_unEnbledTextColor 		= QColor(150, 150, 150);
		m_frameColor				= QColor(0, 102, 180);
		m_hoverColor				= QColor(0, 90, 150);
		m_backgroundColor			= QColor(0, 102, 180);
		m_backupBackgroundColor		= QColor(0, 102, 180);
		m_disableBackgroundColor	= QColor(165, 165, 165);
		m_pressColor				= QColor(10, 110, 180);
	}

	void RectangleButton::setTextColor(const QColor &color)
	{
		m_textColor = color;
	}

	QColor RectangleButton::getTextColor() const
	{
		return m_textColor;
	}

	void RectangleButton::setUnEnabledTextColor(const QColor &color)
	{
		m_unEnbledTextColor = color;
	}

	QColor RectangleButton::getUnEnabledTextColor() const
	{
		return m_unEnbledTextColor;
	}

	void RectangleButton::setFrameColor(const QColor &color)
	{
		m_frameColor = color;
	}

	QColor RectangleButton::getFrameColor() const
	{
		return m_frameColor;
	}

	void RectangleButton::setHoverColor(const QColor &color)
	{
		m_hoverColor = color;
	}

	QColor RectangleButton::getHoverColor() const
	{
		return m_hoverColor;
	}

	void RectangleButton::setBackgroundColor(const QColor &color)
	{
		m_backupBackgroundColor = color;
	}

	QColor RectangleButton::getBackgroundColor() const
	{
		return m_backupBackgroundColor;
	}

	void RectangleButton::setDisableBackgroundColor(const QColor &color)
	{
		m_disableBackgroundColor = color;
	}

	QColor RectangleButton::getDisableBackgroundColor() const
	{
		return m_disableBackgroundColor;
	}

	void RectangleButton::setPressBackgroundColor(const QColor& color)
	{
		m_pressColor = color;
	}

	QColor RectangleButton::getPressBackgroundColor() const
	{
		return m_pressColor;
	}

	QRectF RectangleButton::getWidgetRect() const
	{
		return rect();
	}

	QMargins RectangleButton::getMargins() const
	{
		return QMargins(WIDGET_MARGIN, WIDGET_MARGIN, WIDGET_MARGIN, WIDGET_MARGIN);
	}

	bool RectangleButton::event(QEvent *event)
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
					m_backgroundColor = m_backupBackgroundColor;
					update();
				}
				break;
			}
			case QEvent::MouseButtonPress: {
				if (isEnabled() && dynamic_cast<QMouseEvent*>(event)->button() == Qt::LeftButton) {
					m_backgroundColor = m_pressColor;
					update();
				}
				break;
			}
			case QEvent::MouseButtonRelease: {
				if (isEnabled() && dynamic_cast<QMouseEvent*>(event)->button() == Qt::LeftButton) {
					m_backgroundColor = m_backupBackgroundColor;
					update();
				}
				break;
			}
			default: break;
		}

		return OverlayAbstractButton::event(event);
	}

	void RectangleButton::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);

		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		QRectF rect = getWidgetRect().marginsRemoved(getMargins());

		paintWidget(&painter, rect);

		QPen pen;
		pen.setColor(isEnabled() ? m_textColor : m_unEnbledTextColor);
		painter.setPen(pen);

		painter.drawText(rect, Qt::AlignCenter, text());
	}


}