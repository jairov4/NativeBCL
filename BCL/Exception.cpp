#include "BCL.h"

namespace System
{
	Exception::Exception() : innerException(nullptr), message("")
	{
	}

	Exception::Exception(String message) : innerException(nullptr), message(message)
	{
	}

	Exception::Exception(String message, ref<Exception> innerException) : innerException(innerException), message(message)
	{
	}
}