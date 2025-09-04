#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <vector>

struct Author {
    int id;
    std::string firstName;
    std::string lastName;
};

namespace author {
    const std::string FILE_NAME = "authors.txt";

    void create(Author& author);
    void readAll(std::vector<Author>& authors);
    Author* findById(const std::vector<Author>& authors, int id);
    void update(Author& author);
    void remove(int id);
    void searchByName(const std::vector<Author>& authors, const std::string& name);
    bool isAuthorId(int authorId, const std::vector<Author>& authors);
}

#endif //AUTHOR_H