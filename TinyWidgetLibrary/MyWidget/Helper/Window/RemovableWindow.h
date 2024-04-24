//
// Created by 86186 on 2024/2/12.
//

#ifndef TINYWIDGETLIBRARY_REMOVABLEWINDOW_H
#define TINYWIDGETLIBRARY_REMOVABLEWINDOW_H

#include <qevent.h>
#include <qdialog.h>
#include <qwidget.h>
#include <qmainwindow.h>

namespace TinyWidgetLibrary
{
	class RemovableWidget : public QWidget
    {
		Q_OBJECT

    public:

		explicit 		RemovableWidget(QWidget* parent = nullptr);

		virtual 		~RemovableWidget();

		void 			setDrapable(bool dragable);
		bool 			getDrapable() const;

	protected:

		void			initMove();

		void			setRemovableWidgetRect(QWidget* widget);

		virtual void	mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

		virtual void	mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

		virtual void	mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

	private:

		QSize 	m_size;
		bool 	b_draggable;
		bool 	b_removable;
		QPoint 	m_mousePoint;
		QPoint 	m_windowPoint;
		QPoint 	m_removableWidgetLeftTop;

    };


	class RemovableDialog : public QDialog
	{
		Q_OBJECT

	public:

		explicit		RemovableDialog(QWidget* parent = nullptr);

		virtual			~RemovableDialog();

		void 			setDrapable(bool dragable);
		bool 			getDrapable() const;

	protected:

		void			initMove();

		void			setRemovableWidgetRect(QWidget* widget);

		virtual void	mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

		virtual void	mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

		virtual void	mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

	private:

		QSize 	m_size;
		bool 	b_draggable;
		bool 	b_removable;
		QPoint 	m_mousePoint;
		QPoint 	m_windowPoint;
		QPoint 	m_removableWidgetLeftTop;
	};

	class RemovableMainWindow : public QMainWindow
	{
		Q_OBJECT

	public:

		explicit 		RemovableMainWindow(QWidget* parent = nullptr);

		virtual 		~RemovableMainWindow();

		void 			setDrapable(bool dragable);
		bool 			getDrapable() const;

	protected:

		void			initMove();

		void			setRemovableWidgetRect(QWidget* widget);

		virtual void	mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

		virtual void	mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

		virtual void	mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

	private:

		QSize 	m_size;
		bool 	b_draggable;
		bool 	b_removable;
		QPoint 	m_mousePoint;
		QPoint 	m_windowPoint;
		QPoint 	m_removableWidgetLeftTop;

	};
}

#endif //TINYWIDGETLIBRARY_REMOVABLEWINDOW_H
