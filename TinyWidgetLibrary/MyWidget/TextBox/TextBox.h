//
// Created by 86186 on 2024/3/5.
//

#ifndef TINYWIDGETLIBRARY_TEXTBOX_H
#define TINYWIDGETLIBRARY_TEXTBOX_H

#include <qlineedit.h>
#include "Helper/TextBox/PaintWidget.h"

namespace TinyWidgetLibrary
{

	class TextBox : public PaintWidget
	{
		Q_OBJECT

	public:

		explicit 	TextBox(QWidget* parent = nullptr);
		virtual 	~TextBox() = default;

		QLineEdit	*getLineEdit() const;

		QString		getPlaceholderText() const;
		void		setPlaceholderText(const QString& str);

		QColor		getFocusInPlaceholderTextColor() const;
		void		setFocusInPlaceholderTextColor(QColor color);

		QColor		getFocusOutPlaceholderTextColor() const;
		void		setFocusOutPlaceholderTextColor(QColor color);

	protected:

		bool		eventFilter(QObject *watched, QEvent *event) override;

	private:

		QColor		m_focusInPlaceholderTextColor;
		QColor		m_focusOutPlaceholderTextColor;

	};

} // TinyWidgetLibrary

#endif //TINYWIDGETLIBRARY_TEXTBOX_H
