#ifndef VEC3
#define VEC3

#include <cmath>
#include <ostream>

namespace raytracer
{
    class Vec3
    {
    private:
        float v[3] = {0, 0, 0};

    public:
        Vec3() {}

        Vec3(float x, float y, float z)
        {
            v[0] = x;
            v[1] = y;
            v[2] = z;
        }

        void Set(float x, float y, float z)
        {
            v[0] = x;
            v[1] = y;
            v[2] = z;
        }

        float x() const { return v[0]; }
        float y() const { return v[1]; }
        float z() const { return v[2]; }
    };

    #pragma region Math Operations

    inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
    }

    inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
    }

    inline Vec3 operator-(const Vec3 &v)
    {
        return Vec3(-v.x(), -v.y(), -v.z());
    }

    inline Vec3 operator*(const Vec3 &v, const float scale)
    {
        return Vec3(v.x() * scale, v.y() * scale, v.z() * scale);
    }

    inline Vec3 operator*(const float scale, const Vec3 &v)
    {
        return v * scale;
    }
    
    inline Vec3 operator/(const Vec3 &v, const float scale)
    {
        return Vec3(v.x() / scale, v.y() / scale, v.z() / scale);
    }

    inline std::ostream &operator<<(std::ostream &out, const Vec3 &v)
    {
        return out << "{" << v.x() << ", " << v.y() << ", " << v.z() << "}";
    }

    inline float SqrMagnitude(const Vec3 &v)
    {
        return v.x() * v.x() + v.y() * v.y() + v.z() * v.z();
    }

    inline float Magnitude(const Vec3 &v)
    {
        return sqrt(SqrMagnitude(v));
    }

    inline Vec3 UnitVector(const Vec3 &v)
    {
        return v / Magnitude(v);
    }

    inline float Dot(const Vec3 &u, const Vec3 &v)
    {
        return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
    }

    #pragma endregion

} // namespace raytracer

#endif