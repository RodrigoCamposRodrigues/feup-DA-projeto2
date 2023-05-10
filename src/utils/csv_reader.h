#ifndef PROJETO2DA_CSV_READER_H
#define PROJETO2DA_CSV_READER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "graph.h"


class CsvReader {
public:
    // open the file and read the first line (header)
    CsvReader(std::string fname);
    //read line
    std::vector<std::string> read_line();
    // clear the whole file
    void clear_file();
    // write a line to the file
    void write_line(std::vector<std::string> line);

    // get the header of the file
    std::vector<std::string> get_header() const;
    // goes true if end of file is achieved via read_line()
    bool is_eof() const;

    bool is_error() const;

private:
    std::fstream file_read;
    // std::fstream file_write;
    std::string file_name;

    std::vector<std::string> header;

    bool error = false;
};

#endif //PROJETO2DA_CSV_READER_H