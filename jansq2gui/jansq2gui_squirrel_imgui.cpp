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

bool jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow()
{
    bool ret = false;
    ImGui::ShowDemoWindow(&ret);
    return ret;
}

bool jansq2gui::Api::jansq2gui__ImGui__ShowAboutWindow()
{
    bool ret = false;
    ImGui::ShowAboutWindow(&ret);
    return ret;
}

bool jansq2gui::Api::jansq2gui__ImGui__ShowMetricsWindow()
{
    bool ret = false;
    ImGui::ShowMetricsWindow(&ret);
    return ret;
}

void jansq2gui::Api::jansq2gui__ImGui__Begin(const char* name, bool* p_open, ImGuiWindowFlags flags)
{
    ImGui::Begin(name, p_open, flags);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
    return ImGui::BeginChild(str_id, size, border, flags);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChildId(ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
    return ImGui::BeginChild(id, size, border, flags);
}

void jansq2gui::CSquirrel::BindImGui()
{
    Sqrat::Table table(m_vm);
    m_rootTable->Bind(_SC("imgui"), table);

    table.Func(_SC("get_version"),             &ImGui::GetVersion);

    table.Func(_SC("show_demo_window"),        &jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow);
    table.Func(_SC("show_about_window"),       &jansq2gui::Api::jansq2gui__ImGui__ShowAboutWindow);
    table.Func(_SC("show_metrics_window"),     &jansq2gui::Api::jansq2gui__ImGui__ShowMetricsWindow);

    table.Func(_SC("begin"),                   &jansq2gui::Api::jansq2gui__ImGui__Begin);
    table.Func(_SC("end"),                     &ImGui::End);

    table.Func(_SC("begin_child"),             &jansq2gui::Api::jansq2gui__ImGui__BeginChild);
    table.Func(_SC("begin_child_id"),          &jansq2gui::Api::jansq2gui__ImGui__BeginChildId);
    table.Func(_SC("end_child"),               &ImGui::EndChild);
}
// ----------------------------------------------------------------------//
