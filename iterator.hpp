/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:28:51 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/12/06 01:00:24 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "type_traits.hpp"

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};	

	typedef std::input_iterator_tag				input_iterator_tag;
	typedef std::output_iterator_tag			output_iterator_tag;
	typedef std::forward_iterator_tag			forward_iterator_tag;
	typedef std::bidirectional_iterator_tag		bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag		random_access_iterator_tag;

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type 		difference_type;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T* 								pointer;
		typedef T& 								reference;
		typedef random_access_iterator_tag		iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T* 						pointer;
		typedef const T& 						reference;
		typedef random_access_iterator_tag		iterator_category;
	};

	template <class Iterator>
	class reverse_iterator
	{
					
		private:
			Iterator _current;

		public:	
			typedef			 Iterator										iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type 	difference_type;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			
			reverse_iterator() : _current (nullptr) {}
			explicit reverse_iterator(Iterator iter) : _current(iter) {}

			template <class U>
				reverse_iterator(const reverse_iterator<U> &other) : _current(other.base()) {}
				
			~reverse_iterator() {}
			
			template <class U>
			reverse_iterator& operator=(const reverse_iterator<U> &other)
			{
				_current = other.base();
				return (*this);
			}	
			
			Iterator base() const { return (_current); }
			
			reference operator* () const
			{
				Iterator tmp = _current;
				return (*--tmp);
			}
			
			pointer   operator->() const { return (&operator*()); }
			
			reverse_iterator &operator++()
			{ 
				--_current;
				return (*this);
			}
			
			reverse_iterator  operator++(int)
			{ 
				reverse_iterator tmp(*this);
				--_current;
				return (tmp);
			}
			
			reverse_iterator &operator--()
			{
				++_current;
				return (*this);
			}
			
			reverse_iterator  operator--(int)
			{
				reverse_iterator tmp(*this);
				++_current;
				return (tmp);
			}
			
			reverse_iterator  operator+ (difference_type n) const
			{
				return (reverse_iterator(_current - n));
			}
			
			reverse_iterator &operator+=(difference_type n)
			{
				_current -= n;
				return (*this);
			}
			
			reverse_iterator  operator- (difference_type n) const
			{
				return (reverse_iterator(_current + n));
			}

			reverse_iterator &operator-=(difference_type n)
			{
				_current += n;
				return (*this);
			}
			
			reference         operator[](difference_type n) const
			{
				return (*(*this + n));
			}
	};

	template <class Iterator1, class Iterator2>
	inline	bool operator==(const ft::reverse_iterator <Iterator1> &lhs,
							const ft::reverse_iterator <Iterator2> &rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator< (const ft::reverse_iterator <Iterator1> &lhs,
							const ft::reverse_iterator <Iterator2> &rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator!=(const ft::reverse_iterator <Iterator1> &lhs,
							const ft::reverse_iterator <Iterator2> &rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator> (const ft::reverse_iterator <Iterator1> &lhs,
							const ft::reverse_iterator <Iterator2> &rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator>=(const ft::reverse_iterator <Iterator1> &lhs,
							const ft::reverse_iterator <Iterator2> &rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator<=(const ft::reverse_iterator <Iterator1> &lhs,
							const ft::reverse_iterator <Iterator2> &rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline typename ft::reverse_iterator <Iterator1>::difference_type
				 operator- (const ft::reverse_iterator <Iterator1> &lhs,
							const ft::reverse_iterator <Iterator2> &rhs)
		{
			return (rhs.base() - lhs.base());
		}

	template <class Iterator>
	inline typename ft::reverse_iterator <Iterator>
				 operator+ (typename ft::reverse_iterator <Iterator>::difference_type n,
							const 	 ft::reverse_iterator <Iterator> &x)
		{
			return reverse_iterator <Iterator>(x.base() - n);
		}

	template <class Iterator>
	class random_access_iterator
	{
		private:
			Iterator _current;

		public:
			typedef			 Iterator											iterator_type;
			typedef typename std::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type				value_type;
			typedef typename iterator_traits<Iterator>::difference_type 		difference_type;
			typedef typename iterator_traits<Iterator>::reference				reference;
			typedef typename iterator_traits<Iterator>::pointer					pointer;

			random_access_iterator() : _current (nullptr) {}

			explicit random_access_iterator(Iterator iter) : _current(iter) {}

			template <class U>
				random_access_iterator(const random_access_iterator<U> &other) : _current(other.base()) {}
				
			~random_access_iterator() {}

			template <class U>
			random_access_iterator &operator=(const random_access_iterator<U> &other)
			{	
				this->_current = other.base();
				return (*this);
			}


			Iterator base() const { return (_current); }

			reference operator* () const
			{
				return (*_current);
			}

			pointer   operator->() const { return (&operator*()); }

			random_access_iterator &operator++()
			{ 
				++_current;
				return (*this);
			}

			random_access_iterator  operator++(int)
			{ 
				random_access_iterator tmp(*this);
				++_current;
				return (tmp);
			}

			random_access_iterator &operator--()
			{
				_current--;
				return (*this);
			}
			
			random_access_iterator  operator--(int)
			{
				random_access_iterator tmp(*this);
				_current--;
				return (tmp);
			}

			random_access_iterator  operator+ (difference_type n) const
			{
				return (random_access_iterator(_current + n));
			}
			
			random_access_iterator &operator+=(difference_type n)
			{
				_current += n;
				return (*this);
			}

			random_access_iterator  operator- (difference_type n) const
			{
				return (random_access_iterator(_current - n));
			}

			random_access_iterator &operator-=(difference_type n)
			{
				_current -= n;
				return (*this);
			}
			
			reference        		operator[](difference_type n) const
			{
				return (*(*this + n));
			}
	};
	
	template <class Iterator1, class Iterator2>
	inline	bool operator==(const ft::random_access_iterator <Iterator1> &lhs,
							const ft::random_access_iterator <Iterator2> &rhs)
		{
			return (lhs.base() == rhs.base());
		}


	template <class Iterator1, class Iterator2>
	inline	bool operator< (const ft::random_access_iterator <Iterator1> &lhs,
							const ft::random_access_iterator <Iterator2> &rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator!=(const ft::random_access_iterator <Iterator1> &lhs,
							const ft::random_access_iterator <Iterator2> &rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator> (const ft::random_access_iterator <Iterator1> &lhs,
							const ft::random_access_iterator <Iterator2> &rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator>=(const ft::random_access_iterator <Iterator1> &lhs,
							const ft::random_access_iterator <Iterator2> &rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline	bool operator<=(const ft::random_access_iterator <Iterator1> &lhs,
							const ft::random_access_iterator <Iterator2> &rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class Iterator1, class Iterator2>
	inline typename ft::random_access_iterator <Iterator1>::difference_type
				 operator- (const ft::random_access_iterator <Iterator1> &lhs,
							const ft::random_access_iterator <Iterator2> &rhs)
		{
			return (lhs.base() - rhs.base());
		}

	template<class Iterator>
	inline typename ft::random_access_iterator<Iterator>
				 operator+ (typename ft::random_access_iterator<Iterator>::difference_type n,
							const 	 ft::random_access_iterator<Iterator> &x)
		{
			return random_access_iterator <Iterator>(x.base() + n);
		}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
		do_distance(Iterator first, Iterator last, input_iterator_tag)
		{
			typename iterator_traits <Iterator>::difference_type dist = 0;
			while (first != last)
			{
				first++;
				dist++;
			}
			return (dist);
		}

	template <class RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type
		do_distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
		{
			return (last - first);
		}
	
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last)
		{
			return (do_distance(first, last, typename iterator_traits <Iterator>::iterator_category()));
		}

	template<class Iterator>
		void do_advance(Iterator &it, typename iterator_traits <Iterator>::difference_type n, input_iterator_tag)
		{
			while (n > 0) {
				--n;
				++it;
			}
		}

	template<class Iterator>
		void do_advance(Iterator &it, typename iterator_traits <Iterator>::difference_type n, bidirectional_iterator_tag)
		{
			while (n > 0) {
				--n;
				++it;
			}
			while (n < 0) {
				++n;
				--it;
			}
		}

	template<class Iterator>
		void do_advance(Iterator &it, typename iterator_traits <Iterator>::difference_type n, random_access_iterator_tag)
		{
			it += n;
		}

	template<class Iterator, class Distance>
		void advance(Iterator &it, Distance n)
		{
			do_advance(it, typename iterator_traits <Iterator>::difference_type(n),
						   typename iterator_traits <Iterator>::iterator_category());
		}
}

#endif
