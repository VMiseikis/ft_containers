/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:28:05 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/12/02 23:26:39 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef 		 Container							container_type;
			typedef typename container_type::size_type			size_type;
			typedef typename container_type::reference 			reference;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::const_reference	const_reference;

			explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}
			
			~stack() {} 
			
			stack &operator=(const stack &other)
			{
				this->c = other.c;
				return (*this);
			}

			value_type	 		&top() 							{ return (c.back()); }
			const value_type	&top() const 					{ return (c.back()); }
			bool 				empty() const					{ return (c.empty()); }
			size_type 			size() const 					{ return (c.size()); }
			void 				push(const value_type &value)	{ c.push_back(value); }
			void 				pop() 							{ c.pop_back(); }
		
			friend bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
			{ return (lhs.c == rhs.c); }

			friend bool operator< (const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
			{ return (lhs.c < rhs.c); }
		
			friend bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
			{ return !(lhs == rhs); }

			friend bool operator> (const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
			{ return (rhs < lhs); }

			friend bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
			{ return !(lhs < rhs);}

			friend bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
			{ return !(rhs < lhs); }
		
		protected:
			container_type c;
	};
}

#endif
