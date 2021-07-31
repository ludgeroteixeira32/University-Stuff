#include <stdio.h>
#include <stdlib.h>

// == Global data =============================================================

#define W  * 4
#define KB * 1024
#define MB KB KB

#define DATA_SZ   1 MB
#define HEAP_SZ   1 MB
#define STACK_SZ  1 MB

#define MEM_SZ ((DATA_SZ) + (HEAP_SZ) + (STACK_SZ))

union {
  long mem[0];
  struct {
    long m_dots[1];
    long m_spaces[1];
    long m_temp_spaces[1];
    long m_temp_dots[1];
  } named;
  struct {
    long z_data[DATA_SZ];
    long z_heap[HEAP_SZ];
    long z_stack[STACK_SZ];
  } zone;
} global;

#define M      global.mem
#define DATA   global.zone.z_data
#define HEAP   global.zone.z_heap
#define STACK  global.zone.z_stack

long SP = MEM_SZ;
long FP = 0;
long SR;
void *PC;				// (unused)

// -- Names for global variables ----------------------------------------------

#define GV_dots ((long *) &global.named.m_dots - (long *) &global.named)
#define GV_spaces ((long *) &global.named.m_spaces - (long *) &global.named)
#define GV_temp_spaces ((long *) &global.named.m_temp_spaces - (long *) &global.named)
#define GV_temp_dots ((long *) &global.named.m_temp_dots - (long *) &global.named)

// == Program =================================================================

int main (int argc, char *argv[])
{
  long i;

// -- Initialization ----------------------------------------------------------
  for (i=0; i<1; ++i) global.named.m_dots[i] = 0;
  for (i=0; i<1; ++i) global.named.m_spaces[i] = 0;
  for (i=0; i<1; ++i) global.named.m_temp_spaces[i] = 0;
  for (i=0; i<1; ++i) global.named.m_temp_dots[i] = 0;

// -- Library -----------------------------------------------------------------

	goto lib_init;			// skip library code!

print_int:				// print_int (int) -> ()
	printf ("%ld\n", M[SP+1]);
	goto * ((void *) M[SP++]);

print_char:				// print_char (int) -> ()
	putchar (M[SP+1]);
	goto * ((void *) M[SP++]);

read_int:				// read_int () -> int
	scanf ("%ld", &M[SP+1]);
	goto * ((void *) M[SP++]);

read_char:				// read_char () -> int
	M[SP+1] = getchar ();
	goto * ((void *) M[SP++]);

halt:					// halt () -> ()
	return 0;

dump_regs:				// dump_regs () -> ()
	{
	  printf ("-- Register dump --\n");
	  printf ("SP = 0x%lx (%ld)\n", (long) SP, (long) SP);
	  printf ("FP = 0x%lx (%ld)\n", (long) FP, (long) FP);
	  printf ("SR = 0x%lx (%ld)\n", (long) SR, (long) SR);
	  printf ("PC = (unused)\n");
	}
	goto * ((void *) M[SP++]);

dump_stack:				// dump_stack () -> ()
	{
	  printf ("-- Stack dump --\n");
	}
	goto * ((void *) M[SP++]);

stack_trace:				// stack_trace () -> ()
	{
	  printf ("-- Stack trace --\n");
	}
	goto * ((void *) M[SP++]);

lib_init:
	{
	  // (declarations for function ) (print_int);
	  // (declarations for function ) (print_char);
	  // (declarations for function ) (read_int);
	  // (declarations for function ) (read_char);
	  // (declarations for function ) (halt);
	  // (declarations for function ) (dump_regs);
	  // (declarations for function ) (dump_stack);
	  // (declarations for function ) (stack_trace);
	}

// -- Start execution ---------------------------------------------------------
  M[--SP] = (long) &&L_exit_program; // Save return address for main program
  goto program;			// start kicking...
L_exit_program:			// Return here, and...
  exit (0);			// quit.
  

// -- Instructions ------------------------------------------------------------
program:
	M[--SP] = (long) &&start;	// PUSH start
	goto * ((void *) M[SP++]);		// JUMP
pot:
	M[--SP] = 0;	// PUSH 0
	{ long N = M[SP]; M[SP]= FP; FP=SP+1; SP -= N; } // LINK
	M[--SP] = 1;	// PUSH 1
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = (long) &&l3;	// PUSH l3
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	if (! M[SP++]) goto P_12;	// SKIPZ
	goto * ((void *) M[SP++]);		// JUMP
P_12:	++SP;				// POP
	M[--SP] = 1;	// PUSH 1
	M[--SP] = 4;	// PUSH 4
	M[SP] = M[SP] + FP;		// LOCAL
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	SP=FP; FP=M[SP-1];		// UNLINK
	goto * ((void *) M[SP++]);		// JUMP
l3:
	M[--SP] = 0;	// PUSH 0
	M[--SP] = 3;	// PUSH 3
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 2;	// PUSH 2
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 1;	// PUSH 1
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 1;	// PUSH 1
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = (long) &&pot;	// PUSH pot
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_33; goto *C; } // CALL
P_33:	++SP;				// POP
	++SP;				// POP
	++SP;				// POP
	M[--SP] = 3;	// PUSH 3
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[SP+1] = M[SP+1] * M[SP+0]; ++SP; // MUL
	M[--SP] = 4;	// PUSH 4
	M[SP] = M[SP] + FP;		// LOCAL
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	SP=FP; FP=M[SP-1];		// UNLINK
	goto * ((void *) M[SP++]);		// JUMP
fact:
	M[--SP] = 0;	// PUSH 0
	{ long N = M[SP]; M[SP]= FP; FP=SP+1; SP -= N; } // LINK
	M[--SP] = 1;	// PUSH 1
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[SP-1] = M[SP]; --SP;		// DUP
	M[--SP] = (long) &&l1;	// PUSH l1
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	if (! M[SP++]) goto P_55;	// SKIPZ
	goto * ((void *) M[SP++]);		// JUMP
P_55:	++SP;				// POP
	++SP;				// POP
	M[--SP] = 1;	// PUSH 1
	M[--SP] = 2;	// PUSH 2
	M[SP] = M[SP] + FP;		// LOCAL
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	SP=FP; FP=M[SP-1];		// UNLINK
	goto * ((void *) M[SP++]);		// JUMP
l1:
	M[SP-1] = M[SP]; --SP;		// DUP
	M[--SP] = 0;	// PUSH 0
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	M[--SP] = 1;	// PUSH 1
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = (long) &&fact;	// PUSH fact
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_70; goto *C; } // CALL
P_70:	++SP;				// POP
	M[SP+1] = M[SP+1] * M[SP+0]; ++SP; // MUL
	M[--SP] = 2;	// PUSH 2
	M[SP] = M[SP] + FP;		// LOCAL
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	SP=FP; FP=M[SP-1];		// UNLINK
	goto * ((void *) M[SP++]);		// JUMP
abs:
	M[--SP] = 0;	// PUSH 0
	{ long N = M[SP]; M[SP]= FP; FP=SP+1; SP -= N; } // LINK
	M[--SP] = 0;	// PUSH 0
	M[--SP] = 1;	// PUSH 1
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[SP+1] = M[SP+1] < M[SP+0]; ++SP; // SLT
	M[--SP] = (long) &&lendabs;	// PUSH lendabs
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	if (! M[SP++]) goto P_88;	// SKIPZ
	goto * ((void *) M[SP++]);		// JUMP
P_88:	++SP;				// POP
	M[--SP] = -1;	// PUSH -1
	M[--SP] = 1;	// PUSH 1
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[SP+1] = M[SP+1] * M[SP+0]; ++SP; // MUL
	M[--SP] = 2;	// PUSH 2
	M[SP] = M[SP] + FP;		// LOCAL
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	SP=FP; FP=M[SP-1];		// UNLINK
	goto * ((void *) M[SP++]);		// JUMP
lendabs:
	M[--SP] = 1;	// PUSH 1
	M[SP] = M[SP] + FP;		// LOCAL
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 2;	// PUSH 2
	M[SP] = M[SP] + FP;		// LOCAL
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	SP=FP; FP=M[SP-1];		// UNLINK
	goto * ((void *) M[SP++]);		// JUMP
start:
	M[--SP] = 1;	// PUSH 1
	M[--SP] = GV_dots;	// PUSH dots
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	M[--SP] = 30;	// PUSH 30
	M[--SP] = GV_spaces;	// PUSH spaces
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
l0start:
	M[--SP] = GV_spaces;	// PUSH spaces
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 0;	// PUSH 0
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = 0;	// PUSH 0
	M[SP+1] = M[SP+1] < M[SP+0]; ++SP; // SLT
	M[--SP] = (long) &&l0do;	// PUSH l0do
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	if (! M[SP++]) goto P_124;	// SKIPZ
	goto * ((void *) M[SP++]);		// JUMP
P_124:	++SP;				// POP
	M[--SP] = (long) &&l0end;	// PUSH l0end
	goto * ((void *) M[SP++]);		// JUMP
l0do:
	M[--SP] = GV_spaces;	// PUSH spaces
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = GV_temp_spaces;	// PUSH temp_spaces
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
l1start:
	M[--SP] = GV_temp_spaces;	// PUSH temp_spaces
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 0;	// PUSH 0
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = 0;	// PUSH 0
	M[SP+1] = M[SP+1] < M[SP+0]; ++SP; // SLT
	M[--SP] = (long) &&l1do;	// PUSH l1do
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	if (! M[SP++]) goto P_142;	// SKIPZ
	goto * ((void *) M[SP++]);		// JUMP
P_142:	++SP;				// POP
	M[--SP] = (long) &&l1end;	// PUSH l1end
	goto * ((void *) M[SP++]);		// JUMP
l1do:
	M[--SP] = 32;	// PUSH 32
	M[--SP] = (long) &&print_char;	// PUSH print_char
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_148; goto *C; } // CALL
P_148:	++SP;				// POP
	M[--SP] = GV_temp_spaces;	// PUSH temp_spaces
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 1;	// PUSH 1
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = GV_temp_spaces;	// PUSH temp_spaces
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	M[--SP] = (long) &&l1start;	// PUSH l1start
	goto * ((void *) M[SP++]);		// JUMP
l1end:
	M[--SP] = GV_dots;	// PUSH dots
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = GV_temp_dots;	// PUSH temp_dots
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
l2start:
	M[--SP] = GV_temp_dots;	// PUSH temp_dots
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 0;	// PUSH 0
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = 0;	// PUSH 0
	M[SP+1] = M[SP+1] < M[SP+0]; ++SP; // SLT
	M[--SP] = (long) &&l2do;	// PUSH l2do
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	if (! M[SP++]) goto P_172;	// SKIPZ
	goto * ((void *) M[SP++]);		// JUMP
P_172:	++SP;				// POP
	M[--SP] = (long) &&l2end;	// PUSH l2end
	goto * ((void *) M[SP++]);		// JUMP
l2do:
	M[--SP] = 46;	// PUSH 46
	M[--SP] = (long) &&print_char;	// PUSH print_char
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_178; goto *C; } // CALL
P_178:	++SP;				// POP
	M[--SP] = GV_temp_dots;	// PUSH temp_dots
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 1;	// PUSH 1
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = GV_temp_dots;	// PUSH temp_dots
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	M[--SP] = (long) &&l2start;	// PUSH l2start
	goto * ((void *) M[SP++]);		// JUMP
l2end:
	M[--SP] = 10;	// PUSH 10
	M[--SP] = (long) &&print_char;	// PUSH print_char
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_190; goto *C; } // CALL
P_190:	++SP;				// POP
	M[--SP] = GV_dots;	// PUSH dots
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 2;	// PUSH 2
	M[SP+1] = M[SP+1] + M[SP+0]; ++SP; // ADD
	M[--SP] = GV_dots;	// PUSH dots
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	M[--SP] = GV_spaces;	// PUSH spaces
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 1;	// PUSH 1
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = GV_spaces;	// PUSH spaces
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	M[--SP] = (long) &&l0start;	// PUSH l0start
	goto * ((void *) M[SP++]);		// JUMP
l0end:
	M[--SP] = 29;	// PUSH 29
	M[--SP] = GV_spaces;	// PUSH spaces
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
l3start:
	M[--SP] = GV_spaces;	// PUSH spaces
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 0;	// PUSH 0
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = 0;	// PUSH 0
	M[SP+1] = M[SP+1] < M[SP+0]; ++SP; // SLT
	M[--SP] = (long) &&l3do;	// PUSH l3do
	M[SP-1] = M[SP]; M[SP] = M[SP+1]; M[SP+1]=M[SP-1]; // SWAP
	if (! M[SP++]) goto P_219;	// SKIPZ
	goto * ((void *) M[SP++]);		// JUMP
P_219:	++SP;				// POP
	M[--SP] = (long) &&l3end;	// PUSH l3end
	goto * ((void *) M[SP++]);		// JUMP
l3do:
	M[--SP] = 32;	// PUSH 32
	M[--SP] = (long) &&print_char;	// PUSH print_char
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_225; goto *C; } // CALL
P_225:	++SP;				// POP
	M[--SP] = GV_spaces;	// PUSH spaces
	M[SP] = M[M[SP]];		// LOAD
	M[--SP] = 1;	// PUSH 1
	M[SP+1] = M[SP+1] - M[SP+0]; ++SP; // SUB
	M[--SP] = GV_spaces;	// PUSH spaces
	M[M[SP]] = M[SP+1]; SP += 2;	// STORE
	M[--SP] = (long) &&l3start;	// PUSH l3start
	goto * ((void *) M[SP++]);		// JUMP
l3end:
	M[--SP] = 69;	// PUSH 69
	M[--SP] = (long) &&print_char;	// PUSH print_char
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_237; goto *C; } // CALL
P_237:	++SP;				// POP
	M[--SP] = 78;	// PUSH 78
	M[--SP] = (long) &&print_char;	// PUSH print_char
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_241; goto *C; } // CALL
P_241:	++SP;				// POP
	M[--SP] = 68;	// PUSH 68
	M[--SP] = (long) &&print_char;	// PUSH print_char
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_245; goto *C; } // CALL
P_245:	++SP;				// POP
	M[--SP] = 10;	// PUSH 10
	M[--SP] = (long) &&print_char;	// PUSH print_char
	{ void *C = (void *) M[SP]; M[SP]=(long)&&P_249; goto *C; } // CALL
P_249:	++SP;				// POP

}

