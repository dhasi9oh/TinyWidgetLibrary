//
// Created by 86186 on 2024/2/12.
//

#ifndef TINYWIDGETLIBRARY_POINTFIXEDWIDGET_H
#define TINYWIDGETLIBRARY_POINTFIXEDWIDGET_H

#include <qevent.h>
#include <qdialog.h>
#include <qpainter.h>

namespace TinyWidgetLibrary
{
	class PointFixedWidget : public QDialog
	{
		Q_OBJECT

		constexpr static qint32 FLOAT_WINDOW_SPACING	= 2;
		constexpr static qint32 FLOAT_WINDOW_RADIUS		= 6;

	public:

		enum class Orientation
		{
			TOP,
			BOTTOM,
			LEFT,
			RIGHT
		};

	public:

		explicit		PointFixedWidget(QWidget* parent = nullptr);
		virtual			~PointFixedWidget();

		void 			setOrientation(Orientation orientation);
		Orientation		getOrientation() const;

		void			setSize(QSize size);

	protected:

		virtual bool	event(QEvent *) Q_DECL_OVERRIDE;

		virtual bool	eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

		virtual void	paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

		void			updateOrientation(QSize size);

		void			updateOrientation(qint32 h, qint32 w);

	private:

		void			init();

	private:

		Orientation m_orientation;

	};


}

#endif //TINYWIDGETLIBRARY_POINTFIXEDWIDGET_H
