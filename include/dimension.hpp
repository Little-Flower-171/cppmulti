/**
 * @file dimension.hpp
 * Provides multi-dimensional size support.
 */

#ifndef INC_LF_MULTI_DIMENSION_HPP_T1COCZBICK
#define INC_LF_MULTI_DIMENSION_HPP_T1COCZBICK

#include <array>
#include <cstddef>
#include <stdexcept>

#include "common.hpp"

namespace LF_lib {
  namespace multi {

    /**
     * Multi-dimensional size type.
     *
     * Literal aggregate type.
     * Default-constructs to all zero.
     *
     * @tparam N The number of dimensions. Can be zero.
     */
    template <std::size_t N>
    struct Dimension {
      /**
       * Stores the @c N extents.
       */
      std::array<std::size_t, N> extents{};

      /**
       * Calculates the total size.
       *
       * @pre    The total size is representable by \c std::size_t.
       * @post   The result is equal to <code>extents[0] * extents[1] * ... * extents[N-1]</code>.
       * @return The total size.
       */
      constexpr std::size_t size() const noexcept
      {
	std::size_t result = 1;
	for (std::size_t i = 0; i < N; ++i)
	  result *= extents[i];
	return result;
      }

      /**
       * Converts a multi-dimensional index to a single index.
       *
       * @param  indices  The indices on each dimension.
       *
       * @throw  std::out_of_range  Some of the indices are out of range.
       *
       * @pre    Each index is less than or equal to the corresponding
       *         dimension.
       * @post   The result is equal to
       *         <code>indices[0] * extents[1] * extents[2] * ... * extents[N-1] + indices[1] * extents[2] * ... * extents[N-1] + ... + indices[N-2] * extents[N-1] + indices[N-1]</code>.
       * @return The multi-dimensional index converted to a single index.
       */
      constexpr std::size_t index(const std::array<std::size_t, N>& indices) const
      {
	std::size_t result = 0;
	for (std::size_t i = 0; i < N; ++i) {
	  if (indices[i] >= extents[i])
	    throw std::out_of_range{"LF_lib::multi::Dimension<N>::index out of range"};
	  result *= extents[i];
	  result += indices[i];
	}
	return result;
      }
    };
  
  }
}

#endif
