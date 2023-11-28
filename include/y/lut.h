#ifndef Y_LUT_H
#define Y_LUT_H

#include <cassert>
#include <gsl/span>

namespace y {
template<typename TY, typename TX = TY>
class Lut {
public:
    using YType = TY;
    using XType = TX;

protected:
    // static auto lerp(auto a, auto b, auto t) { return a + t * (b - a); }
    static float lerp(float a, float b, float t) { return a + t * (b - a); }
    static double lerp(double a, double b, double t) { return a + t * (b - a); }
    static double lerp(double a, double b, float t) { return a + t * (b - a); }
    static double lerp(float a, float b, double t) { return a + t * (b - a); }
};

/**
 * LookUp Table when X values that are evenly spaced between X_1 and X_n for all n Y values
 */
template<typename TY, typename TX = TY>
class EvenLut : public Lut<TY, TX> {
public:
    using YType = typename Lut<TY, TX>::YType;
    using XType = typename Lut<TY, TX>::XType;

    template<typename U>
    EvenLut(XType x1, XType xn, const U& ys)
        : ys(ys)
        , x1(x1)
        , oneOverXStep(static_cast<XType>(ys.size() - 1) / (xn - x1)) {}

    YType operator[](XType x) const {
        auto betweenIndex = (x - x1) * oneOverXStep;
        auto floorIndex = floor(betweenIndex);
        auto index = static_cast<gsl::index>(floorIndex);

        return (index < 0)                ? ys.front()
               : (index >= ys.size() - 1) ? ys.back()
                                          : EvenLut::lerp(ys[index], ys[index + 1], betweenIndex - floorIndex);
    }

private:
    gsl::span<const YType> ys;
    XType x1;
    XType oneOverXStep;
};

/**
 * LookUp Table when X values that are not evenly spaced for all n Y values
 *
 * Steps are supported (two consecutive identical Xs); the value for the last one is returned when looking up exactly that value.
 */
template<typename TY, typename TX = TY>
class UnevenLut : public Lut<TY, TX> {
public:
    using YType = typename Lut<TY, TX>::YType;
    using XType = typename Lut<TY, TX>::XType;

    struct XYType {
        XType x;
        YType y;
    };
    using XYContainer = gsl::span<const XYType>;
    explicit UnevenLut(const XYContainer& xys)
        : xys(xys) {
        auto previousX = -std::numeric_limits<XType>::infinity();
        for (auto xy : xys) {
            assert(previousX <= xy.x);
            previousX = xy.x;
        }
    }

    YType operator[](XType x) const {
        if (xys.back().x <= x) { return xys.back().y; }
        auto it = std::lower_bound(xys.rbegin(), xys.rend(), x, [](auto& xy, auto& v) { return v < xy.x; });
        if (it == xys.rend()) { return xys.front().y; }

        const auto& lower = *it;
        const auto& upper = *--it;
        return UnevenLut::lerp(lower.y, upper.y, (x - lower.x) / (upper.x - lower.x));
    }

private:
    XYContainer xys;
};

}// namespace y

#endif//Y_LUT_H
