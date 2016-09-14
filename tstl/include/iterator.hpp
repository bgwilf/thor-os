//=======================================================================
// Copyright Baptiste Wicht 2013-2016.
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://www.opensource.org/licenses/MIT)
//=======================================================================

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <type_traits.hpp>
#include <utility.hpp>
#include <types.hpp>
#include <enable_if.hpp>

namespace std {

template <typename Iterator>
size_t distance(Iterator it, Iterator end) {
    // For now, we only have random access iterator
    return end - it;
}

template <typename Iterator>
struct reverse_iterator {
    using iterator_type   = Iterator;
    using value_type      = typename std::iterator_traits<Iterator>::value_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using pointer         = typename std::iterator_traits<Iterator>::pointer;
    using reference       = typename std::iterator_traits<Iterator>::reference;

    reverse_iterator(Iterator it)
            : it(it) {
        //Nothing else
    }

    reference operator*() {
        return *it;
    }

    reverse_iterator& operator++() {
        --it;
        return *this;
    }

    reverse_iterator& operator--() {
        ++it;
        return *this;
    }

    bool operator==(const reverse_iterator& rhs) {
        return it == rhs.it;
    }

    bool operator!=(const reverse_iterator& rhs) {
        return it != rhs.it;
    }

private:
    iterator_type it;
};

template <typename Container>
struct back_insert_iterator {
    using container_type  = Container;
    using value_type      = void;
    using difference_type = void;
    using reference       = void;
    using const_reference = void;

    container_type& container;

    explicit back_insert_iterator(container_type& container)
            : container(container) {}

    back_insert_iterator& operator=(const typename container_type::value_type& value) {
        container.push_back(value);

        return *this;
    }

    back_insert_iterator& operator=(typename container_type::value_type&& value) {
        container.push_back(std::move(value));

        return *this;
    }

    back_insert_iterator& operator*() {
        return *this;
    }

    back_insert_iterator& operator++() {
        return *this;
    }

    back_insert_iterator& operator++(int) {
        return *this;
    }
};

template <typename Container>
struct front_insert_iterator {
    using container_type  = Container;
    using value_type      = void;
    using difference_type = void;
    using reference       = void;
    using const_reference = void;

    container_type& container;

    explicit front_insert_iterator(container_type& container)
            : container(container) {}

    front_insert_iterator& operator=(const typename container_type::value_type& value) {
        container.push_front(value);

        return *this;
    }

    front_insert_iterator& operator=(typename container_type::value_type&& value) {
        container.push_front(std::move(value));

        return *this;
    }

    front_insert_iterator& operator*() {
        return *this;
    }

    front_insert_iterator& operator++() {
        return *this;
    }

    front_insert_iterator& operator++(int) {
        return *this;
    }
};

template <typename Container>
std::back_insert_iterator<Container> back_inserter(Container& c) {
    return std::back_insert_iterator<Container>(c);
}

template <typename Container>
std::front_insert_iterator<Container> front_inserter(Container& c) {
    return std::front_insert_iterator<Container>(c);
}

} //end of namespace std

#endif
