/*
 *  Copyright (c) 2005 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <qrect.h>

#include <kdebug.h>

#include "kis_brush.h"
#include "kis_global.h"
#include "kis_paint_device.h"
#include "kis_painter.h"
#include "kis_types.h"
#include "kis_paintop.h"

#include "kis_wetop.h"

KisPaintOp * KisWetOpFactory::createOp(KisPainter * painter)
{
	KisPaintOp * op = new KisWetOp(painter);
	return op;
}

KisWetOp::KisWetOp(KisPainter * painter)
	: super(painter)
{
}

KisWetOp::~KisWetOp()
{
}

void KisWetOp::paintAt(const KisPoint &pos,
			 const double pressure,
			 const double /*xTilt*/,
			 const double /*yTilt*/)
{
	if (!m_painter -> device()) return;

	KisBrush *brush = m_painter -> brush();
	KisPaintDeviceSP device = m_painter -> device();

	KisPoint hotSpot = brush -> hotSpot(pressure);
	KisPoint pt = pos - hotSpot;

	// Split the coordinates into integer plus fractional parts. The integer
	// is where the dab will be positioned and the fractional part determines
	// the sub-pixel positioning.
	Q_INT32 x;
	double xFraction;
	Q_INT32 y;
	double yFraction;

	splitCoordinate(pt.x(), &x, &xFraction);
	splitCoordinate(pt.y(), &y, &yFraction);

}
