#include <iostream>
#include<stdio.h>
#include <string.h>
#include<cstring>
#include <fstream>
#include<ctype.h>





using namespace std;


typedef enum TSymbolType
{
	strin, intconst, text, semicolon, period, quotas, othersy
}TSymbol;

TSymbol Symbol;
char Char;

void Field();
void Record();


/*datafile :: = record { record }
record :: = field{ ; field } .
field :: = integer | string
integer :: = digit { digit }
string :: = " text "
text :: = char { char }
char :: = letter | digit
letter :: = A | B | C | D | E | G | H | J | K | L | M | N | P | R | S | T | V | W | X | Y | Z
digit :: = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 */




void GetNextChar() {
	ifstream f;
	string filename;

	f.open(filename.c_str());
	f.get(Char);
	
	f.close();

}

void GetNextSymbol() {
	int digit = 0;
	int k = 0;
	char Spelling[20] = {};
	int Constant = intconst;


	while (Char == ' ') {
		GetNextChar();
	}
	switch (toupper(Char)) {
	case 'A' - 'Z':
	{
		strcpy_s(Spelling, "       ");
		do {
			if (k < MB_LEN_MAX) {
				Spelling[k] = toupper(Char);
				k++;
			}
			GetNextChar();

		} while ((Char >= '0') && (Char <= '9') || (toupper(Char) >= 'A') && (toupper(Char) <= 'Z'));
		Symbol = text;
	} break;

	case '0' - '9': {
		Constant = 0;
		do {
			digit = (unsigned int)(Char)-(unsigned int)('0');
			if ((Constant < (INT_MAX / 10))
				|| ((Constant == (INT_MAX / 10))
					&& (digit = (INT_MAX % 10)))) {
				Constant = (10 * Constant) + digit;
			}
			else {
				printf("error: Int constant too large");
				Constant = 0;
				exit(0);
			}
			GetNextChar();
		} while ((Char >= '0') && (Char <= '9'));
		Symbol = intconst;
	}break;
	case '.': {
		Symbol = period;
		GetNextChar();
	}break;
	case';': {
		Symbol = semicolon;
		GetNextChar();
	}break;
	case '"': {
		Symbol = quotas;
		GetNextChar();
	}break;
	default: {
		Symbol = othersy;
		GetNextChar();
	}break;
	}


}

void error(string msg) {
	
		printf("%s", msg.c_str());
	exit(0);
}


int accept(TSymbol sym) {
	if (Symbol == sym) {
		GetNextSymbol();
		return 1;
	}
	return 0;
}

int expect(TSymbol sym) {
	if (accept(sym))
		return 1;
	error(" expect: unexpected symbol");
	return 0;

}


void DataFile(void) {
	Record();
	while ((Symbol == intconst) || (Symbol == quotas))
	{
		GetNextSymbol();
		Record();
	}
}

void Record() {
	Field();
	while (Symbol == semicolon) {
		accept(semicolon);
		Field();
	}
	expect(period);

}

void Field() {
	if (accept(intconst)) {
		;
	}
	else if (accept(quotas)) {
		expect(text);
		expect(quotas);
	}
	else {
		error("field: expects intconst or string");
		
	}
}

int main() {
	string fName;
	cout << "Enter File Name: "; cin >> fName;
	GetNextChar();
	DataFile();
	return 0;
}
