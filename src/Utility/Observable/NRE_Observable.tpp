
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

            inline typename Observable::SizeType Observable::getCount() const {
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

            inline typename Observable::Iterator Observable::begin() {
                return observers.begin();
            }

            inline typename Observable::ConstIterator Observable::begin() const {
                return observers.begin();
            }

            inline typename Observable::ConstIterator Observable::cbegin() const {
                return observers.cbegin();
            }

            inline typename Observable::Iterator Observable::end() {
                return observers.end();
            }

            inline typename Observable::ConstIterator Observable::end() const {
                return observers.end();
            }

            inline typename Observable::ConstIterator Observable::cend() const {
                return observers.cend();
            }

            inline void Observable::setChanged(bool state) {
                changed = state;
            }

        }
    }
