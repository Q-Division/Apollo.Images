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

#include <stdexcept>

using namespace std;
using namespace Apollo::Images;

Image::Image(uint32_t width, uint32_t height, uint32_t stride,
	PixelFormat pixelformat)
	:mWidth(width), mHeight(height), mStride(stride), mPixelFormat(pixelformat)
{
	mData = unique_ptr<uint8_t[]>(new uint8_t[mHeight * mStride]);
}

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

uint32_t Image::GetStride() const
{
	return mStride;
}

PixelFormat Image::GetPixelFormat() const
{
	return mPixelFormat;
}

Color Image::GetPixel(uint32_t x, uint32_t y) const
{
	if(x >= mWidth)
	{
		throw out_of_range("X >= Width");
	}

	if(y >= mHeight)
	{
		throw out_of_range("Y >= Height");
	}
	
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

void Apollo::Images::Image::SetPixel(uint32_t x, uint32_t y, Color color)
{
	if (x >= mWidth)
	{
		throw out_of_range("X >= Width");
	}

	if (y >= mHeight)
	{
		throw out_of_range("Y >= Height");
	}

	if (mPixelFormat == PixelFormat::R8G8B8)
	{
		const uint32_t index = (y * mStride) + (x * 3);

		mData[index] = color.R;		//R
		mData[index + 1] = color.G;	//G
		mData[index + 2] = color.B;	//B
	}
	else
	{
		const uint32_t index = (y * mStride) + (x * 4);

		mData[index] = color.R;		//R
		mData[index + 1] = color.G;	//G
		mData[index + 2] = color.B;	//B
		mData[index + 3] = color.A;	//A
	}
}

uint8_t const* Image::GetData() const
{
	return mData.get();
}
