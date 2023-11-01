#ifndef Y_LUT_H
#define Y_LUT_H

#include <gsl/span>

template<typename TOut, typename TIn = TOut>
class Lut {
    using ValueType = TOut;
    using IndexType = TIn;

    gsl::span<const ValueType> table;
    ValueType lowerX;
    IndexType oneOverStep;

public:
    template<typename U>
    Lut(IndexType lowerX, IndexType higherX, const U& table)
        : table(table)
        , lowerX(lowerX)
        , oneOverStep(static_cast<IndexType>(table.size() - 1) / (higherX - lowerX)) {}

    ValueType operator[](IndexType x) const {
        auto betweenIndex = (x - lowerX) * oneOverStep;
        auto floorIndex = floor(betweenIndex);
        auto index = static_cast<gsl::index>(floorIndex);

        return (index < 0)                   ? table.front()
               : (index >= table.size() - 1) ? table.back()
                                             : std::lerp(table[index], table[index + 1], betweenIndex - floorIndex);
    }
};

#endif//Y_LUT_H
