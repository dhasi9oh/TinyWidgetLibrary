//
// Created by 86186 on 2024/3/5.
//

#include "TextBox/ComboBox.h"

namespace TinyWidgetLibrary
{
	ComboBox::ComboBox(QWidget *parent)
		: PaintWidget(new QComboBox, parent)
	{
	}

	QComboBox *ComboBox::getComboBox() const
	{
		return qobject_cast<QComboBox*>(getTarget());
	}

	QString ComboBox::getPlaceholderText() const
	{
		return getComboBox()->placeholderText();
	}

	void ComboBox::setPlaceholderText(const QString &str)
	{
		getComboBox()->setPlaceholderText(str);
	}

	QColor ComboBox::getFocusInPlaceholderTextColor() const
	{
		return m_focusInPlaceholderTextColor;
	}

	void ComboBox::setFocusInPlaceholderTextColor(QColor color)
	{
		m_focusInPlaceholderTextColor = color;
	}

	QColor ComboBox::getFocusOutPlaceholderTextColor() const
	{
		return m_focusInPlaceholderTextColor;
	}

	void ComboBox::setFocusOutPlaceholderTextColor(QColor color)
	{
		m_focusOutPlaceholderTextColor = color;
	}

	bool ComboBox::eventFilter(QObject *watched, QEvent *event)
	{
		if (watched == m_target) {
			QPalette palette1 = m_target->palette();

			switch (event->type()) {
				case QEvent::FocusIn: {
					palette1.setColor(QPalette::PlaceholderText, m_focusInPlaceholderTextColor);
					m_target->setPalette(palette1);
					break;
				}
				case QEvent::FocusOut: {
					palette1.setColor(QPalette::PlaceholderText, m_focusOutPlaceholderTextColor);
					m_target->setPalette(palette1);
					break;
				}
				default:
					break;
			}
		}

		return PaintWidget::eventFilter(watched, event);
	}


} // TinyWidgetLibrary