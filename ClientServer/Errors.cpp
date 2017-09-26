/*!
\file Errors.cpp
\brief definition of Errors functions
\author Friday
*/

#include "Errors.hpp"

namespace Network
{
	namespace Errors
	{
		int Get()
		{
#ifdef _WIN32
			return WSAGetLastError();
#else
			return errno;
#endif
		}
	}
}