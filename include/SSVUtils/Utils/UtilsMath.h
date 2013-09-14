// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_UTILS_MATH
#define SSVU_UTILS_MATH

#include <cassert>
#include <array>
#include <random>

namespace ssvu
{
	static std::minstd_rand rndEngine;
	template<typename T> using RndDistributionI = std::uniform_int_distribution<T>;
	template<typename T> using RndDistributionR = std::uniform_real_distribution<T>;

	constexpr float pi{3.14159265f};
	constexpr float degRadRatio{pi / 180.f};

	/// @brief Gets a random integer value between [mMin and mMax).
	/// @tparam T Type of integer value. (can also be unsigned int, for example)
	/// @param mMin Lower inclusive bound.
	/// @param mMax Upper exclusive bound.
	/// @return Returns a random integer value, between [mMin and mMax).
	template<typename T = int> inline T getRnd(T mMin, T mMax) { assert(mMin < mMax); return RndDistributionI<T>{mMin, mMax - 1}(rndEngine); }

	/// @brief Gets a random real value between [mMin and mMax).
	/// @tparam T Type of integer value. (can also be double, for example)
	/// @param mMin Lower inclusive bound.
	/// @param mMax Upper exclusive bound.
	/// @return Returns a random real value, between [mMin and mMax).
	template<typename T = float> inline T getRndR(T mMin, T mMax) { assert(mMin < mMax); return RndDistributionR<T>{mMin, mMax - 1}(rndEngine); }

	/// @brief Gets the sign of a numeric value. (unsigned version)
	/// @tparam T Type of value.
	/// @param mValue Value to use.
	/// @return Returns 1 if the value is >0, -1 if the value is < 0, 0 if the value == 0.
	template<typename T> constexpr inline int getSign(T mValue, typename std::enable_if<!std::is_signed<T>::value>::type* = nullptr) noexcept { return 0 < mValue; }

	/// @brief Gets the sign of a numeric value. (signed version)
	/// @tparam T Type of value.
	/// @param mValue Value to use.
	/// @return Returns 1 if the value is >0, -1 if the value is < 0, 0 if the value == 0.
	template<typename T> constexpr inline int getSign(T mValue, typename std::enable_if<std::is_signed<T>::value>::type* = nullptr) noexcept { return (0 < mValue) - (mValue < 0); }

	/// @brief Clamps a numeric value. (lower-bound only)
	/// @tparam T Type of value.
	/// @param mValue Reference to the value. (will be modified)
	/// @param mMin Lower bound.
	template<typename T> inline void clampMin(T& mValue, const T& mMin) noexcept { if(mValue < mMin) mValue = mMin; }

	/// @brief Clamps a numeric value. (upper-bound only)
	/// @tparam T Type of value.
	/// @param mValue Reference to the value. (will be modified)
	/// @param mMax Upper bound.
	template<typename T> inline void clampMax(T& mValue, const T& mMax) noexcept { if(mValue > mMax) mValue = mMax; }

	/// @brief Clamps a numeric value.
	/// @tparam T Type of value.
	/// @param mValue Reference to the value. (will be modified)
	/// @param mMin Lower bound.
	/// @param mMax Upper bound.
	template<typename T> inline void clamp(T& mValue, const T& mMin, const T& mMax) noexcept { assert(mMin <= mMax); if(mValue < mMin) mValue = mMin; else if(mValue > mMax) mValue = mMax; }

	/// @brief Gets a clamped numeric value. (lower-bound only)
	/// @tparam T Type of value.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @param mMin Lower bound.
	/// @return Returns mMin if mValue < mMin, mValue otherwise.
	template<typename T> constexpr inline T getClampedMin(const T& mValue, const T& mMin) noexcept { return mValue < mMin ? mMin : mValue; }

	/// @brief Gets a clamped numeric value. (upper-bound only)
	/// @tparam T Type of value.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @param mMax Upper bound.
	/// @return Returns mMax if mValue > mMax, mValue otherwise.
	template<typename T> constexpr inline T getClampedMax(const T& mValue, const T& mMax) noexcept { return mValue > mMax ? mMax : mValue; }

	/// @brief Gets a clamped numeric value.
	/// @tparam T Type of value.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @param mMin Lower bound.
	/// @param mMax Upper bound.
	/// @return Returns mMax if mValue > mMax, mMin if mValue < mMin, mValue if mMin < mValue < mMax.
	template<typename T> constexpr inline T getClamped(const T& mValue, const T& mMin, const T& mMax) noexcept { /*assert(mMin <= mMax);*/ return mValue < mMin ? mMin : (mValue > mMax ? mMax : mValue); }

	/// @brief Converts degrees to radians.
	/// @tparam T Type of value.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @return Returns the value in radians.
	template<typename T> constexpr inline T toRadians(const T& mValue) noexcept { return mValue * degRadRatio; }

	/// @brief Converts radians to degrees.
	/// @tparam T Type of value.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @return Returns the value in degrees.
	template<typename T> constexpr inline T toDegrees(const T& mValue) noexcept { return mValue / degRadRatio; }

	/// @brief Restricts a radian value between 0 and 6.28f.
	/// @tparam T Type of value.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @return Returns the restricted value in radians.
	template<typename T> inline T wrapRadians(T mValue) noexcept { mValue = fmod(mValue, 6.28f); if(mValue < 0) mValue += 6.28f; return mValue; }

	/// @brief Restricts a degree value between 0 and 360.f.
	/// @tparam T Type of value.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @return Returns the restricted value in degrees.
	template<typename T> inline T wrapDegrees(T mValue) noexcept { mValue = fmod(mValue, 360.f); if(mValue < 0) mValue += 360.f; return mValue; }

	/// @brief Gets a rotated angle in radians.
	/// @details Example use: a character slowly aiming towards the mouse position.
	/// @tparam T Type of value.
	/// @tparam J Type of rotation value.
	/// @param mStart Angle to start from.
	/// @param mEnd Target angle.
	/// @param mSpeed Rotation speed.
	/// @return Returns the rotated angle in radians.
	template<typename T, typename J> inline T getRotatedRadians(const T& mStart, const T& mEnd, const J& mSpeed) noexcept
	{
		T start(wrapRadians(mStart)), end(wrapRadians(mEnd));
		if(std::abs(start - end) < mSpeed) return end;
		return wrapRadians(start + (std::sin(end - start)) * mSpeed);
	}

	/// @brief Gets a rotated angle in degrees.
	/// @details Example use: a character slowly aiming towards the mouse position.
	/// @tparam T Type of value.
	/// @tparam J Type of rotation value.
	/// @param mStart Angle to start from.
	/// @param mEnd Target angle.
	/// @param mSpeed Rotation speed.
	/// @return Returns the rotated angle in degrees.
	template<typename T, typename J> inline T getRotatedDegrees(const T& mStart, const T& mEnd, const J& mSpeed) noexcept
	{
		T start(wrapDegrees(mStart)), end(wrapDegrees(mEnd));
		if(std::abs(start - end) < mSpeed) return end;
		return wrapDegrees(start + (std::sin(toDegrees(end - start))) * mSpeed);
	}

	/// @brief Gets a 1D index from a 2D index.
	/// @details Useful when dealing with "implicit 2D" arrays, that are stored as 1D arrays.
	/// Internally, it calculates and returns `mY * mColumns + mX`.
	/// @tparam T Type of index value.
	/// @param mX X index.
	/// @param mY Y index.
	/// @param mColumns Number of columns of the 2D array.
	/// @return Returns a 1D index for an "implicit 2D" array with `mColumns` columns.
	template<typename T> constexpr inline T get1DIndexFrom2D(const T& mX, const T& mY, const T& mColumns) noexcept { return mY * mColumns + mX; }

	/// @brief Gets a 2D index from an 1D index.
	///
	/// Useful when dealing with "implicit 2D" arrays, that are stored as 1D arrays.
	///
	/// @tparam T Type of index value.
	/// @param mIdx 1D index.
	/// @param mColumns Number of columns of the 2D array.
	/// @return Returns a 2D index (under the form of an std::array<T, 2>) for a 2D array with `mColumns` columns.
	template<typename T> inline std::array<T, 2> get2DIndexFrom1D(const T& mIdx, const T& mColumns) noexcept { T y{mIdx / mColumns}; return std::array<T, 2>{{mIdx - y * mColumns, y}}; }

	/// @brief Gets sign-indepedent modulo calculation.
	/// @code
	/// assert(getSIMod(-2, 12) == 10);
	/// @endcode
	/// @tparam T Type of value.
	/// @param mA Left side of operation.
	/// @param mB Right side of operation.
	/// @return Returns the mathematically correct mA % mB.
	template<typename T> inline T getSIMod(const T& mA, const T& mB)
	{
		if(mB < 0) return getSIMod(-mA, -mB);
		T result{mA % mB};
		if(result < 0) result += mB;
		return result;
	}

	/// @brief Calculates euclidean distance (squared) between two points.
	/// @tparam T Type of value.
	/// @param mX1 First point X.
	/// @param mY1 First point Y.
	/// @param mX2 Second point X.
	/// @param mY2 Second point Y.
	/// @return Returns the euclidean distance (squared).
	template<typename T> inline T getDistanceEuclideanSquared(T mX1, T mY1, T mX2, T mY2) noexcept { return (mX1 - mX2) * (mX1 - mX2) + (mY1 - mY2) * (mY1 - mY2); }

	/// @brief Calculates euclidean distance between two points.
	/// @tparam T Type of value.
	/// @param mX1 First point X.
	/// @param mY1 First point Y.
	/// @param mX2 Second point X.
	/// @param mY2 Second point Y.
	/// @return Returns the euclidean distance.
	template<typename T> inline T getDistanceEuclidean(T mX1, T mY1, T mX2, T mY2) noexcept { return std::sqrt(getDistanceEuclideanSquared(mX1, mY1, mX2, mY2)); }

	/// @brief Calculates degrees needed to turn towards a point.
	/// @tparam T Type of value.
	/// @param mX1 First point X.
	/// @param mY1 First point Y.
	/// @param mX2 Second point X.
	/// @param mY2 Second point Y.
	/// @return Returns the needed degrees.
	template<typename T> inline T getRadiansTowards(T mX1, T mY1, T mX2, T mY2) noexcept { return std::atan2(mY2 - mY1, mX2 - mX1); }

	/// @brief Calculates radians needed to turn towards a point.
	/// @tparam T Type of value.
	/// @param mX1 First point X.
	/// @param mY1 First point Y.
	/// @param mX2 Second point X.
	/// @param mY2 Second point Y.
	/// @return Returns the needed radians.
	template<typename T> inline T getDegreesTowards(T mX1, T mY1, T mX2, T mY2) noexcept { return toDegrees(getDegreesTowards(mX1, mY1, mX2, mY2)); }
}

#endif

