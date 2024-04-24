//
// Created by 86186 on 2024/2/15.
//

#ifndef TINYWIDGETLIBRARY_SIZEFIXEDDIALOG_H
#define TINYWIDGETLIBRARY_SIZEFIXEDDIALOG_H

#include <qstate.h>
#include <qstatemachine.h>
#include <qgraphicseffect.h>
#include <qsignaltransition.h>
#include <qpropertyanimation.h>
#include <qapplication.h>
#include <qpainterpath.h>

#include "Helper/Window/SizeFixedWidget.h"

namespace TinyWidgetLibrary
{

	class SizeFixedDialog : public QWidget
	{
		Q_OBJECT

		constexpr static qint32 WIDGET_LEFT_MARGIN_WIDTH = 64;
		constexpr static qint32 WIDGET_RIGHT_MARGIN_WIDTH = 64;

	signals:

		void showTarget();

		void hideTarget();

	public:

		explicit SizeFixedDialog(QWidget *parent = nullptr);
		virtual ~SizeFixedDialog();

		void	setStartOpacity(qreal opacity);
		void	setEndOpacity(qreal opacity);
		void	setStartMarginTop(qint32 margin_top_width);
		void	setEndMarginTop(qint32 margin_top_width);
		void	setMarginWidth(qint32 margin_top_width, qint32 margin_bottom_width);

		void	addWidget(QWidget* widget);

	protected slots:

		void shown();

		void hidden();

	protected:

		virtual void paintEvent(QPaintEvent *event) override;

	private:

		void  init();

	private:

		QStateMachine	*m_stateMachine;
		QState			*m_startState;
		QState			*m_middleState;
		QState			*m_endState;
		QStackedLayout	*m_stackedLayout;
		CoverWidget		*m_coverWidget;
		TargetWidget	*m_targetWidget;

	};

} // TinyWidgetLibrary

#endif //TINYWIDGETLIBRARY_SIZEFIXEDDIALOG_H
