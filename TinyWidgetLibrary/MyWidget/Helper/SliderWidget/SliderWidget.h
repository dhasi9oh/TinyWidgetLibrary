//
// Created by 86186 on 2024/2/22.
//

#ifndef TINYWIDGETLIBRARY_SLIDERWIDGET_H
#define TINYWIDGETLIBRARY_SLIDERWIDGET_H

#include <qstate.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qstatemachine.h>
#include <qeventtransition.h>
#include <qpropertyanimation.h>

namespace TinyWidgetLibrary
{
	class SliderWidget : public QWidget
	{
		Q_OBJECT

		Q_PROPERTY(qreal scale READ getScale WRITE setScale)

	public:

		explicit SliderWidget(QWidget *parent = nullptr);
		virtual ~SliderWidget();

		void	setScale(qreal scale);
		qreal	getScale() const;

		void	setCenterColor(const QColor &color);
		QColor	getCenterColor() const;

	protected:

		virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	private:

		void	init();

	private:

		qreal			m_scale;
		QColor			m_centerColor;
		QStateMachine	*m_stateMachine;
		QState			*m_startState;
		QState			*m_endState;

	};

} // TinyWidgetLibrary

#endif //TINYWIDGETLIBRARY_SLIDERWIDGET_H
