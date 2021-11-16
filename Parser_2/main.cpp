#include <iostream>
#include<iostream>
#include<fstream>
#include<ctype.h>
#include<string>
using namespace std;

enum token{
	cin_sy , cout_sy, cin_op_sy, cout_op_sy, lparn_sy, rparn_sy, plus_sy, mult_sy, id , int_sy, real_sy,
	error_sy, end_source_sy
	/*intconst, text, semicolon, period, quotas,
	othersy,+ cinSym, +coutSym,
	+idSym, +error, +endSym*/
};

class parser{

	private:
		ifstream f;
		token curr_token;
//***************************************
		token check_reserved (string s){
			if (s=="cin") return cin_sy;
			else if (s=="cout") return cout_sy;
			else return id;
		}
//******************************************
		token get_token(){

			char ch;
			string s;
			int state = 0;


			while(state>=0 && state <=11 && !f.eof()){

				switch(state){
					case 0:
						f.get(ch);
						if (f.eof()) return end_source_sy;
						else if (isspace(ch)) {s=ch; state = 0;}
						else if (isdigit(ch)) {s=ch; state = 1;}
						else if (ch=='.') {s=ch; state = 2;}

						else if (isalpha(ch)) {s=ch; state = 4;}
						else if (ch=='<') state = 5;
						else if (ch=='>') state = 6;
						else if (ch=='+') state = 7;
						else if (ch=='*') state = 8;
						else if (ch=='(') state = 9;
						else if (ch==')') state = 10;
						else state = 11;
						break;

					case 1:
						f.get(ch);	//5555
						if (isdigit(ch)) {s+=ch; state=1;}
						else if (ch=='.') state=3;
						else {f.putback(ch); return int_sy;}
						break;

					case 2:
						f.get(ch);
						if (isdigit(ch)) {s+=ch; state=2;}
						else
						{
							f.putback(ch);
							return real_sy;
						}
						break;

					case 3:
						f.get(ch);
						if (isdigit(ch)) {s+=ch; state=3;}
						else
						{
							f.putback(ch);
							return real_sy;
						}
						break;

					case 4:
						f.get(ch);
						if(isalnum(ch)) {s+=ch; state=4;}
						else
						{
							f.putback(ch);
							return check_reserved(s);
						}
						break;

					case 5:
						f.get(ch);
						if(ch=='<') return cout_op_sy;
						else return error_sy;
						break;

					case 6:
						f.get(ch);
						if(ch=='>') return cin_op_sy;
						else return error_sy;
						break;

					case 7:
						return plus_sy; break;

					case 8:
						return mult_sy; break;

					case 9:
						return lparn_sy; break;

					case 10:
						return rparn_sy; break;

					case 11:
						return error_sy; break;


				}
			}
			return end_source_sy;
		}
//****************************************

	string name(token t){

		switch(t){

			case cin_sy: return "cin token";break;
			case cout_sy: return "cout token";break;
			case cin_op_sy: return ">> token";break;
			case cout_op_sy: return "<< token";break;
			case id: return "identifier";break;
			case int_sy: return "int token";break;
			case real_sy: return "real token";break;
			case plus_sy: return "+ token";break;
			case mult_sy: return "* token";break;
			case lparn_sy: return "( token";break;
			case rparn_sy: return ") token";break;
			case error_sy: return "error token";break;
			case end_source_sy: return "End of file";break;

		}

		return "error token";
	}
//****************************************

	public:


		parser(string filename){
			f.open(filename.c_str());
		}

		~parser(){
			f.close();
		}
		void match(token terminal){

			if (curr_token == terminal)
				cout<<name(curr_token)<<" is matched"<<endl;

			else
				syntax_error(curr_token);
			curr_token = get_token();
		}

		void syntax_error(token terminal){
			cout<<name(terminal)<<" is not Expected\n";
		}

		void sample_parser(){
			curr_token = get_token();
			program();
			match(end_source_sy);

		}

		//<program> ::= cin  >>  <expr-seq> |  cout  << <expr-seq>

		void program(){
			if(curr_token == cin_sy){
				match(cin_sy);
				match(cin_op_sy);
				expr_seq();
			}
			else if(curr_token == cout_sy){
				match(cout_sy);
				match(cout_op_sy);
				expr_seq();
			}
			else
				syntax_error(curr_token);
		}

		//<expr-seq>::= <expr> { <expr> }

		void expr_seq(){
			expr();
			while(curr_token == id || curr_token == int_sy || curr_token == real_sy || curr_token == lparn_sy || curr_token == rparn_sy ){
				expr();
			}
		}

		//<expr>    ::= <id>|<int> | <real> |  ( + <expr-seq>) | ( * <expr-seq>)

		void expr(){

			switch(curr_token){

				case id: match(id); break;
				case int_sy : match(int_sy);break;
				case real_sy : match(real_sy);break;

				case lparn_sy:
					match (lparn_sy);
					if (curr_token == plus_sy){
						match (plus_sy);
						expr_seq();
						match(rparn_sy);
					}
					else if (curr_token == mult_sy){
						match (mult_sy);
						expr_seq();
						match(rparn_sy);
					}
					else{
						syntax_error(curr_token);
					}
					break;

			}


		}


};


int main()
{
    string name;
    cout<<"Enter File Name: "; cin>>name;
    parser p(name);
    p.sample_parser();
    p.~parser();
}
