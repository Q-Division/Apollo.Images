//------------------------------------------------------------------------------
// ImageTest.cpp
//
// Image Test Class
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "Image.h"

using namespace std;

namespace Apollo
{
	namespace Images
	{
		namespace UnitTests
		{
			//Get Width
			TEST(ImageTest, GetWidth)
			{
				//Setup
				uint32_t width = 256;
				auto data = make_unique<uint8_t[]>(2);

				auto image = make_shared<Image>(width, 123, 456, PixelFormat::R8G8B8A8, move(data));
				
				//Run
				auto imagewidth = image->GetWidth();

				//Check
				EXPECT_EQ(imagewidth, width);
			}

			//Get Height
			TEST(ImageTest, GetHeight)
			{
				//Setup
				uint32_t height = 345;
				auto data = make_unique<uint8_t[]>(2);

				auto image = make_shared<Image>(123, height, 456, PixelFormat::R8G8B8A8, move(data));

				//Run
				auto imageheight = image->GetHeight();

				//Check
				EXPECT_EQ(imageheight, height);
			}

			//Get Stride
			TEST(ImageTest, GetStride)
			{
				//Setup
				uint32_t stride = 456;
				auto data = make_unique<uint8_t[]>(2);

				auto image = make_shared<Image>(123, 345, stride, PixelFormat::R8G8B8A8, move(data));

				//Run
				auto imagestride = image->GetStride();

				//Check
				EXPECT_EQ(imagestride, stride);
			}

			//Get Pixel Format
			TEST(ImageTest, GetPixelFormat)
			{
				//Setup
				auto format = PixelFormat::R8G8B8A8;
				auto data = make_unique<uint8_t[]>(2);

				auto image = make_shared<Image>(123, 234, 456, format, move(data));

				//Run
				auto imageformat = image->GetPixelFormat();

				//Check
				EXPECT_EQ(imageformat, format);
			}

			//Get Pixel (RGBA)
			TEST(ImageTest, GetPixel_RGBA)
			{
				//Setup
				auto data = make_unique<uint8_t[]>(16);
				data[0] = 220;
				data[1] = 230;
				data[2] = 240;
				data[3] = 250;
				
				auto image = make_shared<Image>(2, 2, 8, PixelFormat::R8G8B8A8, move(data));

				//Run
				auto color = image->GetPixel(0, 0);

				//Check
				EXPECT_EQ(color.R, 220);
				EXPECT_EQ(color.G, 230);
				EXPECT_EQ(color.B, 240);
				EXPECT_EQ(color.A, 250);
			}

			//Get Pixel (RGB)
			TEST(ImageTest, GetPixel_RGB)
			{
				//Setup
				auto data = make_unique<uint8_t[]>(12);
				data[0] = 220;
				data[1] = 230;
				data[2] = 240;

				auto image = make_shared<Image>(2, 2, 8, PixelFormat::R8G8B8, move(data));

				//Run
				auto color = image->GetPixel(0, 0);

				//Check
				EXPECT_EQ(color.R, 220);
				EXPECT_EQ(color.G, 230);
				EXPECT_EQ(color.B, 240);
				EXPECT_EQ(color.A, 255);
			}

			//Get Pixel (x = width)
			TEST(ImageTest, GetPixel_XisWidth)
			{
				//Setup
				auto data = make_unique<uint8_t[]>(16);
				auto image = make_shared<Image>(2, 2, 8, PixelFormat::R8G8B8A8, move(data));
				const auto expectedmessage = "X >= Width";

				//Run
				auto correctexception = false;
				
				try
				{
					auto color = image->GetPixel(2, 0);
				}
				catch (const out_of_range& ex)
				{
					//Correct Exception, Check Message
					correctexception = true;
					
					EXPECT_STREQ(ex.what(), expectedmessage);
				}

				if (!correctexception)
				{
					//Failed, wrong exception
					FAIL();
				}
			}

			//Get Pixel (y = height)
			TEST(ImageTest, GetPixel_YisHeight)
			{
				//Setup
				auto data = make_unique<uint8_t[]>(16);
				auto image = make_shared<Image>(2, 2, 8, PixelFormat::R8G8B8A8, move(data));
				const auto expectedmessage = "Y >= Height";

				//Run
				auto correctexception = false;
				
				try
				{
					auto color = image->GetPixel(0, 2);
				}
				catch (const out_of_range& ex)
				{
					//Correct Exception, Check Message
					correctexception = true;
				
					EXPECT_STREQ(ex.what(), expectedmessage);
				}

				if(!correctexception)
				{
					//Failed, wrong exception
					FAIL();
				}
			}
			
			//Get Data
			TEST(ImageTest, GetData_RGBA)
			{
				//Setup
				auto srcdata = make_unique<uint8_t[]>(16);

				for(uint8_t i = 0; i < 16; i++)
				{
					srcdata[i] = 250 - i;
				}
					
				auto image = make_shared<Image>(2, 2, 8, PixelFormat::R8G8B8A8, move(srcdata));

				//Run
				auto imgdata = image->GetData();

				//Check
				for (uint8_t i = 0; i < 16; i++)
				{
					EXPECT_EQ(imgdata[i], 250 - i);		
				}
			}			
			
		}
	}
}