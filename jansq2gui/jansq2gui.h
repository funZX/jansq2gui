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

}; // namespace jansq2gui

#define jansq2gui_assert( x )				ZPL_ASSERT_MSG(x, __FUNCTION__)

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

#endif // __JANSQ2GUI_H
