#pragma once

#pragma region defines
#define ID_MAXSIZE 15
#define ID_SCOPE_SIZE 15
#define TI_MAXSIZE 4096
#define TI_INT_DEFAUL 0x0000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX -1
#define TI_STR_MAXSIZE 255
#pragma endregion

namespace IT {
	enum class IDDATATYPE { INT = 1, STR = 2 };
	enum class IDTYPE { V = 1, F = 2, P = 3, L = 4 }; //q “»œ€ »ƒ≈Õ“»‘» ¿“Œ–Œ¬: œ≈–≈Ã≈ÕÕ¿ﬂ, ‘”Õ ÷»ﬂ, œ¿–¿Ã≈“–, À»“≈–¿À

	struct Entry {
		int idxfirstLE;
		char id[ID_MAXSIZE];
		char scope[ID_SCOPE_SIZE];
		char literalID[ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union Value {
			int vint;
			struct String {
				size_t len;
				char str[TI_STR_MAXSIZE];
			} vstr;
		} value;
		Entry() = default;
		Entry(int idxfirstLE, const char* id, const char* scope, const char* literalID, IDDATATYPE iddatatype, IDTYPE idtype, std::string value);
	};

	struct IdTable {
		int maxsize, size; //q size < maxsize
		Entry* table;
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, const Entry& entry);
	Entry GetEntry(IdTable& idtable, int n);
	bool is_digit(std::string str);
	int IsId(IdTable& idtable, const char id[ID_MAXSIZE], const char prefix[ID_SCOPE_SIZE]); //q ¬ÓÁ‚‡Ú ÌÓÏÂ‡ ÒÚÓÍË, ÂÒÎË ÒÛ˘ÂÒÚ‚ÛÂÚ || TI_NULLIDX
	int LiteralRepeat(IdTable& idtable, std::string literal);
	void Delete(IdTable& idtable);
}