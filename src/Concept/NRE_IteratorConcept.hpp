    
    /**
     * @file NRE_IteratorConcept.hpp
     * @brief Declaration of Utility's API's Concept
     * @author Louis ABEL
     * @date 15/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../Utility/Traits/NRE_IteratorTraits.hpp"
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Concept
         * @brief Concept's API
         */
        namespace Concept {
            namespace Detail {
                /**
                 * @interface IndirectlyReadable
                 * @brief Define an indirectly readable type through operator* like pointer or input iterator
                 */
                template <class T>
                concept IndirectlyReadable = requires (const T t) {
                    typename Utility::IteratorValueT<T>;
                    typename Utility::IteratorReferenceT<T>;
                    typename Utility::IteratorRValueReferenceT<T>;
                    { *t } -> SameAs<Utility::IteratorReferenceT<T>>;
                    { std::ranges::iter_move(t) } -> SameAs<Utility::IteratorRValueReferenceT<T>>;
                } && CommonReferenceWith<Utility::IteratorReferenceT<T>&&, Utility::IteratorValueT<T>&>
                  && CommonReferenceWith<Utility::IteratorReferenceT<T>&&, Utility::IteratorRValueReferenceT<T>&&>
                  && CommonReferenceWith<Utility::IteratorReferenceT<T>&&, Utility::IteratorValueT<T> const&>;
            }
            
            /**
             * @interface IndirectlyReadable
             * @brief Define an indirectly readable type through operator* like pointer or input iterator
             */
            template <class T>
            concept IndirectlyReadable = Detail::IndirectlyReadable<Utility::RemoveCVReferenceT<T>>;
            
        }
        /**
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
            /** Compute the common reference between the the reference type and a reference on the value type of a given type */
            template <Concept::IndirectlyReadable T>
            using IteratorCommonReferenceT = CommonReferenceT<IteratorReferenceT<T>, IteratorValueT<T>&>;
        }
    }