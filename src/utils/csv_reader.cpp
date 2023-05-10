#include "csv_reader.h"
#include "graph.h"
#include <iostream>

CsvReader::CsvReader(std::string fname) : file_name(fname) {
    this->file_read = std::fstream (fname);
    // this->file_write = std::fstream(fname, std::ios::app);

    // simple error handling
    if(!this->file_read /*|| !this->file_write*/) {
        this->error = true;
        return;
    }

    // read the header of the csv
    std::string line;
    std::getline(this->file_read, line);
    std::stringstream ss(line); 

    std::string s;
    while(std::getline(ss, s, ',')) {
        this->header.push_back(s);
    }
}

std::vector<std::string> CsvReader::read_line(){
    std::string line;
    std::vector<std::string> words;

    //while line != empty, read
    if(std::getline(file_read, line)){
        std::stringstream ss(line);
        std::string word;
        while(std::getline(ss, word, ',')){
            words.push_back(word);
        }
    }

    return words;

}


// void CsvReader::clear_file() {
//     this->file_write.close();
//     this->file_write.open(this->file_name, ios::out | ios::trunc);
//     this->file_write.close();
//     this->file_write.open(this->file_name, ios::app);
// }

// void CsvReader::write_line(vector<string> line) {
//     string result;

//     for(string s : line) {
//         result += s + ",";
//     }

//     // remove the last ","
//     result.pop_back();

//     file_write << result << endl;
// }

// vector<string> CsvReader::get_header() const {
//     return header;
// }

bool CsvReader::is_eof() const {
    return this->file_read.eof();
}

bool CsvReader::is_error() const {
    return this->error;
}
