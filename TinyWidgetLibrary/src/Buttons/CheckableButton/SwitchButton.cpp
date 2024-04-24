//
// Created by 86186 on 2024/2/6.
//
#include "Buttons/CheckableButton/SwitchButton.h"
#include "Helper/Ripple/RoundRipple.h"

namespace TinyWidgetLibrary
{
	SwitchButton::SwitchButton(QWidget *parent)
		: CheckableButton(parent)
		, m_floatRadiusScale(0.8)
	{
		init();
	}

	SwitchButton::~SwitchButton()
	{
	}

	void SwitchButton::setFloatRadiusScale(qreal scale)
	{
		m_floatRadiusScale = scale;
		update();
	}

	qreal SwitchButton::getFloatRadiusScale() const
	{
		return m_floatRadiusScale;
	}

	void SwitchButton::init()
	{
		setAttribute(Qt::WA_Hover);
		setCheckedStateValue(1.0);
		setDisableCheckedStateValue(1.0);
		setCheckRippleColor(QColor(0, 102, 180));
		setUncheckRippleColor(QColor(70, 109, 190));

		m_checkedTransitionAnimation->setDuration(360);
		m_uncheckedTransitionAnimation->setDuration(360);

		QStateMachine* machine = new QStateMachine(this);
		QState *smallState = new QState(machine);
		QState *bigState = new QState(machine);

		auto smallToBigAnimation =
				new QPropertyAnimation(this, "float_radius_scale");

		smallToBigAnimation->setDuration(250);

		auto smallToBigTransition =
				new QEventTransition(this, QEvent::HoverEnter);

		smallToBigTransition->setTargetState(bigState);
		smallState->addTransition(smallToBigTransition);
		smallToBigTransition->addAnimation(smallToBigAnimation);

		auto bigToSmallAnimation =
				new QPropertyAnimation(this, "float_radius_scale");

		smallToBigAnimation->setDuration(250);

		auto bigToSmallTransition =
				new QEventTransition(this, QEvent::HoverLeave);

		bigToSmallTransition->setTargetState(smallState);
		bigState->addTransition(bigToSmallTransition);
		bigToSmallTransition->addAnimation(bigToSmallAnimation);

		bigState->assignProperty(this, "float_radius_scale", 0.95);
		smallState->assignProperty(this, "float_radius_scale", 0.8);

		machine->addState(smallState);
		machine->addState(bigState);
		machine->setInitialState(smallState);
		machine->start();
		QCoreApplication::processEvents();
	}

	QSize SwitchButton::sizeHint() const
	{
		int w 			= WIDGET_WIDTH + 2 * WIDGET_MARGIN;
		int h 			= WIDGET_HEIGHT + 2 * WIDGET_MARGIN;
		QString text 	= this->text();

		if (text.isEmpty())  return QSize(w, h);

		int font_w = fontMetrics().size(Qt::TextShowMnemonic, text).width();
		return QSize(font_w + w + CHARACTER_INTERVAL + END_INTERVAL, h);
	}

	QMargins SwitchButton::getMargins() const
	{
		return QMargins(
				WIDGET_MARGIN,
				WIDGET_MARGIN,
				WIDGET_MARGIN,
				WIDGET_MARGIN);
	}

	QRectF SwitchButton::getWidgetRect() const
	{
		return QRectF(
				0,
				(height() - WIDGET_HEIGHT) / 2 - WIDGET_MARGIN,
				WIDGET_WIDTH + 2 * WIDGET_MARGIN,
				WIDGET_HEIGHT + 2 * WIDGET_MARGIN);
	}

	void SwitchButton::paintWidget(QPainter *painter, const QRectF &rect_f)
	{
		bool is_checked		= isChecked();
		qreal frame_radius 	= WIDGET_HEIGHT / 2;											// 整体的控件方框的半径
		qreal float_radius 	= SLIDER_RADIUS * m_floatRadiusScale;							// 控件中间滑块的半径
		QRectF angle		= rect_f.marginsRemoved(getMargins());					// 控件方框绘画的区域
		qreal float_y		= angle.y() + angle.height() / 2;								// 滑块的 y 轴位置
		qreal float_x		=
				angle.x() + frame_radius + (WIDGET_WIDTH - 2 * frame_radius) * m_scale;		// 滑块的 x 轴位置


		if (is_checked) {
			painter->setPen(m_triggerColor);
			painter->setBrush(m_triggerColor);
			painter->drawRoundedRect(angle, frame_radius, frame_radius);
			painter->setPen(Qt::NoPen);
			painter->setBrush(m_backgroundColor);
		}
		else {
			painter->setPen(m_frameColor);
			painter->setBrush(m_backgroundColor);
			painter->drawRoundedRect(angle, frame_radius, frame_radius);
			painter->setPen(Qt::NoPen);
			painter->setBrush(m_frameColor);
		}

		painter->drawEllipse(QPointF(float_x, float_y), float_radius, float_radius);
	}

	void SwitchButton::mousePressEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);

		if (!isEnabled()) return;

		QPoint pos = QPoint(
				WIDGET_MARGIN + WIDGET_WIDTH * 0.5 - RIPPLE_WIDGET_EXTEND,
				height() * 0.5 - RIPPLE_WIDGET_EXTEND
				);

		RoundRipple* ripple = new RoundRipple(pos);

		ripple->setOverlay(m_overlay);
		ripple->setColor(isChecked() ? m_checkRippleColor : m_uncheckRippleColor);
		ripple->setRadiusAnimationEndValue(18);
		ripple->setOpacityAnimationStartValue(0.8);

		m_overlay->addRipple(ripple);

		QAbstractButton::mousePressEvent(event);
	}

}
