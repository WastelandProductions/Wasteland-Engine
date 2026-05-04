workspace "Wasteland"
	architecture "x64"
	startproject "DemonCore-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories releative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Wasteland/vendor/GLFW/include"
IncludeDir["Glad"] = "Wasteland/vendor/Glad/include"
IncludeDir["ImGui"] = "Wasteland/vendor/imgui"
IncludeDir["glm"] = "Wasteland/vendor/glm"
IncludeDir["stb_image"] = "Wasteland/vendor/stb_image"
IncludeDir["entt"] = "Wasteland/vendor/entt/single_include"

group "Dependencies"
	include "Wasteland/vendor/GLFW"
	include "Wasteland/vendor/Glad"
	include "Wasteland/vendor/imgui"

group ""

project "Wasteland"
	location "Wasteland"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "wlpch.h"
	pchsource "Wasteland/src/wlpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions
		{
			"/utf-8"
		}

		defines
		{
			"WL_PLATFORM_WINDOWS",
			"WL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "WL_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "WL_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "WL_DIST"
		optimize "On"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Wasteland/vendor/spdlog/include",
		"Wasteland/vendor",
		"Wasteland/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Wasteland",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions
		{
			"/utf-8"
		}

		defines
		{
			"WL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "WL_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "WL_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "WL_DIST"
		optimize "On"
		runtime "Release"

project "DemonCore-Editor"
	location "DemonCore-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Wasteland/vendor/spdlog/include",
		"Wasteland/vendor",
		"Wasteland/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Wasteland",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions
		{
			"/utf-8"
		}

		defines
		{
			"WL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "WL_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "WL_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "WL_DIST"
		optimize "On"
		runtime "Release"