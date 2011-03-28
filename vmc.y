%{
#include <stdio.h>
#include <stdlib.h>

int lineno=1;
extern char* yytext;

int tmp, tval;

%}

%token tLeft tRight tIncr tAdd tDecr tSub tSet tIn tOut tEr tJr tJrnz tJp tJpnz tCopy tMove tSwap tDiv tMult tMod tNop tHalt tNum tErr

%%

start:	start input		{ ++lineno; }
	| input			{ ++lineno; }
	;

input:	tLeft			{ putchar(0x10); }
	| tLeft tNum		{ putchar(0x11); putchar($2); }
	| tRight		{ putchar(0x12); }
	| tRight tNum		{ putchar(0x13); putchar($2); }
	| tIncr			{ putchar(0x20); }
	| tAdd tNum		{ putchar(0x21); putchar($2); }
	| tDecr			{ putchar(0x22); }
	| tSub tNum		{ putchar(0x23); putchar($2); }
	| tSet			{ putchar(0x24); }
	| tSet tNum		{ putchar(0x25); putchar($2); }
	| tIn			{ putchar(0x30); }
	| tIn tNum		{ putchar(0x31); putchar($2); }
	| tOut			{ putchar(0x32); }
	| tOut tNum		{ putchar(0x33); putchar($2); }
	| tEr			{ putchar(0x34); }
	| tJr tNum		{ putchar(0x40); putchar($2); }
	| tJrnz tNum		{ putchar(0x41); putchar($2); }
	| tJp tNum		{ putchar(0x42); putchar($2); }
	| tJpnz tNum		{ putchar(0x43); putchar($2); }
	| tCopy			{ putchar(0x50); }
	| tCopy tNum		{ putchar(0x51); putchar($2); }
	| tMove			{ putchar(0x52); }
	| tMove tNum		{ putchar(0x53); putchar($2); }
	| tSwap			{ putchar(0x54); }
	| tSwap tNum		{ putchar(0x55); putchar($2); }
	| tDiv			{ putchar(0x60); }
	| tMult			{ putchar(0x61); }
	| tMod			{ putchar(0x62); }
	| tNop			{ putchar(0x00); }
	| tHalt			{ putchar(0x01); }
	;

%%
int yyerror(char* s) {
	if (yytext[0]==10) fprintf(stderr, "!!SYNTAX ERROR!! on line %d. Token read was NEWLINE.\n", lineno);
	else fprintf(stderr, "!!SYNTAX ERROR!! on line %d. Token read was \"%s\".\n", lineno, yytext);
}

int main() {
	return yyparse();
}
