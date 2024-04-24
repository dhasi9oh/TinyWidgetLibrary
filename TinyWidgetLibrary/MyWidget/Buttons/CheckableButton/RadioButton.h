//
// Created by 86186 on 2024/2/3.
//

#ifndef TINYWIDGETLIBRARY_RADIOBUTTON_H
#define TINYWIDGETLIBRARY_RADIOBUTTON_H

#include "Helper/Button/CheckableButton.h"

namespace TinyWidgetLibrary
{
	class RadioButton : public CheckableButton
	{
		Q_OBJECT

		constexpr static int WIDGET_LENGTH = 16;
		constexpr static int WIDGET_MARGIN = 1;

	public:

		explicit 	RadioButton(QWidget *parent = nullptr);

		virtual 	~RadioButton();

		virtual QSize 		sizeHint() const Q_DECL_OVERRIDE;

		virtual QMargins 	getMargins() const Q_DECL_OVERRIDE;

		virtual QRectF 		getWidgetRect() const Q_DECL_OVERRIDE;

	private:

		void 				init();

	protected:

		virtual void 		paintWidget(QPainter *painter, const QRectF& rect_f) Q_DECL_OVERRIDE;

		virtual void        mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

	};

}

#endif //TINYWIDGETLIBRARY_RADIOBUTTON_H
