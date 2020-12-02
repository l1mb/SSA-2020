#include "pch.h"
#include "Error.h"
#include "Log.h"
#include "LT.h"
#include "MFST.h"
#include "GRB.h"

#define GRB_ERROR_SERIES 600

namespace GRB
{
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
		: size(psize)
	{
		va_list params;
		va_start(params, psize);
		for (short i = 0; i < psize; ++i)
			nt.push_back(va_arg(params, GRBALPHABET));
	};
	Rule::Rule() : chains(NULL), size(0), nn(0), iderror(NULL) {}
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
		: nn(pnn), iderror(piderror), size(psize)
	{
		va_list params;
		va_start(params, psize);
		for (int i = 0; i < size; i++)
			chains.push_back(va_arg(params, Chain));
	};
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
		: startN(pstartN), stbottomT(pstbottom), size(psize)
	{
		va_list params;
		va_start(params, psize);
		for (int i = 0; i < size; i++)
			rules.push_back(va_arg(params, Rule));
	};
	Greibach Greibach::initGreibach()
	{
#pragma region "gr"
		Greibach greibach(NS('S'), TS('$'),
			6,
			Rule(NS('S'), GRB_ERROR_SERIES + 0,
				8, //todo m{NrE;};   tfi(F){NrE;};S   m{NrE;};S   tfi(F){NrE;};   tfi(){NrE;};   tfi(){NrE;};S
				Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
				Rule::Chain(7, TS('m'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
				Rule::Chain(8, TS('m'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
				Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
				Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
				Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
				Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
				Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'))
			),
		
			Rule(NS('N'), GRB_ERROR_SERIES + 1,
				27, //todo dti;   rE;   i=E;   dtfi(F);   dti;N   rE;N   i=E;N   dtfi(F);N
				Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
				Rule::Chain(3, TS('r'), NS('E'), TS(';')),
				Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
				Rule::Chain(4, TS('s'), TS('='), NS('E'), TS(';')),
				Rule::Chain(5, TS('s'), TS('='), NS('E'), TS(';'), NS('N')),
				Rule::Chain(4, TS('n'), TS('='), NS('E'), TS(';')),
				Rule::Chain(4, TS('n'), TS('='), NS('E'), TS(';'), NS('N')), 

				Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
				Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('s'), TS('('), NS('F'), TS(')'), TS(';')),
				Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('c'), TS('('), NS('F'), TS(')'), TS(';')),
				Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('n'), TS('('), NS('F'), TS(')'), TS(';')),
				Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
				Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
				Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
				Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
				Rule::Chain(8, TS('d'), TS('f'), TS('s'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
				Rule::Chain(8, TS('d'), TS('f'), TS('n'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
				Rule::Chain(8, TS('d'), TS('f'), TS('c'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
				Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
				Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
				Rule::Chain(3, TS('p'), TS('i'), TS(';')),
				Rule::Chain(3, TS('p'), TS('l'), TS(';')),
				Rule::Chain(6, TS('p'), TS('i'), TS('('), NS('W'), TS(')'), TS(';')),
				Rule::Chain(5, TS('c'), TS('('), NS('W'), TS(')'), TS(';')),
				Rule::Chain(6, TS('c'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
				Rule::Chain(8, TS('w'), TS('('), TS('i'), TS(')'), TS('['), NS('N'), TS(']'), TS(';')),
				Rule::Chain(9, TS('w'), TS('('), TS('i'), TS(')'), TS('['), NS('N'), TS(']'), TS(';'), NS('N'))
			),
			Rule(NS('E'), GRB_ERROR_SERIES + 2,
				12, //todo i   l   (E)   i(W)   iM   lM   (E)M   i(W)M
				Rule::Chain(1, TS('i')),
				Rule::Chain(1, TS('l')),
				Rule::Chain(3, TS('('), NS('E'), TS(')')),
				Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
				Rule::Chain(4, TS('s'), TS('('), NS('W'), TS(')')),
				Rule::Chain(4, TS('n'), TS('('), NS('W'), TS(')')),
				Rule::Chain(2, TS('i'), NS('M')),
				Rule::Chain(2, TS('l'), NS('M')),
				Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
				Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
				Rule::Chain(2, TS('-'), TS('i')),
				Rule::Chain(2, TS('+'), TS('i'))
			),
			Rule(NS('M'), GRB_ERROR_SERIES + 3,
				20, //todo vE    vEM   v(E) v(E)M
				Rule::Chain(2, TS('+'), NS('E')),
				Rule::Chain(4, TS('+'), TS('('), NS('E'), TS(')')),
				Rule::Chain(5, TS('+'), TS('('), NS('E'), TS(')'), NS('M')),
				Rule::Chain(3, TS('+'), NS('E'), NS('M')),
				Rule::Chain(2, TS('-'), NS('E')),
				Rule::Chain(4, TS('-'), TS('('), NS('E'), TS(')')),
				Rule::Chain(5, TS('-'), TS('('), NS('E'), TS(')'), NS('M')),
				Rule::Chain(3, TS('-'), NS('E'), NS('M')),
				Rule::Chain(2, TS('*'), NS('E')),
				Rule::Chain(4, TS('*'), TS('('), NS('E'), TS(')')),
				Rule::Chain(5, TS('*'), TS('('), NS('E'), TS(')'), NS('M')),
				Rule::Chain(3, TS('*'), NS('E'), NS('M')),
				Rule::Chain(2, TS('/'), NS('E')),
				Rule::Chain(4, TS('/'), TS('('), NS('E'), TS(')')),
				Rule::Chain(5, TS('/'), TS('('), NS('E'), TS(')'), NS('M')),
				Rule::Chain(3, TS('/'), NS('E'), NS('M')),
				Rule::Chain(2, TS('%'), NS('E')),
				Rule::Chain(4, TS('%'), TS('('), NS('E'), TS(')')),
				Rule::Chain(5, TS('%'), TS('('), NS('E'), TS(')'), NS('M')),
				Rule::Chain(3, TS('%'), NS('E'), NS('M'))
			),
			Rule(NS('F'), GRB_ERROR_SERIES + 4,
				2, //todo ti   ti,F
				Rule::Chain(2, TS('t'), TS('i')),
				Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
			),
			Rule(NS('W'), GRB_ERROR_SERIES + 5,
				4, //todo i   l   i,W   l,W
				Rule::Chain(1, TS('i')),
				Rule::Chain(1, TS('l')),
				Rule::Chain(3, TS('i'), TS(','), NS('W')),
				Rule::Chain(3, TS('l'), TS(','), NS('W'))
			)
		);
#pragma endregion
		return greibach;
	}
	Greibach getGreibach() { return Greibach::initGreibach(); };
	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1, i = 0;
		while (i < size && rules[i].nn != pnn)
			i++;
		rc = i < size ? i : -1;
		prule = rules[rc];
		return rc;
	};
	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	}
	std::string Rule::getCRule(short nchain)
	{
		std::string bchain = "";
		bchain += Chain::alphabet_to_char(nn);
		bchain += '-';
		bchain += '>';
		bchain += chains[nchain].getCChain();
		return bchain;
	};
	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = j < size ? j : -1;
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	};
	std::string Rule::Chain::getCChain()
	{
		std::string b = "";
		for (int i = 0; i < size; i++)
			b.push_back(Chain::alphabet_to_char(nt[i]));
		return b;
	};
};