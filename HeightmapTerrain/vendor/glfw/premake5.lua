project "GLFW"
    kind "StaticLib"
    language "C"
	staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/GLFW/glfw3.h",
		"include/GLFW/glfw3native.h",

		"src/glfw_config.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/vulkan.c",
		"src/window.c"
	}

	includedirs
	{
		"include"
	}
    
    filter "system:windows"
        systemversion "latest"
 
		files
		{
			"src/win32_init.c",
			"src/win32_joystick.c",
			"src/win32_monitor.c",
			"src/win32_time.c",
			"src/win32_thread.c",
			"src/win32_window.c",
			"src/wgl_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c"
		}


      defines
	  {
	 	"_GLFW_WIN32",
		"_CRT_SECURE_NO_WARNINGS",
	 	"HEIGHT_PLATFORM_WINDOWS"
	  }


     filter "configurations:Debug"
	 	defines "HEIGHT_DEBUG"
        runtime "Debug"
        symbols "on"             -- Deixamos on os debug symbols
        
     filter "configurations:Release"
	 	defines "HEIGHT_RELEASE"
        runtime "Release"
        optimize "on"            -- Ripamos todas as configura��es de debug e otimizamos o projeto


     filter "configurations:Dist"
	 defines "HEIGHT_DIST"
	 runtime "Release"
	 symbols "Off"
	 optimize "Full"