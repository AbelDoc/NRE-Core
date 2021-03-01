    
    /**
     * @file NRE_IteratorTraits.hpp
     * @brief Declaration of Core's API's Iterator Traits
     * @author Louis ABEL
     * @date 15/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../../Concept/NRE_Concept.hpp"
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {
        
            /**
             * Query a value's address even if the value type overload address operator
             * @param t the value to obtain the adress
             * @return the computed address
             */
            template <class T>
            [[nodiscard]] constexpr T* addressOf(T& t) noexcept {
                return std::addressof(t);
            }
    
            /**
             * Inhibit addressOf so user can't get address of const r-value
             * @param t the value to obtain the adress
             * @return the computed address
             */
            template <class T>
            [[nodiscard]] const T* addressOf(T && t) = delete;
            
            /**
             * @struct InputIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct InputIteratorCategory {
                using iterator_category = std::input_iterator_tag;
                using iterator_concept = iterator_category;
            };
    
            /**
             * @struct OutputIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct OutputIteratorCategory {
                using iterator_category = std::output_iterator_tag;
                using iterator_concept = iterator_category;
            };
    
            /**
             * @struct ForwardIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct ForwardIteratorCategory : public InputIteratorCategory {
                using iterator_category = std::forward_iterator_tag;
                using iterator_concept = iterator_category;
            };
    
            /**
             * @struct BidirectionalIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct BidirectionalIteratorCategory : public ForwardIteratorCategory {
                using iterator_category = std::bidirectional_iterator_tag;
                using iterator_concept = iterator_category;
            };
    
            /**
             * @struct RandomAccessIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct RandomAccessIteratorCategory : public BidirectionalIteratorCategory {
                using iterator_category = std::random_access_iterator_tag;
                using iterator_concept = iterator_category;
            };
    
            /**
             * @struct ContiguousIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct ContiguousIteratorCategory : public RandomAccessIteratorCategory {
                using iterator_category = std::contiguous_iterator_tag;
                using iterator_concept = iterator_category;
            };
            
            /**
             * @struct IteratorCategoryAdapter
             * @brief Allow to adapt STL iterator tag to NRE iterator tag
             */
            template <class T>
            struct IteratorCategoryAdapter {
            };
            
            template <class T> requires Concept::SameAs<T, std::input_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = InputIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::output_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = OutputIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::forward_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = ForwardIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::bidirectional_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = BidirectionalIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::random_access_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = RandomAccessIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::contiguous_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = ContiguousIteratorCategory;
            };
            
            /** Helper to access IteratorCategoryAdapter type */
            template <class T>
            using IteratorCategoryAdapterT = typename IteratorCategoryAdapter<T>::Type;
    
            /**
             * @struct IncrementableTraits
             * @brief Allow an abstract access to incrementable traits with STL compatiblity (STL -> NRE)
             */
            template <class T>
            struct IncrementableTraits {
            };
    
            template <Concept::Object T>
            struct IncrementableTraits<T*> {
                using DifferenceType = Core::DifferenceType;
            };
    
            template <class T>
            struct IncrementableTraits<const T> : IncrementableTraits<T> {
            };
    
            template <class T> requires requires {
                typename T::DifferenceType;
            } && (!requires {
                typename T::difference_type;
            })
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::DifferenceType;
            };
    
            template <class T> requires requires {
                typename T::difference_type;
            } && (!requires {
                typename T::DifferenceType;
            })
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::difference_type;
            };
    
            template <class T> requires requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::DifferenceType, typename T::difference_type>;
            }
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::DifferenceType;
            };
    
            template <class T> requires (!requires {
                typename T::DifferenceType;
            } && !requires {
                typename T::difference_type;
            } && !requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::DifferenceType, typename T::difference_type>;
            }) && requires (T const& a, T const& b) {
                { a - b } -> Concept::Integral;
            }
            struct IncrementableTraits<T> {
                using DifferenceType = MakeSignedT<decltype(std::declval<T>() - std::declval<T>())>;
            };
            
            /**
             * @struct IndirectlyReadableTraits
             * @brief Allow an abstract access to indirectly readable traits with STL compatiblity (STL -> NRE)
             */
            template <class T>
            struct IndirectlyReadableTraits {
            };
    
            template <Concept::Object T>
            struct IndirectlyReadableTraits<T*> {
                using ValueType = RemoveCVT<T>;
            };
    
            template <Concept::Array T>
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<RemoveExtentT<T>>;
            };
    
            template <class T>
            struct IndirectlyReadableTraits<const T> : IndirectlyReadableTraits<T> {
            };
    
            template <class T> requires requires {
                typename T::ValueType;
            } && (!requires {
                typename T::value_type;
            })
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::ValueType>;
            };
    
            template <class T> requires requires {
                typename T::value_type;
            } && (!requires {
                typename T::ValueType;
            })
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::value_type>;
            };
    
    
            template <class T> requires requires {
                typename T::ValueType;
                typename T::value_type;
                Concept::SameAs<typename T::ValueType, typename T::value_type>;
            }
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::ValueType>;
            };
    
            /**
             * @struct IteratorCategoryTraits
             * @brief Allow an abstract access to iterator category traits with STL compatiblity (STL -> NRE)
             */
            template <class T>
            struct IteratorCategoryTraits {
            };
            
            template <Concept::Object T>
            struct IteratorCategoryTraits<T*> {
                using Category = ContiguousIteratorCategory;
            };
            
            template <class T>
            struct IteratorCategoryTraits<const T> : IteratorCategoryTraits<T> {
            };
            
            template <class T> requires requires {
                typename T::Category;
            } && (!requires {
                typename T::iterator_category;
            } && !requires {
                typename T::iterator_concept;
            })
            struct IteratorCategoryTraits<T> {
                using Category = typename T::Category;
            };
    
            template <class T> requires requires {
                typename T::iterator_category;
            } && (!requires {
                typename T::Category;
            } && !requires {
                typename T::iterator_concept;
            })
            struct IteratorCategoryTraits<T> {
                using Category = IteratorCategoryAdapterT<typename T::iterator_category>;
            };
            
            template <class T> requires requires {
                typename T::iterator_concept;
            } && (!requires {
                typename T::Category;
            })
            struct IteratorCategoryTraits<T> {
                using Category = IteratorCategoryAdapterT<typename T::iterator_concept>;
            };
            
            template <class T> requires requires {
                typename T::Category;
                typename T::iterator_category;
                Concept::SameAs<typename T::Category, IteratorCategoryAdapterT<typename T::iterator_category>>;
            } && (!requires {
                typename T::iterator_concept;
            })
            struct IteratorCategoryTraits<T> {
                using Category = typename T::Category;
            };
            
            template <class T> requires requires {
                typename T::Category;
                typename T::iterator_concept;
                Concept::SameAs<typename T::Category, IteratorCategoryAdapterT<typename T::iterator_concept>>;
            }
            struct IteratorCategoryTraits<T> {
                using Category = typename T::Category;
            };
    
            /**
             * @struct IteratorPointerTraits
             * @brief Allow an abstract access to iterator pointer traits with STL compatiblity (STL -> NRE)
             */
            template <class T>
            struct IteratorPointerTraits {
            };
    
            template <Concept::Object T>
            struct IteratorPointerTraits<T*> {
                using Pointer = T*;
            };
    
            template <class T>
            struct IteratorPointerTraits<const T> {
                using Pointer = const typename IteratorPointerTraits<T>::Pointer;
            };
    
            template <class T> requires requires {
                typename T::Pointer;
            } && (!requires {
                typename T::pointer;
            })
            struct IteratorPointerTraits<T> {
                using Pointer = typename T::Pointer;
            };
    
            template <class T> requires requires {
                typename T::pointer;
            } && (!requires {
                typename T::Pointer;
            })
            struct IteratorPointerTraits<T> {
                using Pointer = typename T::pointer;
            };
    
            template <class T> requires requires {
                typename T::Pointer;
                typename T::pointer;
                Concept::SameAs<typename T::Pointer, typename T::pointer>;
            }
            struct IteratorPointerTraits<T> {
                using Pointer = typename T::Pointer;
            };
    
            template <class T> requires (!requires {
                typename T::Pointer;
            } && !requires {
                typename T::pointer;
            } && !requires {
                typename T::Pointer;
                typename T::pointer;
                Concept::SameAs<typename T::Pointer, typename T::pointer>;
            }) && requires (T& a) {
                a.operator->();
            }
            struct IteratorPointerTraits<T> {
                using Pointer = decltype(std::declval<T&>().operator->());
            };
    
            template <class T> requires (!requires {
                typename T::Pointer;
            } && !requires {
                typename T::pointer;
            } && !requires {
                typename T::Pointer;
                typename T::pointer;
                Concept::SameAs<typename T::Pointer, typename T::pointer>;
            } && !requires (T& a) {
                a.operator->();
            })
            struct IteratorPointerTraits<T> {
                using Pointer = void;
            };
    
            /** Helper to access an iterator Category */
            template <class T>
            using IteratorCategoryT = typename IteratorCategoryTraits<RemoveCVReferenceT<T>>::Category;

            /** Helper to access an iterator ValueType */
            template <class T>
            using IteratorValueT = typename IndirectlyReadableTraits<RemoveCVReferenceT<T>>::ValueType;
            
            /** Helper to access an iterator DifferenceType */
            template <class T>
            using IteratorDifferenceT = typename IncrementableTraits<RemoveCVReferenceT<T>>::DifferenceType;
    
            /** Helper to access an iterator Pointer */
            template <class T>
            using IteratorPointerT = typename IteratorPointerTraits<RemoveVolatileT<RemoveReferenceT<T>>>::Pointer;
            
            /** Compute the reference type of a given type */
            template <Concept::Dereferenceable T>
            using IteratorReferenceT = decltype(*std::declval<T&>());
            
            /** Compute the r-value reference type of a given type */
            template <class T> requires requires (T& t) {
                { std::ranges::iter_move(t) } -> Concept::Referenceable;
            }
            using IteratorRValueReferenceT = decltype(std::ranges::iter_move(std::declval<T&>()));
            
            /** Allow to prevent iterators and sentinels that can be subtracted to satisfy the concept */
            template <class S, class T>
            inline constexpr bool DISABLE_SIZED_SENTINEL_FOR = false || std::disable_sized_sentinel_for<S, T>;
            
            /** Allow the use of borrowed iterator on object passed by value */
            template <class T>
            inline constexpr bool ENABLE_BORROWED_RANGE = false || std::ranges::enable_borrowed_range<T>;
            
            /**
             * @struct IteratorTraits
             * @brief Allow uniform access to iterator's traits
             */
            template <class T>
            struct IteratorTraits {
                using DifferenceType = IteratorDifferenceT<T>;
                using ValueType = IteratorValueT<T>;
                using Pointer = IteratorPointerT<T>;
                using Reference = IteratorReferenceT<T>;
                using Category = IteratorCategoryT<T>;
            };
            
            /**
             * @class Iterator
             * @brief Define a base for user iterators, giving useful typedef and operators using CRTP
             */
            template <class It, class Cat, class T, class Diff = DifferenceType, class Ptr = T*, class Ref = T&>
                requires Concept::DerivedFrom<Cat, InputIteratorCategory> ||
                         Concept::DerivedFrom<Cat, OutputIteratorCategory>
            class Iterator : public StaticInterface<Iterator<It, Cat, T, Diff, Ptr, Ref>> {
                public :    // Traits
                    using Derived           = It;
                    using DifferenceType    = Diff;
                    using ValueType         = T;
                    using Pointer           = Ptr;
                    using Reference         = Ref;
                    using Category          = Cat;
                    using difference_type   = DifferenceType;
                    using value_type        = ValueType;
                    using pointer           = Pointer;
                    using reference         = Reference;
                    using iterator_category = Category::iterator_category;
                    using iterator_concept  = Category::iterator_concept;
                    
                public :    // Methods
                    //## Methods ##//
                        /**
                         * @return a reference on the iterated data
                         */
                        Reference dereference() const {
                            return this->impl().dereference();
                        }
                        /**
                         * Increment the iterator position by one
                         */
                        void increment() {
                            this->impl().increment();
                        }
                        /**
                         * Decrement the iterator position by one
                         */
                        void decrement() requires Concept::DerivedFrom<Category, BidirectionalIteratorCategory> {
                            this->impl().decrement();
                        }
                        /**
                         * Move the iterator by a given number (can be negative)
                         * @param n the distance to move
                         */
                        void advance(DifferenceType n) requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            this->impl().advance(n);
                        }
                        /**
                         * Tell the distance between the given iterator
                         * @param it the other iterator
                         * @return   the distance between it and this
                         */
                        DifferenceType distanceTo(Iterator const& it) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return this->impl().distanceTo(it);
                        }
                        /**
                         * Test if the given iterator point to the same position
                         * @param it the other iterator
                         * @return   the test's result
                         */
                        bool equal(Iterator const& it) const {
                            return this->impl().equal(it);
                        }
            
                    //## Access Operator ##//
                        /**
                         * Dereference operator, allow access to the data
                         * @return the iterator data
                         */
                        Reference operator*() const {
                            return dereference();
                        }
                        /**
                         * Arrow dereference operator, allow access to the data
                         * @return the iterator data pointer
                         */
                        Pointer operator->() {
                            return &dereference();
                        }
            
                    //## Increment Operator ##//
                        /**
                         * Pre increment operator, access the next element
                         * @return the reference of himself
                         */
                        Derived& operator++() {
                            increment();
                            return this->impl();
                        }
                        /**
                         * Post increment operator, access the next element
                         * @return the iterator on the current element
                         */
                        Derived operator++(int) {
                            Derived tmp(this->impl());
                            ++*this;
                            return tmp;
                        }
            
                    //## Decrement Operator ##//
                        /**
                         * Pre decrement operator, access the previous element
                         * @return the reference of himself
                         */
                        Derived& operator--() requires Concept::DerivedFrom<Category, BidirectionalIteratorCategory> {
                            decrement();
                            return this->impl();
                        }
                        /**
                         * Post decrement operator, access the previous element
                         * @return the iterator on the current element
                         */
                        Derived operator--(int) requires Concept::DerivedFrom<Category, BidirectionalIteratorCategory> {
                            Derived tmp(this->impl());
                            --*this;
                            return tmp;
                        }
            
                    //## Shortcut Operator ##//
                        /**
                         * Move the iterator by n
                         * @param n the distance to add
                         * @return the reference of himself
                         */
                        Derived& operator +=(DifferenceType n) requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            advance(n);
                            return this->impl();
                        }
                        /**
                         * Move the iterator by n
                         * @param n the distance to subtract
                         * @return the reference of himself
                         */
                        Derived& operator -=(DifferenceType n) requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            advance(-n);
                            return this->impl();
                        }
            
                    //## Arithmetic Operator ##//
                        /**
                         * Create an iterator resulting in the move of this by n
                         * @param n the distance to add
                         * @return the new iterator
                         */
                        Derived operator +(DifferenceType n) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return Derived(this->impl()) += n;
                        }
                        /**
                         * Create an iterator resulting in the move of this by n
                         * @param n the distance to subtract
                         * @return the new iterator
                         */
                        Derived operator -(DifferenceType n) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return Derived(this->impl()) -= n;
                        }
                        /**
                         * Compute the signed distance between this and it
                         * @param it the other iterator
                         * @return the iterators distance
                         */
                        DifferenceType operator -(Derived const& it) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return it.distanceTo(this->impl());
                        }
                        /**
                         * Create an iterator resulting in the move of it by n
                         * @param n  the distance to add
                         * @param it the iterator to move
                         * @return the new iterator
                         */
                        friend Derived operator +(Diff n, Derived const& it) requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return Derived(it) += n;
                        }
                        /**
                         * Create an iterator resulting in the move of it by n
                         * @param n  the distance to subtract
                         * @param it the iterator to move
                         * @return the new iterator
                         */
                        friend Derived operator -(Diff n, Derived const& it) requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return Derived(it) -= n;
                        }
        
                    //## Access Operator ##//
                        /**
                         * Return a reference on an iterated element
                         * @warning No range check performed
                         * @param n the number of move from the current position
                         * @return the new element reference
                         */
                        Reference operator [](DifferenceType n) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            Derived it(*this);
                            it += n;
                            return *it;
                        }
            
                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and it
                         * @param it the other iterator
                         * @return the test result
                         */
                        bool operator==(Derived const& it) const {
                            return this->impl().equal(it);
                        }
                        /**
                         * Inequality test between this and it
                         * @param it the other iterator
                         * @return the test result
                         */
                        bool operator!=(Derived const& it) const {
                            return !this->impl().equal(it);
                        }
                        /**
                         * Inferior test between this and it
                         * @param it the vector to test with this
                         * @return the test's result
                         */
                        bool operator <(Derived const& it) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return it.distanceTo(this->impl()) < 0;
                        }
                        /**
                         * Superior test between this and it
                         * @param it the vector to test with this
                         * @return the test's result
                         */
                        bool operator >(Derived const& it) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return it.distanceTo(this->impl()) > 0;
                        }
                        /**
                         * Inferior or Equal test between this and it
                         * @param it the vector to test with this
                         * @return the test's result
                         */
                        bool operator <=(Derived const& it) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return it.distanceTo(this->impl()) <= 0;
                        }
                        /**
                         * Superior or Equal test between this and it
                         * @param it the vector to test with this
                         * @return the test's result
                         */
                        bool operator >=(Derived const& it) const requires Concept::DerivedFrom<Category, RandomAccessIteratorCategory> {
                            return it.distanceTo(this->impl()) >= 0;
                        }
            };
            
        }
    }