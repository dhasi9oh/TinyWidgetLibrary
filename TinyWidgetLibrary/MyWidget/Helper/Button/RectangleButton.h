//
// Created by 86186 on 2024/2/7.
//

#ifndef TINYWIDGETLIBRARY_RECTANGLEBUTTON_H
#define TINYWIDGETLIBRARY_RECTANGLEBUTTON_H

#include "Helper/Ripple/OverlayAbstractButton.h"

namespace TinyWidgetLibrary
{

	// ������һ����׼�İ�ť�࣬��Ҫ���𷽿�İ�ť
	// ���¿��Ż滭�ӿڣ�
	// paintWidget

	class RectangleButton : public OverlayAbstractButton
	{
		Q_OBJECT

		constexpr static int WIDGET_MARGIN		= 1;

	public:

		explicit RectangleButton(QWidget *parent = nullptr);
		virtual ~RectangleButton();

		void	setTextColor(const QColor &color);	//�����ı���ɫ
		QColor  getTextColor() const;				//��ȡ�ı���ɫ

		void 	setUnEnabledTextColor(const QColor &color); //���ð�ť���ɵ����ɫ
		QColor  getUnEnabledTextColor() const;				//��ȡ��ť���ɵ����ɫ

		void	setFrameColor(const QColor &color);	//���ð�ť����ɫ
		QColor  getFrameColor() const;				//��ȡ��ť����ɫ

		void 	setHoverColor(const QColor &color);	//������������ڰ�ť�ϵı���ɫ
		QColor  getHoverColor() const;				//��ȡ��������ڰ�ť�ϵı���ɫ

		void	setBackgroundColor(const QColor &color);//���ð�ť����ɫ
		QColor  getBackgroundColor() const;				//��ȡ��ť����ɫ

		void	setDisableBackgroundColor(const QColor &color); //���ð�ťʧЧʱ�ı�����ɫ
		QColor  getDisableBackgroundColor() const;				//��ȡ��ťʧЧʱ�ı�����ɫ

		void 	setPressBackgroundColor(const QColor &color);	//���ð�ť����ʱ����ɫ
		QColor  getPressBackgroundColor() const;				//��ȡ��ť����ʱ����ɫ

		virtual QRectF		getWidgetRect() const;
		virtual QMargins 	getMargins() const;

	private:

		void 				init();

	protected:

		virtual bool 		event(QEvent *event) Q_DECL_OVERRIDE;

		virtual void 		paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

		virtual void 		paintWidget(QPainter *painter, const QRectF& rect_f) = 0;

	protected:

		QColor				m_textColor;
		QColor				m_unEnbledTextColor;
		QColor				m_frameColor;
		QColor				m_hoverColor;
		QColor				m_backgroundColor;
		QColor				m_backupBackgroundColor;
		QColor				m_disableBackgroundColor;
		QColor				m_pressColor;

	};

}

#endif //TINYWIDGETLIBRARY_RECTANGLEBUTTON_H
