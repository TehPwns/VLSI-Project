#include <iostream>
#include "stdcell.h"
#include "padframe.h"
#include "floorplan.h"
#include "module.h"
#include "utility.h"
#include "kerninghan.h"
#include "output.h"

#if 1
int main(int argc, char** argv)
{
    //If not enough arguments print usage
    if(argc < 4) {
        std::cout
            << "Usage: " << argv[0]
            << " <stdcell file> <module file> <padframe file>" << std::endl;
        return 1;
    }

    srand(time(NULL));

    try 
    {
        //Loads all files and information
        MattCellFile cells(argv[1]);
        std::vector<module> modules = readModuleFile(argv[2], cells);
        PadframeFile f(argv[3]);

        //Partition module into slice-sizes modules
        std::cout << "Partitioning..." << std::endl;
        std::vector<module> partitions = kerninghanLinPadframeSlice(modules[0], f);

        //Floorplan all modules
        std::cout << "Floorplanning..." << std::endl;
        auto polishes = floorplan_all(partitions);

        //Write out unity
        UnityFile unity("unity.out");
        unity.write(partitions, polishes);

        //Print out results
        for(polish_string& s : polishes)
            std::cout << s << std::endl;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
#endif
