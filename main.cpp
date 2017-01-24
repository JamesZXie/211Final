/*
	A main function for testing assignment 8.
	
	Author:		Larry Henschen
	Last Modified:	Dec 1, 2016 (Sara Sood)
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "definitions.h"
#include "system_utilities.h"

device* devices[MAX_DEVICES];
int numDevices = 0;
LIST* eventList;
int globalTime = 0; 
int checkEngine = 0;

int main() {
   


    ifstream* inp = new ifstream;
    string* cmd_line = new string;
    string* parsed_command = new string[MAX_TOKENS_ON_A_LINE];
    int  number_of_tokens;
    int  done;
    int  k1, k2, k3;
    EVENT *tmpev;
    
    int cmd;
    
    inp->open("p8input.txt", ios::in);
    if(inp->fail()) {
        cout << "***Could not open file.";
        return 0;
    }
    
    fillSystemCommandList();
    done = 0;
    eventList = new LIST();
    
    do {
        if (getline(*inp, *cmd_line))
        {
            done = false; //we were able to get a line, so we're not done
        }
        else
        {
            done = true; //failed to get a line, so we're done
        }
        
        if (!done) //we have a line to process
        {
            //call the function that YOU define (parseCommandLine)
            number_of_tokens = parseCommandLine(*cmd_line, parsed_command);
        }
    
        cmd = getCommandNumber(parsed_command[0]);
        switch(cmd) {
            case HALT:
            {
                cout << "Command halt recognized" << endl;
                done = 1;
                break;
            }
            case STATUS:
            {
                cout << "Command status recognized" << endl;
                cout << "Time is: " << globalTime << endl;
                if (parsed_command[1] == "events") {
                    cout << "Event status." << endl;
                    eventList -> display();
                    cout << endl;
                }
                else if (parsed_command[1] == "devices"){
                    cout << "Device status." << endl;
                    for(int k=0; k<numDevices; k++) {
                        devices[k]->display();
                        cout << endl;
                    }
                }
                break;
            }
            case TIME_CLICK:
            {
                cout << "Command time_click recognized" << endl;
                globalTime += 1;
				processEvents();
                break;
            }
                
            case CREATE_DEVICE:
            {
                cout << "Command create_device recognized" << endl;
                if (numDevices >= MAX_DEVICES){
                    cout << "***ERROR: could not create device named "
                        << parsed_command[2] << ". Too many devices in system.";
                    break;
                } else {
                    device* dp  = makeDevice(parsed_command);
                    if (dp == NULL) {
                        cout << "***ERROR: could not create device named "
                            << parsed_command[2] << ". Illegal type." << endl;
                    } else {
                        devices[numDevices] = dp;
                        numDevices++;
                    }
                }
                break;
            }
            case CREATE_EVENT:
            {
                cout << "Command create_event recognized" << endl;
                k1 = convertStringToValue(parsed_command[2]);
                k2 = convertStringToValue(parsed_command[3]);
                tmpev = new EVENT(parsed_command[1], k1, k2);
                eventList->insertEvent(tmpev);
                break;
            }
            case SET_DEVICE_VALUE:
            {
                cout << "Command set_device_value recognized" << endl;
				string devName = parsed_command[1];
				int devValue = convertStringToValue(parsed_command[2]);
				
				device* newDevice = devices[findDevice(devName)];

				if (newDevice->myType() == DIGITAL_SENSOR || newDevice->myType() == DIGITAL_CONTROLLER)
				{
					if (devValue == 1)
					{
						devValue = ON;
					}
					else if (devValue == 0)
					{
						devValue = OFF;
					}
				}
				
				newDevice->setValue(devValue);
				break;
            }
            case PROCESS_EVENTS:
            {
                cout << "Command process_events recognized" << endl;
                processEvents();
                break;
            }
			case MALFUNCTION:
			{
				cout << "Command malfunction recognized" << endl;
				devices[findDevice(parsed_command[1])]->recordMalfunction(convertStringToValue(parsed_command[2]), globalTime);
				break;
			}
            case UNDEFINED_COMMAND:
            {
                cout << "Command not recognized" << endl;
                break;
            }
        }
    }
    while(!done);
    
    cout << "That's all, folks." << endl;
    
    freeSystemCommandList(); 
    delete[] parsed_command;
    delete cmd_line;
    delete inp;
    
    for (int i = 0; i < numDevices; i++) {
        delete devices[i];
    }
    
    delete eventList;
	int more;
	cin >> more;
}