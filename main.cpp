#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <typename T> struct Show {
    static std::string str(const T &v) {
        std::ostringstream os;
        os << v;
        return os.str();
    }
};

// TODO: a full specialization of Show for bool  (true -> yes, false -> no)
template <> struct Show<bool> {
    static std::string str(const bool &v) {
        if (v) {
            return "yes";
        } else {
            return "no";
        }
    }
};

// TODO: a full specialization of Show for std::string  (wrap the text in double
// quotes)
template <> struct Show<std::string> {
    static std::string str(const std::string &v) { return "\"" + v + "\""; }
};

// The partial specialization for vectors: writing "[a, b, c]" is the part you
// add.
template <typename T> struct Show<std::vector<T>> {
    static std::string str(const std::vector<T> &v) {
        std::string s = "[";
        for (std::size_t i = 0; i < v.size(); ++i) {
            if (i != 0) {
                s += ", ";
            }
            s += Show<T>::str(v[i]);
        }
        s += "]";
        return s;
    }
};

template <typename T> std::vector<T> readList() {
    int n;
    std::cin >> n;
    std::vector<T> v;
    for (int i = 0; i < n; ++i) {
        T x;
        std::cin >> x;
        v.push_back(x);
    }
    return v;
}

template <typename T> std::vector<std::vector<T>> readRows() {
    int k;
    std::cin >> k;
    std::vector<std::vector<T>> rows;
    for (int i = 0; i < k; ++i)
        rows.push_back(readList<T>());
    return rows;
}

template <typename T> void print(const T &v) {
    std::cout << Show<T>::str(v) << "\n";
}

int main() {
    std::string kind;
    while (std::cin >> kind) {
        if (kind == "int") {
            int x;
            std::cin >> x;
            print(x);
        } else if (kind == "bool") {
            bool x;
            std::cin >> x;
            print(x);
        } else if (kind == "word") {
            std::string x;
            std::cin >> x;
            print(x);
        } else if (kind == "ints")
            print(readList<int>());
        else if (kind == "bools")
            print(readList<bool>());
        else if (kind == "words")
            print(readList<std::string>());
        else if (kind == "rows")
            print(readRows<int>());
        else if (kind == "boolrows")
            print(readRows<bool>());
        else if (kind == "wordrows")
            print(readRows<std::string>());
    }
    return 0;
}
