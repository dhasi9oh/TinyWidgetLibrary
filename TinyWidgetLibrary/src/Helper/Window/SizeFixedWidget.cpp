//
// Created by 86186 on 2024/2/15.
//

#include "Helper/Window/SizeFixedWidget.h"

namespace TinyWidgetLibrary
{
	CoverWidget::CoverWidget(QWidget *dialog, QWidget *target, QWidget *parent)
		: QWidget(parent)
		, b_showMode(false)
		, m_opacity(0.0)
		, m_dialog(dialog)
		, m_target(target)
	{
		resize(m_target->size());
	}

	CoverWidget::~CoverWidget()
	{
	}

	void CoverWidget::setOpacity(qreal opacity)
	{
		b_showMode	= true;
		m_opacity	= opacity;
		update();
	}

	qreal CoverWidget::getOpacity() const
	{
		return m_opacity;
	}

	void CoverWidget::setMarginTop(qint32 margin_top)
	{
		QMargins margins = m_dialog->layout()->contentsMargins();
		qint32 margin_bottom = margins.bottom() - margin_top + margins.top();
		margins.setTop(margin_top);
		margins.setBottom(margin_bottom);
		m_dialog->layout()->setContentsMargins(margins);
	}

	qint32 CoverWidget::getMarginTop() const
	{
		return m_dialog->layout()->contentsMargins().top();
	}

	void CoverWidget::setMarginLeft(qint32 margin_left)
	{
		QMargins margins = m_dialog->layout()->contentsMargins();
		margins.setLeft(margin_left);
		m_dialog->layout()->setContentsMargins(margins);
	}

	qint32 CoverWidget::getMarginLeft() const
	{
		return m_dialog->layout()->contentsMargins().left();
	}

	void CoverWidget::makeOpaque()
	{
		m_opacity	= 1.0;
		b_showMode	= true;

		update();
	}

	void CoverWidget::makeTransparent()
	{
		m_dialog->close();
	}

	void CoverWidget::setShowMode(bool showMode)
	{
		b_showMode = showMode;
		update();
	}

	bool CoverWidget::getShowMode() const
	{
		return b_showMode;
	}

	QSize CoverWidget::sizeHint() const
	{
		return m_target->size();
	}

	void CoverWidget::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);

		if (!b_showMode) return;

		QPainter painter(this);
		painter.setOpacity(m_opacity);

		QPixmap pixmap = m_target->grab(rect());

		painter.drawPixmap(rect(), pixmap);
	}

	bool CoverWidget::event(QEvent *event)
	{
			switch (event->type()) {
				case QEvent::Move:
				case QEvent::Resize: {
					m_target->setGeometry(geometry());
					break;
				}
				default:
					break;
			}

		return QWidget::event(event);
	}

	TargetWidget::TargetWidget(QWidget *parent, CoverWidget* cover_widget)
		: QWidget(parent)
	{
	}

	TargetWidget::~TargetWidget()
	{
	}

	void TargetWidget::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event);
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(QColor(255, 255, 255));

		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		painter.setBrush(brush);

		painter.drawRect(rect());
	}

} // TinyWidgetLibrary