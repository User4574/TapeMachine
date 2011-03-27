#include <stdlib.h>
#include <stdio.h>
#include "vm.h"

int main(int argc, char** argv) {
	checkArgs(&argc, argv);

	int end = atoi(argv[1]) - 1, length = 0, programCounter = 0, head = 0;
	char* tape = calloc(end + 1, sizeof(char));
	char* program;
	
	readProgram(argv[2], &program, &length);

	int rc = execute(end, length, programCounter, head, tape, program);
	printError(rc);

	free(tape);
	free(program);

	return 0;
}

void printError(int rc) {
	switch(rc) {
		case rOk:
			break;
		case rErrorTapeRunoff:
			fprintf(stderr, "+ ERROR: Tape Runoff\n+ Immediate execution cessation\n");
			break;
		case rErrorProgramRunoff:
			fprintf(stderr, "+ ERROR: Program Runoff\n+ Immediate execution cessation\n");
			break;
		case rErrorNotAnInstruction:
			fprintf(stderr, "+ ERROR: Invalid Instruction\n+ Immediate execution cessation\n");
			break;
		default:
			fprintf(stderr, "+ ERROR %d: Invalid Error, WTF?\n+ Immediate execution cessation\n", rc);
			break;
	}
}

void checkArgs(int* argc, char** argv) {
	if(*argc != 3) {
		fprintf(stderr, "Usage:\n\tvm <tape length> <bytecode>\n+ Could not start machine.\n");
		exit(1);
	}
	FILE* file = fopen(argv[2], "r");
	if(!file) {
		fprintf(stderr, "+ File '%s' does not exist.\n+ Could not start machine.\n", argv[2]);
		exit(1);
	}
	fclose(file);
	return;
}

void readProgram(char* filename, char** program, int* length) {
	FILE* file = fopen(filename, "r");
	fseek(file, 0, SEEK_END);
	*length = ftell(file);
	fseek(file, 0, SEEK_SET);
	*program = calloc(*length, sizeof(char));
	fread(*program, *length, 1, file);
	fclose(file);
	return;
}

int execute(int end, int length, int programCounter, int head, char* tape, char* program) {
	char instruction = iNop, argument = 0, temp = 0;
	while(programCounter <= length) {
		instruction = program[programCounter++];
		switch(instruction) {
			case iNop:
				break;
			case iLeft:
				head--;
				if(head < 0) return rErrorTapeRunoff;
				break;
			case iLeftX:
				argument = program[programCounter++];
				head -= argument;
				if(head < 0) return rErrorTapeRunoff;
				break;
			case iRight:
				head++;
				if(head > end) return rErrorTapeRunoff;
				break;
			case iRightX:
				argument = program[programCounter++];
				head += argument;
				if(head > end) return rErrorTapeRunoff;
				break;
			case iIncr:
				tape[head]++;
				break;
			case iAddX:
				argument = program[programCounter++];
				tape[head] += argument;
				break;
			case iDecr:
				tape[head]--;
				break;
			case iSubX:
				argument = program[programCounter++];
				tape[head] -= argument;
				break;
			case iSet:
				tape[head] = 0;
				break;
			case iSetX:
				argument = program[programCounter++];
				tape[head] = argument;
				break;
			case iIn:
				read(0, &(tape[head]), 1);
				break;
			case iOut:
				write(1, &(tape[head]), 1);
				break;
			case iInX:
				argument = program[programCounter++];
				read((int)argument, &(tape[head]), 1);
				break;
			case iOutX:
				argument = program[programCounter++];
				write((int)argument, &(tape[head]), 1);
				break;
			case iErr:
				write(2, &(tape[head]), 1);
				break;
			case iJrX:
				argument = program[programCounter++];
				programCounter += (int)argument;
				if((programCounter < 0) || (programCounter > length)) return rErrorProgramRunoff;
				break;
			case iJrnzX:
				if(tape[head] == 0) {
					programCounter++;
					break;
				}
				argument = program[programCounter++];
				programCounter += (int)argument;
				if((programCounter < 0) || (programCounter > length)) return rErrorProgramRunoff;
				break;
			case iJpX:
				argument = program[programCounter++];
				programCounter += (int)argument;
				if((programCounter < 0) || (programCounter > length)) return rErrorProgramRunoff;
				break;
			case iJpnzX:
				if(tape[head] == 0) {
					programCounter++;
					break;
				}
				argument = program[programCounter++];
				programCounter = (int)argument;
				if((programCounter < 0) || (programCounter > length)) return rErrorProgramRunoff;
				break;
			case iCopy:
				temp = tape[head];
				head++;
				if(head > end) return rErrorTapeRunoff;
				tape[head] = temp;
				break;
			case iCopyX:
				temp = tape[head];
				argument = program[programCounter++];
				head += argument;
				if((head < 0) || (head > end)) return rErrorTapeRunoff;
				tape[head] = temp;
				break;
			case iMove:
				temp = tape[head];
				tape[head] = 0;
				head++;
				if(head > end) return rErrorTapeRunoff;
				tape[head] = temp;
				break;
			case iMoveX:
				temp = tape[head];
				tape[head] = 0;
				argument = program[programCounter++];
				head += argument;
				if((head < 0) || (head > end)) return rErrorTapeRunoff;
				tape[head] = temp;
				break;
			case iSwap:
				temp = tape[head];
				head++;
				if(head > end) return rErrorTapeRunoff;
				tape[head - 1] = tape[head];
				tape[head] = temp;
				break;
			case iSwapX:
				temp = tape[head];
				argument = program[programCounter++];
				head += argument;
				if((head < 0) || (head > end)) return rErrorTapeRunoff;
				tape[head - argument] = tape[head];
				tape[head] = temp;
				break;
			case iHalt:
				return rOk;
				break;
			default:
				return rErrorNotAnInstruction;
				break;
		}
	}
	return rOk;
}
