
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
                private:    //Fields
                    bool changed;                      /**< Tell if changes had happened */
                    std::vector<Observer*> observers;  /**< All registered observers */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Observable() = default;

                    //## Copy-Constructor ##//
                        /**
                         * Copy o into this
                         * @param o the observable to copy
                         */
                        inline Observable(Observable const& o) : changed(o.changed), observers(o.observers) {
                        }

                    //## Move-Constructor ##//
                        /**
                         * Move o into this
                         * @param o the observable to move
                         */
                        inline Observable(Observable && o) : changed(std::move(o.changed)), observers(std::move(o.observers)) {
                        }

                    //## Deconstructor ##//
                        /**
                         * Observable Deconstructor
                         */
                        virtual ~Observable() = default;

                    //## Getter ##//
                        /**
                         * @return the changed state
                         */
                        inline bool const& isChanged() const {
                            return changed;
                        }

                    //## Methods ##//
                        /**
                         * Add an observer
                         * @param o the observer to add
                         */
                        inline void addObserver(Observer* o) {
                            observers.push_back(o);
                        }
                        /**
                         * Remove an observer
                         * @param o the observer to add
                         */
                        inline void removeObserver(Observer* o) {
                            observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
                        }
                        /**
                         * Remoev all observers
                         */
                        inline void removeObservers() {
                            observers.clear();
                        }
                        /**
                         * @return the number of observer
                         */
                        inline std::size_t countObservers() const {
                            return observers.size();
                        }
                        /**
                         * Notify all observer if changes happened
                         * @param arg the notification argument
                         */
                        inline void notifyObservers(void* arg = 0) {
                            if (isChanged()) {
                                setChanged(false);
                                for (Observer* o : observers) {
                                    o->update(this, arg);
                                }
                            }
                        }

                    //## Access Operator ##//
                        /**
                         * @return an iterator on the first element
                         */
                        inline std::vector<Observer*>::iterator begin() {
                            return observers.begin();
                        }
                        /**
                         * @return a const iterator on the first element
                         */
                        inline std::vector<Observer*>::const_iterator begin() const {
                            return observers.begin();
                        }
                        /**
                         * @return an iterator on the end of the container
                         */
                        inline std::vector<Observer*>::iterator end() {
                            return observers.end();
                        }
                        /**
                         * @return a const iterator on the end of the container
                         */
                        inline std::vector<Observer*>::const_iterator end() const {
                            return observers.end();
                        }

                    //## Assignment Operator ##//
                        /**
                         * Copy o into this
                         * @param o the observable to copy into this
                         * @return  the reference of himself
                         */
                        inline Observable& operator =(Observable const& o) = default;
                        /**
                         * Move o into this
                         * @param o the observable to move into this
                         * @return  the reference of himself
                         */
                        inline Observable& operator =(Observable && o) = default;

                protected: // Methods
                    /**
                     * Changed setter
                     * @param state the new changed state
                     */
                    inline void setChanged(bool state) {
                        changed = state;
                    }
            };
        }
    }
