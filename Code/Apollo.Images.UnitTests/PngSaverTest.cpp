//------------------------------------------------------------------------------
// PngSaverTest.cpp
//
// PngSaver Test Class
//
// Part of Apollo.Images
// (c) 2021 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "Color.h"
#include "PngLoader.h"
#include "PngSaver.h"
#include "InvalidPngException.h"
#include "PathHelper.h"

#ifdef _WINDOWS
	#define LoadImageA LoadImage
#endif

using namespace std;

namespace Apollo
{
	namespace Images
	{
		namespace UnitTests
		{
			namespace PngSaverTest
			{
				shared_ptr<Image> Create2x2Image(PixelFormat pixelformat)
				{
					auto image = make_shared<Image>(2, 2, 8, pixelformat);

					image->SetPixel(0, 0, { 255, 0, 0 });
					image->SetPixel(1, 0, { 0, 255, 0 });
					image->SetPixel(0, 1, { 0, 0, 255 });
					image->SetPixel(1, 1, { 255, 255, 0 });

					return image;
				}

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
				TEST(PngSaverTest, RGBA_2x2)
				{
					//Setup
					auto pngsaver = make_shared<PngSaver>();
					auto pngloader = make_shared<PngLoader>();

					string path = PathHelper::GetExecutablePath();
					path = path + "/GeneratedTestImages/RGBA_2x2.png";

					auto image = Create2x2Image(PixelFormat::R8G8B8A8);

					//Run
					pngsaver->SaveImage(image.get(), path);

					//Check
					auto loadedimage = pngloader->LoadImage(path);

					EXPECT_EQ(image->GetWidth(), 2);
					EXPECT_EQ(image->GetHeight(), 2);
					EXPECT_EQ(image->GetPixelFormat(), PixelFormat::R8G8B8A8);
					Check2x2Image(loadedimage.get());
				}

				//RGB 2x2
				TEST(PngSaverTest, RGB_2x2)
				{
					//Setup
					auto pngsaver = make_shared<PngSaver>();
					auto pngloader = make_shared<PngLoader>();

					string path = PathHelper::GetExecutablePath();
					path = path + "/GeneratedTestImages/RGB_2x2.png";

					auto image = Create2x2Image(PixelFormat::R8G8B8);

					//Run
					pngsaver->SaveImage(image.get(), path);

					//Check
					auto loadedimage = pngloader->LoadImage(path);

					EXPECT_EQ(image->GetWidth(), 2);
					EXPECT_EQ(image->GetHeight(), 2);
					EXPECT_EQ(image->GetPixelFormat(), PixelFormat::R8G8B8);
					Check2x2Image(loadedimage.get());
				}

				//Unsupported Pixel Format (Currently using 4bit)
				TEST(PngSaverTest, UnsupportedPixelFormat)
				{
					//Setup
					auto pngsaver = make_shared<PngSaver>();
					const auto expectedmessage = "Could not extract/unsupported pixel format";

					auto image = make_shared<Image>(2, 2, 8, PixelFormat::Unknown);

					string path = PathHelper::GetExecutablePath();
					path = path + "/GeneratedTestImages/Unknown_2x2.png";

					//Run
					try
					{
						pngsaver->SaveImage(image.get(), path);
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
}