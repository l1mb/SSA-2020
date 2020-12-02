#include "CodeGeneration.h"

CG::Generator::Generator(LT::LexTable lexT, IT::IdTable idT, wchar_t outfile[PARM_MAX_SIZE])
{
	lextable = lexT;
	idtable = idT;
	out = std::ofstream(outfile);
}

void CG::Generator::Start(const Log::LOG& log)
{
	Head();
	Constants();
	Data();
	Code();
	*log.stream << "-------------------------------------------------------------------------------------\n";

	*log.stream << "Код успешно сгенерирован\n";
	*log.stream << "-------------------------------------------------------------------------------------\n";
}

void CG::Generator::Head()
{
	out << ".586\n";
	out << ".model flat, stdcall\n";
	out << "includelib libucrt.lib\n";
	out << "includelib kernel32.lib\n";
	out << "includelib ../LP_LIB/Debug/LP_Lib.lib\n";
	out << "ExitProcess PROTO : DWORD\n";
	out << "EXTRN Concat\t\t\t: PROC\n";
	out << "EXTRN ConvertToChar\t\t: PROC\n";
	out << "EXTRN Copy\t\t\t: PROC\n";
	out << "EXTRN ConsoleWrite\t\t: PROC\n\n";
	out << "EXTRN Strlen \t\t\t: PROC\n\n";
	out << "\n.stack 4096\n";
}
//! std::setw(8) << std::setfill('0')
void CG::Generator::Constants()
{
	out << ".const\n";
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::IDTYPE::L)
		{
			out << "\t" << idtable.table[i].literalID;
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR)
				out << " BYTE " << idtable.table[i].value.vstr.str << ", 0";
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT)
				out << " DWORD " << std::setw(8) << std::setfill('0') << idtable.table[i].value.vint ;
			out << '\n';
		}
}

void CG::Generator::Data()
{
	std::vector<char> operators = { LEX_MINUS, LEX_PLUS, LEX_DIRSLASH, LEX_STAR, LEX_PERCENT };
	out << ".data\n";
	for (int i = 0; i < idtable.size; i++)
		if (idtable.table[i].idtype == IT::IDTYPE::V) {
			out << '\t';
			out << idtable.table[i].scope << idtable.table[i].id;
			out << "\t\t\tDWORD 0\n";
		}
}

void CG::Generator::Code()
{
	out << "\n.code\n";
	int indOfFunc = -1;
	int indOflex = -1;
	bool func = false;
	bool main = false;
	IT::Entry whileIterator;
	for (int i = 0; i < lextable.size; i++) {
		switch (lextable.table[i].lexema) {
		case LEX_FUNCTION: {
			if (func || main)
				break;
			indOfFunc = i + 1;
			out << idtable.table[lextable.table[indOfFunc].idxTI].id << " PROC ";
			func = true;
			int backup = i;
			while (lextable.table[i].lexema != LEX_RIGHTHESIS)
				i++;
			while (lextable.table[i].lexema != LEX_LEFTHESIS)
			{
				if (lextable.table[i].lexema == LEX_ID)
				{
					out << idtable.table[lextable.table[i].idxTI].id << ": DWORD";
					if (lextable.table[i - 2].lexema != LEX_LEFTHESIS)
						out << ", ";
				}
				i--;
			}
			i = backup;
			out << std::endl;
			break;
		}
		case LEX_MAIN: {
			main = true;
			out << "main PROC\n";
			break;
		}
		case LEX_BRACELET: {
			if (func)
			{
				out << idtable.table[lextable.table[indOfFunc].idxTI].id << " ENDP\n\n";
				func = false;
			}
			else
				out << "\tcall\t\tExitProcess\nmain ENDP\n";
			indOfFunc = 0;
			break;
		}
		case LEX_RETURN: {
			if (main) {
				out << "\tpush\t\t";
				if (lextable.table[i + 1].lexema == LEX_ID) {
					out << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
				}
				else
					out << idtable.table[lextable.table[i + 1].idxTI].literalID;
				out << std::endl;
			}
			else
			{
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR) {
					if (idtable.table[lextable.table[i + 1].idxTI].idtype != IT::IDTYPE::L)
						out << "\tmov\t\teax, " << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id << "\n\tret\n";
					else
						out << "\tmov\t\teax, offset " << idtable.table[lextable.table[i + 1].idxTI].literalID << "\n\tret\n";
				}
				else
					out << "\tmov\t\teax, " << idtable.table[lextable.table[i + 1].idxTI].scope
					<< idtable.table[lextable.table[i + 1].idxTI].id << "\n\tret\n";
			}
			break;
		}
		case LEX_PRINT: {
			if (lextable.table[i + 1].lexema == LEX_ID) {
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT) {
					out << "\tpush\t\t" << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\tConvertToChar\n";
					out << "\tpush\t\teax\n";
					out << "\tcall\t\tConsoleWrite\n\n";
				}
				else {
					out << "\tpush\t\t" << idtable.table[lextable.table[i + 1].idxTI].scope
						<< idtable.table[lextable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\tConsoleWrite\n\n";
				}
			}
			else if (lextable.table[i + 1].lexema == LEX_LITERAL) {
				if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT) {
					out << "\tpush\t\t" << idtable.table[lextable.table[i + 1].idxTI].literalID;
					out << "\n\tcall\t\tConvertToChar\n";
					out << "\tpush\t\teax\n";
					out << "\tcall\t\tConsoleWrite\n\n";
				}
				else {
					out << "\tpush\t\toffset " << idtable.table[lextable.table[i + 1].idxTI].literalID;
					out << "\n\tcall\t\tConsoleWrite\n\n";
				}
			}
			break;
		}
		case LEX_EQUAL: {
			indOflex = i - 1;
			while (lextable.table[i].lexema != LEX_SEMICOLON) {
				if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype != IT::IDTYPE::F)
					if (!func)
						out << "\tpush\t\t" << idtable.table[lextable.table[i].idxTI].scope
						<< idtable.table[lextable.table[i].idxTI].id << "\n";
					else
						out << "\tpush\t\t" << idtable.table[lextable.table[i].idxTI].id << "\n";
 				if (lextable.table[i].lexema == LEX_LITERAL) {
					if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						out << "\tpush\t\t";
					else
						out << "\tpush\t\toffset ";
					out << idtable.table[lextable.table[i].idxTI].literalID << "\n";
				}
				if (lextable.table[i].lexema == LEX_HEADOFFUNC)
				{
					int delta = lextable.table[i + 1].lexema - '0' + 1;
					out << "\tcall\t\t" << idtable.table[lextable.table[i - delta].idxTI].id << "\n";
					out << "\tpush\t\teax\n";
				}
				if (lextable.table[i].lexema == LEX_PLUS)
				{
					out << "\t;\\/Сложение\\/\n";
					out << "\tpop\t\teax\n";
					out << "\tpop\t\tebx\n";
					out << "\tadd\t\teax, ebx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\Сложение/\\\n";
				}
				if (lextable.table[i].lexema == LEX_MINUS)
				{
					out << "\t;\\/Вычитание\\/\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tsub\t\teax, ebx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\Вычитание/\\\n";
				}
				if (lextable.table[i].lexema == LEX_STAR)
				{
					out << "\t;\\/Умножение\\/\n";
					out << "\tpop\t\teax\n";
					out << "\tpop\t\tebx\n";
					out << "\tmul\t\tebx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\Умножение/\\\n";
				}
				if (lextable.table[i].lexema == LEX_DIRSLASH) {
					out << "\t;\\/Деление\\/\n";
					out << "\tpop\t\tebx\n";
					out << "\tmov\t\tedx, 0\n";
					out << "\tpop\t\teax\n";
					out << "\tdiv\t\tebx\n";
					out << "\tpush\t\teax\n";
					out << "\t;/\\Деление/\\\n";
				}
				if (lextable.table[i].lexema == LEX_PERCENT) {
					out << "\t;\\/Остаток от деления\\/\n";
					out << "\tpop\t\tebx\n";
					out << "\tmov\t\tedx, 0\n";
					out << "\tpop\t\teax\n";
					out << "\tdiv\t\tebx\n";
					out << "\tpush\t\tedx\n";
					out << "\t;/\\Остаток от деления/\\\n";
				}
				i++;
			}
			out << "\tpop\t\t\t" << idtable.table[lextable.table[indOflex].idxTI].scope
				<< idtable.table[lextable.table[indOflex].idxTI].id << "\n\n";
			break;
		}
		case LEX_COPY: {
			if (lextable.table[i - 1].lexema == LEX_FUNCTION)
				break;
			int positionOfParm = 0, q = i;
			while (lextable.table[q].lexema != LEX_SEMICOLON)
				q++;
			while (lextable.table[q].lexema != LEX_COPY) {
				q--;
				if (lextable.table[q].lexema == LEX_ID && idtable.table[lextable.table[q].idxTI].idtype != IT::IDTYPE::F) {
					if (!positionOfParm)
						out << "\tpush\t\toffset ";
					else
						out << "\tpush\t\t";
					out << idtable.table[lextable.table[q].idxTI].scope
						<< idtable.table[lextable.table[q].idxTI].id << std::endl;
					positionOfParm++;
				}
				else if (lextable.table[q].lexema == LEX_LITERAL) {
					if (!positionOfParm)
						out << "\tpush\t\toffset ";
					else
						out << "\tpush\t\t";
					out << idtable.table[lextable.table[q].idxTI].literalID << std::endl;
					positionOfParm++;
				}
			}
			out << "\tcall\t\tCopy\n";
			break;
		}

		case LEX_LEFTSQUARE: {
			int backup = i;
			out << "\t.while\t\t";
			while (lextable.table[i].lexema != LEX_WHILE) {
				i--;
				if (lextable.table[i].lexema == LEX_ID) {
					out << idtable.table[lextable.table[i].idxTI].scope
						<< idtable.table[lextable.table[i].idxTI].id << "\n\t;\\/Тело цикла\\/\n";
					whileIterator = idtable.table[lextable.table[i].idxTI];
				}
			}
			i = backup;
			break;
		}
		
		case LEX_RIGHTSQUARE: {
			out << "\tdec\t\t\t" << whileIterator.scope << whileIterator.id << std::endl;
			out << "\t;/\\Тело цикла/\\\n";
			out << "\t.endw\n";
			break;
		}
		default:break;
		}
	}
	out << "end main\n";
}