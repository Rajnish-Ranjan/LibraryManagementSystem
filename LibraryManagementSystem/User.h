#pragma once
#include<bits/stdc++.h>
using std::string;
using std::set;

class User {
	static int idCount;
public:
	string Id,Name;
	int MaxLimit;
	int NBooksAlloted;
	set<string> BookCopyIds;
	User(string name, int maxLim = 5)
	{
		NBooksAlloted = 0;
		MaxLimit = maxLim;
		Name = name;
		MaxLimit = maxLim;
		Id = name + std::to_string(idCount++);
	}
	void AddBook(string bookCopyid) {
		if (NBooksAlloted == MaxLimit) {
			throw "Cannot Borrow More Books, Max Limit for the User has been reached";
		}
		if (BookCopyIds.find(bookCopyid) != BookCopyIds.end()) {
			throw "this book is already allotted";
		}
		BookCopyIds.insert( bookCopyid);
		NBooksAlloted++;
	}
	void RemoveBook(string bookCopyId) {
		if (BookCopyIds.find(bookCopyId) == BookCopyIds.end()) {
			throw "Book Copy is not assigned to user [" + Id + "].";
		}
		BookCopyIds.erase(bookCopyId);
		NBooksAlloted--;
	}
};
int User::idCount = 0;