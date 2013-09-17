#include <string>

using namespace std;

string ParsingUserMessage(string *userMsg)
{
	string tmp = "";
	int len = userMsg->find(";");

	tmp.assign(*userMsg, 0, len);
	userMsg->erase(0, len + 1);
	
	return tmp;
}

/*	Example

int main(void)
{
	string test = "rs232.dll;100;COM1;115200;8;0;0;0";

	string fileName, portName;
	unsigned long timeOut;
	unsigned long baudRate;
	char dataBits, stopBits, parity, flowControl;

	string tmp;

	fileName = ParsingUserMessage(&test);
	tmp = ParsingUserMessage(&test);	timeOut = (unsigned long)atol(tmp.c_str());
	portName = ParsingUserMessage(&test);
	tmp = ParsingUserMessage(&test);	baudRate = (unsigned long)atol(tmp.c_str());
	tmp = ParsingUserMessage(&test);	dataBits = atoi(tmp.c_str());
	tmp = ParsingUserMessage(&test);	stopBits = atoi(tmp.c_str());
	tmp = ParsingUserMessage(&test);	parity = atoi(tmp.c_str());
	tmp = ParsingUserMessage(&test);	flowControl = atoi(tmp.c_str());

	printf("%s  %d  %s  %d  %d  %d  %d  %d\n", fileName.c_str(), timeOut, portName.c_str(), baudRate, dataBits, stopBits, parity,
		flowControl);
	
	
	return 0;
}
*/