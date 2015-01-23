#include "BCL.h"

namespace System
{
	InvalidOperationException::InvalidOperationException()
	{
	}

	InvalidOperationException::InvalidOperationException(String message) : Exception(message)
	{
	}

	InvalidOperationException::InvalidOperationException(String message, ref<Exception> innerException) : Exception(message, innerException)
	{
	}
}