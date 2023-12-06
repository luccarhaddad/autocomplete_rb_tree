#include <rb_tree_autocomplete.h>

void AutoComplete::assembleDictionary(std::ifstream& inputFile, RBTree& Dic){
	std::string line;
	long idx = 0;
	while(std::getline(inputFile, line)){
		Dic.add(line, ++idx);
	}
}

std::vector<std::string> AutoComplete::suggestions(std::string& currentWord, RBTree& Dic){
	
}