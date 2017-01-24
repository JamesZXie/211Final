/*
	Event, LLNODE and LIST class declaration.
 
    Events include the name of the device, the type of event, and the time stamp.
	(Time-stamp 0 means this is urgent and should be processed before any other
	events.  Events are order be increasing time stamp.  Some events will not
	be processed until later times; for example, flashing a turn signal on and off
	happens every 3 seconds, so when it is turned on a new event is added for 3
	seconds later.
	
	An ordered linked list is used to store events.  A separate class is defined
	for the list nodes.
	
	Author:		Larry Henschen
	Last Modified:	Nov 26, 2016 (Sara Sood)
 */

#include <string>
using namespace std;

class LIST;
class EVENT;

class LLNODE {
	friend class LIST; //"LIST is my friend!"
	
	private:
		LLNODE *next;
		EVENT  *ev;
		
	public:
		LLNODE(EVENT *e);
        ~LLNODE();
};

class LIST {
	private:
		LLNODE *front;
		
	public:
		LIST();
		~LIST();
		void display();
		EVENT* getFirstEvent();
		void removeFirstEvent();
		void insertEvent(EVENT *e);
        void removeEventsNamed(string n); //new for pa8
};

class EVENT {
	private:
		string device;
		int  value;
		int  processTime;
		
	public:
		EVENT(string n, int v, int pt);
		void display();
		int  getProcessTime();
        string getDeviceName();
        int getValue();         
};

