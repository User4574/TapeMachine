void checkArgs(int* argc, char** argv);
void readProgram(char* filename, char** program, int* length);
int execute(int end, int length, int programCounter, int head, char* tape, char* program);
void printError(int rc);

#define iLeft 0x10
#define iLeftX 0x11
#define iRight 0x12
#define iRightX 0x13
#define iIncr 0x20
#define iAddX 0x21
#define iDecr 0x22
#define iSubX 0x23
#define iSet 0x24
#define iSetX 0x25
#define iIn 0x30
#define iInX 0x31
#define iOut 0x32
#define iOutX 0x33
#define iErr 0x34
#define iJrX 0x40
#define iJrnzX 0x41
#define iJpX 0x42
#define iJpnzX 0x43
#define iCopy 0x50
#define iCopyX 0x51
#define iMove 0x52
#define iMoveX 0x53
#define iSwap 0x54
#define iSwapX 0x55
#define iDiv 0x60
#define iMult 0x61
#define iMod 0x62
#define iNop 0x00
#define iHalt 0x01

#define rOk 0
#define rErrorTapeRunoff 1
#define rErrorProgramRunoff 2
#define rErrorNotAnInstruction 3
