//
// Created by 86186 on 2024/2/9.
//

#ifndef TINYWIDGETLIBRARY_ROUNDRIPPLE_H
#define TINYWIDGETLIBRARY_ROUNDRIPPLE_H

#include <qpainter.h>
#include <qpropertyanimation.h>

#include "Ripple.h"
#include "Overlay.h"

namespace  TinyWidgetLibrary
{

	class RoundRipple : public Ripple
    {
		Q_OBJECT

		// 注册波纹效果的属性
		Q_PROPERTY(qreal radius READ getRadius WRITE setRadius)
		Q_PROPERTY(qreal opacity READ getOpacity WRITE setOpacity)

    public:

        explicit		RoundRipple(const QPoint &point, QWidget *parent = nullptr);
		explicit		RoundRipple(const QPoint &point, Overlay* overlay, QWidget *parent = nullptr);
        virtual			~RoundRipple();

		void			setRadius(qreal radius);
		qreal			getRadius() const;

		void 			setOpacity(qreal opacity);
		qreal 			getOpacity() const;

		void 			setColor(const QColor &color);
		QColor 			getColor() const;

		void			setBrush(const QBrush &brush);
		QBrush 			getBrush() const;

		void			setRadiusAnimationStartValue(qreal value);
		void			setRadiusAnimationEndValue(qreal value);

		void			setOpacityAnimationStartValue(qreal value);
		void			setOpacityAnimationEndValue(qreal value);

		void			setAnimationDuration(int duration);

		virtual void	paintRipple(QPainter* painter) Q_DECL_OVERRIDE;

	private:

		void			init();

		QPropertyAnimation* createAnimtion(
				const QByteArray& name,
				qint32 duratino = 800,
				const QEasingCurve &easingCurve = QEasingCurve::OutQuad
		);

	private:

		qreal                     	m_radius;
		qreal                     	m_opacity;
		QBrush                    	m_brush;
		QPropertyAnimation *const 	m_radiusAnimation;
		QPropertyAnimation *const 	m_opacityAnimation;

	};

}

#endif //TINYWIDGETLIBRARY_ROUNDRIPPLE_H
