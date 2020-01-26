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

#include <jansq2gui_squirrel.h>

// ----------------------------------------------------------------------//

bool jansq2gui__ImGui__ShowDemoWindow()
{
    bool ret = false;
    ImGui::ShowDemoWindow(&ret);
    return ret;
}

void jansq2gui::CSquirrel::BindAll()
{
    Sqrat::Table imgui(m_vm);    
    imgui.Func("ShowDemoWindow", &jansq2gui__ImGui__ShowDemoWindow);
    m_rootTable->Bind("imgui", imgui);
}

// ----------------------------------------------------------------------//
