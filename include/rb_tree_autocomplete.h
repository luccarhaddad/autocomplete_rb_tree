#ifndef RB_TREE_AUTOCOMPLETE_H
#define RB_TREE_AUTOCOMPLETE_H

#include "rb_tree.h"
#include <fstream>

class AutoComplete{
private:
	RBTree Dictionary;
public:
	void assembleDictionary(std::ifstream& inputFile, RBTree& Dic);
	std::vector<std::string> suggestions(std::string& currentWord, RBTree& Dic);
};

#endif