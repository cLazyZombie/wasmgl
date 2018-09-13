#pragma once

namespace VoxerEngine
{
	enum class Direction : uint8_t
	{
		Start,
		Right = Start,
		Left,
		Up,
		Down,
		Front,
		Back,
		Count
	};

	wstring ToString(const Direction& d);

	class DirectionIterator
	{
	private:
		Direction m_direction;

	public:
		explicit DirectionIterator(Direction direction);
		DirectionIterator& operator++();
		Direction operator*();
		bool operator!=(const DirectionIterator& other) const;
	};

	DirectionIterator begin(Direction dir);
	DirectionIterator end(Direction dir);
	Direction OppositeDirection(Direction dir);
}
