//------------------------------------------------------------------------------
// IImageLoader.h
//
// PNG Loader Interface
//
// Part of Apollo.Images
// (c) 2020 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifndef APOLLO_IMAGES_IIMAGELOADER_H
#define APOLLO_IMAGES_IIMAGELOADER_H

#include <string>
#include "Image.h"

namespace Apollo
{
	namespace Images
	{
		//----------------------------------------------------------
		// IImageLoader
		//
		/// <summary>
		/// Abstract Image Loader Interface
		/// </summary>
		//----------------------------------------------------------
		class IImageLoader
		{
		public:
			//--- Destructor ---
			virtual ~IImageLoader() = default;

			//--- Methods ---
			//----------------------------------------------------------
			// LoadImage
			//
			/// <summary>
			/// Loads an image from a file
			/// </summary>
			/// <param name="path">Path to image file</param>
			/// <returns>Loaded image</returns>
			//----------------------------------------------------------
			std::unique_ptr<Image> LoadImage(std::string path);
		};
	}
}

#endif //APOLLO_IMAGES_IIMAGELOADER_H
