//------------------------------------------------------------------------------
// PngHeader.h
//
// PNG Header Model
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifndef APOLLO_IMAGES_PNGHEADER_H
#define APOLLO_IMAGES_PNGHEADER_H

namespace Apollo
{
	namespace Images
	{
		struct PngHeader
		{
			//Read Values
			uint32_t Width;				///< Width
			uint32_t Height;			///< Height
			uint32_t Stride;			///< Stride
			uint8_t Channels;			///< Number of channels
			uint8_t ChannelDepth;		///< Bit depth of a channel
			uint8_t ColorType;			///< Color Type
			uint8_t InterlaceType;		///< Interlace Type
			uint8_t CompressionType;	///< Compression Method
			uint8_t FilterType;			///< Filter Method
		};
	}
}

#endif //APOLLO_IMAGES_PNGHEADER_H
