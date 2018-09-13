#include "stdafx.h"
#include "Ray.h"
#include "Vector3.h"
#include "Mathematics.h"

namespace VoxerEngine
{
	Ray::Ray(const Vector3& pos, const Vector3& dir, float distance /*= 30000.0f*/)
		: Pos(pos), Dir(dir), Distance(distance)
	{
	}

	bool Ray::Intersect(const AABB& aabb, bool checkInside, float* hitDistance, Direction* hitDir) const
	{
		// aabb 안에서 ray가 시작할때
		if (aabb.Has(Pos))
		{
			if (checkInside)
			{
				if (hitDir) *hitDir = Direction::Up;
				if (hitDistance) *hitDistance = 0.0f;
				return true;
			}

			return false;
		}

		// x축
		float tmin, tmax, tymin, tymax, tzmin, tzmax;
		tmin = 0;
		tmax = Distance;

		if (Math::Absf(Dir.X) < Math::Epsilon)
		{
			if (Pos.X < aabb.MinPos.X || Pos.X > aabb.MaxPos.X) return false;
		}
		else
		{
			tmin = (aabb.MinPos.X - Pos.X) / Dir.X;
			tmax = (aabb.MaxPos.X - Pos.X) / Dir.X;
			if (tmin > tmax) swap(tmin, tmax);
		}

		if (Math::Absf(Dir.Y) < Math::Epsilon)
		{
			if (Pos.Y < aabb.MinPos.Y || Pos.Y > aabb.MaxPos.Y) return false;
		}
		else
		{
			tymin = (aabb.MinPos.Y - Pos.Y) / Dir.Y;
			tymax = (aabb.MaxPos.Y - Pos.Y) / Dir.Y;

			if (tymin > tymax) swap(tymin, tymax);
			if ((tmin > tymax) || (tymin > tmax)) return false;
			if (tymin > tmin) tmin = tymin;
			if (tymax < tmax) tmax = tymax;
		}

		if (Math::Absf(Dir.Z) < Math::Epsilon)
		{
			if (Pos.Z < aabb.MinPos.Z || Pos.Z > aabb.MaxPos.Z) return false;
		}
		else
		{
			tzmin = (aabb.MinPos.Z - Pos.Z) / Dir.Z;
			tzmax = (aabb.MaxPos.Z - Pos.Z) / Dir.Z;
			if (tzmin > tzmax) swap(tzmin, tzmax);
			if ((tmin > tzmax) || (tzmin > tmax)) return false;
			if (tzmin > tmin) tmin = tzmin;
			if (tzmax < tmax) tmax = tzmax;
		}

		if (tmin > Distance) return false;

		// 뒤로 부딪히는 경우
		if (tmin < 0)
		{
			if (tmax > 0 && checkInside)
			{
				tmin = 0;
			}
			else
			{
				return false;
			}
		}

		if (hitDir != nullptr)
		{
			Vector3 hitPos = Pos + (Dir * tmin);
			
			*hitDir = Direction::Up;
			float minDist = 100.0f;	// 1m 오차보다 작아야 사용.
			float curDist;

			// front
			curDist = Math::Absf(aabb.MaxPos.X - hitPos.X);
			if (curDist < minDist)
			{
				*hitDir = Direction::Front;
				minDist = curDist;
			}

			// back
			curDist = Math::Absf(aabb.MinPos.X - hitPos.X);
			if (curDist < minDist)
			{
				*hitDir = Direction::Back;
				minDist = curDist;
			}

			// right
			curDist = Math::Absf(aabb.MaxPos.Y - hitPos.Y);
			if (curDist < minDist)
			{
				*hitDir = Direction::Right;
				minDist = curDist;
			}

			// left
			curDist = Math::Absf(aabb.MinPos.Y - hitPos.Y);
			if (curDist < minDist)
			{
				*hitDir = Direction::Left;
				minDist = curDist;
			}

			// up
			curDist = Math::Absf(aabb.MaxPos.Z - hitPos.Z);
			if (curDist < minDist)
			{
				*hitDir = Direction::Up;
				minDist = curDist;
			}

			// down
			curDist = Math::Absf(aabb.MinPos.Z - hitPos.Z);
			if (curDist < minDist)
			{
				*hitDir = Direction::Down;
				minDist = curDist;
			}
		}

		if (hitDistance != nullptr)
		{
			*hitDistance = tmin;
		}

		return true;
	}

}