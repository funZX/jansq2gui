-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------

local prjDir = path.getabsolute(".")

-----------------------------------------------------------------
------------------------  solution  -----------------------------

solution "jansq2gui"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		"x32",
		"x64",
	}

	language "C++"
	startproject "jansq2gui"
	
    configuration "Debug"
        targetdir "bin/Debug"
		debugdir "bin/Debug"
		flags { "Symbols", "NoRTTI" }
		defines { 
			"DEBUG",
			"JANSQ2GUI_WITH_DEBUGGER",
			
			"IMGUI_USE_GLAD",
			"IMGUI_USE_GLFW_BINDING",
			"IMIMPL_SHADER_GLES",
			"LIBASYNC_STATIC",
		}

    configuration "Release"
        targetdir "bin/Release"	
		debugdir "bin/Release"
		flags {
			"OptimizeSpeed",
			"NoRTTI"
		}
		defines {
			"NDEBUG",
			
			"IMGUI_USE_GLAD",
			"IMGUI_USE_GLFW_BINDING",
			"IMIMPL_SHADER_GLES",
			"LIBASYNC_STATIC",			
		}
		
	configuration { "vs*", "x32 or x64" }
		flags { 
			"FullSymbols"
		}
		defines {
			"WIN32", "_WIN32", "_MBCS",
			"WIN32_LEAN_AND_MEAN",
			"_GLFW_WIN32",
		}

	configuration { "linux-*", "x32 or x64" }
		defines {
			"LINUX",
			"_GLFW_X11",
		}
		
-----------------------------------------------------------------
	
project ("jansq2gui")
	kind "ConsoleApp"	
	
	includedirs { 
		path.join(prjDir, "../jansq2gui"),
		
		path.join(prjDir, "../3rdparty/squirrel/include"),
		path.join(prjDir, "../3rdparty/squirrel/sqstdlib"),
		path.join(prjDir, "../3rdparty/squirrel/squirrel"),
		path.join(prjDir, "../3rdparty/squirrel/sqdbg"),
		path.join(prjDir, "../3rdparty/squirrel/sqrat/include"),
		
		path.join(prjDir, "../3rdparty/zpl-c/enet/include"),
		path.join(prjDir, "../3rdparty/zpl-c/zpl/code"),
		path.join(prjDir, "../3rdparty/zpl-c/librg/include"),

		path.join(prjDir, "../3rdparty/asyncplusplus/include"),
		
		path.join(prjDir, "../3rdparty/jansson/src"),
		path.join(prjDir, "../3rdparty/jansson/janssonxx"),
		
		path.join(prjDir, "../3rdparty/sqlite3"),
		path.join(prjDir, "../3rdparty/sqlite3/sqlite3pp/src"),
		
		path.join(prjDir, "../3rdparty/imgui"),
		path.join(prjDir, "../3rdparty/imgui/misc"),
		path.join(prjDir, "../3rdparty/imgui/addons"),
		
		path.join(prjDir, "../3rdparty/zpl-c/zpl/code"),
		path.join(prjDir, "../3rdparty/zpl-c/enet/include"),
		path.join(prjDir, "../3rdparty/zpl-c/librg/include"),

		path.join(prjDir, "../3rdparty/glfw/include"),
		path.join(prjDir, "../3rdparty/glfw/deps"),		
	}

	files {
		path.join(prjDir, "../jansq2gui/**.h"),
		path.join(prjDir, "../jansq2gui/**.cpp"),
	}
	
	links {
		"3rdparty",
	}
	
	libdirs {
		path.join(prjDir, "../build/**"),
	}
-----------------------------------------------------------------
		
project ("3rdparty")
	kind "StaticLib"

	local localDir = path.join(prjDir, "../3rdparty")
	
	includedirs { 
		path.join(localDir, "squirrel/include"),
		path.join(localDir, "squirrel/sqstdlib"),
		path.join(localDir, "squirrel/squirrel"),
		path.join(localDir, "squirrel/sqdbg"),
		path.join(localDir, "squirrel/sqrat/include"),
		
		path.join(localDir, "zpl-c/enet/include"),
		path.join(localDir, "zpl-c/zpl/code"),
		path.join(localDir, "zpl-c/librg/include"),

		path.join(localDir, "asyncplusplus/include"),
		
		path.join(localDir, "jansson/src"),
		path.join(localDir, "jansson/janssonxx"),
		
		path.join(localDir, "sqlite3"),
		path.join(localDir, "sqlite3/sqlite3pp/src"),
		
		path.join(localDir, "imgui"),
		path.join(localDir, "imgui/misc"),
		path.join(localDir, "imgui/addons"),
		
		path.join(localDir, "zpl-c/zpl/code"),
		path.join(localDir, "zpl-c/enet/include"),
		path.join(localDir, "zpl-c/librg/include"),

		path.join(localDir, "glfw/include"),
		path.join(localDir, "glfw/deps"),
	}

	files {
		path.join(localDir, "squirrel/include/**.h"),
		path.join(localDir, "squirrel/squirrel/**.cpp"),
		path.join(localDir, "squirrel/squirrel/**.h"),
		path.join(localDir, "squirrel/sqstdlib/**.cpp"),
		path.join(localDir, "squirrel/sqstdlib/**.h"),
		path.join(localDir, "squirrel/sqdbg/**.cpp"),
		path.join(localDir, "squirrel/sqdbg/**.h"),

		path.join(localDir, "squirrel/sqrat/include/**.h"),
		path.join(localDir, "squirrel/sqrat/sqimport/**.cpp"),
		path.join(localDir, "squirrel/sqrat/sqratthread/**.h"),
		path.join(localDir, "squirrel/sqrat/sqratthreadg/**.cpp"),
		path.join(localDir, "squirrel/sqrat/sqratthread/**.h"),
		
		path.join(localDir, "asyncplusplus/include/**.h"),
		path.join(localDir, "asyncplusplus/src/**.cpp"),
		path.join(localDir, "asyncplusplus/src/**.h"),

		path.join(localDir, "jansson/include/**.h"),
		path.join(localDir, "jansson/src/**.c"),
		path.join(localDir, "jansson/src/**.h"),
		path.join(localDir, "jansson/janssonxx/jansson.hpp"),
		path.join(localDir, "jansson/janssonxx/jansson-impl.hpp"),	
		
		path.join(localDir, "sqlite3/include/**.h"),
		path.join(localDir, "sqlite3/**.c"),
		path.join(localDir, "sqlite3/**.h"),
		path.join(localDir, "sqlite3/sqlite3pp/src/**.c"),
		path.join(localDir, "sqlite3/sqlite3pp/src/**.h"),
		
		path.join(localDir, "imgui/include/**.h"),
		path.join(localDir, "imgui/imconfig.h"),
		path.join(localDir, "imgui/imgui.h"),
		path.join(localDir, "imgui/imgui.cpp"),
		path.join(localDir, "imgui/imgui_*.cpp"),
		path.join(localDir, "imgui/imgui_*.h"),
		path.join(localDir, "imgui/imstb_*.cpp"),
		path.join(localDir, "imgui/imstb_*.h"),		
		path.join(localDir, "imgui/addons/**.cpp"),
		path.join(localDir, "imgui/addons/**.h"),
		
		path.join(localDir, "zpl-c/zpl/code/header/**.h"),
		path.join(localDir, "zpl-c/zpl/code/other/**.h"),
		path.join(localDir, "zpl-c/zpl/code/source/**.c"),
		
		path.join(localDir, "zpl-c/enet/include/enet.h"),
		path.join(localDir, "zpl-c/librg/include/librg.h"),
		path.join(localDir, "zpl-c/zpl-c.c"),

		path.join(localDir, "glfw/include/**.h"),
		path.join(localDir, "opengles/include/**.h"),
		
		path.join(localDir, "glfw/src/internal.h"),
		path.join(localDir, "glfw/src/mappings.h"),
		path.join(localDir, "glfw/src/context.c"),
		path.join(localDir, "glfw/src/init.c"),
		path.join(localDir, "glfw/src/input.c"),
		path.join(localDir, "glfw/src/monitor.c"),
        path.join(localDir, "glfw/src/vulkan.c"),
		path.join(localDir, "glfw/src/window.c"),
		path.join(localDir, "glfw/src/osmesa_context.h"),
		path.join(localDir, "glfw/src/osmesa_context.c"),
		path.join(localDir, "glfw/src/egl_context.h"),
		path.join(localDir, "glfw/src/egl_context.c"),
		
		path.join(localDir, "glfw/deps/**.h"),
		path.join(localDir, "glfw/deps/**.c"),
		path.join(localDir, "glfw/deps/glad/**.h"),
		path.join(localDir, "glfw/deps/glad/**.c"),
	}
	
	excludes {
		path.join(localDir, "imgui/addons/**.cpp"),
		path.join(localDir, "imgui/addons/**.h"),	
		path.join(localDir, "zpl-c/zpl/code/source/**.c"),
	}
	
	configuration { "vs*", "x32 or x64" }
		files {
			path.join(localDir, "glfw/src/win32_platform.h"),
			path.join(localDir, "glfw/src/win32_joystick.h"),
			path.join(localDir, "glfw/src/wgl_context.h"),
			path.join(localDir, "glfw/src/win32_init.c"),
			path.join(localDir, "glfw/src/win32_joystick.c"),
			path.join(localDir, "glfw/src/win32_monitor.c"),
			path.join(localDir, "glfw/src/win32_time.c"),
			path.join(localDir, "glfw/src/win32_thread.c"),
			path.join(localDir, "glfw/src/win32_window.c"),
			path.join(localDir, "glfw/src/wgl_context.c"),
		}

	configuration { "linux-*", "x32 or x64" }
		files {
			path.join(localDir, "glfw/src/x11_platform.h"),
			path.join(localDir, "glfw/src/xkb_unicode.h"),
			path.join(localDir, "glfw/src/posix_time.h"),
			path.join(localDir, "glfw/src/posix_thread.h"),
			path.join(localDir, "glfw/src/glx_context.h"),
			path.join(localDir, "glfw/src/x11_init.c"),
			path.join(localDir, "glfw/src/x11_monitor.c"),
			path.join(localDir, "glfw/src/x11_window.c"),
			path.join(localDir, "glfw/src/xkb_unicode.c"),
			path.join(localDir, "glfw/src/posix_time.c"),
			path.join(localDir, "glfw/src/posix_thread.c"),
			path.join(localDir, "glfw/src/glx_context.c"),
		}
-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------