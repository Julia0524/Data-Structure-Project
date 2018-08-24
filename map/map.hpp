/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
	/**
	 * the internal type of data.
	 * it should have a default constructor, a copy constructor.
	 * You can use sjtu::map as value_type by typedef.
	 */
	typedef pair<const Key, T> value_type;
	struct node
	{
	    value_type *data;
	    node *left;
        node *right;
        int height;
        node(value_type *d = NULL, node* l = NULL, node* r = NULL, int h=0) :data(d), left(l), right(r), height(h){}
        ~node() {}
	};
	/**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong throw invalid_iterator.
	 *     like it = map.begin(); --it;
	 *       or it = map.end(); ++end();
	 */
	class const_iterator;
	class iterator {
	    friend class map;
	public:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		 node* current;
		 const map* mp;
	public:
		iterator(node* c= NULL,const map* m=NULL)
		{
			// TODO
			current = c;
			mp = m;
		}
		iterator(const iterator &other)
		{
			// TODO
			current = other.current;
			mp = other.mp;
		}
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, just return the answer.
		 * as well as operator-
		 */
		/**
		 * TODO iter++
		 */
		iterator operator++(int)
		{
		    iterator res(current,mp);
		    if(current == NULL) {
                throw invalid_iterator();
            }
            else if(current == mp->maxNode()){
                current = NULL;
                return res;
            }
            else if(current->right != NULL){
               node* tmp = current->right;
               while(tmp->left != NULL)  {
                    tmp = tmp->left;
               }
               current = tmp;
               return res;
            }
            else if(current->right == NULL){
                Compare cmp;
                node* tmp;
                node* t = mp->root;
                while(t!= NULL && (cmp(current->data->first,t->data->first)||cmp(t->data->first,current->data->first))){
                    if(cmp(current->data->first,t->data->first)){
                        tmp = t;
                        t = t->left;
                    }
                    else if(cmp(t->data->first,current->data->first)){
                        t = t->right;
                    }
                }
                if(t == NULL || t!= current){
                    throw invalid_iterator();
                }
                current = tmp;
                return res;
            }
		}
		/**
		 * TODO ++iter
		 */
		iterator & operator++()
		{
            if(current == NULL) {
                throw invalid_iterator();
            }
            else if(current == mp->maxNode()){
                current = NULL;
                return *this;
            }
            if(current->right != NULL){
               node* tmp = current->right;
               while(tmp->left != NULL)  {
                    tmp = tmp->left;
               }
               current = tmp;
            }
            else {
                Compare cmp;
                node* tmp;
                node* t = mp->root;
                while(t!= NULL && (cmp(current->data->first,t->data->first)||cmp(t->data->first,current->data->first))){
                    if(cmp(current->data->first,t->data->first)){
                        tmp = t;
                        t = t->left;
                    }
                    else if(cmp(t->data->first,current->data->first)){
                        t = t->right;
                    }
                }
                if(t == NULL || t!= current){
                    throw invalid_iterator();
                }
                current = tmp;
            }
		    return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int)
		{
		    iterator res = *this;
		    if(current == mp->minNode()){
                throw invalid_iterator();
		    }
		    if(current == NULL) {
                current = mp->maxNode();
                return res;
            }
		    else if(current->left != NULL) {
                node* tmp = current->left;
                while(tmp->right != NULL)  {
                    tmp = tmp->right;
                }
                current = tmp;
            }
            else {
                Compare cmp;
                node* tmp;
                node* t = mp->root;
                while(t!= NULL && (cmp(current->data->first,t->data->first)||cmp(t->data->first,current->data->first))){
                    if(cmp(current->data->first,t->data->first)){
                        t = t->left;
                    }
                    else if(cmp(t->data->first,current->data->first)){
                        tmp = t;
                        t = t->right;
                    }
                }
                if(t == NULL || t!= current){
                    throw invalid_iterator();
                }
                current = tmp;
            }
            return res;
		}
		/**
		 * TODO --iter
		 */
		iterator & operator--()
		{
		    if(current == mp->minNode()){
                throw invalid_iterator();
		    }
		    if(current == NULL) {
                current = mp->maxNode();
                return *this;
            }
		    else if(current->left != NULL) {
                node* tmp = current->left;
                while(tmp->right != NULL)  {
                    tmp = tmp->right;
                }
                current = tmp;
            }
            else {
                Compare cmp;
                node* tmp;
                node* t = mp->root;
                while(t!= NULL && (cmp(current->data->first,t->data->first)||cmp(t->data->first,current->data->first))){
                    if(cmp(current->data->first,t->data->first)){
                        t = t->left;
                    }
                    else if(cmp(t->data->first,current->data->first)){
                        tmp = t;
                        t = t->right;
                    }
                }
                if(t == NULL || t!= current){
                    throw invalid_iterator();
                }
                current = tmp;
            }
            return *this;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		value_type & operator*() const
		{
		    return *(current->data);
		}
		bool operator==(const iterator &rhs) const
		{
		    return (current == rhs.current) && (mp == rhs.mp);
		}
		bool operator==(const const_iterator &rhs) const
		{
            return (current == rhs.current) && (mp == rhs.mp);
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const
		{
		    return !(*this == rhs);
		}
		bool operator!=(const const_iterator &rhs) const
		{
            return !(*this == rhs);
		}

		/**
		 * for the support of it->first.
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept
		{
		    return current->data;
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		public:
			// data members.
			node* current;
			const map* mp;
		public:
			const_iterator(node* c = NULL,const map* m = NULL)
			{
				// TODO
				current = c;
				mp = m;;

			}
			const_iterator(const const_iterator &other)
			{
				// TODO
				current = other.current;
				mp = other.mp;
			}
			const_iterator(const iterator &other)
			{
				// TODO
				current = other.current;
				mp = other.mp;
			}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
			const_iterator operator++(int)
		    {
		        const_iterator res = *this;
		        if(current == NULL) {
                    throw invalid_iterator();
                }
                else if(current == mp->maxNode()){
                    current = NULL;
                    return res;
                }
                if(current->right != NULL){
                   node* tmp = current->right;
                   while(tmp->left != NULL)  {
                        tmp = tmp->left;
                   }
                   current = tmp;
                }
                else {

                    Compare cmp;
                    node* tmp;
                    node* t = mp->root;
                    while(t!= NULL && (cmp(current->data->first,t->data->first)||cmp(t->data->first,current->data->first))){
                        if(cmp(current->data->first,t->data->first)){
                            tmp = t;
                            t = t->left;
                        }
                        else if(cmp(t->data->first,current->data->first)){
                            t = t->right;
                        }
                    }
                    if(t == NULL || t!= current){
                        throw invalid_iterator();
                    }
                    current = tmp;
                }
                return res;
		    }
		/**
		 * TODO ++iter
		 */
		    const_iterator & operator++()
		    {
		        if(current == NULL) {
                    throw invalid_iterator();
                }
                else if(current == mp->maxNode()){
                    current = NULL;
                    return *this;
                }
                if(current->right != NULL){
                   node* tmp = current->right;
                   while(tmp->left != NULL)  {
                        tmp = tmp->left;
                   }
                   current = tmp;
                   return *this;
                }
                else {
                    Compare cmp;
                    node* tmp;
                    node* t = mp->root;
                    while(t!= NULL && (cmp(current->data->first,t->data->first)||cmp(t->data->first,current->data->first))){
                        if(cmp(current->data->first,t->data->first)){
                            tmp = t;
                            t = t->left;
                        }
                        else if(cmp(t->data->first,current->data->first)){
                            t = t->right;
                        }
                    }
                    if(t == NULL || t!= current){
                        throw invalid_iterator();
                    }
                    current = tmp;
                    return *this;
                }
		    }
		    /**
		 * TODO iter--
		 */
		    const_iterator operator--(int)
		    {
                const_iterator res = *this;
		        if(current == mp->minNode()){
                    throw invalid_iterator();
		        }
		        if(current == NULL) {
                    current = mp->maxNode();
                    return res;
                }
		        else if(current->left != NULL) {
                    node* tmp = current->left;
                    while(tmp->right != NULL)  {
                        tmp = tmp->right;
                    }
                    current = tmp;
                }
                else {
                    Compare cmp;
                    node* tmp;
                    node* t = mp->root;
                    while(t!= NULL && (cmp(current->data->first,t->data->first)||cmp(t->data->first,current->data->first))){
                        if(cmp(current->data->first,t->data->first)){
                            t = t->left;
                        }
                        else if(cmp(t->data->first,current->data->first)){
                            tmp = t;
                            t = t->right;
                        }
                    }
                    if(t == NULL || t!= current){
                        throw invalid_iterator();
                    }
                    current = tmp;
                }
                return res;
		    }
		/**
		 * TODO --iter
		 */
		    const_iterator & operator--()
		    {
		        if(current == mp->minNode()){
                    throw invalid_iterator();
		        }
		        if(current == NULL) {
                    current = mp->maxNode();
                    return *this;
                }
		        else if(current->left != NULL) {
                    node* tmp = current->left;
                    while(tmp->right != NULL)  {
                        tmp = tmp->right;
                    }
                    current = tmp;
                }
                else {
                    Compare cmp;
                    node* tmp;
                    node* t = mp->root;
                    while(t!= NULL && (cmp(current->data->first,t->data->first)||cmp(t->data->first,current->data->first))){
                        if(cmp(current->data->first,t->data->first)){
                            t = t->left;
                        }
                        else if(cmp(t->data->first,current->data->first)){
                            tmp = t;
                            t = t->right;
                        }
                    }
                    if(t == NULL || t!= current){
                        throw invalid_iterator();
                    }
                    current = tmp;
                }
                return *this;
		    }
			value_type & operator*() const
		    {
		        return *(current->data);
		    }
		    bool operator==(const iterator &rhs) const
		    {
		        return (current == rhs.current) && (mp == rhs.mp);
		    }
		    bool operator==(const const_iterator &rhs) const
		    {
                return (current == rhs.current) && (mp == rhs.mp);
		    }
		/**
		 * some other operator for iterator.
		 */
		    bool operator!=(const iterator &rhs) const
		    {
		        return !(*this == rhs);
		    }
		    bool operator!=(const const_iterator &rhs) const
		    {
                return !(*this == rhs);
		    }
		/**
		 * for the support of it->first.
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		    value_type* operator->() const noexcept
		    {
		        return current->data;
		    }

	};
private:
    node* root;
    int currentSize;
public:
	/**
	 * TODO two constructors
	 */
	map()
	{
	    root = NULL;
	    currentSize = 0;
	}
	map(const map &other)
	{
	    root = NULL;
	    currentSize = other.currentSize;
	    clone(root,other.root);
	}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other)
	{
	    if(this == &other){
            return *this;
	    }
	    if(root != NULL){
            clear();
	    }
        currentSize = other.currentSize;
        clone(root,other.root);
        return *this;
	}
	/**
	 * TODO Destructors
	 */
	~map()
	{
	    clear();
	}
	/**
	 * TODO
	 * access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
	T & at(const Key &key)
	{
	    node* tmp = find(root,key);
	    if(tmp==NULL){
            throw index_out_of_bound();
	    }
	    return tmp->data->second;
	}
	const T & at(const Key &key) const
	{
	    node* tmp = find(root,key);
	    if(tmp==NULL){
            throw index_out_of_bound();
	    }
	    return tmp->data->second;
	}
	/**
	 * TODO
	 * access specified element
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key)
	{
	    node* tmp = find(root,key);
	    if(tmp==NULL){
            T b;
            value_type a(key,b);
            tmp = insert(root,a);
            ++currentSize;
            return tmp->data->second;
	    }
	    else{
            return tmp->data->second;
	    }

	}
	/**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
	const T & operator[](const Key &key) const
	{
	    node* tmp = find(root,key);
	    if(tmp==NULL){
            throw index_out_of_bound();
	    }
	    return tmp->data->second;
	}
	/**
	 * return a iterator to the beginning
	 */
	iterator begin()
	{
	    if(root==NULL){
            return iterator(root,this);
	    }
	    else{
            node* tmp = root;
            while(tmp->left != NULL){
                tmp = tmp->left;
            }
            return iterator(tmp,this);
	    }
	}
	const_iterator cbegin() const
	{
	    if(root==NULL){
            return const_iterator(root,this);
	    }
	    else{
            node* tmp = root;
            while(tmp->left){
                tmp = tmp->left;
            }
            return const_iterator(tmp,this);
	    }
	}
	/**
	 * return a iterator to the end
	 * in fact, it returns past-the-end.
	 */
	iterator end()
	{
	    return iterator(NULL,this);
	}
	const_iterator cend() const
	{
	    return const_iterator(NULL,this);
	}
	/**
	 * checks whether the container is empty
	 * return true if empty, otherwise false.
	 */
	bool empty() const
	{
	    return currentSize == 0;
	}
	/**
	 * returns the number of elements.
	 */
	size_t size() const
	{
	    return currentSize;
	}
	/**
	 * clears the contents
	 */
	void clear()
	{
	    currentSize = 0;
	    clear(root);
	}
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion),
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(const value_type &value)
	{
        node *p = find(root,value.first);
        if(p == NULL){
            p = insert(root,value);
            ++currentSize;
            return pair<iterator,bool>(iterator(p,this),true);
        }
        else if(p!= NULL){
            return pair<iterator,bool>(iterator(p,this),false);
        }
	}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos)
	{
	    node *t = pos.current;
        if(t == NULL || pos.mp!= this) {
            throw invalid_iterator();
        }
        erase(root,*(t->data));
        --currentSize;
	}
	/**
	 * Returns the number of elements with key
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const
	{
	    if(find(root,key)==NULL){
            return 0;
	    }
	    return 1;

	}
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	iterator find(const Key &key)
	{
	    if(root == NULL){
            return iterator(NULL,this);
	    }
	    return iterator(find(root,key),this);
	}
	const_iterator find(const Key &key) const
	{
	    if(root == NULL){
            return const_iterator(NULL,this);
	    }
	    return const_iterator(find(root,key),this);
	}
private:
    int max(int a,int b)
    {
        return (a>b)?a:b;
    }

    node* maxNode() const
    {
        node* t = root;
	    if (t != NULL)
	    {
		    while (t->right != NULL){
                t = t->right;
		    }
		    return t;
	    }
	    return t;
    }

    node* minNode() const
    {
        node* t = root;
	    if (t != NULL)
	    {
		    while (t->left != NULL){
                t = t->left;
		    }
		    return t;
	    }
	    return t;
    }

    int height(node* t)
    {
	    if (t != NULL){
            return t->height;
	    }
	    return -1;
    }

    void clone(node *&root, const node* r)
    {
        if(r == NULL){
            root = NULL;
            return ;
        }
        else{
            root = new node();
            root -> data = new value_type(*(r->data));
            root ->left = NULL; root ->right = NULL;
            clone(root ->left, r->left);
            clone(root ->right, r->right);
        }
    }

    void clear(node *&t)
    {
        if(t == NULL){
            return;
        }
        clear(t->left);
        clear(t->right);
        delete t->data;
        delete t;
        t = NULL;
    }

    void LL(node *&t)
    {
        node *tmp = t->left;
        t->left = tmp->right;
        tmp->right = t;
        t->height = max(height(t->left),height(t->right))+1;
        tmp->height = max(height(tmp->left),height(tmp->right))+1;
        t = tmp;
    }

    void RR(node *&t)
    {
        node *tmp = t->right;
        t->right = tmp->left;
        tmp->left = t;
        t->height = max(height(t->left),height(t->right))+1;
        tmp->height = max(height(tmp->left),height(tmp->right))+1;
        t = tmp;
   }

    void LR(node *&t)
    {
        RR(t->left);
        LL(t);
    }

    void RL(node *&t)
    {
        LL(t->right);
        RR(t);
    }

    node* insert(node *&t,const value_type &value)
    {
        Compare cmp;
        node* res;
	    if (t == NULL){
	        t = new node;
            t->data = new value_type(value.first,value.second);
		    return t;
	    }
	    else if (cmp(t->data->first,value.first)){
		    res = insert(t->right, value);
		    if (height(t->right) - height(t->left) == 2){
			    if (cmp(t->right->data->first,value.first)){
				    RR(t);
				}
			    else if (cmp(value.first,t->right->data->first)) {
				    RL(t);
				}
		    }
	    }
	    else if (cmp(value.first,t->data->first)){
		    res = insert(t->left, value);
		    if (height(t->left) - height(t->right) == 2){
			    if (cmp(value.first,t->left->data->first)){
                    LL(t);
			    }
			    else if (cmp(t->left->data->first,value.first)){
                    LR(t);
			    }
		    }
	    }
	    else{
            return t;
	    }
	    t->height = max(height(t->left), height(t->right)) + 1;
	    return res;
    }

    void erase(node *&t,value_type value)
    {
        Compare cmp;
        if(t == NULL){
            return;
        }
        if (!cmp(t->data->first,value.first) && !cmp(value.first,t->data->first)){
            if (t->left != NULL && t->right != NULL){
                node *tmp = t->right, *cur = t;
                if(tmp->left == NULL){
                    t = tmp;
                    t -> left = cur -> left;
                    cur ->right = t -> right;
                    t -> right = cur;
                    t ->height = cur -> height;
                    cur ->left = NULL;
                }
                else{
                    while(tmp-> left -> left != NULL){
                        tmp = tmp -> left;
                    }
                    node *p = tmp;
                    tmp = tmp -> left;
                    p->left = cur;
                    t = tmp;
                    p = cur -> right;
                    cur -> right = t -> right;
                    t -> left = cur -> left;
                    t -> right = p;
                    t -> height = cur -> height;
                    cur -> left = NULL;
                }
                erase(t->right,value);
                if(height(t->left)-height(t->right) == 2){
                    if(t->left->right!= NULL && height(t->left->right)>height(t->left->left)){
                        LR(t);
                    }
                    else {
                        LL(t);
                    }
                }
            }
            else{
                node* tmp = t;
                if (t->left != NULL){
                    t = t->left;
                }
                else {
                    t = t->right;
                }
                delete tmp->data;
                delete tmp;
                return ;
            }

        }
        else if (cmp(t->data->first,value.first)){
            erase(t->right,value);
            if (height(t->left) - height(t->right) == 2){
                if (height(t->left->right)>height(t->left->left) && t->left->right != NULL){
                    LR(t);
                }
                else{
                    LL(t);
                }
            }
        }
        else if (cmp(value.first,t->data->first))	{
            erase(t->left, value);
            if (height(t->right) - height(t->left) == 2){
                if (height(t->right->left)>height(t->right->right) && t->right->left != NULL){
                    RL(t);
                }
                else{
                    RR(t);
                }
            }
        }
        if(t == NULL) {
            return;
        }
        t->height = max(height(t->left),height(t->right))+1;
    }

    node* find(node* t,const Key &key) const
    {
        Compare cmp;
	    if (t != NULL){
		    if (cmp(key,t->data->first)){
                return find(t->left,key);
		    }
		    if (cmp(t->data->first,key)){
                return find(t->right,key);
		    }
		    else{
                return t;
		    }

	    }
	    return NULL;
    }

};

}

#endif
