/*
	Classes malfunctionRecord and device for car embedded system project.
	
	Author:		Larry Henschen
	Last Modified:	Dec 1, 2016 (Sara Sood)
*/

#include <string>
using namespace std;

class malfunctionRecord {
    private:
        int count;
        int lastMalfunction;
        int lastMalfunctionTime;
	public:
        malfunctionRecord();
        void display() const;
        void malfunction(int mtype, int time);
        int  getRecord(int& m, int& t);
};

class device {
	protected:
        string name;
        int  id;
        malfunctionRecord mr;
        int value;
        int type;               
	public:
        device(string n, int i);
		string giveName();
        virtual void display() const;
        void recordMalfunction(int m, int t);
        int  getMalfunctionRecord(int& m, int& t);
        int  amIThisDevice(string n);
        //new or changed for pa8
        virtual int myType();
        virtual int getValue();
        virtual void setValue(int v) = 0;
        void createEvent(int tm);
        //end new or changed for pa8
};

class digitalSensorDevice : public device {
    public:
        digitalSensorDevice(string n, int i, int v);
        void display() const;
        void setValue(int v); 
};

class analogSensorDevice: public device {
    private:
        int bitsOfResolution;
    public:
        analogSensorDevice(string n, int i, int v, int bor);
        void display() const;
        void setValue(int v);
};

class digitalControllerDevice: public device {
    public:
        digitalControllerDevice(string n, int i);
        void display() const;
        void setValue(int v); 
};

class analogControllerDevice: public device {
    private:
        int upperLimit;
        int lowerLimit;
    public:
        analogControllerDevice(string n, int i, int v, int up, int low);
        void display() const;
        void setValue(int v);
};