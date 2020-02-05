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
	
jansq2gui::CScript::CScript( CSquirrel* sq )
	:Sqrat::Script( sq->GetSQVM() )
{

}

// ----------------------------------------------------------------------//

jansq2gui::CScript::~CScript()
{

}

// ----------------------------------------------------------------------//

bool jansq2gui::CScript::Load(const SQChar* filename)
{
    SQRESULT result = sqstd_loadfile(vm, filename, SQTrue);

    sq_getstackobj(vm, -1, &obj);
    sq_addref(vm, &obj);
    sq_pop(vm, 1);

    return SQ_OK == result;
}
// ----------------------------------------------------------------------//
