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

bool jansq2gui__Enet_False()
{
    return false;
}

void jansq2gui::CSquirrel::BindEnet()
{
    Sqrat::Table table(m_vm);
    m_rootTable->Bind(_SC("enet"), table);


    table.Bind(_SC("socket"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_Socket>(m_vm, _SC("socket"))
        .Ctor()
        .Var(_SC("fd"), &jansq2gui::Api::jansq2gui__Enet_Socket::fd)
    );

    table.Bind(_SC("address"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_Address>(m_vm, _SC("address"))
        .Ctor()
    );

    table.Bind(_SC("host"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_Host>(m_vm, _SC("host"))
        .Ctor()
    );

    table.Bind(_SC("peer"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_Peer>(m_vm, _SC("peer"))
        .Ctor()
    );

    table.Bind(_SC("packet"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_Packet>(m_vm, _SC("packet"))
        .Ctor()
    );

    table.Bind(_SC("buffer"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_Buffer>(m_vm, _SC("buffer"))
        .Ctor()
    );

    table.Func(_SC("initialize"), &enet_initialize);
    table.Func(_SC("deinitialize"), &enet_deinitialize);
    table.Func(_SC("linked_version"), &enet_linked_version);
    table.Func(_SC("time_get"), &enet_time_get);
}

// ----------------------------------------------------------------------//
