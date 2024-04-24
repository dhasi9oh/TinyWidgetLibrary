//
// Created by 86186 on 2024/3/5.
//

#include "TextBox/TextBox.h"

namespace TinyWidgetLibrary
{
	TextBox::TextBox(QWidget *parent)
			: PaintWidget(new QLineEdit, parent)
	{
		m_focusInPlaceholderTextColor	= QColor(0, 102, 180);
		m_focusOutPlaceholderTextColor	= Qt::white;

		QPalette palette1 = m_target->palette();
		palette1.setColor(QPalette::PlaceholderText, m_focusInPlaceholderTextColor);
		m_target->setPalette(palette1);
	}

	QLineEdit *TextBox::getLineEdit() const
	{
		return qobject_cast<QLineEdit*>(getTarget());
	}

	QString TextBox::getPlaceholderText() const
	{
		return getLineEdit()->placeholderText();
	}

	void TextBox::setPlaceholderText(const QString &str)
	{
		getLineEdit()->setPlaceholderText(str);
	}

	QColor TextBox::getFocusInPlaceholderTextColor() const
	{
		return m_focusInPlaceholderTextColor;
	}

	void TextBox::setFocusInPlaceholderTextColor(QColor color)
	{
		m_focusInPlaceholderTextColor = color;
	}

	QColor TextBox::getFocusOutPlaceholderTextColor() const
	{
		return m_focusInPlaceholderTextColor;
	}

	void TextBox::setFocusOutPlaceholderTextColor(QColor color)
	{
		m_focusOutPlaceholderTextColor = color;
	}

	bool TextBox::eventFilter(QObject *watched, QEvent *event)
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