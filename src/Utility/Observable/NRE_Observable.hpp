
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
             * @pure Observable
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
                         * @param o the observable to copy the content
                         */
                        Observable(Observable const& o) : changed(o.changed), observers(o.observers) {
                        }

                    //## Move-Constructor ##//
                        /**
                         * Move o into this, leaving o empty
                         * @param o the observable to move
                         */
                        Observable(Observable && o) : changed(std::move(o.changed)), observers(std::move(o.observers)) {
                        }

                    //## Deconstructor ##//
                        /**
                         * Observable Deconstructor
                         */
                        virtual ~Observable() = default;

                    //## Getter ##//
                        /**
                         * Changed getter
                         * @return the changed state
                         */
                        bool const& isChanged() const {
                            return changed;
                        }

                    //## Methods ##//
                        /**
                         * Add an observer
                         * @param o the observer to add
                         */
                        void addObserver(Observer* o) {
                            observers.push_back(o);
                        }
                        /**
                         * Remove an observer
                         * @param o the observer to add
                         */
                        void removeObserver(Observer* o) {
                            observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
                        }
                        /**
                         * Remoev all observers
                         */
                        void removeObservers() {
                            observers.clear();
                        }
                        /**
                         * Count all observers
                         * @return the number of observer
                         */
                        std::size_t countObservers() const {
                            return observers.size();
                        }
                        /**
                         * Notify all observer if changes happened
                         * @param arg the notification argument
                         */
                        void notifyObservers(void* arg = 0) {
                            if (isChanged()) {
                                setChanged(false);
                                for (Observer* o : observers) {
                                    o->update(this, arg);
                                }
                            }
                        }

                    //## Access Operator ##//
                        /**
                         * Begin iterator
                         * @return an iterator on the observers
                         */
                        std::vector<Observer*>::iterator begin() {
                            return observers.begin();
                        }
                        /**
                         * Begin iterator
                         * @return a const iterator on the observers
                         */
                        std::vector<Observer*>::const_iterator begin() const {
                            return observers.begin();
                        }
                        /**
                         * End iterator
                         * @return an iterator on the observers
                         */
                        std::vector<Observer*>::iterator end() {
                            return observers.end();
                        }
                        /**
                         * End iterator
                         * @return a const iterator on the observers
                         */
                        std::vector<Observer*>::const_iterator end() const {
                            return observers.end();
                        }

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of o into this
                         * @param o the observable to copy into this
                         * @return      the reference of himself
                         */
                        Observable& operator =(Observable const& o) {
                            changed = o.changed;
                            observers = o.observers;
                            return *this;
                        }
                        /**
                         * Move assignment of o into this, leaving o empty
                         * @param o the observable to move into this
                         * @return      the reference of himself
                         */
                        Observable& operator =(Observable && o) {
                            changed = std::move(o.changed);
                            observers = std::move(o.observers);
                            return *this;
                        }

                protected: // Methods
                    /**
                     * Changed setter
                     * @param state the new changed state
                     */
                    void setChanged(bool state) {
                        changed = state;
                    }
            };
        }
    }
