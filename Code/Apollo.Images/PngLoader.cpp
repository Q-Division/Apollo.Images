//------------------------------------------------------------------------------
// PngLoader.cpp
//
// PNG Loader Class
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#include "PngLoader.h"
#include <fstream>
#include "png.h"
#include "zlib.h"
#include "InvalidPngException.h"

using namespace std;
using namespace Apollo::Images;

PngLoader::PngLoader()
{
}

PngLoader::~PngLoader()
{
}

unique_ptr<Image> PngLoader::LoadImage(string path)
{
	fstream file;

	//Open File
	file.open(path.c_str(), ios::in | ios::binary);

	//Check for Valid PNG (Check for Signature)
	if(!IsValid(file))
	{
		file.close();
		throw InvalidPngException("It is not a PNG file");
	}

	//Create PNG read structure
	auto pngptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

	if(!pngptr)
	{
		file.close();
		throw InvalidPngException("Could not create png_struct");
	}

	//Create PNG info structure
	auto infoptr = png_create_info_struct(pngptr);

	if (!infoptr)
	{
		file.close();
		png_destroy_read_struct(&pngptr, nullptr, nullptr);
		throw InvalidPngException("Could not create png_info");
	}

	//Set Read Function
	png_set_read_fn(pngptr, static_cast<png_voidp>(&file), UserReadData);

	//Read Header
	auto header = ReadHeader(pngptr, infoptr);

	//Read Data
	auto data = ReadData(pngptr, header);

	//Cleanup
	file.close();
	png_destroy_read_struct(&pngptr, &infoptr, nullptr);

	//Get PixelFormat
	auto pixelformat = GetPixelFormat(header);

	if(pixelformat == PixelFormat::Unknown)
	{
		throw InvalidPngException("Invalid or Unsupported Pixel Format");
	}

	//Create Image
	auto image = make_unique<Image>(header.Width, header.Height, header.Stride,
									pixelformat, std::move(data));

	//Return Image
	return image;
}

//------------------------------------------------------------------------------
//******************************************************************************
// Internal Methods
//******************************************************************************
//------------------------------------------------------------------------------

bool PngLoader::IsValid(fstream& file)
{
	png_byte pngsig[8];
	file.read(reinterpret_cast<char*>(pngsig), 8);

	return  !png_sig_cmp(pngsig, 0, 8);
}

PngHeader PngLoader::ReadHeader(png_structp pngptr, png_infop infoptr)
{
	//Set Signature Bytes (have already been read)
	png_set_sig_bytes(pngptr, 8);

	//Read Header into info block
	png_read_info(pngptr, infoptr);

	PngHeader header;

	header.Width = png_get_image_width(pngptr, infoptr);
	header.Height = png_get_image_height(pngptr, infoptr);
	header.Stride = png_get_rowbytes(pngptr, infoptr);
	header.Channels = png_get_channels(pngptr, infoptr);
	header.ChannelDepth = png_get_bit_depth(pngptr, infoptr);
	header.ColorType = png_get_color_type(pngptr, infoptr);
	header.InterlaceType = png_get_interlace_type(pngptr, infoptr);
	header.CompressionType = png_get_compression_type(pngptr, infoptr);
	header.FilterType = png_get_filter_type(pngptr, infoptr);

	return header;
}

std::unique_ptr<uint8_t[]> PngLoader::ReadData(png_structp pngptr, PngHeader& header)
{
	//Calculate Data Size
	const uint32_t datasize = header.Stride * header.Height;

	//Create Data Array
	auto data = unique_ptr<uint8_t[]>(new uint8_t[datasize]);

	//Create row pointers
	const auto rowptrs = new png_bytep[header.Height];

	//Map row pointers to data
	for(uint32_t i = 0; i < header.Height; i++)
	{
		rowptrs[i] = static_cast<png_bytep>(data.get()) + (i * header.Stride);
	}

	//Read Image
	png_read_image(pngptr, rowptrs);

	//Clean up
	delete[] rowptrs;

	return data;
}

PixelFormat PngLoader::GetPixelFormat(PngHeader& header)
{
	if(header.ColorType == PNG_COLOR_TYPE_RGBA)
	{
		if(header.Channels == 4)
		{
			if(header.ChannelDepth == 8)
			{
				return PixelFormat::R8G8B8A8;
			}
		}
	}
	else if (header.ColorType == PNG_COLOR_TYPE_RGB)
	{
		if (header.Channels == 3)
		{
			if (header.ChannelDepth == 8)
			{
				return PixelFormat::R8G8B8;
			}
		}
	}

	return PixelFormat::Unknown;
}

//-----------------------------------------------------------------------------
// UserReadData
//
/// <summary>
/// Custom read function so libpng uses fstream
/// </summary>
//-----------------------------------------------------------------------------
void PngLoader::UserReadData(png_structp pngPtr, png_bytep data, png_size_t length) 
{
	//Get I/O pointer from struct
	png_voidp file = png_get_io_ptr(pngPtr);

	//Cast and read
	static_cast<fstream*>(file)->read(reinterpret_cast<char*>(data), length);
}
