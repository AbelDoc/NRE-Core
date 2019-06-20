
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
                observers.push_back(o);
            }

            inline void Observable::remove(Observer* o) {
                observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
            }

            inline void Observable::clear() {
                observers.clear();
            }

            inline std::size_t Observable::getCount() const {
                return observers.size();
            }

            inline void Observable::notifyAll(void* arg) {
                if (isChanged()) {
                    setChanged(false);
                    for (Observer* o : observers) {
                        o->update(this, arg);
                    }
                }
            }

            inline std::vector<Observer*>::iterator Observable::begin() {
                return observers.begin();
            }

            inline std::vector<Observer*>::const_iterator Observable::begin() const {
                return observers.begin();
            }

            inline std::vector<Observer*>::iterator Observable::end() {
                return observers.end();
            }

            inline std::vector<Observer*>::const_iterator Observable::end() const {
                return observers.end();
            }

            inline void Observable::setChanged(bool state) {
                changed = state;
            }


        }
    }
