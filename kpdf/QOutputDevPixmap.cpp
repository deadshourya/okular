/***************************************************************************
 *   Copyright (C) 2003-2004 by Christophe Devriese                        *
 *                         <Christophe.Devriese@student.kuleuven.ac.be>    *
 *   Copyright (C) 2003 by Helio Chissini de Castro                        *
 *                           <helio@conectiva.com.br>                      *
 *   Copyright (C) 2003 by Dirk Mueller <mueller@kde.org>                  *
 *   Copyright (C) 2003 by Scott Wheeler <wheeler@kde.org>                 *
 *   Copyright (C) 2003 by Ingo Kl�cker <kloecker@kde.org>                 *
 *   Copyright (C) 2003 by Andy Goossens <andygoossens@telenet.be>         *
 *   Copyright (C) 2004 by Dominique Devriese <devriese@kde.org>           *
 *   Copyright (C) 2004 by Albert Astals Cid <tsdgeos@terra.es>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifdef __GNUC__
#pragma implementation
#endif

#include <GfxState.h>

#include <qpixmap.h>
#include <qimage.h>

#include <kdebug.h>

#include "SplashBitmap.h"
#include "SplashTypes.h"

#include "QOutputDevPixmap.h"

//------------------------------------------------------------------------
// QOutputDevPixmap
//------------------------------------------------------------------------

QOutputDevPixmap::QOutputDevPixmap(SplashColor paperColor) : QOutputDev(paperColor), m_pixmap(0)
{
}

QOutputDevPixmap::~QOutputDevPixmap( )
{
	delete m_pixmap;
}

void QOutputDevPixmap::startPage ( int pageNum, GfxState *state )
{
	QOutputDev::startPage(pageNum, state);
	delete m_pixmap;

	m_pixmap = new QPixmap ( qRound ( state->getPageWidth ( )), qRound ( state->getPageHeight ( )));

	//printf ( "NEW PIXMAP (%ld x %ld)\n", qRound ( state-> getPageWidth ( )),  qRound ( state-> getPageHeight ( )));

	m_pixmap-> fill ( Qt::white ); // clear pixmap
}

void QOutputDevPixmap::endPage ( )
{
	SplashColorPtr dataPtr;
	int bh, bw;
	
	QOutputDev::endPage();
	bh = getBitmap()->getHeight();
	bw = getBitmap()->getWidth();
	dataPtr = getBitmap()->getDataPtr();
	m_pixmap->convertFromImage(QImage((uchar*)dataPtr.rgb8, bw, bh, 32, 0, 0, QImage::IgnoreEndian));
}
