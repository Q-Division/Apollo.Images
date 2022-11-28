//------------------------------------------------------------------------------
// Image.h
//
// Image Class
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifndef APOLLO_IMAGES_IMAGE_H
#define APOLLO_IMAGES_IMAGE_H

#include <cstdint>
#include <memory>
#include "PixelFormat.h"
#include "Color.h"

namespace Apollo
{
	namespace Images
	{
		class Image
		{
		private:
			uint32_t mWidth;						///< Width
			uint32_t mHeight;						///< Height		
			uint32_t mStride;						///< Stride
			PixelFormat mPixelFormat;

			std::unique_ptr<uint8_t[]> mData;		///< Data

		public:
			Image(uint32_t width, uint32_t height, uint32_t stride,
				PixelFormat pixelformat);
			Image(uint32_t width, uint32_t height, uint32_t stride,
				PixelFormat pixelformat, std::unique_ptr<uint8_t[]> data);
			~Image();

			uint32_t GetWidth() const;
			uint32_t GetHeight() const;
			uint32_t GetStride() const;

			PixelFormat GetPixelFormat() const;

			Color GetPixel(uint32_t x, uint32_t y) const;
			void SetPixel(uint32_t x, uint32_t y, Color color);

			uint8_t const* GetData() const;
		};
	}
}

#endif //APOLLO_IMAGES_IMAGE_H
