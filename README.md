# lut

Class to implement LUTs (LookUp Tables) easily in C++

## Why

### Existing solutions

Surprisingly, there does not seem to be a library performing simple 1D LUTs with interpolation for C++. Or I didn't find
any. There are some options available for 3D LUTs (mainly tailored for image color adjustment) though.

## How it works

## Limitations

### For evenly spaced Xs (EvenLut)

When X's are provided in reverse order, no error are risen but results are consequently reversed. This is not a
limitation per se, but it may be unintuitive for most people. It is therefore recommended to avoid that situation by
making sure we provide both X's in proper order.

In a similar way, if both X's are equal, the result might be unexpected. For example, a division by 0 might occur down
the line. On many platforms, dividing by a 0.0 as float is not an issue because there is a way to represent +inf or NaN
with floats on these platforms. But with fixed points or with floats on some other platforms, that might not be the
case. Therefore, users of that library should make sure both X's are different values.

## Future

### Many dimensions LUTs

This class might evolve in a set of classes to support LUTs that have more dimensions than 1.

### Support for fixed point

Because many embedded platforms do not have hardware floating point support, it might be useful to support fixed point
LUTs. This would mostly be done by implementing a fixed point class (outside the goal of this repo) and make sure it
plays well with this library by adding unit tests for it.  