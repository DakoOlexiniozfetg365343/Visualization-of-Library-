#include "book.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

namespace book {
    void create(Book& book){
        utils::backupFile(book::FILE_NAME);
        std::ofstream file(book::FILE_NAME, std::ios::app);
        file << book.id << "|" << book.title << "|" << book.authorId << "|" << book.year << "|" << book.copies << "\n";
        file.close();

        utils::printSuccess("Book created successfully");
    }

    void readAll(std::vector<Book>& books){
        books.clear();
        std::ifstream file(book::FILE_NAME);
        std::string line;
        while (std::getline(file, line)){
            auto tokens = utils::split(line, utils::DELIMITER);
            if(tokens.size() == 5){
                Book book = {std::stoi(tokens[0]), tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4])};
                books.push_back(book);
            }
        }
        file.close();
    }
    bool isUniqueBookId(int bookId, const std::vector<Book>& books) {
    for (const auto& book : books) {
        if (book.id == bookId) {
            return false;
        }
    }
    return true;
}


    Book* findById(const std::vector<Book>& books, int id){
        for(const auto& book : books){
            if(book.id == id) return const_cast<Book*>(&book);
        }
        return nullptr;
    }

    void update(Book& book){
        std::vector<Book> books;
        readAll(books);
        bool isPresent = false;
        for(auto& b : books){
            if(b.id == book.id){
                b = book;
                isPresent = true;
                break;
            }
        }
        if (isPresent){
            utils::backupFile(book::FILE_NAME);
            std::ofstream file(book::FILE_NAME);
            for(const auto& b : books){
                file << b.id << "|" << b.title << "|" << b.authorId << "|" << b.year << "|" << b.copies << "\n";
            }
            file.close();
            utils::printSuccess("Book updated successfully");
        }else{
          std::cout << "Issue with ID " << book.id << " not found.\n";
        }
    }

    void remove(int id){
    	std::vector<Book> books;
    	readAll(books);


    	books.erase(std::remove_if(books.begin(), books.end(), [id](const Book& b){
        	return b.id == id;
    	}), books.end());


    	utils::backupFile(book::FILE_NAME);


    	std::ofstream file(book::FILE_NAME, std::ios::trunc);
    	for(const auto& b : books){
        	file << b.id << "|" << b.title << "|" << b.authorId << "|" << b.year << "|" << b.copies << "\n";
    	}
    	file.close();

    	utils::printSuccess("Book removed successfully");
}



    void searchByTitle(const std::vector<Book>& books, std::string title){
        utils::printTableHeaders({"ID", "Title", "Author", "Year", "Copies"});
        for(const auto& book : books){
            if(book.title.find(title) != std::string::npos){
                std::cout << std::left << std::setw(20) << book.id << "|"
                          << std::setw(20) << book.title << "|"
                          << std::setw(20) << book.authorId << "|"
                          << std::setw(20) << book.year << "|"
                          << std::setw(20) << book.copies << "\n";
            }
        }
    }
    void searchByYear(const std::vector<Book>& books, int year){
      utils::printTableHeaders({"ID", "Title", "Author", "Year", "Copies"});
        for(const auto& book : books){
            if(book.year == year){
                std::cout << std::left << std::setw(20) << book.id << "|"
                          << std::setw(20) << book.title << "|"
                          << std::setw(20) << book.authorId << "|"
                          << std::setw(20) << book.year << "|"
                          << std::setw(20) << book.copies << "\n";
            }
        }
    }


    void sortByYear(std::vector<Book>& books, bool ascending){
        std::sort(books.begin(), books.end(), [ascending](const Book& a, const Book& b){
            return ascending ? a.year < b.year : a.year > b.year;
        });
        utils::printSuccess("Sorted by year");
    }
}
