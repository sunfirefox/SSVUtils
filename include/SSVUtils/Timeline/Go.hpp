// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_TIMELINE_GO
#define SSVU_TIMELINE_GO

#include "SSVUtils/Timeline/Command.hpp"
#include "SSVUtils/Timeline/Timeline.hpp"

namespace ssvu
{
	namespace Internal
	{
		template<typename T> class GoImpl final : public Command
		{
			protected:
				T target;
				int times, currentTimes;

				inline void update(FT) override
				{
					if(currentTimes == 0)		{ timeline.next(); }
					else if(currentTimes > 0)	{ --currentTimes; timeline.jumpTo(target); }
					else						{ timeline.jumpTo(target); }
				}
				inline void reset() override { currentTimes = times; }

			public:
				GoImpl(Timeline& mTimeline, T mTarget, int mTimes = -1) noexcept : Command{mTimeline}, target(mTarget), times{mTimes}, currentTimes{mTimes} { }
		};
	}

	using Go = Internal::GoImpl<int>;
	using Goto = Internal::GoImpl<Command&>;
}

#endif
