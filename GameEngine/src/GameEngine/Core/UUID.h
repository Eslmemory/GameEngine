#pragma once
#include "Core.h"
#include <xhash>

namespace GE {
	class GE_API UUID {
	public:
		UUID();
		UUID(uint64_t& id);
		UUID(const UUID& uuid);

		operator uint32_t() { return m_UUID; }
		operator const uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};
}

namespace std {

	template<>
	struct hash<GE::UUID> {
		std::size_t operator()(const GE::UUID& uuid) const {
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}