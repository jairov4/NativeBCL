#include "BCL.h"

namespace System
{
	static const String baseMessage = u"";

	ArgumentOutOfRangeException::ArgumentOutOfRangeException()
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(String paramName) : ArgumentException(baseMessage, paramName)
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(String message, ref<Exception> innerException) : ArgumentException(message, innerException)
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(String param, String message) : ArgumentException(message, param)
	{
	}
	
}