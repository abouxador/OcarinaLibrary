/**
 * Copyright (c) 2013 OpenPipe Labs. <openpipelabs@gmail.com>. All rights reserved.
 *
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OCARINA_H
#define OCARINA_H

#include <inttypes.h> 

#define CAPACITANCE_THRESHOLD 3
#define PRESSURE_THRESHOLD 5


class OcarinaClass
{
public:
	OcarinaClass();
	int fingers();
	int pressure();
	void setMinPressure(int pressure);

private:
	int pressure_min;
	static const char ocarina_pins[];
	static uint8_t readCapacitivePin(int pinToMeasure);
};

extern OcarinaClass Ocarina;

 #endif
