
    /**
     * @file NRE_Observer.hpp
     * @brief Declaration of Core's API's Object : Observer
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
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {

            class Observable;

            /**
             * @class Observer
             * @brief Describe an observer object attached to an Observable
             */
            class Observer {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Observer() = default;
    
                    //## Copy-Constructor ##//
                        /**
                         * Copy o into this
                         * @param o the observer to copy
                         */
                        Observer(Observer const& o) = default;
        
                    //## Move-Constructor ##//
                        /**
                         * Move o into this
                         * @param o the observer to move
                         */
                        Observer(Observer && o) = default;
                        
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
    
                    //## Assignment Operator ##//
                        /**
                         * Copy o into this
                         * @param o the observer to copy into this
                         * @return  the reference of himself
                         */
                        Observer& operator =(Observer const& o) = default;
                        /**
                         * Move o into this
                         * @param o the observer to move into this
                         * @return  the reference of himself
                         */
                        Observer& operator =(Observer && o) = default;
            };
        }
    }
