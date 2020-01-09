//------------------------------------------------------------------------------
// PathHelper.h
//
// Path Helper
//
// Part of Apollo.Images
// (c) 2019 Q_Division
// Distributed under MIT license. See LICENSE for details.
//------------------------------------------------------------------------------

#ifdef _WINDOWS
	#include <Windows.h>
#else
	#include <unistd.h>
#endif
#include <string>

namespace Apollo
{
	namespace Images
	{
		namespace UnitTests
		{
			namespace PathHelper
			{
				static std::string GetExecutablePath()
				{
					std::string path;

					char buffer[256];
					size_t buffersize = 256;

					#ifdef _WINDOWS
						GetModuleFileName(NULL, buffer, buffersize);

						path = buffer;

						auto index = path.find_last_of('\\');
						path = path.substr(0, index);
					#else
						readlink("/proc/self/exe", buffer, buffersize);

						path = buffer;

						auto index = path.find_last_of('/');
						path = path.substr(0, index);
					#endif

					return path;
				}
			}
		}
	}
}
