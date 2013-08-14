// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_UTILS_CONTAINERS
#define SSVU_UTILS_CONTAINERS

#include <vector>
#include <map>
#include <algorithm>

namespace ssvu
{
	/*!
	 *
	 * @brief Wrapper around std::find that takes a container instead of two iterators.
	 *
	 * @tparam T Type of the container.
	 * @tparam V Type of the value.
	 * @param mContainer Reference to the container.
	 * @param mValue Const reference to the value.
	 *
	 */
	template<typename T, typename V> inline typename T::const_iterator find(const T& mContainer, const V& mValue)
	{
		return std::find<typename T::const_iterator, V>(std::begin(mContainer), std::end(mContainer), mValue);
	}

	/*!
	 *
	 * @brief Gets the index of a item in the container, using find and subtracting the begin iterator.
	 *
	 * @tparam T Type of the container.
	 * @tparam V Type of the value.
	 * @param mContainer Reference to the container.
	 * @param mValue Const reference to the value.
	 *
	 */
	template<typename T, typename V> inline typename T::size_type indexOf(const T& mContainer, const V& mValue)
	{
		return find(mContainer, mValue) - std::begin(mContainer);
	}

	/*!
	 *
	 * @brief Finds a item that matches a specific predicate. Returns an interator (can be end iterator if the item is not found).
	 *
	 * @tparam T Type of the container.
	 * @tparam P Type of the predicate.
	 * @param mContainer Reference to the container.
	 * @param mPredicate Predicate used for checking. Can be std::function, a lambda, a functor, etc...
	 *
	 */
	template<typename T, typename P> inline typename T::const_iterator findIf(const T& mContainer, const P& mPredicate)
	{
		return std::find_if<typename T::const_iterator, P>(std::begin(mContainer), std::end(mContainer), mPredicate);
	}

	/*!
	 *
	 * @brief Checks if a container contains any item that matches a specific predicate.
	 *
	 * @tparam T Type of the container.
	 * @tparam P Type of the predicate.
	 * @param mContainer Reference to the container.
	 * @param mPredicate Predicate used for checking. Can be std::function, a lambda, a functor, etc...
	 *
	 */
	template<typename T, typename P> inline bool containsAnyIf(T& mContainer, const P& mPredicate)
	{
		return findIf(mContainer, mPredicate) != std::end(mContainer);
	}

	/*!
	 *
	 * @brief Removes a specific item from a container.
	 *
	 * @tparam T Type of the container.
	 * @tparam V Type of the value.
	 * @param mContainer Reference to the container.
	 * @param mValue Const reference to the value.
	 *
	 */
	template<typename T, typename V> inline void eraseRemove(T& mContainer, const V& mValue)
	{
		mContainer.erase(std::remove(std::begin(mContainer), std::end(mContainer), mValue), std::end(mContainer));
	}

	/*!
	 *
	 * @brief Checks if a specific item is in a container.
	 *
	 * @tparam T Type of the container.
	 * @tparam V Type of the value.
	 * @param mContainer Reference to the container.
	 * @param mValue Const reference to the value.
	 *
	 * @return Returns true if the container contains the specific item.
	 *
	 */
	template<typename T, typename V> inline bool contains(const T& mContainer, const V& mValue)
	{
		return find(mContainer, mValue) != std::end(mContainer);
	}

	/*!
	 *
	 * @brief Checks if any item from a container is in another container.
	 *
	 * This method calls "contains" on every item.
	 *
	 * @tparam T Type of the container to check.
	 * @tparam T2 Type of the container containing items to check.
	 * @param mContainer Reference to the container to check.
	 * @param mValues Const reference to the container containing the items to check.
	 *
	 * @return Returns true if the container contains any of the items.
	 *
	 */
	template<typename T, typename T2> inline bool containsAnyOf(T& mContainer, const T2& mValues)
	{
		for(const auto& v : mValues) if(contains(mContainer, v)) return true;
		return false;
	}

	/*!
	 *
	 * @brief Sorts a container. (no predicate)
	 *
	 * @tparam T Type of the container.
	 * @param mContainer Reference to the container.
	 *
	 */
	template<typename T> void inline sort(T& mContainer) { std::sort(std::begin(mContainer), std::end(mContainer)); }

	/*!
	 *
	 * @brief Sorts a container with a user-defined predicate.
	 *
	 * @tparam T Type of the container.
	 * @tparam P Type of the predicate.
	 * @param mContainer Reference to the container.
	 * @param mPredicate Predicate used for sorting. Can be std::function, a lambda, a functor, etc...
	 *
	 */
	template<typename T, typename P> inline void sort(T& mContainer, P mPredicate) { std::sort(std::begin(mContainer), std::end(mContainer), mPredicate); }

	/*!
	 *
	 * @brief Gets all the keys from a map container.
	 *
	 * @tparam TContainer Type of map container.
	 * @param mMap Const reference to the map container.
	 *
	 * @return Returns a std::vector containing all the keys.
	 *
	 */
	template<typename TContainer> auto getKeys(const TContainer& mMap) -> std::vector<typename TContainer::key_type>
	{
		std::vector<typename TContainer::key_type> result;
		for(const auto& p : mMap) result.push_back(p.first);
		return result;
	}

	/*!
	 *
	 * @brief Removes all items that satisfy a predicate from a container.
	 *
	 * @tparam T Type of the container.
	 * @tparam TPredicate Type of the predicate.
	 * @param mContainer Reference to the container.
	 * @param mPredicate Const reference to the predicate.
	 *
	 */
	template<typename T, typename TPredicate> inline void eraseRemoveIf(T& mContainer, const TPredicate& mPredicate)
	{
		mContainer.erase(std::remove_if(std::begin(mContainer), std::end(mContainer), mPredicate), std::end(mContainer));
	}
}

#endif
