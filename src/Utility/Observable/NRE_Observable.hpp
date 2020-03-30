
    /**
     * @file NRE_Observable.hpp
     * @brief Declaration of Utility's API's Object : Observable
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <vector>
    #include <algorithm>

    #include "../Observer/NRE_Observer.hpp"
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
             * @class Observable
             * @brief Describe an observable object, coupled with observer
             */
            class Observable {
                public:     //Traits
                    /** The observers container */
                    using Container     = Vector<Observer*>;
                    /** The observers iterator */
                    using Iterator      = typename Container::Iterator;
                    /** The observers const iterator */
                    using ConstIterator = typename Container::ConstIterator;
                    /** The observable size type */
                    using SizeType      = typename Container::SizeType;
                    
                private:    //Fields
                    bool changed;         /**< Tell if changes had happened */
                    Container observers;  /**< All registered observers */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Observable();

                    //## Copy-Constructor ##//
                        /**
                         * Copy o into this
                         * @param o the observable to copy
                         */
                        Observable(Observable const& o) = default;

                    //## Move-Constructor ##//
                        /**
                         * Move o into this
                         * @param o the observable to move
                         */
                        Observable(Observable && o) = default;

                    //## Deconstructor ##//
                        /**
                         * Observable Deconstructor
                         */
                        virtual ~Observable() = default;

                    //## Getter ##//
                        /**
                         * @return the changed state
                         */
                        bool isChanged() const;

                    //## Methods ##//
                        /**
                         * Add an observer
                         * @param o the observer to add
                         */
                        void add(Observer* o);
                        /**
                         * Remove an observer
                         * @param o the observer to add
                         */
                        void remove(Observer* o);
                        /**
                         * Remove all observers
                         */
                        void clear();
                        /**
                         * @return the number of observer
                         */
                        SizeType getCount() const;
                        /**
                         * Notify all observer if changes happened
                         * @param arg the notification argument
                         */
                        void notifyAll(void* arg = 0);

                    //## Access Operator ##//
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

                    //## Assignment Operator ##//
                        /**
                         * Copy o into this
                         * @param o the observable to copy into this
                         * @return  the reference of himself
                         */
                        Observable& operator =(Observable const& o) = default;
                        /**
                         * Move o into this
                         * @param o the observable to move into this
                         * @return  the reference of himself
                         */
                        Observable& operator =(Observable && o) = default;

                protected: // Methods
                    /**
                     * Changed setter
                     * @param state the new changed state
                     */
                    void setChanged(bool state);
            };
        }
    }

    #include "NRE_Observable.tpp"
