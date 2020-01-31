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

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__Begin1(const char* name)
{
    jansq2gui::Api::jansq2gui__ImGui_Status ret;
    ret.show = ImGui::Begin(name, 0, 0);
    return ret;
}

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__Begin2(const char* name, ImGuiWindowFlags flags)
{
    jansq2gui::Api::jansq2gui__ImGui_Status ret;    
    ret.show = ImGui::Begin(name, 0, flags);
    return ret;
}

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__Begin3(const char* name, ImGuiWindowFlags flags, bool p_open)
{
    jansq2gui::Api::jansq2gui__ImGui_Status ret;
    ret.show = ImGui::Begin(name, p_open ? &ret.open : 0, flags);
    return ret;
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild1(const char* str_id)
{
    return ImGui::BeginChild(str_id);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild2(const char* str_id, const ImVec2& size)
{
    return ImGui::BeginChild(str_id, size);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild3(const char* str_id, const ImVec2& size, bool border)
{
    return ImGui::BeginChild(str_id, size, border);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild4(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
    return ImGui::BeginChild(str_id, size, border, flags);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId1(ImGuiID id)
{
    return ImGui::BeginChild(id);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId2(ImGuiID id, const ImVec2& size)
{
    return ImGui::BeginChild(id, size);

}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId3(ImGuiID id, const ImVec2& size, bool border)
{
    return ImGui::BeginChild(id, size, border);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId4(ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
    return ImGui::BeginChild(id, size, border, flags);
}


jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow()
{
    ImGui::ShowDemoWindow();

    jansq2gui::Api::jansq2gui__ImGui_Status ret;
    ret.show = true;
    return ret;
}

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow(bool p_open)
{
    jansq2gui::Api::jansq2gui__ImGui_Status ret;
    ret.show = true;
    ImGui::ShowDemoWindow(p_open ? &ret.open : 0);
    return ret;
}

void jansq2gui::CSquirrel::BindImGui()
{
    Sqrat::Table table(m_vm);
    m_rootTable->Bind(_SC("imgui"), table);

    table.Bind(_SC("vec2"), Sqrat::Class<ImVec2>(m_vm, _SC("vec2"))
        .Ctor()
        .Ctor<float, float>()
        .Var(_SC("x"), &ImVec2::x)
        .Var(_SC("y"), &ImVec2::y)
    );

    table.Bind(_SC("vec4"), Sqrat::Class<ImVec4>(m_vm, _SC("vec4"))
        .Ctor()
        .Ctor<float, float, float, float>()
        .Var(_SC("x"), &ImVec4::x)
        .Var(_SC("y"), &ImVec4::y)
        .Var(_SC("z"), &ImVec4::z)
        .Var(_SC("w"), &ImVec4::w)
    );

    table.Bind(_SC("status"), Sqrat::Class<jansq2gui::Api::jansq2gui__ImGui_Status>(m_vm, _SC("status"))
        .Ctor()
        .Var(_SC("show"), &jansq2gui::Api::jansq2gui__ImGui_Status::show)
        .Var(_SC("open"), &jansq2gui::Api::jansq2gui__ImGui_Status::open)
    );

    table.Func(_SC("get_version"),             &ImGui::GetVersion);

    table.Overload<jansq2gui::Api::jansq2gui__ImGui_Status(*)()>
        (_SC("show_demo_window"),              &jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow);
    table.Overload<jansq2gui::Api::jansq2gui__ImGui_Status(*)(bool)>
        (_SC("show_demo_window"),              &jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow);

    table.Overload
        (_SC("begin"),                         &jansq2gui::Api::jansq2gui__ImGui__Begin1);
    table.Overload
        (_SC("begin"),                         &jansq2gui::Api::jansq2gui__ImGui__Begin2);
    table.Overload
        (_SC("begin"),                         &jansq2gui::Api::jansq2gui__ImGui__Begin3);

    table.Func(_SC("end"),                     &ImGui::End);

    table.Overload
        (_SC("begin_child"),                   &jansq2gui::Api::jansq2gui__ImGui__BeginChild1);
    table.Overload
        (_SC("begin_child"),                   &jansq2gui::Api::jansq2gui__ImGui__BeginChild2);
    table.Overload
        (_SC("begin_child"),                   &jansq2gui::Api::jansq2gui__ImGui__BeginChild3);
    table.Overload
        (_SC("begin_child"),                   &jansq2gui::Api::jansq2gui__ImGui__BeginChild4);

    table.Overload
        (_SC("begin_child_id"),                &jansq2gui::Api::jansq2gui__ImGui__BeginChild1);
    table.Overload
        (_SC("begin_child_id"),                &jansq2gui::Api::jansq2gui__ImGui__BeginChild2);
    table.Overload
        (_SC("begin_child_id"),                &jansq2gui::Api::jansq2gui__ImGui__BeginChild3);
    table.Overload
        (_SC("begin_child_id"),                &jansq2gui::Api::jansq2gui__ImGui__BeginChild4);

    table.Func(_SC("end_child"),               &ImGui::EndChild);

}
// ----------------------------------------------------------------------//
