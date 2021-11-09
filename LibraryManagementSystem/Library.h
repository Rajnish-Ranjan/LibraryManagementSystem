#pragma once
#include<bits/stdc++.h>
#include "User.h"
#include "BookCopy.h"
#include "Book.h"
#include "Rack.h"

using std::map;
using std::string;

class Library {
public:
	string Id;
	int No_Racks;
	map<string, User*> UserMapping;
	map<string, BookCopy*> BookCopyMapping;
	map<string, Book*> BookMapping;
	map<int, Rack*> RackMapping;

	Library(string libId, int no_racks) {
		Id = libId;
		No_Racks = no_racks;
		for (int i = 0; i < no_racks; i++) {
			RackMapping[i] = new Rack(i);
		}
	}
	int LowestAvailableRack(string bookId) {
		int i = 0;
		while (i<No_Racks)
		{
			if (RackMapping[i]->BookIdHaveBookCopy.find(bookId) == RackMapping[i]->BookIdHaveBookCopy.end()) {
				return i;
			}
			i++;
		}
		throw "All the racks are occupied for this book";
	}
};