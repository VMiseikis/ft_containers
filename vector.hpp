/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:16:09 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/12/06 17:04:45 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"
# include "type_traits.hpp"


namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef 		 T											value_type;
			typedef 		 Allocator 									allocator_type;
			typedef typename allocator_type::difference_type			difference_type;
			typedef typename allocator_type::size_type					size_type;
			typedef typename allocator_type::pointer 		 			pointer;
			typedef typename allocator_type::reference		 			reference;
			typedef typename allocator_type::const_pointer 	 			const_pointer;
			typedef typename allocator_type::const_reference			const_reference;
			typedef 		 ft::random_access_iterator<pointer>		iterator; 
			typedef			 ft::random_access_iterator<const_pointer>  const_iterator;
			typedef 		 ft::reverse_iterator<iterator>				reverse_iterator; 
			typedef			 ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			pointer 		_vct;
			size_type		_vsize;
			size_type 		_vcapacity;
			allocator_type 	_allocator;

		public:	
			explicit vector(const allocator_type &alloc = allocator_type())
					 		: _vct(nullptr),  _vsize(0), _vcapacity(0), _allocator(alloc) {}
			
			explicit vector(size_type n, const value_type &val = value_type(),
							const allocator_type &alloc = allocator_type())
							: _vct(nullptr), _vsize(n), _vcapacity(n), _allocator(alloc)
			{
				if (_vcapacity > max_size())
					throw (std::length_error("ft vector size"));
				_vct = _allocator.allocate(n);
				size_type i = 0;
				try
				{
					for (i = 0; i < n; i++)
						_allocator.construct(_vct + i, val);
				} catch (...) {
					for (; i > 0; i--)
						_allocator.destroy(&_vct[i]);
					_allocator.deallocate(_vct, n);
					throw; 
				}
			}

			template <class InputIterator>
			vector( InputIterator first,
					typename enable_if <!ft::is_integral <InputIterator>::value, InputIterator>::type last,
					const allocator_type& alloc = allocator_type())
			: _vct(nullptr),  _vsize(0), _vcapacity(0), _allocator(alloc)
			{
				do_ctor_range(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
			}

			template <class InputIterator>
       		void do_ctor_range(InputIterator first, InputIterator last, input_iterator_tag)
			{ construct_input(first, last); }

			template <class InputIterator>
       		void do_ctor_range(InputIterator first, InputIterator last, random_access_iterator_tag)
			{ construct_range(first, last); }

			template <class InputIterator>
			void construct_input(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					push_back(*first);
			}

			template <class InputIterator>
			void construct_range(InputIterator first, InputIterator last)
			{
				InputIterator tmp = first;
				for (; tmp != last; _vcapacity++, tmp++) {}

				if (_vcapacity > max_size())
					throw (std::length_error("ft vector size"));
				tmp = first;
				try
				{
					_vct = _allocator.allocate(_vcapacity);
					for (; first != last; first++, _vsize++)
						_allocator.construct(_vct + _vsize, *first);
				} catch (...) {
					for (; tmp != first; tmp--, _vsize--)
						_allocator.destroy(_vct + _vsize);
					_allocator.deallocate(_vct, _vcapacity);
					_vcapacity = 0;
					throw; 
				} 
			}

			vector(const vector &src)
			: _vct(nullptr), _vsize(0), _vcapacity(src.capacity()), _allocator(src.get_allocator())
			{ 
				const_iterator it = src.begin();
				try
				{
					_vct = _allocator.allocate(_vcapacity);
					for (; it != src.end(); it++, _vsize++)
						_allocator.construct(_vct + _vsize, *it);
				} catch (...) {
					for (; it != src.begin(); it--, _vsize--)
						_allocator.destroy(_vct + _vsize);
					_allocator.deallocate(_vct, _vcapacity);
					_vcapacity = 0;
					throw;
				}
			}

			~vector()
			{
				clear();
				if (_vct != nullptr)
					_allocator.deallocate(_vct, _vcapacity);
			}

			vector &operator=(const vector &other)
			{
				if (this != &other)
				{
					clear();
					if (other._vcapacity < _vcapacity)
					{
						vector temp_vct;
						temp_vct.reserve(other._vcapacity);
						swap(temp_vct);						
					}
					insert(begin(), other.begin(), other.end());
				}
				return (*this);
			}

			allocator_type get_allocator() const
			{ return (_allocator); }

			iterator begin()
			{ return (iterator(_vct)); }

			iterator end()
			{ return (iterator(_vct + _vsize)); }

			reverse_iterator rbegin()
			{ return (reverse_iterator(end())); }

			reverse_iterator rend()
			{ return (reverse_iterator(begin())); }

			const_iterator begin() const
			{ return (const_iterator(_vct)); }

			const_iterator end() const
			{ return (const_iterator(_vct + _vsize)); }

			const_reverse_iterator rbegin() const
			{ return (const_reverse_iterator(end())); }

			const_reverse_iterator rend() const
			{ return (const_reverse_iterator(begin())); }

			reference operator[]( size_type pos)
			{ return (_vct[pos]); }

			const_reference operator[]( size_type pos) const
			{ return (_vct[pos]); }

			reference at(size_type n)
			{
				if (n >= _vsize)
					throw (std::out_of_range("ft vector index"));
				return (_vct[n]);
			}

			const_reference at(size_type n) const
			{
				if (n >= _vsize)
					throw (std::out_of_range("ft vector index"));
				return (_vct[n]);	
			}

			reference front()
			{ return (*_vct); }

			const_reference front() const
			{ return (*_vct); }

			reference back()
			{ return *(_vct + _vsize - 1); }

			const_reference back() const
			{ return *(_vct + _vsize - 1); }

			value_type *data() {
				if (_vsize != 0)
					return (_vct);
				return (nullptr);
			}

			const value_type *data() const
			{
				if (_vsize != 0)
					return (_vct);
				return (nullptr);
			}

			bool empty() const
			{ return (_vsize == 0); }

			size_type size() const
			{ return (_vsize); }

			size_type max_size() const 
			{ 
				size_type amax = _allocator.max_size();
				size_type nmax = static_cast<size_type>(std::numeric_limits<difference_type>::max());
				if (amax > nmax)
					return (nmax);
				return (amax);
			}

			size_type capacity() const
			{ return (_vcapacity); }
			
			void clear()
			{
				while (_vsize > 0)
					pop_back();
			}

			void pop_back()
			{
				_vsize--;
				_allocator.destroy(_vct + _vsize);
			}

			void push_back(const T &value)
			{
				if (_vsize + 1 > _vcapacity)
				{
					if (_vcapacity == 0)
						reserve(1);
					else
						reserve(_vcapacity + _vcapacity);
				}
				try
				{
					_allocator.construct(_vct + _vsize, value);
					_vsize++;
				} catch (...) {
					_allocator.destroy(_vct + _vsize);
					throw;
				}
			}

			void reserve(size_type new_cap)
			{
				if (new_cap > max_size() || new_cap < 0)
					throw (std::length_error("ft vector size"));

				if (new_cap > _vcapacity)
				{
					pointer new_vct;
					new_vct = _allocator.allocate(new_cap);

					if (_vcapacity != 0)
					{
						size_type i = 0;
						try
						{
							for (; i < _vsize; i++)
								_allocator.construct(new_vct + i, _vct[i]);
						}
						catch (...)
						{
							for (; i > 0; i--)
								_allocator.destroy(&new_vct[i]);
							_allocator.deallocate(new_vct, new_cap);
							throw;
						}
						for (size_type i = 0; i < _vsize; i++)
							_allocator.destroy(&_vct[i]);;
					}
					if (_vct != nullptr)
						_allocator.deallocate(_vct, _vcapacity);
					_vct = new_vct;
					_vcapacity = new_cap;
				}
			}

			void resize(size_type count, T value = T())
			{
				size_type temp = _vsize;

				if (count > max_size())
					throw (std::length_error("ft vector size"));

				while (count < _vsize)
					pop_back();

				if (count > _vcapacity)
				{
					size_type temp = _vcapacity;

					if (_vcapacity == 0)
						temp = 1;
					while (count > temp)
						temp += temp;
					reserve(temp);
				}
				try
				{
					for (; _vsize < count; _vsize++)
						_allocator.construct(_vct + _vsize, value);
				}
				catch (...)
				{
					for (; _vsize > temp; _vsize--)
						_allocator.destroy(_vct + _vsize);
					throw;
				}
			}

			iterator insert(iterator position, const value_type &val)
			{
				difference_type dist = ft::distance(begin(), position);

				if (_vsize + 1 > _vcapacity)
					reserve(_vcapacity + _vcapacity);
				insert (begin() + dist, 1, val);

				return (begin() + dist);
			}

    		void insert(iterator position, size_type n, const value_type &val)
			{
				if (n <= 0)
					return ;

				size_type count = _vsize + n;
				difference_type dist = ft::distance(begin(), position);
				vector temp_vct(begin(), end());
				if (count > _vcapacity)
					reserve(count);
				try
				{
					for (difference_type i = _vsize - 1; i >= dist; i--)
					{
						_allocator.construct(_vct + n + i, *(_vct + i));
						_allocator.destroy(_vct + i);
					}
					for (size_type i = 0; i < n; i++, _vsize++)
						_allocator.construct(_vct + dist + i, val);
				}
				catch (...)
				{ 
					swap(temp_vct);
					throw;
				}
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename enable_if <!ft::is_integral <InputIterator>::value, InputIterator>::type* = nullptr)
			{ do_insert(position, first, last, typename ft::iterator_traits<InputIterator>::iterator_category()); }

			template<class InputIterator>
			void do_insert(iterator position, InputIterator first, InputIterator last, random_access_iterator_tag)
			{ rand_it_insert(position, first, last); }

			template<class InputIterator>
			void do_insert(iterator position, InputIterator first, InputIterator last, input_iterator_tag)
			{ input_it_insert(position, first, last); }

			template<class InputIterator>
			void input_it_insert(iterator position, InputIterator first, InputIterator last)
			{
				(void) position;
				if (position == end())
				{
					for (; first != last; first++)
				 		push_back(*first);
				}
				else if (first != last)
				{
					rand_it_insert(position, first, last);
				}
       		}

			template <class InputIterator>
			void rand_it_insert(iterator position, InputIterator first, InputIterator last)
			{
				if (first == last)
					return;
				
				size_type n = ft::distance(first, last);
				difference_type dist = ft::distance(begin(), position);
				size_type count = _vsize + n;

				vector temp_vct(begin(), end());

				if (_vcapacity == 0)
					reserve(count);
				else if (n > _vcapacity)
					reserve(count);
				else
				{
					size_type temp = _vcapacity;
					while (count > temp)
						temp += temp;
					reserve(temp);
				}
				try
				{
					for (difference_type i = _vsize - 1; i >= dist; i--)
					{
						_allocator.construct(_vct + n + i, *(_vct + i));
						_allocator.destroy(_vct + i);
					}
					for (; first != last; first++, dist++, _vsize++)
						_allocator.construct(_vct + dist, *first);
				}
				catch (...)
				{
					swap(temp_vct);
					throw;
				}
			}

			void assign(size_type n, const value_type &val)
			{
				clear();
				reserve(n);
				size_type i = 0;
				try {
					for (i = 0; i < n; i++)
					{
						_allocator.construct(_vct + _vsize, val);
						_vsize++;
					}
				} catch (...) {
					for (; i > 0; i--)
					{
						_allocator.destroy(_vct + _vsize);
						_vsize--;
					}
					throw;
				}
			}

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
						typename enable_if <!ft::is_integral <InputIterator>::value, InputIterator>::type* = nullptr)
			{
				clear();
				insert(begin(), first, last);
			}

			void swap(vector &x)
			{
				pointer		tmp_vct 		= _vct;
				size_type 	tmp_vsize 		= _vsize;
				size_type 	tmp_vcapacity 	= _vcapacity;

				_vct = x._vct;
				_vsize = x._vsize;
				_vcapacity = x._vcapacity;
			
				x._vct = tmp_vct;
				x._vsize = tmp_vsize;
				x._vcapacity = tmp_vcapacity;
			}

			iterator erase(iterator position)
			{
				size_type dist = ft::distance(begin(), position);
				for (; dist < _vsize; dist++)
				{
					_allocator.destroy(_vct + dist);
					try {
						if ((dist + 1) < _vsize)
							_allocator.construct(_vct + dist, *(_vct + dist + 1));
					} catch (...) { throw; }
				}
				_vsize--;

				return (position);
			}

			iterator erase(iterator first, iterator last)
			{
				size_type dist = ft::distance(begin(), first);
				size_type count = ft::distance(first, last);

				if (first == last)
					return (first);

				for (; dist < _vsize; dist++)
				{
					_allocator.destroy(_vct + dist);
					try {
						if (dist + count < _vsize)
							_allocator.construct(_vct + dist, *(_vct + dist + count));
					} catch (...) { throw; }
				}
				_vsize -= count;

				return (first);
			}
	};

	template <class T, class Alloc>
		bool operator==(const vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
			{ return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

	template <class T, class Alloc>
		bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
			{ return !(lhs == rhs); }

	template <class T, class Alloc>
		bool operator< (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
			{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	
	template <class T, class Alloc>
		bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
			{ return !(rhs < lhs); }
	
	template <class T, class Alloc>
		bool operator> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
			{ return (rhs < lhs); }
	
	template <class T, class Alloc>
		bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
			{ return !(lhs < rhs); }
	
	template <class T, class Alloc>
		void swap (vector<T, Alloc> &x, vector<T, Alloc> &y)
			{ x.swap(y); }
}

#endif
