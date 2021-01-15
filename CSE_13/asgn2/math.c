#define EPSILON 0.000000001
#include <assert.h>
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//maps x to a number in [-pi,pi] such that it represent the same angle
double restrict_to_circle(double x) {
  //translating x so as to take an offset modulus
  x += M_PI;

  //taking x modulus 2pi
  x = x - (int)(x / (2 * M_PI)) * 2 * M_PI;
  if (x < 0) {
    x += 2 * M_PI;
  }

  //undoing first translation
  x -= M_PI;

  //ensuring that x is in [-pi,pi]
  assert(x >= -M_PI && x <= M_PI);

  return x;
}

double pade_sin(double x) {
  x = restrict_to_circle(x);

  double x_sqr = x * x;

  double numerator = (((-479249 * x_sqr + 52785432) * x_sqr - 1640635920) * x_sqr + 11511339840)* x;
  double denominator = ((18361 * x_sqr + 3177720) * x_sqr + 277920720) * x_sqr + 11511339840;

  return numerator / denominator;
}

double pade_cos(double x) {
  x = restrict_to_circle(x);

  double x_sqr = x * x;

  double numerator = ((-14615 * x_sqr + 1075032) * x_sqr - 18471600) * x_sqr + 39251520;
  double denominator = ((127 * x_sqr + 16632) * x_sqr + 1154160) * x_sqr + 39251520;

  return numerator / denominator;
}

//The following implementation uses symmetries of the circle
//so that any use of a Pade approximation is at most PI/4 away from 0.
//This chooses between the sine Pade and the cosine Pade
//
//The following use of 'union' refers to the set theory constructor,
//not the 'union' found in C
//
//Region 0 is the union of {[-PI/4        ,-PI/4 +  PI/2) + k2PI, k is an integer}
//Region 1 is the union of {[-PI/4 +  PI/2,-PI/4 + 2PI/2) + k2PI, k is an integer}
//Region 2 is the union of {[-PI/4 + 2PI/2,-PI/4 + 3PI/2) + k2PI, k is an integer}
//Region 3 is the union of {[-PI/4 + 3PI/2,-PI/4 + 4PI/2) + k2PI, k is an integer}
//
//visual:
//2|3|0|1|2|3|0|1|2|3|0|1|2|3|0|1|
//      -       -       -       -
//     / \     / \     / \     / \
//\   /   \   /   \   /   \   /
// \ /     \ /     \ /     \ /
//  -       -       -       -
//when in Region 0, calculate Sine   (x)
//when in Region 1, calculate Cosine (x - PI/2)
//when in Region 2, calculate -Sin   (x - 2PI/2)
//when in Region 3, calculate -Cosine(x - 3PI/2)
double Sin(double x) {
  int8_t region = (int)floor((x + M_PI / 4) / (M_PI / 2)) % 4;
  if (region < 0) {
    region += 4;
  }

  x -= region * M_PI / 2;
  if (region == 0 || region == 2) {
    x = pade_sin(x);
  } else {
    x = pade_cos(x);
  }

  if (region > 1) {
    x = -x;
  }
  return x;
}

//Cosine is simply a translation of sine
double Cos(double x) {
  return Sin(M_PI / 2 - x);
}

double Tan(double x) {
  //domain of tan is half circle
  x = restrict_to_circle(x * 2) / 2;

  double x_sqr = x * x;
  //Pade approximation for Tangent
  double numerator = ((((x_sqr - 990) * x_sqr + 135135) * x_sqr - 4729725) * x_sqr + 34459425) * x;
  double denominator = ((((x_sqr - 308) * x_sqr + 21021) * x_sqr - 360360) * x_sqr + 765765) * 45;

  return numerator / denominator;
}

double Exp(double x) {
  //Exp(+-708) throws an error
  //Exp(x):x<-24 produces inaccurate negative results
  if (x > 707 || x < -24) {
    return 0;
  }

  double exp_x = 1;
  uint32_t term_number = 1;
  double term_value = 1;
  while (term_value > EPSILON || term_value < -EPSILON) {
    term_value *= x;
    term_value /= term_number;
    exp_x += term_value;
    term_number++;
  }
  return exp_x;
}

void test_sin() {
  printf("\n\n");
  printf("x         Sin          Library      Difference\n");
  printf("-         ---          -------      ----------\n");
  for (double x = -2 * M_PI; x < 2 * M_PI; x += M_PI / 16) {
    double Sinx = Sin(x);
    double sinx = sin(x);
    printf("%-10.4lf%-13.8lf%-13.8lf%-13.20lf\n", x, Sinx, sinx, Sinx - sinx);
  }
}

void test_cos() {
  printf("\n\n");
  printf("x         Cos          Library      Difference\n");
  printf("-         ---          -------      ----------\n");
  for (double x = -2 * M_PI; x < 2 * M_PI; x += M_PI / 16) {
    double Cosx = Cos(x);
    double cosx = cos(x);
    printf("%-10.4lf%-13.8lf%-13.8lf%-13.20lf\n", x, Cosx, cosx, Cosx - cosx);
  }
}

void test_tan() {
  printf("\n\n");
  printf("x         Tan             Library         Difference\n");
  printf("-         ---             -------         ----------\n");
  for (double x = -M_PI / 2 + 0.001; x < M_PI / 2 - 0.001; x += M_PI / 16) {
    double Tanx = Tan(x);
    double tanx = tan(x);
    printf("%-10.4lf%-16.8lf%-16.8lf%-13.20lf\n", x, Tanx, tanx, Tanx - tanx);
  }
}

void test_exp() {
  printf("\n\n");
  printf("x         Exp               Library           Difference\n");
  printf("-         ---               -------           ----------\n");
  for (double x = 0; x < 10; x += 0.1) {
    double Expx = Exp(x);
    double expx = exp(x);
    printf("%-10.4lf%-18.8lf%-18.8lf%-13.20lf\n", x, Expx, expx, Expx - expx);
  }
}

int main(int argc, char **argv) {
  int8_t c = 0;

  while ((c = getopt(argc, argv, "sctea")) != -1) {
    switch (c) {
    case 's':
      test_sin();
      return 0;
      break;

    case 'c':
      test_cos();
      return 0;
      break;

    case 't':
      test_tan();
      return 0;
      break;

    case 'e':
      test_exp();
      return 0;
      break;

    case 'a':
      test_sin();
      test_cos();
      test_tan();
      test_exp();
      return 0;
      break;
    }
  }
  return 0;
}
