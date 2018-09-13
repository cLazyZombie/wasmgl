#pragma once

namespace VoxerEngine
{
	struct Float2
	{
		union 
		{
			struct 
			{
				float X;
				float Y;
			};

			struct
			{
				float U;
				float V;
			};
		};

		Float2(float x, float y) : X(x), Y(y) {}
		Float2() {}
	};
}
