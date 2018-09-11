/* A Hack assembler written in C++. */

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

/* A function to determine the binary expansion of an integer. Returns the binary expansion in string form. */

string binaryExpansion(int input)
{
    int len = 16;
    string output;
    for (int i = 0; i < len; i++)
    {
        int remainder = (input / (int) pow(2, i)) % 2;
        if (remainder == 1)
        {
            output.push_back('1');
        }
        else
        {
            output.push_back('0');
        }
        input = input - remainder;
    }
    std::reverse(output.begin(), output.end());
    return(output);
}

/* Entry struct for input into symbol table. */

struct entry
{
    /* An entry consists of a symbol and a memory location. */

    string symbol;
    string memory;
};

void entry_init(entry& E, string symbol, string memory)
{
    /* Initialization of an entry. */

    E.symbol = symbol;
    E.memory = memory;
}

/* Symbol table class for keeping track of pre-defined and user-implemented symbols. */

class symbolTable
{
    /* Declare a vector of entries. */

    private:

    vector<entry> entries;

    /* Declare accessor functions. */

    public:

    string memory_lookup(string symbol);
    void new_entry(string symbol, string memory);
    void clear_entries();
    void print_entries();

};

std::string symbolTable::memory_lookup(string symbol)
{
    /* Declare an iterator. */

    std::vector<entry>::iterator it;

    /* Iterate over entries and search for input symbol. */

    for (it = entries.begin(); it != entries.end(); it++)
    {
        if (symbol == it -> symbol)
        {
            return(it -> memory);
        }
    }

    /* Return NULL if not found in entries. */

    return("0000000000000000");
}

void symbolTable::new_entry(string symbol, string memory)
{
    entry new_association;
    entry_init(new_association, symbol, memory);
    entries.push_back(new_association);
}

void symbolTable::clear_entries()
{
    entries.clear();
}

void symbolTable::print_entries()
{
    std::vector<entry>::iterator it;
    cout << "The symbol table contains:\n";
    for (it = entries.begin(); it != entries.end(); it++)
    {
        cout << it -> symbol << " | " << it -> memory << "\n";
    }
}

symbolTable init_Hack_table()
{
    /* Pre-defined symbols in Hack. */

    string predefined[7] = {"SP", "LCL", "ARG", "THIS", "THAT", "SCREEN", "KBD"};
    string predefined_mem[7]= {"0", "1", "2", "3", "4", "16384", "24576"};

    /* Create the default symbol table. */

    symbolTable symbols;
    for (int i = 0; i < 7; i++)
    {
        symbols.new_entry(predefined[i], binaryExpansion(stoi(predefined_mem[i])));
    }

    /* Basic RAM labels. */

    string RAM[15];
    string RAM_mem[15];
    for (int j = 0; j < 16; j++)
    {
        RAM[j] = "R" + to_string(j);
        RAM_mem[j] = to_string(j);
        symbols.new_entry(RAM[j], binaryExpansion(stoi(RAM_mem[j])));
    }

    /* Binary instructions for calculations, destinations, and jumps. */

    string calculations[28] = {"0", "1", "-1", "D", "A", "!D", "!A", "-D", "-A", "D+1", "A+1", "D-1", "A-1", "D+A", "D-A", "A-D", "D&A", "D|A", "M", "!M", "-M", "M+1", "M-1", "D+M", "D-M", "M-D", "D&M", "D|M"};
    string calculations_binary[28] = {"1110101010000000", "1110111111000000", "1110111010000000", "1110001100000000","1110110000000000", "1110001101000000", "1110110001000000", "1110001111000000", "1110110011000000", "1110011111000000", "1110110111000000", "1110001110000000", "1110110010000000", "1110000010000000", "1110010011000000", "1110000111000000", "1110000000000000", "1110010101000000", "1111110000000000","1111110001000000", "1111110011000000", "1111110111000000", "1111110010000000", "1111000010000000","1111010011000000", "1111000111000000", "1111000000000000", "1111010101000000"};
    string destinations[8] = {"dest_null", "dest_M", "dest_D", "dest_MD", "dest_A", "dest_AM", "dest_AD", "dest_AMD"};
    string destinations_binary[8] = {"0000000000000000", "0000000000001000", "0000000000010000", "0000000000011000", "0000000000100000", "0000000000101000", "0000000000110000", "0000000000111000"};
    string jumps[8] = {"jmp_null", "jmp_JGT", "jmp_JEQ", "jmp_JGE", "jmp_JLT", "jmp_JNE", "jmp_JLE", "jmp_JMP"};
    string jumps_binary[8] = {"0000000000000000", "0000000000000001", "0000000000000010", "0000000000000011", "0000000000000100", "0000000000000101", "0000000000000110", "0000000000000111"};

    /* Input symbols for calculations */

    for (int j = 0; j < 28; j++)
    {
        symbols.new_entry(calculations[j], calculations_binary[j]);
    }

    /* Input symbols for destinations and jumps. */

    for (int k = 0; k < 8; k++)
    {
        symbols.new_entry(destinations[k], destinations_binary[k]);
        symbols.new_entry(jumps[k], jumps_binary[k]);
    }
    
    /* Print out the current symbol table. */

    symbols.print_entries();

    /* Return the table. */

    return(symbols);
}

/* Translate takes in an input line and returns the translated line. */

std::string translate(string input, symbolTable symbols)
{
    /* Instantiate output. */

    string output;

    /* Declare an index for finding various elements in the input line. */

    std::size_t found;

    /* Declare an index for removing spaces from beginning of lines. */

    std::size_t first_non_space = input.find_first_not_of(" ");

    /* Declare iterator for input. */

    std::string::iterator it;

    /* Destroy comments. */

    if ((found = input.find_first_of("//") != std::string::npos))
    {
        return(output);
    }

    /* First, try addressing with symbol @. */

    if ((found = input.find_first_of("@")) != std::string::npos)
    {
        int convert_to_binary = stoi(input.substr(found+1, std::string::npos));
        return(binaryExpansion(convert_to_binary));
    }

    /* Now, try for calculation and memory assignment by looking for =. */

    found = input.find_first_of("=");
    if (found != std::string::npos)
    {
        /* Slice input for easy thinking. */
        
        input = input.substr(first_non_space);

        /* Separate input string across the = sign. */

        int calculation_slice_length = input.length() - (found + 2);
        string destination = "dest_" + input.substr(0, found);
        string calculation = input.substr(found+1, calculation_slice_length);

        /* Look up symbols in the symbol table. */

        destination = symbols.memory_lookup(destination);
        calculation = symbols.memory_lookup(calculation);

        /* Generate output. */
        
        for (int i = 0; i < 16; i++)
        {
            if (destination[i] == '1' || calculation[i] == '1')
            {
                output.push_back('1');
            }

            else
            {
                output.push_back('0');
            }
        }

        return(output);
    }

    /* Else, return input. */
    else
    {
        return(input);
    }
}

/* Main. */
int main()
{
    /* Initialize the default symbol table. */

    symbolTable symbols = init_Hack_table();

    /* Declare input file and output file from user input. */

    string filename;
    cout << "Please enter the name of the file to be assembled:\n";
    cin >> filename;
    ifstream input;
    ofstream output;
    input.open(filename + ".asm");
    output.open(filename + ".hack");
    /* Translate line by line. */

    string line;
    if (input.is_open())
    {
        while (getline(input, line))
        {
            if (!translate(line, symbols).empty())
            {
                output << translate(line, symbols) << '\n'; 
            }
        }
        input.close();
    }

    /* Close files and clear memory. */

    output.close();

    /* End. */

    return(0);
}