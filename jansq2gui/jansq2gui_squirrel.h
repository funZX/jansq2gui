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

#ifndef __JANSQ2GUI_SQUIRREL_H
#define __JANSQ2GUI_SQUIRREL_H

#include <jansq2gui.h>

namespace jansq2gui
{
// ----------------------------------------------------------------------//
class CScript;
// ----------------------------------------------------------------------//

class CSquirrel
{
public:
    typedef enum 
    {
        k_Error_None, 
		k_Error_Compile, 
		k_Error_Runtime

    } K_ERROR;
	// ------------------------------------------------------------------//
    CSquirrel();
    ~CSquirrel();
	// ------------------------------------------------------------------//
	HSQUIRRELVM						GetSQVM() { return m_vm; }

	template<class V>
	void							AddRootSlot(const SQChar* name, V* val);

	template<class V>
	void							AddConstSlot(const SQChar* name, V* val);

    void							SetPrintFunc(SQPRINTFUNCTION printFunc, SQPRINTFUNCTION errFunc);
    void							SetErrorHandler(SQFUNCTION runErr, SQCOMPILERERROR comErr);

    void                            ExecMainFunc( HSQOBJECT& func );
    K_ERROR							Exec( CScript* script );

    void							DebugOn();
    void							DebugOff();

	// ------------------------------------------------------------------//
protected:

	// ------------------------------------------------------------------//
    void		                    BindImGui(Sqrat::Class<jansq2gui::Api>& api);
    void		                    BindZpl(Sqrat::Class<jansq2gui::Api>& api);
    void		                    BindEnet(Sqrat::Class<jansq2gui::Api>& api);
    void		                    BindLibrg(Sqrat::Class<jansq2gui::Api>& api);
    void		                    BindSqlite(Sqrat::Class<jansq2gui::Api>& api);
    void		                    BindJson(Sqrat::Class<jansq2gui::Api>& api);

	void							BindAll();
	// ------------------------------------------------------------------//


    static void						PrintFunc(HSQUIRRELVM v, const SQChar *s, ...);
    static SQInteger				RuntimeErrorHandler(HSQUIRRELVM v);
    static void						CompilerErrorHandler(HSQUIRRELVM v,
														const SQChar* desc,
														const SQChar* source,
														SQInteger line,
														SQInteger column);
	// ------------------------------------------------------------------//
protected:
	// ------------------------------------------------------------------//
    HSQUIRRELVM						m_vm;
    Sqrat::RootTable*				m_rootTable;
	Sqrat::ConstTable*				m_constTable;

	HSQREMOTEDBG					m_rdbg;
    bool                            m_rdbg_shutdown;
	// ------------------------------------------------------------------//
};

// ----------------------------------------------------------------------//
template<class V>
void CSquirrel::AddRootSlot(const SQChar* name, V* val)
{
	m_rootTable->SetInstance(name, val);
}

// ----------------------------------------------------------------------//
template<class V>
void CSquirrel::AddConstSlot(const SQChar* name, V* val)
{
	m_constTable->Enum(name, val);
}

// ----------------------------------------------------------------------//
}; // namespace jansq2gui

#endif // __JANSQ2GUI_SQUIRREL_H
