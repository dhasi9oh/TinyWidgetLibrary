//
// Created by 86186 on 2024/2/7.
//

#ifndef TINYWIDGETLIBRARY_RECTANGLEBUTTON_H
#define TINYWIDGETLIBRARY_RECTANGLEBUTTON_H

#include "Helper/Ripple/OverlayAbstractButton.h"

namespace TinyWidgetLibrary
{

	// 该类是一个标准的按钮类，主要负责方框的按钮
	// 向下开放绘画接口：
	// paintWidget

	class RectangleButton : public OverlayAbstractButton
	{
		Q_OBJECT

		constexpr static int WIDGET_MARGIN		= 1;

	public:

		explicit RectangleButton(QWidget *parent = nullptr);
		virtual ~RectangleButton();

		void	setTextColor(const QColor &color);	//设置文本颜色
		QColor  getTextColor() const;				//获取文本颜色

		void 	setUnEnabledTextColor(const QColor &color); //设置按钮不可点击颜色
		QColor  getUnEnabledTextColor() const;				//获取按钮不可点击颜色

		void	setFrameColor(const QColor &color);	//设置按钮框颜色
		QColor  getFrameColor() const;				//获取按钮框颜色

		void 	setHoverColor(const QColor &color);	//设置鼠标悬空在按钮上的背景色
		QColor  getHoverColor() const;				//获取鼠标悬空在按钮上的背景色

		void	setBackgroundColor(const QColor &color);//设置按钮背景色
		QColor  getBackgroundColor() const;				//获取按钮背景色

		void	setDisableBackgroundColor(const QColor &color); //设置按钮失效时的背景颜色
		QColor  getDisableBackgroundColor() const;				//获取按钮失效时的背景颜色

		void 	setPressBackgroundColor(const QColor &color);	//设置按钮触发时的颜色
		QColor  getPressBackgroundColor() const;				//获取按钮触发时的颜色

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
