#ifndef ERRORS_HPP
#define ERRORS_HPP

/*!
	\file Erros.hpp
	\brief declaration of network errors' type and functions
	\author Friday
*/


/////////////////////////////////////////
//preprocessor compatibility managment//
///////////////////////////////////////
#ifdef _WIN32
	#include <WinSock2.h>
#else
	#include <cerrno>
	#define SOCKET int
	#define INVALID_SOCKET ((int)-1)
	#define SOCKET_ERROR (int(-1))
#endif
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////


/*!
	\namespace Network

	\brief contains all network things
*/
namespace Network
{

	/*!
		\namespace Errors

		\brief contains error values and function
	*/
	namespace Errors
	{
		/*!
			\brief to get the last network error

			\return error code
		*/
		int Get();

		/*!
			\enum
		*/
		enum {
#ifdef _WIN32
			AGAIN = WSATRY_AGAIN,/*!< Nonauthoritative host not found */
			WOULDBLOCK = WSAEWOULDBLOCK,/*!< Ressource temporarily unavailable*/
			INPROGRESS = WSAEINPROGRESS,/*!< Operation in progress*/
			INTR = WSAEINTR,/*!< Interrupted function call*/
#else
			AGAIN = EAGAIN,/*!< Nonauthoritative host not found */
			WOULDBLOCK = EWOULDBLOCK,/*!< Ressource temporarily unavailable*/
			INPROGRESS = EINPROGRESS,/*!< Operation in progress*/
			INTR = EINTR,/*!< Interrupted function call*/
#endif
		};
	}
}

#endif