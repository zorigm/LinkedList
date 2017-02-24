#ifndef MAGNAITUVSHIN_Z_LIST
#define MAGNAITUVSHIN_Z_LIST
typedef unsigned int uint;

#include <cassert>
#include <sstream>

using namespace std;

/**
 * a simplified generic singly linked list class to illustrate C++ concepts
 * @author Zorig Magnaituvshin
 * @version 6 February 2017
 */
template< typename Object >
class List
{
 private:
  /**
   * A class to store data and provide a link to the next node in the list
   */
  class Node
  {
   public:
     /**
      * The constructor
      * @param data the data to be stored in this node
      */
      explicit Node( const Object & data )
        : data{ data }, next{ nullptr } {}

    Object data;
    Node * next;
  };

 public:
  /**
   * The constructor for an empty list
   */
  List()
    : size{ 0 }, first{ nullptr }, last{ nullptr }{}


  /**
  * Copy Constructor for a list. Takes in the old list and iterates
  * through to copy into new list.
  * @param rhs the list to be copied.
  */
  List( const List & rhs )
  {
    last = NULL;
    size = 0;
      if(rhs.size == 0)
      {
        first = NULL;
      }
      else
      {
        push_front(rhs.front());
        Node * old_list_itr = rhs.first -> next;
        last = first;
        while(old_list_itr != NULL)
        {
          Node * new_node = new Node( old_list_itr->data );
          last -> next = new_node;
          last = new_node;
          old_list_itr = old_list_itr->next;
          size++;
        }
      }
  };


   /**
   * disallow the rvalue copy constructor
   */
   List( const List && rhs ) = delete;

  /**
   * the operator= method
   * @param rhs the list to be copied.
   */
  List & operator=( const List & rhs )
  {
    Node * current = first;
    Node * temp;
    while(current != NULL)
    {
      temp = current;
      current = current->next;
      delete temp;
    }

    first = last = NULL;

    push_front(rhs.front());
    last = first;

    Node * iterator2 = rhs.first -> next;

    while(iterator2 != NULL)
    {
      Node * new_node1 = new Node(iterator2 -> data);
      last -> next = new_node1;
      last = new_node1;
      iterator2 = iterator2->next;
      size++;
    }
    return *this;

  }

  /**
   * disallow the rvalue operator=
   */
  List & operator=( const List && rhs ) = delete;

  /**
   * The destructor that gets rid of everything that's in the list and
   * resets it to empty. If the list is already empty, do nothing.
   *
   * Next time: use a for loop, as we know how big the list is
   * 
   */
  ~List()
  {
    if( size != 0 )
    {
      Node * current = first;
      Node * temp;

      while( current != nullptr )
      {
        temp = current;
        current = current->next;
        delete temp;
      }
    }
  }

  /**
   * Put a new element onto the beginning of the list
   * @param item the data the new element will contain
   */
  void push_front( const Object& item )
  {
    Node * new_node = new Node( item );

    if (is_empty())
    {
      first = last = new_node;
    }
    else
    {
      new_node -> next = first;
      first = new_node;
    }
    size++;
  }

  /**
   * Remove the element that's at the front of the list. Causes an
   * assertion error if the list is empty.
   */
  void pop_front()
  {
    assert( !is_empty() );
    Node * temp = first;

    if( first == last )
    {
      first = last = nullptr;
    }
    else
    {
      first = first->next;
    }
    delete temp;
    size--;
  }

  /**
   * Accessor to return the data of the element at the front of the list.
   * Causes an assertion error if the list is empty.
   * @return the data in the front element
   */
  const Object & front() const
  {
    assert( !is_empty() );
    return first->data;
  }

  /**
   * Accessor to return the data of the element at the tail of the list.
   * Causes an assertion error if the list is empty.
   * @return the data in the last element
   */
  const Object & tail() const
  {
    assert( !is_empty());
    return last -> data;
  }

  /**
   * Accessor to determine whether the list is empty
   * @return a boolean corresponding to the emptiness of the list
   */
  bool is_empty() const
  {
    return size == 0;
  }

  /**
   * Generate a string representation of the list
   * Requires operator<< to be defined for the list's object type
   * @return string representation of the list
   */

  string to_string() const
  {
    if( size == 0 )
    {
      return "";
    }
    stringstream buffer;
    for( auto current = first; current != nullptr; current = current->next )
    {
      buffer << current->data << ' ';
    }
    return move( buffer.str() );
  }

 private:
  uint size;
  Node * first;
  Node * last;
};

#endif
