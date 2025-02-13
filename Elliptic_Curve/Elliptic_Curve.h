//License
#include <any>
#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

/*
Homogeneous coordinates in projective space.
Usually, z = 1 except the infinity point [0,1,0].
*/
template <typename T> class EcPoint;

template <typename T>
class EcPoint
{
    public:
    EcPoint():x(0), y(0), z(0) {}

    EcPoint(const T& ox, const T& oy, const T& oz)
    :x(ox), y(oy), z(oz) {}

    EcPoint(const long& ox, const long& oy, const long& oz)
    {
        x = NTL::conv<T>(ox);
        y = NTL::conv<T>(oy);
        z = NTL::conv<T>(oz);
    }

    friend std::ostream& operator<<(std::ostream& os, const EcPoint<T>& P)
    {
        os << "[" << P.x << ", " << P.y << ", " << P.z << "]";
        return os;
    }

    void Reduce()
    {
        if (z)
        {
            x /= z;
            y /= z;
            z = T(1);
        }
        else
            y = T(1);
    }

    bool operator==(const EcPoint &Q)
    { 
        return (x == Q.x && y == Q.y && z == Q.z); 
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

    bool HasPoint(const EcPoint<T> &P)
    {
        if(P.z == 0) return P.x == 0;
        T x_power_two = NTL::power(P.x, 2);
        return NTL::power(P.y, 2) + a_1 * P.x * P.y + a_3 * P.y -
        x_power_two * P.x - a_2 * x_power_two - a_4 * P.x - a_6 == 0;
    }

    void Negate(EcPoint<T> &P)
    {
        P.y = - P.y - a_1 * P.x - a_3;
    }

    EcPoint<T> Negate(const EcPoint<T> &P)
    {
        EcPoint<T> Q(P);
        Negate(Q);
        return Q;
    }

    void Add(EcPoint<T> &S, const EcPoint<T> &P, const EcPoint<T> &Q)
    {
        T lambda;
        T v;
        if(P.x == Q.x)
        {
            if(P.y + Q.y + a_1 * Q.x + a_3 == 0)
            {
                S = EcPoint<T>();
                return;
            }
            else
            {
                T Px_power_two = NTL::power(P.x, 2);
                T dominator = 2 * P.y + a_1 * P.x + a_3;
                lambda = (3 * Px_power_two + 2 * a_2 * P.x + a_4 - a_1 * P.y) / dominator;
                v = (- P.x * Px_power_two + a_4 * P.x + 2 * a_6 - a_3 * P.y) / dominator;
            }
        }
        else
        {
            T dominator = Q.x - P.x;
            lambda = (Q.y - P.y) / dominator;
            v = (P.y * Q.x - Q.y * P.x) / dominator;
        }
        S.z = 1;
        S.x =  NTL::power(lambda, 2) + a_1 * lambda - a_2 - P.x - Q.x;
        S.y = -(lambda + a_1) * S.x - v - a_3;
    }

    EcPoint<T> Add(const EcPoint<T> &P, const EcPoint<T> &Q)
    {
        EcPoint<T> S;
        Add(S, P ,Q);
        return S;
    }

    T field;
    T a_1, a_2, a_3, a_4, a_6;
};
