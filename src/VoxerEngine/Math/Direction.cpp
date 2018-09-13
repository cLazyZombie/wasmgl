#include "stdafx.h"
#include "Direction.h"

namespace VoxerEngine
{
	DirectionIterator::DirectionIterator(Direction direction)
		: m_direction(direction)
	{
	}

	Direction DirectionIterator::operator*()
	{
		return m_direction;
	}

	DirectionIterator& DirectionIterator::operator++()
	{
		if (m_direction < Direction::Count)
		{
			m_direction = (Direction)((uint8_t)m_direction + 1);
		}

		return *this;
	}

	bool DirectionIterator::operator!=(const DirectionIterator& other) const
	{
		return m_direction != other.m_direction;
	}

	DirectionIterator begin(Direction)
	{
		return DirectionIterator(Direction::Start);
	}

	DirectionIterator end(Direction)
	{
		return DirectionIterator(Direction::Count);
	}

	Direction OppositeDirection(Direction dir)
	{
		switch (dir)
		{
		case Direction::Right:
			return Direction::Left;

		case Direction::Left:
			return Direction::Right;

		case Direction::Up:
			return Direction::Down;

		case Direction::Down:
			return Direction::Up;

		case Direction::Front:
			return Direction::Back;

		case Direction::Back:
		default:
			return Direction::Front;
		}
	}

	wstring ToString(const Direction& d)
	{
		switch (d)
		{
		case VoxerEngine::Direction::Right:
			return wstring(L"Right");

		case VoxerEngine::Direction::Left:
			return wstring(L"Left");

		case VoxerEngine::Direction::Up:
			return wstring(L"Up");

		case VoxerEngine::Direction::Down:
			return wstring(L"Down");

		case VoxerEngine::Direction::Front:
			return wstring(L"Front");

		case VoxerEngine::Direction::Back:
			return wstring(L"Back");

		default:
			return wstring();
		}
	}

}