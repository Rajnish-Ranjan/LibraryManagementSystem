#include<bits/stdc++.h>
#include "LibraryService.h"

using std::string;
using std::set;
using std::vector;
using std::cout;
using std::cin;

int main()
{
	try {
		LibraryService* lService = new LibraryService();
		set<string> authors, publishers;
		vector<string> bookCopies;
		string  bookTitle, bookAuthor, bookPublisher;
		string userName;
		string Command;
		string libId, bookId, bookCopyId, userId;
		int dueDate;
		int TotalRacks;

		while (true)
		{
			cin >> Command;
			if (Command == "ADDLIBRARY") {
				cin >> libId >> TotalRacks;
				try {
					cout << lService->AddLibrary(libId, TotalRacks) << "\n";
				}
				catch (const char* ex) {
					cout << "Exception has procured: " << ex << "\n";
				}
			}
			if (Command == "ADDUSER") {
				cin >> userName;
				try {
					cout << lService->AddUser(userName) << "\n";
				}
				catch (const char* ex) {
					cout << "Exception has procured: " << ex << "\n";
				}
			}
			if (Command == "BORROWBOOK") {
				cin >> bookId >> userId >> dueDate;
				try {
					cout << lService->BorrowBook(bookId, userId, dueDate) << "\n";
				}
				catch (const char* ex) {
					cout << "Exception has procured: " << ex << "\n";
				}
			}
			if (Command == "RETURNBOOK") {
				cin >> bookId >> bookCopyId;
				try {
					cout << lService->ReturnBook(bookId, bookCopyId) << "\n";
				}
				catch (const char* ex) {
					cout << "Exception has procured: " << ex << "\n";
				}
			}
			if (Command == "BORROWEDBOOKS") {
				cin >> userId;
				try {
					lService->PrintBorrowedBooks(userId);
				}
				catch (const char* ex) {
					cout << "Exception has procured: " << ex << "\n";
				}
			}
			if (Command == "SEARCHBOOKS") {
				cin >> bookTitle >> bookAuthor >> bookPublisher;
				if (bookTitle == "NA") {
					bookTitle = "";
				}
				if (bookAuthor == "NA") {
					bookAuthor = "";
				}
				if (bookPublisher == "NA") {
					bookPublisher = "";
				}
				try {
					lService->SearchBook(bookTitle, bookAuthor, bookPublisher);
				}
				catch (const char* ex) {
					cout << "Exception has procured: " << ex << "\n";
				}
			}
			if (Command == "ADDBOOKS") {
				cin >> bookId >> bookTitle;
				set<string> Authors;
				set<string> Publishers;
				vector<string> bookCopyIds;
				int nA, nP, nC;
				cout << "Enter number of Authors, Publishers and Copies\n";
				cin >> nA >> nP >> nC;
				cout << "Authors >> \n";
				while (nA--) {
					cin >> bookAuthor;
					Authors.insert(bookAuthor);
				}
				cout << "Publishers >>\n";
				while (nP--) {
					cin >> bookPublisher;
					Publishers.insert(bookPublisher);
				}
				cout << "Book Copy Ids >> \n";
				while (nC--) {
					cin >> bookCopyId;
					bookCopyIds.push_back(bookCopyId);
				}
				try {
					lService->AddBook(bookId, bookTitle, Authors, Publishers, bookCopyIds);
				}
				catch (const char* ex) {
					cout << "Exception has procured: " << ex << "\n";
				}
			}
			if (Command == "EXIT") {
				break;
			}
		}
		/*
		authors.insert("Raju");
		publishers.insert("Prasad");
		bookCopies.push_back("c1");
		bookCopies.push_back("c2");
		cout << lService->AddBook("book0", "Hey Ram", authors, publishers, bookCopies) << "\n";
		cout << lService->AddUser("raju") << "\n";
		cout << lService->AddUser("Molecule") << "\n";
		lService->BorrowBook("book0", "raju0", 9);
		lService->BorrowBook("book0", "Molecule1", 10);
		*/
	}
	catch (const char* ex) {
		cout << ex;
	}
	catch (std::exception ex) {
		cout << ex.what();
	}
}
