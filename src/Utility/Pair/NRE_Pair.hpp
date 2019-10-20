
    /**
     * @file NRE_Pair.hpp
     * @brief Declaration of Utility's API's Object : Pair
     * @author Louis ABEL
     * @date 23/06/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../String/NRE_String.hpp"
    #include "../Interfaces/Stringable/NRE_Stringable.hpp"

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
             * @class Pair
             * @brief A basic template pair
             */
            template <class T, class K>
            class Pair : public Stringable<Pair<T, K>> {
                public :   // Fields
                    T first;    /**< The first object */
                    K second;   /**< The second object */

                public :    // Methods
                    //## Conpuctor ##//
                        /**
                         * Conpuct the pair with default values
                         */
                        constexpr Pair();
                        /**
                         * Conpuct the pair with x and y
                         * @param x the first object
                         * @param y the second object
                         */
                        Pair(T const& x, K const& y);
                        /**
                         * Conpuct the pair while forwarding given elements
                         * @param x the first object
                         * @param y the second object
                         */
                        template <class T2, class K2>
                        Pair(T2 && x, K2 && y);

                    //## Copy Conpuctor ##//
                        /**
                         * Copy p into this
                         * @param  p the pair to copy
                         */
                        Pair(Pair const& p) = default;
                        /**
                         * Conpuct the pair using the given pair
                         * @param p the pair to initialize this
                         */
                        template <class T2, class K2>
                        Pair(Pair<T2, K2> const& p);

                    //## Move Conpuctor ##//
                        /**
                         * Move p into this
                         * @param  p the pair to move
                         */
                        Pair(Pair && p) = default;
                        /**
                         * Conpuct the pair by moving the given pair elements
                         * @param p the pair to move
                         */
                        template <class T2, class K2>
                        Pair(Pair<T2, K2> && p);

                    //## Deconpuctor ##//
                        /**
                         * Pair Deconpuctor
                         */
                        ~Pair() = default;

                    //## Methods ##//
                        /**
                         * Swap the pair with another pair
                         * @param p the other pair
                         */
                        void swap(Pair& p);

                    //## Assignment Operator ##//
                        /**
                         * Copy p into this
                         * @param p the pair to copy into this
                         * @return  the reference of himself
                         */
                        Pair& operator =(Pair const& p) = default;
                        /**
                         * Copy p into this
                         * @param p the pair to copy into this
                         * @return  the reference of himself
                         */
                        template <class T2, class K2>
                        Pair& operator =(Pair<T2, K2> const& p);
                        /**
                         * Move p into this
                         * @param p the pair to move into this
                         * @return    the reference of himself
                         */
                        Pair& operator =(Pair && p) = default;
                        /**
                         * Move p into this by forwarding it
                         * @param p the pair to move into this
                         * @return  the reference of himself
                         */
                        template <class T2, class K2>
                        Pair& operator =(Pair<T2, K2> && p);

                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and p
                         * @param p the other pair to compare with this
                         * @return    the test result
                         */
                        bool operator==(Pair const& p) const;
                        /**
                         * Inequality test between this and p
                         * @param p the other pair to compare with this
                         * @return    the test result
                         */
                        bool operator!=(Pair const& p) const;
                        /**
                         * Inferiority test between this and p
                         * @param p the other pair to compare with this
                         * @return    the test result
                         */
                        bool operator<(Pair const& p) const;
                        /**
                         * Inferior or Equal test between this and p
                         * @param p the other pair to compare with this
                         * @return    the test result
                         */
                        bool operator<=(Pair const& p) const;
                        /**
                         * Superiority test between this and p
                         * @param p the other pair to compare with this
                         * @return    the test result
                         */
                        bool operator>(Pair const& p) const;
                        /**
                         * Superior or Equal or Equal test between this and p
                         * @param p the other pair to compare with this
                         * @return    the test result
                         */
                        bool operator>=(Pair const& p) const;

                    //## Stream Operator ##//
                        /**
                         * Convert the object into a string representation
                         * @return the converted object
                         */
                        String toString() const;

            };
        }
    }

    #include "NRE_Pair.tpp"
