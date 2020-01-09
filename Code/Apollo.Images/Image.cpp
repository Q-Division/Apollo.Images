//------------------------------------------------------------------------------
// Image.cpp
//
// Image Class
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#include "Image.h"

using namespace std;
using namespace Apollo::Images;

Image::Image(uint32_t width, uint32_t height, uint32_t stride, 
	         PixelFormat pixelformat, unique_ptr<uint8_t[]> data)
	:mWidth(width), mHeight(height), mStride(stride), mPixelFormat(pixelformat),
	 mData(std::move(data))
{
}

Image::~Image()
{
	mData = nullptr;
}

uint32_t Image::GetWidth() const
{
	return mWidth;
}

uint32_t Image::GetHeight() const
{
	return mHeight;
}

PixelFormat Image::GetPixelFormat() const
{
	return mPixelFormat;
}

Color Image::GetPixel(uint32_t x, uint32_t y) const
{
	if (mPixelFormat == PixelFormat::R8G8B8)
	{
		const uint32_t index = (y * mStride) + (x * 3);

		const uint8_t r = mData[index];		//R
		const uint8_t g = mData[index + 1];	//G
		const uint8_t b = mData[index + 2];	//B

		return { r, g, b };
	}
	else
	{
		const uint32_t index = (y * mStride) + (x * 4);

		const uint8_t r = mData[index];		//R
		const uint8_t g = mData[index + 1];	//G
		const uint8_t b = mData[index + 2];	//B
		const uint8_t a = mData[index + 3];	//A

		return { r, g, b, a };
	}
}
