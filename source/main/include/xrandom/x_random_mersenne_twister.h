#ifndef __XRANDOM_MT_RANDOM_H__
#define __XRANDOM_MT_RANDOM_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_debug.h"
#include "xbase/x_random.h"
#include "xrandom/x_random.h"

namespace xcore
{
	/**
	 * @group		random_t
 	 * @desc		Mersenne Twister random number generator
	 * @note		The period is 2^19937-1, and 623-dimensional equi-distribution property is assured.
	 *			Note that this means, by default, that there is negligible serial correlation between 
	 *			successive values in the output sequence. 
	 */
	class xrndmersenne : public random_t
	{
	private:
		xrnd::xrndmt		m_rnd;

	public:
							xrndmersenne() {}
		virtual void		reset(s32 seed = 0) { m_rnd.reset(seed); }
		virtual u32			generate() { return m_rnd.generate(); }

		inline u32			randU32(u32 inBits = 32)
		{
			ASSERT(inBits <= 32);
			u32 r = generate();
			return (r >> (32 - inBits));
		}
		inline s32			randS32( u32 inBits = 31)
		{
			ASSERT(inBits <= 31);
			return (randU32(inBits + 1) - (1 << inBits));
		}
		inline f32			randF32()
		{
			u32 r          = generate();
			u32 fake_float = (r >> (32 - 23)) | 0x3f800000;
			return ((*(f32*)&fake_float) - 1.0f);
		}

		inline f32 randF32S() { return ((randF32() - 0.5f) * 2.0f); }
		inline bool randBool() { return (randU32(1) == 0); }
	};
}

#endif	///< __XRANDOM_MT_RANDOM_H__
