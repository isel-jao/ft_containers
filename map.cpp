#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
#include <deque>

#define waza() std::cout << "WAZAAAAAAAA,\t\tline: " << __LINE__ << ",\tfunc: " << __FUNCTION__ << std::endl

struct vec
{
	int x, y, z;
	vec(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z)
	{
		std::cout << "constructor called" << std::endl;
	}
	vec(vec const &obj) : x(obj.x), y(obj.y), z(obj.z)
	{
		std::cout << "copy constructor called" << std::endl;
	}
	vec &operator=(vec &obj)
	{
		std::cout << "oparetor = is called" << std::endl;
		x = obj.x;
		y = obj.y;
		z = obj.z;
		return *this;
	}
	~vec()
	{
		std::cout << "vec deconstructor called" << std::endl;
	}
};
std::ostream &operator<<(std::ostream &out, vec &v)
{
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

template <
	typename K,
	class Compare>
struct bst
{
	K key;
	bst *left;
	bst *right;
	bst *parent;
	Compare cmp;
	bst(K const &k = K());
	bst(const bst<K, Compare> &obj);
	~bst();
};

template <typename K, class Compare>
bst<K, Compare>::bst(K const &k)
	: key(k), left(NULL), right(NULL), parent(NULL) {}

template <typename K, class Compare>
bst<K, Compare>::bst(const bst<K, Compare> &obj)
	: key(obj.key), left(obj.left), right(obj.right), parent(obj.parent) {}

template <typename K, class Compare>
bst<K, Compare>::~bst() {}

template <typename Node, typename K>
Node *bst_insert(Node *node, K const &key, bool &inserted)
{
	if (node == NULL)
		return new Node(key);

	Node *child;
	if (node->cmp(key.first, node->key.first))
	{
		child = bst_insert(node->left, key, inserted);
		if (!node->left)
			child->parent = node;
		node->left = child;
	}
	else if (node->cmp(node->key.first, key.first))
	{
		child = bst_insert(node->right, key, inserted);
		if (!node->right)
			child->parent = node;
		node->right = child;
	}
	else
		inserted = false;
	return node;
}

template <typename Node, typename K>
Node *bst_erease(Node *root, K key, bool &deleted)
{
	Node *to_delete = bst_search(root, key);
	if (!to_delete)
	{
		deleted = false;
		return root;
	}
	Node *parent = to_delete->parent;
	// if to delete has no right replace with its left
	if (!to_delete->right)
	{
		if (parent)
		{
			if (to_delete == parent->right)
				parent->right = to_delete->left;
			else if (parent && to_delete == parent->left)
				parent->left = to_delete->left;
		}
		else
			root = to_delete->left;
		if(to_delete->left)
			to_delete->left->parent = parent;
		delete to_delete;
	}
	// if to_delete has no left replace with its right
	else if (!to_delete->left)
	{
		if (parent)
		{
			if (to_delete == parent->left)
				parent->left = to_delete->right;
			else if (parent && to_delete == parent->right)
				parent->right = to_delete->right;
		}
		else
			root = to_delete->right;
		if (to_delete->right)
			to_delete->right->parent = parent;
		delete to_delete;
	}
	// if to_delte has both righ and left find next successor and replace it value with it and delete the successor instead
	else
	{
		Node *succ = to_delete->right;
		while (succ->left != NULL)
		{
			parent = succ;
			succ = succ->left;
		}
		if (parent != to_delete)
		{
			if (succ->right)
				succ->right->parent = parent;
			parent->left = succ->right;
		}
		else
		{
			if (succ->right)
				succ->right->parent = parent;
			parent->right = succ->right;
		}
		root->key = succ->key;
		delete succ;
	}
	return root;
}

template <typename Node, typename K>
Node *bst_search(Node *root, K const &key)
{
	if (!root || root->key.first == key)
		return root;
	if (root->cmp(key, root->key.first))
		return (bst_search(root->left, key));
	else
		return (bst_search(root->right, key));
}
template <typename Node, typename K>
Node *bst_nearest(Node *root, K const &key)
{
	if (!root || root->key.first == key)
		return root;
	while (true)
	{
		if (root->left && root->cmp(key, root->key.first))
			root = root->left;
		else if(root->right && root->cmp( root->key.first, key))
			root = root->right;
		else 
			return root;
	}
	
}

template <typename Node>
void bst_destroy(Node *root)
{
	if (!root)
		return;
	bst_destroy(root->left);
	Node *right = root->right;
	delete root;
	bst_destroy(right);
}
template <typename Node>
void inorder(Node *root)
{
	if (!root)
		return;
	inorder(root->left);
	std::cout << root->key.first << ", " << root->key.second << std::endl;
	inorder(root->right);
}

#define key_type Key
#define mapped_type T
#define value_type std::pair<Key, T>
#define size_type std::size_t
#define difference_type std::ptrdiff_t
#define key_compare Compare
#define allocator_type Allocator
#define reference value_type &
#define const_reference const value_type &
#define bst_node bst<value_type, Compare>
namespace ft
{
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
	private:
		key_type _key;
		mapped_type _mapped;
		value_type _value;
		bst_node *root;
		size_type _size;
		key_compare cmp;
	public:
		map()
			: _key(key_type()), _mapped(mapped_type()), _value(value_type()), root(NULL), _size(0) {}
		class iterator
		{
		public:
			iterator(bst_node *ptr = NULL) : m_ptr(ptr), end(0) {}
			iterator(iterator const &other) : m_ptr(other.m_ptr), end(other.end) {}
			~iterator() {}
			iterator &operator=(iterator const &other)
			{
				if (*this == other)
					return (*this);
				m_ptr = other.m_ptr;
				return (*this);
			}

			bool operator==(const iterator &other) { return m_ptr + end == other.m_ptr; };
			bool operator!=(const iterator &other) { return m_ptr + end != other.m_ptr; };
			value_type &operator*() const { return (m_ptr + end)->key; }
			value_type *operator->() { return &((m_ptr + end)->key); }
			iterator &operator++()
			{
				bst_node *node = m_ptr;
				// if it == m.begin() - 1
				if (end < 0)
				{
					end = 0;
					return *this;
				}
				// if it == m.end()
				if (end > 0)
					return *this;
				if (node->right)
				{
					node = node->right;
					while (node->left)
						node = node->left;
				}
				else if (node->parent)
				{
					// check if node is the left sibling
					if (node->parent->left == node)
						node = node->parent;
					// get the first parent of right sibling
					else
					{
						while (node->parent && node->parent->right == node)
							node = node->parent;
						node = node->parent;
					}
				}
				if (node)
					m_ptr = node;
				else
					end = 4;
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			iterator &operator--()
			{
				if (end > 0)
				{
					end = 0;
					return *this;
				}
				if (end < 0)
					return *this;
				bst_node *node = m_ptr;
				if (node->left)
				{
					node = node->left;
					while (node->right)
						node = node->right;
				}
				else if (node->parent)
				{

					// check if node is the right sibling
					if (node->parent->right == node)
						node = node->parent;
					// get the left parent
					else
					{
						while (node->parent && node->parent->left == node)
							node = node->parent;
						node = node->parent;
					}
				}
				if (node)
					m_ptr = node;
				else
					end = -4;
				return *this;
				// friend value_type &operator=(iterator const &other)
			}
			iterator operator--(int)
			{
				iterator tmp = *this;
				--(*this);
				return tmp;
			}

		private:
			bst_node *m_ptr;
			char end;
		};

		mapped_type &operator[](const key_type &k)
		{
			bst_node *found = bst_search(this->root, k);
			if (found)
				return (found->key.second);
			return _key;
		}
		iterator begin()
		{
			bst_node *left = root->left;
			if (!left)
				return root;
			while (left->left)
				left = left->left;
			return iterator(left);
		}

		void clear()
		{
			bst_destroy(root);
			root = NULL;
			_size = 0;
		}

		size_type count(const key_type &k) const { return (bool(bst_search(root, k))); }

		bool empty() const { return _size == 0; }

		iterator end()
		{
			bst_node *right = root->right;
			if (!right)
				return root;
			while (right->right)
				right = right->right;
			return iterator(right + 4);
		}

		void erase(iterator position)
		{
			bool deleted = true;
			root = bst_erease(root, position->first, deleted);
			_size -= deleted;
		}

		size_type erase(const key_type &k)
		{
			bool deleted = true;
			root = bst_erease(root, k, deleted);
			_size -= deleted;
			return deleted;
		}

		void erase(iterator first, iterator last)
		{
			bool deleted;
			(void)last;
			iterator tmp;
			for(; first != last;)
			{
				tmp = ++first;
				deleted = true;
				root = bst_erease(root, tmp->first, deleted);
				_size -= deleted;
			}
		}

		// return iterator to the element, if an element with specified key is found, or map::end otherwise.
		iterator find (const key_type& k)
		{
			bst_node *node = bst_search(root, k);
			if (node)
				return iterator(node);
			else
				return(map::end());
		}

		// return The allocator.
		// allocator_type get_allocator() const { return }
		std::pair<iterator, bool> insert(const value_type &val)
		{
			std::pair<iterator, bool> p;
			bool inserted = true;
			root = bst_insert(root, val, inserted);
			_size += inserted;
			return p;
		}

		iterator lower_bound (const key_type& k)
		{
			bst_node *node = bst_nearest(root, k);
			iterator it =  iterator(node);
			if (cmp(it->first, k))
				it++;
			return it;
		}

		iterator upper_bound (const key_type& k)
		{
			bst_node *node = bst_nearest(root, k);
			iterator it =  iterator(node);
			if (it->first == k ||  cmp(it->first, k))
				it++;
			return it;

		}
		size_type size() const { return _size; }
	};
}

#ifndef NAMESPACE
#define NAMESPACE std
#endif

int main()
{

	NAMESPACE::map<std::string, int> m;

	m.insert(std::pair<std::string, int>("issam0", 28));
	m.insert(std::pair<std::string, int>("issam1", 28));
	m.insert(std::pair<std::string, int>("issam2", 28));
	m.insert(std::pair<std::string, int>("issam3", 28));
	m.insert(std::pair<std::string, int>("yahya", 24));
	m.insert(std::pair<std::string, int>("md", 23));
	m.insert(std::pair<std::string, int>("ichoukri1", 20));
	m.insert(std::pair<std::string, int>("ichoukri2", 40));

	NAMESPACE::map<std::string, int >::iterator it = m.upper_bound("issam01");
	if (it != m.end())
		std::cout << it->first << ", " << it->second << std::endl;
	// NAMESPACE::map<std::string, int >::iterator b = m.begin();
	// NAMESPACE::map<std::string, int >::iterator it, it1, it2;
	// // NAMESPACE::map<std::string, int >::iterator e = m.end();


	// it1 = ++b;
	// it2 = ++it1;
	// ++it2;
	// ++it2;
	// m.erase(it1, it2);
	// int count = 0;
	// for(it = m.begin() ; it != m.end() && count++ < 30; it++ )
	// {
	// 	std::cout << it->first << ", " << it->second << std::endl;
	// }


	// std::cout << "----------------------------" << std::endl;
	// bst<std::pair<std::string, int>, std::less<std::string> > *root = NULL;
	// bool b;

	// root = bst_insert(root, std::pair<std::string, int>("issam0", 28), b);
	// root = bst_insert(root, std::pair<std::string, int>("issam1", 28), b);
	// root = bst_insert(root, std::pair<std::string, int>("issam2", 28), b);
	// root = bst_insert(root, std::pair<std::string, int>("issam3", 28), b);
	// root = bst_insert(root, std::pair<std::string, int>("yahya", 24), b);
	// root = bst_insert(root, std::pair<std::string, int>("md", 23), b);
	// root = bst_insert(root, std::pair<std::string, int>("ichoukri1", 20), b);
	// root = bst_insert(root, std::pair<std::string, int>("ichoukri2", 40), b);

	// root = bst_erease(root, "issam2", b);
	// root = bst_erease(root, "md", b);
	// inorder(root);
	// bst<std::pair<int, int> , std::greater<int> > *tmp = bst_search(root, 2);

	// std::cout << tmp->key.first << ". " << tmp->key.second << std::endl;
	// if (tmp->parent)
	// {
	// 	tmp = tmp->parent;
	// }
	// std::cout << tmp->key.first << ". " << tmp->key.second << std::endl;

	// inorder(root);
}

//////////////////////////////// bugs ////////////////////////////////
// cmp in bst needs to be static
// map::end() return false value
// *it = v (op overload missing)
// bst_erase is broken