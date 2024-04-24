//
// Created by 86186 on 2024/2/7.
//

#ifndef TINYWIDGETLIBRARY_RECTANGLEBUTTON_H
#define TINYWIDGETLIBRARY_RECTANGLEBUTTON_H

#include "Helper/Ripple/OverlayAbstractButton.h"

namespace TinyWidgetLibrary
{
	class RectangleButton : public OverlayAbstractButton
	{
		Q_OBJECT

		constexpr static int WIDGET_MARGIN		= 1;

	public:

		explicit 			RectangleButton(QWidget *parent = nullptr);
		virtual 			~RectangleButton();

		void				setTextColor(const QColor &color);
		QColor              getTextColor() const;

		void 				setUnEnabledTextColor(const QColor &color);
		QColor              getUnEnabledTextColor() const;

		void				setFrameColor(const QColor &color);
		QColor              getFrameColor() const;

		void 				setHoverColor(const QColor &color);
		QColor              getHoverColor() const;

		void				setBackgroundColor(const QColor &color);
		QColor              getBackgroundColor() const;

		void				setDisableBackgroundColor(const QColor &color);
		QColor              getDisableBackgroundColor() const;

		void 				setTriggerColor(const QColor &color);
		QColor              getTriggerColor() const;

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
		QColor				m_triggerColor;

	};

}

#endif //TINYWIDGETLIBRARY_RECTANGLEBUTTON_H
