#include "BCL.h"

namespace System
{
	NotImplementedException::NotImplementedException()
	{
	}

	NotImplementedException::NotImplementedException(String message) : Exception(message)
	{
	}

	NotImplementedException::NotImplementedException(String message, ref<Exception> innerException) : Exception(message, innerException)
	{
	}
}