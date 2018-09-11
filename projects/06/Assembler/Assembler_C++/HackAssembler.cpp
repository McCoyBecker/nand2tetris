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
    string output = NULL;
    for (int i = 0; i < len; i++)
    {
        int remainder = (input / (int) pow(2, i)) % 2;
        char c = remainder;
        if (c == 1)
        {
            output[len-i-1] = '1';
        }
        else
        {
            output[len-i-1] = '0';
        }
        input = input - remainder;
    }
    return(output);
}

/* Entry struct for input into symbol table. */

struct entry
{
    string symbol;
    string memory;
};

void entry_init(entry& E, string symbol, string memory)
{
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

};

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

std::string symbolTable::memory_lookup(string symbol)
{
    /* Declare an iterator. */

    std::vector<entry>::iterator it;

    /* Iterate over entries and search for input symbol. */

    for (it = entries.begin(); it != entries.end(); it++)
    {
        if (symbol.compare(it -> symbol))
        {
            return(it -> memory);
        }
    }

    /* Return NULL if not found in entries. */

    return(NULL);
}

/* Translate takes in an input line and returns the translated line. */

std::string translate(string input, symbolTable symbols)
{
    /* Instantiate output. */

    string output = NULL;

    /* Declare an index for finding various elements in the input line. */

    std::size_t found;

    /* Declare an index for removing spaces from beginning of lines. */

    std::size_t first_non_space = input.find_first_not_of(" ");

    /* Declare iterator for input. */

    std::string::iterator it;

    /* First, try addressing with symbol @. */

    if ((found = input.find_first_of("@")) != std::string::npos)
    {
        int convert_to_binary = stoi(input.substr(found, std::string::npos));
        output = binaryExpansion(convert_to_binary);
    }

    /* Now, try for calculation and memory assignment by looking for =. */

    found = input.find_first_of("=");
    if (found != std::string::npos)
    {
        /* Separate input string across the = sign. */

        string destination = input.substr(first_non_space, found);
        string calculation = input.substr(found, std::string::npos);

        /* Look up symbols in the symbol table. */

        destination = symbols.memory_lookup(destination);
        calculation = symbols.memory_lookup(calculation);

        /* Generate output. */
        
        for (int i = 0; i < sizeof(input); i++)
        {
            if (destination[i] == '1' || calculation[i] == '1')
            {
                output[i] = '1';
            }

            else
            {
                output[i] = '0';
            }
        }
    }

    /* Return output. */

    return(output);
}

/* Main. */
int main()
{
    /* Pre-defined symbols in Hack. */

    char predefined[7][7] = {"SP", "LCL", "ARG", "THIS", "THAT", "SCREEN", "KBD"};
    char predefined_mem[7][6] = {"0", "1", "2", "3", "4", "16384", "24576"};

    /* Create the default symbol table. */

    symbolTable symbols;
    for (int i = 0; i < sizeof(predefined); i++)
    {
        symbols.new_entry(predefined[i], predefined_mem[i]);
    }

    /* Declare input file and output file from user input. */

    char filename[100];
    cout << "Please enter the name of the file to be assembled\n";
    cin >> filename;
    ifstream input;
    ofstream output;
    input.open(strcat(filename, ".asm"));
    output.open(strcat(filename,".hack"));

    /* Translate line by line. */

    string line;
    if (input.is_open())
    {
        while (getline(input, line))
        {
            output << translate(line, symbols) << '\n';  
        }

        input.close();
    }

    /* Close files and clear memory. */

    output.close();

    /* End. */

    return(0);
}