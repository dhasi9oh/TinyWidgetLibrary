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
			, m_overlay(nullptr)
			, QParallelAnimationGroup(parent)
	{
		//在动画结束时将该波纹从m_overlay的波纹集合中删除
		connect(this, &QAbstractAnimation::finished, this, &Ripple::destroy);
	}

	Ripple::Ripple(const QPoint &point, Overlay *overlay, QWidget *parent)
			: b_use(false)
			, m_center(point)
			, m_overlay(overlay)
			, QParallelAnimationGroup(parent)
	{
		//在动画结束时将该波纹从m_overlay的波纹集合中删除
		connect(this, &QAbstractAnimation::finished, this, &Ripple::destroy);
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
