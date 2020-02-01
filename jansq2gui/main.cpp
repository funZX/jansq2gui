/*
*
*    MIT License
*
*    Copyright (C) 2020  Adrian SIMINCIUC
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
#include <fstream>
#include <console.h>

#include <jansq2gui.h>
#include <jansq2gui_script.h>
#include <jansq2gui_squirrel.h>

static jansq2gui::CSquirrel    vm;
static jansq2gui::CScript      nut(&vm);

struct Options
{
public:
    zpl_opts o;

    Options(char* name) { zpl_opts_init(&o, zpl_heap(), name); }
    ~Options() { zpl_opts_free(&o); }
};

struct Console
{
public:
    Console()   { open_console(); }
    ~Console()  { close_console(); }
};

struct Debugger
{
public:
    jansq2gui::CSquirrel* vm;

    Debugger(jansq2gui::CSquirrel* v, unsigned short port) : vm(v) { if (vm) vm->DebugOn(port); }
    ~Debugger() { if (vm) vm->DebugOff(); }
};

// ----------------------------------------------------------------------//

int main(int argc, char** argv)
{
    Console console;
    Options options(argv[0]);

    zpl_opts_add(&options.o, "d", "debug",     "Start with debugger.", ZPL_OPTS_FLAG);
    zpl_opts_add(&options.o, "p", "debugport", "Debugger port", ZPL_OPTS_INT);
    zpl_opts_add(&options.o, "e", "exec",   "Path to script.", ZPL_OPTS_STRING);
    zpl_opts_add(&options.o, "a", "args", "Command line arguments for script", ZPL_OPTS_STRING);

    if (!zpl_opts_compile(&options.o, argc, argv) || !zpl_opts_has_arg(&options.o, "exec"))
    {
        zpl_opts_print_errors(&options.o);
        zpl_opts_print_help(&options.o);
        return 0;
    }

    const char* filename    = zpl_opts_string(&options.o, "exec", "");
    bool debugOn            = zpl_opts_has_arg(&options.o, "debug");
    int debugPort           = zpl_opts_integer(&options.o, "debugport", 20900);
    
    jansq2gui::CSquirrel* debugVm = (debugOn && (debugPort > 0 && debugPort < USHRT_MAX)) ? &vm : 0;
    Debugger debugger       = Debugger(debugVm, debugPort);

    if (!zpl_fs_exists(filename))
    {
        jansq2gui_error("File not found %s", filename);
        return 1;
    }

    if (!nut.Load(filename))
    {
        jansq2gui_error("Failed to load %s", filename);
        return 1;
    }

    static char work_dir[256];
    char* full_name = zpl_path_get_full_name(zpl_heap(), filename);
    const char* file_base_name = zpl_path_base_name(full_name);
    int file_full_path_size = file_base_name - full_name;

    jansq2gui_memcpy(work_dir, full_name, file_full_path_size);
    work_dir[file_full_path_size] = 0;

    zpl_free(zpl_heap(), full_name);

    jansq2guiApi.WorkDir = work_dir;
    jansq2guiApi.VM = vm.GetSQVM();
    sqrat_importlib_library_path = jansq2guiApi.WorkDir;

    nut.Run();

    if (OT_CLOSURE != jansq2guiApi.RunFunc._type)
        return 0;

    const unsigned char ttf_font[] = 
#                                   include "ttf_font.inl"
        ;

    ImImpl_InitParams ini(
        jansq2guiApi.Width,
        jansq2guiApi.Height,
        jansq2guiApi.Title,
        0,
        (const unsigned char*)ttf_font, sizeof(ttf_font) / sizeof(ttf_font[0]),
        16);

    ImImpl_Main(&ini, argc, argv);
    return 0;
}

// ----------------------------------------------------------------------//

void DrawGL()
{
    static ImVec4 clearColor(0, 0, 0, 1);
    ImImpl_ClearColorBuffer(clearColor);

    vm.ExecMainFunc(jansq2guiApi.RunFunc);
    fflush(0);
}

// ----------------------------------------------------------------------//

void InitGL()
{

}

void ResizeGL(int w, int h)
{
}

void DestroyGL()
{
}