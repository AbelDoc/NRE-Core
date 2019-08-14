
    /**
     * @file NRE_Singleton.hpp
     * @brief Declaration of Utility's API's Object : Singleton
     * @author Louis ABEL
     * @date 14/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

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
             * @class Singleton
             * @brief Describe a singleton object
             */
            template <class T>
            class Singleton {
                friend T;
                public :    // Methods
                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param s the singleton to copy
                         */
                        Singleton(Singleton const& s) = delete;

                    //## Assignment Operator ##//
                        /**
                         * Copy forbidden
                         * @param s the singleton to copy
                         */
                        Singleton& operator=(Singleton const& s) = delete;

                protected: // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Singleton() = default;

                    //## Deconstructor ##//
                        /**
                         * Singleton Deconstructor
                         */
                        ~Singleton() = default;


                public:     // Static
                    /**
                     * Access function
                     * @return the static singleton
                     */
                    static T& get();

            };
        }
    }

    #include "NRE_Singleton.tpp"
