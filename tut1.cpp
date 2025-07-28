#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

long long convertToDecimal(const string& value, int base) {
    long long result = 0;
    long long power = 1;
    
    for (int i = value.length() - 1; i >= 0; i--) {
        char c = value[i];
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            throw invalid_argument("Invalid character in number");
        }
        
        if (digit >= base) {
            throw invalid_argument("Digit exceeds base");
        }
        
        result += digit * power;
        power *= base;
    }
    
    return result;
}

double lagrangeInterpolation(const vector<pair<int, long long>>& points, int x = 0) {
    double result = 0.0;
    int n = points.size();
    
    for (int i = 0; i < n; i++) {
        double term = points[i].second;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (double)(x - points[j].first) / (points[i].first - points[j].first);
            }
        }
        
        result += term;
    }
    
    return result;
}

long long processTestCase(const vector<pair<int, pair<int, string>>>& testData, int k) {
    vector<pair<int, long long>> points;
    
    for (const auto& data : testData) {
        int x = data.first;
        int base = data.second.first;
        string value = data.second.second;
        
        long long y = convertToDecimal(value, base);
        points.push_back({x, y});
        
        cout << "Point: (" << x << ", " << y << ") [decoded from base " << base << "]" << endl;
    }
    
    sort(points.begin(), points.end());
    points.resize(k);
    
    double constant = lagrangeInterpolation(points, 0);
    
    return (long long)round(constant);
}

int main() {
    try {
        cout << "=== Test Case 1 ===" << endl;
        vector<pair<int, pair<int, string>>> testCase1 = {
            {1, {10, "4"}},
            {2, {2, "111"}},
            {3, {10, "12"}},
            {6, {4, "213"}}
        };
        
        long long secret1 = processTestCase(testCase1, 3);
        cout << "Secret (constant term): " << secret1 << endl << endl;
        
        cout << "=== Test Case 2 ===" << endl;
        vector<pair<int, pair<int, string>>> testCase2 = {
            {1, {6, "13444211440455345511"}},
            {2, {15, "aed7015a346d63"}},
            {3, {15, "6aeeb69631c227c"}},
            {4, {16, "e1b5e05623d881f"}},
            {5, {8, "316034514573652620673"}},
            {6, {3, "2122212201122002221120200210011020220200"}},
            {7, {3, "20120221122211000100210021102001201112121"}},
            {8, {6, "20220554335330240002224253"}},
            {9, {12, "45153788322a1255483"}},
            {10, {7, "1101613130313526312514143"}}
        };
        
        long long secret2 = processTestCase(testCase2, 7);
        cout << "Secret (constant term): " << secret2 << endl << endl;
        
        cout << "=== Final Results ===" << endl;
        cout << "Test Case 1 Secret: " << secret1 << endl;
        cout << "Test Case 2 Secret: " << secret2 << endl;
        
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}