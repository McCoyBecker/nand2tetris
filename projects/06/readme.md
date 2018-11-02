# Structure of the assembler.

Here's how my assembler is structured.

1. There's a symbol table class which deals with assigning symbols to memory address, etc. It supports user-defined symbols as well.
2. There's a parser module which first scans the input .asm file. It converts everything to symbols in the symbol table.
3. There's a translation module which scans the input .asm file and uses the symbol table lookup to convert symbols to addresses and binary instructions. During translation, if the module encounters an undefined address symbol, it adds it to the symbol table, beginning at memory address 16 and incrementing.
4. The main() function allows the user to specify what file to assemble, as well as to do query the symbol table after translation is complete.
