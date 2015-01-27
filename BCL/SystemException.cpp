#include "BCL.h"

namespace System
{
	SystemException::SystemException()
	{
	}

	SystemException::SystemException(String message) : Exception(message)
	{
	}

	SystemException::SystemException(String message, ref<Exception> innerException) : Exception(message, innerException)
	{
	}
}