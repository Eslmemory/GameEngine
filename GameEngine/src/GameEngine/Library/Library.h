#pragma once
#include "GameEngine/Core/PublicSingleton.h"
#include "GameEngine/Core/Core.h"
#include "GameEngine/Core/Log.h"
#include <unordered_map>

namespace GE {
	
	template<template<typename> typename LibraryType, typename ContentType>
	class LibraryBase : public Singleton<LibraryType<ContentType>> {
	public:
		void Add(const std::string& name, const std::shared_ptr<ContentType>& mem) {
			GE_CORE_ASSERT(m_Library.find(name) == m_Library, "Already have this member in Library");
			m_Library[name] = mem;
		}

		void Set(const std::string& name, const std::shared_ptr<ContentType>& mem) {
			GE_CORE_ASSERT(m_Library.find(name) != m_Library, "Already have this member in Library");
			m_Library[name] = mem;
		}

		std::shared_ptr<ContentType> Get(const std::string& name) {
			GE_CORE_ASSERT(m_Library.find(name) != m_Library, "Already have this member in Library");
			return m_Library[name];
		}

	protected:
		std::unordered_map<std::string, std::shared_ptr<ContentType>> m_Library;
	};

	template<typename ContentType>
	class Library : public LibraryBase<Library, ContentType> {
	public:
		Library();
	};
}