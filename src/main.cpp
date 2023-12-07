#include <iostream>
#include "rb_tree_autocomplete.h"
#include <cstdlib>
#include <curses.h>

int main(){
    std::string filepath = "dicionario_ordenado.txt";
    std::string userInput, line;
    std::vector<std::string> currentSuggestions;
    char c;

    std::ifstream inputFile;
    inputFile.open(filepath);

    AutoComplete algorithm;
    RBTree tree;
    algorithm.assembleDictionary(inputFile, tree);

    while(true){
        c = std::getchar();

        if(c == 27 || c == '\n') break;
        else if (c == 127 && userInput.size() > 0){
            userInput.pop_back();
        }
        if(std::isalpha(c) && c != ' ' && c != 127 && c != 27 && c != '\n'){userInput.push_back(c);}
        
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif
        
        currentSuggestions = algorithm.suggestions(userInput, tree);
        sort(currentSuggestions.begin(), currentSuggestions.end());
        if (currentSuggestions.empty()) {
            std::cout << "Sem sugestões." << std::endl;
        } else {
            std::cout << "Sugestões:" << std::endl;
            for (const std::string& word : currentSuggestions) {
                std::cout << word << std::endl;
            }
        }
        currentSuggestions.clear();
    }

    inputFile.close();
    return 0;
}