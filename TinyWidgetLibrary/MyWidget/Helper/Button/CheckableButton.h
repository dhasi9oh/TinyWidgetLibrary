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

	// 该类是一个逻辑按钮类，主要负责可选择的按钮
	// 向下开放绘画接口：
	// paintWidget、getWidgetRect、getMargins

	class  CheckableButton : public OverlayAbstractButton
    {
        Q_OBJECT

		// 该逻辑类的放缩属性
		Q_PROPERTY(qreal scale READ getScale WRITE setScale)

	public:

		// 文本对齐方式
		enum class EAlignment
        {
            Left	= Qt::AlignLeft,	//左
            Right	= Qt::AlignRight	//右
        };

	public:

		explicit CheckableButton(QWidget *parent = nullptr);

		virtual ~CheckableButton();

		void 	setTextAlignment(EAlignment alignment);
		EAlignment getTextAlignment() const;

		void 	setScale(qreal scale);
		qreal 	getScale() const;

		void 	setTextColor(const QColor &color);	//设置文本颜色
		QColor 	getTextColor() const;				//获取文本颜色

		void 	setFrameColor(const QColor &color);	//设置按钮框颜色
		QColor 	getFrameColor() const;				//获取按钮框颜色

		void 	setHoverColor(const QColor &color);	//设置鼠标悬空在按钮上的背景色
		QColor 	getHoverColor() const;				//获取鼠标悬空在按钮上的背景色

		void 	setCheckedColor(const QColor &color);	//设置被选中的颜色
		QColor 	getCheckedColor() const;				//获取被选中的颜色

		void 	setUncheckedColor(const QColor &color);	//设置未被选中的颜色
		QColor 	getUncheckedColor() const;				//获取未被选中的颜色

		void 	setDisableCheckedColor(const QColor &color);	//设置当按钮失效被选中时的颜色
		QColor 	getDisableCheckedColor() const;					//获取当按钮失效被选中时的颜色

		void 	setDisableUncheckedColor(const QColor &color);	//设置当按钮失效未被选中时的颜色
		QColor 	getDisableUncheckedColor() const;				//获取当按钮失效未被选中时的颜色

		void	setCheckRippleColor(const QColor &color);		//设置选中时波纹的颜色
		void	setUncheckRippleColor(const QColor &color);		//设置未被选中时波纹的颜色

		void 	setCheckedStateValue(qreal value);				//设置该类的scale属性在可选时选中时的值
		void 	setUncheckedStateValue(qreal value);			//设置该类的scale属性在可选时未选中时的值
		void    setDisableCheckedStateValue(qreal value);		//设置该类的scale属性在不可选时选中时的值
		void    setDisableUncheckedStateValue(qreal value);		//设置该类的scale属性在不可选时未选中时的值
		//控件分为绘画区和文本区
		virtual QRectF		getWidgetRect() const = 0;	//需要绘画控件的区域，作为paintWidget的第二个参数

		virtual QMargins 	getMargins() const = 0;		//控件的上下左右方框的厚度

	private:

		void 				init(); //控制控件的显示

	protected:

		virtual bool 		event(QEvent *event) Q_DECL_OVERRIDE;

		virtual void 		paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

		virtual void 		paintWidget(QPainter *painter, const QRectF& rect_f) = 0; //如何绘画控件

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
