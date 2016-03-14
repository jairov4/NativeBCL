#pragma once

#include "BCL.h"

namespace System
{
	inline uint64_t HashSequence64(const uint8_t* buffer, uint64_t count)
	{
		const auto fnv_offset_basis = 14695981039346656037ULL;
		const auto fnv_prime = 1099511628211ULL;

		auto val = fnv_offset_basis;
		while (count--)
		{
			// fold in another byte
			val ^= *buffer++;
			val *= fnv_prime;
		}

		return val;
	}

	inline uint32_t HashSequence32(const uint8_t* buffer, uint64_t count)
	{
		const auto fnv_offset_basis = 2166136261U;
		const auto fnv_prime = 16777619U;

		auto val = fnv_offset_basis;
		while (count--)
		{
			// fold in another byte
			val ^= *buffer++;
			val *= fnv_prime;
		}

		return val;
	}
}