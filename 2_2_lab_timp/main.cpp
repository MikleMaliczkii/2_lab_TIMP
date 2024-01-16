#include <iostream>
#include "shifr.h"
void check(const std::wstring& Text, const int key, const bool
           destructCipherText=false)
{
    try {
        std::wstring cipherText;
        std::wstring decryptedText;
        Shifr cipher(key);
        cipherText = cipher.encrypt(Text);
        if(destructCipherText) {
            cipherText+=L' ';
        }
        decryptedText = cipher.decrypt(cipherText);
        std::wcout << L"key=" << key << std::endl;
        std::wcout << Text << std::endl;
        std::wcout << cipherText << std::endl;
        std::wcout << decryptedText << std::endl;
    } catch (const cipher_error & e) {
        std::wcerr << L"Error: " << e.what() << std::endl;
    }
}
int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int columns;
    std::wcout << L" Введите количество столбцов в таблице: ";
    std::wcin >> columns;
    std::wcin.ignore();
    std::wstring text;
    std::wcout << L" Введите текст для шифрования: ";
    getline(std::wcin, text);
    check(text, columns);
    return 0;
}
