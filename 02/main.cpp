#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "lib.h"

struct DataRecord {
    std::string field1;
    std::string field2;
    std::string field3;
};

// Function to split a string by delimiter and convert to integers
std::vector<int> parseVersionString(const std::string& version) {
    std::vector<int> parts;
    std::istringstream iss(version);
    std::string part;
    
    while (std::getline(iss, part, '.')) {
        try {
            parts.push_back(std::stoi(part));
        } catch (const std::exception&) {
            // If conversion fails, treat as 0
            parts.push_back(0);
        }
    }
    
    return parts;
}
bool compareVersionReverse(const DataRecord& a, const DataRecord& b) {
    std::vector<int> partsA = parseVersionString(a.field1);
    std::vector<int> partsB = parseVersionString(b.field1);
    
    // Make both vectors the same size by padding with zeros
    size_t maxSize = std::max(partsA.size(), partsB.size());
    partsA.resize(maxSize, 0);
    partsB.resize(maxSize, 0);
    
    // Compare each part numerically (reverse order: greater first)
    for (size_t i = 0; i < maxSize; ++i) {
        if (partsA[i] != partsB[i]) {
            return partsA[i] > partsB[i]; // Reverse order
        }
    }
    
    return false; // Equal
}
int main() {
    std::string line;
    std::vector<DataRecord> record_IPs;
    
    std::cout << "Enter data (Ctrl+D or Ctrl+Z to finish):\n";
    
    while (std::getline(std::cin, line)) {
        
        std::istringstream iss(line);
        std::string field1, field2, field3;
        
        if (line == "q" || line == "Q") {
            std::cout << "Input terminated by user.\n";
            break;
        }
        
        // Read three fields separated by tabs
        if (std::getline(iss, field1, '\t') &&
            std::getline(iss, field2, '\t') &&
            std::getline(iss, field3)) {
            
            DataRecord record = {field1, field2, field3};
            record_IPs.push_back(record);
            
            std::cout << "Read: [" << field1 << "] [" << field2 << "] [" << field3 << "]\n";
        } else {
            std::cerr << "Error: Invalid format in line: " << line << std::endl;
        }
    }
    
    std::cout << "\nTotal records read: " << record_IPs.size() << std::endl;

    // Sort records by field1 in reverse lexicographical order
    std::sort(record_IPs.begin(), record_IPs.end(), compareVersionReverse);
    
// Display all records after sorting
std::cout << "\nRecords sorted by field1 (reverse lexicographical):\n";
for (size_t i = 0; i < record_IPs.size(); ++i) {
    std::cout << "Record " << (i + 1) << ": "
              << record_IPs[i].field1 << " | "
              << record_IPs[i].field2 << " | "
              << record_IPs[i].field3 << std::endl;
    
            }

std::cout << "\nRecords started with 1:\n";
for(const auto& record :record_IPs){
    if(record.field1.length() >=2 &&
        record.field1[0] =='1' &&
        record.field1[1] == '.')
        {
            std::cout<<record.field1<< " ("<<record.field2 <<")\n";
        }
    }



std::cout << "\nRecords started with 46.70:\n";
for (const auto& record : record_IPs)
{
    if(record.field1.length() >=6 &&
    record.field1.substr(0,6) == "46.70." )
    {
        std::cout<<record.field1<< " ("<<record.field2 <<")\n";
    }
}

std::cout << "\nRecords has 46:\n";
for (const auto& record : record_IPs)
{
    std::vector<int> parts = parseVersionString(record.field1);
    bool contains46 = false;
    for (int part : parts){
        if(part ==46){
            contains46 = true;
            break;
        }
    }
    if(contains46){
        std::cout<<record.field1<< " ("<<record.field2 <<")\n";
    }
}

return 0;
}
/// test case
/*
1.2.1.1    server1    active
1.10.1.1    server2    inactive
2.1.1.1    server3    active
1.1.1.1    server4    inactive

*/