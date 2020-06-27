// Copyright (c) 2020, Matthew Bentley (mattreecebentley@gmail.com) www.plflib.org

// zLib license (https://www.zlib.net/zlib_license.html):
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
// 	claim that you wrote the original software. If you use this software
// 	in a product, an acknowledgement in the product documentation would be
// 	appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// 	misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.


#ifndef PLF_INDSORT_H
#define PLF_INDSORT_H

// Compiler-specific defines used by indiesort:

#if defined(_MSC_VER)
	#if _MSC_VER < 1600
		#define PLF_INDSORT_NOEXCEPT throw()
	#elif _MSC_VER == 1600
		#define PLF_INDSORT_DECLTYPE_SUPPORT
		#define PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
		#define PLF_INDSORT_NOEXCEPT throw()
	#elif _MSC_VER == 1700
		#define PLF_INDSORT_DECLTYPE_SUPPORT
		#define PLF_INDSORT_TYPE_TRAITS_SUPPORT
		#define PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
		#define PLF_INDSORT_NOEXCEPT throw()
	#elif _MSC_VER == 1800
		#define PLF_INDSORT_DECLTYPE_SUPPORT
		#define PLF_INDSORT_TYPE_TRAITS_SUPPORT
		#define PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_INDSORT_VARIADICS_SUPPORT // Variadics, in this context, means both variadic templates and variadic macros are supported
		#define PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
		#define PLF_INDSORT_NOEXCEPT throw()
	#elif _MSC_VER >= 1900
		#define PLF_INDSORT_DECLTYPE_SUPPORT
		#define PLF_INDSORT_TYPE_TRAITS_SUPPORT
		#define PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_INDSORT_VARIADICS_SUPPORT
		#define PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
		#define PLF_INDSORT_NOEXCEPT noexcept
	#endif

	#if defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L)
		#define PLF_INDSORT_CONSTEXPR constexpr
		#define PLF_INDSORT_CONSTEXPR_SUPPORT
	#else
		#define PLF_INDSORT_CONSTEXPR
	#endif

#elif defined(__cplusplus) && __cplusplus >= 201103L // C++11 support, at least
	#if defined(__GNUC__) && defined(__GNUC_MINOR__) && !defined(__clang__) // If compiler is GCC/G++
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || __GNUC__ > 4 // 4.2 and below do not support variadic templates or decltype
			#define PLF_INDSORT_VARIADICS_SUPPORT
			#define PLF_INDSORT_DECLTYPE_SUPPORT
		#endif

		#if (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || __GNUC__ < 4
			#define PLF_INDSORT_NOEXCEPT throw()
		#else
			#define PLF_INDSORT_NOEXCEPT noexcept
		#endif

		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7) || __GNUC__ > 4
			#define PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
		#endif

		#if __GNUC__ >= 5 // GCC v4.9 and below do not support std::is_trivially_copyable
			#define PLF_INDSORT_TYPE_TRAITS_SUPPORT
		#endif
	#elif defined(__GLIBCXX__) // Using another compiler type with libstdc++ - we are assuming full c++11 compliance for compiler - which may not be true
		#define PLF_INDSORT_DECLTYPE_SUPPORT

		#if __GLIBCXX__ >= 20080606 	// libstdc++ 4.2 and below do not support variadic templates
			#define PLF_INDSORT_VARIADICS_SUPPORT
		#endif
		#if __GLIBCXX__ >= 20160111
			#define PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
			#define PLF_INDSORT_NOEXCEPT noexcept
		#elif __GLIBCXX__ >= 20120322
			#define PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
			#define PLF_INDSORT_NOEXCEPT noexcept
		#else
			#define PLF_INDSORT_NOEXCEPT throw()
		#endif
		#if __GLIBCXX__ >= 20150422 // libstdc++ v4.9 and below do not support std::is_trivially_copyable
			#define PLF_INDSORT_TYPE_TRAITS_SUPPORT
		#endif
	#elif defined(_LIBCPP_VERSION)
		#define PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_INDSORT_VARIADICS_SUPPORT
		#define PLF_INDSORT_INITIALIZER_LIST_SUPPORT
		#define PLF_INDSORT_NOEXCEPT noexcept

		#if !(defined(_LIBCPP_CXX03_LANG) || defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES))
			#define PLF_INDSORT_DECLTYPE_SUPPORT
			#define PLF_INDSORT_TYPE_TRAITS_SUPPORT
		#endif
	#else // Assume type traits and initializer support for other compilers and standard libraries
		#define PLF_INDSORT_DECLTYPE_SUPPORT
		#define PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_INDSORT_VARIADICS_SUPPORT
		#define PLF_INDSORT_TYPE_TRAITS_SUPPORT
		#define PLF_INDSORT_NOEXCEPT noexcept
	#endif

	#if __cplusplus >= 201703L
		#if defined(__clang__) && ((__clang_major__ == 3 && __clang_minor__ == 9) || __clang_major__ > 3)
			#define PLF_INDSORT_CONSTEXPR constexpr
			#define PLF_INDSORT_CONSTEXPR_SUPPORT
		#elif defined(__GNUC__) && __GNUC__ >= 7
			#define PLF_INDSORT_CONSTEXPR constexpr
			#define PLF_INDSORT_CONSTEXPR_SUPPORT
		#elif !defined(__clang__) && !defined(__GNUC__)
			#define PLF_INDSORT_CONSTEXPR constexpr // assume correct C++17 implementation for other compilers
			#define PLF_INDSORT_CONSTEXPR_SUPPORT
		#else
			#define PLF_INDSORT_CONSTEXPR
		#endif
	#else
		#define PLF_INDSORT_CONSTEXPR
	#endif

	#define PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
#else
	#define PLF_INDSORT_NOEXCEPT throw()
	#define PLF_INDSORT_CONSTEXPR
#endif



#ifdef PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
	#ifdef PLF_INDSORT_VARIADICS_SUPPORT
		#define PLF_INDSORT_CONSTRUCT(the_allocator, allocator_instance, location, ...)	std::allocator_traits<the_allocator>::construct(allocator_instance, location, __VA_ARGS__)
	#else
		#define PLF_INDSORT_CONSTRUCT(the_allocator, allocator_instance, location, data) std::allocator_traits<the_allocator>::construct(allocator_instance, location, data)
	#endif

	#define PLF_INDSORT_ALLOCATE(the_allocator, allocator_instance, size, hint) 		std::allocator_traits<the_allocator>::allocate(allocator_instance, size, hint)
	#define PLF_INDSORT_DEALLOCATE(the_allocator, allocator_instance, location, size) 	std::allocator_traits<the_allocator>::deallocate(allocator_instance, location, size)
#else
	#ifdef PLF_INDSORT_VARIADICS_SUPPORT
		#define PLF_INDSORT_CONSTRUCT(the_allocator, allocator_instance, location, ...)	allocator_instance.construct(location, __VA_ARGS__)
	#else
		#define PLF_INDSORT_CONSTRUCT(the_allocator, allocator_instance, location, data) allocator_instance.construct(location, data)
	#endif

	#define PLF_INDSORT_ALLOCATE(the_allocator, allocator_instance, size, hint)	 		allocator_instance.allocate(size, hint)
	#define PLF_INDSORT_DEALLOCATE(the_allocator, allocator_instance, location, size) 	allocator_instance.deallocate(location, size)
#endif


#ifndef PLF_INDSORT_SORT_FUNCTION
	#include <algorithm> // std::sort
#endif

#include <cassert>	// assert
#include <cstddef> // std::size_t
#include <memory>	// std::allocator
#include <limits>  // std::numeric_limits


#ifdef PLF_INDSORT_TYPE_TRAITS_SUPPORT
	#include <iterator> // std::iterator_traits
	#include <type_traits> // is_same
#endif

#ifdef PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
	#include <utility> // std::move
#endif



namespace plf
{

	#ifdef PLF_INDSORT_DECLTYPE_SUPPORT
		template <typename T>
		class has_size_function
		{
			private:
				typedef char one;
				struct two { char x[2]; };

				template <typename C> static one test( decltype(&C::size) ) ;
				template <typename C> static two test(...);

			public:
				enum { value = sizeof(test<T>(0)) == sizeof(char) };
		};
	#endif



	template <class element_type>
	struct less
	{
		bool operator() (const element_type &a, const element_type &b) const PLF_INDSORT_NOEXCEPT
		{
			return a < b;
		}
	};



	// Function-object, used to redirect the sort function to compare element pointers by the elements they point to, and sort the element pointers instead of the elements:
	template <class comparison_function, class element_type>
	struct sort_dereferencer
	{
		comparison_function stored_instance;

		explicit sort_dereferencer(const comparison_function &function_instance):
			stored_instance(function_instance)
		{}

		sort_dereferencer() PLF_INDSORT_NOEXCEPT
		{}

		bool operator() (const element_type first, const element_type second)
		{
			return stored_instance(*(first.original_location), *(second.original_location));
		}
	};



	template <bool condition, class T = void>
	struct enable_if_c
	{
		typedef T type;
	};

	template <class T>
	struct enable_if_c<false, T>
	{};



	template <typename T>
	struct is_pointer
	{
		static const bool value = false;
	};

	template <typename T>
	struct is_pointer<T*>
	{
		static const bool value = true;
	};



	template< class T > struct remove_pointer                    {typedef T type;};
	template< class T > struct remove_pointer<T*>                {typedef T type;};
	template< class T > struct remove_pointer<T* const>          {typedef T type;};
	template< class T > struct remove_pointer<T* volatile>       {typedef T type;};
	template< class T > struct remove_pointer<T* const volatile> {typedef T type;};



	template <bool flag, class the_type> struct derive_type;

	template <class the_type> struct derive_type<true, the_type>
	{
		typedef typename plf::remove_pointer<the_type>::type type;
	};

	template <class the_type> struct derive_type<false, the_type>
	{
		typedef typename the_type::value_type type;
	};



	// Must be non-local to the function below for C++03 compatibility:
	template <class pointer, typename size_type>
	struct pointer_index_tuple
	{
		pointer original_location;
		size_type original_index;

		pointer_index_tuple(const pointer _item, const size_type _index) PLF_INDSORT_NOEXCEPT:
			original_location(_item),
			original_index(_index)
		{}
	};



	template <class iterator_type, class comparison_function>
	void indiesort(const iterator_type first, const iterator_type last, comparison_function compare, const std::size_t size)
	{
		if (size < 2)
		{
			return;
		}

		typedef typename plf::derive_type<plf::is_pointer<iterator_type>::value, iterator_type>::type	element_type;
		typedef element_type *																									pointer;
		typedef typename std::size_t																							size_type;
		typedef pointer_index_tuple<pointer, size_type> 																item_index_tuple;

		typedef typename std::allocator<item_index_tuple> tuple_allocator_type;
		tuple_allocator_type tuple_allocator;

		item_index_tuple * const sort_array = PLF_INDSORT_ALLOCATE(tuple_allocator_type, tuple_allocator, size, NULL);
		item_index_tuple *tuple_pointer = sort_array;

		// Construct pointers to all elements in the sequence:
		size_type index = 0;

		for (iterator_type current_element = first; current_element != last; ++current_element, ++tuple_pointer, ++index)
		{
			#ifdef PLF_INDSORT_VARIADICS_SUPPORT
				PLF_INDSORT_CONSTRUCT(tuple_allocator_type, tuple_allocator, tuple_pointer, &*current_element, index);
			#else
				PLF_INDSORT_CONSTRUCT(tuple_allocator_type, tuple_allocator, tuple_pointer, item_index_tuple(&*current_element, index));
			#endif
		}


		// Now, sort the pointers by the values they point to (std::sort is default sort function if the macro below is not defined):
		#ifndef PLF_INDSORT_SORT_FUNCTION
			std::sort(sort_array, sort_array + size, plf::sort_dereferencer<comparison_function, item_index_tuple>(compare));
		#else
			PLF_INDSORT_SORT_FUNCTION(sort_array, sort_array + size, plf::sort_dereferencer<comparison_function, item_index_tuple>(compare));
		#endif

		// This special value indicates that the element being pointed to in that tuple has been sorted already:
		PLF_INDSORT_CONSTEXPR const size_type sorted = std::numeric_limits<size_type>::max(); // Also improves performance for pre-constexpr compilers


		// Sort the actual elements via the tuple array:
		index = 0;

		for (item_index_tuple *current_tuple = sort_array; current_tuple != tuple_pointer; ++current_tuple, ++index)
		{
      	if (current_tuple->original_index != index && current_tuple->original_index != sorted)
      	{
				#ifdef PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
					element_type end_value = std::move(*(current_tuple->original_location));
				#else
					element_type end_value = *(current_tuple->original_location);
					*(current_tuple->original_location).~element_type();
				#endif

				size_type destination_index = index;
				size_type source_index = current_tuple->original_index;

				do
				{
					#ifdef PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
						*(sort_array[destination_index].original_location) = std::move(*(sort_array[source_index].original_location));
					#else
						*(sort_array[destination_index].original_location) = *(sort_array[source_index].original_location);
						*(sort_array[source_index].original_location).~element_type();
					#endif

				   destination_index = source_index;
					source_index = sort_array[destination_index].original_index;
					sort_array[destination_index].original_index = sorted;
				} while (source_index != index);

				#ifdef PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
					*(sort_array[destination_index].original_location) = std::move(end_value);
				#else
					*(sort_array[destination_index].original_location) = end_value;
					end_value.~element_type();
				#endif
			}
		}

		PLF_INDSORT_DEALLOCATE(tuple_allocator_type, tuple_allocator, sort_array, size);
	}



	// Non-pointer template:
	template <class iterator_type, class comparison_function>
	inline void indiesort(const typename plf::enable_if_c<!plf::is_pointer<iterator_type>::value, iterator_type>::type first, const iterator_type last, comparison_function compare)
	{
		#if defined(PLF_INDSORT_TYPE_TRAITS_SUPPORT) && defined(PLF_INDSORT_CONSTEXPR_SUPPORT) // Constexpr must be present for the following statement to compile - otherwise the subtraction statement can be invalid for a given type
			if PLF_INDSORT_CONSTEXPR (std::is_same<typename std::iterator_traits<iterator_type>::iterator_category, std::random_access_iterator_tag>::value)
			{
				assert(first <= last);
				indiesort(first, last, compare, last - first);
			}
			else
		#endif
		{
			std::size_t size = 0;

			for (iterator_type temp = first; temp != last; ++temp, ++size)
			{}

			indiesort(first, last, compare, size);
		}
	}



	// Pointer template:
	template <class iterator_type, class comparison_function>
	inline void indiesort(const typename plf::enable_if_c<plf::is_pointer<iterator_type>::value, iterator_type>::type first, const iterator_type last, comparison_function compare)
	{
		assert(first <= last);
		indiesort(first, last, compare, last - first);
	}



	template <class iterator_type>
	inline void indiesort(const iterator_type first, const iterator_type last)
	{
		indiesort(first, last, plf::less<typename plf::derive_type<plf::is_pointer<iterator_type>::value, iterator_type>::type>());
	}



	template <class container_type, class comparison_function>
	inline void indiesort(container_type &container, comparison_function compare)
	{
		#ifdef PLF_INDSORT_DECLTYPE_SUPPORT
			if PLF_INDSORT_CONSTEXPR (!plf::has_size_function<container_type>::value)
			{
				indiesort(container.begin(), container.end(), compare); // call range indiesort
			}
			else
		#endif
		{
			indiesort(container.begin(), container.end(), compare, static_cast<std::size_t>(container.size()));
		}
	}



	template <class container_type>
	inline void indiesort(container_type &container)
	{
		indiesort(container, plf::less<typename container_type::value_type>());
	}
}


#undef PLF_INDSORT_DECLTYPE_SUPPORT
#undef PLF_INDSORT_TYPE_TRAITS_SUPPORT
#undef PLF_INDSORT_ALLOCATOR_TRAITS_SUPPORT
#undef PLF_INDSORT_VARIADICS_SUPPORT
#undef PLF_INDSORT_MOVE_SEMANTICS_SUPPORT
#undef PLF_INDSORT_NOEXCEPT
#undef PLF_INDSORT_CONSTEXPR
#undef PLF_INDSORT_CONSTEXPR_SUPPORT

#undef PLF_INDSORT_CONSTRUCT
#undef PLF_INDSORT_ALLOCATE
#undef PLF_INDSORT_DEALLOCATE

#endif // PLF_INDSORT_H