/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_function.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:32:03 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/12/03 00:04:21 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_FUNCTIONS_HPP
# define BINARY_FUNCTIONS_HPP

namespace ft {
    template <class Arg1, class Arg2, class Result>
    struct binary_function {
        typedef Arg1   first_argument_type;
        typedef Arg2   second_argument_type;
        typedef Result result_type;
    };

    template<class T>
    struct less: public binary_function<T, T, bool>
	{
        bool operator()(const T &lhs, const T &rhs) const
		{ return lhs < rhs; }
    };
}

#endif
