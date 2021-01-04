
    #include <string>
    extern "C" {const char * getModuleDescriptor ();}

    const char * getModuleDescriptor () {
    return
    #include "mnscmodule.kmd.json"
;}