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

#include <jansq2gui_mem_stream.h>

// ----------------------------------------------------------------------//

jansq2gui::CMemStream::CMemStream( void *mem, u32 maxsize )
{
	m_memory		= (s8*) mem;
	m_maxsize		= maxsize;
	m_cursor		= 0;
	m_isMemOwn		= false;
}

// ----------------------------------------------------------------------//

jansq2gui::CMemStream::CMemStream( u32 maxsize )
{
	m_memory		= jansq2gui_new s8[ maxsize ];
	m_maxsize		= maxsize;
	m_cursor		= 0;
	m_isMemOwn		= true;
}

// ----------------------------------------------------------------------//

jansq2gui::CMemStream::~CMemStream()
{
	if( m_isMemOwn ) {
		jansq2gui_delete_array( m_memory );
	}
}

// ----------------------------------------------------------------------//

char jansq2gui::CMemStream::ReadS8()
{
	jansq2gui_assert( CanRead( sizeof( s8 ) ) );

	s8 c = *( m_memory + m_cursor );
	m_cursor++;

	return c;
}

// ----------------------------------------------------------------------//

jansq2gui::u8 jansq2gui::CMemStream::ReadU8()
{
	jansq2gui_assert( CanRead( sizeof( u8 ) ) );

	u8 c = (u8)( *( m_memory + m_cursor ) );
	m_cursor++;

	return c;
}

// ----------------------------------------------------------------------//

jansq2gui::s16 jansq2gui::CMemStream::ReadS16()
{
	jansq2gui_assert( CanRead( sizeof( s16 ) ) );

	s16 h = 0;

	h  = ( m_memory[ m_cursor++ ] & 0xFF) << 8;
    h |= ( m_memory[ m_cursor++ ] & 0xFF);

    return h;
}

// ----------------------------------------------------------------------//

jansq2gui::u16 jansq2gui::CMemStream::ReadU16()
{
	jansq2gui_assert( CanRead( sizeof( u16 ) ) );

	u16 h;

	h  = ( m_memory[ m_cursor++ ] & 0xFF) << 8;
    h |= ( m_memory[ m_cursor++ ] & 0xFF);

    return h;
}

// ----------------------------------------------------------------------//

jansq2gui::s32 jansq2gui::CMemStream::ReadS32()
{
	jansq2gui_assert( CanRead( sizeof( s32 ) ) );

	s32 i = 0;

	i  = ( m_memory[ m_cursor++ ] & 0xFF ) << 24;
    i |= ( m_memory[ m_cursor++ ] & 0xFF ) << 16;
    i |= ( m_memory[ m_cursor++ ] & 0xFF ) << 8;
    i |= ( m_memory[ m_cursor++ ] & 0xFF );

    return i;
}

// ----------------------------------------------------------------------//

jansq2gui::u32 jansq2gui::CMemStream::ReadU32()
{
	jansq2gui_assert( CanRead( sizeof( u32 ) ) );

	u32 i = 0;

	i  = ( m_memory[ m_cursor++ ] & 0xFF ) << 24;
    i |= ( m_memory[ m_cursor++ ] & 0xFF ) << 16;
    i |= ( m_memory[ m_cursor++ ] & 0xFF ) << 8;
    i |= ( m_memory[ m_cursor++ ] & 0xFF );

    return i;
}

// ----------------------------------------------------------------------//

jansq2gui::f32 jansq2gui::CMemStream::ReadF32()
{
	jansq2gui_assert( CanRead( sizeof( f32 ) ) );

	f32 f  = 0.0f;
	s8 *p = ( s8 * )&f;

	*( p + 0 )	= m_memory[ m_cursor++ ];
	*( p + 1 )	= m_memory[ m_cursor++ ];
	*( p + 2 )	= m_memory[ m_cursor++ ];
	*( p + 3 )	= m_memory[ m_cursor++ ];

	return f;
}

// ----------------------------------------------------------------------//

std::string jansq2gui::CMemStream::ReadString()
{
	std::string s( &m_memory[ m_cursor ] );

	while  ( m_memory[ m_cursor++ ] );

	return s;
}

// ----------------------------------------------------------------------//

void* jansq2gui::CMemStream::Read( u32 nBytes )
{
	jansq2gui_assert( CanRead( nBytes * sizeof( s8 ) ) );

	s8 *c = nullptr;

	if( nBytes >= 0 )
	{
		c = &m_memory[ m_cursor ];
		m_cursor += nBytes * sizeof( s8 );
	}

	return c;
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::WriteS8( s8 c )
{
	jansq2gui_assert( CanWrite( sizeof( s8 ) ) );

	m_memory[ m_cursor++ ] = c;
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::WriteU8( u8 c )
{
	jansq2gui_assert( CanWrite( sizeof( u8 ) ) );

	m_memory[ m_cursor++ ] = (s8) c;
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::WriteS16( s16 h )
{
	jansq2gui_assert( CanWrite( sizeof( s16 ) ) );

	m_memory[ m_cursor++ ] = ( s8 )( ( h & 0x0000FF00 ) >> 8 );
	m_memory[ m_cursor++ ] = ( s8 )( ( h & 0x000000FF ) );
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::WriteU16( u16 h )
{
	jansq2gui_assert( CanWrite( sizeof( u16 ) ) );

	m_memory[ m_cursor++ ] = ( s8 )( ( h & 0x0000FF00 ) >> 8 );
	m_memory[ m_cursor++ ] = ( s8 )( ( h & 0x000000FF ) );
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::WriteS32( s32 i )
{
	jansq2gui_assert( CanWrite( sizeof( s32 ) ) );

	m_memory[ m_cursor++ ] = ( s8 )( ( i & 0xFF000000 ) >> 24 );
	m_memory[ m_cursor++ ] = ( s8 )( ( i & 0x00FF0000 ) >> 16 );
	m_memory[ m_cursor++ ] = ( s8 )( ( i & 0x0000FF00 ) >> 8 );
	m_memory[ m_cursor++ ] = ( s8 )( ( i & 0x000000FF ) );
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::WriteU32( u32 i )
{
	jansq2gui_assert( CanWrite( sizeof( u32 ) ) );

	m_memory[ m_cursor++ ] = ( s8 )( ( i & 0xFF000000 ) >> 24 );
	m_memory[ m_cursor++ ] = ( s8 )( ( i & 0x00FF0000 ) >> 16 );
	m_memory[ m_cursor++ ] = ( s8 )( ( i & 0x0000FF00 ) >> 8 );
	m_memory[ m_cursor++ ] = ( s8 )( ( i & 0x000000FF ) );
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::WriteF32( f32 f )
{
	jansq2gui_assert( CanWrite( sizeof( f32 ) ) );

	f32 data = f;
	s8 *p = ( s8* ) &data;

	m_memory[ m_cursor++ ] = *( p + 0 );
	m_memory[ m_cursor++ ] = *( p + 1 );
	m_memory[ m_cursor++ ] = *( p + 2 );
	m_memory[ m_cursor++ ] = *( p + 3 );
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::WriteString( const std::string& s )
{
	u32 len = s.length() + 1;

	jansq2gui_memcpy( &m_memory[ m_cursor ], s.c_str(), len );

	m_cursor += len;
}

// ----------------------------------------------------------------------//

void jansq2gui::CMemStream::Write( void *p, u32 nBytes )
{
	jansq2gui_assert( CanWrite( nBytes * sizeof( s8 ) ) );

	if( nBytes > 0 )
	{
		jansq2gui_memcpy( &m_memory[ m_cursor ], p, nBytes * sizeof( s8 ) );
		m_cursor += nBytes * sizeof( s8 );
	}
}

// ----------------------------------------------------------------------//

bool jansq2gui::CMemStream::CanWrite( u32 nBytes )
{
	return ( m_cursor + nBytes <= m_maxsize );
}

// ----------------------------------------------------------------------//

bool jansq2gui::CMemStream::CanRead( u32 nBytes )
{
	return ( m_cursor + nBytes <= m_maxsize );
}

// ----------------------------------------------------------------------//

void* jansq2gui::CMemStream::Drop()
{
	void *buf		= m_memory;

	m_memory		= nullptr;
	m_maxsize		= 0;
	m_cursor		= 0;
	m_isMemOwn		= false;

	return buf;
}

// ----------------------------------------------------------------------//
