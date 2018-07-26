// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Multiplies R0 and R1, stores in R2

    @R2         // Access R2
    M = 0       // Set number in memory to 0

    (LOOP)
        
        @R0             // Access R0
        D = M           // Load number in memory to D register
        @END            // Check condition to jump to end
        D;JEQ           // If D = 0, jump

        @R1             // Access R1
        D = M           // Load the number in memory at R1 onto D register

        @R2             // Access R2
        M = M + D       // Add D to the number in memory

        @R0             // Access R0
        M = M - 1       // Decrement the number in memory by 1

        @LOOP           // Else, return to top of loop by jump
        0;JMP

    (END)
    
        @END
        0;JMP // Infinite loop