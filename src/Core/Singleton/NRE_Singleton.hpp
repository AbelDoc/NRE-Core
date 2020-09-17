
    /**
     * @file NRE_Singleton.hpp
     * @brief Declaration of Core's API's Object : Singleton
     * @author Louis ABEL
     * @date 14/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../Interfaces/Uncopyable/NRE_Uncopyable.hpp"

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
             * @class Singleton
             * @brief Describe a singleton object
             */
            template <class T>
            class Singleton : public Uncopyable<Singleton<T>> {
                friend T;
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
