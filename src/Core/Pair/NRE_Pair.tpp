
    /**
     * @file NRE_Pair.tpp
     * @brief Implementation of Core's API's Object : Pair
     * @author Louis ABEL
     * @date 23/06/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Core {

             template <class T, class K>
             constexpr Pair<T, K>::Pair() : first(), second() {
             }

             template <class T, class K>
             inline Pair<T, K>::Pair(T const& x, K const& y) : first(x), second(y) {
             }

             template <class T, class K>
             template <class T2, class K2>
             inline Pair<T, K>::Pair(T2 && x, K2 && y) : first(std::forward<T2>(x)), second(std::forward<K2>(y)) {
             }

             template <class T, class K>
             template <class T2, class K2>
             inline Pair<T, K>::Pair(Pair<T2, K2> const& p) : first(p.first), second(p.second) {
             }

             template <class T, class K>
             template <class T2, class K2>
             inline Pair<T, K>::Pair(Pair<T2, K2> && p) : first(std::move(p.first)), second(std::move(p.second)) {
             }

             template <class T, class K>
             inline void Pair<T, K>::swap(Pair& p) {
                 using std::swap;
                 swap(first, p.first);
                 swap(second, p.second);
             }

             template <class T, class K>
             template <class T2, class K2>
             inline Pair<T, K>& Pair<T, K>::operator=(Pair<T2, K2> const& p) {
                 first = p.first;
                 second = p.second;
                 return *this;
             }

             template <class T, class K>
             template <class T2, class K2>
             inline Pair<T, K>& Pair<T, K>::operator=(Pair<T2, K2> && p) {
                 first = std::forward<T2>(p.first);
                 second = std::forward<K2>(p.second);
                 return *this;
             }

             template <class T, class K>
             inline bool Pair<T, K>::operator==(Pair const& p) const {
                 return first == p.first && second == p.second;
             }

             template <class T, class K>
             inline bool Pair<T, K>::operator!=(Pair const& p) const {
                 return !(*this == p);
             }

             template <class T, class K>
             inline bool Pair<T, K>::operator<(Pair const& p) const {
                 return first < p.first || (!(p.first < first) && second < p.second);
             }

             template <class T, class K>
             inline bool Pair<T, K>::operator<=(Pair const& p) const {
                 return !(p < *this);
             }

             template <class T, class K>
             inline bool Pair<T, K>::operator>(Pair const& p) const {
                 return p < *this;
             }

             template <class T, class K>
             inline bool Pair<T, K>::operator>=(Pair const& p) const {
                 return !(*this < p);
             }

             template <class T, class K>
             inline String Pair<T, K>::toString() const {
                 String res;
                 res << '(' << first << ',' << ' ' << second << ')';
                 return res;
             }

         }
     }
