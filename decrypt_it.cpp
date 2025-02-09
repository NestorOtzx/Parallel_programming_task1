#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <locale>
#include <codecvt>

using namespace std;


//these are used to avoid problems with linux/windows accent differences
//
std::wstring stringAwstring(const std::string str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}
//
std::string wstringAstring(const std::wstring wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

std::wstring removeAccents(const std::wstring text) {
    std::unordered_map<wchar_t, wchar_t> acc = {
        {L'á', L'a'}, {L'é', L'e'}, {L'í', L'i'}, {L'ó', L'o'}, {L'ú', L'u'},
        {L'Á', L'A'}, {L'É', L'E'}, {L'Í', L'I'}, {L'Ó', L'O'}, {L'Ú', L'U'}
    };

    std::wstring res = text;

    for (wchar_t& c : res) {
        if (acc.find(c) != acc.end()) {
            c = acc[c];
        }
    }

    return res;
}


//text to lower
string normalize(const string input) {
    string normalized;
    string noacc = wstringAstring(removeAccents(stringAwstring(input)));

    for (size_t i = 0; i < noacc.size(); ++i) {
        string current(1, noacc[i]);
        if (isalpha(noacc[i])) {
            normalized += tolower(noacc[i]);
        } else {
            normalized += noacc[i];
        }
    }
    return normalized;
}


string cesarCipher(const string text, int shift) {
    string ciphered;

    for (char c : text) {
        if (isalpha(c)) {
            char base = 'a';
            ciphered += (c - base + shift + 26) % 26 + base;
        } else {
            ciphered += c; //keep spaces and all that
        }
    }

    return ciphered;
}

int main(int argc, char*argv[]) {
    if (argc < 3 ){ 
        return -1;
    }

    int offset = atoi(argv[1]);
    string normalized = normalize(string(argv[2]));
    string ans = cesarCipher(normalized, -offset);
    std::cout<<offset<<" \""<<ans<<"\""<<std::endl;
    return 0;
}