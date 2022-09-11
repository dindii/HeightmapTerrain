workspace "HeightmapTerrain"
		architecture "x64"
		startproject "HeightmapTerrain"


configurations
{
	"Debug",
	"Release",
	"Dist"
}

characterset ("MBCS")

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 IncludeDir = {}
  IncludeDir["glad"] = "HeightmapTerrain/vendor/glad/include"
  IncludeDir["stbi"] = "HeightmapTerrain/vendor/stbi"
  IncludeDir["glfw"] = "HeightmapTerrain/vendor/glfw/include"

  group "Dependencies"
  include "HeightmapTerrain/vendor/glad"
  include "HeightmapTerrain/vendor/glfw"
  group ""

project "HeightmapTerrain"
	location "HeightmapTerrain"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.glad}",
		"%{IncludeDir.stbi}",
		"%{IncludeDir.glfw}"
	}
	
	links
	{
		"glad",
		"GLFW"
	}

	filter "system:windows"
	systemversion "latest"

	defines
	{
		"HEIGHT_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
	defines "HEIGHT_DEBUG"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	defines "HEIGHT_RELEASE"
	runtime "Release"
	optimize "Debug"

	filter "configurations:Dist"
	defines "HEIGHT_DIST"
	runtime "Release"
	symbols "Off"
	optimize "Full"