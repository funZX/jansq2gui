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

#include <lib/jansq2gui_rect.h>

// ----------------------------------------------------------------------//
	
jansq2gui::CRect::CRect()
{
    m_position = ImVec2(0, 0);
    m_size = ImVec2(0, 0);
}

// ----------------------------------------------------------------------//

jansq2gui::CRect::CRect(ImVec2 pos, ImVec2 size)
{
    m_position.x = pos.x;
    m_position.y = pos.y;

    m_size.x = size.x;
    m_size.y = size.y;
}

// ----------------------------------------------------------------------//

jansq2gui::CRect::CRect(f32 x, f32 y, f32 width, f32 height)
{
    m_position.x = x;
    m_position.y = y;

    m_size.x = width;
    m_size.y = height;
}

// ----------------------------------------------------------------------//

jansq2gui::CRect::~CRect()
{

}
f32	jansq2gui::CRect::Left(void) const
{
    return m_position.x;
}

// ----------------------------------------------------------------------//

f32 jansq2gui::CRect::Right(void) const
{
    return (m_position.x + m_size.x);
}

// ----------------------------------------------------------------------//

f32 jansq2gui::CRect::Top(void) const
{
    return m_position.y;
}

// ----------------------------------------------------------------------//

f32 jansq2gui::CRect::Bottom(void) const
{
    return (m_position.y + m_size.y);
}

// ----------------------------------------------------------------------//

f32 jansq2gui::CRect::Width(void) const
{
    return m_size.x;
}

// ----------------------------------------------------------------------//

f32 jansq2gui::CRect::Height(void) const
{
    return m_size.y;
}

// ----------------------------------------------------------------------//

ImVec2 jansq2gui::CRect::TopLeft(void) const
{
    return ImVec2(Left(), Top());
}

// ----------------------------------------------------------------------//

ImVec2 jansq2gui::CRect::TopRight(void) const
{
    return ImVec2(Right(), Top());
}

// ----------------------------------------------------------------------//

ImVec2 jansq2gui::CRect::BottomLeft(void) const
{
    return ImVec2(Left(), Bottom());
}

// ----------------------------------------------------------------------//

ImVec2 jansq2gui::CRect::BottomRight(void) const
{
    return ImVec2(Right(), Bottom());
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Bound(f32 x, f32 y, f32 width, f32 height)
{
    m_position.x = x;
    m_position.y = y;
    m_size.x = width;
    m_size.y = height;
}
// ----------------------------------------------------------------------//

void jansq2gui::CRect::Bound(ImVec2 pos, ImVec2 size)
{
    m_position.x = pos.x;
    m_position.y = pos.y;
    m_size.x = size.x;
    m_size.y = size.y;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Bound(CRect r)
{
    m_position.x = r.m_position.x;
    m_position.y = r.m_position.y;
    m_size.x = r.m_size.x;
    m_size.y = r.m_size.y;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Move(ImVec2 d)
{
    m_position.x += d.x;
    m_position.y += d.y;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Move(f32 dx, f32 dy)
{
    m_position.x += dx;
    m_position.y += dy;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::MoveTo(f32 x, f32 y)
{
    m_position.x = x;
    m_position.y = y;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::MoveTo(ImVec2 pos)
{
    m_position.x = pos.x;
    m_position.y = pos.y;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Inflate(ImVec2 v)
{
    m_size.x += v.x;
    m_size.y += v.y;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Inflate(f32 dw, f32 dh)
{
    m_size.x += dw;
    m_size.y += dh;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Zoom(ImVec2 v)
{
    m_size.x += v.x;
    m_size.y += v.y;
    m_position.x -= (v.x * 0.5f);
    m_position.y -= (v.y * 0.5f);
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Zoom(f32 dw, f32 dh)
{
    m_size.x += dw;
    m_size.y += dh;
    m_position.x -= (dw * 0.5f);
    m_position.y -= (dh * 0.5f);
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Resize(ImVec2 v)
{
    m_size.x = v.x;
    m_size.y = v.y;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Resize(f32 w, f32 h)
{
    m_size.x = w;
    m_size.y = h;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Scale(ImVec2 v)
{
    m_size.x *= v.x;
    m_size.y *= v.y;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::Scale(f32 kw, f32 kh)
{
    m_size.x *= kw;
    m_size.y *= kh;
}

// ----------------------------------------------------------------------//

jansq2gui::CRect jansq2gui::CRect::Union(CRect r1, CRect r2)
{
    CRect o;

    f32 x = r1.m_position.x > r2.m_position.x ? r2.m_position.x : r1.m_position.x;
    f32 y = r1.m_position.y > r2.m_position.y ? r2.m_position.y : r1.m_position.y;
    f32 r = r1.Right()  < r2.Right()  ? r2.Right()  : r1.Right();
    f32 b = r1.Bottom() < r2.Bottom() ? r2.Bottom() : r1.Bottom();

    o.Bound(x, y, r - x, b - y);

    return o;
}

// ----------------------------------------------------------------------//

jansq2gui::CRect jansq2gui::CRect::Intersect(CRect r1, CRect r2)
{
    CRect o;

    f32 x = r1.m_position.x > r2.m_position.x ? r1.m_position.x : r2.m_position.x;
    f32 y = r1.m_position.y > r2.m_position.y ? r1.m_position.y : r2.m_position.y;
    f32 r = r1.Right()  < r2.Right()  ? r1.Right()  : r2.Right();
    f32 b = r1.Bottom() < r2.Bottom() ? r1.Bottom() : r2.Bottom();

    o.Bound(x, y, r - x, b - y);

    return o;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::SetCenter(ImVec2 center)
{
    m_position.x = center.x - (m_size.x * 0.5f);
    m_position.y = center.y - (m_size.y * 0.5f);
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::SetCenter(float x, float y)
{
    m_position.x = x - (m_size.x * 0.5f);
    m_position.y = y - (m_size.y * 0.5f);
}

// ----------------------------------------------------------------------//

ImVec2 jansq2gui::CRect::GetCenter() const
{
    ImVec2 center;

    center.x = m_position.x + (m_size.x * 0.5f);
    center.y = m_position.y + (m_size.y * 0.5f);

    return center;
}

// ----------------------------------------------------------------------//

void jansq2gui::CRect::AlignTo(CRect c, Align align)
{
    switch (align)
    {
    case Align::InRight:
        m_position.x = c.Right() - m_size.x;
        break;

    case Align::OutRight:
        m_position.x = c.Right();
        break;

    case Align::InLeft:
        m_position.x = c.m_position.x;
        break;

    case Align::OutLeft:
        m_position.x = c.m_position.x - m_size.x;
        break;

    case Align::InBottom:
        m_position.y = c.Bottom() - m_size.y;
        break;

    case Align::OutBottom:
        m_position.y = c.Bottom();
        break;

    case Align::InTop:
        m_position.y = c.Top();
        break;

    case Align::OutTop:
        m_position.y = c.Top() - Height();
        break;

    case Align::HorCenter:
        m_position.x = c.m_position.x + ((c.m_size.x - m_size.x) * 0.5f);
        break;

    case Align::VerCenter:
        m_position.y = c.m_position.y + ((c.m_size.y - m_size.y) * 0.5f);
        break;

    case Align::Center:
        m_position.x = c.m_position.x + ((c.m_size.x - m_size.x) * 0.5f);
        m_position.y = c.m_position.y + ((c.m_size.y - m_size.y) * 0.5f);
        break;
    }
}

// ----------------------------------------------------------------------//
bool jansq2gui::CRect::IsInside(f32 x, f32 y)
{
    return (x > m_position.x && x < this->Right() && y > m_position.y && y < this->Top());
}

// ----------------------------------------------------------------------//

bool jansq2gui::CRect::IsInside(ImVec2 v)
{
    return (v.x >= m_position.x && v.x < this->Right() && v.y >= m_position.y && v.y < this->Top());
}

// ----------------------------------------------------------------------//
