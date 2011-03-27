.PHONY:	clean all tar
COM=vmc
MAC=vm
TAR=is.txt vm.c vm.h vmc.l vmc.y Makefile

all:		${COM} ${MAC}

${MAC}:		${MAC}.c ${MAC}.h
		gcc -o $@ $^

${COM}:		${COM}.tab.o lex.yy.o
		gcc -o $@ $^ -lfl

%.o:		%.c ${COM}.tab.h
		gcc -c $^

${COM}.tab.h:	${COM}.y
		bison -d ${COM}.y

lex.yy.c:	${COM}.l
		flex ${COM}.l

${COM}.tab.c:	${COM}.y
		bison ${COM}.y

clean:
		rm *.tab.* *.yy.* ${COM} ${MAC}

tar:		${TAR}
		tar -czvf tapemachine.tar.gz $^
