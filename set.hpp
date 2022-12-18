/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:25:15 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/12/04 19:08:31 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "./utils/RB_tree.hpp"

namespace ft
{
	template <class Key, class Compare = ft::less<Key>,
			  class Allocator = std::allocator<Key> >
	class set
	{
		public:
			typedef 			Key     						key_type;
			typedef 			key_type						value_type;
			typedef 			Compare							key_compare;
			typedef 			key_compare						value_compare;
			typedef 			Allocator						allocator_type;
			typedef typename 	allocator_type::size_type       size_type;
			typedef typename 	allocator_type::difference_type difference_type;
			typedef typename 	allocator_type::pointer 		pointer;
			typedef typename 	allocator_type::const_pointer 	const_pointer;
			typedef 			value_type& 					reference;
			typedef const 		value_type& 					const_reference;

			typedef RB_tree<key_type, key_compare, allocator_type> rbtree_type;

			typedef typename rbtree_type::const_iterator 		iterator;
			typedef typename rbtree_type::const_iterator		const_iterator;
			typedef ft::reverse_iterator<const_iterator> 		reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 		const_reverse_iterator;

		public:
			explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _allocator(alloc), _kcompare(comp), _rbtree(comp) {}

			template <class InputIterator>
			set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _allocator(alloc), _kcompare(comp), _rbtree(comp)
			{ _rbtree.insert(first, last); }
			
			set(const set &other)
			: _allocator(other._allocator), _kcompare(other._kcompare), _rbtree(other._rbtree) {}

			~set() {}

			set &operator=(const set &other)
			{
				if (this != &other)
				{
					_allocator 	= other._allocator;
					_kcompare  	= other._kcompare;
					_rbtree 	= other._rbtree;
				}
				return (*this);
			}

			allocator_type get_allocator() const
			{ return (_allocator); }

			iterator begin()
			{ return (_rbtree.begin()); }

			iterator end()
			{ return (_rbtree.end()); }

			const_iterator begin() const
			{ return (_rbtree.begin()); }

			const_iterator end()   const
			{ return (_rbtree.end()); }

			reverse_iterator rbegin()
			{ return (reverse_iterator(end())); }

			reverse_iterator rend()
			{ return (reverse_iterator(begin())); }

			const_reverse_iterator rbegin() const
			{ return (const_reverse_iterator(end())); }

			const_reverse_iterator rend() const
			{ return (const_reverse_iterator(begin())); }

			bool empty() const
			{ return (_rbtree.empty()); }

			size_type size() const
			{ return (_rbtree.size()); }

			size_type max_size() const
			{ return (_rbtree.max_size()); }

			ft::pair<iterator, bool> insert(const value_type& val)
			{ return (_rbtree.insert(val)); }

			iterator insert(iterator position, const value_type& val)
			{
				(void) position;
				return (_rbtree.insert(val).first);
			}

			template <class InputIterator> 
			void insert(InputIterator first, InputIterator last)
			{ _rbtree.insert(first, last); }

			void erase (iterator position)
			{ _rbtree.erase(*position); }

			size_type erase(const value_type& val)
			{ return (_rbtree.erase(val)); }

     		void erase(iterator first, iterator last)
			{ 
				for(iterator it = first; it != last; first = it)
				{
					++it;
					erase(first);
				}
			}

			void swap(set &x)
			{ _rbtree.swap(x._rbtree); }

			void clear()
			{ _rbtree.clear(); }

			key_compare key_comp() const
			{ return (_kcompare); }

			value_compare value_comp() const
			{ return (value_compare(key_comp())); }

			iterator find(const key_type &val)
			{ return iterator(_rbtree.find(val));}

			const_iterator find(const key_type &val) const
			{ return (_rbtree.find(val));}

			size_type count(const value_type& val) const
			{ 
				if (find(val) == end())
					return (false);
				return (true);
			}

			iterator lower_bound(const key_type &k)
			{ return (_rbtree.lower_bound(k)); }

			const_iterator lower_bound(const key_type &k) const
			{ return (_rbtree.lower_bound(k)); }

			iterator upper_bound(const key_type &k)
			{ return (_rbtree.upper_bound(k)); }

			const_iterator upper_bound(const key_type &k) const
			{ return (_rbtree.upper_bound(k)); }

			pair<iterator, iterator>equal_range(const key_type &k)
			{ return (ft::make_pair(lower_bound(k), upper_bound(k))); }

			pair<const_iterator,const_iterator> equal_range(const key_type &k) const
			{ return (ft::make_pair(lower_bound(k), upper_bound(k))); }	

			private:
				allocator_type 	_allocator;
				key_compare 	_kcompare;
				rbtree_type		_rbtree;
	};

	template< class Key, class Compare, class Allocator >
		bool operator==( const set<Key, Compare, Allocator> &lhs,
						 const set<Key, Compare, Allocator> &rhs)
			{ return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

	template< class Key, class Compare, class Allocator >
		bool operator!=( const set<Key, Compare, Allocator> &lhs,
						 const set<Key, Compare, Allocator> &rhs)
			{ return !(lhs == rhs); }

	template< class Key, class Compare, class Allocator >
		bool operator< ( const set<Key, Compare, Allocator> &lhs,
						 const set<Key, Compare, Allocator> &rhs)
			{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template< class Key, class Compare, class Allocator >
		bool operator<=( const set<Key, Compare, Allocator> &lhs,
						 const set<Key, Compare, Allocator> &rhs)
			{ return !(rhs < lhs); }

	template< class Key, class Compare, class Allocator >
		bool operator> ( const set<Key, Compare, Allocator> &lhs,
						 const set<Key, Compare, Allocator> &rhs)
			{ return (rhs < lhs); }

	template< class Key, class Compare, class Allocator >
		bool operator>=( const set<Key, Compare, Allocator> &lhs,
						 const set<Key, Compare, Allocator> &rhs)
			{ return !(lhs < rhs); }

  	template< class Key, class Compare, class Allocator >
 		void swap( set<Key, Compare, Allocator> &lhs,
				   set<Key, Compare, Allocator> &rhs)
			{ lhs.swap(rhs); }
}

#endif
