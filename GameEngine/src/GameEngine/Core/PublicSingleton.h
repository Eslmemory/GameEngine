#pragma once
#include "Core.h"

namespace GE {
	
	template<typename T>
	class GE_API Singleton {
	protected:
		Singleton() = default;

	public:
		static T& GetInstance() {
			static T instance;
			return instance;
		}

		virtual ~Singleton() = default;
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
	};
}