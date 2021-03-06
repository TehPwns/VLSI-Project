#ifndef STD_CELL_H
#define STD_CELL_H

#include <vector>
#include <map>
#include <string>

struct stdcell
{
    std::string name;
    float width = 0;
    float length = 0;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
};

//stdcell output operator
std::ostream& operator<<(std::ostream& os, const stdcell& d);

/******************************************************************/

/* Class to hold a standard cell library from a Matt Cell File
 * into a map, indexed by name.
 * Overloaded [] operator to access stdcell structures.
 * See `stdcell_test.cpp` for usage
 */

class MattCellFile
{
public:
    //Construct and load cell definitions from a file
    MattCellFile(const std::string& filename);

    //Lookup a standard cell definition by name
    const stdcell& operator[](const std::string& cell_name) const;

private:
    //Output operator
    friend std::ostream& operator<<(std::ostream& os, const MattCellFile& mc);
    
    //Parses a stdcell from a line
    void readCell(std::istream& is, stdcell& d, int lineNumber);

    //Data members
    std::map<std::string, stdcell> cells;
    std::string cellfilename;
};


/******************************************************************/

#endif
