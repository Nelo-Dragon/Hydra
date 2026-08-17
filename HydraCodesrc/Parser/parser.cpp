#include "HydraCodesrc/Parser/parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>



HydraError error(std::string line, int lineN, std::string token, bool inQ, bool inBS, bool inCp) {
    
    HydraError error;

    if (inBS) {

        error.Err = "Ended in '\\'.";
        error.token = line;
        error.line = lineN;
        return error;
    }
    if (inQ) {

        error.Err = "\nMissed an end quote.";
        error.token = line;
        error.line = lineN;
        return error;
    }
    if (!line.empty() && line.back() == ',') {

        error.Err = "\nEnded in nothing.";
        error.token = line;
        error.line = lineN;
        return error;
    }
    if (inCp == true) {

        error.Err = "\nArithmatic not finished.";
        error.token = line;
        error.line = lineN;
        return error;
    }
    return error;
}



std::vector<Command> ParseFile(const std::string& filename, HydraError& outErr) {

    std::vector<Command> commands;

    

    std::ifstream file(filename);

    if (!file.is_open()) { // Check if it opened the file

        outErr.Err = "Failed to open the file.";
        return {};
    }

    std::string fileLine;
    int lineN = 1;

    while (std::getline(file, fileLine)) { // Runs while theres lines to run and sets line to file

        Command cmd; // My command var
        cmd.line = lineN;
        lineN++; 

        if (fileLine.empty() || fileLine[0] == '#') { // Comments

            continue;
        }
    
        std::stringstream lineStream(fileLine); // I think this gets the first word or smthn
        std::string command;
        lineStream >> command; // pushes line stream to command
        cmd.name = command; // pushes command to args
        std::string source;
        std::string token;

        
        if (std::getline(lineStream, source)) { 

            bool inQ = false; // is in quotes
            bool inBS = false; // is in back slash/exit char
            bool inCp = false;

            HydraError err;

            for (size_t i = 0; i < source.size(); i++) { // for however long the line is, run

                if (source[i] == '#' && !inQ) { // comments

                    break;
                }

                if (inQ) { // is in quotes?

                    if (!inBS && source[i] == '\\') { // find the backslashes

                        inBS = true;
                        continue;
                    }

                    if (source[i] != '"' || inBS) { // get the current char and put in the token

                        token.push_back(source[i]);
                        inBS = false;
                    }
                    else { // finds ending quote and pushes token to args

                        cmd.args.push_back(token);
                        inCp = false;
                        token.clear();
                        inBS = false;
                        inQ = false;
                    }
                }
                else { // unquoted stuff

                    if (source[i] != '"') { // just hear for the else kinda

                        if (source[i] == '=' ||
                            source[i] == '!' ||
                            source[i] == '<' ||
                            source[i] == '>') {

                            inCp = true;

                            if (!token.empty()) {

                                cmd.args.push_back(token);
                                inCp = false;
                                token.clear();
                            }

                            token.push_back(source[i]);

                            if (i + 1 < source.size()) {

                                if (source[i + 1] == '=') {

                                    token.push_back(source[i + 1]);
                                    i++;
                                }
                            }

                            cmd.args.push_back(token);
                            token.clear();

                            continue;
                        }

                        if (source[i] != ',') { //finds the ends of arguments

                            if (source[i] != ' ') { // skips spaces and final if till push to token

                            token.push_back(source[i]);
                            }
                        }
                        else if (!token.empty()) { // found end char and pushes token to args

                            cmd.args.push_back(token);
                            inCp = false;
                            token.clear();
                        }
                    }
                    else { // found a quote and turns to quote mode
                        token.clear();
                        inQ = true;
                    }
                }

                

                
            } 

            if (!token.empty()) {

                cmd.args.push_back(token);
                inCp = false;
                token.clear();
            }

            err = error(fileLine, cmd.line, token, inQ, inBS, inCp);

            if (!err.Err.empty()) {
                outErr = err;
                return commands;
            }
        }

        commands.push_back(cmd);
    }

    file.close();
    return commands;
}

