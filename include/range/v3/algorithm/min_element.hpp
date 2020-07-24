/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2014-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//
#ifndef RANGES_V3_ALGORITHM_MIN_ELEMENT_HPP
#define RANGES_V3_ALGORITHM_MIN_ELEMENT_HPP

#include <range/v3/range_fwd.hpp>

#include <range/v3/functional/comparisons.hpp>
#include <range/v3/functional/identity.hpp>
#include <range/v3/functional/invoke.hpp>
#include <range/v3/iterator/concepts.hpp>
#include <range/v3/iterator/operations.hpp>
#include <range/v3/iterator/traits.hpp>
#include <range/v3/range/access.hpp>
#include <range/v3/range/concepts.hpp>
#include <range/v3/range/dangling.hpp>
#include <range/v3/range/traits.hpp>
#include <range/v3/utility/static_const.hpp>

#include <range/v3/detail/disable_warnings.hpp>

namespace ranges
{
    /// \addtogroup group-algorithms
    /// @{
    RANGES_FUNC_BEGIN(min_element)

        /// \brief function template \c min_element
        CPP_template(typename I, typename S, typename C = less, typename P = identity)( //
            requires forward_iterator<I> && sentinel_for<S, I>  && //
            indirect_strict_weak_order<C, projected<I, P>>) //
        I RANGES_FUNC(min_element)(I first, S last, C pred = C{}, P proj = P{})
        {
            if(first != last)
                for(auto tmp = next(first); tmp != last; ++tmp)
                    if(invoke(pred, invoke(proj, *tmp), invoke(proj, *first)))
                        first = tmp;
            return first;
        }

        /// \overload
        CPP_template(typename Rng, typename C = less, typename P = identity)( //
            requires forward_range<Rng>  && //
            indirect_strict_weak_order<C, projected<iterator_t<Rng>, P>>) //
        auto RANGES_FUNC(min_element)(Rng && rng, C pred = C{}, P proj = P{}) //
            -> borrowed_iterator_t<Rng>
        {
            return (*this)(begin(rng), end(rng), std::move(pred), std::move(proj));
        }

    RANGES_FUNC_END(min_element)

    namespace cpp20
    {
        using ranges::min_element;
    }
    /// @}
} // namespace ranges

#include <range/v3/detail/reenable_warnings.hpp>

#endif
