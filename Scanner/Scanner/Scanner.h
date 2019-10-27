#pragma once
#include "LexicalAnalyser.h"
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <map>
#include <string>
#include <typeinfo>

class Token {
private:
	LexemType _type;
	int _value;
	std::string _str;  
	bool ForInt = false;

public:
	Token(LexemType type) : _type(type) {};
	Token(LexemType type, int value) : _type(type), _value(value) { ForInt = true; };
	Token(LexemType type, const std::string& str) : _type(type), _str(str) {};

	int value() { return _value; };
	std::string str() { return _str; };
	LexemType type() { return _type; };

	void print(std::ostream& stream) {
		if (_type == LexemType::eof) {
			stream << "[" + lexemTranslations[_type] + ']' << std::endl;
		}
		else if (_type == LexemType::error) {
			stream << '[' + lexemTranslations[_type] + ':' + _str + ']' << std::endl;
		}
		else if (this->_str.empty() == false) {
			stream << '[' + lexemTranslations[_type] + ", " + "\"" + _str + +"\"" + ']' << std::endl;
		}
		else if (ForInt) {
			stream << '[' + lexemTranslations[_type] + ", " << _value << ']' << std::endl;
		}
		else { 
			stream << '[' + lexemTranslations[_type] +']' << std::endl;
		}
	}
};

class Scanner {
private:
	char SavedChar;
	std::istream& LexemStream;
	int State = 0;
	int Value;
	std::string value;
	int GoTo = 0;

public:
	Scanner(std::istream& stream) : LexemStream(stream) {};

	Token getNextToken() {
		while (true) {
			if (this->GoTo == 0) {
				LexemStream >> std::noskipws >> this->SavedChar;
			}
			else { this->GoTo = 0; }

			switch (this->State) {
			case 0:

				if (this->LexemStream.eof()) { return Token(LexemType::eof); };
				// Punct
				if (SavedChar == '(') { return Token(LexemType::lpar); };
				if (SavedChar == ')') { return Token(LexemType::rpar); };
				if (SavedChar == '{') { return Token(LexemType::lbrace); };
				if (SavedChar == '}') { return Token(LexemType::rbrace); };
				if (SavedChar == '[') { return Token(LexemType::lbracket); };
				if (SavedChar == ']') { return Token(LexemType::rbracket); };
				if (SavedChar == ';') { return Token(LexemType::semicolon); };
				if (SavedChar == ',') { return Token(LexemType::comma); };
				if (SavedChar == ':') { return Token(LexemType::colon); };

				// Operations
				if (SavedChar == '*') { return Token(LexemType::opmult); };
				if (SavedChar == '$') { return Token(LexemType::eof); };
				if (SavedChar == '>') { return Token(LexemType::opgt); };

				// WS
				if (SavedChar == ' ') { this->State = 0; break; };
				if (SavedChar == '\n') { this->State = 0; break;};
				if (SavedChar == '\t') { this->State = 0; break; };

				if (SavedChar >= '0' && SavedChar <= '9') {
					this->Value = (int)SavedChar%48;
					this->State = 1;
					break;
				};

				if (SavedChar == '\'') {
					this->value = "";
					this->State = 2;
					break;
				};

				if (SavedChar == '"') {
					this->value = "";
					this->State = 4;
					break;
				};

				if (SavedChar >= (char)'a' && SavedChar <= (char)'z' || SavedChar >= (char)'A' && SavedChar <= (char)'Z') {
					this->value = SavedChar;
					this->State = 5;
					break;
				};

				if (SavedChar == '-') {
					this->State = 6;
					break;
				};

				if (SavedChar == '!') {
					this->State = 7;
					break;
				};

				if (SavedChar == '<') {
					this->State = 8;
					break;
				};

				if (SavedChar == '=') {
					this->State = 9;
					break;
				};

				if (SavedChar == '+') {
					this->State = 10;
					break;
				};

				if (SavedChar == '|') {
					this->State = 11;
					break;
				};

				if (SavedChar == '&') {
					this->State = 12;
					break;

				};


			case 1:
				if (SavedChar >= '0' && SavedChar <= '9') { State = 1; Value = Value * 10 + (int)SavedChar%48; break;};
				this->State = 0;
				this->GoTo = 1;
				return Token(LexemType::num, this->Value);

			case 2:
				if (SavedChar == '\'') { return Token(LexemType::error, "Empty character constant"); };
				this->value = SavedChar;
				this->State = 3;
				break;
	
			case 3:
				if (SavedChar == '\'') { this->State = 0; return Token(LexemType::chr, this->value); };
				return Token(LexemType::error, "Character constant containing more than one character");
		

			case 4:
				if (SavedChar == '$') { return Token(LexemType::error, "Unsupported character"); };
				if (SavedChar == '"') { this->State = 0; return Token(LexemType::str, this->value); };
				this->State = 4;
				this->value += SavedChar;
				break;

			case 5:
				if (SavedChar >= (char)'a' && SavedChar <= (char)'z' || SavedChar >= (char)'A' && SavedChar <= (char)'Z') {
					this->State = 5; 
					this->value += SavedChar; 
					break;
				};
				
				if (SavedChar >= '0' && SavedChar <= '9') {
					this->State = 5;
					this->value += SavedChar;

					break;
				};
				

				if (this->value == "int") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwint); };
				if (this->value == "char") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwchar); };
				if (this->value == "if") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwif); };
				if (this->value == "else") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwelse); };
				if (this->value == "switch") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwswitch); };
				if (this->value == "case") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwcase); };
				if (this->value == "while") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwwhile); };
				if (this->value == "for") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwfor); };
				if (this->value == "return") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwreturn); };
				if (this->value == "in") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwin); };
				if (this->value == "out") { this->State = 0; this->GoTo = 1; return Token(LexemType::kwout); };

				this->State = 0;
				this->GoTo = 1;
				return Token(LexemType::id, this->value);

			case 6:
				if (SavedChar >= '0' && SavedChar <= '9') { State = 1; this->Value = (-1) * SavedChar; break;};
				return Token(LexemType::opminus);
		

			case 7:
				this->State = 0;
				if (SavedChar == '=') { return Token(LexemType::opne); };
				return Token(LexemType::opnot);
			

			case 8:
				this->State = 0;
				if (SavedChar == '=') { return Token(LexemType::ople); };
				return Token(LexemType::oplt);
	

			case 9:
				this->State = 0;
				if (SavedChar == '=') { return Token(LexemType::opeq); };
				return Token(LexemType::opassign);

			case 10:
				this->State = 0;
				if (SavedChar == '+') { return Token(LexemType::opinc); };
				return Token(LexemType::opplus);
			

			case 11:
				if (SavedChar == '|') { this->State = 0; return Token(LexemType::opor); break;};
				return Token(LexemType::error, "Incomplete OR operator");
	

			case 12:
				if (SavedChar == '&') { this->State = 0; return Token(LexemType::opand); break;};
				return Token(LexemType::error, "Incomplete AND operator");

			}
		}
	};
};
