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

// WPXTable: an intermediate representation of a table, designed to be created
// "ahead of time". unlike wordperfect's table definition messages, this representation
// is _consistent_: we can always count on the messages being sent using this representation
// (once it is created and finalized) to be reliable (assuming no bugs in this code!) :-)
//
// example situation where this might be useful: WordPerfect allows two cells,
// side by side, one with border, one without-- creating a false ambiguity (none
// actually exists: if one cell does not have a border, the other doesn't either)

#ifndef _WPXTABLE_H
#define _WPXTABLE_H

#include <vector>

struct WPXTableCell
{
	WPXTableCell(unsigned char colSpan, unsigned char rowSpan, unsigned char borderBits);
	unsigned char m_colSpan;
	unsigned char m_rowSpan;
	unsigned char m_borderBits;
};

class WPXTable
{
public:
	WPXTable() : m_tableRows() {}
	~WPXTable();
	void insertRow();
	void insertCell(unsigned char colSpan, unsigned char rowSpan, unsigned char borderBits);
	const WPXTableCell  *getCell(std::size_t i, std::size_t j)
	{
		return &(m_tableRows[i])[j];
	}
	void makeBordersConsistent();

	unsigned getRowCount() const
	{
		return m_tableRows.size();
	}
	unsigned getColumnCount(unsigned row) const
	{
		return m_tableRows[row].size();
	}
	bool isEmpty() const
	{
		return m_tableRows.empty();
	}

private:
	static void _makeCellBordersConsistent(WPXTableCell &cell, std::vector<WPXTableCell *> &adjacentCells,
	                                       int adjacencyBitCell, int adjacencyBitBoundCells);
	std::vector<WPXTableCell *>  _getCellsBottomAdjacent(int i, int j);
	std::vector<WPXTableCell *>  _getCellsRightAdjacent(int i, int j);

private:
	std::vector< std::vector<WPXTableCell> > m_tableRows;
};

#endif /* _WPXTABLE_H */
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
