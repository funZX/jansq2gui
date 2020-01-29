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

#include <jansq2gui.h>
#include <jansq2gui_script.h>
#include <jansq2gui_squirrel.h>

static jansq2gui::CSquirrel    vm;
static jansq2gui::CScript      nut(&vm);

// ----------------------------------------------------------------------//

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        jansq2gui_error( "Usage: jansq2gui file.nut [width height]" );
        return 1;
    }
   
    const char* filename = argv[1];

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
    
    jansq2gui_memcpy(work_dir, full_name, file_base_name - full_name);
    work_dir[file_base_name - full_name] = 0;

    zpl_free(zpl_heap(), full_name);

    jansq2guiApi.WorkDir = work_dir;
    jansq2guiApi.VM = vm.GetSQVM();

    vm.DebugOn();
    nut.Run();

    if (OT_CLOSURE != jansq2guiApi.RunFunc._type)
    {
        jansq2gui_echo("Done!");
        return 0;
    }

    ImImpl_InitParams ini;
    ini.gWindowSize.x = jansq2guiApi.Width;
    ini.gWindowSize.y = jansq2guiApi.Height;
    jansq2gui_memcpy(ini.gWindowTitle, jansq2guiApi.Title, zpl_strlen(jansq2guiApi.Title) + 1);

    ImImpl_Main(&ini, argc, argv);

    return 0;
}

// ----------------------------------------------------------------------//

void DrawGL()
{
    static ImVec4 clearColor(0, 0, 0, 1);
    ImImpl_ClearColorBuffer(clearColor);

    vm.ExecMainFunc(jansq2guiApi.RunFunc);
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