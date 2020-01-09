//------------------------------------------------------------------------------
// ColorTest.cpp
//
// Color Test Class
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "Color.h"
#include "PngLoader.h"
#include "InvalidPngException.h"
#include "PathHelper.h"

#ifdef _WINDOWS
	#define LoadImage LoadImage
#endif

using namespace std;

namespace Apollo
{
	namespace Images
	{
		namespace UnitTests
		{
			void Check2x2Image(Image* image)
			{
				//0,0 = Red
				EXPECT_EQ(image->GetPixel(0, 0).R, 255);
				EXPECT_EQ(image->GetPixel(0, 0).G, 0);
				EXPECT_EQ(image->GetPixel(0, 0).B, 0);
				EXPECT_EQ(image->GetPixel(0, 0).A, 255);

				//1,0 = Green
				EXPECT_EQ(image->GetPixel(1, 0).R, 0);
				EXPECT_EQ(image->GetPixel(1, 0).G, 255);
				EXPECT_EQ(image->GetPixel(1, 0).B, 0);
				EXPECT_EQ(image->GetPixel(1, 0).A, 255);

				//0,1 = Green
				EXPECT_EQ(image->GetPixel(0, 1).R, 0);
				EXPECT_EQ(image->GetPixel(0, 1).G, 0);
				EXPECT_EQ(image->GetPixel(0, 1).B, 255);
				EXPECT_EQ(image->GetPixel(0, 1).A, 255);

				//1,1 = Yellow
				EXPECT_EQ(image->GetPixel(1, 1).R, 255);
				EXPECT_EQ(image->GetPixel(1, 1).G, 255);
				EXPECT_EQ(image->GetPixel(1, 1).B, 0);
				EXPECT_EQ(image->GetPixel(1, 1).A, 255);
			}
			
			//RGBA 2x2
			TEST(PngLoaderTest, RGBA_2x2)
			{
				//Setup
				auto pngloader = make_shared<PngLoader>();

				string path = PathHelper::GetExecutablePath();
				path = path + "/TestImages/RGBA_2x2.png";
				
				//Run
				auto image = pngloader->LoadImage(path);

				//Check
				EXPECT_EQ(image->GetWidth(), 2);
				EXPECT_EQ(image->GetHeight(), 2);
				EXPECT_EQ(image->GetPixelFormat(), PixelFormat::R8G8B8A8);
				Check2x2Image(image.get());
			}

			//RGB 2x2
			TEST(PngLoaderTest, RGB_2x2)
			{
				//Setup
				auto pngloader = make_shared<PngLoader>();
				string path = PathHelper::GetExecutablePath();
				path = path + "/TestImages/RGB_2x2.png";
				
				//Run
				auto image = pngloader->LoadImage(path);

				//Check
				EXPECT_EQ(image->GetWidth(), 2);
				EXPECT_EQ(image->GetHeight(), 2);
				EXPECT_EQ(image->GetPixelFormat(), PixelFormat::R8G8B8);
				Check2x2Image(image.get());
			}

			//Not A PNG
			TEST(PngLoaderTest, NotAPng)
			{
				//Setup
				auto pngloader = make_shared<PngLoader>();
				const auto expectedmessage = "It is not a PNG file";

				string path = PathHelper::GetExecutablePath();
				path = path + "/TestImages/NotAPng.txt";
				
				//Run
				try
				{
					auto image = pngloader->LoadImage(path);
				}
				catch (const InvalidPngException & ex)
				{
					//Correct Exception, Check Message
					EXPECT_STREQ(ex.what(), expectedmessage);
				}
				catch(...)
				{
					//Failed, wrong exception
					FAIL();
				}
			}

			//Unsupported Pixel Format (Currently using 4bit)
			TEST(PngLoaderTest, UnsupportedPixelFormat)
			{
				//Setup
				auto pngloader = make_shared<PngLoader>();
				const auto expectedmessage = "Invalid or Unsupported Pixel Format";

				string path = PathHelper::GetExecutablePath();
				path = path + "/TestImages/4bit_2x2.png";

				//Run
				try
				{
					auto image = pngloader->LoadImage(path);
				}
				catch (const InvalidPngException & ex)
				{
					//Correct Exception, Check Message
					EXPECT_STREQ(ex.what(), expectedmessage);
				}
				catch (...)
				{
					//Failed, wrong exception
					FAIL();
				}
			}
		}
	}
}