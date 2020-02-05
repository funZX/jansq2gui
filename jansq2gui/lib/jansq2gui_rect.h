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

#ifndef __JANSQ2GUI_RECT_H
#define __JANSQ2GUI_RECT_H

#include <jansq2gui.h>

namespace jansq2gui
{
// ----------------------------------------------------------------------//

// ----------------------------------------------------------------------//

class CRect
{
public:
// ----------------------------------------------------------------------//
    CRect();
    CRect(ImVec2 pos, ImVec2 size);
    CRect(float x, float y, float width, float height);
    ~CRect();
// ----------------------------------------------------------------------//
    enum Align
    {
        InLeft,
        InRight,
        InTop,
        InBottom,

        OutLeft,
        OutRight,
        OutTop,
        OutBottom,

        HorCenter,
        VerCenter,
        Center
    };
// ----------------------------------------------------------------------//


    float						Left(void) const;
    float						Right(void) const;
    float						Top(void) const;
    float						Bottom(void) const;
    float						Width(void) const;
    float						Height(void) const;
    ImVec2                      TopLeft(void) const;
    ImVec2                      TopRight(void) const;
    ImVec2                      BottomLeft(void) const;
    ImVec2                      BottomRight(void) const;

    void						Move(ImVec2 d);
    void						Move(float x, float y);
    void						MoveTo(ImVec2 pos);
    void						MoveTo(float x, float y);

    void						Inflate(ImVec2 v);
    void						Inflate(float dw, float dh);
    void						Zoom(ImVec2 v);
    void						Zoom(float dw, float dh);
    void						Resize(ImVec2 v);
    void						Resize(float dw, float dh);
    void						Scale(ImVec2 v);
    void						Scale(float dw, float dh);

    void						SetCenter(ImVec2 center);
    void						SetCenter(float x, float y);
    ImVec2						GetCenter() const;

    void						AlignTo(CRect r, Align align);

    bool						IsInside(ImVec2 pos);
    bool						IsInside(float x, float y);

    void						Bound(float, float, float, float);
    void						Bound(ImVec2 pos, ImVec2 size);
    void						Bound(CRect);

    static CRect				Union(CRect, CRect);
    static CRect				Intersect(CRect, CRect);

// ----------------------------------------------------------------------//

protected:
    // ------------------------------------------------------------------//
    ImVec2						m_position;
    ImVec2						m_size;
    // ------------------------------------------------------------------//
};

// ----------------------------------------------------------------------//
}; // namespace jansq2gui

#endif // __JANSQ2GUI_SCRIPT_H
