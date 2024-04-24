//
// Created by 86186 on 2024/2/15.
//

#ifndef TINYWIDGETLIBRARY_SIZEFIXEDWIDGET_H
#define TINYWIDGETLIBRARY_SIZEFIXEDWIDGET_H

#include <qevent.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qstackedlayout.h>

namespace TinyWidgetLibrary
{
	constexpr int COVER_WIDGET_INDEX	= 0;
	constexpr int TARGET_WIDGET_INDEX	= 1;

	class CoverWidget : public QWidget
	{
		Q_OBJECT

		Q_PROPERTY(qreal opacity READ getOpacity WRITE setOpacity)
		Q_PROPERTY(qint32 margin_top READ getMarginTop WRITE setMarginTop)
		Q_PROPERTY(qint32 margin_left READ getMarginLeft WRITE setMarginLeft)

	public:

		explicit		CoverWidget(QWidget *dialog, QWidget* target, QWidget* parent = nullptr);
		virtual			~CoverWidget();

		void			setOpacity(qreal opacity);
		qreal			getOpacity() const;

		void			setMarginTop(qint32 margin_top);
		qint32			getMarginTop() const;

		void			setMarginLeft(qint32 margin_left);
		qint32			getMarginLeft() const;

		void			setShowMode(bool showMode);
		bool			getShowMode() const;

		virtual QSize	sizeHint() const Q_DECL_OVERRIDE;

	public slots:

		void			makeOpaque();

		void			makeTransparent();

	protected:

		virtual bool	event(QEvent *event) Q_DECL_OVERRIDE;

		virtual void	paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	private:

		bool					b_showMode;
		qreal					m_opacity;
		QWidget * const 		m_dialog;
		QWidget * const 		m_target;

	};

	class TargetWidget : public QWidget
    {
        Q_OBJECT

    public:

        explicit		TargetWidget(QWidget* parent = nullptr, CoverWidget* cover_widget = nullptr);
        virtual			~TargetWidget();

    protected:

		virtual void	paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	private:

		CoverWidget	*m_coverWidget;

    };

} // TinyWidgetLibrary

#endif //TINYWIDGETLIBRARY_SIZEFIXEDWIDGET_H
