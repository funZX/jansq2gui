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
		defines { 
			"DEBUG",
			"JANSQ2GUI_WITH_DEBUGGER"
		}

    configuration "Release"
        targetdir "bin/Release"	
		debugdir "bin/Release"
		defines { 
			"NDEBUG",
		}
		
	configuration { "vs*", "x32 or x64" }
		defines { 
			"_GLFW_WIN32",
			"IMGUI_USE_GLFW_BINDING",		
		}

	configuration { "linux-*", "x32 or x64" }
		defines { 
			"_GLFW_X11",
			"IMGUI_USE_GLFW_BINDING",
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
		path.join(prjDir, "../3rdparty/jansson/src/janssonxx"),
		
		path.join(prjDir, "../3rdparty/sqlite3"),
		path.join(prjDir, "../3rdparty/sqlite3/sqlite3pp"),
		
		path.join(prjDir, "../3rdparty/imgui"),
		path.join(prjDir, "../3rdparty/imgui/misc"),
		path.join(prjDir, "../3rdparty/imgui/addons"),
		
		path.join(prjDir, "../3rdparty/zpl-c/zpl/code"),
		path.join(prjDir, "../3rdparty/zpl-c/enet/include"),
		path.join(prjDir, "../3rdparty/zpl-c/librg/include"),

		path.join(prjDir, "../3rdparty/glfw/include"),
		
		path.join(prjDir, "../3rdparty/opengles/include"),
	}

	files {
		path.join(prjDir, "../jansq2gui/**.h"),
		path.join(prjDir, "../jansq2gui/**.cpp"),
	}
	
	links {
		"libEGL",
		"libGLESv2",
		"3rdparty",
	}
	
	libdirs {
		path.join(prjDir, "../build/**"),
		path.join(prjDir, "../3rdparty/opengles/bin"),
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
		path.join(localDir, "jansson/src/janssonxx"),
		
		path.join(localDir, "sqlite3"),
		path.join(localDir, "sqlite3/sqlite3pp"),
		
		path.join(localDir, "imgui"),
		path.join(localDir, "imgui/misc"),
		path.join(localDir, "imgui/addons"),
		
		path.join(localDir, "zpl-c/zpl/code"),
		path.join(localDir, "zpl-c/enet/include"),
		path.join(localDir, "zpl-c/librg/include"),

		path.join(localDir, "glfw/include"),
		
		path.join(localDir, "opengles/include"),
	}

	files {
		path.join(localDir, "squirel/include/**.h"),
		path.join(localDir, "squirel/squirrel/**.cpp"),
		path.join(localDir, "squirel/squirrel/**.h"),
		path.join(localDir, "squirel/sqstdlib/**.cpp"),
		path.join(localDir, "squirel/sqstdlib/**.h"),
		path.join(localDir, "squirel/sqdbg/**.cpp"),
		path.join(localDir, "squirel/sqdbg/**.h"),

		path.join(localDir, "squirel/sqrat/include/**.h"),
		path.join(localDir, "squirel/sqrat/sqimport/**.cpp"),
		path.join(localDir, "squirel/sqrat/sqratthread/**.h"),
		path.join(localDir, "squirel/sqrat/sqratthreadg/**.cpp"),
		path.join(localDir, "squirel/sqrat/sqratthread/**.h"),
		
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
		path.join(localDir, "sqlite3/sqlite3pp/**.c"),
		path.join(localDir, "sqlite3/sqlite3pp/**.h"),
		
		path.join(localDir, "imgui/include/**.h"),
		path.join(localDir, "imgui/imconfig.h"),
		path.join(localDir, "imgui/imgui.h"),
		path.join(localDir, "imgui/imgui.cpp"),
		path.join(localDir, "imgui/imgui_*.cpp"),
		path.join(localDir, "imgui/imgui_*.h"),
		path.join(localDir, "imgui/imstb_*.cpp"),
		path.join(localDir, "imgui/imstb_*.h"),
		
		path.join(localDir, "zpl-c/zpl/code/zpl.h"),
		path.join(localDir, "zpl-c/enet/include/enet.h"),
		path.join(localDir, "zpl-c/librg/include/librg.h"),

		path.join(localDir, "opengles/include/**.h"),
	}
	
	configuration { "vs*", "x32 or x64" }
		files {
			path.join(localDir, "glfw/src/win32_platform.h"),
			path.join(localDir, "glfw/src/win32_joystick.h"),
			path.join(localDir, "glfw/src/wgl_context.h"),
			path.join(localDir, "glfw/src/egl_context.h"),
			path.join(localDir, "glfw/src/osmesa_context.h"),
			path.join(localDir, "glfw/src/win32_init.c"),
			path.join(localDir, "glfw/src/win32_joystick.c"),
			path.join(localDir, "glfw/src/win32_monitor.c"),
			path.join(localDir, "glfw/src/win32_time.c"),
			path.join(localDir, "glfw/src/win32_thread.c"),
			path.join(localDir, "glfw/src/win32_window.c"),
			path.join(localDir, "glfw/src/wgl_context.c"),
			path.join(localDir, "glfw/src/egl_context.c"),
			path.join(localDir, "glfw/src/osmesa_context.c"),			
		}

	configuration { "linux-*", "x32 or x64" }
		files {
			path.join(localDir, "glfw/src/x11_platform.h"),
			path.join(localDir, "glfw/src/xkb_unicode.h"),
			path.join(localDir, "glfw/src/posix_time.h"),
			path.join(localDir, "glfw/src/posix_thread.h"),
			path.join(localDir, "glfw/src/glx_context.h"),
			path.join(localDir, "glfw/src/egl_context.h"),
			path.join(localDir, "glfw/src/osmesa_context.h"),
			path.join(localDir, "glfw/src/x11_init.c"),
			path.join(localDir, "glfw/src/x11_monitor.c"),
			path.join(localDir, "glfw/src/x11_window.c"),
			path.join(localDir, "glfw/src/xkb_unicode.c"),
			path.join(localDir, "glfw/src/posix_time.c"),
			path.join(localDir, "glfw/src/posix_thread.c"),
			path.join(localDir, "glfw/src/glx_context.c"),
			path.join(localDir, "glfw/src/egl_context.c"),
			path.join(localDir, "glfw/src/osmesa_context.c"),
		}
-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------