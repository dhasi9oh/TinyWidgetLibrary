//
// Created by 86186 on 2024/2/15.
//

#ifndef TINYWIDGETLIBRARY_FLOATWINDOW_H
#define TINYWIDGETLIBRARY_FLOATWINDOW_H

#include "Helper/Window/PointFixedWidget.h"

#include <qevent.h>
#include <qstate.h>
#include <qpainter.h>
#include <qstatemachine.h>
#include <qsignaltransition.h>
#include <qpropertyanimation.h>
#include <qapplication.h>

namespace TinyWidgetLibrary
{
	class FloatWindow : public PointFixedWidget
	{
		Q_OBJECT

		Q_PROPERTY(QSize window_size READ size WRITE setWindowSize)

	signals:

		void		showTarget();
		void		hideTarget();

	public:

		explicit 	FloatWindow(QWidget *parent = nullptr);
		virtual 	~FloatWindow();
		void		setShowSize(QSize size);
		void		setWindowSize(QSize size);
		//该函数只能调用一次
		void		addWidget(QWidget *widget);

	private:

		void		init();

	private:

		QSize			m_targetSize;
		QStateMachine	*m_stateMachine;
		QState			*m_startState;
		QState			*m_middleState;
		QState			*m_endState;

	};

} // TinyWidgetLibrary

#endif //TINYWIDGETLIBRARY_FLOATWINDOW_H
