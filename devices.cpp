/*
	Classes malfunctionRecord and device for car embedded system project.
	
	Author:		Larry Henschen
	Last Modified:	Dec 1, 2016 (Sara Sood)
*/

#include "definitions.h"
#include "devices.h"
#include "events.h"
#include <iostream>
#include <cmath>

using namespace std;

extern int globalTime;
extern LIST* eventList;
extern int checkEngine;

// malfunctionRecord functions.
malfunctionRecord::malfunctionRecord() {
	count = 0;
	lastMalfunction = NO_MALFUNCTION;
	lastMalfunctionTime = 0;
}

void malfunctionRecord::display() const {
	
	if(count==0) cout << "Device has never malfunctioned.\n";
	else {
		cout << "Malfunction record:\n";
		cout << count << " malfunctions.\n";
		cout << "Most recent: " << lastMalfunctionTime << "\n";
		cout << "Malfunction type: ";
		switch(lastMalfunction) {
			case MALFUNCTION_OVER_RANGE:
            {
                cout << "reading over limit.\n";
                break;
            }
			case MALFUNCTION_UNDER_RANGE:
            {
                cout << "reading under limit.\n";
                break;
            }
			case MALFUNCTION_STOPPED_WORKING:
            {
                cout << "device stopped working.\n";
                break;
            }
			default:
            {
                cout << "unspecified error.\n";
                break;
            }
		}
	}
}


void malfunctionRecord::malfunction(int mtype, int time) {
	count += 1;
	lastMalfunction     = mtype;
	lastMalfunctionTime = time;
	
	if (globalTime > 0)
	{
		checkEngine = 1;
	}
}


int malfunctionRecord::getRecord(int& m, int& t) {
	m = lastMalfunction;
	t = lastMalfunctionTime;
	return count;
}

// device class functions

device::device(string n, int i) {
	// NOTE: The default constructor for mr should be called automatically.
    name = n;
	id = i;
    value = 0;
    type = GENERIC;
}

string device::giveName() {
	string tempName = name;
	return tempName;
	
}

void device::display() const {
	
	cout <<  "Device: " << name << ". ID: " << id << ". Value: " << value << "\n";
	mr.display();
}

void device::recordMalfunction(int m, int t) {
	mr.malfunction(m,t);
}

int device::getMalfunctionRecord(int& m, int& t) {
	return mr.getRecord(m,t);
}

int device::amIThisDevice(string n) {
	if(name == n)
        return 1;
	else
        return 0;
}


int device::myType() {
    return type;
}

int device::getValue() {
    return value;
}

void device::createEvent(int tm) {
	EVENT* newEvent = new EVENT(name, value, tm);
	eventList->insertEvent(newEvent);
}

// digitalSensorDevice members
digitalSensorDevice::digitalSensorDevice(string n, int i, int v) : device(n, i) {
    value = v;
    type = DIGITAL_SENSOR;
}

void digitalSensorDevice::display() const {
    device::display();
    cout << "This is a digital sensor device." << endl;
    cout << "The device is currently ";
    if(value==ON) cout << "ON." << endl;
    else          cout << "OFF." << endl;
}

void digitalSensorDevice::setValue(int v) {
    value = v;
	if (globalTime > 0)
	{
		// *************** What's the time that I enter into createEvent? globalTime? **************//
		createEvent(globalTime);
	}
}

analogSensorDevice::analogSensorDevice(string n, int i, int v, int bor) : device(n, i) {
    type = ANALOG_SENSOR;
    bitsOfResolution = bor;
    if (bitsOfResolution < 1 || bitsOfResolution > 16)
        bitsOfResolution = 8;
    analogSensorDevice::setValue(v);
}

void analogSensorDevice::display() const {
    device::display();
    cout << "This is an analog sensor device." << endl;
    cout << "The resolution is "<< bitsOfResolution <<", and the value is "<< value << "."<< endl;
}

void analogSensorDevice::setValue(int v) {
    int big_x = pow(2, bitsOfResolution) - 1;
    if (v < 0)
        value = 0;
    else if (v > big_x)
        value = big_x;
    else
        value = v;

	if (globalTime > 0)
	{
		createEvent(globalTime);
	}
}

digitalControllerDevice::digitalControllerDevice(string n, int i) :device(n, i) {
    value = OFF;
    type = DIGITAL_CONTROLLER; 
}

void digitalControllerDevice::display() const {
    device::display();
    cout << "This is a digital controller device." << endl;
    cout << "The device is currently ";
    if(value==ON) cout << "ON." << endl;
    else          cout << "OFF." << endl;
}

void digitalControllerDevice::setValue(int v) {
    value = v;
}

analogControllerDevice::analogControllerDevice(string n, int i, int v, int up, int low) : device(n, i) {
    lowerLimit = low;
    upperLimit = up;
    type = ANALOG_CONTROLLER;
    analogControllerDevice::setValue(v);
}

void analogControllerDevice::display() const {
    device::display();
    cout << "This is an analog controller device with range "<< lowerLimit
        <<" to "<< upperLimit <<"." << endl;
    cout << "The value is "<< value <<"." << endl;
}

void analogControllerDevice::setValue(int v) {
    if (v < lowerLimit) {
        value = lowerLimit;
        cout << "***ERROR: Controller " << name << " assigned value below range." << endl;
    } else if (v > upperLimit) {
        value = upperLimit;
        cout << "***ERROR: Controller " << name << " assigned value above range." << endl;
    } else {
        value = v;
    }
}

