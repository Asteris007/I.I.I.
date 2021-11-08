#include <iostream>
#include<iostream>
#include<fstream>
#include<ctype.h>
#include<string>

using namespace std;

 enum  TSymbol {
	
	 cinSym, coutSym, cinOper, coutOper, period, quotas,semicolon, idSym, intconst, text,
	 error, endSym, othersy
};

 TSymbol Symbol;


class parser {

private:
	ifstream f;
	
	
	

	 TSymbol getCheck(string s) {
		
		 if (s == "cin") return cinSym;
		 else if (s == "cout") return coutSym;
		 else if (s == "end") return text;
		 else if (s == "course1")return text;
		 else if (s == "Hello") return text;
		 else if (s == "1234") return intconst;
		 else if (s == "631") return intconst;
		 else if (s ==  "5678")return intconst;

		 else return idSym;
	}



	TSymbol getNextSymbol() {

		char ch;
		string s;
		int state = 0;


		while (state >= 0 && state <= 11 && !f.eof()) {

			switch (state) {
			case 0:
				f.get(ch);
				if (f.eof()) return endSym;//end_source_sy
				else if (isspace(ch)) { s = ch; state = 0; }
				else if (isdigit(ch)) { s = ch; state = 1; }
				else if (ch == '.') { s = ch; state = 2; }

				else if (isalpha(ch)) { s = ch; state = 4; }
				else if (ch == ';') state = 5;
				else if (ch == '"') state = 6;
				else if (ch == '<') state = 7;
				else if (ch == '>') state = 8;
				else if ((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) state = 9;
				else if ((ch >= '0') && (ch <= '9')) state = 10;
				else state = 11;
				break;

			case 1:
				f.get(ch);	
				if (isdigit(ch)) { s += ch; state = 1; }
				else if (ch == '.') state = 3;
				else { f.putback(ch); return intconst; }
				break;

			case 2:
				f.get(ch);
				if (isdigit(ch)) { s += ch; state = 2; }
				else
				
				{
					f.putback(ch);
					return text;
				}
				break;

			case 3:
				f.get(ch);
				if (isdigit(ch)) { s += ch; state = 3; }
				else
				{
					f.putback(ch);
					return text;
				}
				break;

			case 4:
				f.get(ch);
				if (isalpha(ch)) { s += ch; state = 4; }
				else
				{
					f.putback(ch);
					return getCheck(s);

				}
				break;

			case 5:
				f.get(ch);
				if (ch == ';') {
					return semicolon;
				}
				else 
					return error;
				break;

			case 6:
				f.get(ch);
				if (ch == '"')
				{
					return quotas;
				}
				else return error;
				break;

			case 7:
				f.get(ch);
				if (ch == '<') return coutOper;
				else return error;
				break;

			case 8:
				f.get(ch);
				if (ch == '>') return cinOper;
				else return error;
				break;

			case 9:
				f.get(ch);
				if ((ch >= '0') && (ch <= '9')) return intconst;
				else return othersy;

			case 10:
				f.get(ch);
				if ((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) return text;
				else return othersy;
			
			case 11:

				return error; break;



			}
		}
		return endSym;
	}
	

	string identifyName(TSymbol s) {

		switch (s) {

		case cinSym: return " cin symbol"; break;
		case coutSym: return " cout symbol"; break;
		case cinOper: return ">> operator"; break;
		case coutOper: return "<< operator"; break;
		case idSym: return " Symbol "; break;
		case intconst: return " Intconstant "; break;
		case text: return " String "; break;
		case period: return " . "; break;
		case quotas: return " '' "; break;
		case semicolon: return " ; "; break;
		case othersy:return " Other symbol "; break;
		case error: return " Error symbol "; break;
		case endSym: return " End of file "; break;

		}

		return "error";
	}
	

public:


	parser(string filename) {
		f.open(filename.c_str());
	}

	~parser() {
		f.close();
	}
	
	void accept( TSymbol sym) {//match

		if (Symbol == sym)
			cout << identifyName(Symbol) << " Is matched" << endl;

		else
			expect(Symbol);
		Symbol = getNextSymbol();
	}

	void expect(TSymbol sym) {
		cout << identifyName(sym) << " is not Expected\n";
	}

	void record() {//sample..
		Symbol = getNextSymbol();
			getNextChar();
			accept(endSym);
	
	}

	//<program> ::= cin  >>  <expr-seq> |  cout  << <expr-seq>

	void getNextChar() {//program
		if (Symbol == cinSym) {
			accept(cinSym);
			accept(cinOper);
			accept(period);
			accept(quotas);
			accept(semicolon);
			accept(text);
			accept(intconst);
			

			dataFile();
			

		}
		else if (Symbol == coutSym) {
			accept(coutSym);
			accept(coutSym);
			
			dataFile();
			
		}
		else
			printf("field: expects intconst or string ");
			expect(Symbol);
	}

	//<expr-seq>::= <expr> { <expr> }

	void dataFile() {//expr_sq
		field();
		while ((Symbol == intconst) || (Symbol == quotas)) {
			field();
		}
	}

	//<expr>    ::= <id>|<int> | <real> |  ( + <expr-seq>) | ( * <expr-seq>)

	void field() { //expr

		switch (Symbol) {
	

		case intconst:accept(intconst);
			 {
				dataFile();
				accept(intconst);
			}
			 if (Symbol == quotas) {
				accept(quotas);
				dataFile();
				expect(text);
				expect(quotas);
				
			}
			else {
				 printf("field: expects intconst or string");
				expect(Symbol);
			}
			break;

		}


	}


};


int main()
{
	string name;
	cout << "Enter File Name: "; cin >> name;
	parser p(name);
	p.record();
	p.~parser();
}
