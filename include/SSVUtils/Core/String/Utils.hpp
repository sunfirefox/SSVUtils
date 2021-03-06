// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_CORE_STRING_UTILS
#define SSVU_CORE_STRING_UTILS

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "SSVUtils/Core/Global/Common.hpp"

namespace ssvu
{
	template<typename> struct Stringifier;

	/// @brief Stringifies a value in a stream.
	/// @details Uses Stringifier<T> internally.
	/// @tparam TFmt Use formatting? (set to false if the target stream isn't the console)
	/// @param mStream Reference to the target stream.
	/// @param mValue Const reference to the value. (original value won't be changed)
	template<bool TFmt, typename TStream, typename T> inline void stringify(TStream& mStream, const T& mValue)
	{
		Stringifier<T>::template impl<TFmt>(mStream, mValue);
	}

	namespace Internal
	{
		void resetFmt(std::ostream& mStream);
		inline std::ostringstream& getStringifyStream() noexcept { static std::ostringstream oss; return oss; }
		template<bool TFmt, bool TResetFmt = true, typename T> inline void callStringifyImpl(std::ostream& mStream, const T& mValue)
		{
			if(TResetFmt) resetFmt(mStream);
			stringify<TFmt>(mStream, mValue);
			if(TResetFmt) resetFmt(mStream);
		}
	}

	/// @brief Converts a value to a string.
	/// @details Uses Stringifier<T> internally, with disabled formatting options.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @return Returns a std::string representing the stringified value.
	template<typename T> inline std::string toStr(const T& mValue)
	{
		Internal::getStringifyStream().str("");
		Internal::callStringifyImpl<false, false>(Internal::getStringifyStream(), mValue);
		return Internal::getStringifyStream().str();
	}

	/// @brief Returns true if mChar is a digit. (Wraps std::isdigit)
	inline bool isDigit(char mChar) noexcept { return std::isdigit(mChar); }

	/// @brief Returns true if mChar is a space. (Wraps std::isspace)
	inline bool isSpace(char mChar) noexcept { return std::isspace(mChar); }

	/// @brief Returns true if mChar is a control. (Wraps std::iscntrl)
	inline bool isControl(char mChar) noexcept { return std::iscntrl(mChar); }

	/// @brief Returns true if mChar is printable. (Wraps std::isprint)
	inline bool isPrintable(char mChar) noexcept { return std::isprint(mChar); }

	/// @brief Returns true if mChar is graphical. (Wraps std::isgraph)
	inline bool isGraphical(char mChar) noexcept { return std::isgraph(mChar); }

	/// @brief Returns true if mChar is a punctuation. (Wraps std::ispunct)
	inline bool isPunctuation(char mChar) noexcept { return std::ispunct(mChar); }

	/// @brief Returns true if mChar is blank. (Wraps std::isblank)
	inline bool isBlank(char mChar) noexcept { return std::isblank(mChar); }

	/// @brief Returns true if mChar is alphanumeric. (Wraps std::isalnum)
	inline bool isAlphanumeric(char mChar) noexcept { return std::isalnum(mChar); }

	/// @brief Returns true if mChar is alphabetical. (Wraps std::isalpha)
	inline bool isAlphabetical(char mChar) noexcept { return std::isalpha(mChar); }

	/// @brief Returns true if mChar is uppercase. (Wraps std::isupper)
	inline bool isUppercase(char mChar) noexcept { return std::isupper(mChar); }

	/// @brief Returns true if mChar is lowercase. (Wraps std::islower)
	inline bool isLowercase(char mChar) noexcept { return std::islower(mChar); }

	/// @brief Returns true if mChar is an hexadecimal digit. (Wraps std::isxdigit)
	inline bool isDigitHexadecimal(char mChar) noexcept { return std::isxdigit(mChar); }

	/// @brief Returns mChar, converted to lowercase. (Wraps std::tolower)
	inline char toLowercase(char mChar) noexcept { return std::tolower(mChar); }

	/// @brief Returns mChar, converted to uppercase. (Wraps std::tolower)
	inline char toUppercase(char mChar) noexcept { return std::toupper(mChar); }

	/// @brief Replace the first occurrence of a string in a string with another string.
	/// @param mStr String to work with.
	/// @param mFrom String to replace.
	/// @param mTo Replacement string.
	inline void replace(std::string& mStr, const std::string& mFrom, const std::string& mTo)
	{
		std::size_t startPos{mStr.find(mFrom)};
		if(startPos == std::string::npos) return;
		mStr.replace(startPos, mFrom.size(), mTo);
	}

	/// @brief Replace all occurrences of a string in a string with another string.
	/// @param mStr String to work with.
	/// @param mFrom String to replace.
	/// @param mTo Replacement string.
	inline void replaceAll(std::string& mStr, const std::string& mFrom, const std::string& mTo)
	{
		std::size_t startPos{mStr.find(mFrom)};
		while(startPos != std::string::npos)
		{
			mStr.replace(startPos, mFrom.size(), mTo);
			startPos = mStr.find(mFrom);
		}
	}

	/// @brief Returns whether a string starts with a specific string.
	/// @param mStr String to work with.
	/// @param mStart String to test.
	/// @return Returns true if mStr starts with mStart.
	inline bool beginsWith(const std::string& mStr, const std::string& mStart) noexcept { return mStart.size() <= mStr.size() && mStr.compare(0, mStart.size(), mStart) == 0; }

	/// @brief Returns whether a string starts with a specific char.
	/// @param mStr String to work with.
	/// @param mChar Char to test.
	/// @return Returns true if mStr starts with mChar.
	inline bool beginsWith(const std::string& mStr, char mChar) noexcept { return mStr.size() > 0 && mStr.front() == mChar; }

	/// @brief Returns whether a string ends with a specific string.
	/// @param mStr String to work with.
	/// @param mEnding String to test.
	/// @return Returns true if mStr ends with mEnding.
	inline bool endsWith(const std::string& mStr, const std::string& mEnding) noexcept { return mStr.size() >= mEnding.size() && mStr.compare(mStr.size() - mEnding.size(), mEnding.size(), mEnding) == 0; }

	/// @brief Returns whether a string ends with a specific char.
	/// @param mStr String to work with.
	/// @param mChar Char to test.
	/// @return Returns true if mStr ends with mChar.
	inline bool endsWith(const std::string& mStr, char mChar) noexcept { return mStr.size() > 0 && mStr.back() == mChar; }

	/// @brief Converts a string to a lowercase string.
	/// @param mStr String to convert.
	/// @return Returns a std::string that is a copy of mStr, with all characters lowercase.
	inline std::string toLower(std::string mStr) { std::transform(std::begin(mStr), std::end(mStr), std::begin(mStr), ::tolower); return mStr; }

	/// @brief Converts a string to an uppercase string.
	/// @param mStr String to convert.
	/// @return Returns a std::string that is a copy of mStr, with all characters uppercase.
	inline std::string toUpper(std::string mStr) { std::transform(std::begin(mStr), std::end(mStr), std::begin(mStr), ::toupper); return mStr; }

	/// @brief Copies a string and replaces the first occurrence of a string in it with another string.
	/// @param mStr String to copy.
	/// @param mFrom String to replace.
	/// @param mTo Replacement string.
	/// @return Returns a std::string with mFrom replaced by mTo (first occurrence).
	inline std::string getReplaced(std::string mStr, const std::string& mFrom, const std::string& mTo) { replace(mStr, mFrom, mTo); return mStr; }

	/// @brief Copies a string and replaces the all occurences of a string in it with another string.
	/// @param mStr String to copy.
	/// @param mFrom String to replace.
	/// @param mTo Replacement string.
	/// @return Returns a std::string with mFrom replaced by mTo (all occurrences).
	inline std::string getReplacedAll(std::string mStr, const std::string& mFrom, const std::string& mTo) { replaceAll(mStr, mFrom, mTo); return mStr; }

	/// @brief Counts the number of occurences of a certain char in a std::string.
	/// @param mStr String to work with.
	/// @param mChar Character to look for.
	/// @return Returns an unsigned int which is the count of the character's occurrences.
	inline std::size_t getCharCount(const std::string& mStr, const char& mChar) { return std::count(std::begin(mStr), std::end(mStr), mChar); }

	/// @brief Counts the number of newlines in a std::string.
	/// @param mStr String to work with.
	/// @return Returns an unsigned int which is the count of newlines.
	inline std::size_t getNewLinesCount(const std::string& mStr) { return getCharCount(mStr, '\n'); }

	/// @brief Calculates the levenshtein distance between two strings.
	/// @details Levenshtein distance measures the "difference" between two strings.
	/// Useful for mispelling detection, for example.
	/// @param mA First string.
	/// @param mB Second string.
	/// @return Returns the levenshtein distance between two strings as an std::size_t.
	inline std::size_t getDistLevenshtein(const std::string& mA, const std::string& mB)
	{
		const auto& m(mA.size());
		const auto& n(mB.size());
		if(m == 0) return n;
		if(n == 0) return m;

		auto costs(Uptr<std::size_t[]>(new std::size_t[n + 1]));
		for(std::size_t k{0}; k <= n; ++k) costs[k] = k;

		std::size_t i{0};
		for(auto it1(std::begin(mA)); it1 != std::end(mA); ++it1, ++i)
		{
			costs[0] = i + 1;
			auto corner(i);

			std::size_t j{0};
			for(auto it2(std::begin(mB)); it2 != std::end(mB); ++it2, ++j)
			{
				auto upper(costs[j + 1]);
				if(*it1 == *it2) costs[j + 1] = corner;
				else
				{
					const auto& t(upper < corner ? upper : corner);
					costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
				}

				corner = upper;
			}
		}
		return costs[n];
	}

}

#endif
