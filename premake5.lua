workspace "GameEngine"
	architecture "x64"
	configurations { "Debug", "Release" }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{prj.name}/vendor/GLFW/include"
IncludeDir["Glad"] = "%{prj.name}/vendor/Glad/include"
IncludeDir["ImGui"] = "%{prj.name}/vendor/imgui"
IncludeDir["ImGuizmo"] = "%{prj.name}/vendor/imgui/ImGuizmo"
IncludeDir["glm"] = "%{prj.name}/vendor/glm"
IncludeDir["assimp"] = "%{prj.name}/vendor/assimp/include"

LibDir = {}
LibDir["assimp"] = "%{prj.name}/vendor/assimp/lib"

include "GameEngine/vendor/GLFW"
include "GameEngine/vendor/Glad"
include "GameEngine/vendor/imgui"
include "GameEngine/vendor/ImGuizmo"

project "GameEngine"
	location "GameEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on" 

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "%{prj.name}/src/gepch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/stb_image.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/entt/include/entt.hpp"
	}

	defines{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.assimp}",
		"%{prj.name}/vendor/stb_image",
		"%{prj.name}/vendor/entt/include"
	}

	libdirs{
		"%{LibDir.assimp}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"ImGuizmo",
		"assimp-vc143-mtd.lib"
	}

	filter "system:Windows"
		systemversion "latest"
		defines {
			"GE_BUILD_DLL",
			"WINDOW_PLATFORM_DLL"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "GameEngineEditor"
	location "GameEngineEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on" 

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"GameEngine/src",
		"GameEngine/vendor",
		"GameEngine/vendor/spdlog/include",
		"GameEngine/vendor/glm",
		"GameEngine/vendor/entt/include",
		"GameEngine/vendor/assimp/include",
		"GameEngine/vendor/ImGuizmo",
		"%{prj.name}/src"
	}

	links{
		"GameEngine"
	}

	filter "system:Windows"
		systemversion "latest"
		defines{
			"WINDOW_PLATFORM_DLL"
		}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"