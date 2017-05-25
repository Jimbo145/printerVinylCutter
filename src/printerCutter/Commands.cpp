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

#include "printerCutter.h"


void Commands::commandLoop() {
    while(true) {
        //if(!Printer::isBlockingReceive()) { // TODO: if the move queue is full pause here
            GCode::readFromSerial();
            GCode *code = GCode::peekCurrentCommand();
            if(code) {
                Commands::executeGCode(code);
                code->popCurrentCommand();
            }
        //}
        //Printer::defaultLoopActions(); //inactivity shutdown
    }
}

void Commands::checkForPeriodicalActions(bool allowNewMoves) {
   
}

/** \brief Waits until movement cache is empty.

Some commands expect no movement, before they can execute. This function
waits, until the steppers are stopped. In the meanwhile it buffers incoming
commands and manages temperatures.
*/
void Commands::waitUntilEndOfAllMoves() {
    /*while(PrintLine::hasLines()) {
        GCode::readFromSerial();
        checkForPeriodicalActions(false);
        UI_MEDIUM;
    }*/
}

void Commands::waitUntilEndOfAllBuffers() {
    /*GCode *code = NULL;

    while(PrintLine::hasLines() || (code != NULL)) {
        GCode::readFromSerial();
        code = GCode::peekCurrentCommand();
        UI_MEDIUM; // do check encoder
        if(code) {
            Commands::executeGCode(code);
            code->popCurrentCommand();
        }
        Commands::checkForPeriodicalActions(false); // only called from memory
        UI_MEDIUM;
    }*/
}

void Commands::printCurrentPosition() {
    
}


void microstepMode(uint8_t driver, uint8_t stepping_mode) {
    
}

void microstepReadings() {
}

void microstepInit() {

}


/**
\brief Execute the G command stored in com.
*/
void Commands::processGCode(GCode *com) {
    uint32_t codenum; //throw away variable
    switch(com->G) {
        case 0: // G0 -> G1
        case 1: // G1 MOVE
            if(com->hasZ()){
              moveZ(com->Z);
              if((com->Z)>5){
                
                //moveZ(-10);
              }else{
                
                //moveZ(10);
              }
              
            }
            if(com->hasX() && com->hasY()){
              moveTo(com->X, com->Y);
            }else if(com->hasX()){
              moveTo(com->X, UNUSED);
            }else if (com->hasY()){
              moveTo(UNUSED, com->Y);
            }
            while(isMoving());
            break;
        case 2: // CW Arc
         break;
        case 3: // CCW Arc MOTION_MODE_CW_ARC: case MOTION_MODE_CCW_ARC:
         break;

        case 4: // G4 dwell
            /*Commands::waitUntilEndOfAllMoves();
            codenum = 0;
            if(com->hasP()) codenum = com->P; // milliseconds to wait
            if(com->hasS()) codenum = com->S * 1000; // seconds to wait
            codenum += HAL::timeInMilliseconds();  // keep track of when we started waiting
            while((uint32_t)(codenum-HAL::timeInMilliseconds())  < 2000000000 ) {
                GCode::readFromSerial();
                Commands::checkForPeriodicalActions(true);
            }*/
            break;

        case 20: // G20 Units to inches
            break;
        case 21: // G21 Units to mm
            break;
        case 28: { //G28 Home all Axis one at a time
              if(com->hasY()){
                feedY();
              }
              if(com->hasZ()){
                //moveZ(0);
              }
              homeX();
            }
            break;
        case 29:  // G29 3 points, build average or distortion compensation

            break;
        case 30: // G30 single probe set Z0
                
            break;
        case 31:  // G31 display hall sensor output
            
            break;
        case 90: // G90 Set to Absolute Positioning
            setAbsolutePositioning(true);
            break;
        case 91: // G91 Set to Relative Positioning
            setAbsolutePositioning(false);
            break;
        case 92: { // G92 Set Position
                
            }
            break;

        default:
        break;
    }
    //previousMillisCmd = millis(); //printer inactivity
}
/**
\brief Execute the G command stored in com.
*/
void Commands::processMCode(GCode *com) {
    switch( com->M ) {
        case 3: // Spindle/laser on
            break;
        case 4: // Spindle CCW
            break;
        case 5: // Spindle/laser off
            break;


        case 42: //M42 -Change pin status via gcode
            
            break;
        case 80: // M80 - ATX Power On

            break;
        case 81: // M81 - ATX Power Off

            break;
        case 82: // M82 unsSet extruder to relative mode
            break;
        case 83: // M83 Set extruder to relative mode
            break;
        case 84: // M84
            break;
        case 85: // M85 Set inactivity shutdown timer
            
            break;
        case 92: // M92 Set axis_steps_per_unit 
            
            break;
        case 99: { // M99 S<time> wait
                
            }
            break;

        case 104: // M104 temperature

            break;
        case 140: // M140 set bed temp
            break;
        case 105: // M105  get temperature. Always returns the current temperature, doesn't wait until move stopped
            
            break;
        case 190: { // M190 - Wait bed for heater to reach target.
          }
            break;


        case 111: // M111 enable/disable run time debug flags

            break;
        case 115: // M115 Get Firmware Version and Capabilities
            break;
        case 114: // M114 Get Current Position
            break;
        case 117: // M117 message to lcd
           
            break;
        case 119: // M119 Get Endstop Status
            Commands::waitUntilEndOfAllMoves();
            
            break;


        case 200: { // M200 T<extruder> D<diameter> set filament diameter
                
            }
            break;

        case 203: // M203 Temperature monitor
            
            break;
        case 204: { // M204 Set PID parameter
            }
            break;
        case 205: // M205 Show EEPROM settings
            //EEPROM::writeSettings();
            break;
        case 206: // M206 T[type] P[pos] [Sint(long] [Xfloat]  Set eeprom value
            //EEPROM::update(com);
            break;
        case 207: // M207 X<XY jerk> Z<Z Jerk>
            break;
        case 209: // M209 S<0/1> Enable/disable autoretraction
            
            break;
        case 220: // M220 S<Feedrate multiplier in percent>
            //changeFeedrateMultiply(com->getS(100));
            break;
        case 221: // M221 S<Extrusion flow multiplier in percent>
            
            break;
        case 226: // M226 P<pin> S<state 0/1> - Wait for pin getting state S
            
            break;
        case 281: // Trigger watchdog

            break;

        case 302: // M302 S<0 or 1> - allow cold extrusion. Without S parameter it will allow. S1 will disallow.
            
            break;
        case 303: { // M303 Run PID tuning

            }
            break;
        case 350: { // M350 Set microstepping mode. Warning: Steps per unit remains unchanged. S code sets stepping mode for all drivers.
               
            }
            break;
        case 355: // M355 S<0/1> - Turn case light on/off, no S = report status
            if(com->hasS()) {
                //Printer::setCaseLight(com->S);
            } else
               // Printer::reportCaseLightStatus();
            break;
        case 360: // M360 - show configuration
            
            break;
        case 400: // M400 Finish all moves
            Commands::waitUntilEndOfAllMoves();
            break;
        case 401: // M401 Memory position
            break;
        case 402: // M402 Go to stored position
            break;
        case 450:
            //Printer::reportPrinterMode();
            break;
        case 451:
            //Printer::mode = PRINTER_MODE_FFF;
            //Printer::reportPrinterMode();
            break;
        case 452:
            //Printer::reportPrinterMode();
            break;
        case 453:
            //Printer::reportPrinterMode();
            break;

        case 500: { // M500
                //EEPROM::storeDataIntoEEPROM(false);
                //Com::printInfoFLN(Com::tConfigStoredEEPROM);
            }
            break;
        case 501: { // M501
                //EEPROM::readDataFromEEPROM(true);
                //Extruder::selectExtruderById(Extruder::current->id);
                //Com::printInfoFLN(Com::tConfigLoadedEEPROM);
            }
            break;
        case 502: // M502
            //EEPROM::restoreEEPROMSettingsFromConfiguration();
            break;
        case 601:
            break;
        case 602:
            Commands::waitUntilEndOfAllMoves();
            break;
        case 603: //set interrupt event jam detected
            break;
        case 907: { // M907 Set digital trimpot/DAC motor current using axis codes.

            }
            break;
        case 908: { // M908 Control digital trimpot directly.

            }
            break;
        case 909: { // M909 Read digital trimpot settings.

            }
            break;
        case 910: // M910 - Commit digipot/DAC value to external EEPROM
            break;
    case 999: // Stop fatal error take down
      
      break;
        default:
        break;
    }
}

/**
\brief Execute the command stored in com.
*/
void Commands::executeGCode(GCode *com) {
    if(com->hasG()) processGCode(com);
    else if(com->hasM()) processMCode(com);
    else if(com->hasT()) {    // Process T code
        //com->printCommand(); // for testing if this the source of extruder switches
        Commands::waitUntilEndOfAllMoves();
        
    } else {
        Serial.println("UNK CMD");
    }
}

void Commands::emergencyStop() {

}


