//
// Created by 86186 on 2024/2/3.
//

#ifndef TINYWIDGETLIBRARY_RIPPLE_H
#define TINYWIDGETLIBRARY_RIPPLE_H

#include <qpainter.h>
#include <qpainterpath.h>
#include <qparallelanimationgroup.h>

namespace TinyWidgetLibrary
{
	class Overlay;

	// 波纹效果的抽象数据类
	// 开放接口：
	//paintRipple
	class Ripple : public QParallelAnimationGroup
	{
		Q_OBJECT

	public:
		//point是波纹的中心
		explicit		Ripple(const QPoint &point, QWidget *parent = nullptr);
		explicit		Ripple(const QPoint &point, Overlay* overlay, QWidget *parent = nullptr);
		virtual			~Ripple();

		void			setOverlay(Overlay *overlay);	//该波纹在哪一个显示波纹的控件上播放

		void			setUseClipPath(bool useClipPath);	//是否使用显示波纹的控件的显示方式
		bool			getUseClipPath() const;

		void			setClipPath(const QPainterPath &path);	//波纹自己的方式
		QPainterPath	getClipPath() const;

		QPoint 			getCenter() const;	//获取波纹的中心

		Overlay* 		getOverlayPtr();

		virtual void 	paintRipple(QPainter* painter) = 0;

	public slots:

		void 			destroy();//从m_overlay中删除该波纹

	protected:

		bool			b_use;
		QPoint			m_center;
		Overlay*		m_overlay;
		QPainterPath	m_path;

	};
}

#endif //TINYWIDGETLIBRARY_RIPPLE_H
