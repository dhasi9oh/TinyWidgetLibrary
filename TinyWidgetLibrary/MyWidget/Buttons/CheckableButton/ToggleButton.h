//
// Created by 86186 on 2024/2/7.
//

#ifndef TINYWIDGETLIBRARY_TOGGLEBUTTON_H
#define TINYWIDGETLIBRARY_TOGGLEBUTTON_H

#include <qstate.h>
#include <qapplication.h>
#include <qstatemachine.h>
#include <qsignaltransition.h>
#include <qpropertyanimation.h>

#include "Helper/Ripple/RoundRipple.h"
#include "Helper/Ripple/OverlayAbstractButton.h"

namespace TinyWidgetLibrary
{
	class ToggleButton : public OverlayAbstractButton
    {
		Q_OBJECT

		Q_PROPERTY(qreal scale READ getScale WRITE setScale)

		constexpr static int WIDGET_MARGIN 		= 1;
		constexpr static int RECT_ANGLE_RADIUS 	= 8;

    public:

        explicit 			ToggleButton(QWidget *parent = nullptr);

        virtual 			~ToggleButton();

		void 				setScale(qreal scale);
		qreal 				getScale() const;

		void 				setCheckedTextColor(const QColor& color);
		QColor				getCheckedTextColor() const;

		void 				setUnCheckedTextColor(const QColor& color);
		QColor				getUnCheckedTextColor() const;

		void 				setUnEnabledCheckedTextColor(const QColor& color);
		QColor				getUnEnabledCheckedTextColor() const;

		void				setFrameColor(const QColor& color);
		QColor				getFrameColor() const;

		void				setUnEnabledFrameColor(const QColor& color);
		QColor				getUnEnabledFrameColor() const;

		void				setHoverColor(const QColor& color);
		QColor				getHoverColor() const;

		void				setTriggerdColor(const QColor& color);
		QColor				getTriggerdColor() const;

		void				setCheckedColor(const QColor& color);
		QColor				getCheckedColor() const;

		void				setUnCheckedColor(const QColor& color);
		QColor				getUnCheckedColor() const;

		void				setUnEnabledCheckedColor(const QColor& color);
		QColor				getUnEnabledCheckedColor() const;

		void				setUnEnabledUnCheckedColor(const QColor& color);
		QColor				getUnEnabledUnCheckedColor() const;

		virtual QRectF		getWidgetRect() const;

		virtual QMargins	getMargins() const;

	protected:

		virtual bool 		event(QEvent *event) Q_DECL_OVERRIDE;

		virtual void 		mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

		virtual void		paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

		virtual void		paintWidget(QPainter *painter, const QRectF& rect_f);

	private:

		void				init();

	private:

		qreal			m_scale;
		QColor			m_checkedTextColor;
		QColor			m_uncheckedTextColor;
		QColor			m_unEnabledCheckedTextColor;
		QColor			m_unEnabledUncheckedTextColor;
		QColor			m_frameColor;
		QColor          m_disableFrameColor;
		QColor			m_hoverColor;
		QColor			m_triggerColor;
		QColor			m_backgroundColor;
		QColor			m_checkedColor;
		QColor			m_uncheckedColor;
		QColor			m_disableCheckedColor;
		QColor			m_disableUncheckedColor;
		QStateMachine	*m_stateMachine;
		QState			*m_checkedState;
		QState			*m_unCheckedState;
    };
}

#endif //TINYWIDGETLIBRARY_TOGGLEBUTTON_H
