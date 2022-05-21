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

--include "Vendor/GLFW"
--include "Vendor/GLAD"
include "Vendor/Soil"
--include "Vendor/Assimp"
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
--------------------------------------------------------------------------------------------	
-- 										Project GLAD
--------------------------------------------------------------------------------------------	
project "GLAD"
	kind "StaticLib"
	language "C"
	location "Vendor"

	targetdir 	("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir 		("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Vendor/Glad/include/glad/glad.h",
		"Vendor/Glad/include/KHR/khrplatform.h",
		"Vendor/Glad/src/glad.c"		
	}	
	
	includedirs
	{
		"%{IncludeDir.GLAD}"
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

--------------------------------------------------------------------------------------------	
-- 										Project GLFW
--------------------------------------------------------------------------------------------	
project "GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	location "Vendor"
	
	targetdir 	("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir 		("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Vendor/GLFW/include/GLFW/glfw3.h",
		"Vendor/GLFW/include/GLFW/glfw3native.h",
		"Vendor/GLFW/src/internal.h",
		"Vendor/GLFW/src/platform.h",
		"Vendor/GLFW/src/mappings.h",
		"Vendor/GLFW/src/context.c",
		"Vendor/GLFW/src/init.c",
		"Vendor/GLFW/src/input.c",
		"Vendor/GLFW/src/monitor.c",
		"Vendor/GLFW/src/platform.c",
		"Vendor/GLFW/src/vulkan.c",
		"Vendor/GLFW/src/window.c",
		"Vendor/GLFW/src/egl_context.c",
		"Vendor/GLFW/src/osmesa_context.c",
		"Vendor/GLFW/src/null_platform.h",
		"Vendor/GLFW/src/null_joystick.h",
		"Vendor/GLFW/src/null_init.c",

		"Vendor/GLFW/src/null_monitor.c",
		"Vendor/GLFW/src/null_window.c",
		"Vendor/GLFW/src/null_joystick.c",
	}

	filter "system:windows"
		--systemversion "latest"

		files
		{
			"Vendor/GLFW/src/win32_init.c",
			"Vendor/GLFW/src/win32_module.c",
			"Vendor/GLFW/src/win32_joystick.c",
			"Vendor/GLFW/src/win32_monitor.c",
			"Vendor/GLFW/src/win32_time.h",
			"Vendor/GLFW/src/win32_time.c",
			"Vendor/GLFW/src/win32_thread.h",
			"Vendor/GLFW/src/win32_thread.c",
			"Vendor/GLFW/src/win32_window.c",
			"Vendor/GLFW/src/wgl_context.c",
			"Vendor/GLFW/src/egl_context.c",
			"Vendor/GLFW/src/osmesa_context.c"
		}

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

--------------------------------------------------------------------------------------------	
-- 										Project Assimp
--------------------------------------------------------------------------------------------	
project "Assimp"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	location "Vendor"

	targetdir 	("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir 		("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	

  files {
		-- Dependencies
		--'contrib/unzip/**',
		--'contrib/irrXML/**',
		--'contrib/zlib/*',
		-- Common
		--'code/Common/**',
		--'code/PostProcessing/**',
		--'code/Material/**',
		--'code/CApi/**',
		-- Importers
		--'code/Collada/**',
		--'code/Obj/**',
		-- 'assimp/code/Blender/**', 'assimp/contrib/poly2tri/poly2tri/**',
		--'code/FBX/**',
		-- 'assimp/code/glTF2/**',
		-- 'assimp/code/glTF/**',
		--'code/Assbin/**' -- For caching 
		
		files
    {
        "Vendor/Assimp/include/**",
        "Vendor/Assimp/code/Common/Assimp.cpp",
		"Vendor/Assimp/code/Common/material.cpp",
		"Vendor/Assimp/code/Common/Exceptional.cpp",
        "Vendor/Assimp/code/Common/BaseImporter.cpp",
        "Vendor/Assimp/code/AssetLib/Collada/ColladaLoader.cpp",
        "Vendor/Assimp/code/AssetLib/Collada/ColladaParser.cpp",
        "Vendor/Assimp/code/Common/CreateAnimMesh.cpp",
        "Vendor/Assimp/code/AssetLib/Ply/PlyParser.cpp",
        "Vendor/Assimp/code/AssetLib/Ply/PlyLoader.cpp",
        "Vendor/Assimp/code/Common/BaseProcess.cpp",
        "Vendor/Assimp/code/PostProcessing/EmbedTexturesProcess.cpp",
        "Vendor/Assimp/code/PostProcessing/ConvertToLHProcess.cpp",
		"Vendor/Assimp/code/Common/IOSystem.cpp",
        "Vendor/Assimp/code/Common/DefaultIOStream.cpp",
        "Vendor/Assimp/code/Common/DefaultIOSystem.cpp",
        "Vendor/Assimp/code/Common/DefaultLogger.cpp",
        "Vendor/Assimp/code/PostProcessing/GenVertexNormalsProcess.cpp",
        "Vendor/Assimp/code/Common/Importer.cpp",
        "Vendor/Assimp/code/Common/ImporterRegistry.cpp",
        "Vendor/Assimp/code/Material/MaterialSystem.cpp",
        "Vendor/Assimp/code/Common/PostStepRegistry.cpp",
        "Vendor/Assimp/code/PostProcessing/ProcessHelper.cpp",
        "Vendor/Assimp/code/Common/scene.cpp",
        "Vendor/Assimp/code/Common/ScenePreprocessor.cpp",
        "Vendor/Assimp/code/PostProcessing/ScaleProcess.cpp",
        "Vendor/Assimp/code/Common/SGSpatialSort.cpp",
        "Vendor/Assimp/code/Common/SkeletonMeshBuilder.cpp",
        "Vendor/Assimp/code/Common/SpatialSort.cpp",
        "Vendor/Assimp/code/PostProcessing/TriangulateProcess.cpp",
        "Vendor/Assimp/code/PostProcessing/ValidateDataStructure.cpp",
        "Vendor/Assimp/code/Common/Version.cpp",
        "Vendor/Assimp/code/Common/VertexTriangleAdjacency.cpp",
        "Vendor/Assimp/code/AssetLib/Obj/ObjFileImporter.cpp",
        "Vendor/Assimp/code/AssetLib/Obj/ObjFileMtlImporter.cpp",
        --"code/AssetLib/FBX/FBXAnimation.cpp",
        --"code/AssetLib/FBX/FBXBinaryTokenizer.cpp",
        --"code/AssetLib/FBX/FBXConverter.cpp",
        --"code/AssetLib/FBX/FBXDeformer.cpp",
        --"code/AssetLib/FBX/FBXDocument.cpp",
        --"code/AssetLib/FBX/FBXDocumentUtil.cpp",
        --"code/AssetLib/FBX/FBXImporter.cpp",
        --"code/AssetLib/FBX/FBXMaterial.cpp",
        --"code/AssetLib/FBX/FBXMeshGeometry.cpp",
        --"code/AssetLib/FBX/FBXModel.cpp",
        --"code/AssetLib/FBX/FBXNodeAttribute.cpp",
        --"code/AssetLib/FBX/FBXParser.cpp",
        --"code/AssetLib/FBX/FBXProperties.cpp",
        --"code/AssetLib/FBX/FBXTokenizer.cpp",
        --"code/AssetLib/FBX/FBXExporter.cpp",
        --"code/AssetLib/FBX/FBXExportNode.cpp",
        --"code/AssetLib/FBX/FBXExportProperty.cpp",
        --"code/AssetLib/FBX/FBXUtil.cpp",
        "Vendor/Assimp/code/AssetLib/Obj/ObjFileParser.cpp",
        "Vendor/Assimp/code/AssetLib/glTF/glTFImporter.cpp",
        "Vendor/Assimp/code/AssetLib/glTF2/glTF2Importer.cpp",
        "Vendor/Assimp/code/PostProcessing/MakeVerboseFormat.cpp",
        "Vendor/Assimp/code/PostProcessing/CalcTangentsProcess.cpp",
        "Vendor/Assimp/code/PostProcessing/ScaleProcess.cpp",
        "Vendor/Assimp/code/PostProcessing/EmbedTexturesProcess.cpp",
		"Vendor/Assimp/code/PostProcessing/GenBoundingBoxesProcess.cpp",
        "Vendor/Assimp/contrib/irrXML/*"		
    }

  }


  includedirs {
		"Vendor/Assimp/include",
		"Vendor/Assimp/contrib",
		--'code/common/',
		"Vendor/Assimp/contrib/zlib",
		"Vendor/Assimp/contrib/irrXML",
		"Vendor/Assimp/contrib/pugixml/src",
		--'contrib/unzip/',
		"Vendor/Assimp/contrib/rapidjson/include",
		"Vendor/Assimp/code"		
	}

-- Importers
	defines {
		"_CRT_SECURE_NO_WARNINGS",
		-- "SWIG",
        --"ASSIMP_BUILD_NO_OWN_ZLIB",
		"ASSIMP_BUILD_NO_ARMATUREPOPULATE_PROCESS",
        "ASSIMP_BUILD_NO_X_IMPORTER",
		"ASSIMP_BUILD_NO_IQM_IMPORTER",
        "ASSIMP_BUILD_NO_3DS_IMPORTER",
        "ASSIMP_BUILD_NO_MD3_IMPORTER",
        "ASSIMP_BUILD_NO_MDL_IMPORTER",
        "ASSIMP_BUILD_NO_MD2_IMPORTER",
        "ASSIMP_BUILD_NO_PLY_IMPORTER",
        "ASSIMP_BUILD_NO_ASE_IMPORTER",
        -- "ASSIMP_BUILD_NO_OBJ_IMPORTER",
        "ASSIMP_BUILD_NO_AMF_IMPORTER",
        "ASSIMP_BUILD_NO_HMP_IMPORTER",
        "ASSIMP_BUILD_NO_SMD_IMPORTER",
        "ASSIMP_BUILD_NO_MDC_IMPORTER",
        "ASSIMP_BUILD_NO_MD5_IMPORTER",
        "ASSIMP_BUILD_NO_STL_IMPORTER",
        "ASSIMP_BUILD_NO_LWO_IMPORTER",
        "ASSIMP_BUILD_NO_DXF_IMPORTER",
        "ASSIMP_BUILD_NO_NFF_IMPORTER",
        "ASSIMP_BUILD_NO_RAW_IMPORTER",
        "ASSIMP_BUILD_NO_OFF_IMPORTER",
        "ASSIMP_BUILD_NO_AC_IMPORTER",
        "ASSIMP_BUILD_NO_BVH_IMPORTER",
        "ASSIMP_BUILD_NO_IRRMESH_IMPORTER",
        "ASSIMP_BUILD_NO_IRR_IMPORTER",
        "ASSIMP_BUILD_NO_Q3D_IMPORTER",
        "ASSIMP_BUILD_NO_B3D_IMPORTER",
        "ASSIMP_BUILD_NO_COLLADA_IMPORTER",
        "ASSIMP_BUILD_NO_TERRAGEN_IMPORTER",
        "ASSIMP_BUILD_NO_CSM_IMPORTER",
        "ASSIMP_BUILD_NO_3D_IMPORTER",
        "ASSIMP_BUILD_NO_LWS_IMPORTER",
        "ASSIMP_BUILD_NO_OGRE_IMPORTER",
        "ASSIMP_BUILD_NO_OPENGEX_IMPORTER",
        "ASSIMP_BUILD_NO_MS3D_IMPORTER",
        "ASSIMP_BUILD_NO_COB_IMPORTER",
        "ASSIMP_BUILD_NO_BLEND_IMPORTER",
        "ASSIMP_BUILD_NO_Q3BSP_IMPORTER",
        "ASSIMP_BUILD_NO_NDO_IMPORTER",
        "ASSIMP_BUILD_NO_IFC_IMPORTER",
        "ASSIMP_BUILD_NO_XGL_IMPORTER",
        "ASSIMP_BUILD_NO_FBX_IMPORTER",
        "ASSIMP_BUILD_NO_ASSBIN_IMPORTER",
        "ASSIMP_BUILD_NO_GLTF_IMPORTER",
        "ASSIMP_BUILD_NO_C4D_IMPORTER",
        "ASSIMP_BUILD_NO_3MF_IMPORTER",
        "ASSIMP_BUILD_NO_X3D_IMPORTER",
        "ASSIMP_BUILD_NO_MMD_IMPORTER",
		"ASSIMP_BUILD_NO_M3D_IMPORTER",

        "ASSIMP_BUILD_NO_STEP_EXPORTER",
        "ASSIMP_BUILD_NO_SIB_IMPORTER",     
        -- "ASSIMP_BUILD_NO_MAKELEFTHANDED_PROCESS",
        -- "ASSIMP_BUILD_NO_FLIPUVS_PROCESS",
        -- "ASSIMP_BUILD_NO_FLIPWINDINGORDER_PROCESS",
        -- "ASSIMP_BUILD_NO_CALCTANGENTS_PROCESS",
        "ASSIMP_BUILD_NO_JOINVERTICES_PROCESS",
        -- "ASSIMP_BUILD_NO_TRIANGULATE_PROCESS",
        "ASSIMP_BUILD_NO_GENFACENORMALS_PROCESS",
        -- "ASSIMP_BUILD_NO_GENVERTEXNORMALS_PROCESS",
        "ASSIMP_BUILD_NO_REMOVEVC_PROCESS",
        "ASSIMP_BUILD_NO_SPLITLARGEMESHES_PROCESS",
        "ASSIMP_BUILD_NO_PRETRANSFORMVERTICES_PROCESS",
        "ASSIMP_BUILD_NO_LIMITBONEWEIGHTS_PROCESS",
        -- "ASSIMP_BUILD_NO_VALIDATEDS_PROCESS",
        "ASSIMP_BUILD_NO_IMPROVECACHELOCALITY_PROCESS",
        "ASSIMP_BUILD_NO_FIXINFACINGNORMALS_PROCESS",
        "ASSIMP_BUILD_NO_REMOVE_REDUNDANTMATERIALS_PROCESS",
        "ASSIMP_BUILD_NO_FINDINVALIDDATA_PROCESS",
        "ASSIMP_BUILD_NO_FINDDEGENERATES_PROCESS",
        "ASSIMP_BUILD_NO_SORTBYPTYPE_PROCESS",
        "ASSIMP_BUILD_NO_GENUVCOORDS_PROCESS",
        "ASSIMP_BUILD_NO_TRANSFORMTEXCOORDS_PROCESS",
        "ASSIMP_BUILD_NO_FINDINSTANCES_PROCESS",
        "ASSIMP_BUILD_NO_OPTIMIZEMESHES_PROCESS",
        "ASSIMP_BUILD_NO_OPTIMIZEGRAPH_PROCESS",
        "ASSIMP_BUILD_NO_SPLITBYBONECOUNT_PROCESS",
        "ASSIMP_BUILD_NO_DEBONE_PROCESS",
        "ASSIMP_BUILD_NO_EMBEDTEXTURES_PROCESS",
        "ASSIMP_BUILD_NO_GLOBALSCALE_PROCESS",
    }
	
   filter "system:windows"
      systemversion "latest"

   filter  "configurations:Debug"
       runtime "Debug"
       symbols "on"

   filter  "configurations:Release"
       runtime "Release"
       optimize "on"