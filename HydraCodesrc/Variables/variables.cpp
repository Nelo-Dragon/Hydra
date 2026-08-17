#include "HydraCodesrc/Variables/variables.h"

#include <iostream>
#include <string>
#include <vector>


void VarSys::Set(const std::string& name, const std::string& value) {

    VarSys::vars[name] = value;
}

void VarSys::Kill(const std::string& name) {

    vars.erase(name);
}


VarCheck VarSys::IsVar(const std::string& arg) {

    VarCheck var;

    if (arg[0] == '$') {

        var.var = true;
        var.name = arg;
        var.name.erase(0, 1);
        return var;
    }
    else {
        var.var = false;
    }

    return var;
}



std::string VarSys::Get(const std::string& name) {

    auto it = vars.find(name);

    if (it != vars.end()) {
        return it->second;
    }
    
    return "";
}


