#pragma once
class CMessageHandler
{
private:
	char type;
	char message[100];

public:
	void encapsulate();
	void decapsulate();
};

