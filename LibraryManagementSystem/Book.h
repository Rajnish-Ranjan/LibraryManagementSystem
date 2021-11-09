#pragma once
#include<bits/stdc++.h>
using std::string;
using std::set;

class Book {
public:
	string Id;
	string Title;
	set<string> Authors;
	set<string> Publishers;
	Book() {}
	Book(string id, string title, set<string> authors, set<string> publishers) {
		Id = id;
		Authors = authors;
		Publishers = publishers;
		Title = title;
	}
	string BookDetails() {
		string authors;
		for (string a : Authors) {
			authors = " " + authors + a + ",";
		}
		if (authors.length() > 0)
			authors.pop_back();
		string publishers;
		for (string p : Publishers) {
			publishers = " " + publishers + p + ",";
		}
		if (publishers.length() > 0) {
			publishers.pop_back();
		}
		return " [" + Id + "] " + Title + " \n\tAuthors: " + authors + "\n\tPublishers: " + publishers + "\n";
	}
	bool IsMatching(string bookTitle, string bookAuthor, string bookPublisher) {
		if (Title.find(bookTitle) == std::string::npos) {
			return false;
		}
		if (bookAuthor != "" && Authors.find(bookAuthor) == Authors.end()) {
			return false;
		}
		if (bookPublisher != "" && Publishers.find(bookPublisher) == Publishers.end()) {
			return false;
		}
		return true;
	}
};