// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_PREPROCESSOR_UTILS
#define SSVU_PREPROCESSOR_UTILS

namespace ssvu
{
	#define SSVU_PP_EMPTY()
	#define SSVU_PP_COMMA() ,

	#define SSVU_PP_STRINGIFY_IMPL(mX)	#mX
	#define SSVU_PP_STRINGIFY(mX)		SSVU_PP_STRINGIFY_IMPL(mX)

	#define SSVU_PP_DEFER(mX) mX SSVU_PP_EMPTY()

	#define SSVU_PP_EXPAND(mX) mX

	#define SSVU_PP_IMPL_TOKENPASTE_2(m0, m1)				m0 ## m1
	#define SSVU_PP_IMPL_TOKENPASTE_3(m0, m1, m2)			m0 ## m1 ## m2
	#define SSVU_PP_IMPL_TOKENPASTE_4(m0, m1, m2, m3)		m0 ## m1 ## m2 ## m3
	#define SSVU_PP_IMPL_TOKENPASTE_5(m0, m1, m2, m3, m4)	m0 ## m1 ## m2 ## m3 ## m4

	#define SSVU_PP_TOKENPASTE_2(m0, m1)					SSVU_PP_IMPL_TOKENPASTE_2(m0, m1)
	#define SSVU_PP_TOKENPASTE_3(m0, m1, m2)				SSVU_PP_IMPL_TOKENPASTE_3(m0, m1, m2)
	#define SSVU_PP_TOKENPASTE_4(m0, m1, m2, m3)			SSVU_PP_IMPL_TOKENPASTE_4(m0, m1, m2, m3)
	#define SSVU_PP_TOKENPASTE_5(m0, m1, m2, m3, m4)		SSVU_PP_IMPL_TOKENPASTE_5(m0, m1, m2, m3, m4)

	//#define SSVU_PP_IMPL_WHILE(mPredicate, mOp

	/*
		#define SSVU_PP_IMPL_WHILE_IMPL(pred, op, ...) \
			SSVU_PP_IF(pred(__VA_ARGS__)) \
			( \
				SSVU_PP_DEFER(SSVU_PP_IMPL_WHILE_IMPL) () \
				( \
					pred, op, op(__VA_ARGS__) \
				), \
				__VA_ARGS__ \
			)

		#define SSVU_PP_WHILE(...) SSVU_PP_IMPL_WHILE_IMPL(__VA_ARGS__)
	*/
}

#endif
