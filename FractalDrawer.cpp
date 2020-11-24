// ------------------------------ includes ------------------------------
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include "Fractal.h"

// -------------------------- const definitions -------------------------
/**
 * The massage to be printed if the number of argument sent wasn't good
 */
#define ERR_USAGE "Usage: FractalDrawer <file path>"

/**
 * The massage to be printed if there was a problem with the input (invalid or non-existing file)
 */
#define ERR_INPUT "Invalid input"

/**
 * The number of arguments that the program should get
 */
#define ARGS_COUNT 2

/**
 * @brief this is the only file type that is considered valid
 */
#define NEEDED_FILE_TYPE ".csv"

// ------------------------------ functions -----------------------------

/**
 * @brief this outputs to cerr an invalid input error message, and exits with exit code of failure
 */
void inputErr()
{
    std::cerr << ERR_INPUT << std::endl;
    exit(EXIT_FAILURE);
}

/**
 * @brief this holds the wanted fractal's values- the type and dimensions of it
 */
struct NeededFractal
{
    int type;
    int dimension;
} typedef NeededFractal;

/**
 * @brief this checks if the file given is valid- that is exists and is in the wanted type
 * @param path
 */
void checkFileValid(const boost::filesystem::path &path)
{
    if (!boost::filesystem::exists(path))
    {
        inputErr();
    }
    if (path.extension() != NEEDED_FILE_TYPE)
    {
        inputErr();
    }
}

/**
 * reads file into vector with checking if holds the right value type and is in bounds
 * @param path the path to a file to read
 * @param v the vector to read the information to
 */
void readFileToVector(const boost::filesystem::path &path, std::vector<NeededFractal> &v)
{
    typedef boost::tokenizer <boost::char_separator<char>> tokenizer;
    boost::filesystem::ifstream toRead(path);
    std::string line;
    boost::char_separator<char> sep(",", " ", boost::keep_empty_tokens);
    while (std::getline(toRead, line))
    {
        if (line.empty())
        {
            inputErr();
        }
        tokenizer tok{line, sep};
        int type = 0;
        int dim = 0;
        int numTokens = 0;
        for (const auto &t: tok)
        {
            if (t.length() != 1 || t == " ")
            {
                inputErr();
            }
            if (!std::isdigit(t.c_str()[0]))
            { // I know it has the length of 1
                inputErr();
            }
            int n = std::stoi(t);
            if (numTokens == 0)
            {
                if (n > MAX_INDEX || n < MIN_INDEX)
                {
                    inputErr();
                }
                type = n;
                numTokens += 1;
            }
            else
            {
                if (numTokens != 1 || n > MAX_DIM || n < MIN_DIM)
                {
                    inputErr();
                }
                dim = n;
                numTokens += 1;
            }
        }
        if (numTokens != 2)
        {
            inputErr();
        }
        v.push_back({type, dim});
    }
}

/**
 * @brief this sends the fractal's information one by one in reversed order to the fractal
 * factory which makes them, and then this function prints them
 * @param v the vector that holds the information about the needed fractals
 */
void printFractals(std::vector<NeededFractal> v)
{
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        Fractal *f;
        f = FractalFactory::makeFractal(it->type, it->dimension);
        f->makeAndPrint();
        delete (f);
    }
}

/**
 * @brief this reads, validates and prints the fractals as needed
 * @param path the path to the file to read the information from
 */
void dealWithInput(const boost::filesystem::path &path)
{
    checkFileValid(path);
    std::vector<NeededFractal> v;
    readFileToVector(path, v);
    printFractals(v);
}


/**
 * Program's main
 * @param argc count of args
 * @param argv args values
 * @return program exit status code
 */
int main(int argc, char **argv)
{
    if (argc != ARGS_COUNT)
    {
        std::cerr << ERR_USAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    dealWithInput(boost::filesystem::path{argv[1]});
    return EXIT_SUCCESS;
}