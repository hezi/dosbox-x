/* Copyright (C) 2003, 2004, 2005, 2006, 2008, 2009 Dean Beeler, Jerome Fisher
 * Copyright (C) 2011, 2012, 2013 Dean Beeler, Jerome Fisher, Sergey V. Mikayev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MT32EMU_TVF_H
#define MT32EMU_TVF_H

namespace MT32Emu {

class TVF {
private:
	const Partial * const partial;
	LA32Ramp *cutoffModifierRamp;
	const TimbreParam::PartialParam *partialParam;

	Bit8u baseCutoff = 0;
	int keyTimeSubtraction = 0;
	unsigned int levelMult = 0;

	Bit8u target = 0;
	unsigned int phase = 0;

	void startRamp(Bit8u newTarget, Bit8u newIncrement, int newPhase);
	void nextPhase();

public:
	TVF(const Partial *usePartial, LA32Ramp *useCutoffModifierRamp);
	void reset(const TimbreParam::PartialParam *newPartialParam, Bit32u basePitch);
	// Returns the base cutoff (without envelope modification).
	// The base cutoff is calculated when reset() is called and remains static
	// for the lifetime of the partial.
	// Barring bugs, the number returned is confirmed accurate
	// (based on specs from Mok).
	Bit8u getBaseCutoff() const;
	void handleInterrupt();
	void startDecay();

	void saveState( std::ostream &stream );
	void loadState( std::istream &stream );

	// savestate debugging
	void rawVerifyState( char *name, Synth *synth );
};

}

#endif
