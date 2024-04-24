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
	// 该类的是在其它控件的前面加一个透明窗口来显示波纹
	class Overlay : public QWidget
	{
		Q_OBJECT

	public:

		explicit	Overlay(QWidget *parent = nullptr);
		virtual 	~Overlay();
		
		void		addRipple(Ripple* ripple);	// 添加波纹
		
		void		removeRipple(Ripple* ripple);	// 移除波纹
		
		void		setClipPath(const QPainterPath& clipPath);	// 设置波纹的显示的方式

	protected:

		virtual bool	event(QEvent *event) Q_DECL_OVERRIDE;

		virtual bool	eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

		virtual void	paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	private:

		// 获取显示类父控件的坐标和长宽
		QRect			overlayGeometry() const;

	private:

		QPainterPath	m_clipPath;

		// 该控件会根据以下波纹的集合绘画所有波纹
		QList<Ripple*>	m_ripples;

	};

}

#endif //TINYWIDGETLIBRARY_OVERLAY_H
