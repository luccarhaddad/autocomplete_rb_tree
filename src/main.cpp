#include <iostream>
#include "rb_tree_autocomplete.h"
#include <cstdlib>

void DFS(node* x){
    if(x == nullptr){
        return;
    }
    std::cout << x->key << std::endl;
    DFS(x->left);
    DFS(x->right);
}

int main(){
    std::string filepath = "palavras.txt";
    std::string userInput, line;
    std::vector<std::string> currentSuggestions;
    std::ifstream inputFile(filepath);
    AutoComplete algorithm;
    RBTree tree;

    while(inputFile >> line){
		std::cout << line << std::endl;
	}

    algorithm.assembleDictionary(inputFile, tree);
    DFS(tree.getRoot());
    while(true){
        std::getline(std::cin, userInput);
        if(userInput.empty()){ break; }
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif
        currentSuggestions = algorithm.suggestions(userInput, tree);
        if (currentSuggestions.empty()) {
            std::cout << "Sem sugestões." << std::endl;
        } else {
            std::cout << "Sugestões:" << std::endl;
            for (const std::string& word : currentSuggestions) {
                std::cout << word << std::endl;
            }
        }
    }
    return 0;
}