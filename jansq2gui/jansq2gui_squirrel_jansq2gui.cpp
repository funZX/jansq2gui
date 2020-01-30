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

void jansq2gui::CSquirrel::BindJansq2gui()
{
    Sqrat::Class<jansq2gui::Api> api(m_vm, "api");

    api.ConstVar(_SC("Width"), &jansq2gui::Api::Width);
    api.ConstVar(_SC("Height"), &jansq2gui::Api::Height);
    api.ConstVar(_SC("Title"), &jansq2gui::Api::Title);
    api.ConstVar(_SC("WorkDir"), &jansq2gui::Api::WorkDir);

    m_rootTable->SetInstance(_SC("jansq2gui"), &jansq2guiApi);
    m_rootTable->Func(_SC("jansq2gui__Api_Init"), &jansq2gui::Api::jansq2gui__Api_Init);
    m_rootTable->Func(_SC("jansq2gui__Run"), &jansq2gui::Api::jansq2gui__Run);
}

// ----------------------------------------------------------------------//
