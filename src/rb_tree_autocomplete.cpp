#include "rb_tree_autocomplete.h"

void AutoComplete::assembleDictionary(std::ifstream& inputFile, RBTree& Dic, long& wordCount){
	std::string line;
	wordCount = 0;
	while(std::getline(inputFile, line)){
		Dic.add(line);
		wordCount++;
	}
	inputFile.close();
}

std::vector<std::string> AutoComplete::suggestions(std::string& currentWord, RBTree& Dic){
	std::vector<std::string> list;
	Dic.findSuggestions(currentWord, list);
	return list;
}