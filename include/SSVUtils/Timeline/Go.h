// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVU_TIMELINE_GO
#define SSVU_TIMELINE_GO

#include <cassert>
#include "SSVUtils/Timeline/Command.h"
#include "SSVUtils/Timeline/Timeline.h"

namespace ssvu
{
	namespace Internal
	{
		template<typename T> class GoImpl : public Command
		{
			protected:
				T target;
				int times, currentTimes;

				inline void update(float) override
				{
					if(currentTimes == 0)		{ timeline.next(); }
					else if(currentTimes > 0)	{ --currentTimes; timeline.jumpTo(target); }
					else						{ timeline.jumpTo(target); }
				}
				inline void reset() override { currentTimes = times; }

			public:
				GoImpl(Timeline& mTimeline, T mTarget, int mTimes = -1) : Command{mTimeline}, target(mTarget), times{mTimes}, currentTimes{mTimes} { }
		};
	}

	using Go = Internal::GoImpl<int>;
	using Goto = Internal::GoImpl<Command&>;
}

#endif
