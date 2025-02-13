
#include <NTL/ZZ.h>
#include <iostream>
#include "Elliptic_Curve.h"

using namespace std;

int main()
{
   Elliptic_Curve<NTL::ZZ> EC(NTL::ZZ(0), NTL::ZZ(0), NTL::ZZ(0), 
		   NTL::ZZ(0), NTL::ZZ(0), NTL::ZZ(17));

  EcPoint<NTL::ZZ> P1(-2, 3, 1), P5(8, 23, 1);
  EcPoint<NTL::ZZ> Q = EC.Add(P1, P1);

  std::cout << Q << "\n";
  std::cout << (Q == P5) << "\n";
	return 0;
}
