#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

struct Book {
  int id;
  std::string title;
  int authorId;
  int year;
  int copies;
};

namespace book {
  const std::string FILE_NAME = "books.txt";

  void create(Book& book);
  void readAll(std::vector<Book>& books);
  Book* findById(const std::vector<Book>& books, int id);
  void update(Book& book);
  void remove(int id);
  void searchByTitle(const std::vector<Book>& books, std::string title);
  void searchByYear(const std::vector<Book>& books, int year);
  void sortByYear(std::vector<Book>& books, bool ascending);
  bool isUniqueBookId(int bookId, const std::vector<Book>& books);
}

#endif
