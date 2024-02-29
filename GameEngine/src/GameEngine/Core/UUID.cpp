#include "gepch.h"
#include "UUID.h"

#include <random>
#include <unordered_map>

namespace GE {

	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UnifromDistribution;

	UUID::UUID() 
		: m_UUID(s_UnifromDistribution(s_Engine))
	{
		
	}

	UUID::UUID(uint64_t& id)
		: m_UUID(id) 
	{
	}

	UUID::UUID(const UUID& uuid)
		: m_UUID(uuid.m_UUID)
	{
	}
}