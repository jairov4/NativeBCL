#include "BCL.h"

namespace System
{
	OverflowException::OverflowException()
	{
	}

	OverflowException::OverflowException(String message) : SystemException(message)
	{
	}

	OverflowException::OverflowException(String message, ref<Exception> innerException) : SystemException(message, innerException)
	{
	}
}