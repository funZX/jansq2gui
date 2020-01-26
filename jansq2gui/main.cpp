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
    if (argc != 2 && argc != 4)
    {
        jansq2gui_error( "Usage: jansq2gui file.nut [width height]" );
        return 1;
    }
    const char* filename = argv[1];
    int width   = argc == 4 ? zpl_str_to_f32(argv[2], 0) : 480;
    int height  = argc == 4 ? zpl_str_to_f32(argv[3], 0) : 320;

    std::ifstream infile(filename);
    if (!infile.good())
    {
        jansq2gui_error("File not found %s", filename);
        return 1;
    }

    if (!nut.Load(filename))
    {
        jansq2gui_error("Failed to load %s", filename);
        return 1;
    }

    ImImpl_InitParams ini;
    ini.gWindowSize.x = width;
    ini.gWindowSize.y = height;
    jansq2gui_memcpy(ini.gWindowTitle, filename, zpl_strlen(filename) + 1);

    ImImpl_Main(&ini, argc, argv);

    return 0;
}

// ----------------------------------------------------------------------//

void DrawGL()
{
    static ImVec4 clearColor(0, 0, 0, 1);
    ImImpl_ClearColorBuffer(clearColor);

    nut.Run();
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