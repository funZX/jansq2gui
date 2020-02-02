-----------------------------------------------------------------
------------------------  solution  -----------------------------

solution "jansq2gui"
	configurations {
		"Native",
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
		defines {
			"IMGUI_USE_GLAD",
			"IMGUI_USE_GLFW_BINDING",
			"IMIMPL_SHADER_GLES",
			"LIBASYNC_STATIC",
		}

    configuration "Release"
		defines {			
			"IMGUI_USE_GLAD",
			"IMGUI_USE_GLFW_BINDING",
			"IMIMPL_SHADER_GLES",
			"LIBASYNC_STATIC",
		}		

	configuration { "*", "x64" }
		defines {
			"_SQ64",
		}
		
	configuration { "vs*" }
		defines {
			"_GLFW_WIN32",
		}

	configuration { "linux*" }
		defines {
			"_GLFW_X11",
		}
		links { "pthread", "X11" }
		
	configuration { "cygwin*" }
		defines {
			"_GLFW_X11",
		}
		links { "pthread", "X11" }		
	

-----------------------------------------------------------------
JQ2_DIR = path.getabsolute("..")
JQ2_BUILD_DIR = path.join(JQ2_DIR, "build")
JQ2_THIRD_PARTY_DIR = path.join(JQ2_DIR, "3rdparty")

print(JQ2_DIR);
print(JQ2_BUILD_DIR);
print(JQ2_THIRD_PARTY_DIR);

dofile "toolchain.lua"
toolchain(JQ2_BUILD_DIR, JQ2_THIRD_PARTY_DIR)
-----------------------------------------------------------------
	
project ("jansq2gui")
	kind "WindowedApp"	
	
	includedirs { 
		path.join(JQ2_DIR, "jansq2gui"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqstdlib"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/squirrel"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqdbg"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqrat/include"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/enet/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/librg/include"),

		path.join(JQ2_THIRD_PARTY_DIR, "asyncplusplus/include"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/src"),
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/janssonxx"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3"),
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3/sqlite3pp/src"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "imgui"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/misc"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/addons"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/enet/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/librg/include"),

		path.join(JQ2_THIRD_PARTY_DIR, "glfw/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/deps"),	

		path.join(JQ2_THIRD_PARTY_DIR, "helper"),
	}

	files {
		path.join(JQ2_DIR, "jansq2gui/**.h"),
		path.join(JQ2_DIR, "jansq2gui/**.cpp"),
	}
	
	links {
		"3rdparty",
	}
	
	strip()

-----------------------------------------------------------------
		
project ("3rdparty")
	kind "StaticLib"
	
	includedirs { 
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqstdlib"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/squirrel"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqdbg"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqrat/include"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/enet/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/librg/include"),

		path.join(JQ2_THIRD_PARTY_DIR, "asyncplusplus/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "sigcxx/include"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/src"),
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/janssonxx"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3"),
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3/sqlite3pp/src"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "imgui"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/misc"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/addons"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/enet/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/librg/include"),

		path.join(JQ2_THIRD_PARTY_DIR, "glfw/include"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/deps"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "helper"),
	}

	files {
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/include/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/squirrel/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/squirrel/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqstdlib/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqstdlib/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqdbg/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqdbg/**.h"),

		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqrat/include/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqrat/sqimport/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqrat/sqratthread/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqrat/sqratthreadg/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "squirrel/sqrat/sqratthread/**.h"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "asyncplusplus/include/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "asyncplusplus/src/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "asyncplusplus/src/**.h"),

		path.join(JQ2_THIRD_PARTY_DIR, "sigcxx/include/**.hpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "sigcxx/src/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "sigcxx/src/**.h"),		
		
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/include/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/src/**.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/src/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/janssonxx/jansson.hpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "jansson/janssonxx/jansson-impl.hpp"),	
		
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3/include/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3/*.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3/*.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3/sqlite3pp/headeronly_src/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3/sqlite3pp/src/**.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "sqlite3/sqlite3pp/src/**.h"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/include/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/imconfig.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/imgui.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/imgui.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/imgui_*.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/imgui_*.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/imstb_*.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/imstb_*.h"),		
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/addons/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/addons/**.h"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code/*.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code/header/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code/other/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code/source/**.c"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/enet/include/enet.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/librg/include/librg.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl-c.c"),

		path.join(JQ2_THIRD_PARTY_DIR, "glfw/include/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "opengles/include/**.h"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/internal.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/mappings.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/context.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/init.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/input.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/monitor.c"),
        path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/vulkan.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/window.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/osmesa_context.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/osmesa_context.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/egl_context.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/egl_context.c"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/deps/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/deps/**.c"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/deps/glad/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "glfw/deps/glad/**.c"),
		
		path.join(JQ2_THIRD_PARTY_DIR, "helper/**.h"),
		path.join(JQ2_THIRD_PARTY_DIR, "helper/**.cpp"),
	}
	
	excludes {
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/addons/**.cpp"),
		path.join(JQ2_THIRD_PARTY_DIR, "imgui/addons/**.h"),	
		path.join(JQ2_THIRD_PARTY_DIR, "zpl-c/zpl/code/source/**.c"),
	}
	
	configuration { "vs*" }
		files {
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/win32_joystick.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/win32_joystick.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/win32_platform.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/wgl_context.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/win32_init.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/win32_monitor.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/win32_time.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/win32_thread.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/win32_window.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/wgl_context.c"),
		}

	configuration { "not vs*" }
		files {
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/linux_joystick.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/linux_joystick.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/x11_platform.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/xkb_unicode.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/posix_time.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/posix_thread.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/glx_context.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/x11_init.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/x11_monitor.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/x11_window.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/xkb_unicode.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/posix_time.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/posix_thread.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/glx_context.c"),
		}
		
	configuration { "cygwin*" }
		files {
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/null_joystick.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/x11_platform.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/xkb_unicode.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/posix_time.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/posix_thread.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/glx_context.h"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/x11_init.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/x11_monitor.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/x11_window.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/xkb_unicode.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/posix_time.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/posix_thread.c"),
			path.join(JQ2_THIRD_PARTY_DIR, "glfw/src/glx_context.c"),
		}
	strip()	
	
-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------