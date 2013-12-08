// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_STRING_UTILS
#define SSVU_STRING_UTILS

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "SSVUtils/Global/Common.hpp"
#include "SSVUtils/Utils/UtilsContainers.hpp"
#include "SSVUtils/Utils/UtilsIterator.hpp"

namespace ssvu
{
	template<typename> struct Stringifier;

	namespace Internal
	{
		void resetFmt(std::ostream& mStream);
		inline std::ostringstream& getStringifyStream() noexcept { static std::ostringstream oss; return oss; }
		template<bool TLogify, bool TResetFmt, typename T> inline void callStringifyImpl(const T& mValue, std::ostream& mStream)
		{
			if(TResetFmt) Internal::resetFmt(mStream);
			Stringifier<T>::template impl<TLogify>(mValue, mStream);
			if(TResetFmt) Internal::resetFmt(mStream);
		}
	}

	template<typename T> struct Stringifier
	{
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream) { mStream << mValue; }
	};

	/// @brief Converts a value to a std::string
	/// @details Uses std::ostringstream internally.
	/// @param mValue Const reference to the value. (original value won't be changed)
	/// @return Returns a std::string representing the converted value.
	template<typename T> inline std::string toStr(const T& mValue)
	{
		Internal::getStringifyStream().str("");
		Internal::callStringifyImpl<false, false>(mValue, Internal::getStringifyStream());
		return Internal::getStringifyStream().str();
	}
}

#include "SSVUtils/Utils/UtilsConsole.hpp"

#define SSVU_FLAVORED_STRINGIFIER(mType, mColor, mStyle, mPostfix) \
	template<> struct Stringifier<mType> \
	{ \
		template<bool TLogify> inline static void impl(const mType& mValue, std::ostream& mStream) \
		{ \
			if(TLogify) mStream << Console::setStyle(mStyle) << Console::setColorFG(mColor); \
			mStream << mValue; \
			if(TLogify) mStream << mPostfix; \
		} \
	} \

namespace ssvu
{
	namespace Internal
	{
		inline void resetFmt(std::ostream& mStream) { mStream << Console::resetFmt(); }
	}

	// TODO: docs
	SSVU_FLAVORED_STRINGIFIER(int,				Console::Color::LightBlue,		Console::Style::ReverseFGBG,	"");
	SSVU_FLAVORED_STRINGIFIER(long,				Console::Color::LightBlue,		Console::Style::ReverseFGBG,	"l");
	SSVU_FLAVORED_STRINGIFIER(unsigned int,		Console::Color::LightBlue,		Console::Style::ReverseFGBG,	"u");
	SSVU_FLAVORED_STRINGIFIER(unsigned long,	Console::Color::LightBlue,		Console::Style::ReverseFGBG,	"ul");
	SSVU_FLAVORED_STRINGIFIER(float,			Console::Color::LightRed,		Console::Style::ReverseFGBG,	"f");
	SSVU_FLAVORED_STRINGIFIER(double,			Console::Color::LightRed,		Console::Style::ReverseFGBG,	"d");
	SSVU_FLAVORED_STRINGIFIER(std::string,		Console::Color::LightYellow,	Console::Style::Underline,		"");

	template<typename T1, typename T2> struct Stringifier<std::pair<T1, T2>>
	{
		using T = std::pair<T1, T2>;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "{";

			Internal::callStringifyImpl<TLogify, true>(std::get<0>(mValue), mStream);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << ", ";

			Internal::callStringifyImpl<TLogify, true>(std::get<1>(mValue), mStream);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "}";
		}
	};

	namespace Internal
	{
		template<bool TLogify, std::size_t I = 0, typename... TArgs> inline EnableIf<I == sizeof...(TArgs), void> implTpl(const std::tuple<TArgs...>&, std::ostream&) { }
		template<bool TLogify, std::size_t I = 0, typename... TArgs> inline EnableIf<I < sizeof...(TArgs), void> implTpl(const std::tuple<TArgs...>& mTpl, std::ostream& mStream)
		{
			Internal::callStringifyImpl<TLogify, true>(std::get<I>(mTpl), mStream);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << ", ";

			implTpl<I + 1, TArgs...>(mTpl, mStream);
		}
	}

	template<typename... TArgs> struct Stringifier<std::tuple<TArgs...>>
	{
		using T = std::tuple<TArgs...>;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "{";

			Internal::implTpl<TLogify>(mValue, mStream);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "}";
		}
	};

	template<template<typename, typename...> class TContainer, typename TType, typename... TArgs> struct Stringifier<TContainer<TType, TArgs...>>
	{
		using T = TContainer<TType, TArgs...>;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "{";

			for(auto itr(std::begin(mValue)); itr < std::end(mValue) - 1; ++itr)
			{
				Internal::callStringifyImpl<TLogify, true>(*itr, mStream);

				if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
				mStream << ", ";
			}

			Internal::callStringifyImpl<TLogify, true>(*(std::end(mValue) - 1), mStream);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "}";
		}
	};

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
	inline std::size_t getLevenshteinDistance(const std::string& mA, const std::string& mB)
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

	/// @brief Trims all characters of a certain type from the string's left.
	/// @param mStr String to trim. (will be modified)
	/// @param mChar Character to trim.
	inline void trimStrL(std::string& mStr, char mChar = ' ') { trimL<std::string>(mStr, [mChar](char mC){ return mC == mChar; }); }

	/// @brief Trims all characters of a certain type from the string's right.
	/// @param mStr String to trim. (will be modified)
	/// @param mChar Character to trim.
	inline void trimStrR(std::string& mStr, char mChar = ' ') { trimR<std::string>(mStr, [mChar](char mC){ return mC == mChar; }); }

	/// @brief Trims all characters of a certain type both from the string's left and right.
	/// @param mStr String to trim. (will be modified)
	/// @param mChar Character to trim.
	inline void trimStrLR(std::string& mStr, char mChar = ' ') { trimLR<std::string>(mStr, [mChar](char mC){ return mC == mChar; }); }

	/// @brief Gets a copy of a string with characters of a certain type trimmed from the left.
	/// @param mStr String to trim. (will not be modified)
	/// @param mChar Character to trim.
	/// @return Returns a copy of the string, trimmed.
	inline std::string getTrimmedStrL(std::string mStr, char mChar = ' ') { trimStrL(mStr, mChar); return mStr; }

	/// @brief Gets a copy of a string with characters of a certain type trimmed from the right.
	/// @param mStr String to trim. (will not be modified)
	/// @param mChar Character to trim.
	/// @return Returns a copy of the string, trimmed.
	inline std::string getTrimmedStrR(std::string mStr, char mChar = ' ') { trimStrR(mStr, mChar); return mStr; }

	/// @brief Gets a copy of a string with characters of a certain type trimmed both from the left and right.
	/// @param mStr String to trim. (will not be modified)
	/// @param mChar Character to trim.
	/// @return Returns a copy of the string, trimmed.
	inline std::string getTrimmedStrLR(std::string mStr, char mChar = ' ') { trimStrLR(mStr, mChar); return mStr; }
}

#endif
