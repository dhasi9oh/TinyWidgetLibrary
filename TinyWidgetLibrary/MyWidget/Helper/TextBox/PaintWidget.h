//
// Created by 86186 on 2024/2/2.
//

#ifndef TINYWIDGETLIBRARY_PAINTWIDGET_H
#define TINYWIDGETLIBRARY_PAINTWIDGET_H

#include <qevent.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qpainter.h>
#include <qstate.h>
#include <qapplication.h>
#include <qstatemachine.h>
#include <qeventtransition.h>
#include <qpropertyanimation.h>

#include "Paint/Paint.h"
#include "Helper/Ripple/Overlay.h"

namespace TinyWidgetLibrary
{
	constexpr char default_qss[] = "QWidget{\n"
								   "\tborder: none;\n"
								   "\toutline: none;\n"
								   "\tbackground: transparent;\n"
								   "}\n";

	class Paint;
	class RisePaint;

	// 这个类是用来作div的
	class PaintWidget : public QWidget
	{
        Q_OBJECT

		Q_PROPERTY(qreal scale READ getScale WRITE setScale)

	public:

		explicit 		PaintWidget(QWidget *source, QWidget* parent = nullptr);
		virtual			~PaintWidget();

		qreal			getScale() const;
		void			setScale(qreal scale);

		QWidget*		getTarget() const;
		void			setTarget(QWidget* target);

		void 			setPaint(Paint* paint);

		QColor			getFrameColor() const;
		void			setFrameColor(QColor color);

		QColor			getTargetColor() const;
		void			setTargetColor(QColor color);

		QColor			getBackgroundColor() const;
		void			setBackgroundColor(QColor color);

		QColor			getFocusInFontColor() const;
		void			setFocusInFontColor(QColor color);

		QColor			getFocusOutFontColor() const;
		void			setFocusOutFontColor(QColor color);

	protected:

		virtual void	paintEvent(QPaintEvent* event) override;

		virtual bool	eventFilter(QObject *watched, QEvent *event) override;

	private:

		void			init();

	protected:

		// 装在div里的控件
		qreal			m_scale;
		Paint			*m_paint;
		QWidget			*m_target;
		QStateMachine	*m_stateMachine;
		QState			*m_startState;
		QState			*m_endState;
		QColor			m_focusInColor;
		QColor			m_focusOutColor;
	};
}

#endif //TINYWIDGETLIBRARY_PAINTWIDGET_H
