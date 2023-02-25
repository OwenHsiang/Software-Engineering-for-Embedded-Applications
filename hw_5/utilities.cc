#include <bits/stdc++.h>
#include "utilities.h"

using namespace std;

void sort_by_magnitude(vector<double> &arr) {
    sort(arr.begin(), arr.end(), [](const double &a, const double &b)
    { 
        return abs(a) < abs(b); 
    });
}

TypedArray<TypedArray<double>> read_matrix_csv(const string path) {
    
    TypedArray<TypedArray<double>> res;
    try {
        // check if path is valid
        ifstream f(path.c_str());
        if(!f.good()) throw logic_error("Path is invalid:" + path);

        string line;
        size_t row_count = 0;

        while(getline(f, line)) {
            stringstream ss(line);
            string cell;
            TypedArray<double> row;
            while (getline(ss, cell, ',')) {
                if (cell.empty()) {
                    throw invalid_argument("errors in the format: " + path);
                }
                stringstream cell_ss(cell);
                double value;
                if (!(cell_ss >> value)) {
                    throw invalid_argument("errors in the format: " + path);
                }
                row.set(row.size(), value);
            }
            if (res.size() > 0 && row.size() != res.safe_get(0).size()) {
                throw invalid_argument("errors in the format: " + path);
            }
            res.set(res.size(), row);
            row_count++;
        }
        if (res.size() == 0) {
            throw invalid_argument("Empty file: " + path);
        }
    }

    catch(const exception& e) {
        cout << "[read_matrix_csv] Error: " << e.what() << endl;
        throw logic_error(e.what());
    }        
    return res;     
}

void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path) {
    try {
        // make a file
        ofstream f;
        f.open(path.c_str());
        if (!f.is_open()) throw logic_error("Cannot open file.");
        int row = matrix.size();
        for(int i=0; i<row; ++i) {
            string line;
            int colsize = matrix.safe_get(i).size();
            for(int j=0; j<colsize; ++j)
                line += (to_string(matrix.safe_get(i).safe_get(j)) + ",");
            line.pop_back();
            f << line << "\n";
        }
        f.close();    
    }

    catch(const exception& e) {
        cout << "[write_matrix_csv] Error: " << e.what() << endl;
        throw logic_error(e.what());
    }
}

// determine whether the string is valid
bool IsValidStr(string &str) {    
    // empty string is invalid
    if(str.length() == 0) return false;

    // transform to lower letter
    transform(str.begin(), str.end(), str.begin(), [](unsigned char v){ return tolower(v); });

    // erase invalid punctuations
    unordered_set<char> InvalidPunc = {',', '.', '!', '?', ':', ';','\r', '\n', '\"', '\'', '(', ')'};
    while(InvalidPunc.count(str.front()))
        str = str.substr(1);
    while(InvalidPunc.count(str.back()))
        str = str.substr(0, str.length()-1);
    if(str.length() == 0) return false;

    // exclude invalid words
    for(auto &v : str) {
        if(!isdigit(v) && !islower(v) && v != '\'')
            return false;
    }

    return true;
}

map<string, int> occurrence_map(const string path) {
    try {
        // check if path is valid
        ifstream f(path.c_str());
        if(!f.good()) throw logic_error("Path is invalid:" + path);
        map<string, int> res;
        string line;
        while(getline(f, line)) {
            string word;
            stringstream sstream(line.c_str());
            while (getline(sstream, word, ' ')) {
                if(IsValidStr(word))
                    res[word]++;
            }
        }
        return res;
    }

    catch(const exception& e) {
        cout << "[write_matrix_csv] Error: " << e.what() << endl;
        throw logic_error(e.what());
    }
}