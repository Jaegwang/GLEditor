#pragma once

class ShortString
{
private:

	char buffer[128];

public:

	ShortString() {}
	ShortString(const char* ch)
	{
		for( int n=0; n<128; ++n )
		{ 
			buffer[n] = ch[n];
			if (ch[n] == '\0') break;
		}
	}

	const char* c_str() { return buffer; }



};

