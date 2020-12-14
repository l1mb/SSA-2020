#include "pch.h"

extern "C" {
	char* _stdcall Concat(char* str2, char* str1)
	{
		if (str1 == NULL || str2 == NULL)
			return (char*)"NULL";
		char* out = (char*)calloc(255, sizeof(char));
		if (out == NULL)
			return NULL;
		for (size_t i = 0; i < strlen(str1); i++)
			out[i] = str1[i];
		for (size_t i = 0, q = strlen(str1); i < strlen(str2); i++, q++)
			out[q] = str2[i];
		out[strlen(str1) + strlen(str2)] = '\0';
		return out;
	}

	int _stdcall Copy(char* origin, char*& destination)
	{
		if (origin == NULL)
			return NULL;
		destination = (char*)calloc(255, sizeof(char));
		if (destination == NULL)
			return NULL;
		for (size_t i = 0; i < strlen(origin); i++)
			destination[i] = origin[i];
		destination[strlen(origin)] = '\0';
		return strlen(destination);
	}

	int _stdcall Strlen(char* str)
	{
		if (str == NULL)
			return 0;
		else
			return strlen(str);
	}

	char* _stdcall ConvertToChar(long number)
	{
		if (number == 0)
			return (char*)"0";
		char* temp = (char*)calloc(255, sizeof(char));
		char* buffer = (char*)calloc(255, sizeof(char));
		if (temp == NULL)
			return NULL;
		if (buffer == NULL)
			return NULL;

		int bin = number, i = 0;
		if (number < 0)
		{
			unsigned long cumber = number * (-1);
			bin = cumber;
		}
		while (bin) {
			temp[i++] = (bin % 10) + '0';
			bin /= 10;
		}

		if (number < 0)
		{
			buffer[0] = '-';
			for (size_t i = 1, j = strlen(temp) - 1; i <= strlen(temp); i++, j--)
				buffer[i] = temp[j];
		}
		else
		{
			for (size_t i = 0, j = strlen(temp) - 1; i < strlen(temp); i++, j--)
				buffer[i] = temp[j];
		}

		buffer[++i] = '\0';
		return buffer;
	}

	void _stdcall ConsoleWrite(const char* buffer)
	{
		setlocale(0, "");
		if (buffer == NULL) {
			std::cout << "NULL\n";
			return;
		}
		std::cout << buffer << std::endl;
		return;
	}
}