#include <iostream>
#include <vector>
#include <list>
#include "set.h"

void Constructors();
void Assignments();
void ElementOps();
void SetOps();
void SetRelations();
void Iterators();
void AlgorithmsLike();

int main() {
    Constructors();
    std::cout << "-------------------------\n";

    Assignments();
    std::cout << "-------------------------\n";

    ElementOps();
    std::cout << "-------------------------\n";

    SetOps();
    std::cout << "-------------------------\n";

    SetRelations();
    std::cout << "-------------------------\n";

    Iterators();
    std::cout << "-------------------------\n";

    AlgorithmsLike();
    return 0;
}

void Constructors() {
    std::cout << "[Constructors]\n";

    Set<int> empty;
    std::cout << "empty: " << empty
              << " size=" << empty.size()
              << " isEmpty=" << empty.isEmpty() << "\n";

    Set<int> il{42};
    std::cout << "initializer_list ctor: " << il << "\n";

    int arr[] = {1, 2, 3, 4, 5};
    Set<int> fromArray(static_cast<int>(std::size(arr)), arr);
    std::cout << "array ctor: " << fromArray << "\n";

    double darr[] = {1.1, 2.9, 3.5};
    Set<int> fromOtherArray(static_cast<int>(std::size(darr)), darr);
    std::cout << "array<U> ctor: " << fromOtherArray << "\n";

    Set<int> copyCtor(fromArray);
    std::cout << "copy ctor: " << copyCtor << "\n";

    Set<int> moveCtor(Set<int>{7, 8, 9});
    std::cout << "move ctor: " << moveCtor << "\n";

    Set<long> longSet{10, 20, 30};
    Set<int> fromOtherSet(longSet);
    std::cout << "Set<U> copy ctor: " << fromOtherSet << "\n";

    Set<int> fromMovedOtherSet(Set<long>{100, 200, 300});
    std::cout << "Set<U> move ctor: " << fromMovedOtherSet << "\n";

    Set<int> fromInitOther{1.2, 2.8, 3.1};
    std::cout << "initializer_list<U> ctor: " << fromInitOther << "\n";

    std::vector<int> v{11, 22, 33};
    Set<int> fromRange(v);
    std::cout << "range ctor from vector: " << fromRange << "\n";

    Set<int> fromIter(v.begin(), v.end());
    std::cout << "iterator ctor: " << fromIter << "\n";
}

void Assignments() {
    std::cout << "[Assignments]\n";

    Set<int> a{1, 2, 3};
    Set<int> b{4, 5, 6};
    std::cout << "before: a=" << a << " b=" << b << "\n";

    a = b;
    std::cout << "a = b -> " << a << "\n";

    Set<int> c{100, 200, 300};
    a = std::move(c);
    std::cout << "a = move(c) -> " << a << "\n";

    a = {7, 8, 9};
    std::cout << "a = {7,8,9} -> " << a << "\n";

    Set<long> ls{1000, 2000, 3000};
    a = ls;
    std::cout << "a = Set<long> -> " << a << "\n";

    a = Set<long>{9, 8, 7};
    std::cout << "a = Set<long>{...} -> " << a << "\n";

    a = {1.5, 2.5, 3.5};
    std::cout << "a = initializer_list<double> -> " << a << "\n";

    std::vector<int> vec{13, 14, 15};
    a = vec;
    std::cout << "a = vector<int> -> " << a << "\n";
}

void ElementOps() {
    std::cout << "[ElementOps]\n";

    Set<int> s{2, 4, 6};
    std::cout << "start: " << s << "\n";

    std::cout << "contains(4): " << s.contains(4) << "\n";
    std::cout << "contains(5): " << s.contains(5) << "\n";

    std::cout << "add(8): " << s.add(8) << " -> " << s << "\n";
    std::cout << "add(4): " << s.add(4) << " -> " << s << "\n";

    s += 10;
    std::cout << "s += 10 -> " << s << "\n";

    auto plusElem = s + 12;
    std::cout << "s + 12 -> " << plusElem << "\n";
    std::cout << "s after + 12 -> " << s << "\n";

    std::cout << "erase(2): " << s.erase(2) << " -> " << s << "\n";
    std::cout << "erase(111): " << s.erase(111) << " -> " << s << "\n";

    s -= 4;
    std::cout << "s -= 4 -> " << s << "\n";

    auto minusElem = s - 6;
    std::cout << "s - 6 -> " << minusElem << "\n";
    std::cout << "s after - 6 -> " << s << "\n";

    !s;
    std::cout << "!s -> " << s << " size=" << s.size()
              << " isEmpty=" << s.isEmpty() << "\n";
}

void SetOps() {
    std::cout << "[SetOps]\n";

    Set<int> A{1, 2, 3, 4, 5};
    Set<int> B{3, 4, 5, 6, 7};

    std::cout << "A: " << A << "\n";
    std::cout << "B: " << B << "\n";

    Set<int> u1 = A;
    u1.unity(B);
    std::cout << "A.unity(B) -> " << u1 << "\n";

    Set<int> u2 = A;
    u2 += B;
    std::cout << "A += B -> " << u2 << "\n";

    Set<int> u3 = A;
    u3 |= B;
    std::cout << "A |= B -> " << u3 << "\n";

    std::cout << "A + B -> " << (A + B) << "\n";
    std::cout << "A | B -> " << (A | B) << "\n";

    Set<int> d1 = A;
    d1.difference(B);
    std::cout << "A.difference(B) -> " << d1 << "\n";

    Set<int> d2 = A;
    d2 -= B;
    std::cout << "A -= B -> " << d2 << "\n";

    Set<int> d3 = A;
    d3 /= B;
    std::cout << "A /= B -> " << d3 << "\n";

    std::cout << "A - B -> " << (A - B) << "\n";
    std::cout << "A / B -> " << (A / B) << "\n";

    Set<int> i1 = A;
    i1.intersection(B);
    std::cout << "A.intersection(B) -> " << i1 << "\n";

    Set<int> i2 = A;
    i2 *= B;
    std::cout << "A *= B -> " << i2 << "\n";

    Set<int> i3 = A;
    i3 &= B;
    std::cout << "A &= B -> " << i3 << "\n";

    std::cout << "A * B -> " << (A * B) << "\n";
    std::cout << "A & B -> " << (A & B) << "\n";

    Set<int> s1 = A;
    s1.symmetric_difference(B);
    std::cout << "A.symmetric_difference(B) -> " << s1 << "\n";

    Set<int> s2 = A;
    s2 ^= B;
    std::cout << "A ^= B -> " << s2 << "\n";

    std::cout << "A ^ B -> " << (A ^ B) << "\n";
}

void SetRelations() {
    std::cout << "[SetRelations]\n";

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

    auto cmpXY = (X <=> Y);
    auto cmpXZ = (X <=> Z);
    auto cmpZX = (Z <=> X);

    std::cout << "X <=> Y: "
              << (cmpXY < 0 ? "X < Y" : cmpXY > 0 ? "X > Y" : "X == Y") << "\n";
    std::cout << "X <=> Z: "
              << (cmpXZ < 0 ? "X < Z" : cmpXZ > 0 ? "X > Z" : "X == Z") << "\n";
    std::cout << "Z <=> X: "
              << (cmpZX < 0 ? "Z < X" : cmpZX > 0 ? "Z > X" : "Z == X") << "\n";

    std::cout << "X.equal(Y): " << X.equal(Y) << "\n";
    std::cout << "X.notEqual(Z): " << X.notEqual(Z) << "\n";
    std::cout << "X.less(Z): " << X.less(Z) << "\n";
    std::cout << "X.lessEqual(Y): " << X.lessEqual(Y) << "\n";
    std::cout << "Z.greater(X): " << Z.greater(X) << "\n";
    std::cout << "Z.greaterEqual(X): " << Z.greaterEqual(X) << "\n";

    std::cout << "W.isSubSetOf(X): " << W.isSubSetOf(X) << "\n";
    std::cout << "X.isSubSetOf(Z): " << X.isSubSetOf(Z) << "\n";
    std::cout << "Z.isSuperSetOf(W): " << Z.isSuperSetOf(W) << "\n";
    std::cout << "X.isSuperSetOf(Z): " << X.isSuperSetOf(Z) << "\n";

    std::cout << "bool(X): " << static_cast<bool>(X) << "\n";
    Set<int> empty;
    std::cout << "bool(empty): " << static_cast<bool>(empty) << "\n";
}

void Iterators() {
    std::cout << "[Iterators]\n";

    Set<int> S{1, 2, 3, 4, 5};
    std::cout << "S: " << S << "\n";

    std::cout << "begin/end: ";
    for (auto it = S.begin(); it != S.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "cbegin/cend: ";
    for (auto it = S.cbegin(); it != S.cend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "rbegin/rend: ";
    for (auto it = S.rbegin(); it != S.rend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "crbegin/crend: ";
    for (auto it = S.crbegin(); it != S.crend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}

void AlgorithmsLike() {
    std::cout << "[AlgorithmsLike]\n";

    Set<int> S{1, 2, 3, 4, 5};
    std::cout << "S: " << S << "\n";

    std::cout << "size: " << S.size() << "\n";
    std::cout << "isEmpty: " << S.isEmpty() << "\n";

    std::cout << "contains(3): " << S.contains(3) << "\n";
    std::cout << "contains(10): " << S.contains(10) << "\n";

    std::cout << "clear -> ";
    S.clear();
    std::cout << S << " size=" << S.size()
              << " isEmpty=" << S.isEmpty()
              << " bool=" << static_cast<bool>(S) << "\n";

    std::list<int> lst{9, 8, 7};
    Set<int> fromListIter(lst.begin(), lst.end());
    std::cout << "from list iterators: " << fromListIter << "\n";
}
