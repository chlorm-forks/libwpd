/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpd
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2002 Marc Maurer (uwog@uwog.net)
 * Copyright (C) 2006 Fridrich Strba (fridrich.strba@bluewin.ch)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#include "WPXTableList.h"

#include "WPXTable.h"

WPXTableList::WPXTableList() :
	m_tableList(new std::vector<WPXTable *>),
	m_refCount(new int)
{
	(*m_refCount) = 1;
}

WPXTableList::WPXTableList(const WPXTableList &tableList) :
	m_tableList(tableList.get()),
	m_refCount(tableList.getRef())
{
	if (m_refCount)
		(*m_refCount)++;
}

WPXTableList &WPXTableList::operator=(const WPXTableList &tableList)
{
	if (this != &tableList)
	{
		release();
		acquire(tableList.getRef(), tableList.get());
	}

	return (*this);
}

void WPXTableList::acquire(int *refCount, std::vector<WPXTable *> *tableList)
{
	m_refCount = refCount;
	m_tableList = tableList;
	if (m_refCount)
		(*m_refCount)++;
}

void WPXTableList::release()
{
	if (m_refCount)
	{
		if (--(*m_refCount) == 0)
		{
			for (auto &iter : (*m_tableList))
				delete iter;
			delete m_tableList;
			delete m_refCount;
		}
		m_refCount = nullptr;
		m_tableList = nullptr;
	}
}

WPXTableList::~WPXTableList()
{
	release();
}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
