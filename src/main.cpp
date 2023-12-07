#include <iostream>
#include <ncurses.h>
#include "rb_tree_autocomplete.h"
#include <chrono>

#define COLOR_PAIR_GREEN 1

int main(){
    char c;
    int row = 0;
    long words;

    std::string filepath = "dicionario_ordenado.txt";
    std::string userInput, line;
    std::vector<std::string> currentSuggestions;
    std::ifstream inputFile;

    AutoComplete algorithm;
    RBTree tree;

    inputFile.open(filepath);
    auto start = std::chrono::high_resolution_clock::now();
    algorithm.assembleDictionary(inputFile, tree, words);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    size_t memoryUsage = (sizeof(node)*(words+1));

    initscr();
    start_color();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    init_pair(COLOR_PAIR_GREEN, COLOR_GREEN, COLOR_BLACK);
    mvprintw(row, 0, "AUTOCOMPLETE ALGORITHM (RED-BLACK TREE)");
    mvprintw(++row, 0, "Data Structure Creation Time: %s ms", std::to_string(duration.count()).c_str());
    mvprintw(++row, 0, "Number of Nodes: %d", words+1);
    mvprintw(++row, 0, "Memory Usage: %d kB", memoryUsage/1000); ++row;
    mvprintw(++row, 0, "Input: %s", userInput.c_str());
    
    while(true){
        c = getch();
        row = 0;
        if (c == 27 || c == '\n'){
            break;
        }
        else if (c == 127 && userInput.size() > 0) {
            userInput.pop_back();
        }
        if (std::isalpha(c) && c != ' ' && c != 127 && c != 27 && c != '\n') {
            userInput.push_back(c);
        }

        clear();
        mvprintw(row, 0, "AUTOCOMPLETE ALGORITHM (RED-BLACK TREE)");
        mvprintw(++row, 0, "Data Structure Creation Time: %s ms", std::to_string(duration.count()).c_str());
        mvprintw(++row, 0, "Number of Nodes: %d", words+1);
        mvprintw(++row, 0, "Memory Usage: %d kB", memoryUsage/1000); ++row;
        mvprintw(++row, 0, "Input: %s", userInput.c_str());

        auto start = std::chrono::high_resolution_clock::now();
        currentSuggestions = algorithm.suggestions(userInput, tree);
        sort(currentSuggestions.begin(), currentSuggestions.end());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        
        if(userInput.size() > 0){
            mvprintw(++row, 0, "Autocomplete: ");
            attron(COLOR_PAIR(COLOR_PAIR_GREEN));
            for (const std::string& word : currentSuggestions) {
                mvprintw(++row, 0, "%s", word.c_str());
            }
            attroff(COLOR_PAIR(COLOR_PAIR_GREEN));
            mvprintw(++row+1, 0, "Autocomplete Execution Time: %s ms", std::to_string(duration.count()).c_str());
        }
        refresh();
        currentSuggestions.clear();
    }
    endwin();
    inputFile.close();
    return 0;
}