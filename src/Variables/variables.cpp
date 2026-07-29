#include "src/Variables/variables.h"

#include <iostream>
#include <string>
#include <vector>


void VarSys::Set(const std::string& name, const std::string& value) {

    VarSys::vars[name] = value;
}



std::string VarSys::Get(const std::string& name) {

    auto it = vars.find(name);

    if (it != vars.end()) {
        return it->second;
    }
    
    return "";
}


