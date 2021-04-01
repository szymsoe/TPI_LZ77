#include "kod.h"
#include <iostream>
#include <new>
#include <bitset>

kod::kod(const char* kod, int n): length(n)
{
	source = new (std::nothrow) char[length];
	if (!source)
	{
		for (int k = 0; k < N; k++)
		{
			buffer[k] = 0;
			dictionary[k] = 0;

		}
		code = nullptr;
		bitrate = 0;
		entropy = 0;
		code_length = 0;
		return;
	}

	for (int i = 0; i < length; i++)
	{
		source[i] = kod[i];
	}

	entropy_calc(source);

	code = new (std::nothrow) char[3 * (entropy+1) * length];
	if (!code)
	{
		for (int k = 0; k < N; k++)
		{
			buffer[k] = 0;
			dictionary[k] = 0;

		}
		bitrate = 0;
		entropy = 0;
		code_length = 0;
		return;
	}

	make_code();
	bitrate_calc();

}

kod::~kod()
{
	delete[] source;
	delete[] code;

}

void kod::make_code()
{
	int counter = 0;
	int pos = 0; //position in code char*
	for (int i = 0; i < N; i++)
		dictionary[i] = source[0];

	switch (dictionary[0])
	{
	case 'A':
	{
		code[pos++] = '0';
		code[pos++] = '0';
		break;
	}
	case 'B':
	{
		code[pos++] = '0';
		code[pos++] = '1';
		break;
	}
	case 'C':
	{
		code[pos++] = '1';
		code[pos++] = '0';
		break;
	}
	case 'D':
	{
		code[pos++] = '1';
		code[pos++] = '1';
		break;
	}
	default:
		break;
	}

	for (int i = 0; i < N; i++)
		buffer[i] = source[i];

	int i = 0, j = 0;
	std::string word;
	char next;

	do
	{
		LCS(i, j, dictionary, buffer);
		if (j >= N) j = N - 1;


		word = std::bitset<2>(i).to_string();
		code[pos++] = word[0];
		code[pos++] = word[1];
		word = std::bitset<2>(j).to_string();
		code[pos++] = word[0];
		code[pos++] = word[1];

		counter += j;
		next = source[counter];

		switch (next)
		{
		case 'A':
		{
			code[pos++] = '0';
			code[pos++] = '0';
			break;
		}
		case 'B':
		{
			code[pos++] = '0';
			code[pos++] = '1';
			break;
		}
		case 'C':
		{
			code[pos++] = '1';
			code[pos++] = '0';
			break;
		}
		case 'D':
		{
			code[pos++] = '1';
			code[pos++] = '1';
			break;
		}
		default:
			break;
		}
		counter++;

		int end = N;
		if (counter + N > length)
			end = length - counter;

		for (int k = 0; k < N; k++)
			buffer[k] = 0;

		for (int k = 0; k < end; k++)
			buffer[k] = source[counter + k];

		for (int k = 0; k < N-1; k++)
		{
			dictionary[k] = dictionary[k + 1];

		}
		dictionary[N - 1] = next;

	} while (buffer[0] != 0);

	code_length = pos;
}

void LCS(int& i, int& j, char* str1, char* str2)
{
	i, j = 0;
	int size = 0, m = 0, k = 0;
	int tmpk = -1;
	while(k< kod::get_N())
		if (str1[k] == str2[m])
		{
			if(tmpk==-1)
			tmpk = k;

			size++;
			m++;
			if (j < size) 
			{
				j = size;
				i = tmpk;
			}
			k++;
		}
		else
		{
			if(tmpk!=-1) k = tmpk;
			size = 0;
			m = 0;
			k++;
			tmpk = -1;
		}
}


void kod::entropy_calc(const char* string)
{
	double pA = calculate('A', string, length)/length, pB = calculate('B', string, length) / length,
		pC = calculate('C', string, length) / length, pD = calculate('D', string, length) / length;

	if (pA == 0.0) pA = 0.5;
	if (pB == 0.0) pB = 0.5;
	if (pC == 0.0) pC = 0.5;
	if (pD == 0.0) pD = 0.5;


 	entropy = pA * log2(1/pA) + pB * log2(1/pB) + pC * log2(1/pC) + pD * log2(1/pD);

}

void kod::bitrate_calc()
{
	bitrate = (double)code_length / (double)length;
}


void kod::show_entropy()
{
	std::cout << "Entropia: " << entropy << std::endl;;
}

void kod::show_source()
{
	std::cout << "The source: ";
	for (int k = 0; k < length; k++)
		std::cout << source[k];
	std::cout << std::endl;
}

void kod::show_code()
{
	//int end = 3 * (int)(entropy+0.5) * length;

	std::cout << "The code: ";

	for (int k = 0; k < code_length; k++)
		std::cout << code[k];

	std::cout << std::endl;
}

void kod::show_bitrate()
{
	std::cout << "Bitrate: " << bitrate <<std::endl;
}


double calculate(char a, const char* string, int length)
{
	int counter = 0;
	for (int i = 0; i < length; i++)
	{
		if (string[i] == a) counter++;

	}

	return counter;
}


