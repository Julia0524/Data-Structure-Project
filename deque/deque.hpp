#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

namespace sjtu {

template<class T>
class deque {
public:
    struct node
    {
        T *data;
        node *next;
        node *prev;
        node(T *d = NULL, node* n = NULL, node* p = NULL) :next(n), prev(p)
        {
            if(d != NULL){
                data = new T(*d);
            }
            else{
                data = d;
            }
        }
        node(const node &other){data = other.data; next = other.next; prev = other.prev;}
        ~node() {if(data!=NULL) delete data;}
    };
	class const_iterator;
	class iterator {
	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		node* current;
        node* first;
	public:
		iterator(node *c = NULL,node *f = NULL)
		{
			current = c;
			first = f;
		}
		iterator(const iterator &other)
		{
		    current = other.current;
            first = other.first;

		}
		iterator(const const_iterator &other)
		{
		    current = other.current;
            first = other.first;

		}
		~iterator(){}
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, the behaviour is **undefined**.
		 * as well as operator-
		 */
		iterator operator+(const int &n) const
		{
			//TODO
			iterator tmp = *this;
			if(n<0){
               for (int i = 0; i < -n; ++i) {
				   tmp.current = (tmp.current)->prev;
			   }
			}
			else{
               for (int i = 0; i < n; ++i) {
				   tmp.current = (tmp.current)->next;
			   }
			}

			return tmp;
		}
		iterator operator-(const int &n) const
		{
			//TODO
			iterator tmp = *this;
			if(n<0){
               for (int i = 0; i < -n; ++i) {
				   tmp.current = (tmp.current)->next;
			   }
			}
			else{
               for (int i = 0; i < n; ++i) {
				   tmp.current = (tmp.current)->prev;
			   }
			}
			return tmp;

		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const
		{
			//TODO
			if(first != rhs.first){
                throw invalid_iterator();
			}
            int i = 0;
			iterator tmp = *this;
			while (tmp.current != tmp.first) {
				if (tmp == rhs) {
					return i;
				}
				tmp.current = tmp.current->prev;
				++i;
			}
			i=0;
			tmp = *this;
			while (tmp.current != NULL) {
				if (tmp == rhs) {
					return -i;
				}
				tmp.current = tmp.current->next;
				++i;
			}
		}
		iterator operator+=(const int &n)
		{
			//TODO
			if(n<0){
                for (int i = 0; i < -n; ++i) {
				    current = current->prev;
			    }
			}
			else{
                for (int i = 0; i < n; ++i) {
				    current = current->next;
			    }
			}

			return *this;
		}
		iterator operator-=(const int &n)
		{
			//TODO
			if(n<0){
                for (int i = 0; i < -n; ++i) {
				    current = current->next;
			    }
			}
			else{
                for (int i = 0; i < n; ++i) {
				    current = current->prev;
			    }
			}
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int)
		{
			if(this->current->next == NULL){
                throw invalid_iterator();
			}
			iterator tmp = *this;
			current = current->next;
			return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++()
		{
			if(this->current->next == NULL){
                throw invalid_iterator();
			}
			current = current->next;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int)
		{
			if(current == first->next){
                throw invalid_iterator();
			}
			iterator tmp = *this;
			current = current->prev;
			return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--()
		{
			if(current == first->next){
                throw invalid_iterator();
			}
			current = current->prev;
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const
		{
		    if(current->next == NULL){
                throw invalid_iterator();
		    }
			return *(current->data);
		}
		/**
		 * TODO it->field
		 */
		T* operator->() const noexcept
		{
		    if(current->next == NULL){
                throw invalid_iterator();
		    }
		    return current->data;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const
		{
			return (current == rhs.current)&&(first == rhs.first);
		}
		bool operator==(const const_iterator &rhs) const
		{
			return (current == rhs.current)&&(first == rhs.first);
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
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		public:
			// data members.
			node* current;
			node* first;
		public:
			const_iterator()
			{
				// TODO
				current = NULL;
				first = NULL;
			}
			const_iterator(const const_iterator &other)
			{
				// TODO
				current = other.current;
				first = other.first;
			}
			const_iterator(const iterator &other)
			{
				// TODO
				current = other.current;
				first = other.first;
			}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
			const_iterator operator+(const int &n) const
		    {
			//TODO
			    const_iterator tmp = *this;
			    if(n<0){
                   for (int i = 0; i < -n; ++i) {
				       tmp.current = (tmp.current)->prev;
			       }
			    }
			    else{
                   for (int i = 0; i < n; ++i) {
				       tmp.current = (tmp.current)->next;
			       }
			    }

			    return tmp;
		    }
		    const_iterator operator-(const int &n) const
		    {
			//TODO
                const_iterator tmp = *this;
                if(n<0){
                   for (int i = 0; i < -n; ++i) {
				       tmp.current = (tmp.current)->next;
			       }
                }
                else{
                   for (int i = 0; i < n; ++i) {
				       tmp.current = (tmp.current)->prev;
			       }
                }
                return tmp;

            }
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		    int operator-(const const_iterator &rhs) const
		    {
			//TODO
                if(first != rhs.first){
                   throw invalid_iterator();
                }
                const_iterator tmp = *this;
                int i = 0;
                while (tmp.current != tmp.first) {
				    if (tmp == rhs) {
					    return i;
				    }
				    tmp.current = tmp.current->prev;
				    ++i;
                }
                i=0;
			    tmp = *this;
			    while (tmp.current != NULL) {
				    if (tmp == rhs) {
					    return -i;
				    }
				    tmp.current = tmp.current->next;
				    ++i;
			    }
            }
		    const_iterator operator+=(const int &n)
		    {
			//TODO
			    if(n<0){
                    for (int i = 0; i < -n; ++i) {
				        current = current->prev;
			        }
			    }
			    else{
                    for (int i = 0; i < n; ++i) {
				        current = current->next;
			        }
			    }

			    return *this;
		    }
		    const_iterator operator-=(const int &n)
		    {
			//TODO
			    if(n<0){
                    for (int i = 0; i < -n; ++i) {
				        current = current->next;
			        }
			    }
			    else{
                    for (int i = 0; i < n; ++i) {
				        current = current->prev;
			        }
			    }
			    return *this;
		    }
		/**
		 * TODO iter++
		 */
		    const_iterator operator++(int)
		    {
			    if(this->current->next == NULL){
                    throw invalid_iterator();
			    }
			    const_iterator tmp = *this;
			    current = current->next;
			    return tmp;
		    }
		/**
		 * TODO ++iter
		 */
		    const_iterator& operator++()
		    {
			    if(this->current->next == NULL){
                    throw invalid_iterator();
			    }
			    current = current->next;
			    return *this;
		    }
		/**
		 * TODO iter--
		 */
		    const_iterator operator--(int)
		    {
			    if(this->current == first->next){
                    throw invalid_iterator();
			    }
			    const_iterator tmp = *this;
			    current = current->prev;
			    return tmp;
		    }
		/**
		 * TODO --iter
		 */
		    const_iterator& operator--()
		    {
			    if(this->current == first->next){
                    throw invalid_iterator();
			    }
			    current = current->prev;
			    return *this;
		    }
		/**
		 * TODO *it
		 */
		    T& operator*() const
		    {
			    return *(current->data);
		    }
		/**
		 * TODO it->field
		 */
		    T* operator->() const noexcept
		    {
		        return current->data;
		    }
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		    bool operator==(const iterator &rhs) const
		    {
			    return (current == rhs.current)&&(first == rhs.first);
		    }
		    bool operator==(const const_iterator &rhs) const
		    {
			    return (current == rhs.current)&&(first == rhs.first);
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
	    };
private:
    node *head, *tail;
    int currentSize;
	/**
	 * TODO Constructors
	 */
public:
	deque()
	{
	    head = new node;
        tail = new node;
        head->next = tail;
        tail->prev = head;
        currentSize = 0;
	}
	deque(const deque &other)
	{
	    head = new node;
        tail = new node;
        head->next = tail;
        tail->prev = head;
        currentSize = other.currentSize;
        node* obj = other.head;
        node* p = head;

        for(int i=0;i<currentSize;++i){
            obj = obj->next;
            T a(*(obj->data));
            node* tmp = new node(&a,tail,p);
            p->next = tmp;
            tail->prev = tmp;
            p = p->next;
        }
	}
	/**
	 * TODO Deconstructor
	 */
	~deque()
	{
	    clear();
        delete head;
        delete tail;
	}
	/**
	 * TODO assignment operator
	 */
	deque &operator=(const deque &other)
	{
	    if(this == &other){
            return *this;
	    }
	    this->clear();
        currentSize = other.currentSize;
        node* obj = other.head;
        node* p = head;

        for(int i=0;i<currentSize;++i){
            obj = obj->next;
            T a(*(obj->data));
            node* tmp = new node(&a,tail,p);
            p->next = tmp;
            tail->prev = tmp;
            p = p->next;
        }

        return *this;
	}
	/**
	 * access specified element with bounds checking
	 * throw index_out_of_bound if out of bound.
	 */
	T & at(const size_t &pos)
	{
	    node* tmp = head->next;
	    if(pos >= currentSize || pos < 0){
            throw index_out_of_bound();
	    }
	    else{

	        for(int i=0;i<pos;++i){
                tmp = tmp->next;
	        }
	        return *(tmp->data);
	    }
	}
	const T & at(const size_t &pos) const
	{
	    if(pos >= currentSize || pos < 0){
            throw index_out_of_bound();
	    }
	    else{
            node* tmp = head->next;
	        for(int i=0;i<pos;++i){
                tmp = tmp->next;
	        }
	        return *(tmp->data);
	    }
	}
	T & operator[](const size_t &pos)
	{
	    if(pos >= currentSize || pos < 0){
            throw index_out_of_bound();
	    }
	    else{
            node* tmp = head->next;
	        for(int i=0;i<pos;++i){
                tmp = tmp->next;
	        }
	        return *(tmp->data);
	    }
	}
	const T & operator[](const size_t &pos) const
	{
	    if(pos >= currentSize || pos < 0){
            throw index_out_of_bound();
	    }
	    else{
            node* tmp = head->next;
	        for(int i=0;i<pos;++i){
                tmp = tmp->next;
	        }
	        return *(tmp->data);
	    }
	}
	/**
	 * access the first element
	 * throw container_is_empty when the container is empty.
	 */
	const T & front() const
	{
	    if(empty()){
            throw container_is_empty();
	    }
	    else{
            return *(head->next->data);
	    }
	}
	/**
	 * access the last element
	 * throw container_is_empty when the container is empty.
	 */
	const T & back() const
	{
	    if(empty()){
            throw container_is_empty();
	    }
	    else{
            return *(tail->prev->data);
	    }
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin()
	{
	    iterator res(head->next,head);
	    return res;
	}
	const_iterator cbegin() const
	{
	    const_iterator res;
	    res.current = head->next;
	    res.first = head;
	    return res;
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end()
	{
	    iterator res(tail,head);
	    return res;

	}
	const_iterator cend() const
	{
	    const_iterator res;
	    res.current = tail;
	    res.first = head;
	    return res;
	}
	/**
	 * checks whether the container is empty.
	 */
	bool empty() const
	{
	    return (currentSize == 0);
	}
	/**
	 * returns the number of elements
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
	    node *p = head->next, *q;
        head->next = tail;
        tail->prev = head;
        while(p != tail){
            q = p->next;
            delete p;
            p = q;
        }
        currentSize = 0;

	}
	/**
	 * inserts elements at the specified locat on in the container.
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value
	 *     throw if the iterator is invalid or it point to a wrong place.
	 */
	iterator insert(iterator pos, const T &value)
	{
	    int len;
	    if(pos-begin() >= 0 && pos-begin() <= currentSize+1){
            len = pos-begin();
	    }
	    else{
            throw invalid_iterator();
	    }

        ++currentSize;

        node* p = head->next;
        for(int i=0;i<len;++i){
            p = p->next;
        }

	    T a(value);
	    node* tmp = new node(&a, p, p->prev);
	    p->prev->next = tmp;
	    p->prev = tmp;
	    return iterator(begin()+len);
	}
	/**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos)
	{
	    if(empty()){
            throw container_is_empty();
	    }
	    int len;
	    if(pos-begin() >= 0 && pos-begin() < currentSize){
            len = pos-begin();
	    }
	    else{
            throw invalid_iterator();
	    }

        --currentSize;

        node* p = head->next;
        for(int i=0;i<len;++i){
            p = p->next;
        }

	    p->next->prev = p->prev;
	    p->prev->next = p->next;
	    delete p;

	    return iterator(begin()+len);
	}
	/**
	 * adds an element to the end
	 */
	void push_back(const T &value)
	{
	    T a(value);
	    node* p = new node(&a,tail,tail->prev);
	    tail->prev->next = p;
	    tail->prev = p;
	    currentSize++;
	}
	/**
	 * removes the last element
	 *     throw when the container is empty.
	 */
	void pop_back()
	{
	    if(empty()){
            throw container_is_empty();
	    }
        node* tmp = tail->prev;
        tmp->prev->next = tail;
        tail->prev = tmp->prev;
        currentSize--;
        delete tmp;
	}
	/**
	 * inserts an element to the beginning.
	 */
	void push_front(const T &value)
	{
	    T a(value);
	    node* p = new node(&a,head->next,head);
	    head->next->prev = p;
	    head->next = p;
	    currentSize++;
	}
	/**
	 * removes the first element.
	 *     throw when the container is empty.
	 */
	void pop_front()
	{
	    if(empty()){
            throw container_is_empty();
	    }
        node* tmp = head->next;
        tmp->next->prev = head;
        head->next = tmp->next;
        currentSize--;
        delete tmp;
	}
};

}

#endif
