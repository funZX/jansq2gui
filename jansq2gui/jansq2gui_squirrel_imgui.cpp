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
#include <lib/jansq2gui_rect.h>

// ----------------------------------------------------------------------//

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__Begin1(const char* name)
{
    jansq2gui::Api::jansq2gui__ImGui_Status ret;
    ret.show = ImGui::Begin(name, 0, 0);
    return ret;
}

// ----------------------------------------------------------------------//

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__Begin2(const char* name, ImGuiWindowFlags flags)
{
    jansq2gui::Api::jansq2gui__ImGui_Status ret;    
    ret.show = ImGui::Begin(name, 0, flags);
    return ret;
}

// ----------------------------------------------------------------------//

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__Begin3(const char* name, ImGuiWindowFlags flags, bool p_open)
{
    jansq2gui::Api::jansq2gui__ImGui_Status ret;
    ret.show = ImGui::Begin(name, p_open ? &ret.open : 0, flags);
    return ret;
}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild1(const char* str_id)
{
    return ImGui::BeginChild(str_id);
}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild2(const char* str_id, const ImVec2& size)
{
    return ImGui::BeginChild(str_id, size);
}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild3(const char* str_id, const ImVec2& size, bool border)
{
    return ImGui::BeginChild(str_id, size, border);
}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild4(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
    return ImGui::BeginChild(str_id, size, border, flags);
}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId1(ImGuiID id)
{
    return ImGui::BeginChild(id);
}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId2(ImGuiID id, const ImVec2& size)
{
    return ImGui::BeginChild(id, size);

}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId3(ImGuiID id, const ImVec2& size, bool border)
{
    return ImGui::BeginChild(id, size, border);
}

// ----------------------------------------------------------------------//

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId4(ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
    return ImGui::BeginChild(id, size, border, flags);
}

// ----------------------------------------------------------------------//

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow()
{
    ImGui::ShowDemoWindow();

    jansq2gui::Api::jansq2gui__ImGui_Status ret;
    ret.show = true;
    return ret;
}

// ----------------------------------------------------------------------//

jansq2gui::Api::jansq2gui__ImGui_Status jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow(bool p_open)
{
    jansq2gui::Api::jansq2gui__ImGui_Status ret;
    ret.show = true;
    ImGui::ShowDemoWindow(p_open ? &ret.open : 0);
    return ret;
}

// ----------------------------------------------------------------------//

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
        .Var(_SC("Show"), &jansq2gui::Api::jansq2gui__ImGui_Status::show)
        .Var(_SC("Open"), &jansq2gui::Api::jansq2gui__ImGui_Status::open)
    );

    table.Bind(_SC("rect"), Sqrat::Class<jansq2gui::CRect>(m_vm, _SC("rect"))
        .Ctor()
        .Ctor<ImVec2, ImVec2>()
        .Ctor<float, float, float, float>()
        .Prop(_SC("Left"), &jansq2gui::CRect::Left)
        .Prop(_SC("Right"), &jansq2gui::CRect::Right)
        .Prop(_SC("Top"), &jansq2gui::CRect::Top)
        .Prop(_SC("Bottom"), &jansq2gui::CRect::Bottom)
        .Prop(_SC("Width"), &jansq2gui::CRect::Width)
        .Prop(_SC("Height"), &jansq2gui::CRect::Height)
        .Prop(_SC("Center"), &jansq2gui::CRect::GetCenter)
        .Prop(_SC("TopLeft"), &jansq2gui::CRect::TopLeft)
        .Prop(_SC("TopRight"), &jansq2gui::CRect::TopRight)
        .Prop(_SC("BottomLeft"), &jansq2gui::CRect::BottomLeft)
        .Prop(_SC("BottomRight"), &jansq2gui::CRect::BottomRight)
        .Overload<void(jansq2gui::CRect::*)(ImVec2)>(_SC("move"), &jansq2gui::CRect::Move)
        .Overload<void(jansq2gui::CRect::*)(float, float)>(_SC("move"), &jansq2gui::CRect::Move)
        .Overload<void(jansq2gui::CRect::*)(ImVec2)>(_SC("moveto"), &jansq2gui::CRect::MoveTo)
        .Overload<void(jansq2gui::CRect::*)(float, float)>(_SC("moveto"), &jansq2gui::CRect::MoveTo)
        .Overload<void(jansq2gui::CRect::*)(ImVec2)>(_SC("inflate"), &jansq2gui::CRect::Inflate)
        .Overload<void(jansq2gui::CRect::*)(float, float)>(_SC("inflate"), &jansq2gui::CRect::Inflate)
        .Overload<void(jansq2gui::CRect::*)(ImVec2)>(_SC("zoom"), &jansq2gui::CRect::Zoom)
        .Overload<void(jansq2gui::CRect::*)(float, float)>(_SC("zoom"), &jansq2gui::CRect::Zoom)
        .Overload<void(jansq2gui::CRect::*)(ImVec2)>(_SC("resize"), &jansq2gui::CRect::Resize)
        .Overload<void(jansq2gui::CRect::*)(float, float)>(_SC("resize"), &jansq2gui::CRect::Resize)
        .Overload<void(jansq2gui::CRect::*)(ImVec2)>(_SC("scale"), &jansq2gui::CRect::Scale)
        .Overload<void(jansq2gui::CRect::*)(float, float)>(_SC("scale"), &jansq2gui::CRect::Scale)
        .Overload<void(jansq2gui::CRect::*)(ImVec2)>(_SC("center"), &jansq2gui::CRect::SetCenter)
        .Overload<void(jansq2gui::CRect::*)(float, float)>(_SC("center"), &jansq2gui::CRect::SetCenter)
        .Func(_SC("align"), &jansq2gui::CRect::AlignTo)
        .StaticFunc(_SC("union"), &jansq2gui::CRect::Union)
        .StaticFunc(_SC("intersect"), &jansq2gui::CRect::Intersect)
        .Overload<bool(jansq2gui::CRect::*)(ImVec2)>(_SC("is_inside"), &jansq2gui::CRect::IsInside)
        .Overload<bool(jansq2gui::CRect::*)(float, float)>(_SC("is_inside"), &jansq2gui::CRect::IsInside)
        .Overload<void(jansq2gui::CRect::*)(jansq2gui::CRect)>(_SC("bound"), &jansq2gui::CRect::Bound)
        .Overload<void(jansq2gui::CRect::*)(ImVec2, ImVec2)>(_SC("bound"), &jansq2gui::CRect::Bound)
        .Overload<void(jansq2gui::CRect::*)(float, float, float, float)>(_SC("bound"), &jansq2gui::CRect::Bound)
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
