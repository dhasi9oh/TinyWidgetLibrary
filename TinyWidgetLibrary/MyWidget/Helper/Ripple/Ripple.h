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

	// 波纹效果的数据类
	class Ripple : public QParallelAnimationGroup
	{
		Q_OBJECT

	public:

		explicit		Ripple(const QPoint &point, QWidget *parent = nullptr);
		explicit		Ripple(const QPoint &point, Overlay* overlay, QWidget *parent = nullptr);
		virtual			~Ripple();

		void			setOverlay(Overlay *overlay);

		void			setUseClipPath(bool useClipPath);
		bool			getUseClipPath() const;

		void			setClipPath(const QPainterPath &path);
		QPainterPath	getClipPath() const;

		QPoint 			getCenter() const;

		Overlay* 		getOverlayPtr();

		virtual void 	paintRipple(QPainter* painter) = 0;

	public slots:

		void 			destroy();

	protected:

		bool			b_use;
		QPoint			m_center;
		Overlay*		m_overlay;
		QPainterPath	m_path;

	};
}

#endif //TINYWIDGETLIBRARY_RIPPLE_H
