// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// Assumes that R0 >= 0, R1 >= 0, and R0 * R1 < 32768.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

@2
M=0 // Initialize the sum to 0

@0
D=M
@END
D;JEQ // If R0 is 0, we are done here

@1
D=M
@END
D;JEQ // If R1 is 0, we are done here

(LOOP)
@1
D=M
@2
M=D+M
@0
M=M-1
D=M 
@LOOP
D;JGT // If R0 > 0, keep looping

(END)
@END
0;JMP // Infinite loop acts as termination