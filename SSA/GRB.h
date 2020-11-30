#pragma once
#include "Error.h"

typedef short GRBALPHABET;

namespace GRB
{
	struct Rule
	{
		GRBALPHABET  nn;
		int iderror;
		short size;
		struct Chain
		{
			short size;
			std::vector<GRBALPHABET> nt;
			Chain() : size(0), nt(0) { };
			Chain(short psize, GRBALPHABET s, ...);
			std::string getCChain();
			static GRBALPHABET T(char t) { return GRBALPHABET(t); }
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); };
			static bool isT(GRBALPHABET s) { return s > 0; }
			static bool isN(GRBALPHABET s) { return !isT(s); }
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); };
		};
		std::vector<Chain> chains;
		Rule();
		Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...);
		std::string getCRule(short nchain);
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j);
	};
	struct Greibach
	{
		short size;
		GRBALPHABET startN;
		GRBALPHABET stbottomT;
		std::vector<Rule> rules;
		Greibach() : size(0), startN(0), stbottomT(0), rules(0) { };
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbootomT, short psize, Rule r, ...);
		short getRule(GRBALPHABET pnn, Rule& prule);
		Rule getRule(short n);
		static Greibach initGreibach();
	};
	Greibach getGreibach();
};
