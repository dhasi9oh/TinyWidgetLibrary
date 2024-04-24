//
// Created by 86186 on 2024/2/11.
//

#ifndef TINYWIDGETLIBRARY_ROLLINGRIPPLE_H
#define TINYWIDGETLIBRARY_ROLLINGRIPPLE_H

#include "Ripple.h"

#include <qpainter.h>
#include <qpropertyanimation.h>

namespace TinyWidgetLibrary
{
	class RollingRipple : public Ripple
	{
		Q_OBJECT

		// 注册波纹效果的属性
		Q_PROPERTY(qreal scale READ getScale WRITE setScale)
		Q_PROPERTY(qreal opacity READ getOpacity WRITE setOpacity)

	public:

		explicit 		RollingRipple(const QPoint &point, QWidget *parent = nullptr);
		explicit		RollingRipple(const QPoint &point, Overlay* overlay, QWidget *parent = nullptr);
		virtual			~RollingRipple();

		void 			setScale(qreal scale);
		qreal 			getScale() const;

		void 			setOpacity(qreal opacity);
		qreal 			getOpacity() const;

		void			setCirqueColor(const QColor &color);
		QColor			getCirqueColor() const;

		void			setScaleAnimationStartValue(qreal value);
		void			setScaleAnimationEndValue(qreal value);

		void			setOpacityAnimationStartValue(qreal value);
		void			setOpacityAnimationEndValue(qreal value);

		virtual void	paintRipple(QPainter* painter) Q_DECL_OVERRIDE;

	private:

		void init();

		QPropertyAnimation* createAnimtion(
				const QByteArray& name,
				qint32 duratino = 800,
				const QEasingCurve &easingCurve = QEasingCurve::OutQuad
		);

	private:

		qreal                     	m_scale;
		qreal						m_opacity;
		QColor						m_cirqueColor;
		QPropertyAnimation*	const	m_scaleAnimation;
		QPropertyAnimation *const 	m_opacityAnimation;
	};
}

#endif //TINYWIDGETLIBRARY_ROLLINGRIPPLE_H
