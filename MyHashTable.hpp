#ifndef MY_HASH_TABLE_HPP
#define MY_HASH_TABLE_HPP


/**
 * TODO: Complete this class!
 */


/// Your welcome
#include <forward_list>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <numeric>
#include <stdexcept>
#include <utility>


//	More includes ... ?


///	Begin our class namespace
namespace CPSC131::MyHashTable
{
	//
	template<class VTYPE>
	class MyHashTable
	{
		//
		public:
			
			//
			static constexpr size_t DEFAULT_CAPACITY = 1024;
			static constexpr size_t ULLONG_WRAP_AT = 4294967295;
			
			/**
			 * Constructor
			 * 
			 * Probably easiest to do the following:
			 * 
			 *   1. Call on setCapacity() to set the table's capacity
			 */
  			MyHashTable(size_t capacity = MyHashTable::DEFAULT_CAPACITY)
			{
				this->size_ = 0;
				
				this->capacity_ = capacity;
				
				this->n_collisions_ = 0;
				
				this->table_ = new std::forward_list<std::pair<std::string, VTYPE>> [capacity];
			}
			
			/**
			 * Copy constructor
			 */
			MyHashTable(const MyHashTable& other)
			{
				//same with increasing size but same size 
				
				/*
				this->size_ = 0;
				
				this->capacity_ = other.capacity();
				
				this->n_collisions_ = other.n_collisions();
				
				this->table_ = new std::forward_list<std::pair<std::string, VTYPE>> [this->capacity_];
				
				
				 
				size_t list = 0;
				
				 if(other.size() != 0)
				{
					while (list < this->capacity_)
					{
				
						auto iter = (other.getTable()) [list].begin();
				
						auto end = (other.getTable()) [list].end();
				
						for(;iter != end; ++iter)
						{
						//this->add(iter->first, iter->second );
						auto newPair = std::make_pair((*iter).first, (*iter).second);
						table_[list].push_front(newPair);
						size_++;
						}
				
						list++;
					}
				
				}
				
				*/
				
				
				this->capacity_ = other.capacity();
				
				this->n_collisions_ = 0;
				
				this->table_ = new std::forward_list<std::pair<std::string, VTYPE>> [this->capacity_];
				
				
				size_t list = 0;
				
					this->size_ = 0;
					while ( list < this->capacity_ )
					{
				
						
						 for(const auto& a : (other.getTable())[list])
						{
							this->add(a.first, a.second );
						}
			
						list++;
						
						
						/*
						auto iter = (other.getTable())[list].begin();
						auto end = (other.getTable())[list].end();
						for(;iter!=end; ++iter)
						{
							this->add(iter->first, iter->second);
						}
						list++;
						*/
						
				}
				
			
			}
			
			/**
			 * Destructor
			 * 
			 * Deallocate the table (array of std::forward_list 's), and set the table to nullptr
			 * Don't double-deallocate if the table is already a null pointer
			 */
			~MyHashTable()
			{
				if(this->table_ != nullptr)
				{
				delete[] this->table_;
				this->table_ = nullptr;
				}
			}
			
			/**
			 * Should return the capacity_ of this hash table
			 * Meaning, the total number of rows in this hash table
			 * Doesn't discern between used/unused/collided rows
			 */
			size_t capacity() const
			{
				return this->capacity_;
			}
			
			/**
			 * Should return the number of items currently in the hash table
			 */
			size_t size() const
			{
				return this->size_;
			}
			
			/**
			 * Return true if the table is empty, false otherwise
			 */
			bool empty() const
			{
				if(this->size_ == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			
			/**
			 * Should return the number of collisions currently present in the hash table
			 */
			size_t n_collisions() const
			{
				
				size_t collision = 0;
				
				size_t list = 0;
				
				if(this->size() > 1)
			{
					while (list < this->capacity_)
					{
						size_t col = 0;
				
						/*for(const auto& a: table_[list])
						{
							std::string b = a.first;
							col++;
						}
						
						while ( list < this->capacity_ )
					{*/
				
						/*
						 for(const auto& a : other[list])
						{
							this->add(a.first, a.second );
						}
			
						list++;
						*/
						
						auto iter = table_[list].begin();
						auto end = table_[list].end();
						for(;iter!=end; ++iter)
						{
							col++;
						}
						
						
						if(col>=1)
						{
						col--;
						collision += col;
						}
				
						list++;
					}
					
			}
			
				return collision;
			
			}
			
			
			std::forward_list<std::pair<std::string, VTYPE>>* getTable() const
			{
				return this->table_;
			}
			
			
			size_t getCollisions() const
			{
				return this->n_collisions_;
			}
			/**
			 * Set the capacity for this table.
			 * Changes the total number of hash table rows available.
			 * 
			 * Existing entries should survive the change,
			 * 	so you probably want to do the following:
			 * 
			 *  1. Keep the existing table array pointer in a temporary pointer
			 *  
			 *  2. Re-initialize 'this' to contain a new empty table of the right capacity
			 *  
			 *  3. The temporary pointer should now contain the OLD data (old table),
			 *     while 'this' contains the brand new table of the new size.
			 * 
			 *  4. Iterate through all key/value pairs in the old data (temp pointer).
			 * 
			 *  5. For each key/value pair in the old data, call this->add() to insert
			 *     properly into the new table.
			 *  
			 *  6. Deallocate the old table by calling `delete []` on the temporary pointer.
			 * 
			 * Don't forget to check whether the current table is a nullptr before you
			 *  decide to do iterations!
			 */
			void setCapacity(size_t c)
			{
				
				
				auto table_2 = this->table_;
				
				this->table_ = new std::forward_list<std::pair<std::string, VTYPE>> [c];
				
				size_t list = 0;
				
				this->size_ = 0;
					
					while (list < this->capacity_)
					{
					
						
						/*auto iter = table_[list].begin();
						auto end = table_[list].end();
						for(;iter!=end; ++iter)
						{
							auto newPair = std::make_pair((*iter).first, (*iter).second);
							table_[list].push_front(newPair);
							size_++;
						}
							
								auto newPair = std::make_pair(b.first, b.second);
								table_[list].push_frnt(newPair);
								size_++;
							
						}
						*/
					
						list++;
					}
					
			
				
				
				
				
				this->capacity_ = c;
				
				this->n_collisions_ = n_collisions();
				
				delete[] table_2;
				
				table_2 = nullptr;
			
			}
			
			///	Your welcome
			unsigned long long int hash(std::string key) const
			{
				return this->midSquareHash(key);
			}
			
			/**
			 * Implement the "modified mid square" hash function,
			 * as described in the instructions.
			 */
			unsigned long long int midSquareHash(std::string key) const
			{
				unsigned long long int sum = 1;
				
				
				for(char a:key)
				{
					unsigned long long int b;
					b = static_cast<unsigned long long int>(a);
					sum *= b;
					sum = sum % ULLONG_WRAP_AT;
				}
				
				sum *= sum;
				
				std::string stringSum = std::to_string(sum);
				
				size_t d = ( stringSum.length() )/2;
				
				std::string midStringSum = stringSum.substr(d/2, d);
				
				unsigned long long int numStringSum = std::stoull(midStringSum);
				
				if(this->capacity_ != 0)
				{
					numStringSum = numStringSum % (this->capacity_);
				}
				
				return numStringSum;
			}
			
			/**
			 * Implement your own custom hash functions to compete on the Gradescope Leaderboard!
			 * Four stubs are provided to make experimentation a little easier.
			 * Only the best hash function will count towards the leaderboard.
			 */
			 
			unsigned long long int myCustomHashFunction1(std::string key) const
			{
				//mod 39 then n^2+n+41 to generate a prime
				//power this prime 
				//mod ULL
				return 0;
			}
			
			unsigned long long int myCustomHashFunction2(std::string key) const
			{
				//mod 39 then n^2+n+41 to generate a prime
				//power this prime 
				//take partition
				//mod ULL
				return 0;
			}
			unsigned long long int myCustomHashFunction3(std::string key) const
			{
				//randomize table[key] address
				//mod 39 then n^2+n+41 to generate a prime
				//power this prime 
				//take partition
				//mod ULL
				return 0;
			}
			unsigned long long int myCustomHashFunction4(std::string key) const
			{
				//randomize table[key] address
				//flip address
				//mod 39 then n^2+n+41 to generate a prime
				//power this prime 
				//take partition
				//mod ULL
				
				return 0;
			}
			
			/**
			 * Return true if a key exists in the table, or false otherwise.
			 */
		
			bool exists(std::string key) const
			
			{
				unsigned long long int b = hash(key);
				
				if(table_[b].empty() != true)
				{
					for(const auto& a: table_[b])
					{
						if(a.first == key)
						{
						return true;
						}
					}
				}
				return false;
			}
				
			
			 /* Add a key/value pair to this table.
			 * If the key already exists, throw a runtime_error.
			 */
			 
			void add(std::string key, VTYPE value)
			{
				auto newPair = std::make_pair(key, value);
				if( exists(key) == true ) 
				{
					throw std::runtime_error("Key exists.");
				}
				else
				{
					unsigned long long int b = hash(key);
					
					this->table_[b].push_front(newPair);
				}
				
				size_++;
			}
			
			/**
			 * Should return a reference to the VTYPE value associated to the provided key.
			 * If the key/value pair isn't in the table, a runtime_error should be thrown.
			 */
			VTYPE& get(std::string key) const
			{
				static VTYPE second;
				
				if(exists(key) == true)
				{
				
					unsigned long long int b = hash(key);
					
					if(table_[b].empty() != true)
					{
				
						for(const auto& a: table_[b])
						{
							if(a.first == key)
							{
								
							second = a.second;
			
							}
						}
					
					}
					
					return second;
				
				}
				
				else
				{
				throw std::runtime_error("Cannot get value for key because it doesn't exist: ");
				}
			
			}
			
			/**
			 * In a single std::forward_list, return every key currently present in the table
			 * 
			 * If no keys exist (empty table), just return an empty std::forward_list.
			 * 
			 * It's okay that when sorted == false, std::forward_list::push_front will
			 *  return your keys in backwards-order, as there is no guarantee
			 *  of properly-ordered keys anyway.
			 * 
			 * However, if the caller passes sorted=true, you should sort the keys
			 * 	as a last step before returning them.
			 * 	Try using the built-in method std::forward_list::sort
			 */
			 
			std::forward_list<std::string> getAllKeys(bool sorted = false) const
			{
				std::forward_list<std::string> keys;
				
			 	size_t list = 0;
				
				if(table_ != nullptr)
			{
				
					while (list < this->capacity_)
				
					{
				
					auto iter = table_[list].begin();
				
					auto end = table_[list].end();
				
						for(;iter != end; ++iter)
						{
					
						keys.push_front(iter->first);
					
						}
				
					list++;
					
					}
				
				
					if(sorted == true)
					{
						keys.sort();
					}
				
			}	
			
				return keys;
			
			
			}
			/**
			 * Remove a key/value pair that corresponds to the provided key.
			 * If no such key exists, throw a runtime_error.
			 */
			void remove(std::string key)
		    
		    {
			    unsigned long long int b = hash(key);
			
				if(table_[b].empty() == false)
				
				{
				
				/*
				 {
					for(auto a : table_[b])
					{
						if(a.first == key)
						{
							delete a;
							size_--;
						}
					}
				}
				
				*/
					auto iter = table_[b].begin();
					auto prev = table_[b].before_begin();
					auto end = table_[b].end();
				
					for(;iter != end; ++iter)
					{
						
						
						if(iter->first == key)
						{
							
							table_[b].erase_after(prev); 
							//table_[b].clear();
							--size_;
							break;
						}
						//DONT'T INCREMENT A NULL POINTER!!! DOUBLE AN ACTION WILL CAUSE SEG FAULT!!TRACE VARIABLE USING STEP TABLE!!
						else
						{
						prev = iter;
						}
						
						
					}
					
					
				}
					
				
				else
				
				{
					throw std::runtime_error("Cannot remove value for key because it doesn't exist: " + key);
				}
				
			} 
			
			
			/*
		
			if(exists(key) == true)
			{
				unsigned long long int b = hash(key);
				//auto iter = table_[b].begin();
				//auto prev = table_[b].before_begin();
				
				if(table_[b].empty() == false)
				{
				
				for(const auto& a : table_[b])
				{
				//	prev = iter;
				
					if(a.first == key)
					{
						//delete table_[b];
						//table_[b].erase_after(prev);
					}
					//prev = iter;
					//iter++;
					
				}
				
				
				}
				
				size_--;
				
			 }
				else
			 {
				//throw std::runtime_error("Cannot remove value for key because it doesn't exist: " + key);
			 }
			
			*/
			
		
		
		
			/**
			 * Remove all entries in this table
			 * Iterate over each table row and call clear on the row's list
			 */
			void clear()
			{
				
					for( size_t i = 0; i<this->capacity_; i++)
				
					{
						table_[i].clear();
						//delete table_[list];
						
					}
				size_ = 0;
				
			}
			
			/**
			 * Assignment Operator
			 */
			MyHashTable<VTYPE>& operator=(const MyHashTable<VTYPE>& other)
			{
				MyHashTable<VTYPE>& newHash(other);
				//this = MyHashTable(other);
				return newHash;
				//return *this;
			}
			
		//
		
		private:
			
			/**
			 * Keeps track of the capacity of this hash table
			 * (total number of rows in the table, whether used or not)
			 * (does not care about collisions)
			 */
			size_t capacity_ = 0;
			
			/**
			 * Keeps track of the total number of items currently in
			 * the hash table
			 */
			size_t size_ = 0;
			
			/**
			 * Keeps track of the number of collisions currently present in the table
			 */
			size_t n_collisions_ = 0;
			
			/**
			 * The actual hash table.
			 * We'll make this a fixed-sized array,
			 *   but dynamically allocated so we can resize whenever we need.
			 * 
			 * Try to imagine each table row is actually a complete forward_list.
			 * In a perfect situation where a table has no collisions, each list
			 *   will simply contain one item.
			 * 
			 * One "item" in this case refers to an std::pair<std::string, VTYPE>,
			 *   where the first part of the pair is the key and the second
			 *   is the value (of type VTYPE).
			 */
			 
			std::forward_list<std::pair<std::string, VTYPE>> * table_ = nullptr;
			
	};
	
}

















#endif
