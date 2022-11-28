//------------------------------------------------------------------------------
// PngSaver.h
//
// PNG Saver Class
//
// Part of Apollo.Images
// (c) 2021 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifndef APOLLO_IMAGES_PNGSAVER_H
#define APOLLO_IMAGES_PNGSAVER_H

#include <memory>
#include <string>
#include <png.h>
#include "IImageSaver.h"
#include "PngHeader.h"

namespace Apollo
{
	namespace Images
	{
		class PngSaver : public IImageSaver
		{
		public:
			PngSaver() = default;
			~PngSaver() = default;

			void SaveImage(Image* image, std::string path) override;

		private:
			PngHeader BuildHeader(Image* image);
			void SetHeader(png_structp pngptr, png_infop infptr, PngHeader& header);
			void AddData(png_structp pngptr, png_infop infptr, Image* image, PngHeader& header);
			
			void ExtractPixelFormat(PixelFormat pixelformat, uint8_t& colortype, uint8_t& channels, uint8_t& channeldepth);

			static void UserWriteData(png_structp pngPtr, png_bytep data, png_size_t length);
		};
	}
}

#endif //APOLLO_IMAGES_PNGSAVER_H
