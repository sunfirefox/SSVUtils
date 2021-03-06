// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_TEMPLATESYSTEM_DICTIONARY
#define SSVU_TEMPLATESYSTEM_DICTIONARY

#include <string>
#include <vector>
#include <map>
#include "SSVUtils/TemplateSystem/Internal/Symbols.hpp"
#include "SSVUtils/Core/Core.hpp"

namespace ssvu
{
	namespace TemplateSystem
	{
		/// @brief Dictionary used for string-template replacements.
		/// @details Inspired by CTemplate. It's used to generate data from string templates.
		class Dictionary
		{
			private:
				std::map<std::string, std::string> replacements; /*!< Simple key -> string replacements. */
				std::map<std::string, std::vector<Dictionary>> sectionDictionaries; /*!< Key -> subdictionary section replacements. */

			public:
				/// @brief Default constructor.
				/// @details Initializes an empty Dictionary.
				Dictionary() = default;

				/// @brief std::initializer_list constructor.
				/// @details Initializes a dictionary filled with "key -> string" data.
				/// @code
				/// using namespace ssvu::TemplateSystem;
				/// Dictionary dict{{"key1", "value1"}, {"key2", "value2"}};
				/// string toExpand{".{{key1}}.{{key2}}."};
				/// SSVU_ASSERT(dict.getExpanded(toExpand) == ".value1.value2.");
				/// @endcode
				Dictionary(const std::initializer_list<std::pair<std::string, std::string>>& mPairs) { for(const auto& p : mPairs) replacements.insert(p); }

				/// @brief Expands the dictionary.
				/// @details Expands the dictionary, along with subdictionary sections, to a string.
				/// Takes a string parameter which is the template (not a path to the template file).
				/// Consider using ssvufs::getFileContents(...) to pass a template file.
				/// @code
				/// using namespace ssvu::TemplateSystem;
				/// Dictionary dict{{"key1", "value1"}, {"key2", "value2"}};
				/// string toExpand{".{{key1}}.{{key2}}."};
				/// SSVU_ASSERT(dict.getExpanded(toExpand) == ".value1.value2.");
				/// @endcode
				/// @param mStr Template to use (not a path!).
				/// @return Returns a string containing the expanded dictionary template.
				std::string getExpanded(std::string mStr) const
				{
					using namespace Internal;

					for(const auto& p : sectionDictionaries)
					{
						const std::string sectionStart{getSectionStart(p.first)}, sectionEnd{getSectionEnd(p.first)};
						const auto outerSectionStartIndex(mStr.find(sectionStart));
						const auto innerSectionEndIndex(mStr.find(sectionEnd));
						const auto innerSectionStartIndex(outerSectionStartIndex + sectionStart.size());
						const auto outerSectionEndIndex(innerSectionEndIndex + sectionEnd.size());

						const std::string innerSection{mStr.substr(innerSectionStartIndex, innerSectionEndIndex - innerSectionStartIndex)};
						std::string innerSectionResult;

						for(auto d : p.second) innerSectionResult += d.getExpanded(innerSection);

						mStr.replace(outerSectionStartIndex, outerSectionEndIndex - outerSectionStartIndex, innerSectionResult);
					}

					for(const auto& p : replacements) replaceAll(mStr, getKey(p.first), p.second);

					// TODO: cleanup unexpanded sections/replacements? (use regex!)
					// TODO: newline stripping options?

					return mStr;
				}

				/// @brief Sets a "key -> string" replacement.
				/// @details Works similarly to std::map::operator[].
				/// @code
				/// using namespace ssvu::TemplateSystem;
				/// Dictionary dict;
				/// dict["key1"] = "value1";
				/// dict["key2"] = "value2";
				/// string toExpand{".{{key1}}.{{key2}}."};
				/// SSVU_ASSERT(dict.getExpanded(toExpand) == ".value1.value2.");
				/// @endcode
				/// @param mStr Key of the "key -> string" replacement.
				/// @return Returns a reference to the string used in the "key -> string" replacement. Set it to the value you desire.
				inline std::string& operator[](const std::string& mKey) { return replacements[mKey]; }

				/// @brief Adds a "key -> subdictionary" replacement
				/// @code
				/// using namespace ssvu::TemplateSystem;
				/// Dictionary dict;
				/// Dictionary subdict1{{"key", "value1"}};
				/// Dictionary subdict2{{"key", "value2"}};
				///
				/// dict += {"section", subdict1};
				/// dict += {"section", subdict2};
				///
				/// string toExpand{"{{#section}}.{{key}}.{{/section}}"};
				/// SSVU_ASSERT(dict.getExpanded(toExpand) == ".value1..value2.");
				/// @endcode
				/// @param mPair Pair containing the key of the section name and the subdictionary to use in the replacement.
				inline void operator+=(const std::pair<std::string, Dictionary>& mPair) { sectionDictionaries[mPair.first].emplace_back(mPair.second); }
		};
	}
}

#endif
