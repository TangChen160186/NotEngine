project "NotEngine"
	kind "SharedLib"
    language "C"
    toolset "clang"
    cdialect "C17"
    files { "**.h", "**.c" }
	
	includedirs {"%{wks.location}/NotEngine"}
	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")

	defines { "EXPORT" }
	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"