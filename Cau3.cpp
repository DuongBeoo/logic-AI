#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <map>

using namespace std;

bool forall(const vector<int>& domain, const function<bool(int)>& condition) {
    for (int x : domain) {
        if (!condition(x)) {
            return false;
        }
    }
    return true;
}

bool exists(const vector<int>& domain, const function<bool(int)>& condition) {
    for (int x : domain) {
        if (condition(x)) {
            return true;
        }
    }
    return false;
}

int main() {
    size_t domainSize;
    cout << "Nhap kich thuoc mien gia tri: ";
    cin >> domainSize;

    vector<int> domain(domainSize);
    cout << "Nhap cac gia tri trong mien: ";
    for (size_t i = 0; i < domainSize; ++i) {
        cin >> domain[i];
    }

    map<string, function<bool(int)>> predicates;

    size_t predicateCount;
    cout << "Nhap so luong vi tu: ";
    cin >> predicateCount;

    for (size_t i = 0; i < predicateCount; ++i) {
        string predicateName;
        cout << "Nhap ten vi tu khac: ";
        cin >> predicateName;

        cout << "Nhap dinh nghia vi tu: ";
        string definition;
        cin.ignore();
        getline(cin, definition);

        if (definition == "x > 1") {
            predicates[predicateName] = [](int x) { return x > 1; };
        } else if (definition == "x % 2 == 0") {
            predicates[predicateName] = [](int x) { return x % 2 == 0; };
        } else {
            cout << "Dinh nghia vi tu khong duoc ho tro!" << endl;
            return 1;
        }
    }

    bool forallResult = forall(domain, [&](int x) {
        return !predicates["P"](x) || predicates["Q"](x);
    });

    bool existsResult = exists(domain, predicates["P"]);

    bool finalResult = forallResult && existsResult;

    cout << "Ket qua: " << (finalResult ? "Dung" : "Sai") << endl;

    return 0;
}
