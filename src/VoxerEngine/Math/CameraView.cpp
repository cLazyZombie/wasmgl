#include "stdafx.h"
#include "CameraView.h"

namespace VoxerEngine
{
	Frustum CameraView::GetFrustum() const
	{
		return Frustum{Pos, Dir, Up, Near, Far, Fov, Aspect};
	}
}