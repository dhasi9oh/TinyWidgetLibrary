//
// Created by 86186 on 2024/2/12.
//

#ifndef TINYWIDGETLIBRARY_SLIDER_H
#define TINYWIDGETLIBRARY_SLIDER_H

#include <qlabel.h>
#include <qlayout.h>
#include <qabstractslider.h>

#include "PopupBox/FloatWindow.h"
#include "Helper/SliderWidget/SliderWidget.h"

namespace TinyWidgetLibrary
{
	class Slider : public QAbstractSlider
	{
		Q_OBJECT

		constexpr static qint32 SLIDER_MARGIN		= 5;
		constexpr static qint32 SLIDER_LENGTH		= 16;
		constexpr static qint32 PROGRESS_HEIGHT		= 6;
		constexpr static qint32 FLOAT_WINDOW_LENGTH	= 20;

	public:

		enum class Direction {
            TopToBottom,
			BottomToTop,
			LeftToRight,
			RightToLeft
        };

	public:

		explicit		Slider(QWidget *parent = nullptr);
		virtual			~Slider();

		void			setDirection(Direction direction);
		Direction		getDirection() const;

		void			setCenterColor(const QColor &color);
		QColor			getCenterColor() const;

		void			setProgressColor(const QColor &color);
        QColor			getProgressColor() const;

	protected:

		virtual bool	event(QEvent *event) Q_DECL_OVERRIDE;

		virtual void	paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

		virtual void    mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

		virtual void    mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

		virtual void    mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

	private:

		void			init();

	private slots:

		void			onSliderMoved(qint32 position);

	private:

		Direction			m_direction;
		QColor				m_progressColor;
		QLabel				*m_label;
		FloatWindow			*m_floatWindow;
		SliderWidget		*m_sliderWidget;
		QSpacerItem			*m_leftSpacer;
		QSpacerItem			*m_rightSpacer;

	};

}

#endif //TINYWIDGETLIBRARY_SLIDER_H
