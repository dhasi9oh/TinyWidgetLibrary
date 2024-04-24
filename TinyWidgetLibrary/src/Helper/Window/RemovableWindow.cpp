//
// Created by 86186 on 2024/2/12.
//
#include "Helper/Window/RemovableWindow.h"


namespace TinyWidgetLibrary
{
	RemovableWidget::RemovableWidget(QWidget *parent)
	{
		b_removable = false;
		b_draggable = true;
	}

	RemovableWidget::~RemovableWidget()
	{
	}

	void RemovableWidget::setDrapable(bool dragable)
	{
		b_draggable = dragable;
	}

	bool RemovableWidget::getDrapable() const
	{
		return b_draggable;
	}

	void RemovableWidget::initMove()
	{
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlag(Qt::WindowType::FramelessWindowHint);

		b_removable					= false;
		m_removableWidgetLeftTop	= pos();
		m_size						= QSize(width(), height());
	}

	void RemovableWidget::setRemovableWidgetRect(QWidget *widget)
	{
		m_size						= QSize(widget->width(), widget->height());
		m_removableWidgetLeftTop	= widget->mapFromGlobal(QPoint(0, 0));
	}

	void RemovableWidget::mousePressEvent(QMouseEvent *event)
	{
		if (b_draggable) {
			QRect rect(m_removableWidgetLeftTop, m_size);

			if (event->button() == Qt::LeftButton && rect.contains(event->pos())) {
				b_removable		= true;
				m_windowPoint	= pos();
				m_mousePoint	= event->globalPosition().toPoint();
			}
		}

		QWidget::mousePressEvent(event);
	}

	void RemovableWidget::mouseMoveEvent(QMouseEvent *event)
	{
		if (b_draggable && b_removable) {
			QPoint point = event->globalPosition().toPoint();
			QPoint new_pos = QPoint(m_windowPoint.x() + (point.x() - m_mousePoint.x())
					, m_windowPoint.y() + (point.y() - m_mousePoint.y()));

			move(new_pos);
		}

		QWidget::mouseMoveEvent(event);
	}

	void RemovableWidget::mouseReleaseEvent(QMouseEvent *event)
	{
		b_removable = false;
		QWidget::mouseReleaseEvent(event);
	}

	RemovableDialog::RemovableDialog(QWidget *parent)
	{
		b_removable = false;
		b_draggable = true;
	}

	RemovableDialog::~RemovableDialog()
	{
	}

	void RemovableDialog::setDrapable(bool dragable)
	{
		b_draggable = dragable;
	}

	bool RemovableDialog::getDrapable() const
	{
		return b_draggable;
	}

	void RemovableDialog::initMove()
	{
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlag(Qt::WindowType::FramelessWindowHint);

		b_removable					= false;
		m_removableWidgetLeftTop	= pos();
		m_size						= QSize(width(), height());
	}

	void RemovableDialog::setRemovableWidgetRect(QWidget *widget)
	{
		m_size						= QSize(widget->width(), widget->height());
		m_removableWidgetLeftTop	= widget->mapFromGlobal(QPoint(0, 0));
	}

	void RemovableDialog::mousePressEvent(QMouseEvent *event)
	{
		if (b_draggable) {
			QRect rect(m_removableWidgetLeftTop, m_size);

			if (event->button() == Qt::LeftButton && rect.contains(event->pos())) {
				b_removable		= true;
				m_windowPoint	= pos();
				m_mousePoint	= event->globalPosition().toPoint();
			}
		}

		QWidget::mousePressEvent(event);
	}

	void RemovableDialog::mouseMoveEvent(QMouseEvent *event)
	{
		if (b_draggable && b_removable) {
			QPoint point = event->globalPosition().toPoint();
			QPoint new_pos = QPoint(m_windowPoint.x() + (point.x() - m_mousePoint.x())
					, m_windowPoint.y() + (point.y() - m_mousePoint.y()));

			move(new_pos);
		}

		QWidget::mouseMoveEvent(event);
	}

	void RemovableDialog::mouseReleaseEvent(QMouseEvent *event)
	{
		b_removable = false;
		QWidget::mouseReleaseEvent(event);
	}


	RemovableMainWindow::RemovableMainWindow(QWidget* parent)
	{
		b_removable = false;
		b_draggable = true;
	}

	RemovableMainWindow::~RemovableMainWindow()
	{
	}

	void RemovableMainWindow::setDrapable(bool dragable)
	{
		b_draggable = dragable;
	}

	bool RemovableMainWindow::getDrapable() const
	{
		return b_draggable;
	}

	void RemovableMainWindow::initMove()
	{
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlag(Qt::WindowType::FramelessWindowHint);

		b_removable = false;
		m_removableWidgetLeftTop = pos();
		m_size = QSize(width(), height());
	}

	void RemovableMainWindow::setRemovableWidgetRect(QWidget* widget)
	{
		m_size = QSize(widget->width(), widget->height());
		m_removableWidgetLeftTop = widget->mapFromGlobal(QPoint(0, 0));
	}

	void RemovableMainWindow::mousePressEvent(QMouseEvent* event)
	{
		if (b_draggable) {
			QRect rect(m_removableWidgetLeftTop, m_size);

			if (event->button() == Qt::LeftButton && rect.contains(event->pos())) {
				b_removable = true;
				m_windowPoint = pos();
				m_mousePoint = event->globalPosition().toPoint();
			}
		}

		QWidget::mousePressEvent(event);
	}

	void RemovableMainWindow::mouseMoveEvent(QMouseEvent* event)
	{
		if (b_draggable && b_removable) {
			QPoint point = event->globalPosition().toPoint();
			QPoint new_pos = QPoint(m_windowPoint.x() + (point.x() - m_mousePoint.x())
				, m_windowPoint.y() + (point.y() - m_mousePoint.y()));

			move(new_pos);
		}

		QWidget::mouseMoveEvent(event);
	}

	void RemovableMainWindow::mouseReleaseEvent(QMouseEvent* event)
	{
		b_removable = false;
		QWidget::mouseReleaseEvent(event);
	}

}


