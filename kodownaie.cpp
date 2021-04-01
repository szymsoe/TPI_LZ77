//  PODSTAWY TEORII INFORMACJI - PROJEKT
//  Kodowanie slownikowe dynamiczne - LZ77

#include <iostream>
#include "kod.h"

// TODO: kod arrays

int main()
{
    const char* s1 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    kod code1(s1,100);

    code1.show_entropy();
    code1.show_bitrate();
    code1.show_source();
    code1.show_code();

    return 0;
}

