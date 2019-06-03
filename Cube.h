
#include <iostream>
#include <array>
#include <string>

class Cube {
private:
  std::array<int, 8> perm;
  std::array<int, 8> orient;
public:
  Cube();
  void turnRight(const int &n);
  void turnUp(const int &n);
  void turnFront(const int &n);
  std::array<std::array<int, 4>, 6> toFacelet();
  void print();
};
