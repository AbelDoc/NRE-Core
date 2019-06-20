
    /**
     * @file NRE_Observable.tpp
     * @brief Implementation of Utility's API's Object : Observable
     * @author Louis ABEL
     * @date 16/05/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Utility {

            inline Observable::Observable() : changed(false) {
            }

            inline bool Observable::isChanged() const {
                return changed;
            }

            inline void Observable::add(Observer* o) {
                observers.pushBack(o);
            }

            inline void Observable::remove(Observer* o) {
                observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
            }

            inline void Observable::clear() {
                observers.clear();
            }

            inline std::size_t Observable::getCount() const {
                return observers.getSize();
            }

            inline void Observable::notifyAll(void* arg) {
                if (isChanged()) {
                    setChanged(false);
                    for (Observer* o : observers) {
                        o->update(this, arg);
                    }
                }
            }

            inline Vector<Observer*>::Iterator Observable::begin() {
                return observers.begin();
            }

            inline Vector<Observer*>::ConstIterator Observable::begin() const {
                return observers.begin();
            }

            inline Vector<Observer*>::ConstIterator Observable::cbegin() const {
                return observers.cbegin();
            }

            inline Vector<Observer*>::Iterator Observable::end() {
                return observers.end();
            }

            inline Vector<Observer*>::ConstIterator Observable::end() const {
                return observers.end();
            }

            inline Vector<Observer*>::ConstIterator Observable::cend() const {
                return observers.cend();
            }

            inline void Observable::setChanged(bool state) {
                changed = state;
            }

        }
    }
