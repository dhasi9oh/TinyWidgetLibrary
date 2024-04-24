//
// Created by 86186 on 2024/2/8.
//
#include "Helper/Ripple/OverlayAbstractButton.h"

namespace TinyWidgetLibrary
{


	OverlayAbstractButton::OverlayAbstractButton(QWidget *parent)
		: QAbstractButton(parent)
	{
		init();
	}

	OverlayAbstractButton::~OverlayAbstractButton()
	{
	}

	bool OverlayAbstractButton::event(QEvent *event)
	{
		switch (event->type()) {
			case QEvent::Move:
			case QEvent::Resize: {
				m_overlay->setGeometry(geometry());
				break;
			}
			case QEvent::Show: {
				m_overlay->show();
				break;
			}
			case QEvent::ParentChange: {
				QWidget *widget = parentWidget();

				if (widget != nullptr)
					m_overlay->setParent(widget);

				break;
			}
			default:
				break;
		}

		return QAbstractButton::event(event);
	}

	bool OverlayAbstractButton::eventFilter(QObject *watched, QEvent *event)
	{
		if (watched == m_overlay && QEvent::Resize == event->type()) {
			m_overlay->setGeometry(
					geometry().marginsRemoved(
							QMargins(
									RIPPLE_WIDGET_EXTEND,
									RIPPLE_WIDGET_EXTEND,
									RIPPLE_WIDGET_EXTEND,
									RIPPLE_WIDGET_EXTEND
							)
					)
			);
		}

		return QObject::eventFilter(watched, event);
	}

	void OverlayAbstractButton::init()
	{
		m_overlay = new Overlay;
		m_overlay->setParent(this->parentWidget());
		m_overlay->installEventFilter(this);
	}

}