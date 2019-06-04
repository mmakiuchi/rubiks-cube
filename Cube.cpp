#include <iostream>
#include <array>
#include <random>

#include "Cube.h"

Cube::Cube() {
  perm = {0,1,2,3,4,5,6};
  orient = {0,0,0,0,0,0,0};
};

/**
 * Turns right face 
 * @param &n if n=1, turn 90 degrees clockwise, if n=2, turn 180 degrees, if n=3, turn 90 degrees anti-clockwise,
 */
void Cube::turnRight(const int &n) {
  std::array<int, 7> new_perm, new_orient;
  std::copy(perm.begin(), perm.end(), new_perm.begin());
  std::copy(orient.begin(), orient.end(), new_orient.begin());

  int rotation[4] = {5, 4, 1, 2};
  int orient_delta[4] = {0, 1, 0, 1};
  for(int i = 0; i < 4; i++) {
    new_perm[rotation[i]] = perm[rotation[(i + n) % 4]];
    new_orient[rotation[i]] = (orient[rotation[(i + n) % 4]] - orient_delta[(i + n) % 4] + orient_delta[i] + 3) % 3;
  }

  std::copy(new_perm.begin(), new_perm.end(), perm.begin());
  std::copy(new_orient.begin(), new_orient.end(), orient.begin());
};

/**
 * Turns front face 
 * @param &n if n=1, turn 90 degrees clockwise, if n=2, turn 180 degrees, if n=3, turn 90 degrees anti-clockwise,
 */
void Cube::turnFront(const int &n) {
  std::array<int, 7> new_perm, new_orient;
  std::copy(perm.begin(), perm.end(), new_perm.begin());
  std::copy(orient.begin(), orient.end(), new_orient.begin());

  int rotation[4] = {1, 4, 3, 0};
  int orient_delta[4] = {0, 2, 0, 2};
  for(int i = 0; i < 4; i++) {
    new_perm[rotation[i]] = perm[rotation[(i + n) % 4]];
    new_orient[rotation[i]] = (orient[rotation[(i + n) % 4]] - orient_delta[(i + n) % 4] + orient_delta[i] + 3) % 3;
  }


  std::copy(new_perm.begin(), new_perm.end(), perm.begin());
  std::copy(new_orient.begin(), new_orient.end(), orient.begin());
};

/**
 * Turns up face 
 * @param &n if n=1, turn 90 degrees clockwise, if n=2, turn 180 degrees, if n=3, turn 90 degrees anti-clockwise,
 */
void Cube::turnUp(const int &n) {
  std::array<int, 7> new_perm, new_orient;
  std::copy(perm.begin(), perm.end(), new_perm.begin());
  std::copy(orient.begin(), orient.end(), new_orient.begin());

  int rotation[4] = {3, 4, 5, 6};
  for(int i = 0; i < 4; i++) {
    new_perm[rotation[i]] = perm[rotation[(i + n) % 4]];
    new_orient[rotation[i]] = orient[rotation[(i + n) % 4]];
  }

  std::copy(new_perm.begin(), new_perm.end(), perm.begin());
  std::copy(new_orient.begin(), new_orient.end(), orient.begin());
};


/**
 * Shuffle the cube
 */
void Cube::shuffle() {
  std::random_device rnd;
  for(int i = 0; i < 6; i++) {
    int j = i + (rnd() % (7-i));
    int tmp = perm[i];
    perm[i] = perm[j];
    perm[j] = tmp;
  }
  int sum = 0;
  for(int i = 0; i < 6; i++) {
    orient[i] = rnd() % 3;
    sum += orient[i];
  }
  orient[6] = 3 - sum % 3;
}

/**
 * Returns the representation of colors of facelets
 * @return facelet, where facelet[i][j] represents the color of j-th facelet in i-th face.<br/>
 * 
 *                 *---------------*
 *                 |               |
 *                 | [5][0] [5][1] |
 *                 |               |
 *                 | [5][3] [5][2] |
 *                 |               |
 * *---------------*---------------*---------------*---------------*
 * |               |               |               |               |
 * | [1][0] [1][1] | [2][0] [2][1] | [3][0] [3][1] | [4][0] [4][1] |
 * |               |               |               |               |
 * | [1][3] [1][2] | [2][3] [2][2] | [3][3] [3][2] | [4][3] [4][2] |
 * |               |               |               |               |
 * *---------------*---------------*---------------*---------------*
 *                 |               |
 *                 | [0][0] [0][1] |
 *                 |               |
 *                 | [0][3] [0][2] |
 *                 |               |
 *                 *---------------*
 */
std::array<std::array<int, 4>, 6> Cube::toFacelet() {
  int mapper[7][3] = {
    {0, 1, 2},
    {0, 2, 3},
    {0, 3, 4},
    {5, 2, 1},
    {5, 3, 2},
    {5, 4, 3},
    {5, 1, 4},
  };
  
  std::array<std::array<int, 4>, 6> res;
  res[0][0] = mapper[perm[0]][orient[0]];
  res[0][1] = mapper[perm[1]][orient[1]];
  res[0][2] = mapper[perm[2]][orient[2]];
  res[0][3] = 0;

  res[1][0] = mapper[perm[6]][(orient[6]+1) % 3];
  res[1][1] = mapper[perm[3]][(orient[3]+2) % 3];
  res[1][2] = mapper[perm[0]][(orient[0]+1) % 3];
  res[1][3] = 1;

  res[2][0] = mapper[perm[3]][(orient[3]+1) % 3];
  res[2][1] = mapper[perm[4]][(orient[4]+2) % 3];
  res[2][2] = mapper[perm[1]][(orient[1]+1) % 3];
  res[2][3] = mapper[perm[0]][(orient[0]+2) % 3];

  res[3][0] = mapper[perm[4]][(orient[4]+1) % 3];
  res[3][1] = mapper[perm[5]][(orient[5]+2) % 3];
  res[3][2] = mapper[perm[2]][(orient[2]+1) % 3];
  res[3][3] = mapper[perm[1]][(orient[1]+2) % 3];

  res[4][0] = mapper[perm[5]][(orient[5]+1) % 3];
  res[4][1] = mapper[perm[6]][(orient[6]+2) % 3];
  res[4][2] = 4;
  res[4][3] = mapper[perm[2]][(orient[2]+2) % 3];

  res[5][0] = mapper[perm[6]][orient[6]];
  res[5][1] = mapper[perm[5]][orient[5]];
  res[5][2] = mapper[perm[4]][orient[4]];
  res[5][3] = mapper[perm[3]][orient[3]];

  return res;
}
/**
 * Prints the representation of colors of facelets, for debug.
 */
void Cube::print() {
  std::array<std::array<int, 4>, 6> facelet = toFacelet();
  for(int i = 0; i < 7; i++) std::cout << perm[i];
  std::cout << std::endl;
  for(int i = 0; i < 7; i++) std::cout << orient[i];
  std::cout << std::endl;
  std::cout << "   *--*   " << std::endl;
  std::cout << "   |" << facelet[5][0] << facelet[5][1] << "|" << std::endl;
  std::cout << "   |" << facelet[5][3] << facelet[5][2] << "|" << std::endl;
  std::cout << "*--*--*--*--*" << std::endl;
  std::cout << "|" 
    << facelet[1][0] << facelet[1][1] << "|"
    << facelet[2][0] << facelet[2][1] << "|"
    << facelet[3][0] << facelet[3][1] << "|"
    << facelet[4][0] << facelet[4][1] << "|"
    << std::endl;
  std::cout << "|" 
    << facelet[1][3] << facelet[1][2] << "|"
    << facelet[2][3] << facelet[2][2] << "|"
    << facelet[3][3] << facelet[3][2] << "|"
    << facelet[4][3] << facelet[4][2] << "|"
    << std::endl;
  std::cout << "*--*--*--*--*" << std::endl;
  std::cout << "   |" << facelet[0][0] << facelet[0][1] << "|" << std::endl;
  std::cout << "   |" << facelet[0][3] << facelet[0][2] << "|" << std::endl;
  std::cout << "   *--*   " << std::endl;
}