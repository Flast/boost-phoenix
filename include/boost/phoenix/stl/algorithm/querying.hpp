// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2005 Dan Marsden.
// Copyright 2008 Hartmut Kaiser.
// Copyright 2015 John Fletcher.
// Copyright 2017 Kohei Takahashi.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_QUERYING_HPP
#define BOOST_PHOENIX_ALGORITHM_QUERYING_HPP

#include <algorithm>

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_find.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_lower_bound.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_upper_bound.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_equal_range.hpp>

#include <boost/phoenix/stl/algorithm/detail/begin.hpp>
#include <boost/phoenix/stl/algorithm/detail/end.hpp>
#include <boost/phoenix/stl/algorithm/detail/decay_array.hpp>

#include <boost/phoenix/function/adapt_callable.hpp>

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/difference_type.hpp>

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX14_ALGORITHMS
#include <boost/core/enable_if.hpp>
#endif

namespace boost { namespace phoenix {
    namespace impl
    {
        struct find
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& x, mpl::true_) const
            {
                return r.find(x);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& x, mpl::false_) const
            {
                return std::find(detail::begin_(r), detail::end_(r), x);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& x) const
            {
                return execute(r, x, has_find<R>());
            }
        };

        struct find_if
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::find_if(detail::begin_(r), detail::end_(r), p);
            }
        };

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX11_ALGORITHMS
        struct find_if_not
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::find_if_not(detail::begin_(r), detail::end_(r), p);
            }
        };
#endif

        struct find_end
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template<typename This, class R, class R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::find_end(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::find_end(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }
        };

        struct find_first_of
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template<typename This, class R, class R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::find_first_of(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::find_first_of(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }
        };

        struct adjacent_find
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::adjacent_find(detail::begin_(r), detail::end_(r));
            }

            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::adjacent_find(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct count
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_difference<R>
            {};

            template<class R, class T>
            typename range_difference<R>::type
            operator()(R& r, T const& x) const
            {
                return std::count(detail::begin_(r), detail::end_(r), x);
            }
        };

        struct count_if
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_difference<R>
            {};

            template<class R, class P>
            typename range_difference<R>::type
            operator()(R& r, P p) const
            {
                return std::count_if(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct distance
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_difference<R>
            {};

            template<class R>
            typename range_difference<R>::type
            operator()(R& r) const
            {
                return std::distance(detail::begin_(r), detail::end_(r));
            }
        };

        struct equal
        {
            typedef bool result_type;

            template<class R, class I>
            bool operator()(R& r, I i) const
            {
                return std::equal(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class P>
            bool operator()(R& r, I i, P p) const
            {
                return std::equal(detail::begin_(r), detail::end_(r), i, p);
            }

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX14_ALGORITHMS
            template<class R, class R2>
            typename boost::enable_if_has_type<typename range_iterator<R2>::type, bool>::type
            operator()(R& r, R2& r2) const
            {
                return std::equal(detail::begin_(r), detail::end_(r)
                                , detail::begin_(r2), detail::end_(r2));
            }

            template<class R, class R2, class P>
            typename boost::enable_if_has_type<typename range_iterator<R2>::type, bool>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::equal(detail::begin_(r), detail::end_(r)
                                , detail::begin_(r2), detail::end_(r2)
                                , p);
            }
#endif
        };

        struct search
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, typename R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template <typename This, class R, typename R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::search(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::search(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX17_ALGORITHMS
            // At this point, we assume all features of C++11 are avaiable.
            template<class R, class S, class I = typename range_iterator<R>::type>
            auto operator()(R& r, const S& s) const
                -> typename boost::enable_if_has_type<decltype(s(std::declval<I>(), std::declval<I>())), I>::type
            {
                return std::search(
                    detail::begin_(r)
                    , detail::end_(r)
                    , s
                    );
            }
#endif
        };

        struct lower_bound 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.lower_bound(val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::lower_bound(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_lower_bound<R>());
            }

            template<class R, class T, class C>
            typename range_iterator<R>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::lower_bound(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        struct upper_bound 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.upper_bound(val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::upper_bound(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_upper_bound<R>());
            }

            template<class R, class T, class C>
            typename range_iterator<R>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::upper_bound(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        namespace result_of
        {
            template <typename R, typename T, typename C = void>
            struct equal_range
            {
                typedef std::pair<
                    typename range_iterator<R>::type
                    , typename range_iterator<R>::type
                > type;
            };
        }

        struct equal_range 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : result_of::equal_range<R,T>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : result_of::equal_range<R,T, C>
            {};

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.equal_range(val);
            }

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::equal_range(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_equal_range<R>());
            }

            template<class R, class T, class C>
            typename result_of::equal_range<R, T, C>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::equal_range(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        namespace result_of
        {
            template <typename R, typename I, typename P = void, typename = void>
            struct mismatch
            {
                typedef std::pair<
                    typename range_iterator<R>::type
                    , typename detail::decay_array<I>::type
                > type;
            };

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX14_ALGORITHMS
            template <typename R, typename R2, typename P>
            struct mismatch<R, R2, P,
                typename boost::enable_if_has_type<typename range_iterator<R2>::type>::type>
            {
                typedef std::pair<
                    typename range_iterator<R>::type
                    , typename range_iterator<R2>::type
                > type;
            };
#endif
        }

        struct mismatch
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class I>
            struct result<This(R&, I)>
                : result_of::mismatch<R, I>
            {};

            template<typename This, class R, class I, class P>
            struct result<This(R&, I, P)>
                : result_of::mismatch<R, I, P>
            {};

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX14_ALGORITHMS
            template<typename This, class R, class R2>
            struct result<This(R&, R2&)>
                : result_of::mismatch<R1, R2>
            {};

            template<typename This, class R, class R2, class P>
            struct result<This(R&, R2&, P)>
                : result_of::mismatch<R, R2, P>
            {};
#endif

            template<class R, class I>
            typename result_of::mismatch<R, I>::type
            operator()(R& r, I i) const
            {
                return std::mismatch(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class P>
            typename result_of::mismatch<R, I, P>::type
            operator()(R& r, I i, P p) const
            {
                return std::mismatch(detail::begin_(r), detail::end_(r), i, p);
            }

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX14_ALGORITHMS
            template<class R, class R2>
            typename result_of::mismatch<R, R2>::type
            operator()(R& r, R2& r2) const
            {
                return std::mismatch(detail::begin_(r), detail::end_(r)
                                    , detail::begin_(r2), detail::end_(r2));
            }

            template<class R, class R2, class P>
            typename result_of::mismatch<R, R2, P>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::mismatch(detail::begin_(r), detail::end_(r)
                                    , detail::begin_(r2), detail::end_(r2)
                                    , p);
            }
#endif
        };

        struct binary_search 
        {
            typedef bool result_type;

            template<class R, class T>
            bool operator()(R& r, T const& val) const
            {
                return std::binary_search(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T, class C>
            bool operator()(R& r, T const& val, C c) const
            {
                return std::binary_search(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        struct includes 
        {
            typedef bool result_type;

            template<class R1, class R2>
            bool operator()(R1& r1, R2& r2) const
            {
                return std::includes(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    );
            }

            template<class R1, class R2, class C>
            bool operator()(R1& r1, R2& r2, C c) const
            {
                return std::includes(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    , c
                    );
            }
        };

        struct min_element
        {
            template <typename Sig>
            struct result;
            
            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::min_element(detail::begin_(r), detail::end_(r));
            }
        
            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::min_element(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct max_element
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::max_element(detail::begin_(r), detail::end_(r));
            }
        
            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::max_element(detail::begin_(r), detail::end_(r), p);
            }
        };

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX11_ALGORITHMS
        namespace result_of
        {
            template <typename R, typename C = void>
            struct minmax_element
            {
                typedef std::pair<
                    typename range_iterator<R>::type
                    , typename range_iterator<R>::type
                > type;
            };
        }

        struct minmax_element
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : result_of::minmax_element<R>
            {};

            template <typename This, class R, class C>
            struct result<This(R&, C)>
                : result_of::minmax_element<R, C>
            {};

            template<class R>
            typename result_of::minmax_element<R>::type
            operator()(R& r) const
            {
                return std::minmax_element(detail::begin_(r), detail::end_(r));
            }

            template<class R, class C>
            typename result_of::minmax_element<R, C>::type
            operator()(R& r, C c) const
            {
                return std::minmax_element(detail::begin_(r), detail::end_(r), c);
            }
        };
#endif

        struct lexicographical_compare
        {
            typedef bool result_type;

            template<class R1, class R2>
            bool operator()(R1& r1, R2& r2) const
            {
                return std::lexicographical_compare(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    );
            }
        
            template<class R1, class R2, class P>
            bool operator()(R1& r1, R2& r2, P p) const
            {
                return std::lexicographical_compare(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    , p
                    );
            }
        };

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX11_ALGORITHMS
        struct is_partitioned
        {
            typedef bool result_type;

            template<class R, class P>
            bool operator()(R& r, P p) const
            {
                return std::is_partitioned(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct is_sorted
        {
            typedef bool result_type;

            template<class R>
            bool operator()(R& r) const
            {
                return std::is_sorted(detail::begin_(r), detail::end_(r));
            }

            template<class R, class C>
            bool operator()(R& r, C c) const
            {
                return std::is_sorted(detail::begin_(r), detail::end_(r), c);
            }
        };

        struct is_sorted_until
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class C>
            struct result<This(R&, C)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::is_sorted_until(detail::begin_(r), detail::end_(r));
            }

            template<class R, class C>
            typename range_iterator<R>::type
            operator()(R& r, C c) const
            {
                return std::is_sorted_until(detail::begin_(r), detail::end_(r), c);
            }
        };

        struct is_heap
        {
            typedef bool result_type;

            template<class R>
            bool operator()(R& r) const
            {
                return std::is_heap(detail::begin_(r), detail::end_(r));
            }

            template<class R, class C>
            bool operator()(R& r, C c) const
            {
                return std::is_heap(detail::begin_(r), detail::end_(r), c);
            }
        };

        struct is_heap_until
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class C>
            struct result<This(R&, C)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::is_heap_until(detail::begin_(r), detail::end_(r));
            }

            template<class R, class C>
            typename range_iterator<R>::type
            operator()(R& r, C c) const
            {
                return std::is_heap_until(detail::begin_(r), detail::end_(r), c);
            }
        };

        struct is_permutation
        {
            typedef bool result_type;

            template<class R, class I>
            bool operator()(R& r, I i) const
            {
                return std::is_permutation(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class P>
            bool operator()(R& r, I i, P p) const
            {
                return std::is_permutation(detail::begin_(r), detail::end_(r), i, p);
            }

#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX14_ALGORITHMS
            template<class R, class R2>
            typename boost::enable_if_has_type<typename range_iterator<R2>::type, bool>::type
            bool operator()(R& r, R2& r) const
            {
                return std::is_permutation(detail::begin_(r), detail::end_(r)
                                          , detail::begin_(r2), detail::end_(r2));
            }

            template<class R, class R2, class P>
            typename boost::enable_if_has_type<typename range_iterator<R2>::type, bool>::type
            operator()(R& r, R2& r, P p) const
            {
                return std::is_permutation(detail::begin_(r), detail::end_(r)
                                          , detail::begin_(r2), detail::end_(r2)
                                          , p);
            }
#endif
        };
#endif
    }

    BOOST_PHOENIX_ADAPT_CALLABLE(find, impl::find, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_if, impl::find_if, 2)
#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX11_ALGORITHMS
    BOOST_PHOENIX_ADAPT_CALLABLE(find_if_not, impl::find_if_not, 2)
#endif
    BOOST_PHOENIX_ADAPT_CALLABLE(find_end, impl::find_end, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_end, impl::find_end, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_first_of, impl::find_first_of, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_first_of, impl::find_first_of, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(adjacent_find, impl::adjacent_find, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(adjacent_find, impl::adjacent_find, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(count, impl::count, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(count_if, impl::count_if, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(distance, impl::distance, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal, impl::equal, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal, impl::equal, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(search, impl::search, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(search, impl::search, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(lower_bound, impl::lower_bound, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(lower_bound, impl::lower_bound, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(upper_bound, impl::upper_bound, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(upper_bound, impl::upper_bound, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal_range, impl::equal_range, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal_range, impl::equal_range, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(mismatch, impl::mismatch, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(mismatch, impl::mismatch, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(binary_search, impl::binary_search, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(binary_search, impl::binary_search, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(includes, impl::includes, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(includes, impl::includes, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(min_element, impl::min_element, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(min_element, impl::min_element, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(max_element, impl::max_element, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(max_element, impl::max_element, 2)
#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX11_ALGORITHMS
    BOOST_PHOENIX_ADAPT_CALLABLE(minmax_element, impl::minmax_element, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(minmax_element, impl::minmax_element, 2)
#endif
    BOOST_PHOENIX_ADAPT_CALLABLE(lexicographical_compare, impl::lexicographical_compare, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(lexicographical_compare, impl::lexicographical_compare, 3)
#ifdef BOOST_PHOENIX_EXPERIMENTAL_CXX11_ALGORITHMS
    BOOST_PHOENIX_ADAPT_CALLABLE(is_partitioned, impl::is_partitioned, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_sorted, impl::is_sorted, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_sorted, impl::is_sorted, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_sorted_until, impl::is_sorted_until, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_sorted_until, impl::is_sorted_until, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_heap, impl::is_heap, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_heap, impl::is_heap, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_heap_until, impl::is_heap_until, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_heap_until, impl::is_heap_until, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_permutation, impl::is_permutation, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(is_permutation, impl::is_permutation, 3)
#endif
}}

#endif
