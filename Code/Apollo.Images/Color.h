//------------------------------------------------------------------------------
// Color.h
//
// Color Class
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifndef APOLLO_IMAGES_COLOR_H
#define APOLLO_IMAGES_COLOR_H

#include <cstdint>

namespace Apollo
{
	namespace Images
	{
		struct Color
		{
			uint8_t R;
			uint8_t G;
			uint8_t B;
			uint8_t A;

			Color()
				:Color(0, 0, 0, 255) {}

			Color(uint8_t r, uint8_t g, uint8_t b)
				:Color(r, g, b, 255) {}

			Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
				:R(r), G(g), B(b), A(a) {}
		};
	}
}

#endif //APOLLO_IMAGES_COLOR_H
