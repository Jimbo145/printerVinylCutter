/*
Written by Jimbo145

This is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This software is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

See <http://www.gnu.org/licenses/>.

This firmware an adaptation of the repetier-firmware(https://github.com/repetier/Repetier-Firmware) 
which is a nearly complete rewrite of the sprinter firmware
by kliment (https://github.com/kliment/Sprinter)
which based on Tonokip RepRap firmware rewrite based off of Hydra-mmm firmware.
*/

#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

class Commands
{
public:
    static void commandLoop();
    static void checkForPeriodicalActions(bool allowNewMoves);
    static void processArc(GCode *com);
    static void processGCode(GCode *com);
    static void processMCode(GCode *com);
    static void executeGCode(GCode *com);
    static void waitUntilEndOfAllMoves();
    static void waitUntilEndOfAllBuffers();
    static void printCurrentPosition();
    static void printTemperatures(bool showRaw = false);
    static void changeFeedrateMultiply(int factorInPercent);
    static void changeFlowrateMultiply(int factorInPercent);
    static void reportPrinterUsage();
    static void emergencyStop();
    static void checkFreeMemory();
};

#endif // COMMANDS_H_INCLUDED
