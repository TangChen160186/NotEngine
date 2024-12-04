project "TestBed"
	kind "ConsoleApp"
    language "C"
    toolset "clang"
    cdialect "C17"
    files { "**.h", "**.c" }
	
	includedirs { "%{wks.location}/NotEngine","%{wks.location}/TestBed"}
	links { "NotEngine" }
	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")


	postbuildcommands {
		"for /f \"delims=|\" %%i in ('dir /B /S \"%{dependdir}\\*.dll\"') do xcopy /Q /Y \"%%i\" \"%{outputdir}%{cfg.buildcfg}\\%{prj.name}\"",
		"xcopy /Y /I /Q /D \"%{outputdir}%{cfg.buildcfg}\\NotEngine\\NotEngine.dll\" \"%{outputdir}%{cfg.buildcfg}\\%{prj.name}\"",
		"EXIT /B 0"
	}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"

	filter { "system:windows" }
		-- forces post-build commands to trigger even if nothing changed
		fastuptodate "Off"