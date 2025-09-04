#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

struct Reader {
  int id;
  std::string firstName;
  std::string lastName;
  std::string phone;
};

namespace reader {
  const std::string FILE_NAME = "readers.txt";

  void create(Reader& reader);
  void readAll(std::vector<Reader>& readers);
  Reader* findById(const std::vector<Reader>& readers, int id);
  void update(Reader& reader);
  void remove(int r);
  void searchByName(const std::vector<Reader>& readers, const std::string& name);
  bool isUniqueReaderId(int readerId,const std::vector<Reader>& readers);
}

#endif //READER_H