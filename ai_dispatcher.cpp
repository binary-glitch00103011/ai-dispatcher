#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unistd.h>    // For fork() and execvp()
#include <sys/wait.h>  // For waitpid()
#include <algorithm>   // For whitespace trimming

/**
 * THE INSPECTOR'S TRIM: Removes leading/trailing whitespace
 * Makes the configig file forgiving if you have extra spaces.
 */
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (std::string::npos == first) return str;
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

/**
 * THE ARCHITECT'S PROVIDER LOADER
 */
std::map<std::string, std::string> loadProviders(std::string path) {
    std::map<std::string, std::string> providerMap;
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "!! configIG ERROR: Missing file at " << path << std::endl;
        return providerMap; 
    }

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; 

        size_t sep = line.find(':');
        if (sep != std::string::npos) {
            // Apply the trim to both flag and command
            std::string flag = trim(line.substr(0, sep));
            std::string cmd = trim(line.substr(sep + 1));
            providerMap[flag] = cmd; 
        }
    }
    return providerMap;
}

int main(int argc, char* argv[]) {
    // 1. AUDIT: Minimum requirements
    if (argc < 3) {
        std::cout << "Usage: ai <flag> <your message>" << std::endl;
        return 1;
    }

    // 2. PATHING: Keeping the old-school getenv()
    const char* home = getenv("HOME");
    if (!home) {
        std::cerr << "!! SYSTEM ERROR: $HOME not found." << std::endl;
        return 1;
    }
    std::string configigPath = std::string(home) + "/.configig/ai.config";
    
    // 3. INITIALIZE: Load providers
    auto providers = loadProviders(configigPath);

    // 4. DISPATCH: The Security Hardening (fork/execvp)
    std::string flag = argv[1];

    if (providers.count(flag)) {
        // Build the argument list for execvp
        // execvp needs a NULL-terminated array of char pointers (old school!)
        std::vector<char*> execArgs;

        // The first argument is the command itself (the provider)
        execArgs.push_back((char*)providers[flag].c_str());

        // The rest are the message words from the user
        for (int i = 2; i < argc; ++i) {
            execArgs.push_back(argv[i]);
        }
        execArgs.push_back(nullptr); // Final NULL required

        // FORK: Create a child process to run the AI tool
        pid_t pid = fork();

        if (pid == 0) {
            // We are in the CHILD process: Execute the provider
            // This replaces the shell injection risk entirely
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
        std::cerr << "!! ERROR: Provider '" << flag << "' not found." << std::endl;
        return 1;
    }

    return 0;
}
