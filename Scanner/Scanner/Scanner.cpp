#include "LexicalAnalyser.h"
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <map>



class Token {
private:
	LexemType _type;
	int _value;
	std::string _str;
public:
	Token(LexemType type) : _type(type) {};
	Token(int value) : _value(value) {};
	Token(LexemType type, const std::string& str) : _type(type), _str(str) {};

	int value() { return _value; };
	std::string str() { return _str; };
	LexemType type() { return _type; };
	std::string getLexemTranslation(LexemType type, std::string value, int errorNumber = 0) {
		std::map<std::string, int> errors = {
			{ "символьная константа содержит более одного символа", 1 }
		};
		std::map<LexemType, std::string> lexemTranslations{
			{LexemType::num, "num"}, { LexemType::chr, "chr" }, { LexemType::str, "str" }, { LexemType::id, "id" }, { LexemType::lpar, "lpar" }, { LexemType::rpar, "rpar" }, { LexemType::lbrace, "lbrace" }, { LexemType::rbrace, "rbrace" }, { LexemType::lbracket, "lbracket" }, { LexemType::rbracket, "rbracket" },
			{ LexemType::semicolon, "semicolon" }, { LexemType::comma, "comma" }, { LexemType::colon, "colon" }, { LexemType::opassign, "opassign" }, { LexemType::opplus, "opplus" }, { LexemType::opminus, "opminus" }, { LexemType::opmult, "opmult" }, { LexemType::opinc, "opinc" }, { LexemType::opeq, "opeq" }, { LexemType::opne, "opne" }, { LexemType::oplt, "oplt" },
			{ LexemType::opgt, "opgt" }, { LexemType::ople, "ople" }, { LexemType::opnot, "opnot" }, { LexemType::opor, "opor" }, { LexemType::opand, "opand" }, { LexemType::kwint, "kwint" }, { LexemType::kwchar, "kwchar" }, { LexemType::kwif, "kwif" }, { LexemType::kwelse, "kwelse" }, { LexemType::kwswitch, "kwswitch" }, { LexemType::kwcase, "kwcase" }, { LexemType::kwwhile, "kwwhile" },
		{ LexemType::kwfor, "kwfor" }, { LexemType::kwreturn, "kwreturn" }, { LexemType::kwin, "kwin" }, { LexemType::kwout, "kwout" }, { LexemType::eof, "eof" }, { LexemType::error, "error" } };
		if (type == LexemType::eof) {
			return "[" + lexemTranslations[type] + ']';
		}
		if (type == LexemType::error) {
			return '[' + lexemTranslations[type] + ':' + errors.find[errorNumber] + ']';
		}
		else {
			return '[' + lexemTranslations[type] + ':' + value + ']';
		}
	}

	void print(std::ostream& stream) {
		stream << getLexemTranslation(this->_type, this->_str);
	}

};