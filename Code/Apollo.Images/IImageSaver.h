//------------------------------------------------------------------------------
// IImageSaver.h
//
// PNG Saver Interface
//
// Part of Apollo.Images
// (c) 2021 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifndef APOLLO_IMAGES_IIMAGESAVER_H
#define APOLLO_IMAGES_IIMAGESAVER_H

#include <string>
#include "Image.h"

namespace Apollo
{
	namespace Images
	{
		//----------------------------------------------------------
		// IImageSaver
		//
		/// <summary>
		/// Abstract Image Saver Interface
		/// </summary>
		//----------------------------------------------------------
		class IImageSaver
		{
		public:
			//--- Destructor ---
			virtual ~IImageSaver() = default;

			//--- Methods ---
			//----------------------------------------------------------
			// SaveImage
			//
			/// <summary>
			/// Saves an image to a file
			/// </summary>
			/// <param name="image">Image to save</param>
			/// <param name="path">Path to save image</param>
			//----------------------------------------------------------
			virtual void SaveImage(Image* image, std::string path) = 0;
		};
	}
}

#endif //APOLLO_IMAGES_IIMAGESAVER_H
