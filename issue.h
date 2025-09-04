#ifndef ISSUE_H
#define ISSUE_H

#include <string>
#include <vector>
#include "book.h"

struct Issue {
    int id;
    int bookId;
    int readerId;
    std::string issueDate;
    std::string returnDate;
};

namespace issue {
    const std::string FILE_NAME = "issues.txt";

    void create(Issue& issue);
    void readAll(std::vector<Issue>& issues);
    void update(Issue& issue);
    void remove(int id);
    void generateReport(const std::vector<Issue>& issues, const std::vector<Book>& books);
    bool isUniqueIssueId(int issueId,const std::vector<Issue>& issue);
}
#endif