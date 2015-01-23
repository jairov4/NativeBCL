#include "BCL.h"

namespace System
{
	Exception::Exception() : message(""), innerException(nullptr)
	{
	}

	Exception::Exception(String message) : message(message), innerException(nullptr)
	{
	}

	Exception::Exception(String message, ref<Exception> innerException) : message(message), innerException(innerException)
	{
	}
}