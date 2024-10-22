#include <iostream>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;

string caesarEncrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if (isupper(ch))
            result += char(int(ch + shift - 65) % 26 + 65);
        else if (islower(ch))
            result += char(int(ch + shift - 97) % 26 + 97);
        else
            result += ch;
    }
    return result;
}

string caesarDecrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if (isupper(ch))
            result += char(int(ch - shift - 65 + 26) % 26 + 65);
        else if (islower(ch))
            result += char(int(ch - shift - 97 + 26) % 26 + 97);
        else
            result += ch;
    }
    return result;
}

string vigenereEncrypt(string text, string key) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        int shift = (isupper(key[keyIndex]) ? key[keyIndex] - 65 : key[keyIndex] - 97);
        if (isupper(ch)) {
            result += char(int(ch + shift - 65) % 26 + 65);
            keyIndex = (keyIndex + 1) % key.length();
        } else if (islower(ch)) {
            result += char(int(ch + shift - 97) % 26 + 97);
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            result += ch;
        }
    }
    return result;
}

string vigenereDecrypt(string text, string key) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        int shift = (isupper(key[keyIndex]) ? key[keyIndex] - 65 : key[keyIndex] - 97);
        if (isupper(ch)) {
            result += char(int(ch - shift - 65 + 26) % 26 + 65);
            keyIndex = (keyIndex + 1) % key.length();
        } else if (islower(ch)) {
            result += char(int(ch - shift - 97 + 26) % 26 + 97);
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            result += ch;
        }
    }
    return result;
}

string atbashEncrypt(string text) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if (isupper(ch))
            result += char('Z' - (ch - 'A'));
        else if (islower(ch))
            result += char('z' - (ch - 'a'));
        else
            result += ch;
    }
    return result;
}

string polyalphabeticEncrypt(string text, string key) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if (isupper(ch)) {
            int shift = (key[keyIndex] - 'A') % 26;
            result += char((ch - 'A' + shift) % 26 + 'A');
            keyIndex = (keyIndex + 1) % key.length();
        } else if (islower(ch)) {
            int shift = (key[keyIndex] - 'a') % 26;
            result += char((ch - 'a' + shift) % 26 + 'a');
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            result += ch;
        }
    }
    return result;
}

string polyalphabeticDecrypt(string text, string key) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if (isupper(ch)) {
            int shift = (key[keyIndex] - 'A') % 26;
            result += char((ch - 'A' - shift + 26) % 26 + 'A');
            keyIndex = (keyIndex + 1) % key.length();
        } else if (islower(ch)) {
            int shift = (key[keyIndex] - 'a') % 26;
            result += char((ch - 'a' - shift + 26) % 26 + 'a');
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            result += ch;
        }
    }
    return result;
}

string railFenceEncrypt(string text, int rails) {
    vector<string> fence(rails);
    int row = 0, step = 1;
    for (char c : text) {
        fence[row].push_back(c);
        if (row == 0)
            step = 1;
        else if (row == rails - 1)
            step = -1;
        row += step;
    }
    string result;
    for (string row : fence)
        result += row;
    return result;
}

string railFenceDecrypt(string text, int rails) {
    vector<int> len(rails);
    int row = 0, step = 1;
    for (int i = 0; i < text.length(); i++) {
        len[row]++;
        if (row == 0)
            step = 1;
        else if (row == rails - 1)
            step = -1;
        row += step;
    }
    vector<string> fence(rails);
    int pos = 0;
    for (int r = 0; r < rails; r++) {
        fence[r] = text.substr(pos, len[r]);
        pos += len[r];
    }
    string result;
    row = 0, step = 1;
    vector<int> indices(rails);
    for (int i = 0; i < text.length(); i++) {
        result.push_back(fence[row][indices[row]++]);
        if (row == 0)
            step = 1;
        else if (row == rails - 1)
            step = -1;
        row += step;
    }
    return result;
}

string columnarEncrypt(string text, string key) {
    int col = key.length();
    int row = text.length() / col + (text.length() % col != 0 ? 1 : 0);
    vector<vector<char>> grid(row, vector<char>(col, '_'));
    int pos = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col && pos < text.length(); j++) {
            grid[i][j] = text[pos++];
        }
    }
    string result;
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < row; i++) {
            result += grid[i][j];
        }
    }
    return result;
}

string columnarDecrypt(string text, string key) {
    int col = key.length();
    int row = text.length() / col;
    vector<vector<char>> grid(row, vector<char>(col));
    int pos = 0;
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < row; i++) {
            grid[i][j] = text[pos++];
        }
    }
    string result;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result += grid[i][j];
        }
    }
    return result;
}

int main() {
    int choice;
    string text, key;
    int shift, rails;

    cout << "Choose a cipher:\n";
    cout << "1. Caesar Cipher\n";
    cout << "2. Vigenere Cipher\n";
    cout << "3. Atbash Cipher\n";
    cout << "4. Polyalphabetic Cipher\n";
    cout << "5. Rail Fence Cipher\n";
    cout << "6. Simple Columnar Transposition Cipher\n";
    
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter the text: ";
    getline(cin, text);

    if (choice == 1) {
        cout << "Enter the shift value (1-25): ";
        cin >> shift;

        string encryptedText = caesarEncrypt(text, shift);
        cout << "Encrypted Text: " << encryptedText << endl;

        cout << "Do you want to decrypt the text? (y/n): ";
        char decryptChoice;
        cin >> decryptChoice;
        if (decryptChoice == 'y' || decryptChoice == 'Y') {
            string decryptedText = caesarDecrypt(encryptedText, shift);
            cout << "Decrypted Text: " << decryptedText << endl;
        }
    } else if (choice == 2) {
        cout << "Enter the keyword: ";
        cin >> key;

        string encryptedText = vigenereEncrypt(text, key);
        cout << "Encrypted Text: " << encryptedText << endl;

        cout << "Do you want to decrypt the text? (y/n): ";
        char decryptChoice;
        cin >> decryptChoice;
        if (decryptChoice == 'y' || decryptChoice == 'Y') {
            string decryptedText = vigenereDecrypt(encryptedText, key);
            cout << "Decrypted Text: " << decryptedText << endl;
        }
    } else if (choice == 3) {
        string encryptedText = atbashEncrypt(text);
        cout << "Encrypted Text: " << encryptedText << endl;
    } else if (choice == 4) {
        cout << "Enter the key: ";
        cin >> key;

        string encryptedText = polyalphabeticEncrypt(text, key);
        cout << "Encrypted Text: " << encryptedText << endl;

        cout << "Do you want to decrypt the text? (y/n): ";
        char decryptChoice;
        cin >> decryptChoice;
        if (decryptChoice == 'y' || decryptChoice == 'Y') {
            string decryptedText = polyalphabeticDecrypt(encryptedText, key);
            cout << "Decrypted Text: " << decryptedText << endl;
        }
    } else if (choice == 5) {
        cout << "Enter the number of rails: ";
        cin >> rails;

        string encryptedText = railFenceEncrypt(text, rails);
        cout << "Encrypted Text: " << encryptedText << endl;

        cout << "Do you want to decrypt the text? (y/n): ";
        char decryptChoice;
        cin >> decryptChoice;
        if (decryptChoice == 'y' || decryptChoice == 'Y') {
            string decryptedText = railFenceDecrypt(encryptedText, rails);
            cout << "Decrypted Text: " << decryptedText << endl;
        }
    } else if (choice == 6) {
        cout << "Enter the key: ";
        cin >> key;

        string encryptedText = columnarEncrypt(text, key);
        cout << "Encrypted Text: " << encryptedText << endl;

        cout << "Do you want to decrypt the text? (y/n): ";
        char decryptChoice;
        cin >> decryptChoice;
        if (decryptChoice == 'y' || decryptChoice == 'Y') {
            string decryptedText = columnarDecrypt(encryptedText, key);
            cout << "Decrypted Text: " << decryptedText << endl;
        }
    }

    return 0;
}
