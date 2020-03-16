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

jansq2gui::Api::jansq2gui__Enet_Address::jansq2gui__Enet_Address(EAddressInit addr_init, enet_uint16 port, enet_uint16 sin6_scope_id)
{
    address.port = port;
    address.sin6_scope_id = 0;

    switch (addr_init)
    {
    case ENET_ADDRESS_ANY:
        address = IN6ADDR_ANY_INIT;
        break;
    case ENET_ADDRESS_LOOPBACK:
        address = IN6ADDR_LOOPBACK_INIT;
        break;
    }
}

// ----------------------------------------------------------------------//

jansq2gui::Api::jansq2gui__Enet_Address::jansq2gui__Enet_Address(EAddressInit addr_init, enet_uint16 port)
    :jansq2gui__Enet_Address(addr_init, port, 0)
{

}

// ----------------------------------------------------------------------//

void jansq2gui::Api::jansq2gui__Enet_SockSet::zero()
{
    ENET_SOCKETSET_EMPTY(socketset);
}

// ----------------------------------------------------------------------//

void jansq2gui::Api::jansq2gui__Enet_SockSet::set(jansq2gui__Enet_Socket socket)
{
    ENET_SOCKETSET_ADD(socketset, socket.socket);
}

// ----------------------------------------------------------------------//

void jansq2gui::Api::jansq2gui__Enet_SockSet::clr(jansq2gui__Enet_Socket socket)
{
    ENET_SOCKETSET_REMOVE(socketset, socket.socket);
}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__Enet_SockSet::isset(jansq2gui__Enet_Socket socket)
{
    return 0 != ENET_SOCKETSET_CHECK(socketset, socket.socket);
}

// ----------------------------------------------------------------------//

jansq2gui::Api::jansq2gui__Enet_Socket::jansq2gui__Enet_Socket(ENetSocketType type)
{
    socket = enet_socket_create(type);
}

// ----------------------------------------------------------------------//

jansq2gui::Api::jansq2gui__Enet_Socket::~jansq2gui__Enet_Socket()
{
    enet_socket_destroy(socket);
}

// ----------------------------------------------------------------------//

void jansq2gui::CSquirrel::BindEnet()
{
    Sqrat::Table table(m_vm);
    
    m_constTable->Enum(_SC("EnetSocketType"), Sqrat::Enumeration(m_vm)
        .Const(_SC("ENET_SOCKET_TYPE_STREAM"), ENET_SOCKET_TYPE_STREAM)
        .Const(_SC("ENET_SOCKET_TYPE_DATAGRAM"), ENET_SOCKET_TYPE_DATAGRAM)
    );

    m_constTable->Enum(_SC("ENetSocketWait"), Sqrat::Enumeration(m_vm)
        .Const(_SC("ENET_SOCKET_WAIT_NONE"), ENET_SOCKET_WAIT_NONE)
        .Const(_SC("ENET_SOCKET_WAIT_SEND"), ENET_SOCKET_WAIT_SEND)
        .Const(_SC("ENET_SOCKET_WAIT_RECEIVE"), ENET_SOCKET_WAIT_NONE)
        .Const(_SC("ENET_SOCKET_WAIT_INTERRUPT"), ENET_SOCKET_WAIT_SEND)
    );

    m_constTable->Enum(_SC("ENetSocketOption"), Sqrat::Enumeration(m_vm)
        .Const(_SC("ENET_SOCKOPT_NONBLOCK"), ENET_SOCKOPT_NONBLOCK)
        .Const(_SC("ENET_SOCKOPT_BROADCAST"), ENET_SOCKOPT_BROADCAST)
        .Const(_SC("ENET_SOCKOPT_RCVBUF"), ENET_SOCKOPT_RCVBUF)
        .Const(_SC("ENET_SOCKOPT_SNDBUF"), ENET_SOCKOPT_SNDBUF)
        .Const(_SC("ENET_SOCKOPT_REUSEADDR"), ENET_SOCKOPT_REUSEADDR)
        .Const(_SC("ENET_SOCKOPT_RCVTIMEO"), ENET_SOCKOPT_RCVTIMEO)
        .Const(_SC("ENET_SOCKOPT_SNDTIMEO"), ENET_SOCKOPT_SNDTIMEO)
        .Const(_SC("ENET_SOCKOPT_ERROR"), ENET_SOCKOPT_ERROR)
        .Const(_SC("ENET_SOCKOPT_NODELAY"), ENET_SOCKOPT_NODELAY)
        .Const(_SC("ENET_SOCKOPT_IPV6_V6ONLY"), ENET_SOCKOPT_IPV6_V6ONLY)
    );

    m_constTable->Enum(_SC("ENetSocketShutdown"), Sqrat::Enumeration(m_vm)
        .Const(_SC("ENET_SOCKET_SHUTDOWN_READ"), ENET_SOCKET_SHUTDOWN_READ)
        .Const(_SC("ENET_SOCKET_SHUTDOWN_WRITE"), ENET_SOCKET_SHUTDOWN_WRITE)
        .Const(_SC("ENET_SOCKET_SHUTDOWN_READ_WRITE"), ENET_SOCKET_SHUTDOWN_READ_WRITE)
    );
    
    m_constTable->Enum(_SC("ENetAddressInit"), Sqrat::Enumeration(m_vm)
        .Const(_SC("ENET_ADDRESS_ANY"), jansq2gui::Api::jansq2gui__Enet_Address::ENET_ADDRESS_ANY)
        .Const(_SC("ENET_ADDRESS_LOOPBACK"), jansq2gui::Api::jansq2gui__Enet_Address::ENET_ADDRESS_LOOPBACK)
    );

    m_rootTable->Bind(_SC("enet"), table);

    table.Bind(_SC("address"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_Address>(m_vm, _SC("address"))
        .Ctor<jansq2gui::Api::jansq2gui__Enet_Address::EAddressInit, enet_uint16, enet_uint16>()
        .Ctor<jansq2gui::Api::jansq2gui__Enet_Address::EAddressInit, enet_uint16>()
    );

    table.Bind(_SC("socketset"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_SockSet>(m_vm, _SC("socketset"))
        .Ctor()
        .Func(_SC("zero"), &jansq2gui::Api::jansq2gui__Enet_SockSet::zero)
        .Func(_SC("set"), &jansq2gui::Api::jansq2gui__Enet_SockSet::set)
        .Func(_SC("clr"), &jansq2gui::Api::jansq2gui__Enet_SockSet::clr)
        .Func(_SC("isset"), &jansq2gui::Api::jansq2gui__Enet_SockSet::isset)
    );

    table.Bind(_SC("socket"), Sqrat::Class<jansq2gui::Api::jansq2gui__Enet_Socket>(m_vm, _SC("socket"))
        .Ctor<ENetSocketType>()
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
