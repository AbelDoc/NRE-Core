
    /**
     * @file NRE_Vector.hpp
     * @brief Declaration of Utility's API's Container : Vector
     * @author Louis ABEL
     * @date 15/05/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <stdexcept>
     #include <utility>
     #include <cstring>

     #include "../../String/NRE_String.hpp"
     #include "../../Interfaces/Stringable/NRE_Stringable.hpp"
     #include "../../Traits/NRE_TypeTraits.hpp"

     #include <Memory/Allocator/NRE_AllocatorTraits.hpp>
    

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
            
            namespace Detail {
    
                /**
                 * @class Vector
                 * @brief A dynamic array, guarantee to be in contiguous memory
                 */
                template <class T, class Allocator>
                class Vector : public Stringable<Vector<T, Allocator>>, public Allocator {
                    static_assert(Memory::IsAllocatorV<Allocator>);                     /**< Check if the given AllocatorType inherit from NRE::Memory::AllocatorTraits */
                    static_assert(std::is_same_v<T, typename Allocator::ValueType>);    /**< Make sure the allocator is set for the container inner type */
                    
                    public :    // Traits
                        /**< The container's allocated type */
                        using ValueType             = T;
                        /**< The container's allocator */
                        using AllocatorType         = Allocator;
                        /**< The object's size type */
                        using SizeType              = std::size_t;
                        /**< The object's difference type */
                        using DifferenceType        = std::ptrdiff_t;
                        /**< The allocated type reference */
                        using Reference             = ValueType&;
                        /**< The allocated type const reference */
                        using ConstReference        = ValueType const&;
                        /**< The allocated type pointer */
                        using Pointer               = typename AllocatorType::Pointer;
                        /**< The allocated type const pointer */
                        using ConstPointer          = typename AllocatorType::ConstPointer;
                        /**< Mutable random access iterator */
                        using Iterator              = Pointer;
                        /**< Immuable random access iterator */
                        using ConstIterator         = ConstPointer;
                        /**< Mutable reverse random access iterator */
                        using ReverseIterator       = std::reverse_iterator<Iterator>;
                        /**< Immuable reverse random access iterator */
                        using ConstReverseIterator  = std::reverse_iterator<ConstIterator>;
                        /**< STL compatibility */
                        using value_type            = ValueType;
                        /**< STL compatibility */
                        using allocator_type        = AllocatorType;
                        /**< STL compatibility */
                        using size_type             = SizeType;
                        /**< STL compatibility */
                        using difference_type       = DifferenceType;
                        /**< STL compatibility */
                        using reference             = Reference;
                        /**< STL compatibility */
                        using const_reference       = ConstReference;
                        /**< STL compatibility */
                        using pointer               = Pointer;
                        /**< STL compatibility */
                        using const_pointer         = ConstPointer;
                        /**< STL compatibility */
                        using iterator              = Iterator;
                        /**< STL compatibility */
                        using const_iterator        = ConstIterator;
                        /**< STL compatibility */
                        using reverse_iterator      = ReverseIterator;
                        /**< STL compatibility */
                        using const_reverse_iterator= ConstReverseIterator;
        
                    private :   // Fields
                        SizeType length;     /**< The data length */
                        SizeType capacity;   /**< The data capacity */
                        Pointer data;        /**< The internal data array */
        
                    public :    // Methods
                        //## Constructor ##//
                            /**
                             * Construct an empty vector with a base capacity
                             */
                            Vector(AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector filled with count copy of value
                             * @param count the number of copy to perform, will be the vector capacity and length
                             * @param value the value to fill the vector with
                             * @param alloc the vector's memory allocator
                             * @pre value don't reference a vector item
                             */
                            Vector(SizeType count, ConstReference value, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector filled with count default value
                             * @param count the number of default element, will be the vector capacity and length
                             * @param alloc the vector's memory allocator
                             */
                            Vector(SizeType count, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector filled with element between 2 iterators
                             * @param begin the begin iterator
                             * @param end   the end iterator, pointing after the last element
                             * @param alloc the vector's memory allocator
                             * @pre begin and end are not iterator from the vector
                             */
                            template <class InputIterator>
                            Vector(InputIterator begin, InputIterator end, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector from an initializer list
                             * @param init  the list to fill the vector with
                             * @param alloc the vector's memory allocator
                             * @pre list don't contain vector reference
                             */
                            Vector(std::initializer_list<T> init, AllocatorType const& alloc = AllocatorType());
            
                        //## Copy Constructor ##//
                            /**
                             * Copy vec into this
                             * @param vec the vector to copy
                             */
                            Vector(Vector const& vec);
                            /**
                             * Copy vec into this
                             * @param vec   the vector to copy
                             * @param alloc the vector's memory allocator
                             */
                            Vector(Vector const& vec, AllocatorType const& alloc);
            
                        //## Move Constructor ##//
                            /**
                             * Move vec into this
                             * @param vec the vector to move
                             */
                            Vector(Vector && vec);
                            /**
                             * Move vec into this
                             * @param vec   the vector to move
                             * @param alloc the vector's memory allocator
                             */
                            Vector(Vector && vec, AllocatorType const& alloc);
            
                        //## Deconstructor ##//
                            /**
                             * Vector Deconstructor
                             */
                            ~Vector();
            
                        //## Getter ##//
                            /**
                             * Access a particular element with bound checking
                             * @param  index the element index
                             * @return       the corresponding element
                             */
                            Reference get(SizeType index);
                            /**
                             * Access a particular element with bound checking
                             * @param  index the element index
                             * @return       the corresponding element
                             */
                            ConstReference get(SizeType index) const;
                            /**
                             * @return the internal data array
                             */
                            Pointer getData();
                            /**
                             * @return the internal data array
                             */
                            ConstPointer getData() const;
                            /**
                             * @return the internal data array
                             */
                            ConstPointer getCData() const;
                            /**
                             * @return the first element
                             */
                            Reference getFront();
                            /**
                             * @return the first element
                             */
                            ConstReference getFront() const;
                            /**
                             * @return the last element
                             */
                            Reference getLast();
                            /**
                             * @return the last element
                             */
                            ConstReference getLast() const;
                            /**
                             * @return the vector effective size
                             */
                            SizeType getSize() const;
                            /**
                             * @return the maximum vector size
                             */
                            constexpr SizeType getMaxSize() const;
                            /**
                             * @return the vector capacity
                             */
                            SizeType getCapacity() const;
                            /**
                             * @return the vector's memory allocator
                             */
                            AllocatorType const& getAllocator() const;
                            /**
                             * @return if the vector is empty
                             */
                            bool isEmpty() const;
            
                        //## Iterator Access ##//
                            /**
                             * @return an iterator on the first element
                             */
                            Iterator begin();
                            /**
                             * @return a const iterator on the first element
                             */
                            ConstIterator begin() const;
                            /**
                             * @return a const iterator on the first element
                             */
                            ConstIterator cbegin() const;
                            /**
                             * @return an iterator on the end of the container
                             */
                            Iterator end();
                            /**
                             * @return a const iterator on the end of the container
                             */
                            ConstIterator end() const;
                            /**
                             * @return a const iterator on the end of the container
                             */
                            ConstIterator cend() const;
                            /**
                             * @return a reverse iterator on the first element
                             */
                            ReverseIterator rbegin();
                            /**
                             * @return a const reverse iterator on the first element
                             */
                            ConstReverseIterator rbegin() const;
                            /**
                             * @return a const reverse iterator on the first element
                             */
                            ConstReverseIterator crbegin() const;
                            /**
                             * @return a reverse iterator on the end of the container
                             */
                            ReverseIterator rend();
                            /**
                             * @return a const reverse iterator on the end of the container
                             */
                            ConstReverseIterator rend() const;
                            /**
                             * @return a const reverse iterator on the end of the container
                             */
                            ConstReverseIterator crend() const;
            
                        //## Methods ##//
                            /**
                             * Assign the vector with count copy of value, starting from the beginning
                             * @param count the number of copy
                             * @param value the copy to fill the vector with
                             * @pre value don't reference a vector item
                             */
                            void assign(SizeType count, ConstReference value);
                            /**
                             * Assign the vector with element between 2 iterators
                             * @param  begin the begin iterator
                             * @param  end   the end iterator, pointing after the last element
                             * @pre begin and end are not iterator from the vector
                             */
                            template <class InputIterator>
                            void assign(InputIterator begin, InputIterator end);
                            /**
                             * Set the vector capacity to a minimum of size, reallocating memory if needed
                             * @param size the new capacity
                             * @warning size value is not checked against getMaxSize()
                             */
                            void reserve(SizeType size);
                            /**
                             * Clear all object in the vector, not actually releasing memory
                             */
                            template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                            void clear() noexcept {
                                for (SizeType i = 0; i < length; i++) {
                                    this->destroy(&data[i]);
                                }
                                length = 0;
                            }
                            /**
                             * Clear all object in the vector, not actually releasing memory
                             */
                            template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                            void clear() noexcept {
                                length = 0;
                            }
                            /**
                             * Insert a copy of value at the specified position
                             * @param  start the position to insert the value
                             * @param  value the value to insert
                             * @return       the iterator on the inserted value
                             * @pre value don't reference a vector item
                             */
                            Iterator insert(ConstIterator start, ConstReference value);
                            /**
                             * Insert count copy of value at the specified position
                             * @param  start the position to insert values
                             * @param  count the number of copy
                             * @param  value the value to insert
                             * @return       the iterator on the first inserted value
                             * @pre value don't reference a vector item
                             */
                            Iterator insert(ConstIterator start, SizeType count, ConstReference value);
                            /**
                             * Insert a copy of element between begin and end at the specified position
                             * @param  start the position to insert values
                             * @param  begin the begin iterator
                             * @param  end   the end iterator, pointing after the last element
                             * @return       the iterator on the first inserted value
                             * @pre begin and end are not iterator from the vector
                             */
                            template <class InputIterator>
                            Iterator insert(ConstIterator start, InputIterator begin, InputIterator end);
                            /**
                             * Insert a list of value at the specified position
                             * @param  start the position to insert values
                             * @param  list  the list to fill the vector with
                             * @return       the iterator on the first inserted value
                             * @pre list don't contain vector reference
                             */
                            Iterator insert(ConstIterator start, std::initializer_list<T> list);
                            /**
                             * Emplace an element at the specified position
                             * @param  start the position to insert the value
                             * @param  args  the value construction arguments
                             * @return       the iterator on the inserted value
                             */
                            template <class ... Args>
                            Iterator emplace(ConstIterator start, Args && ... args);
                            /**
                             * Erase an element in the vector
                             * @param  pos  the position to erase
                             * @return       an iterator on the next valid element
                             */
                            Iterator erase(ConstIterator pos);
                            /**
                             * Erase a set of element from the vector
                             * @param  begin the start position for erasing
                             * @param  end   the end position for erasing
                             * @return       an iterator on the next valid element
                             */
                            Iterator erase(ConstIterator begin, ConstIterator end);
                            /**
                             * Insert a copy of value at the end of the vector
                             * @param value the value to insert
                             * @pre value don't reference a vector item
                             */
                            void pushBack(ConstReference value);
                            /**
                             * Emplace a value at the end of the vector
                             * @param value the value to insert
                             */
                            void pushBack(T && value);
                            /**
                             * Emplace a value at the end of the vector
                             * @param args the arguments for the value construction
                             */
                            template <class ... Args>
                            void emplaceBack(Args && ... args);
                            /**
                             * Pop the last element in the vector
                             */
                            template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                            void popBack() {
                                this->destroy(end() - 1);
                                length--;
                            }
                            /**
                             * Pop the last element in the vector
                             */
                            template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                            void popBack() {
                                length--;
                            }
                            /**
                             * Resize the container up the given size, insert value if needed
                             * @param count the new capacity
                             */
                            void resize(SizeType count);
                            /**
                             * Resize the container up the given size, insert value if needed
                             * @param count the new capacity
                             * @param value the value used when inserting
                             */
                            void resize(SizeType count, ConstReference value);
                            /**
                             * Swap the vector with another vector
                             * @param vec the other vector
                             */
                            void swap(Vector& vec);
                            /**
                             * Shrink to fit the actual size, actually freeing memory
                             */
                            void shrinkToFit();
            
                        //## Access Operator ##//
                            /**
                             * Access a particular element without bound checking
                             * @param  index the element index
                             * @return       the corresponding element
                             */
                            Reference operator [](SizeType index);
                            /**
                             * Access a particular element without bound checking
                             * @param  index the element index
                             * @return       the corresponding element
                             */
                            ConstReference operator [](SizeType index) const;
            
                        //## Assignment Operator ##//
                            /**
                             * Copy vec into this
                             * @param vec the vector to copy into this
                             * @return    the reference of himself
                             */
                            Vector& operator =(Vector const& vec);
                            /**
                             * Move vec into this
                             * @param vec the vector to move into this
                             * @return    the reference of himself
                             */
                            Vector& operator =(Vector && vec);
            
                        //## Comparison Operator ##//
                            /**
                             * Equality test between this and vec
                             * @param vec the other vector
                             * @return    the test result
                             */
                            template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                            bool operator ==(Vector const& vec) const {
                                bool equal = true;
                                SizeType current = 0;
                                while (equal && current < length) {
                                    equal = data[current] == vec[current];
                                    current++;
                                }
                                return equal;
                            }
                            /**
                             * Equality test between this and vec
                             * @param vec the other vector
                             * @return    the test result
                             */
                            template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                            bool operator ==(Vector const& vec) const {
                                if (length != vec.length) {
                                    return false;
                                }
                                return std::memcmp(data, vec.data, length * sizeof(T)) == 0;
                            }
                            /**
                             * Inequality test between this and vec
                             * @param vec the other vector
                             * @return    the test result
                             */
                            bool operator !=(Vector const& vec) const;
            
                        //## Stream Operator ##//
                            /**
                             * Convert the object into a string representation
                             * @return the converted object
                             */
                            [[nodiscard]] String toString() const;
        
                    private :   // Methods
                        /**
                         * Reallocate and grow the storage capacity
                         */
                        void reallocate();
                        /**
                         * Rellocate the data to the given size
                         * @param newSize the new capacity
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        void reallocate(SizeType newSize) {
                            SizeType tmp = capacity;
                            capacity = newSize;
                            Pointer newData = this->allocate(capacity);
                
                            for (SizeType current = 0; current < length; current++) {
                                this->construct(&newData[current], std::move(data[current]));
                            }
                            this->deallocate(data, tmp);
                            data = newData;
                        }
                        /**
                         * Rellocate the data to the given size
                         * @param newSize the new capacity
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        void reallocate(SizeType newSize) {
                            SizeType tmp = capacity;
                            capacity = newSize;
                            Pointer newData = this->allocate(capacity);
                
                            std::memmove(newData, data, length * sizeof(T));
                            this->deallocate(data, tmp);
                            data = newData;
                        }
                        /**
                         * Reallocate the vector with the neareast grow factor value
                         * @param size the new minimum capacity
                         */
                        void reserveWithGrowFactor(SizeType size);
                        /**
                         * Shift all element in the vector, don't do reallocation
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        void shift(SizeType start, SizeType count) {
                            for (SizeType index = length + count - 1; index != start + count - 1; index--) {
                                this->construct(&data[index], std::move(data[index - count]));
                            }
                        }
                        /**
                         * Shift all element in the vector, don't do reallocation
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        void shift(SizeType start, SizeType count) {
                            std::memmove(data + start + count, data + start, (length - start) * sizeof(T));
                        }
                        /**
                         * Shift back all element in the vector, don't call deconstructor
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        void shiftBack(SizeType start, SizeType count) {
                            for (SizeType index = start; index < start + count; index++) {
                                this->construct(&data[index], std::move(data[index + count]));
                            }
                        }
                        /**
                         * Shift back all element in the vector, don't call deconstructor
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        void shiftBack(SizeType start, SizeType count) {
                            std::memmove(data + start, data + start + count, (length - start) * sizeof(T));
                        }
                        /**
                         * Copy the vector content
                         * @param vec the vector to copy
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        void copy(Vector const& vec) {
                            SizeType current = 0;
                            for (ConstReference it : vec) {
                                this->construct(&data[current], it);
                                current++;
                            }
                        }
                        /**
                         * Copy the vector content
                         * @param vec the vector to copy
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        void copy(Vector const& vec) {
                            std::memcpy(data, vec.data, vec.length * sizeof(T));
                        }
        
                    private :    // Static
                        static constexpr float GROW_FACTOR = 2;                 /**< The container's reallocation growth factor */
                        static constexpr SizeType BASE_ALLOCATION_SIZE = 16;    /**< The container's base size if not given */
                };
            }
        }
    }

    #include "NRE_Vector.tpp"
