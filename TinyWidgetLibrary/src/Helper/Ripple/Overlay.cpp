//
// Created by 86186 on 2024/2/3.
//
#include "Helper/Ripple/Overlay.h"
#include "Helper/Ripple/Ripple.h"

namespace TinyWidgetLibrary
{
	Overlay::Overlay(QWidget *parent)
	       : QWidget(parent)
		   , m_ripples()
	{
		if (parent != nullptr) {
			parent->installEventFilter(this);
		}

		// 鼠标事件穿透到显示波纹控件后的控件
		setAttribute(Qt::WA_NoSystemBackground);
		setAttribute(Qt::WA_TransparentForMouseEvents);
	}

	Overlay::~Overlay()
	{
	}

	void Overlay::addRipple(Ripple *ripple)
	{
		ripple->setParent(this);
		ripple->setOverlay(this);
		m_ripples.push_back(ripple);

		ripple->start();

		// 在波纹触发该信号时先停止再删除
		connect(this, &QObject::destroyed, ripple, &Ripple::stop);
		connect(this, &QObject::destroyed, ripple, &Ripple::deleteLater);
	}

	void Overlay::removeRipple(Ripple *ripple)
	{
		if (m_ripples.removeOne(ripple)) {
			delete ripple;
			update();
		}
	}

	inline void Overlay::setClipPath(const QPainterPath &clipPath)
	{
		m_clipPath = clipPath;
		update();
	}

	bool Overlay::event(QEvent *event)
	{
		/* 父控件改变时将其事件分发器安装到该波纹显示控件
		 * 来监听 resize 和 move 事件，来实现覆盖,
		 * 以及移除旧父控件的事件分发器*/
		if (parent() != nullptr) {
			switch (event->type()) {
				case QEvent::ParentChange: {
					parent()->installEventFilter(this);
					setGeometry(overlayGeometry());
					break;
				}
				case QEvent::ParentAboutToChange: {
					parent()->removeEventFilter(this);
					break;
				}
				default: break;
			}

		}

		return QWidget::event(event);
	}

	bool Overlay::eventFilter(QObject *watched, QEvent *event)
	{
		if (parentWidget() != nullptr && watched == parentWidget()) {
			switch (event->type()) {
				case QEvent::Move:
				case QEvent::Resize: {
					setGeometry(overlayGeometry());
					break;
				}
				default: break;
			}
		}

		return QObject::eventFilter(watched, event);
	}

	void Overlay::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);

		painter.setPen(Qt::NoPen);
		painter.setRenderHint(QPainter::Antialiasing);

		bool use; //判断当前波纹是否使用波纹显示路径

		//遍历每个波纹并绘画
		for (auto ripple : m_ripples) {
			use = ripple->getUseClipPath();
			if (use) {
				painter.setClipPath(ripple->getClipPath());
			}
			painter.setClipping(use);
			ripple->paintRipple(&painter);
		}
	}

	QRect Overlay::overlayGeometry() const
	{
		auto ptr = parentWidget();

		if (ptr == nullptr) return QRect();

		return ptr->rect().marginsRemoved(
				QMargins(
						RIPPLE_WIDGET_EXTEND,
						RIPPLE_WIDGET_EXTEND,
						RIPPLE_WIDGET_EXTEND,
						RIPPLE_WIDGET_EXTEND
						)
						);
	}
}