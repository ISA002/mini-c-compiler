#include "LexicalAnalyser.h"
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <map>
#include <string>

class Token {
private:
	LexemType _type;
	int _value;
	std::string _str;
public:
	Token(LexemType type) : _type(type) {};
	Token(LexemType type, int value) : _type(type), _value(value) {};
	Token(LexemType type, const std::string& str) : _type(type), _str(str) {};

	int value() { return _value; };
	std::string str() { return _str; };
	LexemType type() { return _type; };
	
	std::string getLexemTranslation(LexemType type, std::string value = "") {
		
		if (type == LexemType::eof) {
			return "[" + lexemTranslations[type] + ']';
		}
		else if (type == LexemType::error) {
			return '[' + lexemTranslations[type] + ':' + value + ']';
		}
		else {
			return '[' + lexemTranslations[type] + ':' + value + ']';
		}
	}

	void print(std::ostream& stream) {
		if (this->_str.empty() == false) {
			stream << getLexemTranslation(this->_type, this->_str);
		}
		else {
			stream << getLexemTranslation(this->_type);
		}
	}
};

class Scanner {
private:
	int _State = 0;
	char SavedChar;
	std::istream& LexemStream;
	int State = 0;
	int Value;
	std::string value;

public:
	Scanner(std::istream& stream):LexemStream(stream) {};

	Token getNextToken() {
		while (true) {
			LexemStream >> SavedChar;
			switch (State) {
			case 0:
				//if (LexemStream.eof()) { return Token(LexemType::eof); };

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
				if (SavedChar == ' ') { this->State = 0; continue; };
				if (SavedChar == '\n') { this->State = 0; continue; };
				if (SavedChar == '\t') { this->State = 0; continue; };

				if (SavedChar >= '0' && SavedChar <= '9') {
					this->Value = (int)SavedChar;
					this->State = 1;
					continue;
				};

				if (SavedChar == '\'') {
					this->value = "";
					this->State = 2;
					continue;
				};

				if (SavedChar == '"') {
					this->value = "";
					this->State = 4;
					continue;
				};

				if (SavedChar >= (char)"a" && SavedChar <= (char)"z" || SavedChar >= (char)"A" && SavedChar <= (char)"Z") {
					this->value = SavedChar;
					this->State = 5;
					continue;
				};

				if (SavedChar == '-') {
					this->State = 6;
					continue;
				};

				if (SavedChar == '!') {
					this->State = 7;
					continue;
				};

				if (SavedChar == '<') {
					this->State = 8;
					continue;
				};

				if (SavedChar == '=') {
					this->State = 9;
					continue;
				};

				if (SavedChar == '+') {
					this->State = 10;
					continue;
				};

				if (SavedChar == '|') {
					this->State = 11;
					continue;
				};

				if (SavedChar == '&') {
					this->State = 12;
					continue;
				};
				
				return Token(LexemType::error, "Unsupported character");

			case 1:
				if (SavedChar >= '0' && SavedChar <= '9') { this->State = 1; this->Value = Value * 10 + (int)SavedChar; continue; };
				this->State = 0;
				return Token(LexemType::num, Value);

			case 2:
				if (SavedChar == '\'') { return Token(LexemType::error, "Empty character constant"); };
				this->value = SavedChar;
				this->State = 3;
				continue;

			case 3:
				if (SavedChar == '\'') { this->State = 0; return Token(LexemType::chr, value); };
				return Token(LexemType::error, "Character constant containing more than one character");

			case 4:
				if (SavedChar == '$') { return Token(LexemType::error, "Unsupported character"); };
				if (SavedChar == '"') { this->State = 0; return Token(LexemType::str, value); };
				this->State = 4;
				this->value += SavedChar;
				continue;

			case 5:
				if (SavedChar >= (char)"a" && SavedChar <= (char)"z" || SavedChar >= (char)"A" && SavedChar <= (char)"Z") { 
					this->State = 5; this->value += SavedChar; continue; };
				if (SavedChar >= '0' && SavedChar <= '9') {
					this->State = 5; this->value += SavedChar; continue;
				};
				this->State = 0;
				
				if (this->value == "int") { return Token(LexemType::kwint); };
				if (this->value == "char") { return Token(LexemType::kwchar); };
				if (this->value == "if") { return Token(LexemType::kwif); };
				if (this->value == "else") { return Token(LexemType::kwelse); };
				if (this->value == "switch") { return Token(LexemType::kwswitch); };
				if (this->value == "case") { return Token(LexemType::kwcase); };
				if (this->value == "while") { return Token(LexemType::kwwhile); };
				if (this->value == "for") { return Token(LexemType::kwfor); };
				if (this->value == "return") { return Token(LexemType::kwreturn); };
				if (this->value == "in") { return Token(LexemType::kwin); };
				if (this->value == "out") { return Token(LexemType::kwout); };

				return Token(LexemType::id, value);

			case 6:
				if (SavedChar >= '0' && SavedChar <= '9') { this->State = 1; this->Value = (-1) * SavedChar; continue; };
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
				if (SavedChar == '|') { this->State = 0; return Token(LexemType::opor); };
				return Token(LexemType::error, "Incomplete OR operator");

			case 12:
				if (SavedChar == '&') { this->State = 0; return Token(LexemType::opand); };
				return Token(LexemType::error, "Incomplete AND operator");
			}
		}
	};
};
