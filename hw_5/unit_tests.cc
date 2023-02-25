#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include <stdio.h>
#include "utilities.h"
#include "gtest/gtest.h"

using namespace std;

    TEST(utilities, SortByMagnitude) {
        vector<double> list{-2.2, -1.0, 0.4, 5.4, 10.5};
        sort_by_magnitude(list);
        EXPECT_EQ(list[0], 0.4);
        EXPECT_EQ(list[1], -1.0);
        EXPECT_EQ(list[2], -2.2);
        EXPECT_EQ(list[3], 5.4);
        EXPECT_EQ(list[4], 10.5);
    }

    TEST(utilities, ReadMatrixCSV) {
        string invalidCsvPath = "./ReadInvalid.csv";
        EXPECT_THROW(read_matrix_csv(invalidCsvPath), exception);

        string validCsvPath = "./Myfile.csv";
        TypedArray<TypedArray<double>> csvMtx = read_matrix_csv(validCsvPath);

        EXPECT_EQ(csvMtx.get(0).get(0), 1.0);
        EXPECT_EQ(csvMtx.get(0).get(1), 2.0);
        EXPECT_EQ(csvMtx.get(0).get(2), 3.0);

        EXPECT_EQ(csvMtx.get(1).get(0), 2.7);
        EXPECT_EQ(csvMtx.get(1).get(1), 3.8);
        EXPECT_EQ(csvMtx.get(1).get(2), 5.3);

        EXPECT_EQ(csvMtx.get(2).get(0), 3.5);
        EXPECT_EQ(csvMtx.get(2).get(1), 7.7);
        EXPECT_EQ(csvMtx.get(2).get(2), 8.1);

    }

    TEST(utilities, WriteMatrixCSV) {
        TypedArray<TypedArray<double>> csvData;
        TypedArray<double> first, second, third;
        first.push(1); first.push(2); first.push(3); first.push(4); 
        second.push(5); second.push(6); second.push(7); second.push(8);
        third.push(9); third.push(10); third.push(11); third.push(12);
        csvData.push(first);
        csvData.push(second);
        csvData.push(third);

        // invalid path
        string invalidCsvPath = "WriteInvalid/WriteInvalid";
        EXPECT_THROW(write_matrix_csv(csvData, invalidCsvPath), exception);

        // valid path
        string validCsvPath = "./WriteCSV.csv";
        write_matrix_csv(csvData, validCsvPath);
       
        //Check if they are the same matrix
        TypedArray<TypedArray<double>> newCsvData = read_matrix_csv(validCsvPath);
        EXPECT_EQ(csvData.size(), newCsvData.size());
        for(int i=0; i<csvData.size(); ++i) {
            EXPECT_EQ(csvData.safe_get(i).size(), newCsvData.safe_get(i).size());
            for(int j=0; j<csvData.safe_get(i).size(); ++j)
                EXPECT_EQ(csvData.safe_get(i).safe_get(j), newCsvData.safe_get(i).safe_get(j));
        }
    }

    TEST(utilities, OccurrenceMap) {
        
        // try invalid path
        string invalidTxtPath = "MapInvalid/MapInvalid";
        EXPECT_THROW(occurrence_map(invalidTxtPath), exception);
        
        // try valid path
        string validTxtPath = "./Myfile.txt";
        map<string, int> res = occurrence_map(validTxtPath);
        EXPECT_EQ(res["is"], 4);
        EXPECT_EQ(res["blah"], 3);
        EXPECT_EQ(res["10xgenomics"], 1);
        EXPECT_EQ(res["wier_d"], 0);
    }