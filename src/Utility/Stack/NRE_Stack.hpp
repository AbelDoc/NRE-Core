    
    /**
     * @file NRE_StaticVector.hpp
     * @brief Declaration of Utility's API's Container : StaticVector
     * @author Louis ABEL
     * @date 24/02/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include "../Vector/NRE_Vector.hpp"

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
        
            /**
             * @class Stack
             * @brief A stack adapter wrapping a container class
             */
            template <class T, class Container = Vector<T>>
            class Stack : public Stringable<Stack<T, Container>> {
                static_assert(std::is_same_v<T, Container::ValueType>);
                public :    // Traits
                    /** The container value type */
                    using ValueType      = typename Container::ValueType;
                    /** The container size type */
                    using SizeType       = typename Container::SizeType;
                    /** The value type reference */
                    using Reference      = typename Container::Reference;
                    /** The value type const reference */
                    using ConstReference = typename Container::ConstReference;
                    
                private :   // Fields
                    Container c;    /**< The internal container */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a stack from a moved container
                         * @param container the container to move
                         */
                        Stack(Container && container = Container());
                        /**
                         * Construct a stack from a container to copy
                         * @param container the container to copy
                         */
                        Stack(Container const& container);
    
                    //## Copy Constructor ##//
                        /**
                         * Copy s into this
                         * @param  s the stack to copy
                         */
                        Stack(Stack const& s) = default;
        
                    //## Move Constructor ##//
                        /**
                         * Move s into this
                         * @param  s the stack to move
                         */
                        Stack(Stack && s) = default;
        
                    //## Deconstructor ##//
                        /**
                         * Stack Deconstructor
                         */
                        ~Stack() = default;
    
                    //## Getter ##//
                        /**
                         * @return the top element
                         */
                        Reference getTop();
                        /**
                         * @return the top element
                         */
                        ConstReference getTop() const;
                        /**
                         * @return if the stack is empty
                         */
                        bool isEmpty() const;
                        /**
                         * @return the stack effective size
                         */
                        SizeType getSize() const;
        
                    //## Methods ##//
                        /**
                         * Insert a copy of value at the top of the stack
                         * @param value the value to insert
                         * @pre value don't reference a stack item
                         */
                        void push(ConstReference value);
                        /**
                         * Emplace a value at the top of the stack
                         * @param value the value to insert
                         */
                        void push(ValueType && value);
                        /**
                         * Emplace a value at the top of the stack
                         * @param args the arguments for the value construction
                         */
                        template <class ... Args>
                        void emplace(Args && ... args);
                        /**
                         * Pop the top element in the stack
                         */
                        void pop();
                        /**
                         * Swap the stack with another stack
                         * @param s the other stack
                         */
                        void swap(Stack& s);
    
                    //## Assignment Operator ##//
                        /**
                         * Copy s into this
                         * @param s the stack to copy into this
                         * @return  the reference of himself
                         */
                        Stack& operator =(Stack const& s) = default;
                        /**
                         * Move s into this
                         * @param s the stack to move into this
                         * @return  the reference of himself
                         */
                        Stack& operator =(Stack && s) = default;
        
                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and s
                         * @param s the other stack
                         * @return  the test result
                         */
                        bool operator ==(Stack const& s) const;
                        /**
                         * Inequality test between this and s
                         * @param s the other stack
                         * @return  the test result
                         */
                        bool operator !=(Stack const& s) const;
    
                    //## Stream Operator ##//
                        /**
                         * Convert the object into a string representation
                         * @return the converted object
                         */
                        [[nodiscard]] String toString() const;
            };
        }
    }

    #include "NRE_Stack.tpp"