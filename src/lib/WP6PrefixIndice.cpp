/* libwpd2
 * Copyright (C) 2002 William Lachance (wlach@interlog.com)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by 
 * Corel Corporation or Corel Corporation Limited."
 */

#include "WP6PrefixIndice.h"
// #include "WP6UnsupportedPrefixPacket.h"
#include "WP6FileStructure.h" 
#include "libwpd.h"
#include "libwpd_internal.h"

WP6PrefixIndice::WP6PrefixIndice(GsfInput * input, int id)
	: m_id(id),
	  m_type(0),
	  m_flags(0),
	  m_useCount(0),
	  m_hideCount(0),
	  m_dataSize(0),
	  m_dataOffset(0),
	  m_hasChildren(FALSE)
{
	_read(input);
}

void WP6PrefixIndice::_read(GsfInput *input)
{
	m_flags = *(const guint8 *)gsf_input_read(input, sizeof(guint8), NULL);
	m_type = *(const guint8 *)gsf_input_read(input, sizeof(guint8), NULL);

	m_useCount = *(const guint16 *)gsf_input_read(input, sizeof(guint16), NULL);
	m_hideCount = *(const guint16 *)gsf_input_read(input, sizeof(guint16), NULL);
	m_dataSize = *(const guint32 *)gsf_input_read(input, sizeof(guint32), NULL);
	m_dataOffset = *(const guint32 *)gsf_input_read(input, sizeof(guint32), NULL);

	WPD_DEBUG_MSG(("Prefix Packet (type: %i, data size: %i, data offset: %i)\n", m_type, m_dataSize, m_dataOffset));
	
	if (m_flags & WP6_INDEX_HEADER_ELEMENT_CHILD_PACKET_BIT)
		m_hasChildren = true;

}