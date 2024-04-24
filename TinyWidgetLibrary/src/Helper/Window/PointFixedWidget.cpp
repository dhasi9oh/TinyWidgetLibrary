//
// Created by 86186 on 2024/2/12.
//
#include "Helper/Window/PointFixedWidget.h"

namespace TinyWidgetLibrary
{

	PointFixedWidget::PointFixedWidget(QWidget *parent)
		: QDialog(parent)
	{
		init();
	}

	PointFixedWidget::~PointFixedWidget()
	{
	}

	void PointFixedWidget::setOrientation(PointFixedWidget::Orientation orientation)
	{
		m_orientation = orientation;
		updateOrientation(QWidget::height(), QWidget::width());
	}

	PointFixedWidget::Orientation PointFixedWidget::getOrientation() const
	{
		return m_orientation;
	}

	void PointFixedWidget::setSize(QSize size)
	{
		setFixedSize(size);
		updateOrientation(size);
	}

	void PointFixedWidget::updateOrientation(QSize size)
	{
		updateOrientation(size.height(), size.width());
	}

	void PointFixedWidget::updateOrientation(qint32 h, qint32 w)
	{
		QWidget* ptr	= parentWidget();

		if (ptr == nullptr) return;

		QPoint pos		= ptr->mapToGlobal(QPoint(0, 0));
		qint32 x, y;

		switch (m_orientation) {
			case Orientation::TOP: {
				x = pos.x() + (ptr->width() - w) / 2;
				y = pos.y() - h - FLOAT_WINDOW_SPACING;
				break;
			}
			case Orientation::BOTTOM: {
				x = pos.x() + (ptr->width() - w) / 2;
				y = pos.y() + ptr->height() + FLOAT_WINDOW_SPACING;
				break;
			}
			case Orientation::LEFT: {
				x = pos.x() - w - FLOAT_WINDOW_SPACING;;
				y = pos.y() + (ptr->height() - height()) / 2;
				break;
			}
			case Orientation::RIGHT: {
				x = pos.x() + ptr->width() + FLOAT_WINDOW_SPACING;;
				y = pos.y() + (ptr->height() - height()) / 2;
				break;
			}
			default:
				break;
		}

		move(x, y);
	}

	bool PointFixedWidget::event(QEvent *event)
	{
		switch (event->type()) {
			case QEvent::ParentChange: {
				if (parentWidget()) {
					parentWidget()->installEventFilter(this);
					updateOrientation(QWidget::height(), QWidget::width());
				}
				break;
			}
			case QEvent::ParentAboutToChange: {
				QWidget* ptr = parentWidget();
				if (ptr) {
					ptr->removeEventFilter(this);
					updateOrientation(QWidget::height(), QWidget::width());
				}
				break;
			}
			default:
				break;
		}

		return QWidget::event(event);
	}

	bool PointFixedWidget::eventFilter(QObject *watched, QEvent *event)
	{
		if (watched == parent()) {
			switch (event->type()) {
				case QEvent::Move:
				case QEvent::Resize: {
					updateOrientation(QWidget::height(), QWidget::width());
					break;
				}
				default:
					break;
			}
		}

		return QDialog::eventFilter(watched, event);
	}

	void PointFixedWidget::init()
	{
		setOrientation(Orientation::TOP);

		if (parentWidget()) {
			parentWidget()->installEventFilter(this);
		}

		setAttribute(Qt::WA_TranslucentBackground);
		setWindowFlag(Qt::WindowType::FramelessWindowHint);
	}

	void PointFixedWidget::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);

		QPen pen(QColor(0, 102, 180), 1);
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(pen);
		painter.setBrush(Qt::white);
		painter.drawRoundedRect(rect(), FLOAT_WINDOW_RADIUS, FLOAT_WINDOW_RADIUS);
	}


}