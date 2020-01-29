/*
*
*    MIT License
*
*    Copyright (C) 2012  Adrian SIMINCIUC
*
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in all
*    copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*    SOFTWARE.
*/

#ifndef __JANSQ2GUI_H
#define __JANSQ2GUI_H

#include <iostream>
#include <assert.h>

#include <squirrel.h>
#include <sqrat.h>
#include <sqconfig.h>
#include <sqstdio.h>
#include <sqstdblob.h>
#include <sqstdmath.h>
#include <sqstdsystem.h>
#include <sqstdstring.h>
#include <sqratimport.h>
#include <sqrdbg.h>
#include <sqdbgserver.h>

#include <zpl.h>
#include <enet.h>
#include <librg.h>
#include <async++.h>
#include <jansson.hpp>
#include <imgui.h>
#include <sqlite3pp.h>

#include <GLFW/glfw3.h>

namespace jansq2gui
{
	typedef	char 			s8;
	typedef zpl_u8 			u8;
	typedef	zpl_i16			s16;
	typedef zpl_u16			u16;
	typedef	zpl_i32			s32;
	typedef zpl_u32			u32;
	typedef	zpl_i64		    s64;
	typedef zpl_u64		    u64;

	typedef zpl_f32			f32;
	typedef zpl_f64			f64;

	typedef size_t 			handle;
	typedef zpl_i32 		result;
};

namespace jansq2gui
{
    class CScript;
    class CSquirrel;
}

#define jansq2gui_assert( x, ... )			ZPL_ASSERT_MSG(x, __FUNCTION__, __VA_ARGS__)

#define jansq2gui_echo( ... )			    zpl_printf( __VA_ARGS__ )
#define jansq2gui_warn( ... )				zpl_printf( __VA_ARGS__ )
#define jansq2gui_error( ... )			    zpl_printf_err( __VA_ARGS__ )
#define jansq2gui_info( ... )				zpl_printf( __VA_ARGS__ )

#define jansq2gui_new						new
#define jansq2gui_delete(x)					{ if( x ) { delete x; x = nullptr; } }
#define jansq2gui_delete_array(x)			{ if( x ) { delete[] x; x = nullptr; } }

#define jansq2gui_memcpy					zpl_memcopy
#define jansq2gui_memcmp					zpl_memcompare
#define jansq2gui_memset					zpl_memset

namespace jansq2gui
{
    class Api
    {
    public:
        Api(): Width(640), Height(480), Title("jansq2gui"), WorkDir(""), Ok(false), VM(0) {};

    public:
        u32         Width;
        u32         Height;
        zpl_string  Title;
        zpl_string  WorkDir;
        bool        Ok;

        HSQOBJECT   RunFunc;
        HSQUIRRELVM VM;
    public:

        static void jansq2gui__Api_Init(zpl_string Title, u32 Width, u32 Height, Sqrat::Function func);
        static void jansq2gui__Run(Sqrat::Function func);

        bool        jansq2gui__ImGui__ShowDemoWindow();
        bool        jansq2gui__ImGui__ShowAboutWindow();
        bool        jansq2gui__ImGui__ShowMetricsWindow();

        void        jansq2gui__ImGui__Begin1(const char* name);
        void        jansq2gui__ImGui__Begin2(const char* name, bool* p_open);
        void        jansq2gui__ImGui__Begin3(const char* name, bool* p_open, ImGuiWindowFlags flags);

        bool        jansq2gui__ImGui__BeginChild11(const char* str_id);
        bool        jansq2gui__ImGui__BeginChild12(const char* str_id, const ImVec2& size);
        bool        jansq2gui__ImGui__BeginChild13(const char* str_id, const ImVec2& size, bool border);
        bool        jansq2gui__ImGui__BeginChild14(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags);

        bool        jansq2gui__ImGui__BeginChild21(ImGuiID id);
        bool        jansq2gui__ImGui__BeginChild22(ImGuiID id, const ImVec2& size);
        bool        jansq2gui__ImGui__BeginChild23(ImGuiID id, const ImVec2& size, bool border);
        bool        jansq2gui__ImGui__BeginChild24(ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags);

    };
};

extern jansq2gui::Api jansq2guiApi;

#endif // __JANSQ2GUI_H

