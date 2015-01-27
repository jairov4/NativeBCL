#include "BCL.h"

namespace System
{
	ArgumentException::ArgumentException()
	{
	}

	ArgumentException::ArgumentException(String message) : SystemException(message)
	{
	}

	ArgumentException::ArgumentException(String message, ref<Exception> innerException) : SystemException(message, innerException)
	{
	}
	
	ArgumentException::ArgumentException(String message, String paramName) : SystemException(message), paramName(paramName)
	{
	}
	
	ArgumentException::ArgumentException(String message, String paramName, ref<Exception> innerException) : SystemException(message, innerException), paramName(paramName)
	{
	}
	
}