#pragma once
#include<bits/stdc++.h>
using std::string;

class BookCopy {
public:
	string BookId;
	string BookCopyId;
	string issuedTo;
	string placedAtRack;
	int issueDueDate;
	BookCopy(string bookId,string bookCopyId) {
		BookId = bookId;
		BookCopyId = bookCopyId;
		issuedTo = "";
		placedAtRack = "";
		issueDueDate = 0;
	}
	void IssueBook(string userId,int date) {
		issuedTo = userId;
		placedAtRack = "";
		issueDueDate = date;
	}
};