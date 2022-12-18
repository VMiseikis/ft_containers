/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:31:54 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/12/02 23:31:55 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{
	template <bool Cond, class T = void> struct enable_if {};
	template <class T> struct enable_if <true, T> { typedef T type; };
}

#endif
