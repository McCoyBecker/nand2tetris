// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

    @SCREEN     // Clear screen initially
    M = 0

    (LOOP)      // Loop to listen to screen
        @24576
        D = M
        @BLACKEN
        D;JNE
        @WHITEN
        D;JEQ

    (BLACKEN)
        @SCREEN
        M = -1
        @LOOP
        0;JEQ

    (WHITEN)
        @SCREEN
        M = 0
        @LOOP
        0;JEQ


