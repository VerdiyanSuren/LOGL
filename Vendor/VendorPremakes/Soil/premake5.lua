--------------------------------------------------------------------------------------------	
-- 										Project Soil
--------------------------------------------------------------------------------------------	
project "Soil"
	kind "StaticLib"
	language "C"
	

	targetdir 	("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir 		("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/SOIL/**.h",
		"src/*.c",
		"src/original/*.c"
	}	
	
	includedirs
	{
		"include"
	}	
	
	
	filter "system:windows"
		staticruntime "On"		
		--systemversion "latest"

		
		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		
		