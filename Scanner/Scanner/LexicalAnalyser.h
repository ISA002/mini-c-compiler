#pragma once
#include <map>
#include <string>

enum class LexemType {
	num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket,
	semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc, opeq, opne, oplt,
	opgt, ople, opnot, opor, opand, kwint, kwchar, kwif, kwelse, kwswitch, kwcase, kwwhile,
	kwfor, kwreturn, kwin, kwout, eof, error};std::map<LexemType, std::string> lexemTranslations{
			{LexemType::num, "num"}, { LexemType::chr, "chr" }, { LexemType::str, "str" }, { LexemType::id, "id" }, { LexemType::lpar, "lpar" }, { LexemType::rpar, "rpar" }, { LexemType::lbrace, "lbrace" }, { LexemType::rbrace, "rbrace" }, { LexemType::lbracket, "lbracket" }, { LexemType::rbracket, "rbracket" },
			{ LexemType::semicolon, "semicolon" }, { LexemType::comma, "comma" }, { LexemType::colon, "colon" }, { LexemType::opassign, "opassign" }, { LexemType::opplus, "opplus" }, { LexemType::opminus, "opminus" }, { LexemType::opmult, "opmult" }, { LexemType::opinc, "opinc" }, { LexemType::opeq, "opeq" }, { LexemType::opne, "opne" }, { LexemType::oplt, "oplt" },
			{ LexemType::opgt, "opgt" }, { LexemType::ople, "ople" }, { LexemType::opnot, "opnot" }, { LexemType::opor, "opor" }, { LexemType::opand, "opand" }, { LexemType::kwint, "kwint" }, { LexemType::kwchar, "kwchar" }, { LexemType::kwif, "kwif" }, { LexemType::kwelse, "kwelse" }, { LexemType::kwswitch, "kwswitch" }, { LexemType::kwcase, "kwcase" }, { LexemType::kwwhile, "kwwhile" },
		{ LexemType::kwfor, "kwfor" }, { LexemType::kwreturn, "kwreturn" }, { LexemType::kwin, "kwin" }, { LexemType::kwout, "kwout" }, { LexemType::eof, "eof" }, { LexemType::error, "error" } };
