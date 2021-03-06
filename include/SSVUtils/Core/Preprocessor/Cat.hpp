// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_CORE_PREPROCESSOR_CAT
#define SSVU_CORE_PREPROCESSOR_CAT

#include "SSVUtils/Core/Preprocessor/Utils.hpp"
#include "SSVUtils/Core/Preprocessor/ArgCount.hpp"
#include "SSVUtils/Core/Preprocessor/Bool.hpp"
#include "SSVUtils/Core/Preprocessor/ForEach.hpp"

namespace ssvu
{
	#define SSVPP_IMPL_CAT_0()				SSVPP_EMPTY()
	#define SSVPP_IMPL_CAT_1(m0)			SSVPP_EXPAND(m0)
	#define SSVPP_IMPL_CAT_2(m0, m1)		SSVPP_IMPL_CAT_1(SSVPP_TKNCAT_2(m0, m1))
	#define SSVPP_IMPL_CAT_3(m0, m1, ...)	SSVPP_IMPL_CAT_2(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_4(m0, m1, ...)	SSVPP_IMPL_CAT_3(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_5(m0, m1, ...)	SSVPP_IMPL_CAT_4(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_6(m0, m1, ...)	SSVPP_IMPL_CAT_5(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_7(m0, m1, ...)	SSVPP_IMPL_CAT_6(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_8(m0, m1, ...)	SSVPP_IMPL_CAT_7(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_9(m0, m1, ...)	SSVPP_IMPL_CAT_8(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_10(m0, m1, ...)	SSVPP_IMPL_CAT_9(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_11(m0, m1, ...)	SSVPP_IMPL_CAT_10(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_12(m0, m1, ...)	SSVPP_IMPL_CAT_11(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_13(m0, m1, ...)	SSVPP_IMPL_CAT_12(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_14(m0, m1, ...)	SSVPP_IMPL_CAT_13(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_15(m0, m1, ...)	SSVPP_IMPL_CAT_14(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_16(m0, m1, ...)	SSVPP_IMPL_CAT_15(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_17(m0, m1, ...)	SSVPP_IMPL_CAT_16(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_18(m0, m1, ...)	SSVPP_IMPL_CAT_17(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_19(m0, m1, ...)	SSVPP_IMPL_CAT_18(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_20(m0, m1, ...)	SSVPP_IMPL_CAT_19(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_21(m0, m1, ...)	SSVPP_IMPL_CAT_20(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_22(m0, m1, ...)	SSVPP_IMPL_CAT_21(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_23(m0, m1, ...)	SSVPP_IMPL_CAT_22(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_24(m0, m1, ...)	SSVPP_IMPL_CAT_23(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_25(m0, m1, ...)	SSVPP_IMPL_CAT_24(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_26(m0, m1, ...)	SSVPP_IMPL_CAT_25(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_27(m0, m1, ...)	SSVPP_IMPL_CAT_26(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_28(m0, m1, ...)	SSVPP_IMPL_CAT_27(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_29(m0, m1, ...)	SSVPP_IMPL_CAT_28(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_30(m0, m1, ...)	SSVPP_IMPL_CAT_29(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_31(m0, m1, ...)	SSVPP_IMPL_CAT_30(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_32(m0, m1, ...)	SSVPP_IMPL_CAT_31(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_33(m0, m1, ...)	SSVPP_IMPL_CAT_32(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_34(m0, m1, ...)	SSVPP_IMPL_CAT_33(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_35(m0, m1, ...)	SSVPP_IMPL_CAT_34(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_36(m0, m1, ...)	SSVPP_IMPL_CAT_35(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_37(m0, m1, ...)	SSVPP_IMPL_CAT_36(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_38(m0, m1, ...)	SSVPP_IMPL_CAT_37(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_39(m0, m1, ...)	SSVPP_IMPL_CAT_38(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)
	#define SSVPP_IMPL_CAT_40(m0, m1, ...)	SSVPP_IMPL_CAT_39(SSVPP_TKNCAT_2(m0, m1), __VA_ARGS__)

	#define SSVPP_IMPL_CAT(...)	SSVPP_TKNCAT_2(SSVPP_IMPL_CAT_, SSVPP_ARGCOUNT(__VA_ARGS__)) (__VA_ARGS__)
	#define SSVPP_CAT(...)		SSVPP_IMPL_CAT(__VA_ARGS__)
}

#endif
