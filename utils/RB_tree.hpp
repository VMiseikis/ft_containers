/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RB_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:27:23 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/12/06 15:52:30 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include "../iterator.hpp"
#include "../type_traits.hpp"

namespace ft
{
	enum node_color {RED, BLACK, LEAF};
	enum direction {LEFT, RIGHT};

	template <typename T>
	class RB_tree_node
	{
		public:
			typedef T				value_type;
			typedef	RB_tree_node*	node_ptr;
		
			node_ptr	parent;
			node_ptr	left;
			node_ptr	right;
			node_color	color;
			value_type	key;
			
			RB_tree_node() : parent(NULL), left(NULL), right(NULL), color(RED), key() {}
			RB_tree_node(node_color color) :  parent(NULL), left(NULL), right(NULL), color(color), key() {}
			RB_tree_node(const value_type &val) : parent(NULL), left(NULL), right(NULL), color(RED), key(val) {}
			RB_tree_node(const RB_tree_node &other) : parent(other.parent), left(other.left), right(other.right), color(other.color), key(other.key) {}

			~RB_tree_node() {}

			RB_tree_node &operator=(const RB_tree_node &other)
			{
				if (this != &other)
				{
					left 	= other.left;
					right 	= other.right;
					parent 	= other.parent;
					key 	= other.key;
					color	= other.color;
				}
				return (this);
			}
	};

	template <typename T, typename Node>
	class RB_tree_iterator
	{
		public:
			typedef T			value_type;
			typedef T*			pointer;
			typedef T&			reference;
			typedef Node*		node_type;
			typedef ptrdiff_t	difference_type;

			typedef bidirectional_iterator_tag	iterator_category;

			RB_tree_iterator() : _node(NULL) {}
			RB_tree_iterator(const node_type &other) : _node(other) {}
			RB_tree_iterator(const RB_tree_iterator<T, Node> &other) : _node(other.base()) {}

			~RB_tree_iterator() {}

			node_type base() const { return (_node); }

			RB_tree_iterator& operator=(const RB_tree_iterator &other)
			{
				if (this != &other)
					_node = other.base();
				return (*this);
			}
			reference 	operator* () const { return ( _node->key); }
			pointer 	operator->() const { return (&_node->key); }

			bool operator==(const RB_tree_iterator &other)
       			{ return (_node == other._node); }
			bool operator!=(const RB_tree_iterator &other)
				{ return (_node != other._node); }

			RB_tree_iterator& operator++()
			{
				if (_node == NULL || _node->color == LEAF)
					return (*this);
	
				if (_node->right != NULL)
				{	
					_node = _node->right;
					while (_node->left != NULL && _node->color != LEAF)
						_node = _node->left;
				}
				else
				{
					node_type parent = _node->parent;
					while (parent != NULL && parent->color != LEAF && _node == parent->right)
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (*this);
			}

			RB_tree_iterator& operator--()
			{
				if (_node == NULL)
					return (*this);
				
				if (_node->left != NULL && _node->color != LEAF)
				{
					_node = _node->left;
					while (_node->right != NULL && _node->color != LEAF)
						_node = _node->right;
				}
				else
				{
					node_type parent = _node->parent;
					while (parent != NULL && parent->color != LEAF && _node == parent->left)
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (*this);
			}

			RB_tree_iterator operator++(int)
			{
				RB_tree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			RB_tree_iterator operator--(int)
			{
				RB_tree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			friend bool operator==(const RB_tree_iterator &lhs, const RB_tree_iterator &rhs)
			{ return (lhs.base() == rhs.base()); }

			friend bool operator!=(const RB_tree_iterator &lhs, const RB_tree_iterator &rhs)
			{ return (lhs.base() != rhs.base()); }

		private:
			node_type _node;
	};

	template <typename T, typename Node>
	class const_RB_tree_iterator
	{
		public:
			typedef 	  T		value_type;
			typedef const T*	pointer;
			typedef const T&	reference;
			typedef const Node*	node_type;
			typedef ptrdiff_t	difference_type;

			typedef bidirectional_iterator_tag	iterator_category;

			const_RB_tree_iterator() : _node(NULL) {}
			const_RB_tree_iterator(const node_type &other) : _node(other) {}
			const_RB_tree_iterator(const RB_tree_iterator<T, Node> &other) : _node(other.base()) {}

			~const_RB_tree_iterator() {}

			node_type base() const { return (_node); }

			const_RB_tree_iterator& operator=(const const_RB_tree_iterator &other)
			{
				if (this != &other)
					_node = other.base();
				return (*this);
			}
			reference 	operator* () const { return ( _node->key); }
			pointer 	operator->() const { return (&_node->key); }

			bool operator==(const const_RB_tree_iterator &other)
       			{ return (_node == other._node); }
			bool operator!=(const const_RB_tree_iterator &other)
				{ return (_node != other._node); }

			const_RB_tree_iterator& operator++()
			{
				if (_node == NULL || _node->color == LEAF)
					return (*this);
	
				if (_node->right != NULL)
				{	
					_node = _node->right;
					while (_node->left != NULL && _node->color != LEAF)
						_node = _node->left;
				}
				else
				{
					node_type parent = _node->parent;
					while (parent != NULL && parent->color != LEAF && _node == parent->right)
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (*this);
			}

			const_RB_tree_iterator& operator--()
			{
				if (_node == NULL)
					return (*this);
				
				if (_node->left != NULL && _node->color != LEAF)
				{
					_node = _node->left;
					while (_node->right != NULL && _node->color != LEAF)
						_node = _node->right;
				}
				else
				{
					node_type parent = _node->parent;
					while (parent != NULL && parent->color != LEAF && _node == parent->left)
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (*this);
			}

			const_RB_tree_iterator operator++(int)
			{
				const_RB_tree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			const_RB_tree_iterator operator--(int)
			{
				const_RB_tree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			friend bool operator==(const const_RB_tree_iterator &lhs, const const_RB_tree_iterator &rhs)
			{ return (lhs.base() == rhs.base()); }

			friend bool operator!=(const const_RB_tree_iterator &lhs, const const_RB_tree_iterator &rhs)
			{ return (lhs.base() != rhs.base()); }

		private:
			node_type _node;
	};

	template <class T, class Compare, class Allocator>
	class RB_tree
	{
		public:
			typedef T 								value_type;
			typedef Compare							key_compare;
			typedef ft::RB_tree_node<value_type>	node_type;

			typedef typename Allocator::size_type							size_type;
			typedef typename Allocator::difference_type						difference_type;
			typedef typename Allocator::template rebind<node_type>::other	allocator_type;

			typedef RB_tree_iterator<value_type, node_type> 		iterator;
			typedef const_RB_tree_iterator<value_type, node_type> 	const_iterator;

		public:
			node_type*		_root;
			node_type*		_start;
			node_type*		_end;
			size_type		_size;
			allocator_type	_allocator;
			key_compare		_kcompare;

		public:
			RB_tree(const key_compare &comp, const allocator_type &alloc = allocator_type())
				: _root(NULL), _start(empty_node(LEAF)), _end(empty_node(LEAF)), _size(0), _allocator(alloc), _kcompare(comp) {}

			RB_tree(const RB_tree &other)
			: _root(NULL), _start(empty_node(LEAF)), _end(empty_node(LEAF)), _size(other._size), _allocator(other._allocator), _kcompare(other._kcompare)
			{ copy_tree(other); }

			~RB_tree()
			{ 
				clear();
				delete_node(_start);
				delete_node(_end);
			}

			RB_tree &operator=(const RB_tree &other)
			{
				copy_tree(other);
				return (*this);
			}

			ft::pair<iterator, bool> insert(const value_type& val)
			{
				node_type *node = new_node(val);

				if (_root == NULL)
					return (init_tree(&node, val));
				else
					return (main_insert(&node, _root, val));		
			}

			iterator insert(iterator position, const value_type& val)
			{
				node_type *node = new_node(val);

				if (_root == NULL)
					return (init_tree(&node, val).first);
				else
				{
					node_type *parent = NULL;
					if (position.base() == NULL)
						parent = _end;
					else
						parent = position.base();
			
					if (!_kcompare(parent->key, val))
						while (!_kcompare(parent->key, val) && parent != _root)
							parent = parent->parent;
					else if (!_kcompare(val, parent->key))
						while (!_kcompare(val, parent->key) && parent != _root)
							parent = parent->parent;

					return (main_insert(&node, parent, val).first);	
				}	
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			iterator begin()
			{ return (main_begin()); }

			iterator end () 
			{ return (_end); }

			const_iterator begin() const
			{ return (main_begin()); }

			const_iterator end() const
			{ return (_end); }

			iterator find(const value_type &val)
			{ return (main_find(val)); }

			const_iterator find(const value_type &val) const
			{ return (main_find(val)); }

			iterator lower_bound(const value_type &val)
			{ return (main_lower_bound(val)); }

			const_iterator lower_bound(const value_type &val) const
			{ return (main_lower_bound(val)); }

			iterator upper_bound(const value_type &val)
			{ return (main_upper_bound(val)); }

			const_iterator upper_bound(const value_type &val) const
			{ return (main_upper_bound(val)); }

			value_type &at(const value_type &val)
			{
				iterator it = find(val);
				if (it != end())
					return (it.base()->key);
				throw (std::out_of_range("ft map index"));
			}

			const value_type &at(const value_type &val) const
			{
				const_iterator it = find(val);
				if (it != end())
					return (it.base()->key);
				throw (std::out_of_range("ft map index"));
			}

			void swap(RB_tree &other)
			{
				node_type*		tmp_root;
				node_type*		tmp_start;
				node_type*		tmp_end;
				size_type		tmp_size;

				tmp_root	= other._root;
				tmp_start	= other._start;
				tmp_end		= other._end;
				tmp_size	= other._size;

				other._root		= _root;
				other._start	= _start;
				other._end		= _end;
				other._size		= _size;

				_root	= tmp_root;
				_start	= tmp_start;
				_end 	= tmp_end;
				_size	= tmp_size;
			}

			size_type size() const { return (_size); }

			bool empty() const
			{
				if (_root == NULL)
					return (true);
				return (false);
			}

			size_type max_size() const 
			{ 
				size_type amax = _allocator.max_size();
				size_type nmax = static_cast<size_type>(std::numeric_limits<difference_type>::max());
				if (amax > nmax)
					return (nmax);
				return (amax);
			}

			void clear()
			{
				if (_root != NULL)
				{
					_start->parent->left = NULL;
					_end->parent->right = NULL;
				}
				_start->parent = _end;
				_end->parent = _start;
				delete_tree(_root);
				_root = NULL;
				_size = 0;
			}

			size_type erase(const value_type& val)
			{ return (main_erase(main_find(val))); }

			void erase (iterator position)
			{ main_erase(position.base()); }

			void erase(iterator first, iterator last)
			{
				for(iterator it = first; it != last; first = it)
				{
					++it;
					main_erase(first.base());
				}
			}

		private:
			void copy_tree(const RB_tree &other)
			{
				if (this != &other)
				{
					clear();
					if (other._root != NULL)
					{
						insert(other.begin(), other.end());
						_size = other._size;
					}
				}
			}

			void delete_tree(node_type* node)
			{
				if (node == NULL)
					return ;
				delete_tree(node->left);
				delete_tree(node->right);
				delete_node(node);	
				_size = 0;
			}

			void delete_node(node_type* node)
			{
				_allocator.destroy(node);
				_allocator.deallocate(node, sizeof(node_type));
			}

			node_type* new_node(const value_type &val)
			{
				node_type* node = _allocator.allocate(sizeof(node_type));
				try{ 
					_allocator.construct(node, val);
					node->parent = node->left = node->right = NULL;
				} catch (...) {
					_allocator.deallocate(node, sizeof(node_type)); 
					throw;
				}
				return (node);
			}

			node_type *empty_node(node_color color)
			{
				node_type tmp(color);
				node_type *node = _allocator.allocate(sizeof(node_type));
				try {
					_allocator.construct(node, tmp);
				} catch (...) {
					_allocator.deallocate(node, sizeof(node_type));
					throw;
				}
				node->parent = node->left = node->right = NULL;
				return node;
			}

			ft::pair<iterator, bool> init_tree(node_type** node, const value_type& val)
			{

				(void) val;
				_root = *node;
				_root->color  = BLACK;
				_start->parent = _end->parent = _root;
				_root->left = _start;
				_root->right = _end;
				_size++;
				
				return ft::make_pair(iterator(*node), true);
			}

			void rotate_left(node_type **ptr)
			{
				node_type *tmp = (*ptr)->right;
				(*ptr)->right = tmp->left;

				if ((*ptr)->right != NULL)
					(*ptr)->right->parent = (*ptr);

				tmp->parent = (*ptr)->parent;
				if ((*ptr)->parent == NULL)
					_root = tmp;
				else if ((*ptr) == (*ptr)->parent->left)
					(*ptr)->parent->left = tmp;
				else
					(*ptr)->parent->right = tmp;
				tmp->left = (*ptr);
				(*ptr)->parent = tmp;
			}

			void rotate_right(node_type **ptr)
			{
				node_type *tmp = (*ptr)->left;
				(*ptr)->left = tmp->right;

				if ((*ptr)->left != NULL)
					(*ptr)->left->parent = (*ptr);

				tmp->parent = (*ptr)->parent;
				if ((*ptr)->parent == NULL)
					_root = tmp;
				else if ((*ptr) == (*ptr)->parent->left)
					(*ptr)->parent->left = tmp;
				else
					(*ptr)->parent->right = tmp;
				
				tmp->right = (*ptr);
				(*ptr)->parent = tmp;
			}

			void uncle_is_red(node_type **ptr, node_type **grandparent, node_type **uncle)
			{
					(*ptr)->parent->color = BLACK;
					(*grandparent)->color = RED;
					(*uncle)->color = BLACK;
					(*ptr) = (*grandparent);
			}

			void uncle_is_black_line(node_type **ptr, node_type **parent, int direction)
			{			 
				if (direction == LEFT)
					rotate_left(parent);
				else
					rotate_right(parent);
				(*ptr) = (*parent);
				(*parent) = (*ptr)->parent;
			}

			void uncle_is_black_triangle(node_type **ptr, node_type **parent, node_type **grandparent, int direction)
			{
				if (direction == LEFT)
					rotate_left(grandparent);
				else
					rotate_right(grandparent);

				node_color tmp = (*parent)->color;
				(*parent)->color = (*grandparent)->color;
				(*grandparent)->color = tmp;
				(*ptr) = (*ptr)->parent;
			}

			void parent_is_left_child(node_type **ptr, node_type **parent, node_type **grandparent, node_type **uncle)
			{
				if ((*uncle) != NULL && (*uncle)->color == RED)
					uncle_is_red(ptr, grandparent, uncle);
				else if ((*ptr) == (*parent)->right)
					uncle_is_black_line(ptr, parent, LEFT);
				else
					uncle_is_black_triangle(ptr, parent, grandparent, RIGHT);
			}

			void parent_is_right_child(node_type **ptr, node_type **parent, node_type **grandparent, node_type **uncle)
			{
				if ((*uncle) != NULL && (*uncle)->color == RED)
					uncle_is_red(ptr, grandparent, uncle);
				else if ((*ptr) == (*parent)->left)
					uncle_is_black_line(ptr, parent, RIGHT);
				else
					uncle_is_black_triangle(ptr, parent, grandparent, LEFT);
			}

			void fix_insert_violations(node_type *ptr)
			{
				node_type *parent = NULL;
				node_type *grandparent = NULL;

				while (ptr != _root && ptr->color == RED && ptr->parent->color == RED)
				{
					parent = ptr->parent;
					grandparent = ptr->parent->parent;
					if (ptr->parent == grandparent->left)
						parent_is_left_child(&ptr, &parent, &grandparent, &grandparent->right);
					else
						parent_is_right_child(&ptr, &parent, &grandparent, &grandparent->left);
				}
				_root->color = BLACK;
			}

			ft::pair<iterator, bool> main_insert(node_type** node, node_type* parent, const value_type& val)
			{
				node_type *current = _root;

				while(current != NULL && current->color != LEAF)
				{
					parent = current;
					if (!_kcompare(current->key, val) && !_kcompare(val, current->key))
					{
						delete_node(*node);
						return ft::make_pair(iterator(current), false);
					}
					if (_kcompare(current->key, val))
						current = current->right;
					else
						current = current->left;
				}
				(*node)->parent = parent;
				if (_kcompare(val, _start->parent->key))
				{
					(*node)->left = _start;
					_start->parent = *node;
				}
				else if (_kcompare(_end->parent->key, val))
				{
					(*node)->right = _end;
					_end->parent = *node;
				}

				if (_kcompare(parent->key, val))
					parent->right = *node;
				else
					parent->left = *node;
				fix_insert_violations(*node);
				_size++;
				
				return ft::make_pair(iterator(*node), true);	
			}		

			node_type *subtree_min(node_type *node)
			{
				while (node != NULL && node->left != NULL && node->left->color != LEAF)
					node = node->left;
				return (node);
			}

			node_type *subtree_max(node_type *node)
			{
				while (node != NULL && node->right != NULL && node->right->color != LEAF)
					node = node->right;
				return (node);
			}

			node_type *main_find(const value_type &val) const
			{
				node_type *current = _root;
				while(current != NULL && current->color != LEAF)
				{
					if (!_kcompare(current->key, val) && !_kcompare(val, current->key))
						return (current);
					if (_kcompare(current->key, val))
						current = current->right;
					else
						current = current->left;
				}
				return (_end);
			}

			node_type *main_lower_bound(const value_type &val) const
			{
				node_type *current = _root;
				node_type *lb_node = _end;

				while(current != NULL && current->color != LEAF)
				{
					if (!_kcompare(current->key, val))
					{
						lb_node = current;
						current = current->left;
					}
					else
						current = current->right;
				}
				return (lb_node);
			}

			node_type *main_upper_bound(const value_type &val) const
			{
				node_type *current = _root;
				node_type *ub_node = _end;

				while(current != NULL && current->color != LEAF)
				{
					if (_kcompare(val, current->key))
					{
						ub_node = current;
						current = current->left;
					}
					else
						current = current->right;
				}
				return (ub_node);
			}

			iterator main_begin() const
			{
				if (_root == NULL)
					return (iterator(_end));
				return (iterator(_start->parent));
			}

			void replace_nodes(node_type **node_1, node_type **node_2)
			{
				if ((*node_1)->parent == NULL)
					_root = *node_2;
				else if (*node_1 == (*node_1)->parent->left)
					(*node_1)->parent->left = *node_2;
				else
					(*node_1)->parent->right = *node_2;
				if (*node_2 != NULL)
					(*node_2)->parent = (*node_1)->parent;
			}

			void db_sibling_is_red(node_type **node, node_type **sibling, int direction)
			{
				node_type *parent = (*node)->parent;

				(*sibling)->color = BLACK;
				(*node)->parent->color = RED;
				if (direction == LEFT)
				{
					rotate_left(&parent);
					*sibling = parent->right;
				} else {
					rotate_right(&parent);
					*sibling = parent->left;
				}
			}

			void db_sibling_is_black_and_both_nephews_are_black(node_type **node, node_type **sibling)
			{
				(*sibling)->color = RED;
				*node = (*node)->parent;
			}

			void db_sibling_is_black_and_only_far_nephew_is_black(node_type **node, node_type **sibling, int direction)
			{
				(*sibling)->color = RED;
				if (direction == LEFT)
				{
					(*sibling)->right->color = BLACK;
					rotate_left(sibling);
					*sibling = (*node)->parent->left;
				} else {
					(*sibling)->left->color = BLACK;
					rotate_right(sibling);
					*sibling = (*node)->parent->right;
				}	
			}

			void db_sibling_is_black_and_far_nephew_is_red(node_type **node, node_type **sibling, int direction)
			{
				node_type *parent = (*node)->parent;

				(*sibling)->color = parent->color;
				parent->color = BLACK;
				if (direction == LEFT)
				{
					if ((*sibling)->right != NULL)
						(*sibling)->right->color = BLACK;
					rotate_left(&parent);
				}
				else
				{
					if ((*sibling)->left != NULL)
						(*sibling)->left->color = BLACK;
					rotate_right(&parent);
				}
				*node = _root;
			}

			void node_is_left_child(node_type **node)
			{
				node_type *sibling = (*node)->parent->right;
				
				if (sibling->color == RED)
					db_sibling_is_red(node, &sibling, LEFT);
				if ((sibling->left == NULL || sibling->left->color  == BLACK) 
				&& (sibling->right == NULL || sibling->right->color == BLACK))
					db_sibling_is_black_and_both_nephews_are_black(node, &sibling);
				else
				{	
					if (sibling->right == NULL || sibling->right->color == BLACK)
						db_sibling_is_black_and_only_far_nephew_is_black(node, &sibling, RIGHT);
					db_sibling_is_black_and_far_nephew_is_red(node, &sibling, LEFT);
				}
			}
		
			void node_is_right_child(node_type **node)
			{
				node_type *sibling = (*node)->parent->left;

				if (sibling->color == RED)
					db_sibling_is_red(node, &sibling, RIGHT);
				if ((sibling->left == NULL || sibling->left->color  == BLACK) 
				&& (sibling->right == NULL || sibling->right->color == BLACK))
					db_sibling_is_black_and_both_nephews_are_black(node, &sibling);
				else
				{	
					if (sibling->left == NULL || sibling->left->color == BLACK)
						db_sibling_is_black_and_only_far_nephew_is_black(node, &sibling, LEFT);
					db_sibling_is_black_and_far_nephew_is_red(node, &sibling, RIGHT);
				}
			}

			void fix_erase_violations(node_type **node)
			{
				while (*node != _root && (*node)->color == BLACK)
				{
					if (*node == (*node)->parent->left)
						node_is_left_child(node);
					else
						node_is_right_child(node);
				}
				(*node)->color = BLACK;
			}

			void update_start_end_nodes(node_type *node)
			{
				if (node == _start->parent)
				{
					if (node->right == NULL)
						_start->parent = node->parent;
					else
						_start->parent = subtree_min(node->right);
				}
				else if (node == _end->parent)
				{
					if (node->left == NULL)
						_end->parent = node->parent;
					else
						_end->parent = subtree_max(node->left);
				}
			}

			size_type node_is_last_node_in_the_tree()
			{
				clear();
				return (true);
			}

			size_type node_is_red_and_has_no_children(node_type **node)
			{
				if (*node == (*node)->parent->left)
					(*node)->parent->left = NULL;
				else
					(*node)->parent->right = NULL;
				delete_node(*node);
				_size--;
				_start->parent->left = _start;
				_end->parent->right = _end;

				return (true);
			}

			void replace_NULL_child_with_temp_node(node_type *node, node_type **child, node_type **temp)
			{
				if (*child == NULL)
				{
					*child = empty_node(BLACK);
					(*child)->parent = node;
					*temp = *child;
				}
			}

			void erase_node_from_tree(node_type **node, node_type **db_node, node_type **temp, node_color *color)
			{
				node_type *successor = *node;	

				if ((*node)->left == NULL)
				{
					replace_NULL_child_with_temp_node(*node, &(*node)->right, temp);
					*db_node = (*node)->right;
					replace_nodes(node, &(*node)->right);
				}
				else if ((*node)->right == NULL)
				{
					replace_NULL_child_with_temp_node(*node, &(*node)->left, temp);
					*db_node = (*node)->left;
					replace_nodes(node, &(*node)->left);
				}
				else
				{
					successor = subtree_min((*node)->right);
					*color = successor->color;
					replace_NULL_child_with_temp_node(*node, &successor->right, temp);
					*db_node = successor->right;
					if (successor->parent == *node)
						(*db_node)->parent = successor;
					else
					{				
						replace_nodes(&successor, &successor->right);
						successor->right = (*node)->right;
						successor->right->parent = successor;	
					}
					replace_nodes(node, &successor);
					successor->left = (*node)->left;
					successor->left->parent = successor;
					successor->color = (*node)->color;	
				}

				delete_node(*node);
				_size--;
			}

			size_type main_erase(node_type *node)
			{
				if (_root == NULL || node == _end)
					return (false);

				_start->parent->left = NULL;
				_end->parent->right = NULL;

				if (node == _root && node->left == NULL && node->right == NULL)
					return (node_is_last_node_in_the_tree());

				update_start_end_nodes(node);

				if (node->color == RED && node->left == NULL && node->right == NULL)
					return (node_is_red_and_has_no_children(&node));
				
				node_type *db_node 	= NULL;			
				node_type *temp 	= NULL;		
				node_color color 	= node->color; 

				erase_node_from_tree(&node, &db_node, &temp, &color);
						
				if (color == BLACK)
					fix_erase_violations(&db_node);

				if (temp != NULL)
				{
					if (temp == temp->parent->right)
						temp->parent->right = NULL;
					else
						temp->parent->left = NULL;
					delete_node(temp);
				}
				
				if (_root != NULL)
				{
					_start->parent->left = _start;
					_end->parent->right = _end;
				}
				
				return (true);
			}
	};
}

#endif
