
    /**
     * @file NRE_Observable.cpp
     * @brief Test of Utility's API's Object : Observable
     * @author Louis ABEL
     * @date 20/06/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Utility.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Utility;
    using namespace NRE::Tester;

    struct ObserverImpl : public Observer {
        bool notified = false;
        void update(Observable*, void*) override {
            notified = true;
        }
    };

    struct ObservableImpl : public Observable {
        void update() {
            setChanged(true);
            notifyAll();
        }
    };

    TEST(Observable, Copy) {
        Observable obs;
        ObserverImpl o1, o2;
        obs.add(&o1);
        obs.add(&o2);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
        Observable copy(obs);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
        assertEquals(this, copy.getCount(), static_cast <std::size_t> (2));
        copy.remove(&o1);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
        assertEquals(this, copy.getCount(), static_cast <std::size_t> (1));
    }

    TEST(Observable, Move) {
        Observable obs;
        ObserverImpl o1, o2;
        obs.add(&o1);
        obs.add(&o2);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
        Observable move(std::move(obs));
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (0));
        assertEquals(this, move.getCount(), static_cast <std::size_t> (2));
    }

    TEST(Observable, Changed) {
        Observable obs;
        assertFalse(this, obs.isChanged());
    }

    TEST(Observable, Add) {
        Observable obs;
        ObserverImpl o1;
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (0));
        obs.add(&o1);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (1));
    }

    TEST(Observable, Remove) {
        Observable obs;
        ObserverImpl o1, o2;
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (0));
        obs.add(&o1);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (1));
        obs.remove(&o2);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (1));
        obs.remove(&o1);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (0));
    }

    TEST(Observable, Clear) {
        Observable obs;
        ObserverImpl o1, o2;
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (0));
        obs.add(&o1);
        obs.add(&o2);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
        obs.clear();
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (0));
    }

    TEST(Observable, Count) {
        Observable obs;
        ObserverImpl o1, o2;
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (0));
        obs.add(&o1);
        obs.add(&o2);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
    }

    TEST(Observable, NotifyAll) {
        ObservableImpl obs;
        ObserverImpl o1, o2;
        assertFalse(this, o1.notified);
        assertFalse(this, o2.notified);
        obs.update();
        assertFalse(this, o1.notified);
        assertFalse(this, o2.notified);
        obs.add(&o1);
        obs.add(&o2);
        obs.update();
        assertTrue(this, o1.notified);
        assertTrue(this, o2.notified);
    }

    TEST(Observable, Begin) {
        Observable obs;
        ObserverImpl o1;
        obs.add(&o1);
        assertEquals(this, *(obs.begin()), static_cast <Observer*> (&o1));
    }

    TEST(Observable, End) {
        Observable obs;
        ObserverImpl o1;
        obs.add(&o1);
        assertEquals(this, *(obs.end() - 1), static_cast <Observer*> (&o1));
    }

    TEST(Observable, AssignCopy) {
        Observable obs;
        ObserverImpl o1, o2;
        obs.add(&o1);
        obs.add(&o2);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
        Observable copy;
        assertEquals(this, copy.getCount(), static_cast <std::size_t> (0));
        copy = obs;
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
        assertEquals(this, copy.getCount(), static_cast <std::size_t> (2));
    }

    TEST(Observable, AssignMove) {
        Observable obs;
        ObserverImpl o1, o2;
        obs.add(&o1);
        obs.add(&o2);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (2));
        Observable copy;
        assertEquals(this, copy.getCount(), static_cast <std::size_t> (0));
        copy = std::move(obs);
        assertEquals(this, obs.getCount(), static_cast <std::size_t> (0));
        assertEquals(this, copy.getCount(), static_cast <std::size_t> (2));
    }
