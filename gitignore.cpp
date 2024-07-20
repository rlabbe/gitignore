#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <set>

void add_to_gitignore(const std::string& filename) {
    const std::string gitignore_filename = ".gitignore";
    std::set<std::string> ignore_entries;

    // Check if .gitignore exists, if not create it and warn the user
    if (!std::filesystem::exists(gitignore_filename)) {
        std::ofstream gitignore_file(gitignore_filename);
        if (!gitignore_file) {
            std::cerr << "Error: Could not create .gitignore file." << std::endl;
            return;
        }
        std::cout << "Warning: .gitignore file created as it did not exist." << std::endl;
    }

    // Read existing .gitignore entries
    std::ifstream gitignore_file(gitignore_filename);
    if (gitignore_file) {
        std::string line;
        while (std::getline(gitignore_file, line)) {
            ignore_entries.insert(line);
        }
    } else {
        std::cerr << "Error: Could not read .gitignore file." << std::endl;
        return;
    }
    gitignore_file.close();

    // Check if the file to be ignored is already in .gitignore
    if (ignore_entries.find(filename) != ignore_entries.end()) {
        std::cout << "Info: The file \"" << filename << "\" is already in .gitignore." << std::endl;
        return;
    }

    // Add the file to .gitignore
    std::ofstream gitignore_file_out(gitignore_filename, std::ios::app);
    if (gitignore_file_out) {
        gitignore_file_out << filename << std::endl;
        std::cout << "Info: The file \"" << filename << "\" has been added to .gitignore." << std::endl;
    } else {
        std::cerr << "Error: Could not write to .gitignore file." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: gitignore <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    if (!std::filesystem::exists(filename)) {
        std::cerr << "Error: The file \"" << filename << "\" does not exist." << std::endl;
        return 1;
    }

    add_to_gitignore(filename);

    return 0;
}
