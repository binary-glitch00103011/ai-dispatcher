#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unistd.h>    // For fork() and execvp()
#include <sys/wait.h>  // For waitpid()
#include <algorithm>   // For whitespace trimming

/*
*                                                                          =
*`1010101010                                                       `10101010101.                                                      
*                                                                     `10    `10.                                                     
*  101010                                      =                      `10  =   10                                     `101`   0       
*  10`       `10      10 `10  10`     10   ,1010101,  .1010101"       `10  =  :10  10.  .10101010. `10 ,010101010'   10101` 10        
*  1010101010 `10    10` `10  1010`   10   10  _  10                  `10      01  10.  10         `10     10       10` 10  10        
*              `10  10`       10 101` 10   10  =      .10101:         `10101010'        10   10101         10      10   10  10        
*               .1010.   `10  10   10101   10     10  .10             '            10.  10      10 `10     10     ;1    10  10        
*                .10,    `10  10     101   101010101  .10101010`                   10.  1010101010 `10     10     10  0101  10101010. 
*,°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°`10,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º10.¸¸,ø¤º°`°º¤ø,`10ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤,
*`.                      `10                                                       10.             `10                                     ;
*  ¤                                              _(¯`·._.·(¯`·._.·COVENANT·._.·´¯)·._.·´¯)_                                              ¤ 
*  ø                                                                                                                                      ø
* '                                               EvinceDigital Ethical Open Source Covenant:                                              ' 
*:                                                                                                                                          :
*:           This source code is open source; you can redistribute it and/or modify it under the terms of the EvinceDigital                 : 
* °           OpenWeb Covenant as published by the EvinceDigital.                                                                           °
*  ¤                                                                                                                                      ¤     
*  ø         This source code is distributed in the hope that it will be useful,but without any assurance or guarantee or                 ø         
* '           any implied fitness for any purpos. This is not a legal document, but rather it is an ethical appeal to one's                '  
*:            sense of moral obligation. It is a request to uphold the commonly known standards of Open Source coding & some                :
*:            hard earned lessons outlined in the rest of the EvinceDigital Ethical Open Source Covenant.                                   :
* °                                                                                                                                        °
*  ¤         You should have received a copy of the EvinceDigital Ethical Open Source Covenant along with this source code; if not,       ¤
*  ø          write to the EvinceDigital leader, @ binary.glitch@gmail.com.                                                               ø
*.°                                                                                                                                        ° 
*°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º' 
*/


/*************************************************************
 * THE INSPECTOR'S TRIM: Removes leading/trailing whitespace *
 * Makes the config file forgiving if you have extra spaces. *
 *************************************************************/

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (std::string::npos == first) return str;
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

/***********************************
 * ARCHITECT'S COLLABORATOR LOADER *
 ***********************************/

struct Collaborator {
    std::vector<std::string> commandArgs;
    std::string color;
};

std::vector<std::string> splitCommand(const std::string& cmd) {
    std::vector<std::string> args;
    std::string current;
    bool inQuotes = false;
    for (char c : cmd) {
        if (c == '\"') inQuotes = !inQuotes;
        else if (c == ' ' && !inQuotes) {
            if (!current.empty()) {
                args.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    if (!current.empty()) args.push_back(current);
    return args;
}

std::map<std::string, Collaborator> loadCollaborators(std::string path) {
    std::map<std::string, Collaborator> CollaboratorMap;
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "!! config ERROR: Missing file at " << path << std::endl;
        return CollaboratorMap; 
    }

    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue; 

        size_t sep = line.find(':');
        if (sep != std::string::npos) {
            std::string flag = trim(line.substr(0, sep));
            std::string fullCmd = trim(line.substr(sep + 1));
            
            Collaborator col;
            
            // Look for color in [brackets]
            size_t openBracket = fullCmd.find('[');
            size_t closeBracket = fullCmd.find(']');
            
            if (openBracket != std::string::npos && closeBracket != std::string::npos && closeBracket > openBracket) {
                col.color = trim(fullCmd.substr(openBracket + 1, closeBracket - openBracket - 1));
                std::string cmdPart = trim(fullCmd.substr(0, openBracket));
                col.commandArgs = splitCommand(cmdPart);
            } else {
                col.commandArgs = splitCommand(fullCmd);
            }
            
            if (!col.commandArgs.empty()) {
                CollaboratorMap[flag] = col;
            }
        }
    }
    return CollaboratorMap;
}

void showInternalHelp() {
    std::cout << "Usage: ai <flag> <your message>" << std::endl;
    std::cout << "Internal Commands:" << std::endl;
    std::cout << "  --change-color   Change the color for a collaborator" << std::endl;
    std::cout << "  --override       Override shell config location" << std::endl;
    std::cout << "  --get-override   Show current override path" << std::endl;
}

int main(int argc, char* argv[]) {
    // AUDIT: Minimum requirements
    if (argc < 2) {
        showInternalHelp();
        return 1;
    }

    std::string firstArg = argv[1];

    // INTERNAL COMMANDS: Catch --flags
    if (firstArg.substr(0, 2) == "--") {
        if (firstArg == "--help") {
            showInternalHelp();
        } else if (firstArg == "--change-color") {
            std::cout << "Changing colors is not implemented yet. ^‿-" << std::endl;
        } else if (firstArg == "--override") {
            std::cout << "Override is not implemented yet. ^‿-" << std::endl;
        } else if (firstArg == "--get-override") {
            std::cout << "Get override is not implemented yet. ^‿-" << std::endl;
        } else {
            std::cerr << "!! ERROR: Unknown internal command '" << firstArg << "'" << std::endl;
        }
        return 0;
    }

    if (argc < 3) {
        std::cout << "Usage: ai <flag> <your message>" << std::endl;
        return 1;
    }

    // PATHING: Keeping the old-school getenv()
    const char* home = getenv("HOME");
    if (!home) {
        std::cerr << "!! SYSTEM ERROR: $HOME not found." << std::endl;
        return 1;
    }
    std::string configPath = std::string(home) + "/.config/ai/ai.config";
    
    // INITIALIZE: Load Collaborators
    auto Collaborators = loadCollaborators(configPath);

    // DISPATCH: The Security Hardening (fork/execvp)
    if (Collaborators.count(firstArg)) {
        
        // THE EASTER EGG & SECURITY AUDIT
        // Check the user's message (argv[2] and beyond) for the "Shell Trio"
        bool suspectedInjection = false;
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == ">" || arg == ">>" || arg == "|" || arg == ";") {
                suspectedInjection = true;
                break;
            }
        }

        if (suspectedInjection) {
            std::cout << "Shell metacharacters detected. We keep it simple here. ^‿-" << std::endl;
            return 1;
        } 
        // EASTEREGG: Sanatize for 'rm' tricks as a hat tip to history ^‿- LULZ!
        else if (firstArg == "rm" && argc > 2 && std::string(argv[2]) == "-rf") {
            std::cout << "Nice try, zero-day. We don't do that here. ^‿-" << std::endl;
            return 1;
        }

        // PREPARE EXECUTION
        Collaborator& col = Collaborators[firstArg];
        std::vector<char*> execArgs;

        for (auto& arg : col.commandArgs) {
            execArgs.push_back((char*)arg.c_str());
        }
        for (int i = 2; i < argc; ++i) {
            execArgs.push_back(argv[i]);
        }
        execArgs.push_back(nullptr);

        // FORK: Create a child process (No zombies allowed!)
        pid_t pid = fork();

                // FORK: Create a child process
        pid_t pid = fork();

        if (pid == 0) {
            // 1. YOUR COLOR LOGIC: Apply color before the AI tool takes over the terminal
            if (isatty(STDOUT_FILENO) && !col.color.empty()) {
                // Example: If col.color is "red", you'd print "\033[31m"
                // std::cout << mapToAnsi(col.color) << std::flush;
            }

            // 2. EXECUTION: This replaces the current process
            execvp(execArgs[0], execArgs.data());
            
            // 3. CLEANUP: If we reach this line, execvp FAILED
            perror("!! EXEC ERROR");
            _exit(1); // Use _exit to prevent "ghost" child processes
        } else if (pid > 0) {
            // Parent waits for the AI to finish talking
            int status;
            waitpid(pid, &status, 0);
            
            // OPTIONAL: Reset color after the AI is done so the terminal doesn't stay red/blue
            // std::cout << "\033[0m" << std::endl;
        } else {
            perror("!! FORK FAILED");
            return 1;
        }
