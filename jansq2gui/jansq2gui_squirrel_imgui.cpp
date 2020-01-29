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

void jansq2gui::Api::jansq2gui__ImGui__Begin1(const char* name)
{
    ImGui::Begin(name, 0, 0);
}

void jansq2gui::Api::jansq2gui__ImGui__Begin2(const char* name, bool* p_open)
{
    ImGui::Begin(name, p_open, 0);
}

void jansq2gui::Api::jansq2gui__ImGui__Begin3(const char* name, bool* p_open, ImGuiWindowFlags flags)
{
    ImGui::Begin(name, p_open, flags);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild11(const char* str_id)
{
    return ImGui::BeginChild(str_id, ImVec2(0, 0), false, 0);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild12(const char* str_id, const ImVec2& size)
{
    return ImGui::BeginChild(str_id, size, false, 0);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild13(const char* str_id, const ImVec2& size, bool border)
{
    return ImGui::BeginChild(str_id, size, border, 0);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild14(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
    return ImGui::BeginChild(str_id, size, border, flags);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild21(ImGuiID id)
{
    return ImGui::BeginChild(id, ImVec2(0, 0), false, 0);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild22(ImGuiID id, const ImVec2& size)
{
    return ImGui::BeginChild(id, size, false, 0);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild23(ImGuiID id, const ImVec2& size, bool border)
{
    return ImGui::BeginChild(id, size, border, 0);
}

bool jansq2gui::Api::jansq2gui__ImGui__BeginChild24(ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
    return ImGui::BeginChild(id, size, border, flags);
}

void jansq2gui::CSquirrel::BindImGui(Sqrat::Class<jansq2gui::Api>& api )
{
    api.StaticFunc(_SC("imgui_get_version"),       &ImGui::GetVersion);

    api.Func(_SC("imgui_show_demo_window"),        &jansq2gui::Api::jansq2gui__ImGui__ShowDemoWindow);
    api.Func(_SC("imgui_show_about_window"),       &jansq2gui::Api::jansq2gui__ImGui__ShowAboutWindow);
    api.Func(_SC("imgui_show_metrics_window"),     &jansq2gui::Api::jansq2gui__ImGui__ShowMetricsWindow);

    api.Overload(_SC("imgui_begin"),               &jansq2gui::Api::jansq2gui__ImGui__Begin1);
    api.Overload(_SC("imgui_begin"),               &jansq2gui::Api::jansq2gui__ImGui__Begin2);
    api.Overload(_SC("imgui_begin"),               &jansq2gui::Api::jansq2gui__ImGui__Begin3);
    api.StaticFunc(_SC("imgui_end"),               &ImGui::End);

    api.Overload(_SC("imgui_begin_child"),         &jansq2gui::Api::jansq2gui__ImGui__BeginChild11);
    api.Overload(_SC("imgui_begin_child"),         &jansq2gui::Api::jansq2gui__ImGui__BeginChild12);
    api.Overload(_SC("imgui_begin_child"),         &jansq2gui::Api::jansq2gui__ImGui__BeginChild13);
    api.Overload(_SC("imgui_begin_child"),         &jansq2gui::Api::jansq2gui__ImGui__BeginChild14);
    api.Overload(_SC("imgui_begin_child_id"),      &jansq2gui::Api::jansq2gui__ImGui__BeginChild21);
    api.Overload(_SC("imgui_begin_child_id"),      &jansq2gui::Api::jansq2gui__ImGui__BeginChild22);
    api.Overload(_SC("imgui_begin_child_id"),      &jansq2gui::Api::jansq2gui__ImGui__BeginChild23);
    api.Overload(_SC("imgui_begin_child_id"),      &jansq2gui::Api::jansq2gui__ImGui__BeginChild24);

    api.StaticFunc(_SC("imgui_end_child"),         &ImGui::EndChild);
}
// ----------------------------------------------------------------------//
