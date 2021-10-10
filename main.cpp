#include <iostream>
#include <string>
#include <cstring>
#include "md5.h"
#include "md5.cpp"

using namespace std;
int main() {
    string pass = "aaaaaa";
    string magic = "$1$";
    string salt = "4fTgjp6q";
    string hash = "ihqYanxbDwUOlJEV9cUTB/";
    bool found = false;
    while ((pass != "zzzzzz") && !found) {
        unsigned char *altsum = MD5(pass + salt + pass).digest;
        string x = "";
        for (int i = 0; i < 6; ++i) {
            x.push_back(altsum[i]);
        }
        unsigned char *intsum = MD5(pass + magic + salt + x + pass[0] + '\0' + '\0').digest;
        for (int i = 0; i < 1000; ++i) {
            string inter_sum = "";
            for (int j = 0; j < 16; ++j) {
                inter_sum.push_back(intsum[j]);
            }
            string temp = "";
            if (i % 2 == 0) {
                temp += inter_sum;
            }
            if (i % 2 == 1) {
                temp += pass;
            }
            if (!(i % 3 == 0)) {
                temp += salt;
            }
            if (!(i % 7 == 0)) {
                temp += pass;
            }
            if (i % 2 == 0) {
                temp += pass;
            }
            if (i % 2 == 1) {
                temp += inter_sum;
            }
            intsum = MD5(temp).digest;
        }

        unsigned char order[16];

        order[0] = intsum[11];
        order[1] = intsum[4];
        order[2] = intsum[10];
        order[3] = intsum[5];
        order[4] = intsum[3];
        order[5] = intsum[9];
        order[6] = intsum[15];
        order[7] = intsum[2];
        order[8] = intsum[8];
        order[9] = intsum[14];
        order[10] = intsum[1];
        order[11] = intsum[7];
        order[12] = intsum[13];
        order[13] = intsum[0];
        order[14] = intsum[6];
        order[15] = intsum[12];

        string crypt64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        unsigned long long first_char = (0 | order[13] << 16) | (order[14] << 8) | order[15];
        unsigned long long second_char = (0 | order[10] << 16) | (order[11] << 8) | order[12];
        unsigned long long third_char = (0 | order[7] << 16) | (order[8] << 8) | order[9];
        unsigned long long fourth_char = (0 | order[4] << 16) | (order[5] << 8) | order[6];
        unsigned long long fifth_char = (0 | order[1] << 16) | (order[2] << 8) | order[3];
        unsigned long long sixth_char = 0 | order[0];

        string answer = "";
        int y = 0;

        while (first_char != 0) {
            y = first_char % 64;
            answer += crypt64[y];
            first_char = first_char >> 6;
        }
        while (second_char != 0) {
            y = second_char % 64;
            answer += crypt64[y];
            second_char = second_char >> 6;
        }
        while (third_char != 0) {
            y = third_char % 64;
            answer += crypt64[y];
            third_char = third_char >> 6;
        }
        while (fourth_char != 0) {
            y = fourth_char % 64;
            answer += crypt64[y];
            fourth_char = fourth_char >> 6;
        }
        while (fifth_char != 0) {
            y = fifth_char % 64;
            answer += crypt64[y];
            fifth_char = fifth_char >> 6;
        }
        while (sixth_char != 0) {
            y = sixth_char % 64;
            answer += crypt64[y];
            sixth_char = sixth_char >> 6;
        }
        cout << pass << endl << answer << endl;

        if(answer == hash)  {
            cout << "Password is: " << pass << endl;
            found = true;
        }

        if (pass[5] == 'z') {
            if (pass[4] == 'z') {
                if (pass[3] == 'z') {
                    if (pass[2] == 'z') {
                        if (pass[1] == 'z') {
                            pass[0]++;
                            pass[1] = 'a';
                            pass[2] = 'a';
                            pass[3] = 'a';
                            pass[4] = 'a';
                            pass[5] = 'a';
                        }
                        else {
                            pass[1]++;
                            pass[2] = 'a';
                            pass[3] = 'a';
                            pass[4] = 'a';
                            pass[5] = 'a';
                        }
                    }
                    else {
                        pass[2]++;
                        pass[3] = 'a';
                        pass[4] = 'a';
                        pass[5] = 'a';
                    }
                }
                else {
                    pass[3]++;
                    pass[4] = 'a';
                    pass[5] = 'a';
                }
            }
            else {
                pass[4]++;
                pass[5] = 'a';
            }
        }
        else {
            pass[5]++;
        }
    }
    return 0;
}
