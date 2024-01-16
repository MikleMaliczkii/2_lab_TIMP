#include "shifr.h"
#include <locale>
#include <algorithm>
#include <vector>
Shifr::Shifr(int columns) : key(columns)
{
    if (key <= 1) {
        throw cipher_error("Invalid key");
    }
}
std::wstring Shifr::encrypt(const std::wstring& open_text)
{
    if (key <= 1) {
        throw cipher_error("Invalid key");
    }

    std::wstring tmp = getValidOpenText(open_text);
    int length = tmp.length();
    int rows = (length + key - 1) / key;
    std::wstring ciphertext;

    if (rows <= 1) {
        throw cipher_error("Invalid key");
    }

    for (int i = key - 1; i >= 0; --i) {
        for (int j = 0; j < rows; ++j) {
            int index = j * key + i;
            if (index < length) {
                ciphertext += tmp[index];
            } else {
                ciphertext += ' ';
            }
        }
    }
    return ciphertext;
}

std::wstring Shifr::decrypt(const std::wstring& cipher_text)
{
    std::wstring tmp = getValidCipherText(cipher_text);
    int length = tmp.length();
    int rows = (length + key - 1) / key;
    std::wstring text;

    for (int i = 0; i < rows; ++i) {
        for (int j = key - 1; j >= 0; --j) {
            int index = i + j * rows;
            if (index < length) {
                text += tmp[index];
            }
        }
    }

    return text;
}

std::wstring Shifr::getValidOpenText(const std::wstring &s)
{
    std::wstring tmp;
    for (size_t i = 0; i < s.size(); i++) {
        wchar_t c = s[i];
        if ((c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я') || c == L'ё' || c == L'Ё' || c==' ') {
            tmp.push_back(std::towupper(c));
        }
    }
    if (tmp.empty()) {
        throw cipher_error("Invalid open text");
    }
    return tmp;
}
std::wstring Shifr::getValidCipherText(const std::wstring &s)
{
    std::wstring tmp;
    for (auto c : s) {
        if (iswupper(c) || c==' ') {
            tmp.push_back(c);
        } else {
            throw cipher_error("Invalid cipher text");
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty cipher text");
    return tmp;
}
