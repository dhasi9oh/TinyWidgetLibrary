//
// Created by 86186 on 2024/2/3.
//
#include "Helper/Ripple/Ripple.h"
#include "Helper/Ripple/Overlay.h"

namespace TinyWidgetLibrary
{

	Ripple::Ripple(const QPoint &point, QWidget *parent)
			: b_use(false)
			, m_center(point)
			, QParallelAnimationGroup(parent)
	{
	}

	Ripple::Ripple(const QPoint &point, Overlay *overlay, QWidget *parent)
			: b_use(false)
			, m_center(point)
			, m_overlay(overlay)
			, QParallelAnimationGroup(parent)
	{
	}

	Ripple::~Ripple()
	{
	}

	void Ripple::setOverlay(Overlay *overlay)
	{
		m_overlay = overlay;
	}

	QPoint Ripple::getCenter() const
	{
		return m_center;
	}

	Overlay *Ripple::getOverlayPtr()
	{
		return m_overlay;
	}

	void Ripple::destroy()
	{
		Q_ASSERT(m_overlay != nullptr);
		m_overlay->removeRipple(this);
	}

	void Ripple::setUseClipPath(bool useClipPath)
	{
		b_use = useClipPath;
	}

	void Ripple::setClipPath(const QPainterPath &path)
	{
		m_path = path;
	}

	bool Ripple::getUseClipPath() const
	{
		return b_use;
	}

	QPainterPath Ripple::getClipPath() const
	{
		return m_path;
	}

}
