//------------------------------------------------------------------------------
// PngSaver.cpp
//
// PNG Saver Class
//
// Part of Apollo.Images
// (c) 2021 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#include "PngSaver.h"
#include <fstream>
#include <filesystem>
#include <png.h>
#include <zlib.h>
#include "InvalidPngException.h"

using namespace std;
using namespace Apollo::Images;

namespace fs = std::filesystem;

void PngSaver::SaveImage(Image* image, std::string path)
{
	fstream file;

	auto fspath = fs::path(path);
	auto dirpath = fspath.parent_path();

	fs::create_directories(dirpath);

	//Open File
	file.open(path.c_str(), ios::out | ios::binary);

	if (!file)
	{
		throw exception("Failed to open file for writing");
	}

	//Create PNG write structure
	auto pngptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

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
		png_destroy_write_struct(&pngptr, nullptr);
		throw InvalidPngException("Could not create png_info");
	}

	//Set Write Function
	png_set_write_fn(pngptr, static_cast<png_voidp>(&file), UserWriteData, nullptr);

	//Build Header
	auto header = BuildHeader(image);

	//Set Header
	SetHeader(pngptr, infoptr, header);

	//Add Data
	AddData(pngptr, infoptr, image, header);

	//Write PNG
	png_write_png(pngptr, infoptr, PNG_TRANSFORM_IDENTITY, nullptr);

	//Cleanup
	file.close();
	png_destroy_write_struct(&pngptr, &infoptr);
}

//------------------------------------------------------------------------------
//******************************************************************************
// Internal Methods
//******************************************************************************
//------------------------------------------------------------------------------

PngHeader PngSaver::BuildHeader(Image* image)
{
	uint8_t colortype, channels, channeldepth;

	ExtractPixelFormat(image->GetPixelFormat(), colortype, channels, channeldepth);
	
	PngHeader header;

	header.Width = image->GetWidth();
	header.Height = image->GetHeight();
	header.Stride = image->GetStride();
	header.Channels = channels;
	header.ChannelDepth = channeldepth;
	header.ColorType = colortype;
	header.InterlaceType = PNG_INTERLACE_NONE;
	header.CompressionType = PNG_COMPRESSION_TYPE_DEFAULT;
	header.FilterType = PNG_FILTER_TYPE_DEFAULT;

	return header;
}

void PngSaver::SetHeader(png_structp pngptr, png_infop infoptr, PngHeader& header)
{
	png_set_IHDR(pngptr, infoptr, 
		header.Width, 
		header.Height, 
		header.ChannelDepth, 
		header.ColorType, 
		header.InterlaceType, 
		header.CompressionType, 
		header.FilterType);
}

void PngSaver::AddData(png_structp pngptr, png_infop infoptr, Image* image, PngHeader& header)
{
	if (image->GetHeight() > PNG_UINT_32_MAX / (sizeof(png_byte)))
	{
		throw InvalidPngException("Image is too tall to process in memory");
	}

	if (image->GetWidth() > PNG_UINT_32_MAX / (header.Channels * header.ChannelDepth))
	{
		throw InvalidPngException("Image is too wide to process in memory");
	}

	auto row_pointers = new uint8_t*[image->GetHeight()];

	for (uint32_t i = 0; i < image->GetHeight(); i++)
	{
		row_pointers[i] = nullptr;  /* security precaution */
		row_pointers[i] = const_cast<uint8_t*>(image->GetData()) + (i * header.Stride);		
	}
	
	png_set_rows(pngptr, infoptr, row_pointers);
}

void PngSaver::ExtractPixelFormat(PixelFormat pixelformat, uint8_t& colortype, uint8_t& channels, uint8_t& channeldepth)
{
	switch (pixelformat)
	{
	case PixelFormat::R8G8B8A8:
		colortype = PNG_COLOR_TYPE_RGBA;
		channels = 4;
		channeldepth = 8;
		break;
	case PixelFormat::R8G8B8:
		colortype = PNG_COLOR_TYPE_RGB;
		channels = 3;
		channeldepth = 8;
		break;
	default:
		throw InvalidPngException("Could not extract/unsupported pixel format");
	}
}


//-----------------------------------------------------------------------------
// UserWriteData
//
/// <summary>
/// Custom write function so libpng uses fstream
/// </summary>
//-----------------------------------------------------------------------------
void PngSaver::UserWriteData(png_structp pngPtr, png_bytep data, png_size_t length)
{
	//Get I/O pointer from struct
	png_voidp file = png_get_io_ptr(pngPtr);

	//Cast and write
	static_cast<fstream*>(file)->write(reinterpret_cast<char*>(data), length);
}
