%{
#include "vmc.tab.h"
extern int yylval;
%}
%%
[ \t\n]			/*consume*/;
left			return tLeft;
right			return tRight;

incr			return tIncr;
add			return tAdd;
decr			return tDecr;
sub			return tSub;
set			return tSet;

in			return tIn;
out			return tOut;
err			return tEr;

jr			return tJr;
jrnz			return tJrnz;
jp			return tJp;
jpnz			return tJpnz;
nop			return tNop;

copy			return tCopy;
move			return tMove;
swap			return tSwap;

div			return tDiv;
mult			return tMult;
mod			return tMod;

halt			return tHalt;

[-+]?[0-9]*		yylval=(int)strtol(yytext, NULL, 10); return tNum;
[-+]?[0-9A-Fa-f]*h	yylval=(int)strtol(yytext, NULL, 16); return tNum;
.			yylval=(int)yytext; return tErr;
