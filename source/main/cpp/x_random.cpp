#include "xbase/x_target.h"
#include "xbase/x_allocator.h"
#include "xbase/x_buffer.h"

#include "xrandom/x_random.h"


namespace xcore
{
	namespace xrnd
	{
		xrndgood	good;
		xrndmt		mersenne;
		xrndquick	quick;
		xrndsitmo	sitmo;

		xrndquick::xrndquick() : mSeed(0) {}

		void xrndquick::reset(s32 seed) { mSeed = seed; }
		u32 xrndquick::generate()
		{
			mSeed = mSeed * 1664525 + 1013904223; 
			return mSeed;
		}

		template <typename R> void randBuffer(R* rnd, buffer_t& buffer)
		{
			u32 r = 0;
			for (u32 i = 0; i < buffer.size(); ++i)
			{
				if ((i & 3) == 0)
				{
					r = rnd->generate();
				}
				else
				{
					r = r >> 8;
				}
				buffer.m_mutable[i] = (r & 0xff);
			}
		}

        void  randBuffer(buffer_t& buffer)
		{
			randBuffer<xrndgood>(&good, buffer);
		}
	}
}