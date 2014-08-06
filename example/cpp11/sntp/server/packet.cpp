//
// packet.cpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2014 Lee Clagett (code at leeclagett dot com)
// 
// Distributed under the Boost Software License, Version 1.0. (See accompanying)
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "packet.hpp"

namespace sntp
{
    namespace
    {
	void set_flags(std::uint8_t& flags)
	{
	}

	const std::uint8_t primary_reference = 1;
	const std::uint8_t sixty_four_second_poll_interval = 6;
	const std::uint8_t uncalibrated_local_clock[4] = {'L', 'O', 'C', 'L'};
    }

    packet::packet() :
	flags_(),
	stratum_(),
	poll_(),
	precision_(),
	delay_(),
	dispersion_(),
	identifier_(),
	reference_(),
	originate_(),
	receive_(),
	transmit_(),
	key_identifier_(),
	digest_()
    {
    }   

    void packet::fill_server_values()
    {
	receive_ = timestamp::now();

	set_flags(flags_);
	stratum_ = primary_reference;
	poll_ = sixty_four_second_poll_interval;
	precision_ = timestamp::precision();
	delay_ = 0;
	dispersion_ = 0;
	static_assert(sizeof(identifier_) == sizeof(uncalibrated_local_clock), "size mismatch");
	std::memcpy(identifier_, uncalibrated_local_clock, sizeof(identifier_));
	reference_ = timestamp();
	originate_ = transmit_;

	transmit_ = timestamp::now();
    }
}