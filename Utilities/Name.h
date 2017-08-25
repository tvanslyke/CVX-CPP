/*
 * Name.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef UTILITIES_NAME_H_
#define UTILITIES_NAME_H_

#include <cstddef>
/* from: https://stackoverflow.com/questions/15858141/conveniently-declaring-compile-time-strings-in-c/15859077#15859077 */
#include <boost/preprocessor/repetition/repeat.hpp>
#include <array>
#define GET_STR_AUX_(_, i, str) (sizeof(str) > (i) ? str[(i)] : 0),
#define GET_STR_(str) BOOST_PP_REPEAT(64,GET_STR_AUX_,str) 0
/* */

template <char ... C>
struct Name
{
	static constexpr const std::array<char, sizeof...(C) + 1> name_string_{C ..., '\0'};
	static constexpr const char * name()
	{
		return name_string_.data();
	}
};
#define SYMB(str) Name<GET_STR_(str)>



#endif /* UTILITIES_NAME_H_ */
