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

using namespace std;

namespace Apollo
{
	namespace Images
	{
		namespace UnitTests
		{
			//Check Defaults
			TEST(ColorTest, ConstructorDefaults)
			{
				//Run
				const auto plugin = Color();

				//Check
				EXPECT_EQ(plugin.R, 0);
				EXPECT_EQ(plugin.G, 0);
				EXPECT_EQ(plugin.B, 0);
				EXPECT_EQ(plugin.A, 255);
			}

			//Check RGB Constructor
			TEST(ColorTest, RGBConstructor)
			{
				//Setup
				const uint8_t r = 12;
				const uint8_t g = 34;
				const uint8_t b = 56;
				
				//Run
				const auto plugin = Color(r, g, b);

				//Check
				EXPECT_EQ(plugin.R, r);
				EXPECT_EQ(plugin.G, g);
				EXPECT_EQ(plugin.B, b);
				EXPECT_EQ(plugin.A, 255);
			}

			//Check RGBA Constructor
			TEST(ColorTest, RGBAConstructor)
			{
				//Setup
				const uint8_t r = 12;
				const uint8_t g = 34;
				const uint8_t b = 56;
				const uint8_t a = 78;

				//Run
				const auto plugin = Color(r, g, b, a);

				//Check
				EXPECT_EQ(plugin.R, r);
				EXPECT_EQ(plugin.G, g);
				EXPECT_EQ(plugin.B, b);
				EXPECT_EQ(plugin.A, a);
			}
		}
	}
}