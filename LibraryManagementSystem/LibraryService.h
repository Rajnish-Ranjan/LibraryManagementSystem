#pragma once
#include<bits/stdc++.h>
#include "Library.h"
#include "Book.h"
#include "User.h"

using std::string;
using std::set;
using std::vector;
using std::cout;

class LibraryService {
	int dateNow;
	Library* MyLibrary;
public:
	LibraryService() {
		dateNow = 0;
		MyLibrary = NULL;
	}
	string AddLibrary(string libId, int no_racks) {
		MyLibrary = new Library(libId, no_racks);
		return "Created Library ["+libId+"] with " + std::to_string(no_racks) + " racks";
	}
	string AddBook(string bookId, string title, set<string> authors, set<string> publishers,std::vector<string> bookCopies) 
	{
		if (MyLibrary == NULL) {
			throw "Please Find Library for this operation";
		}
		Book* book;
		if (MyLibrary->BookMapping.find(bookId) == MyLibrary->BookMapping.end()) {
			book = new Book(bookId, title, authors, publishers);
			MyLibrary->BookMapping[bookId] = book;
		}
		else {
			book = MyLibrary->BookMapping[bookId];
		}
		int copiesNum = bookCopies.size();
		int lowestRackId=MyLibrary->LowestAvailableRack(bookId);
		if (MyLibrary->No_Racks - lowestRackId <= copiesNum) {
			throw "Not enough Racks Availbale";
		}

		for (string bookCopyId : bookCopies) {
			BookCopy* bookCopy;
			if (MyLibrary->BookCopyMapping.find(bookCopyId) == MyLibrary->BookCopyMapping.end()) {
				bookCopy = new BookCopy(bookId, bookCopyId);
				MyLibrary->BookCopyMapping[bookCopyId] = bookCopy;
			}
			else {
				bookCopy = MyLibrary->BookCopyMapping[bookCopyId];
			}
			bookCopy->placedAtRack = lowestRackId;
			MyLibrary->RackMapping[lowestRackId]->BookIdHaveBookCopy[bookId] = bookCopyId;
			lowestRackId++;
		}
		return "Book [" + bookId + "] is Added";
	}
	string AddUser(string name) {
		if (MyLibrary == NULL) {
			throw "Library need to be there";
		}
		User* user = new User(name);
		MyLibrary->UserMapping[user->Id] = user;
		return "User [" + user->Id + "] is Added.";
	}
	string BorrowBook(string bookId,string userid,int issueDueDate) {
		if (MyLibrary == NULL) {
			throw "Library need to be there";
		}
		if (MyLibrary->BookMapping.find(bookId) == MyLibrary->BookMapping.end()) {
			throw "Book is Not Registered to Library";
		}
		if (MyLibrary->UserMapping.find(userid) == MyLibrary->UserMapping.end()) {
			throw "User is not registered";
		}
		if (issueDueDate <= dateNow) {
			throw "Due Date should always be greater than current data";
		}
		BookCopy* bookcopy;
		int rackForBookId = MyLibrary->LowestAvailableRack(bookId)-1;
		if (rackForBookId < 0) {
			throw "BookCopy is not available";
		}
		string bookCopyId = MyLibrary->RackMapping[rackForBookId]->BookIdHaveBookCopy[bookId];
		
		if (MyLibrary->BookCopyMapping.find(bookCopyId) == MyLibrary->BookCopyMapping.end()) {
			throw "BookCopy is not available";
		}
		MyLibrary->UserMapping[userid]->AddBook(bookCopyId);
		bookcopy = MyLibrary->BookCopyMapping[bookCopyId];
		bookcopy->IssueBook(userid, issueDueDate);
		return "Book Borrowed";
	}
	string ReturnBook(string bookId, string bookCopyId) {
		if (MyLibrary == NULL) {
			throw "Library need to be there";
		}
		if (MyLibrary->BookMapping.find(bookId) == MyLibrary->BookMapping.end()) {
			throw "Book is not registered to library";
		}
		if (MyLibrary->BookCopyMapping.find(bookCopyId) == MyLibrary->BookCopyMapping.end()) {
			throw "Book copy is inValid";
		}
		Book* book = MyLibrary->BookMapping[bookId];
		BookCopy* bookcopy = MyLibrary->BookCopyMapping[bookCopyId];
		string userId = bookcopy->issuedTo;
		if (MyLibrary->UserMapping.find(userId) == MyLibrary->UserMapping.end()) {
			throw "User has been unregistered";
		}
		User* user = MyLibrary->UserMapping[userId];
		user->RemoveBook(bookCopyId);
		
		
		string message = "";
		if (bookcopy->issueDueDate < dateNow) {
			message = "Fine has been issued";
		}
		else {
			message = "Returned without fine";
		}
		bookcopy->issueDueDate = -1;
		Rack* rack = MyLibrary->RackMapping[MyLibrary->LowestAvailableRack(bookId)];
		rack->BookIdHaveBookCopy[bookId] = bookCopyId;
		bookcopy->placedAtRack = rack->Id;
		bookcopy->issuedTo = "";
		return message;
	}
	void PrintBorrowedBooks(string userId) {
		if (MyLibrary == NULL) {
			throw "Library need to be there";
		}
		if (MyLibrary->UserMapping.find(userId) == MyLibrary->UserMapping.end()) {
			throw "User Not Found";
		}
		User* user = MyLibrary->UserMapping[userId];
		for (string bookCopyId : user->BookCopyIds) {
			string bookId = MyLibrary->BookCopyMapping[bookCopyId]->BookId;
			cout << MyLibrary->BookMapping[bookId]->BookDetails();
		}
	}
	void SearchBook(string bookTitle,string bookAuthor,string bookPublisher) {
		if (MyLibrary == NULL) {
			throw "Library need to be there";
		}
		vector<string> bookIdsAndAvailablility;
		map<string, Book*>::iterator it;
		int lowestRackForBookId;
		for (it = MyLibrary->BookMapping.begin(); it != MyLibrary->BookMapping.end(); it++) {
			if (it->second->IsMatching(bookTitle, bookAuthor, bookPublisher)) {
				lowestRackForBookId = MyLibrary->LowestAvailableRack(it->first);
				if (lowestRackForBookId <= 0) {
					bookIdsAndAvailablility.push_back(it->first + ": Not Available");
				}
				else {
					bookIdsAndAvailablility.push_back(it->first + ": Available");
				}
			}
		}
		for (auto booki : bookIdsAndAvailablility) {
			cout << booki << "\n";
		}
	}

};