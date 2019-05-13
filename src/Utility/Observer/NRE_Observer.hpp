
    /**
     * @file NRE_Observer.hpp
     * @brief Declaration of Utility's API's Object : Observer
     * @author Louis ABEL
     * @date 13/05/2019
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

            class Observable;

            /**
             * @class Observer
             * @brief Describe an observer object attached to an Observable
             */
            class Observer {
                public:    // Methods
                    //## Deconstructor ##//
                        /**
                         * Observer Deconstructor
                         */
                        virtual ~Observer() = default;

                    //## Methods ##//
                        /**
                         * Update the observer when the observable notify it
                         * @param obs the observable
                         * @param arg notification data
                         */
                        virtual void update(Observable* obs, void* arg) = 0;
            };
        }
    }
