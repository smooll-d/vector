#include "vector.hpp"

#include <iostream>

int main()
{
    smoolld::vector<int> v;
    smoolld::vector<int> x;
    smoolld::vector<int> y { 0, 1, 2, 3 };

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    // new value 8
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);

    x.push_back(69);
    x.push_back(420);
    x.push_back(1337);

    v.clear();

    v.push_back(2);

    /*auto it = v.cbegin() + 4;*/

    /*v.insert(v.cbegin(), x.cbegin(), x.cend());*/

    v.insert(v.cbegin(), { 1337, 420, 69 });

    y = static_cast<smoolld::vector<int>&&>(v);

    x.assign(25ul, 7);

    x.push_back(static_cast<int&&>(3));

    x.emplace(x.begin() + 3, 12349);

    x.resize(50, 69);

    std::cout << (v != x) << '\n';

    smoolld::vector<int> less{ 1, 2, 3 };
    smoolld::vector<int> greater{ 1, 2, 4 };

    /*x.erase(x.begin() + 3);*/

    /*x.erase(x.begin() + 3, x.end());*/

    /*x.emplace_back(2137);*/

    if (less > greater)
    { std::cout << "less is less than greater" << '\n'; }

    std::cout << v << '\n';
    std::cout << '\n';
    std::cout << y << '\n';
    std::cout << '\n';
    std::cout << x << '\n';

    std::cout << (v == x ? "true" : "false") << '\n';

    return 0;
}
