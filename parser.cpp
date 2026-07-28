#include "parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>



ErrMes error(std::string line, int lineN, bool inQ, bool inBS) {
    ErrMes error;

    if (inBS) {

        std::cerr << line << "\n";
        std::cerr << "\nEnded in \\" << "\nLine: " << lineN;
        error.Err = "Ended in \\";
        error.token = line;
        error.line = lineN;
        return error;
    }
    if (inQ) {

        std::cerr << line << "\n";
        std::cerr << "\nMissed an end quote." << "\nLine: " << lineN;
        error.Err = "\nMissed an end quote.";
        error.token = line;
        error.line = lineN;
        return error;
    }
    return error;
}



std::vector<Command> ParseFile(const std::string& filename) {

    std::vector<Command> commands;


    std::ifstream file(filename);

    if (!file.is_open()) { // Check if it opened the file

        std::cerr << "Failed to open the file." << std::endl;
        return {};
    }

    std::string line;
    int lineN = 1;

    while (std::getline(file, line)) { // Runs while theres lines to run and sets line to file

        Command cmd; // My command var
        cmd.line = lineN;
        lineN++; 

        if (line.empty() || line[0] == '#') { // Comments

            continue;
        }
    
        std::stringstream lineStream(line); // I think this gets the first word or smthn
        std::string command;
        lineStream >> command; // pushes line stream to command
        cmd.name = command; // pushes command to args
        std::string source;
        std::string token;
        
        if (std::getline(lineStream, source)) { 

            bool inQ = false; // is in quotes
            bool inBS = false; // is in back slash/exit char

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
                        token.clear();
                        inBS = false;
                        inQ = false;
                    }
                }
                else { // unquoted stuff

                    if (source[i] != '"') { // just hear for the else kinda

                        if (source[i] != ';') { //finds the ends of arguments

                            if (source[i] != ' ') { // skips spaces and final if till push to token

                            token.push_back(source[i]);
                            }
                        }
                        else if (!token.empty()) { // found end char and pushes token to args

                            cmd.args.push_back(token);
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
                token.clear();
            }

            ErrMes err = error(token, cmd.line, inQ, inBS);

            if (!err.Err.empty()) {

                return {};
            }

            if (!cmd.args.empty()) {

                commands.push_back(cmd);
            }
        }
    }

    file.close();
    return commands;
}

