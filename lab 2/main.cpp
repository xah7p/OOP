#include <iostream>
#include "set.h"

void Constructors();
void BasicOps();
void SetRelations();
void Algorithms();

int main() {
    Constructors();

    BasicOps();

    SetRelations();

    Algorithms();

    return 0;
}

void Constructors() {
    Set<int> empty;
    std::cout << "empty: " << empty
              << "  size=" << empty.size()
              << "  isEmpty=" << empty.isEmpty() << "\n";

    Set<int> single{42};
    std::cout << "single{42}: " << single << "\n";

    Set<int> fromCapacity(5);
    std::cout << "fromSize(5): " << fromCapacity
              << "  size=" << fromCapacity.size()
              << "  isEmpty=" << fromCapacity.isEmpty() << "\n";

    int arr[] = {1, 2, 2, 3, 4, 5};
    Set<int> fromRange(arr);
    std::cout << "fromRange(arr): " << fromRange << "\n";

    Set<int> fromList{10, 20, 30, 20};
    std::cout << "fromList{10,20,30,20}: " << fromList << "\n";

    Set<int> copy(fromList);
    std::cout << "copy(fromList): " << copy << "\n";

    Set<int> moved(Set<int>{7, 8, 9});
    std::cout << "moved{7,8,9}: " << moved << "\n";

    Set<int> a{1, 2, 3};
    Set<int> b{4, 5, 6};
    std::cout << "a: " << a << "   b: " << b << "\n";
    a = b;
    std::cout << "a = b -> a: " << a << "\n";

    Set<int> c{100, 200, 300};
    std::cout << "c(before move): " << c << "\n";
    a = std::move(c);
    std::cout << "a = move(c): " << a << "\n";
}

void BasicOps() {
    Set<int> A{1, 2, 3, 4, 5};
    Set<int> B{3, 4, 5, 6, 7};
    std::cout << "A: " << A << "\n";
    std::cout << "B: " << B << "\n";

    std::cout << "A + B: " << (A + B) << "\n";
    std::cout << "A | B: " << (A | B) << "\n";

    Set<int> Au = A;
    Au += B;
    std::cout << "A += B: " << Au << "\n";

    Set<int> Ad = A;
    Ad -= B;
    std::cout << "A -= B: " << Ad << "\n";

    Set<int> Ad2 = A;
    Ad2 /= B;
    std::cout << "A /= B: " << Ad2 << "\n";

    std::cout << "A - B: " << (A - B) << "\n";
    std::cout << "A / B: " << (A / B) << "\n";

    std::cout << "A * B: " << (A * B) << "\n";
    std::cout << "A & B: " << (A & B) << "\n";

    Set<int> Ai = A;
    Ai *= B;
    std::cout << "A *= B: " << Ai << "\n";

    Set<int> Ai2 = A;
    Ai2 &= B;
    std::cout << "A &= B: " << Ai2 << "\n";

    std::cout << "A ^ B: " << (A ^ B) << "\n";

    Set<int> As = A;
    As ^= B;
    std::cout << "A ^= B: " << As << "\n";
}

void SetRelations() {
    Set<int> X{1, 2, 3};
    Set<int> Y{1, 2, 3};
    Set<int> Z{1, 2, 3, 4};
    Set<int> W{2, 3};

    std::cout << "X: " << X << "\n";
    std::cout << "Y: " << Y << "\n";
    std::cout << "Z: " << Z << "\n";
    std::cout << "W: " << W << "\n";

    std::cout << "X == Y: " << (X == Y) << "\n";
    std::cout << "X == Z: " << (X == Z) << "\n";

    auto cmpXZ = (X <=> Z);
    std::cout << "X <=> Z: "
              << (cmpXZ < 0 ? "X < Z" :
                  cmpXZ > 0 ? "X > Z" : "X == Z")
              << "\n";

    std::cout << "W isSubSetOf X: " << W.isSubSetOf(X) << "\n";
    std::cout << "X isSubSetOf Z: " << X.isSubSetOf(Z) << "\n";

    std::cout << "bool(X): " << static_cast<bool>(X) << "\n";
    Set<int> empty;
    std::cout << "bool(empty): " << static_cast<bool>(empty) << "\n";
}

void Algorithms() {
    Set<int> S{1, 2, 3, 4, 5};
    std::cout << "S: " << S << "\n";

    std::cout << "S.contains(3): " << S.contains(3) << "\n";
    std::cout << "S.contains(10): " << S.contains(10) << "\n";

    std::cout << "add(6): " << S.add(6) << "  -> " << S << "\n";
    std::cout << "add(3) again: " << S.add(3) << "  -> " << S << "\n";

    std::cout << "erase(1): " << S.erase(1) << "  -> " << S << "\n";
    std::cout << "erase(100): " << S.erase(100) << "  -> " << S << "\n";

    std::cout << "find(4): ";
    auto it = S.find(4);
    if (it != S.cend())
        std::cout << *it << "\n";
    else
        std::cout << "not found\n";

    std::cout << "iterate: ";
    for (auto cit = S.cbegin(); cit != S.cend(); ++cit)
        std::cout << *cit << " ";
    std::cout << "\n";

    std::cout << "reverse iterate: ";
    for (auto rit = S.crbegin(); rit != S.crend(); ++rit)
        std::cout << *rit << " ";
    std::cout << "\n";

    std::cout << "clear(): ";
    S.clear();
    std::cout << "size=" << S.size()
              << " isEmpty=" << S.isEmpty()
              << " bool(S)=" << static_cast<bool>(S) << "\n";
}
