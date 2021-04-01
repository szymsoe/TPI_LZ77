#pragma once


class kod
{
	static const int N = 4; //dictionary length
	int length;
	int code_length;

	double bitrate;
	double entropy;
	char dictionary[N];
	char buffer[N];
	char* code;
	char* source;

	void entropy_calc(const char* string);
public: 
	kod(const char* kod, int n);
	~kod();
	static int get_N() { return N; }
	int get_length() { return length; }
	void bitrate_calc();
	void make_code();
	void show_entropy();
	void show_source();
	void show_code();
	void show_bitrate();

};

void LCS(int& i, int& j, char* str1, char* str2);
double calculate(char a, const char* string, int length);