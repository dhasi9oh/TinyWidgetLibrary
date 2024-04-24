//
// Created by 86186 on 2024/2/3.
//

#ifndef TINYWIDGETLIBRARY_OVERLAY_H
#define TINYWIDGETLIBRARY_OVERLAY_H

#include <qevent.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qpainterpath.h>

namespace TinyWidgetLibrary
{
	class Ripple;

	constexpr static int RIPPLE_WIDGET_EXTEND = -8;

	// 波纹效果的显示类
	class Overlay : public QWidget
	{
		Q_OBJECT

	public:

		explicit		 Overlay(QWidget *parent = nullptr);

		virtual 		~Overlay();

		// 添加波纹
		void			addRipple(Ripple* ripple);

		// 移除波纹
		void			removeRipple(Ripple* ripple);

		void			setClipPath(const QPainterPath& clipPath);

	protected:

		virtual bool	event(QEvent *event) Q_DECL_OVERRIDE;

		virtual bool	eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

		virtual void	paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	private:

		// 获取显示类父控件的坐标和长宽
		QRect			overlayGeometry() const;

	private:

		QPainterPath	m_clipPath;

		QList<Ripple*>	m_ripples;

	};

}

#endif //TINYWIDGETLIBRARY_OVERLAY_H
