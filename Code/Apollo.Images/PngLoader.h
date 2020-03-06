//------------------------------------------------------------------------------
// PngLoader.h
//
// PNG Loader Class
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifndef APOLLO_IMAGES_PNGLOADER_H
#define APOLLO_IMAGES_PNGLOADER_H

#include <memory>
#include <string>
#include <png.h>
#include "IImageLoader.h"
#include "PngHeader.h"

namespace Apollo
{
	namespace Images
	{
		class PngLoader : public IImageLoader
		{
		public:
			PngLoader();
			~PngLoader();

			std::unique_ptr<Image> LoadImage(std::string path) override;

		private:
			bool IsValid(std::fstream& file);
			PngHeader ReadHeader(png_structp pngptr, png_infop infptr);
			std::unique_ptr<uint8_t[]> ReadData(png_structp pngptr, PngHeader& header);
			PixelFormat GetPixelFormat(PngHeader& header);

			static void UserReadData(png_structp pngPtr, png_bytep data, png_size_t length);
		};
	}
}

#endif //APOLLO_IMAGES_PNGLOADER_H
