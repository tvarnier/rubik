#include "Cube.hpp"

std::vector<std::string>    Cube::parseMoves(std::string moves)
{
    std::vector<std::string> elements;
    char delimiteur = ' ';

    stringstream ss(moves);
    string sousChaine;
    while (getline(ss, sousChaine, delimiteur))
    {
        elements.push_back(sousChaine);
    }

    return elements;
}

int             Cube::parseAndMove(std::string moves)
{
    std::vector<std::string> movesArray = parseMoves(moves);
    for ( std::string m : movesArray )
        if (move(m))
            return (lib::printerr(RED, "ERROR: \"", m, "\" is not a valid Move"));
    return (0);
}