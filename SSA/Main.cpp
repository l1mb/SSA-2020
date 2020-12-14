#include "pch.h"
#include "IT.h"
#include "LT.h"
#include "Log.h"
#include "PolishNotation.h"
#include "FST.h"
#include "MFST.h"
#include "SemanticAnalyzer.h"
#include "CodeGeneration.h"
#include <tchar.h>

std::string getDataType(IT::IDDATATYPE type) {
	switch (type) {
	case IT::IDDATATYPE::INT: return "INT";
	case IT::IDDATATYPE::STR: return "STR";
	default: return "ERROR";
	}
}

std::string getType(IT::IDTYPE type) {
	switch (type) {
	case IT::IDTYPE::F: return "FUNCTION";
	case IT::IDTYPE::L: return "LITERAL";
	case IT::IDTYPE::P: return "PARAMETER";
	case IT::IDTYPE::V: return "VARIABLE";
	default: return "ERROR";
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	setlocale(LC_ALL, "rus");

	Log::LOG log = Log::LOG();
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		LT::LexTable lextable = LT::Create((int)in.lexems.size());
		IT::IdTable idtable = IT::Create((int)in.lexems.size());
		std::ofstream outputFile(parm.out);

		/*+-+-+-+-+-+-+-+- Лексический анализ +-+-+-+-+-+-+-+-*/
		FST::Recognize(in.lexems, log.stream, lextable, idtable);
		if (parm.lex) {
			*log.stream << "+-+-+-+-+-+-+-+- Таблица лексем +-+-+-+-+-+-+-+-\n";
			for (int i = 0; i < lextable.size; i++) {
				*log.stream << i << "\t---->\t\t";
				*log.stream << lextable.table[i].idxTI << " - ";
				*log.stream << lextable.table[i].lexema << " - ";
				*log.stream << lextable.table[i].sn << std::endl;
			}
			*log.stream << "+-+-+-+-+-+-+-+- Таблица лексем +-+-+-+-+-+-+-+-\n";
		}

		if (parm.id) {
			*log.stream << "+-+-+-+-+-+-+-+- Таблица идентификаторов +-+-+-+-+-+-+-+-\n";
			for (int i = 0; i < idtable.size; i++) {
				*log.stream << i << "\t---->\t\t";
				if (idtable.table[i].idtype == IT::IDTYPE::L) {
					*log.stream << idtable.table[i].literalID << " - "
						<< getDataType(idtable.table[i].iddatatype) << " - "
						<< getType(idtable.table[i].idtype) << " - "
						<< idtable.table[i].idxfirstLE << " - ";
				}
				else {
					*log.stream << idtable.table[i].scope << " - "
						<< idtable.table[i].id << " - "
						<< getDataType(idtable.table[i].iddatatype) << " - "
						<< getType(idtable.table[i].idtype) << " - "
						<< idtable.table[i].idxfirstLE << " - ";
				}
				if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT)
					*log.stream << idtable.table[i].value.vint << std::endl;
				else
					*log.stream << idtable.table[i].value.vstr.str << std::endl;
			}
			*log.stream << "+-+-+-+-+-+-+-+- Таблица идентификаторов +-+-+-+-+-+-+-+-\n";
		}
		/*+-+-+-+-+-+-+-+- Синтаксический анализ +-+-+-+-+-+-+-+-*/
		MFST::Mfst mfst(lextable, GRB::getGreibach());
		if (!mfst.start(log))
			exit(0);
		mfst.printrules(log);
		MFST::Mfst::clearGreibach(mfst);

		/*+-+-+-+-+-+-+-+- Семантический анализ +-+-+-+-+-+-+-+-*/
		/*SA::SemanticAnalyzer SAnalyzer = SA::SemanticAnalyzer(lextable, idtable);
		SAnalyzer.Start(log);*/	

		/*+-+-+-+-+-+-+-+- Польская запись +-+-+-+-+-+-+-+-*/
		PN::PolishNotation(lextable, idtable);

		/*+-+-+-+-+-+-+-+- Генерация кода +-+-+-+-+-+-+-+-*/
		CG::Generator CodeBuilder = CG::Generator(lextable, idtable, parm.out);
		CodeBuilder.Start(log);
		

		LT::Delete(lextable);
		IT::Delete(idtable);
		std::cout << "Работа завершена. Информация расположена в ";
		std::wcout << parm.log;
		std::cout << std::endl;
	}
	catch (Error::ERROR e) {
		Log::WriteError(log, e);
	}
	Log::Close(log);

#ifdef _DEBUG
	int hasMemoryLeaks = _CrtDumpMemoryLeaks();
#else
	system("pause");
#endif
	return 0;
	}