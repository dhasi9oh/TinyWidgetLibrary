//
// Created by 86186 on 2024/2/20.
//

#ifndef TINYWIDGETLIBRARY_MESSAGEBOX_H
#define TINYWIDGETLIBRARY_MESSAGEBOX_H

#include <qstate.h>
#include <qlabel.h>
#include <qtimer.h>
#include <qlayout.h>
#include <qscreen.h>
#include <qdialog.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qapplication.h>
#include <qstatemachine.h>
#include <qgraphicseffect.h>
#include <qsignaltransition.h>
#include <qpropertyanimation.h>

namespace TinyWidgetLibrary
{
	class MessageBoxHint : public QDialog
	{
		Q_OBJECT

		Q_PROPERTY(qreal opacity READ getOpacity WRITE setOpacity)
		Q_PROPERTY(qint32 window_x READ x WRITE setX)
		Q_PROPERTY(qint32 window_y READ y WRITE setY)

		constexpr static qint32 WIDGET_MARGIN			= 10;
		constexpr static qint32 WIDGET_DEFAULT_WIDTH	= 300;
		constexpr static qint32 WIDGET_DEFAULT_HEIGHT	= 64;

	signals:

		void	readyShow();
		void	readyHide();
		void	hideTarget();

	public:

		explicit		MessageBoxHint(QWidget *parent = nullptr);
		virtual			~MessageBoxHint();

		QLabel*			getLabelPtr();

		QColor			getFrameColor() const;
		void			setFrameColor(const QColor& color);

		qreal			getOpacity() const;
		void			setOpacity(qreal opacity);

		void			setX(qint32 x);
		void			setY(qint32 y);

		void			setText(const QString& text);

		virtual QSize	sizeHint() const Q_DECL_OVERRIDE;

	protected:

		virtual void	showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

		virtual void	paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	private:

		void			init();

		void			updateStartPos();

	private slots:

		void			triggerReadyHide();

	private:

		bool			b_closing;
		QColor			m_frameColor;
		QTimer			*m_timer;
		QLabel			*m_label;
		QPushButton		*m_button;
		QWidget			*m_widget;
		QStateMachine	*m_machine;
		QState			*m_startState;
		QState			*m_middleState;
		QState			*m_endState;

	};
}


#endif //TINYWIDGETLIBRARY_MESSAGEBOX_H
