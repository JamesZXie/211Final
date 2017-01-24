/*
	Defined constants for car embedded system project.
	
	Author:		Larry Henschen
	Last Modified:	Dec 1, 2016 (Sara Sood)
*/

// System parameters
const int MAX_CMD_LINE_LENGTH = 256;
const int MAX_TOKENS_ON_A_LINE = 10;

// Malfunction types.
const int NO_MALFUNCTION = 20;
const int MALFUNCTION_OVER_RANGE = 21;
const int MALFUNCTION_UNDER_RANGE = 22;
const int MALFUNCTION_STOPPED_WORKING = 23;

// System commands
const int NUMBER_OF_COMMANDS = 8;

const int HALT = 50;
const int STATUS = 51;
const int TIME_CLICK = 52;
const int CREATE_DEVICE = 61;
const int CREATE_EVENT = 62;
const int SET_DEVICE_VALUE = 71;
const int PROCESS_EVENTS = 53;
const int MALFUNCTION = 54;

const int UNDEFINED_COMMAND = 99;

// Device type constants.
const int GENERIC = 50;
const int DIGITAL_SENSOR = 51;
const int ANALOG_SENSOR = 52;
const int DIGITAL_CONTROLLER = 53;
const int ANALOG_CONTROLLER = 54;

// Device operating constants.
const int ON = 200;
const int OFF = 250;

const int MAX_DEVICES = 20;
