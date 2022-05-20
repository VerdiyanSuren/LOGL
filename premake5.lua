-- premake5.lua
--------------------------------------------------------------------------------------------	
-- 										Project WORKSPACE
--------------------------------------------------------------------------------------------
workspace "LOGL"
	architecture "x64"
	configurations {"Debug","Release"}
		
	filter {"system:windows","configurations:Debug" }
		symbols 		"On" 
		staticruntime 	"On"	
		defines 		"DEBUG"
		systemversion 	"latest"
			
	filter { "system:windows", "configurations:Release" }
		staticruntime 	"On"
		buildoptions 	"/MT"
		staticruntime 	"off"
		optimize 		"On"
		systemversion 	"latest"
	
outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Vendor/GLFW/include"
IncludeDir["GLAD"] = "Vendor/GLAD/include"
IncludeDir["SOIL"] = "Vendor/SOIL/include"
IncludeDir["ASSIMP"] = "Vendor/Assimp/include"
IncludeDir["GLM"] = "Vendor/glm"

include "Vendor/GLFW"
include "Vendor/GLAD"
include "Vendor/Soil"
include "Vendor/Assimp"
--------------------------------------------------------------------------------------------	
-- 										Project LOGLCore
--------------------------------------------------------------------------------------------
project "LOGLCore"
	kind "ConsoleApp"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir 	  ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/sources/**.cpp"
	}
	includedirs 
	{		
		"%{prj.name}/include/",		
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.SOIL}",
		"%{IncludeDir.ASSIMP}",
		"%{IncludeDir.GLM}"
	}
	libdirs
	{
		"%{wks.location}/bin/" .. outputdir .. "/GLFW",
		"%{wks.location}/bin/" .. outputdir .. "/GLAD",
		"%{wks.location}/bin/" .. outputdir .. "/Assimp"		
	}
	links
	{
		"glfw.lib",
		"glad.lib",
		"Assimp.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
	