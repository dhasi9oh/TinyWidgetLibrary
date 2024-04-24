//
// Created by 86186 on 2024/3/5.
//

#ifndef TINYWIDGETLIBRARY_COMBOBOX_H
#define TINYWIDGETLIBRARY_COMBOBOX_H

#include <qcombobox.h>

#include "Helper/TextBox/PaintWidget.h"

namespace TinyWidgetLibrary
{

	class ComboBox : public PaintWidget
	{
		Q_OBJECT

	public:

		explicit 	ComboBox(QWidget* parent = nullptr);
		virtual 	~ComboBox() = default;

		QComboBox	*getComboBox() const;

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

#endif //TINYWIDGETLIBRARY_COMBOBOX_H
