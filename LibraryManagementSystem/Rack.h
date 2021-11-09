#pragma once
#include<bits/stdc++.h>
using std::string;

class Rack {
public:
	int Id;
	std::map<string, string> BookIdHaveBookCopy;
	Rack(int id) {
		Id = id;
	}
};
