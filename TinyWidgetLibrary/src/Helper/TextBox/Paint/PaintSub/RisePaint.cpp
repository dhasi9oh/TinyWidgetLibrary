//
// Created by 86186 on 2024/3/7.
//

#include "Helper/TextBox/Paint/PaintSub/RisePaint.h"

namespace TinyWidgetLibrary
{
	RisePaint::RisePaint(PaintWidget *source, QObject *parent)
			: Paint(source, parent)
	{}

	RisePaint::~RisePaint()
	{
	}

	void RisePaint::operator()(QPainter *painter)
	{
		painter->setPen(QPen(m_frameColor, 2));
		painter->setBrush(m_backgroundColor);
		painter->drawRect(m_source->rect());

		qreal scale = m_source->getScale();
		int w		= m_source->width();
		int h		= m_source->height();
		int _h		= scale * h;

		painter->setPen(Qt::NoPen);
		painter->setBrush(m_color);
		painter->drawRect(0, h - _h, w, _h);
	}

} // TinyWidgetLibrary