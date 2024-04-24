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

	// ������һ���߼���ť�࣬��Ҫ�����ѡ��İ�ť
	// ���¿��Ż滭�ӿڣ�
	// paintWidget��getWidgetRect��getMargins

	class  CheckableButton : public OverlayAbstractButton
    {
        Q_OBJECT

		// ���߼���ķ�������
		Q_PROPERTY(qreal scale READ getScale WRITE setScale)

	public:

		// �ı����뷽ʽ
		enum class EAlignment
        {
            Left	= Qt::AlignLeft,	//��
            Right	= Qt::AlignRight	//��
        };

	public:

		explicit CheckableButton(QWidget *parent = nullptr);

		virtual ~CheckableButton();

		void 	setTextAlignment(EAlignment alignment);
		EAlignment getTextAlignment() const;

		void 	setScale(qreal scale);
		qreal 	getScale() const;

		void 	setTextColor(const QColor &color);	//�����ı���ɫ
		QColor 	getTextColor() const;				//��ȡ�ı���ɫ

		void 	setFrameColor(const QColor &color);	//���ð�ť����ɫ
		QColor 	getFrameColor() const;				//��ȡ��ť����ɫ

		void 	setHoverColor(const QColor &color);	//������������ڰ�ť�ϵı���ɫ
		QColor 	getHoverColor() const;				//��ȡ��������ڰ�ť�ϵı���ɫ

		void 	setCheckedColor(const QColor &color);	//���ñ�ѡ�е���ɫ
		QColor 	getCheckedColor() const;				//��ȡ��ѡ�е���ɫ

		void 	setUncheckedColor(const QColor &color);	//����δ��ѡ�е���ɫ
		QColor 	getUncheckedColor() const;				//��ȡδ��ѡ�е���ɫ

		void 	setDisableCheckedColor(const QColor &color);	//���õ���ťʧЧ��ѡ��ʱ����ɫ
		QColor 	getDisableCheckedColor() const;					//��ȡ����ťʧЧ��ѡ��ʱ����ɫ

		void 	setDisableUncheckedColor(const QColor &color);	//���õ���ťʧЧδ��ѡ��ʱ����ɫ
		QColor 	getDisableUncheckedColor() const;				//��ȡ����ťʧЧδ��ѡ��ʱ����ɫ

		void	setCheckRippleColor(const QColor &color);		//����ѡ��ʱ���Ƶ���ɫ
		void	setUncheckRippleColor(const QColor &color);		//����δ��ѡ��ʱ���Ƶ���ɫ

		void 	setCheckedStateValue(qreal value);				//���ø����scale�����ڿ�ѡʱѡ��ʱ��ֵ
		void 	setUncheckedStateValue(qreal value);			//���ø����scale�����ڿ�ѡʱδѡ��ʱ��ֵ
		void    setDisableCheckedStateValue(qreal value);		//���ø����scale�����ڲ���ѡʱѡ��ʱ��ֵ
		void    setDisableUncheckedStateValue(qreal value);		//���ø����scale�����ڲ���ѡʱδѡ��ʱ��ֵ
		//�ؼ���Ϊ�滭�����ı���
		virtual QRectF		getWidgetRect() const = 0;	//��Ҫ�滭�ؼ���������ΪpaintWidget�ĵڶ�������

		virtual QMargins 	getMargins() const = 0;		//�ؼ����������ҷ���ĺ��

	private:

		void 				init(); //���ƿؼ�����ʾ

	protected:

		virtual bool 		event(QEvent *event) Q_DECL_OVERRIDE;

		virtual void 		paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

		virtual void 		paintWidget(QPainter *painter, const QRectF& rect_f) = 0; //��λ滭�ؼ�

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
