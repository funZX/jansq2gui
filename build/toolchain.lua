--
-- Copyright 2010-2020 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bx#license-bsd-2-clause
--

local function crtNone()

	buildoptions {
		"-nostdlib",
		"-nodefaultlibs",
		"-nostartfiles",
		"-Wa,--noexecstack",
		"-ffreestanding",
	}

	linkoptions {
		"-nostdlib",
		"-nodefaultlibs",
		"-nostartfiles",
		"-Wa,--noexecstack",
		"-ffreestanding",
	}

	configuration { "linux-*" }

		buildoptions {
			"-mpreferred-stack-boundary=4",
			"-mstackrealign",
		}

		linkoptions {
			"-mpreferred-stack-boundary=4",
			"-mstackrealign",
		}

	configuration {}
end

function toolchain(_buildDir, _libDir)

	newoption {
		trigger = "gcc",
		value = "GCC",
		description = "Choose GCC flavor",
		allowed = {
			{ "linux-gcc",       "Linux  (GCC compiler)"        },
			{ "linux-clang",     "Linux  (Clang compiler)"      },
			{ "linux-arm-gcc",   "Linux  (ARM, GCC compiler)"   },
			{ "linux-arm-clang", "Linux  (ARM, Clang compiler)" },
			{ "cygwin-gcc",      "Cygwin (GCC compiler)"        },
			{ "cygwin-clang",    "Cygwin (CLANG compiler)"      },
		},
	}
	
	newoption {
		trigger     = "noexceptions",
		description = "Disable exceptions.",
	}	

	newoption {
		trigger     = "nortti",
		description = "Disable runtime type information.",
	}
	
	newoption {
		trigger     = "runtimestatic",
		description = "Enable static runtime.",
	}
	
	newoption {
		trigger     = "nocrt",
		description = "Disable linking with standard runtime library.",
	}
	
	-- Avoid error when invoking genie --help.
	if (_ACTION == nil) then return false end

	location (path.join(_buildDir, "projects", _ACTION))

--------------------------------------------------------------------
	if _ACTION == "clean" then
		os.rmdir(_buildDir)
		os.mkdir(_buildDir)
		os.exit(1)
	end
--------------------------------------------------------------------
-------------------- ALL CONFIGURATIONS ----------------------------

	local optionNoExceptions = false
	if _OPTIONS["noexceptions"] then
		print("noexceptions")
		optionNoExceptions = true
	end
	
	local optionNoRTTI = false
	if _OPTIONS["nortti"] then
		print("nortti")
		optionNoRTTI = true
	end
	
	local optionRuntimeStatic = false
	if _OPTIONS["runtimestatic"] then
		print("runtimestatic")
		optionRuntimeStatic = true
	end

	local optionNoCrt = false
	if _OPTIONS["nocrt"] then
		print("nocrt")
		optionNoCrt = true
	end

--------------------------------------------------------------------

	if optionNoCrt then
		crtNone();
	end
--------------------------------------------------------------------

	flags {
		"NoPCH",
		"NativeWChar",
		"NoEditAndContinue",
		"NoFramePointer",
		"ExtraWarnings",
		"FloatFast",		
	}

	defines {
		"__STDC_LIMIT_MACROS",
		"__STDC_FORMAT_MACROS",
		"__STDC_CONSTANT_MACROS",
	}

	configuration { "Debug" }
		flags {	 "Symbols" }
		defines { "_DEBUG", "DEBUG" }

	configuration { "Release" }
		flags { "NoBufferSecurityCheck", "OptimizeSpeed" }
		defines { "NDEBUG" }	
	
	-- ACTION
	if _ACTION == "gmake" or _ACTION == "ninja" then

		if nil == _OPTIONS["gcc"] then
			print("GCC flavor must be specified!")
			os.exit(1)
		end

		if "linux-gcc" == _OPTIONS["gcc"] then
			premake.gcc.cc  = "gcc"
			premake.gcc.cxx = "g++"
			premake.gcc.ar  = "ar"		
			location (path.join(_buildDir, "projects", _ACTION .. "-linux-gcc"))

		elseif "linux-clang" == _OPTIONS["gcc"] then
			premake.gcc.cc  = "clang"
			premake.gcc.cxx = "clang++"
			premake.gcc.ar  = "ar"
			location (path.join(_buildDir, "projects", _ACTION .. "-linux-clang"))

		elseif "linux-arm-gcc" == _OPTIONS["gcc"] then
			premake.gcc.cc  = "gcc"
			premake.gcc.cxx = "g++"
			premake.gcc.ar  = "ar"
			location (path.join(_buildDir, "projects", _ACTION .. "-linux-arm-gcc"))
			
		elseif "linux-arm-clang" == _OPTIONS["gcc"] then
			premake.gcc.cc  = "clang"
			premake.gcc.cxx = "clang++"
			premake.gcc.ar  = "ar"
			location (path.join(_buildDir, "projects", _ACTION .. "-linux-arm-clang"))			

		elseif "cygwin-gcc" == _OPTIONS["gcc"] then
			premake.gcc.cc  = "gcc"
			premake.gcc.cxx = "g++"
			premake.gcc.ar  = "ar"
			location (path.join(_buildDir, "projects", _ACTION .. "-cygwin-gcc"))
			
		elseif "cygwin-clang" == _OPTIONS["gcc"] then
			premake.gcc.cc  = "clang"
			premake.gcc.cxx = "clang++"
			premake.gcc.ar  = "ar"
			location (path.join(_buildDir, "projects", _ACTION .. "-cygwin-clang"))					
		end
	elseif _ACTION == "vs2012"
		or _ACTION == "vs2013"
		or _ACTION == "vs2015"
		or _ACTION == "vs2017"
		or _ACTION == "vs2019"
		then

		local action = premake.action.current()
		action.vstudio.windowsTargetPlatformVersion    = windowsPlatform
		action.vstudio.windowsTargetPlatformMinVersion = windowsPlatform		
	end

--------------------------------------------------------------------
	if optionNoExceptions then
		flags { "NoExceptions", }
		defines {  "_HAS_EXCEPTIONS=0", }
	end

	if optionRuntimeStatic then
		flags { "StaticRuntime", }
	end
	
	if optionNoRTTI then
		flags { "NoRTTI", }
	end

	configuration { "x32", "vs*" }
		defines { "_WIN32" }
		flags { "EnableSSE2" }

	configuration { "x64", "vs*" }
		defines { "_WIN64" }

	configuration { "x32", "*-gcc* or *-clang*" }
		buildoptions { "-Wshadow" }

	configuration { "x64", "*-gcc* or *-clang*" }
		buildoptions { "-Wshadow" }



--------------------------------------------------------------------
-------------------- VS CONFIGURATIONS -----------------------------

	configuration { "vs*", "Debug" }
		flags { "FullSymbols" }
		
	configuration { "vs*", "Release" }
		
	configuration { "vs*" }
		defines {
			"_MBCS",
			"_SCL_SECURE=0",
			"_SECURE_SCL=0",
			"_SCL_SECURE_NO_WARNINGS",
			"_CRT_SECURE_NO_WARNINGS",
			"_CRT_SECURE_NO_DEPRECATE",
			"WIN32_LEAN_AND_MEAN",
		}
		buildoptions {
			"/wd4201", -- warning C4201: nonstandard extension used: nameless struct/union
			"/wd4324", -- warning C4324: '': structure was padded due to alignment specifier
			"/Ob2",    -- The Inline Function Expansion
		}
		linkoptions {
			"/ignore:4221", -- LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library
		}

--------------------------------------------------------------------







--------------------------------------------------------------------
-------------------- LINUX CONFIGURATIONS ---------------------------

	configuration { "linux-*", "Debug" }
		
	configuration { "linux-*", "Release" }

	configuration { "linux-*" }
		links { "rt", "dl" }
		buildoptions {
			"-msse2",
--			"-Wdouble-promotion",
--			"-Wduplicated-branches",
--			"-Wduplicated-cond",
--			"-Wjump-misses-init",
--			"-Wnull-dereference",
			"-Wunused-value",
			"-Wundef",
			"-Wlogical-op",
--			"-Wuseless-cast",
		}
		linkoptions {
			"-Wl,--gc-sections",
			"-Wl,--as-needed",
		}
		
	configuration { "linux-arm-*", "Debug" }
		
	configuration { "linux-arm-*", "Release" }
	
	configuration { "linux-arm-*" }
		buildoptions {
			"-Wunused-value",
			"-Wundef",
		}
		linkoptions {
			"-Wl,--gc-sections",
		}	

--------------------------------------------------------------------








--------------------------------------------------------------------
-------------------- CYGWIN CONFIGURATION --------------------------	
	configuration { "cygwin-*", "Debug" }
		
	configuration { "cygwin-*", "Release" }
	
	configuration { "cygwin-*" }
		buildoptions {
			"-Wunused-value",
			"-fdata-sections",
			"-ffunction-sections",
			"-Wunused-value",
			"-Wundef",
		}
		linkoptions {
			"-Wl,--gc-sections",
		}
--------------------------------------------------------------------





	configuration { "x32", "vs*" }
		targetdir (path.join(_buildDir, "win32_" .. _ACTION, "bin"))
		objdir (path.join(_buildDir, "win32_" .. _ACTION, "obj"))
		libdirs { path.join(_libDir, "lib/win32_" .. _ACTION) }

	configuration { "x64", "vs*" }
		targetdir (path.join(_buildDir, "win64_" .. _ACTION, "bin"))
		objdir (path.join(_buildDir, "win64_" .. _ACTION, "obj"))
		libdirs { path.join(_libDir, "lib/win64_" .. _ACTION)}

	configuration { "linux-gcc*", "x32" }
		targetdir (path.join(_buildDir, "linux32_gcc/bin"))
		objdir (path.join(_buildDir, "linux32_gcc/obj"))
		libdirs { path.join(_libDir, "lib/linux32_gcc") }

	configuration { "linux-gcc*", "x64" }
		targetdir (path.join(_buildDir, "linux64_gcc/bin"))
		objdir (path.join(_buildDir, "linux64_gcc/obj"))
		libdirs { path.join(_libDir, "lib/linux64_gcc") }

	configuration { "linux-clang*", "x32" }
		targetdir (path.join(_buildDir, "linux32_clang/bin"))
		objdir (path.join(_buildDir, "linux32_clang/obj"))
		libdirs { path.join(_libDir, "lib/linux32_clang") }

	configuration { "linux-clang*", "x64" }
		targetdir (path.join(_buildDir, "linux64_clang/bin"))
		objdir (path.join(_buildDir, "linux64_clang/obj"))
		libdirs { path.join(_libDir, "lib/linux64_clang") }

	configuration { "linux-arm-gcc", "x32" }
		targetdir (path.join(_buildDir, "linux32_arm_gcc/bin"))
		objdir (path.join(_buildDir, "linux32_arm_gcc/obj"))
		libdirs { path.join(_libDir, "lib/linux32_arm_gcc") }
		
	configuration { "linux-arm-gcc", "x64" }
		targetdir (path.join(_buildDir, "linux64_arm_gcc/bin"))
		objdir (path.join(_buildDir, "linux64_arm_gcc/obj"))
		libdirs { path.join(_libDir, "lib/linux64_arm_gcc") }
		
	configuration { "linux-arm-clang", "x32" }
		targetdir (path.join(_buildDir, "linux32_arm_clang/bin"))
		objdir (path.join(_buildDir, "linux32_arm_clang/obj"))
		libdirs { path.join(_libDir, "lib/linux32_arm_clang") }
		
	configuration { "linux-arm-clang", "x64" }
		targetdir (path.join(_buildDir, "linux64_arm_clang/bin"))
		objdir (path.join(_buildDir, "linux64_arm_clang/obj"))
		libdirs { path.join(_libDir, "lib/linux64_arm_clang") }
		
	configuration { "cygwin-gcc*", "x32" }
		targetdir (path.join(_buildDir, "cygwin32_gcc/bin"))
		objdir (path.join(_buildDir, "cygwin32_gcc/obj"))
		libdirs { path.join(_libDir, "lib/cygwin32_gcc") }

	configuration { "cygwin-gcc*", "x64" }
		targetdir (path.join(_buildDir, "cygwin64_gcc/bin"))
		objdir (path.join(_buildDir, "cygwin64_gcc/obj"))
		libdirs { path.join(_libDir, "lib/cygwin64_gcc") }

	configuration { "cygwin-clang*", "x32" }
		targetdir (path.join(_buildDir, "cygwin32_clang/bin"))
		objdir (path.join(_buildDir, "cygwin32_clang/obj"))
		libdirs { path.join(_libDir, "lib/cygwin32_clang") }

	configuration { "cygwin-clang*", "x64" }
		targetdir (path.join(_buildDir, "cygwin64_clang/bin"))
		objdir (path.join(_buildDir, "cygwin64_clang/obj"))
		libdirs { path.join(_libDir, "lib/cygwin64_clang") }

	configuration {} -- reset configuration

	return true
end

function postbuild()

	configuration { "linux-*", "Release" }
		postbuildcommands {
		}

	configuration { "vs*", "Release" }
		postbuildcommands {
		}
		
	configuration { "cygwin*", "Release" }
		postbuildcommands {
		}	

	configuration {} -- reset configuration
end
