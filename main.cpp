#include <algorithm>

#include "book.h"
#include "author.h"
#include "reader.h"
#include "issue.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>



enum class MenuOption {
    EXIT = 0,
    ADD_BOOK, LIST_BOOKS, SEARCH_BOOK_BY_TITLE, SEARCH_BOOK_BY_YEAR, SORT_BOOKS,
    UPDATE_BOOK,DELETE_BOOK,
    ADD_AUTHOR, LIST_AUTHORS, SEARCH_AUTHOR,
    UPDATE_AUTHOR,
    DELETE_AUTHOR,
    ADD_READER, LIST_READERS, SEARCH_READER,
    UPDATE_READER,
    DELETE_READER,
    ADD_ISSUE, LIST_ISSUES, RETURN_BOOK,
    UPDATE_ISSUE,
    DELETE_ISSUE,
    GENERATE_REPORT,
};

void printMenu() {
    std::cout << COLOR_YELLOW;
    std::cout << "\n========================================\n";
    std::cout << "        📚 Library Management System    \n";
    std::cout << "========================================\n" << COLOR_RESET;

    std::cout << COLOR_CYAN;
    std::cout << " 0. Exit\n";
    std::cout << "----------------------------------------\n";
    std::cout << " 1. Add Book       | 2. List Books\n";
    std::cout << " 3. Search Book by Title | 4. Search Book by Year\n";
    std::cout << " 5. Sort Books     | 6. Update Book | 7. Delete Book\n";
    std::cout << "----------------------------------------\n";
    std::cout << " 8. Add Author     | 9. List Authors\n";
    std::cout << "10. Search Author  | 11. Update Author | 12. Delete Author\n";
    std::cout << "----------------------------------------\n";
    std::cout << "13. Add Reader     | 14. List Readers\n";
    std::cout << "15. Search Reader  | 16. Update Reader | 17. Delete Reader\n";
    std::cout << "----------------------------------------\n";
    std::cout << "18. Issue Book     | 19. List Issues\n";
    std::cout << "20. Return Book    | 21. Update Issue | 22. Delete Issue\n";
    std::cout << "----------------------------------------\n";
    std::cout << "23. Generate Report\n";
    std::cout << "========================================\n" << COLOR_RESET;

    std::cout << COLOR_GREEN << "Enter choice: " << COLOR_RESET;
}



int main() {
    std::vector<Book> books;
    std::vector<Author> authors;
    std::vector<Reader> readers;
    std::vector<Issue> issues;

    while (true) {
        printMenu();
        int choice = utils::inputInt("");
        std::cin.ignore();

        switch (static_cast<MenuOption>(choice)) {
            case MenuOption::EXIT:
                return 0;

            case MenuOption::ADD_BOOK: {
                book::readAll(books);
                author::readAll(authors);
                Book book;
                book.id = utils::inputInt("Enter ID: ");
                std::cin.ignore();
                std::cout << "Enter title: ";
                std::getline(std::cin, book.title);
                book.authorId = utils::inputInt("Enter author ID: ");
                book.year = utils::inputInt("Enter year: ");
                book.copies = utils::inputInt("Enter copies: ");

                if (utils::validateYear(book.year) && book.copies > 0
                    && book::isUniqueBookId(book.id, books) && author::isAuthorId(book.authorId, authors)) {
                    book::create(book);
                } else {
                    utils::printError("Invalid year, copies, book-id (must be unique), or author-id (not found)");
                }
                break;
            }

            case MenuOption::LIST_BOOKS:
                book::readAll(books);
                utils::printTableHeaders({"ID", "Title", "Author ID", "Year", "Copies"});
                for (const auto& b : books) {
                    std::cout << std::left << std::setw(20) << b.id << "|"
                              << std::setw(20) << b.title << "|"
                              << std::setw(20) << b.authorId << "|"
                              << std::setw(20) << b.year << "|"
                              << std::setw(20) << b.copies << "|\n";
                }
                break;

            case MenuOption::SEARCH_BOOK_BY_TITLE: {
                std::string title;
                std::cout << "Enter title to search: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                book::readAll(books);
                book::searchByTitle(books, title);
                break;
            }

            case MenuOption::SEARCH_BOOK_BY_YEAR: {
                int year = utils::inputInt("Enter year to search: ");
                book::readAll(books);
                book::searchByYear(books, year);
                break;
            }

            case MenuOption::SORT_BOOKS: {
                book::readAll(books);
                book::sortByYear(books, true);
                utils::printTableHeaders({"ID", "Title", "Author ID", "Year", "Copies"});
                for (const auto& b : books) {
                    std::cout << std::left << std::setw(20) << b.id << "|"
                              << std::setw(20) << b.title << "|"
                              << std::setw(20) << b.authorId << "|"
                              << std::setw(20) << b.year << "|"
                              << std::setw(20) << b.copies << "|\n";
                }
                break;
            }
            case MenuOption::UPDATE_BOOK: {
                std::vector<Book> books;
                book::readAll(books);

                if (books.empty()) {
                    std::cout << "No books available to update.\n";
                    break;
                }

                int id;
                std::cout << "Enter the ID of the book to update: ";
                std::cin >> id;
                std::cin.ignore();

                auto it = std::find_if(books.begin(), books.end(),
                                       [id](const Book& b) { return b.id == id; });

                if (it == books.end()) {
                    std::cout << "Book with ID " << id << " not found.\n";
                    break;
                }

                Book updatedBook = *it;

                std::cout << "Enter new title (leave empty to keep \"" << updatedBook.title << "\"): ";
                std::string newTitle;
                std::getline(std::cin, newTitle);
                if (!newTitle.empty()) updatedBook.title = newTitle;

                std::cout << "Enter new author ID (leave empty to keep \"" << updatedBook.authorId << "\"): ";
                std::string newAuthorId;
                std::getline(std::cin, newAuthorId);
                if (!newAuthorId.empty()) updatedBook.authorId = std::stoi(newAuthorId);

                std::cout << "Enter new year (leave empty to keep \"" << updatedBook.year << "\"): ";
                std::string newYear;
                std::getline(std::cin, newYear);

                if (!newYear.empty()) updatedBook.year = std::stoi(newYear);

                std::cout << "Enter new number of copies (leave empty to keep \"" << updatedBook.copies << "\"): ";
                std::string newCopies;
                std::getline(std::cin, newCopies);
                if (!newCopies.empty()) updatedBook.copies = std::stoi(newCopies);

                book::update(updatedBook);
                break;
            }



            case MenuOption::DELETE_BOOK: {
                book::readAll(books);
                int bookId = utils::inputInt("Enter book ID: ");
                book::remove(bookId);
                break;
            }

            case MenuOption::ADD_AUTHOR: {
                author::readAll(authors);
                Author newAuthor;
                newAuthor.id = utils::inputInt("Enter ID: ");
                std::cin.ignore();
                std::cout << "Enter first name: ";
                std::getline(std::cin, newAuthor.firstName);
                std::cout << "Enter last name: ";
                std::getline(std::cin, newAuthor.lastName);

                if (utils::validateString(newAuthor.firstName) &&
                    utils::validateString(newAuthor.lastName) &&
                    !author::isAuthorId(newAuthor.id, authors)) {
                    author::create(newAuthor);
                } else {
                    utils::printError("Invalid name.");
                }
                break;
            }

            case MenuOption::LIST_AUTHORS:
                author::readAll(authors);
                utils::printTableHeaders({"ID", "First Name", "Last Name"});
                for (const auto& a : authors) {
                    std::cout << std::left << std::setw(20) << a.id << "|"
                              << std::setw(20) << a.firstName << "|"
                              << std::setw(20) << a.lastName << "|\n";
                }
                break;

            case MenuOption::SEARCH_AUTHOR: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                author::readAll(authors);
                author::searchByName(authors, name);
                break;
            }
            case MenuOption::UPDATE_AUTHOR: {
                std::vector<Author> authors;
                author::readAll(authors);

                if (authors.empty()) {
                    std::cout << "No authors available to update.\n";
                    break;
                }

                int id;
                std::cout << "Enter the ID of the author to update: ";
                std::cin >> id;
                std::cin.ignore();

                auto it = std::find_if(authors.begin(), authors.end(),
                                       [id](const Author& a) { return a.id == id; });

                if (it == authors.end()) {
                    std::cout << "Author with ID " << id << " not found.\n";
                    break;
                }

                Author updatedAuthor = *it;

                std::cout << "Enter new name (leave empty to keep \"" << updatedAuthor.firstName << "\"): ";
                std::string newName;
                std::getline(std::cin, newName);
                if (!newName.empty()) updatedAuthor.firstName = newName;

                std::cout << "Enter new surname (leave empty to keep \"" << updatedAuthor.lastName << "\"): ";
                std::string newSurname;
                std::getline(std::cin, newSurname);
                if (!newSurname.empty()) updatedAuthor.lastName = newSurname;

                author::update(updatedAuthor);
                break;
            }


            case MenuOption::DELETE_AUTHOR: {
                author::readAll(authors);
                int authorId = utils::inputInt("Enter author ID: ");
                author::remove(authorId);
                break;
            }

            case MenuOption::ADD_READER: {
                reader::readAll(readers);
                Reader reader;
                reader.id = utils::inputInt("Enter ID: ");
                std::cin.ignore();
                std::cout << "Enter first name: ";
                std::getline(std::cin, reader.firstName);
                std::cout << "Enter last name: ";
                std::getline(std::cin, reader.lastName);
                std::cout << "Enter phone: ";
                std::getline(std::cin, reader.phone);

                if (utils::validateString(reader.firstName) && utils::validateString(reader.lastName)
                    && utils::validatePhone(reader.phone) && reader::isUniqueReaderId(reader.id, readers)) {
                    reader::create(reader);
                } else {
                    utils::printError("Invalid input.");
                }
                break;
            }

            case MenuOption::LIST_READERS:
                reader::readAll(readers);
                utils::printTableHeaders({"ID", "First Name", "Last Name", "Phone"});
                for (const auto& r : readers) {
                    std::cout << std::left << std::setw(20) << r.id << "|"
                              << std::setw(20) << r.firstName << "|"
                              << std::setw(20) << r.lastName << "|"
                              << std::setw(20) << r.phone << "|\n";
                }
                break;

            case MenuOption::SEARCH_READER: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                reader::readAll(readers);
                reader::searchByName(readers, name);
                break;
            }
            case MenuOption::UPDATE_READER: {
                std::vector<Reader> readers;
                reader::readAll(readers);

                if (readers.empty()) {
                    std::cout << "No readers available to update.\n";
                    break;
                }

                int id;
                std::cout << "Enter the ID of the reader to update: ";
                std::cin >> id;
                std::cin.ignore();

                auto it = std::find_if(readers.begin(), readers.end(),
                                       [id](const Reader& r) { return r.id == id; });

                if (it == readers.end()) {
                    std::cout << "Reader with ID " << id << " not found.\n";
                    break;
                }

                Reader updatedReader = *it;

                std::cout << "Enter new name (leave empty to keep \"" << updatedReader.firstName << "\"): ";
                std::string newName;
                std::getline(std::cin, newName);
                if (!newName.empty()) updatedReader.firstName = newName;

                std::cout << "Enter new surname (leave empty to keep \"" << updatedReader.lastName << "\"): ";
                std::string newSurname;
                std::getline(std::cin, newSurname);
                if (!newSurname.empty()) updatedReader.lastName = newSurname;

                reader::update(updatedReader);
                break;
            }


            case MenuOption::DELETE_READER: {
                int readerId = utils::inputInt("Enter reader ID: ");
                reader::remove(readerId);
                break;
            }
            case MenuOption::ADD_ISSUE: {
                issue::readAll(issues);
                reader::readAll(readers);
                book::readAll(books);

                Issue newIssue;
                newIssue.id = utils::inputInt("Enter ID: ");
                newIssue.bookId = utils::inputInt("Enter book ID: ");
                newIssue.readerId = utils::inputInt("Enter reader ID: ");

                newIssue.issueDate = utils::currentDate();
                newIssue.returnDate = "";

                auto bookPtr = book::findById(books, newIssue.bookId);

                if (!issue::isUniqueIssueId(newIssue.id, issues)) {
                    utils::printError("Issue ID already exists.");
                    break;
                }

                if (!bookPtr) {
                    utils::printError("Book with this ID does not exist.");
                    break;
                }

                if (!reader::isUniqueReaderId(newIssue.readerId, readers)) {
                    utils::printError("Reader with this ID does not exist.");
                    break;
                }

                if (bookPtr->copies <= 0) {
                    utils::printError("No copies available.");
                    break;
                }
                bookPtr->copies--;
                book::update(*bookPtr);
                issue::create(newIssue);

                utils::printSuccess("Issue created successfully.");
                break;
            }

            case MenuOption::LIST_ISSUES:
                issue::readAll(issues);
                utils::printTableHeaders({"ID", "Book ID", "Reader ID", "Issue Date", "Return Date"});
                for (const auto& i : issues) {
                    std::cout << std::left << std::setw(20) << i.id << "|"
                              << std::setw(20) << i.bookId << "|"
                              << std::setw(20) << i.readerId << "|"
                              << std::setw(20) << i.issueDate << "|"
                              << std::setw(20) << i.returnDate << "|\n";
                }
                break;

            case MenuOption::RETURN_BOOK: {
                int id = utils::inputInt("Enter issue ID: ");
                issue::readAll(issues);

                if (issue::isUniqueIssueId(id, issues)) {
                    utils::printError("Issue ID does not exist.");
                    break;
                }

                for (auto& i : issues) {
                    if (i.id == id && i.returnDate.empty()) {
                        i.returnDate = utils::currentDate();
                        issue::update(i);

                        book::readAll(books);
                        auto bookPtr = book::findById(books, i.bookId);
                        if (bookPtr) {
                            bookPtr->copies++;
                            book::update(*bookPtr);
                        }

                        utils::printSuccess("Book returned.");
                        break;
                    }
                }
                break;
            }
            case MenuOption::UPDATE_ISSUE: {
                std::vector<Issue> issues;
                issue::readAll(issues);

                if (issues.empty()) {
                    std::cout << "No issues available to update.\n";
                    break;
                }

                int id;
                std::cout << "Enter the ID of the issue to update: ";
                std::cin >> id;
                std::cin.ignore();

                auto it = std::find_if(issues.begin(), issues.end(),
                                       [id](const Issue& i) { return i.id == id; });

                if (it == issues.end()) {
                    std::cout << "Issue with ID " << id << " not found.\n";
                    break;
                }

                Issue& issueToUpdate = *it;

                std::cout << "Enter new book ID (leave empty to keep \"" << issueToUpdate.bookId << "\"): ";
                std::string input;
                std::getline(std::cin, input);
                if (!input.empty()) issueToUpdate.bookId = std::stoi(input);

                std::cout << "Enter new reader ID (leave empty to keep \"" << issueToUpdate.readerId << "\"): ";
                std::getline(std::cin, input);
                if (!input.empty()) issueToUpdate.readerId = std::stoi(input);

                std::cout << "Enter new issue date (leave empty to keep \"" << issueToUpdate.issueDate << "\"): ";
                std::getline(std::cin, input);
                if (!input.empty()) issueToUpdate.issueDate = input;

                std::cout << "Enter new return date (leave empty to keep \"" << issueToUpdate.returnDate << "\"): ";
                std::getline(std::cin, input);
                if (!input.empty()) issueToUpdate.returnDate = input;

                issue::update(issueToUpdate);
                break;
            }


            case MenuOption::DELETE_ISSUE: {
                int issueId = utils::inputInt("Enter issue ID: ");
                issue::remove(issueId);
                break;
            }


            case MenuOption::GENERATE_REPORT:
                book::readAll(books);
                issue::readAll(issues);
                issue::generateReport(issues, books);
                break;

            default:
                utils::printError("Invalid choice.");
        }
    }
}
