
    /**
     * @file NRE_Singleton.tpp
     * @brief Implementation of Utility's API's Object : Singleton
     * @author Louis ABEL
     * @date 14/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Utility {

            template <class T>
            inline T& Singleton<T>::get() {
                static T instance;
                return instance;
            }

        }
    }
