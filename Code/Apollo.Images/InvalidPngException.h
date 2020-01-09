//------------------------------------------------------------------------------
// InvalidPngException.h
//
// Invalid Png Exception
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifndef APOLLO_IMAGES_INVALIDPNGEXCEPTION_H
#define APOLLO_IMAGES_INVALIDPNGEXCEPTION_H

#include <stdexcept>

namespace Apollo
{
	namespace Images
	{
		struct InvalidPngException : std::runtime_error
		{
			InvalidPngException(const char* message)
				: std::runtime_error(message) {}
		};
	}
}

#endif //APOLLO_IMAGES_INVALIDPNGEXCEPTION_H