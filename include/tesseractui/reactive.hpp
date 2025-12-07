#pragma once

#include <tesseractui/signals.hpp>

namespace tesseractui {
    template<typename T>
    class Observable {
        public:
        Observable(const T& initial) : m_value(initial) {}

        void set(const T& value) {
            if (m_value != value) {
                m_value = value;
                onChange.emit(m_value);
            }
        }

        const T& get() const { return m_value; }
        Signal<T> onChange;

        private:
            T m_value;
    };
} // namespace tesseractui
