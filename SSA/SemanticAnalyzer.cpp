#include "pch.h"
#include "SemanticAnalyzer.h"

SA::SemanticAnalyzer::SemanticAnalyzer(LT::LexTable lextable, IT::IdTable idtable)
{
	this->lextable = lextable;
	this->idtable = idtable;
}

void SA::SemanticAnalyzer::Start(const Log::LOG& log)
{
	CheckReturn();
	ParmsOfFunc();
	ParmsOfStandFunc();
	Types();
	FuncReturn();
	CorrectAmountOfParms();
	*log.stream << "-------------------------------------------------------------------------------------\n";
	*log.stream << "—емантический анализ выполнен без ошибок\n";
}

//todo +-+-+-+-+-+-+- OK +-+-+-+-+-+-+-
void SA::SemanticAnalyzer::CheckReturn()
{
	bool main = false;
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_RETURN) {
			if (main) {
				if ((lextable.table[i + 1].lexema == LEX_ID || lextable.table[i + 1].lexema == LEX_LITERAL)
					&& idtable.table[lextable.table[i + 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
					throw ERROR_THROW_SEM(708, lextable.table[i].sn);
			}
			else if (lextable.table[i + 1].lexema == LEX_ID) {
				if (idtable.table[lextable.table[i + 1].idxTI].idtype == IT::IDTYPE::F)
					throw ERROR_THROW_SEM(700, lextable.table[i].sn);
			}
		}
		else if (lextable.table[i].lexema == LEX_MAIN)
			main = true;
}

//todo +-+-+-+-+-+-+- OK +-+-+-+-+-+-+-
void SA::SemanticAnalyzer::ParmsOfFunc()
{
	char buf[ID_MAXSIZE];
	int par = 0, funcpar = 0;
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_EQUAL) {
			while (lextable.table[i].lexema == LEX_SEMICOLON) {
				i++;
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F) {
					strcpy(buf, idtable.table[lextable.table[i].idxTI].id);
					for (int j = 0; j < i; j++)
						if (lextable.table[j].lexema == LEX_ID && lextable.table[j - 2].lexema == LEX_FUNCTION
							&& !strcmp(buf, idtable.table[lextable.table[j].idxTI].id)) {
							j++;
							for (j; lextable.table[j].lexema != LEX_RIGHTHESIS; j++)
								if (lextable.table[j].lexema == LEX_ID) {
									funcpar++;
									i += 2;
									if (idtable.table[lextable.table[j].idxTI].iddatatype == IT::IDDATATYPE::INT) {
										if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L
											&& idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
											par++;
										if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
											par++;
									}
									if (idtable.table[lextable.table[j].idxTI].iddatatype == IT::IDDATATYPE::STR) {
										if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L
											&& idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
											par++;
										if (lextable.table[i].lexema == LEX_ID)
											if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
												par++;
									}
								}
							if (funcpar != par || lextable.table[i + 2].lexema != LEX_SEMICOLON)
								throw ERROR_THROW_SEM(701, lextable.table[i].sn);
						}
				}
			}
		}
}

//todo +-+-+-+-+-+-+- OK +-+-+-+-+-+-+-
void SA::SemanticAnalyzer::ParmsOfStandFunc()
{
	for (int i = 0; i < lextable.size; i++)
		switch (lextable.table[i].lexema) {
		case LEX_PRINT: {
			if (lextable.table[i + 1].lexema != LEX_ID && lextable.table[i + 1].lexema != LEX_LITERAL)
				throw ERROR_THROW_SEM(704, lextable.table[i].sn);
			break;
		}
		case LEX_COPY:
		case LEX_CONCAT: {
			int parmsCount = 0;
			while (lextable.table[i].lexema != LEX_SEMICOLON) {
				i++;
				if (lextable.table[i].lexema == LEX_ID) {
					parmsCount++;
					if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::STR)
						throw ERROR_THROW_SEM(702, lextable.table[i].sn);
				}
			}
			if (parmsCount != 2)
				throw ERROR_THROW_SEM(703, lextable.table[i].sn);
			break;
		}
		}
}

//todo +-+-+-+-+-+-+- OK +-+-+-+-+-+-+-
void SA::SemanticAnalyzer::Types()
{
	IT::IDDATATYPE datatype;
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].lexema == LEX_EQUAL) {
			datatype = idtable.table[lextable.table[i - 1].idxTI].iddatatype;
			while (lextable.table[i].lexema != LEX_SEMICOLON) {
				i++;
				if ((lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
					&& idtable.table[lextable.table[i].idxTI].iddatatype != datatype) {
					if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
						throw ERROR_THROW_SEM(705, lextable.table[i].sn);
					else
						throw ERROR_THROW_SEM(706, lextable.table[i].sn);
				}
				else if (lextable.table[i].lexema == LEX_ID
					&& idtable.table[lextable.table[i].idxTI].idtype != IT::IDTYPE::F
					&& lextable.table[i + 1].lexema == LEX_LEFTHESIS)
					throw ERROR_THROW_SEM(709, lextable.table[i].sn);
				else if (lextable.table[i].lexema == LEX_CONCAT && datatype != IT::IDDATATYPE::STR
					|| lextable.table[i].lexema == LEX_COPY && datatype != IT::IDDATATYPE::INT)
					throw ERROR_THROW_SEM(705, lextable.table[i].sn);
			}
		}
	}
}

//todo +-+-+-+-+-+-+- OK +-+-+-+-+-+-+-
void SA::SemanticAnalyzer::FuncReturn()
{
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F
			&& lextable.table[i - 1].lexema == LEX_FUNCTION) {
			IT::IDDATATYPE iddatatype = idtable.table[lextable.table[i].idxTI].iddatatype;
			while (lextable.table[i].lexema != LEX_RETURN)
				i++;
			if (idtable.table[lextable.table[i + 1].idxTI].iddatatype != iddatatype)
				throw ERROR_THROW_SEM(707, lextable.table[i].sn);
		}
}

//todo +-+-+-+-+-+-+- OK +-+-+-+-+-+-+-
void SA::SemanticAnalyzer::CorrectAmountOfParms()
{
	std::string buf;
	buf.reserve(ID_MAXSIZE);
	int parms = 0, funcparms = 0;
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_EQUAL) {
			while (lextable.table[i].lexema != LEX_SEMICOLON) {
				i++;
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F) {
					buf = idtable.table[lextable.table[i].idxTI].id;
					while (lextable.table[i].lexema != LEX_RIGHTHESIS) {
						i++;
						if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
							parms++;
					}
					for (int j = 0; j < i; j++)
						if (lextable.table[j].lexema == LEX_ID && idtable.table[lextable.table[j].idxTI].idtype == IT::IDTYPE::F
							&& buf == idtable.table[lextable.table[j].idxTI].id) {
							j++;
							for (j; lextable.table[j].lexema != LEX_RIGHTHESIS; j++)
								if (lextable.table[j].lexema == LEX_ID)
									funcparms++;
							break;
						}
				}
			}
			if (funcparms != parms)
				throw ERROR_THROW_SEM(701, lextable.table[i].sn);
		}
}

//todo +-+-+-+-+-+-+- OK +-+-+-+-+-+-+-
void SA::SemanticAnalyzer::CheckWhile()
{
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_WHILE)
			while (lextable.table[i].lexema != LEX_LEFTSQUARE) {
				i++;
				if (lextable.table[i].lexema == LEX_ID
					&& idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT)
					throw ERROR_THROW_SEM(710, lextable.table[i].sn);
			}
}