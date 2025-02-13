//License
#include <any>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

/*
Homogeneous coordinates in projective space.
Usually, z = 1 except the infinity point [0,1,0].
*/
template <typename T>
class EcPoint
{
    public:
    EcPoint(const T& ox, const T& oy, const T& oz)
    :x(ox), y(oy), z(oz) {}

    EcPoint(const long& ox, const long& oy, const long& oz)
    {
        x = NTL::conv<T>(ox);
        y = NTL::conv<T>(oy);
        z = NTL::conv<T>(oz);
    }

    T x, y, z;
};

/*
Weierstrass Equation y^2 + a_1 x y + a_3 y = x^3 + a_2 x^2 + a_4 x + a_6
*/
template <typename T>
class Elliptic_Curve
{
public:
    Elliptic_Curve(const T &out_field, const T &out_a_1, const T &out_a_2, 
        const T &out_a_3, const T &out_a_4, const T &out_a_6)
    :field(out_field), a_1(out_a_1), a_2(out_a_2), a_3(out_a_3), 
    a_4(out_a_4), a_6(out_a_6)
    {}

    bool HasPoint(EcPoint<T> P)
    {
        if(P.z == 0) return P.x == 0;
        T x_power_two = NTL::power(P.x, 2);
        return NTL::power(P.y, 2) + a_1 * P.x * P.y + a_3 * P.y -
        x_power_two * P.x - a_2 * x_power_two - a_4 * P.x - a_6 == 0;
    }

    T field;
    T a_1, a_2, a_3, a_4, a_6;
};
