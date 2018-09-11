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
        if (symbol.compare(it -> symbol))
        {
            return(it -> memory);
        }
    }

    /* Return NULL if not found in entries. */

    return(NULL);
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

    /* Else, return input. */
    else
    {
        return(input);
    }
    /* Return output. */

    return(output);
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