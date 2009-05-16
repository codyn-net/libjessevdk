#include "math.hh"
#include <iostream>

using namespace math;
using namespace std;

int main()
{
	float4x4 a = float4x4::identity;
	float2x2 b = float2x2::ones;
	float3x3 c = float3x3::empty;
	
	b = float2x2::zeros;
	b = float2x2::identity;
 
 	c = float3x3::identity;

 	
 	float4x4 copy(a);
 	
 	a *= copy;

	cout << a.inverse() << endl;

 	//a *= float4x4::ones;
 
 	//cout << a << endl;
	return 0;
}
