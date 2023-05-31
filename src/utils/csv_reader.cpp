#include "csv_reader.h"
#include "graph.h"
#include <iostream>

/// @brief Constroí um objeto CsvReader, responsável por ler arquivos csv.
/// @param fname Nome do arquivo csv.
CsvReader::CsvReader(std::string fname) : file_name(fname) {
    this->file_read = std::fstream(fname);
    // this->file_write = std::fstream(fname, std::ios::app);

    // simple error handling
    if(!this->file_read.is_open() /*|| !this->file_write*/) {
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

/// @brief Lê uma linha do arquivo csv.
/// @return Vetor de strings, onde cada string é um campo da linha.
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

/// @brief Verifica se o arquivo csv chegou ao fim.
/// @return True se o arquivo chegou ao fim, false caso contrário.
bool CsvReader::is_eof() const {
    return this->file_read.eof();
}

/// @brief Verifica se houve algum erro ao abrir o arquivo csv.
/// @return True se houve erro, false caso contrário.
bool CsvReader::is_error() const {
    return this->error;
}
