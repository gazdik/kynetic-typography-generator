#ifndef KINETYPOGEN_H
#define KINETYPOGEN_H

#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>
#include <streambuf>
#include <string>

#include "sequencerunner.h"
#include "effect.h"

// Effects
#include "testeffect.h"

class KineTypoGen
{
public:
    KineTypoGen(int& argc, char* argv[]);
    int run();
private:
    std::string str;
};

#endif // KINETYPOGEN_H
