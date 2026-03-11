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

std::map<std::string, std::string> loadCollaborators(std::string path) {
    std::map<std::string, std::string> CollaboratorMap;
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "!! config ERROR: Missing file at " << path << std::endl;
        return CollaboratorMap; 
    }

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; 

        size_t sep = line.find(':');
        if (sep != std::string::npos) {
            // Apply the trim to both flag and command
            std::string flag = trim(line.substr(0, sep));
            std::string cmd = trim(line.substr(sep + 1));
            CollaboratorMap[flag] = cmd; 
        }
    }
    return CollaboratorMap;
}

int main(int argc, char* argv[]) {
    // AUDIT: Minimum requirements
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
    std::string flag = argv[1];

    if (Collaborators.count(flag)) {
        // Build the argument list for execvp
        // execvp needs a NULL-terminated array of char pointers (old school!)
        std::vector<char*> execArgs;

        // The first argument is the command itself (the collaborator)
        execArgs.push_back((char*)Collaborators[flag].c_str());

        // The rest are the message words from the user
        for (int i = 2; i < argc; ++i) {
            execArgs.push_back(argv[i]);
        }
        execArgs.push_back(nullptr); // Final NULL required

        // FORK: Create a child process to run the AI peer
        pid_t pid = fork();

        if (pid == 0) {
            // We are in the CHILD process: Execute the collaborator
            // This bypasses the shell injection risk entirely
            execvp(execArgs[0], execArgs.data());
            
            // If execvp returns, it failed
            perror("!! EXEC ERROR");
            return 1;
        } else if (pid > 0) {
            // We are in the PARENT: Wait for the AI to finish talking
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("!! FORK FAILED");
            return 1;
        }
    } else {
        std::cerr << "!! ERROR: Collaborator '" << flag << "' not found." << std::endl;
        return 1;
    }

    return 0;
}
