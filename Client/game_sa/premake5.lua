project "Game SA"
	language "C++"
	kind "SharedLib"
	targetname "game_sa"
	targetdir(buildpath("mta"))
	
	pchheader "StdInc.h"
	pchsource "StdInc.cpp"
	
	vpaths { 
		["Headers/*"] = "**.h",
		["Headers/*"] = "**.hpp",
		["Sources/*"] = "**.cpp",
		["*"] = "premake5.lua"
	}
	
	filter "system:windows"
		includedirs { "../../vendor/sparsehash/current/src/windows" }
	
	filter {}
		includedirs {
			"../sdk",
			"../../vendor/sparsehash/current/src/"
		}
	
	files {
		"premake5.lua",
		"*.h",
		"*.hpp",
		"*.cpp"
	}
	
	filter "architecture:x64"
		flags { "ExcludeFromBuild" } 
		
	filter "system:not windows"
		flags { "ExcludeFromBuild" } 