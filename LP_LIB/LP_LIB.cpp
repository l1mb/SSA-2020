#include "pch.h"

extern "C" {
	char* Concat(char* str2, char* str1) {
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

	int Copy(char* origin, char*& destination) {
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

	char* ConvertToChar(unsigned long number) {
		if (number == 0)
			return (char*)"0";
		char* temp = (char*)calloc(255, sizeof(char));
		char* buffer = (char*)calloc(255, sizeof(char));
		if (temp == NULL)
			return NULL;
		if (buffer == NULL)
			return NULL;

		int bin = 0, i = 1;
		while (number) {
			bin += (number % 2) * i;
			i *= 10;
			number /= 2;
		}
		i = 0;
		while (bin) {
			temp[i++] = (bin % 10) + '0';
			bin /= 10;
		}
		temp[i] = '\0';

		for (size_t i = 0, j = strlen(temp) - 1; i < strlen(temp); i++, j--)
			buffer[i] = temp[j];
		return buffer;
	}

	void ConsoleWrite(const char* buffer) {
		setlocale(0, "");
		if (buffer == NULL) {
			std::cout << "NULL\n";
			return;
		}
		std::cout << buffer << std::endl;
		return;
	}
}