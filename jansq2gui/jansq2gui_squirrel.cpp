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

#include <jansq2gui_script.h>
#include <jansq2gui_squirrel.h>

// ----------------------------------------------------------------------//

jansq2gui::CSquirrel::CSquirrel()
    : m_vm( sq_open( 1024 ) )
    , m_rootTable( jansq2gui_new Sqrat::RootTable( m_vm ) )
	, m_constTable( jansq2gui_new Sqrat::ConstTable( m_vm ) )
{
    Sqrat::DefaultVM::Set( m_vm );

    sq_pushroottable( m_vm );

    sqstd_register_iolib( m_vm );
    sqstd_register_bloblib( m_vm );
    sqstd_register_mathlib( m_vm );
    sqstd_register_systemlib( m_vm );
    sqstd_register_stringlib( m_vm );
	sqrat_register_importlib( m_vm );
    
    sq_pop( m_vm, 1 );

    SetPrintFunc( PrintFunc, PrintFunc );
    SetErrorHandler( RuntimeErrorHandler, CompilerErrorHandler );

	BindAll();

	m_rdbg = nullptr;
    m_rdbg_shutdown = false;
}

// ----------------------------------------------------------------------//

jansq2gui::CSquirrel::~CSquirrel()
{
    m_rdbg_shutdown = true;
    
    if (m_rdbg)
        DebugOff();
    while (m_rdbg)
        zpl_sleep_ms(50);

	jansq2gui_delete( m_constTable );
    delete( m_rootTable );
    sq_close(m_vm);
}

// ----------------------------------------------------------------------//

void jansq2gui::CSquirrel::PrintFunc( HSQUIRRELVM v, const SQChar *s, ... )
{
    va_list vl;
    va_start( vl, s );
    zpl_printf_va( s, vl );
    va_end( vl );
}

// ----------------------------------------------------------------------//

SQInteger jansq2gui::CSquirrel::RuntimeErrorHandler( HSQUIRRELVM v )
{
    const SQChar *sErr = 0;
    if( sq_gettop(v) >= 1 )
    {
        if( SQ_SUCCEEDED( sq_getstring( v, 2, &sErr ) ) )
        {
            jansq2gui_error(_SC("RuntimeError: %s\n"), sErr);
        }
        else
        {
            jansq2gui_error(_SC("An Unknown RuntimeError Occured.\n"));
        }
    }
    return 0;
}

// ----------------------------------------------------------------------//

void jansq2gui::CSquirrel::CompilerErrorHandler( HSQUIRRELVM v,
    const SQChar* desc,
    const SQChar* source,
    SQInteger line,
    SQInteger column )
{

    jansq2gui_error(_SC("%s(%d:%d): %s"), source, line, column, desc );
}

// ----------------------------------------------------------------------//

void jansq2gui::CSquirrel::SetPrintFunc( SQPRINTFUNCTION printFunc, SQPRINTFUNCTION errFunc )
{
    sq_setprintfunc( m_vm, printFunc, errFunc );
}

// ----------------------------------------------------------------------//

void jansq2gui::CSquirrel::SetErrorHandler( SQFUNCTION runErr, SQCOMPILERERROR comErr )
{
    sq_newclosure( m_vm, runErr, 0 );
    sq_seterrorhandler( m_vm );

    sq_setcompilererrorhandler( m_vm, comErr );
}

// ----------------------------------------------------------------------//

void jansq2gui::CSquirrel::ExecMainFunc(HSQOBJECT& func)
{
    sq_pushroottable(m_vm);
    sq_pushobject(m_vm, func);
    sq_pushroottable(m_vm);
    sq_call(m_vm, 1, SQFalse, Sqrat::ErrorHandling::IsEnabled());
    sq_pop(m_vm, 2);
}

// ----------------------------------------------------------------------//

jansq2gui::CSquirrel::K_ERROR jansq2gui::CSquirrel::Exec( jansq2gui::CScript* script )
{
    Sqrat::string msg;
	return script->Run( msg ) ? k_Error_None : k_Error_Runtime;
}

// ----------------------------------------------------------------------//

void jansq2gui::CSquirrel::BindAll()
{
    BindJansq2gui();
    BindZpl();
    BindEnet();
    BindLibrg();
    BindSqlite();
    BindJson();
    BindImGui();
}

// ----------------------------------------------------------------------//

void jansq2gui::CSquirrel::DebugOn(unsigned short port)
{
    if (m_rdbg)
        return;

    m_rdbg = sq_rdbg_init(m_vm, port, SQTrue);

    jansq2gui_assert(m_rdbg, "Debugger failed to start!");

    sq_enabledebuginfo(m_vm, SQTrue);

    auto start_task = async::spawn([&, this] {
        sq_rdbg_waitforconnections(m_rdbg);
    });

    auto stop_task = start_task.then([&, this] {

        while (!m_rdbg->_terminate)
            sq_rdbg_update(m_rdbg);

        sq_rdbg_shutdown(m_rdbg);

        m_rdbg = nullptr;
        if (!m_rdbg_shutdown)
            DebugOn(port);
     });
}

void jansq2gui::CSquirrel::DebugOff()
{
	if (m_rdbg)
	{
		sq_rdbg_term(m_rdbg);
		sq_enabledebuginfo(m_vm, SQFalse);
	}

    m_rdbg_shutdown = true;
}

// ----------------------------------------------------------------------//

