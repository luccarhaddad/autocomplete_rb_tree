#include <iostream>
#include <ncurses.h>
#include "rb_tree_autocomplete.h"

int main() {
    std::string filepath = "dicionario_ordenado.txt";
    std::string userInput, line;
    std::vector<std::string> currentSuggestions;
    char c;

    std::ifstream inputFile;
    inputFile.open(filepath);

    AutoComplete algorithm;
    RBTree tree;
    algorithm.assembleDictionary(inputFile, tree);

    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    while (true) {
        c = getch();

        if (c == 27 || c == '\n') break;
        else if (c == 127 && userInput.size() > 0) {
            userInput.pop_back();
        }
        if (std::isalpha(c) && c != ' ' && c != 127 && c != 27 && c != '\n') {
            userInput.push_back(c);
        }

        clear();
        mvprintw(0, 0, "Input: %s", userInput.c_str());

        currentSuggestions = algorithm.suggestions(userInput, tree);
        sort(currentSuggestions.begin(), currentSuggestions.end());
        if(userInput.size()>0){
            mvprintw(2, 0, "Autocomplete:");
            int row = 3;
            for (const std::string& word : currentSuggestions) {
                mvprintw(row++, 0, "%s", word.c_str());
            }
        }
        refresh();
        currentSuggestions.clear();
    }
    endwin();
    inputFile.close();
    return 0;
}