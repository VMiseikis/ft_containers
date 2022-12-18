/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:27:53 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/12/04 01:15:25 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "./utils/RB_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>,
			  class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key                                      key_type;
			typedef T                                        mapped_type;
			typedef ft::pair<const key_type, mapped_type>    value_type;
			typedef Compare                                  key_compare;
			typedef Allocator                                allocator_type;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::pointer 		 pointer;
			typedef typename allocator_type::const_pointer	 const_pointer;
			typedef 		 value_type&	 				 reference;
			typedef const 	 value_type&					 const_reference;

			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected:
					key_compare comp;
					value_compare(key_compare c) : comp(c) {}

				public:
					bool operator()(const value_type &x, const value_type &y) const
					{ return comp(x.first, y.first); }
			};

			typedef RB_tree<value_type, value_compare, allocator_type> rbtree_type;

			typedef typename rbtree_type::iterator 			iterator;
			typedef typename rbtree_type::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

		private:
			allocator_type	_allocator;
			key_compare		_kcompare;
			rbtree_type		_rbtree;

		public:
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _kcompare(comp), _rbtree(comp) {}

			template <class InputIterator> 
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _kcompare(comp), _rbtree(comp) { insert(first, last); }

			map(const map& other) : _allocator(other._allocator), _kcompare(other._kcompare), _rbtree(other._rbtree) {}
			
			~map() {}

			map &operator=(const map &other)
			{
				if (this != &other)
				{
					_allocator	= other._allocator;
					_kcompare  	= other._kcompare;
					_rbtree	  	= other._rbtree;
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

			mapped_type &operator[](const key_type &k)
			{ return (this->insert(ft::make_pair(k, mapped_type())).first->second); }
			
			mapped_type &at(const key_type &k)
			{ return (_rbtree.at(ft::make_pair(k, mapped_type())).second); }

			const mapped_type &at(const key_type &k) const
			{ return (_rbtree.at(ft::make_pair(k, mapped_type())).second); }

			ft::pair<iterator, bool> insert(const value_type &val)
			{ return (_rbtree.insert(val)); }

			iterator insert(iterator position, const value_type& val)
			{ return (_rbtree.insert(position, val)); }

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{ _rbtree.insert(first, last); }

			void erase(iterator position)
			{ _rbtree.erase(position); }

			size_type erase(const key_type& k)
			{ return (_rbtree.erase(ft::make_pair(k, mapped_type()))); }

     		void erase(iterator first, iterator last)
			{ _rbtree.erase(first, last); }

			void swap(map &other)
			{ _rbtree.swap(other._rbtree); }

			void clear()
			{ _rbtree.clear(); }

			key_compare key_comp() const
			{ return (_kcompare); }

			value_compare value_comp() const
			{ return (value_compare(key_comp())); }
			
			iterator find(const key_type &k)
			{ return iterator(_rbtree.find(ft::make_pair(k, mapped_type())));}

			const_iterator find(const key_type &k) const
			{ return (_rbtree.find(ft::make_pair(k, mapped_type())));}
			
			size_type count(const key_type &k) const
			{ 
				if (find(k) == end())
					return (false);
				return (true);
			}

			iterator lower_bound(const key_type &k)
			{ return (_rbtree.lower_bound(ft::make_pair(k, mapped_type()))); }

			const_iterator lower_bound(const key_type &k) const
			{ return (_rbtree.lower_bound(ft::make_pair(k, mapped_type()))); }

			iterator upper_bound(const key_type &k)
			{ return (_rbtree.upper_bound(ft::make_pair(k, mapped_type()))); }

			const_iterator upper_bound(const key_type &k) const
			{ return (_rbtree.upper_bound(ft::make_pair(k, mapped_type()))); }

			pair<iterator, iterator>equal_range(const key_type &k)
			{ return (ft::make_pair(lower_bound(k), upper_bound(k))); }

			pair<const_iterator,const_iterator> equal_range(const key_type &k) const
			{ return (ft::make_pair(lower_bound(k), upper_bound(k))); }	
	};

	template< class Key, class T, class Compare, class Allocator >
		bool operator==( const map<Key, T, Compare, Allocator> &lhs,
						 const map<Key, T, Compare, Allocator> &rhs)
			{ return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

	template< class Key, class T, class Compare, class Allocator >
		bool operator!=( const map<Key, T, Compare, Allocator> &lhs,
						 const map<Key, T, Compare, Allocator> &rhs)
			{ return !(lhs == rhs); }

	template< class Key, class T, class Compare, class Allocator >
		bool operator< ( const map<Key, T, Compare, Allocator> &lhs,
						 const map<Key, T, Compare, Allocator> &rhs)
			{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template< class Key, class T, class Compare, class Allocator >
		bool operator<=( const map<Key, T, Compare, Allocator> &lhs,
						 const map<Key, T, Compare, Allocator> &rhs)
			{ return !(rhs < lhs); }

	template< class Key, class T, class Compare, class Allocator >
		bool operator> ( const map<Key, T, Compare, Allocator> &lhs,
						 const map<Key, T, Compare, Allocator> &rhs)
			{ return (rhs < lhs); }

	template< class Key, class T, class Compare, class Allocator >
		bool operator>=( const map<Key, T, Compare, Allocator> &lhs,
						 const map<Key, T, Compare, Allocator> &rhs)
			{ return !(lhs < rhs); }

  	template< class Key, class T, class Compare, class Allocator >
 		void swap( map<Key, T, Compare, Allocator> &lhs,
				   map<Key, T, Compare, Allocator> &rhs)
			{ lhs.swap(rhs); }
}

#endif
