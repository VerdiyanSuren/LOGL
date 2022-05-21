--------------------------------------------------------------------------------------------	
-- 										Project Assimp
--------------------------------------------------------------------------------------------	
project "Assimp"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	

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
        "include/**",
        "code/Common/Assimp.cpp",
		 "code/Common/material.cpp",
		"code/Common/Exceptional.cpp",
        "code/Common/BaseImporter.cpp",
        "code/AssetLib/Collada/ColladaLoader.cpp",
        "code/AssetLib/Collada/ColladaParser.cpp",
        "code/Common/CreateAnimMesh.cpp",
        "code/AssetLib/Ply/PlyParser.cpp",
        "code/AssetLib/Ply/PlyLoader.cpp",
        "code/Common/BaseProcess.cpp",
        "code/PostProcessing/EmbedTexturesProcess.cpp",
        "code/PostProcessing/ConvertToLHProcess.cpp",
		"code/Common/IOSystem.cpp",
        "code/Common/DefaultIOStream.cpp",
        "code/Common/DefaultIOSystem.cpp",
        "code/Common/DefaultLogger.cpp",
        "code/PostProcessing/GenVertexNormalsProcess.cpp",
        "code/Common/Importer.cpp",
        "code/Common/ImporterRegistry.cpp",
        "code/Material/MaterialSystem.cpp",
        "code/Common/PostStepRegistry.cpp",
        "code/PostProcessing/ProcessHelper.cpp",
        "code/Common/scene.cpp",
        "code/Common/ScenePreprocessor.cpp",
        "code/PostProcessing/ScaleProcess.cpp",
        "code/Common/SGSpatialSort.cpp",
        "code/Common/SkeletonMeshBuilder.cpp",
        "code/Common/SpatialSort.cpp",
        "code/PostProcessing/TriangulateProcess.cpp",
        "code/PostProcessing/ValidateDataStructure.cpp",
        "code/Common/Version.cpp",
        "code/Common/VertexTriangleAdjacency.cpp",
        "code/AssetLib/Obj/ObjFileImporter.cpp",
        "code/AssetLib/Obj/ObjFileMtlImporter.cpp",
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
        "code/AssetLib/Obj/ObjFileParser.cpp",
        "code/AssetLib/glTF/glTFImporter.cpp",
        "code/AssetLib/glTF2/glTF2Importer.cpp",
        "code/PostProcessing/MakeVerboseFormat.cpp",
        "code/PostProcessing/CalcTangentsProcess.cpp",
        "code/PostProcessing/ScaleProcess.cpp",
        "code/PostProcessing/EmbedTexturesProcess.cpp",
		"code/PostProcessing/GenBoundingBoxesProcess.cpp",
        "contrib/irrXML/*"		
    }

  }


  includedirs {
		"include",
		"contrib",
		--'code/common/',
		"contrib/zlib",
		"contrib/irrXML",
		"contrib/pugixml/src",
		--'contrib/unzip/',
		"contrib/rapidjson/include",
		"code"		
	}

-- Importers
	defines {
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



		
		