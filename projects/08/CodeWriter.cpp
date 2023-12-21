#include "CodeWriter.h"

void CodeWriter::writeArithmetic(string command) {
    cout << command.length() << endl;
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
            cout << "SUBBING" << endl;
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
        if(segment == "static") {
            out << "@" << curFileName << "." << index << endl;
            out << "D=M" << endl;
        } else {
            out << "@" << index << endl;
            out << "D=A" << endl;

            if(segment != "constant") {
                if(segment == "pointer") {
                    out << "@" << 3 << endl;
                    out << "A=A+D" << endl;
                    out << "D=M" << endl;
                } else if(segment == "temp") {
                    out << "@" << 5 << endl;
                    out << "A=A+D" << endl;
                    out << "D=M" << endl;
                } else {
                    out << segments[segment] << endl;
                    out << "A=D+M"  << endl;
                    out << "D=M" << endl;
                }
            }
        }

        // Load D onto top of stack
        out << "@SP" << endl;
        out << "A=M" << endl;
        out << "M=D" << endl;
        out << "@SP" << endl;
        out << "M=M+1" << endl; // Iterate the given pointer to the top
    } else if (command == c_pop) {
        if(segment == "pointer") {
            out << "@" << index << endl;
            out << "D=A" << endl;
            out << "@" << 3 << endl;
            out << "D=D+A" << endl;
        } else if(segment == "temp") {
            out << "@" << index << endl;
            out << "D=A" << endl;
            out << "@" << 5 << endl;
            out << "D=D+A" << endl;
        } else if(segment == "static") {
            out << "@" << curFileName << "." << index << endl;
            out << "D=A" << endl;    
        } else {
            out << segments[segment] << endl;
            out << "D=M" << endl;
            out << "@" << index << endl;
            out << "D=D+A" << endl;
        }
        out << "@R13" << endl;
        out << "M=D" << endl; // Temporarily store desired adress in R13
        out << "@SP" << endl;
        out << "AM=M-1" << endl; // Decrement and store stack pointer
        out << "D=M" << endl; // Store top of stack in D
        out << "@R13" << endl;
        out << "A=M" << endl;
        out << "M=D" << endl; // Store D into desired location
    }
}

void CodeWriter::writeLabel(string label) {
    out << "(" << curFileName << "$" << label << ")" << endl;
}

void CodeWriter::writeIf(string label) {
    out << "@SP" << endl;
    out << "AM=M-1" << endl; // Decrease SP and pop top of stack
    out << "D=M" << endl; // Store top of stack
    out << "@" << curFileName << "$" << label << endl;
    out << "D;JNE" << endl; // Jump if not 0
}

void CodeWriter::writeGoto(string label) {
    out << "@" << curFileName << "$" << label << endl;
    out << "0;JMP" << endl;
}