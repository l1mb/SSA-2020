#include "pch.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"

template <typename T>
struct container : T
{
	using T::T;
	using T::c;
};

std::string To_string(int n) {
	char buf[40];
	sprintf_s(buf, "%d", n);
	return buf;
}

bool PN::find_elem(std::stack<char> stack, size_t size, char elem) {
	for (size_t i = 0; i < size; i++)
		if (stack.top() == elem)
			return true;
		else
			stack.pop();
	return false;
}

int PN::get_priority(char lexem) {
	std::vector<std::pair<int, char>> priority = { {0, LEX_LEFTHESIS}, {0, LEX_RIGHTHESIS},
													{1, LEX_COMMA},
													{2, LEX_PLUS}, {2, LEX_MINUS},
													{3, LEX_STAR}, {3, LEX_DIRSLASH},
													{3, LEX_PERCENT} };
	for (size_t i = 0; i < priority.size(); i++)
		if (lexem == priority[i].second)
			return priority[i].first;
	return 0;
}

void PN::fix_lextable(LT::LexTable& lextable, const std::string& str, size_t length, size_t pos, const std::vector<int>& ids) {
	for (size_t i = 0, q = 0; i < str.size(); i++) {
		lextable.table[pos + i].lexema = str[i];
		if (lextable.table[pos + i].lexema == LEX_ID || lextable.table[pos + i].lexema == LEX_LITERAL
			|| lextable.table[pos + i].lexema == LEX_CONCAT || lextable.table[pos + i].lexema == LEX_COPY) {
			lextable.table[pos + i].idxTI = ids[q];
			q++;
		}
		else
			lextable.table[pos + i].idxTI = LT_TI_NULLIDX;
	}
	int temp = str.size() + pos;
	for (size_t i = 0; i < length - str.size(); i++) {
		lextable.table[temp + i].idxTI = LT_TI_NULLIDX;
		lextable.table[temp + i].lexema = '!';
		lextable.table[temp + i].sn = -1;
	}
}

void PN::PolishNotation(LT::LexTable& lextable, IT::IdTable& idtable) {
	for (int i = 0; i < lextable.size; i++)
		if (lextable.table[i].lexema == LEX_EQUAL)
			if (!Convertation(i + 1, lextable, idtable))
				throw ERROR_THROW(130);
}

bool PN::Convertation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
{
	container<std::stack<char>> stack;
	std::string PolishString;
	std::vector<char> operators = { LEX_MINUS, LEX_PLUS, LEX_DIRSLASH, LEX_STAR, LEX_PERCENT };
	std::vector<int> ids;
	int operators_count = 0, operands_count = 0, iterator = 0, right_counter = 0, left_counter = 0, params_counter = 0;

	for (int i = lextable_pos; i < lextable.size; i++, iterator++) {
		char lexem = lextable.table[i].lexema;
		size_t stack_size = stack.size();
		if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F) {
			stack.push(LEX_HEADOFFUNC);
			operands_count--;
		}
		if (std::find(operators.begin(), operators.end(), lexem) != operators.end()) {
			if (!stack.empty() && stack.top() != LEX_LEFTHESIS) {
				while (!stack.empty() && PN::get_priority(lexem) <= PN::get_priority(stack.top())) {
					PolishString += stack.top();
					stack.pop();
				}
			}
			stack.push(lexem);
			operators_count++;
		}
		else if (lexem == LEX_COMMA) {
			while (!stack.empty()) {
				if (stack.top() == LEX_LEFTHESIS)
					break;
				PolishString += stack.top();
				stack.pop();
			}
			operands_count--;
		}
		else if (lexem == LEX_LEFTHESIS) {
			left_counter++;
			stack.push(lexem);
		}
		else if (lexem == LEX_RIGHTHESIS) {
			right_counter++;
			if (!PN::find_elem(stack, stack_size, LEX_LEFTHESIS))
				return false;
			while (stack.top() != LEX_LEFTHESIS) {
				PolishString += stack.top();
				stack.pop();
			}
			stack.pop();
			if (!stack.empty() && stack.top() == LEX_HEADOFFUNC) {
				PolishString += stack.top() + To_string(params_counter - 1);
				params_counter = 0;
				stack.pop();
			}
		}
		else if (lexem == LEX_SEMICOLON) {
			if (operators_count != 0 && operands_count != 0)
				if ((!stack.empty() && (stack.top() == LEX_RIGHTHESIS || stack.top() == LEX_LEFTHESIS))
					|| right_counter != left_counter || operands_count - operators_count != 1)
					return false;
			while (!stack.empty()) {
				PolishString += stack.top();
				stack.pop();
			}
			PN::fix_lextable(lextable, PolishString, iterator, lextable_pos, ids);
			break;
		}
		else if (lexem == LEX_ID || lexem == LEX_LITERAL || lexem == LEX_CONCAT || lexem == LEX_COPY) {
			if (std::find(stack.c.begin(), stack.c.begin(), LEX_HEADOFFUNC) != stack.c.end())
				params_counter++;
			PolishString += lexem;
			if (lextable.table[i].idxTI != LT_TI_NULLIDX)
				ids.push_back(lextable.table[i].idxTI);
			operands_count++;
		}
	}
	return true;
}