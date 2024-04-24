//
// Created by 86186 on 2024/2/8.
//
#ifndef TINYWIDGETLIBRARY_OVERLAYABSTRACTBUTTON_H
#define TINYWIDGETLIBRARY_OVERLAYABSTRACTBUTTON_H

#include <qabstractbutton.h>

#include "Overlay.h"

namespace TinyWidgetLibrary
{
	class OverlayAbstractButton : public QAbstractButton
    {
    public:
        explicit		OverlayAbstractButton(QWidget *parent = nullptr);
 		virtual			~OverlayAbstractButton() override;

	protected:

		virtual bool	event(QEvent *event) Q_DECL_OVERRIDE;

		virtual bool	eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

	private:

		void			init();

	protected:

		Overlay		*m_overlay;
    };
}

#endif //TINYWIDGETLIBRARY_OVERLAYABSTRACTBUTTON_H
