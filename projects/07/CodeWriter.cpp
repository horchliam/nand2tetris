#include "CodeWriter.h"

void CodeWriter::writeArithmetic(string command) {
    // Load the top of the stack into D register
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;

    if(command == "neg") {
        out << "D=!D" << endl;
        out << "D=D+1" << endl;
    } else if(command == "not") {
        out << "D=!D" << endl;
    } else {
        // Load the second value's address into the A register
        out << "@SP" << endl;
        out << "M=M-1" << endl;
        out << "@SP" << endl;
        out << "A=M" << endl;

        if(command == "add") {
            out << "D=D+M" << endl;
        } else if(command == "sub") {
            out << "D=M-D" << endl;
        } else if(command == "and") {
            out << "D=D&M" << endl;
        } else if(command == "or") {
            out << "D=D|M" << endl;
        } else if(command == "eq") {
            out << "D=D-M" << endl;
            out << "@eq_" << eqCounter << endl;
            out << "D;JEQ" << endl; // If D-M == 0 then true, which is -1
            out << "D=0" << endl; 
            out << "@not_eq_" << eqCounter << endl;
            out << "0;JMP" << endl;
            out << "(eq_" << eqCounter << ")" << endl;
            out << "D=-1" << endl;
            out << "(not_eq_" << eqCounter++ << ")" << endl;
        } else if(command == "lt") {
            out << "D=M-D" << endl;
            out << "@lt_" << ltCounter << endl;
            out << "D;JLT" << endl;
            out << "D=0" << endl;
            out << "@not_lt_" << ltCounter << endl;
            out << "0;JMP" << endl;
            out << "(lt_"  << ltCounter << ")" << endl;
            out << "D=-1" << endl;
            out << "(not_lt_" << ltCounter++ << ")" << endl;
        } else if(command == "gt") {
            out << "D=M-D" << endl;
            out << "@gt_" << gtCounter << endl;
            out << "D;JGT" << endl;
            out << "D=0" << endl;
            out << "@not_gt_" << gtCounter << endl;
            out << "0;JMP" << endl;
            out << "(gt_"  << gtCounter << ")" << endl;
            out << "D=-1" << endl;
            out << "(not_gt_" << gtCounter++ << ")" << endl;
        }
    }

    // Load D into where the stack pointer currently points
    out << "@SP" << endl;
    out << "A=M" << endl;
    out << "M=D" << endl;
    out << "@SP" << endl;
    out << "M=M+1" << endl; // Iterate the stack pointer to the top of the stack
}

void CodeWriter::writePushPop(CommandType command, string segment, int index) {
    if (command == c_push) {
        out << "@" << index << endl;
        out << "D=A" << endl;
        out << segments[segment] << endl;
        out << "A=M" << endl;
        out << "M=D" << endl;
        out << segments[segment] << endl;
        out << "M=M+1" << endl; // Iterate the given pointer to the top
    } else if (command == c_pop) {
        
    }
}