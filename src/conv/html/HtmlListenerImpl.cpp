 /* libwpd2
 * Copyright (C) 2002 William Lachance (wlach@interlog.com)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
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

#include <stdio.h>
#include "HtmlListenerImpl.h"

HtmlListenerImpl::HtmlListenerImpl() :
	m_isParagraphOpened(FALSE),
	m_isSpanOpened(FALSE)
{
}

HtmlListenerImpl::~HtmlListenerImpl()
{
}


void HtmlListenerImpl::startDocument()
{
    printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\" \"http://www.w3.org/TR/REC-html40/loose.dtd\">\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\" >\n");
    printf("</head>\n");
    printf("<body>\n");
}

void HtmlListenerImpl::endDocument()
{
	if (m_isSpanOpened)
		printf("</span>");
	if (m_isParagraphOpened) 
		printf("</p>\n");

	printf("\n");
	printf("</body>\n");
	printf("</html>\n");
}

void HtmlListenerImpl::openParagraph(guint32 textAttributeBits)
{
	if (m_isParagraphOpened) {
		if (m_isSpanOpened)
			printf("</span>");
		printf("</p>\n");
	}
	else
		m_isParagraphOpened = TRUE;

	printf("<p "); _appendTextAttributes(textAttributeBits); printf(">");
	m_isSpanOpened = FALSE;
}

void HtmlListenerImpl::openSpan(guint32 textAttributeBits)
{
	if (m_isSpanOpened)
		printf("</span>");

	printf("<span "); _appendTextAttributes(textAttributeBits); printf(">");
	m_isSpanOpened = TRUE;
}

void HtmlListenerImpl::insertText(const guint16 *textArray, const guint len)
{
	for (guint i=0; i<len; i++) {
		printf("%c", textArray[i]);
	}
}

void HtmlListenerImpl::_appendTextAttributes(guint32 textAttributeBits)
{
	printf("style=\"");
	if (textAttributeBits & WPX_BOLD_BIT)
		printf("font-weight: bold;");
	if (textAttributeBits & WPX_ITALICS_BIT)
		printf("font-style: italic;");
	printf("\"");
}
