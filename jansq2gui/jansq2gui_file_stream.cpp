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

#include <jansq2gui_file_stream.h>

// ----------------------------------------------------------------------//

jansq2gui::CFileStream::CFileStream( const std::string& filename )
{
	m_cursor 	= 0;
	m_size 		= 0;

	m_memory 	= nullptr;
	m_current 	= nullptr;

	m_filename 	= filename;
}

// ----------------------------------------------------------------------//

jansq2gui::CFileStream::~CFileStream()
{
	Close();
}

// ----------------------------------------------------------------------//

bool jansq2gui::CFileStream::Open()
{
	FILE *f = fopen( m_filename.c_str(), "rb" );

	if( f )
	{
		fseek( f, 0, SEEK_END );
		m_size = ftell( f );
		fseek( f, 0, SEEK_SET );

		s32 size	= m_size + 1;

		m_memory 	= jansq2gui_new s8[ size ];
		m_current 	= m_memory;

		m_memory[ size - 1 ] = 0;

		fread( &m_memory[ 0 ], m_size, 1, f );
		fclose( f );

		return true;
	}

	return false;
}

// ----------------------------------------------------------------------//

void jansq2gui::CFileStream::Close( void )
{
	jansq2gui_delete_array( m_memory );
}

// ----------------------------------------------------------------------//

void* jansq2gui::CFileStream::Drop()
{
	void *buf	= m_memory;

	m_cursor 	= 0;
	m_size 		= 0;

	m_memory 	= nullptr;
	m_current 	= nullptr;

	return buf;
}

// ----------------------------------------------------------------------//

void* jansq2gui::CFileStream::Read( u32 size )
{
	void *ptr = nullptr;

	if( m_cursor + size > m_size ) {
		size = m_size - m_cursor;
	}

	ptr = &m_memory[ m_cursor ];

	m_cursor += size;

	return ptr;
}

// ----------------------------------------------------------------------//

bool jansq2gui::CFileStream::Eof( void )
{
	return m_cursor == m_size;
}

// ----------------------------------------------------------------------//

void jansq2gui::CFileStream::Seek( SeekFrom seekFrom, u32 offset)
{
	switch(seekFrom)
	{
		case SeekFrom::Start:
		{
			m_cursor = offset;
			break;
		}
		case SeekFrom::Current:
		{
			m_cursor += offset;
			break;
		}
		case SeekFrom::End:
		{
			m_cursor -= offset;
			break;
		}
	}
}

// ----------------------------------------------------------------------//

