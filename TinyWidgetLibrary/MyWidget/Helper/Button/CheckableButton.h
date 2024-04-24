//
// Created by 86186 on 2024/2/4.
//

#ifndef TINYWIDGETLIBRARY_CHECKABLEBUTTON_H
#define TINYWIDGETLIBRARY_CHECKABLEBUTTON_H

#include <qstate.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qstatemachine.h>
#include <qabstractbutton.h>
#include <qeventtransition.h>
#include <qsignaltransition.h>
#include <qpropertyanimation.h>

#include "Helper/Ripple/Ripple.h"
#include "Helper/Ripple/Overlay.h"
#include "Helper/Ripple/OverlayAbstractButton.h"

namespace TinyWidgetLibrary
{

	constexpr static int CHARACTER_INTERVAL = 8;
	constexpr static int END_INTERVAL		= 4;

	class  CheckableButton : public OverlayAbstractButton
    {
        Q_OBJECT

		Q_PROPERTY(qreal scale READ getScale WRITE setScale)

	public:

		enum class EAlignment
        {
            Left	= Qt::AlignLeft,
            Right	= Qt::AlignRight
        };

	public:

		explicit CheckableButton(QWidget *parent = nullptr);

		virtual ~CheckableButton();

		void 	setTextAlignment(EAlignment alignment);
		EAlignment getTextAlignment() const;

		void 	setScale(qreal scale);
		qreal 	getScale() const;

		void 	setTextColor(const QColor &color);
		QColor 	getTextColor() const;

		void 	setFrameColor(const QColor &color);
		QColor 	getFrameColor() const;

		void 	setHoverColor(const QColor &color);
		QColor 	getHoverColor() const;

		void 	setCheckedColor(const QColor &color);
		QColor 	getCheckedColor() const;

		void 	setUncheckedColor(const QColor &color);
		QColor 	getUncheckedColor() const;

		void 	setDisableCheckedColor(const QColor &color);
		QColor 	getDisableCheckedColor() const;

		void 	setDisableUncheckedColor(const QColor &color);
		QColor 	getDisableUncheckedColor() const;

		void	setCheckRippleColor(const QColor &color);
		void	setUncheckRippleColor(const QColor &color);

		void 	setCheckedStateValue(qreal value);
		void 	setUncheckedStateValue(qreal value);
		void    setDisableCheckedStateValue(qreal value);
		void    setDisableUncheckedStateValue(qreal value);

		virtual QRectF		getWidgetRect() const = 0;

		virtual QMargins 	getMargins() const = 0;

	private:

		void 				init();

	protected:

		virtual bool 		event(QEvent *event) Q_DECL_OVERRIDE;

		virtual void 		paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

		virtual void 		paintWidget(QPainter *painter, const QRectF& rect_f) = 0;

	protected:

		qreal 							m_scale;
		QSignalTransition               *m_checkedTransition;
		QSignalTransition               *m_uncheckedTransition;
		QStateMachine					*m_stateMachine;
		QState							*m_checkedState;
		QState							*m_uncheckedState;
		QState							*m_disableCheckedState;
		QState							*m_disableUncheckedState;
		CheckableButton::EAlignment		m_alignment;
		QColor							m_textColor;
		QColor							m_unEnbledTextColor;
		QColor	    					m_checkRippleColor;
		QColor							m_uncheckRippleColor;
		QColor							m_frameColor;
		QColor							m_hoverColor;
		QColor							m_triggerColor;
		QColor							m_backgroundColor;
		QColor							m_checkedColor;
		QColor							m_uncheckedColor;
		QColor							m_disableCheckedColor;
		QColor                          m_disableUncheckedColor;
		QPropertyAnimation				*m_checkedTransitionAnimation;
		QPropertyAnimation				*m_uncheckedTransitionAnimation;

    };
}

#endif //TINYWIDGETLIBRARY_CHECKABLEBUTTON_H
