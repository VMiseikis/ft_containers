/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:28:05 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/10/07 20:14:58 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								      InputIterator2 first2, InputIterator2 last2)
		{
			while ((first1 != last1) && (first2 != last2))
			{
				if (*first1 < *first2)
					return (true);
				if (*first2 < *first1)
					return (false);
				++first1;
				++first2;
			}
			return ((first1 == last1) && (first2 != last2));
		}
	
	template <class InputIterator1, class InputIterator2, class Compare>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									  InputIterator2 first2, InputIterator2 last2, Compare comp)
		{
			while ((first1 != last1) && (first2 != last2))
			{
				if (comp(*first1, *first2))
					return (true);
				if (comp(*first2, *first1))
					return (false);
				++first1;
				++first2;
			}
			return ((first1 == last1) && (first2 != last2));
		}
}

#endif
