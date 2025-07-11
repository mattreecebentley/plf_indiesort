// Copyright (c) 2023, Matthew Bentley (mattreecebentley@gmail.com) www.plflib.org

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

#ifndef PLF_INDIESORT_H
#define PLF_INDIESORT_H


// Compiler-specific defines used by indiesort:

// Define default cases before possibly redefining:
#define PLF_CONSTFUNC
#define PLF_NOEXCEPT throw()
#define PLF_CONSTEXPR

#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
    // Suppress incorrect (unfixed MSVC bug) warnings re: constant expressions in constexpr-if statements
	#pragma warning ( push )
    #pragma warning ( disable : 4127 )

	#if _MSC_VER >= 1600
		#define PLF_DECLTYPE_SUPPORT
		#define PLF_MOVE_SEMANTICS_SUPPORT
	#endif
	#if _MSC_VER >= 1700
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
	#endif
	#if _MSC_VER >= 1800
		#define PLF_VARIADICS_SUPPORT // Variadics, in this context, means both variadic templates and variadic macros are supported
	#endif
	#if _MSC_VER >= 1900
		#undef PLF_NOEXCEPT
		#define PLF_NOEXCEPT noexcept
	#endif

	#if defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L)
		#undef PLF_CONSTEXPR
		#define PLF_CONSTEXPR constexpr
	#endif

	#if defined(_MSVC_LANG) && (_MSVC_LANG >= 202002L) && _MSC_VER >= 1929
		#undef PLF_CONSTFUNC
		#define PLF_CONSTFUNC constexpr
	#endif

#elif defined(__cplusplus) && __cplusplus >= 201103L // C++11 support, at least
	#define PLF_MOVE_SEMANTICS_SUPPORT

	#if defined(__GNUC__) && defined(__GNUC_MINOR__) && !defined(__clang__) // If compiler is GCC/G++
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || __GNUC__ > 4 // 4.2 and below do not support variadic templates or decltype
			#define PLF_VARIADICS_SUPPORT
			#define PLF_DECLTYPE_SUPPORT
		#endif
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 6) || __GNUC__ > 4
			#undef PLF_NOEXCEPT
			#define PLF_NOEXCEPT noexcept
		#endif
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7) || __GNUC__ > 4
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#endif
		#if __GNUC__ >= 5 // GCC v4.9 and below do not support std::is_trivially_copyable
			#define PLF_TYPE_TRAITS_SUPPORT
		#endif
	#elif defined(__clang__) && !defined(__GLIBCXX__) && !defined(_LIBCPP_CXX03_LANG)
		#if __clang_major__ >= 3 // clang versions < 3 don't support __has_feature() or traits
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
			#define PLF_TYPE_TRAITS_SUPPORT

			#if __has_feature(cxx_decltype)
				#define PLF_DECLTYPE_SUPPORT
			#endif
			#if __has_feature(cxx_noexcept)
				#undef PLF_NOEXCEPT
				#define PLF_NOEXCEPT noexcept
			#endif
			#if __has_feature(cxx_rvalue_references) && !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES)
				#define PLF_MOVE_SEMANTICS_SUPPORT
			#endif
			#if __has_feature(cxx_variadic_templates) && !defined(_LIBCPP_HAS_NO_VARIADICS)
				#define PLF_VARIADICS_SUPPORT
			#endif
		#endif
	#elif defined(__GLIBCXX__) // Using another compiler type with libstdc++ - we are assuming full c++11 compliance for compiler - which may not be true
		#define PLF_DECLTYPE_SUPPORT

		#if __GLIBCXX__ >= 20080606 	// libstdc++ 4.2 and below do not support variadic templates
			#define PLF_VARIADICS_SUPPORT
		#endif
		#if __GLIBCXX__ >= 20120322
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
			#undef PLF_NOEXCEPT
			#define PLF_NOEXCEPT noexcept
		#endif
		#if __GLIBCXX__ >= 20150422 // libstdc++ v4.9 and below do not support std::is_trivially_copyable
			#define PLF_TYPE_TRAITS_SUPPORT
		#endif
	#elif defined(_LIBCPP_CXX03_LANG) // Special case for checking C++11 support with libcpp
		#if !defined(_LIBCPP_HAS_NO_VARIADICS)
			#define PLF_VARIADICS_SUPPORT
		#endif
	#else // Assume full support for other compilers and standard libraries
		#define PLF_DECLTYPE_SUPPORT
		#define PLF_INITIALIZER_LIST_SUPPORT
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_VARIADICS_SUPPORT
		#define PLF_TYPE_TRAITS_SUPPORT
		#undef PLF_NOEXCEPT
		#define PLF_NOEXCEPT noexcept
	#endif

	#if __cplusplus >= 201703L  &&	((defined(__clang__) && ((__clang_major__ == 3 && __clang_minor__ == 9) || __clang_major__ > 3))	||   (defined(__GNUC__) && __GNUC__ >= 7)   ||	 (!defined(__clang__) && !defined(__GNUC__)))
		#undef PLF_CONSTEXPR
		#define PLF_CONSTEXPR constexpr
	#endif

	#if __cplusplus > 201704L && ((((defined(__clang__) && !defined(__APPLE_CC__) && __clang_major__ >= 14) || (defined(__GNUC__) && (__GNUC__ > 11 || (__GNUC__ == 11 && __GNUC_MINOR__ > 0)))) && ((defined(_LIBCPP_VERSION) && _LIBCPP_VERSION >= 14) || (defined(__GLIBCXX__) && __GLIBCXX__ >= 201806L))) || (!defined(__clang__) && !defined(__GNUC__)))
		#define PLF_CPP20_SUPPORT
		#undef PLF_CONSTFUNC
		#define PLF_CONSTFUNC constexpr
	#endif
#endif




#ifdef PLF_ALLOCATOR_TRAITS_SUPPORT
	#ifdef PLF_VARIADICS_SUPPORT
		#define PLF_CONSTRUCT(the_allocator, allocator_instance, location, ...) std::allocator_traits<the_allocator>::construct(allocator_instance, location, __VA_ARGS__)
	#else
		#define PLF_CONSTRUCT(the_allocator, allocator_instance, location, data)	std::allocator_traits<the_allocator>::construct(allocator_instance, location, data)
	#endif

	#define PLF_DESTROY(the_allocator, allocator_instance, location)				std::allocator_traits<the_allocator>::destroy(allocator_instance, location)
	#define PLF_ALLOCATE(the_allocator, allocator_instance, size, hint)			std::allocator_traits<the_allocator>::allocate(allocator_instance, size, hint)
	#define PLF_DEALLOCATE(the_allocator, allocator_instance, location, size)	std::allocator_traits<the_allocator>::deallocate(allocator_instance, location, size)
#else
	#ifdef PLF_VARIADICS_SUPPORT
		#define PLF_CONSTRUCT(the_allocator, allocator_instance, location, ...) 	(allocator_instance).construct(location, __VA_ARGS__)
	#else
		#define PLF_CONSTRUCT(the_allocator, allocator_instance, location, data)	(allocator_instance).construct(location, data)
	#endif

	#define PLF_DESTROY(the_allocator, allocator_instance, location)				(allocator_instance).destroy(location)
	#define PLF_ALLOCATE(the_allocator, allocator_instance, size, hint)			(allocator_instance).allocate(size, hint)
	#define PLF_DEALLOCATE(the_allocator, allocator_instance, location, size)	(allocator_instance).deallocate(location, size)
#endif



#ifndef PLF_SORT_FUNCTION
	#include <algorithm> // std::sort
	#define PLF_SORT_FUNCTION std::sort
	#define PLF_SORT_FUNCTION_DEFINED
#endif

#include <cassert>	// assert
#include <cstddef> // std::size_t
#include <memory>	// std::allocator, std::to_address
#include <limits>  // std::numeric_limits
#include <iterator> // std::iterator_traits, std::move_iterator, std::distance


#ifdef PLF_TYPE_TRAITS_SUPPORT
	#include <type_traits> // is_same
#endif

#ifdef PLF_MOVE_SEMANTICS_SUPPORT
	#include <utility> // std::move
#endif



namespace plf
{
	// std:: tool replacements for C++03/98/11 support:

#ifndef PLF_TOOLS
	#define PLF_TOOLS

	template <bool condition, class T = void>
	struct enable_if
	{
		typedef T type;
	};

	template <class T>
	struct enable_if<false, T>
	{};



	template <bool flag, class is_true, class is_false> struct conditional;

	template <class is_true, class is_false> struct conditional<true, is_true, is_false>
	{
		typedef is_true type;
	};

	template <class is_true, class is_false> struct conditional<false, is_true, is_false>
	{
		typedef is_false type;
	};



	template <class element_type>
	struct less
	{
		bool operator() (const element_type &a, const element_type &b) const PLF_NOEXCEPT
		{
			return a < b;
		}
	};



	template<class element_type>
	struct equal_to
	{
		const element_type value;

		explicit equal_to(const element_type store_value): // no noexcept as element may allocate and potentially throw when copied
			value(store_value)
		{}

		bool operator() (const element_type compare_value) const PLF_NOEXCEPT
		{
			return value == compare_value;
		}
	};



	// To enable conversion to void * when allocator supplies non-raw pointers:
	template <class source_pointer_type>
	static PLF_CONSTFUNC void * void_cast(const source_pointer_type source_pointer) PLF_NOEXCEPT
	{
		#if defined(PLF_CPP20_SUPPORT)
			return static_cast<void *>(std::to_address(source_pointer));
		#else
			return static_cast<void *>(&*source_pointer);
		#endif
	}



	#ifdef PLF_MOVE_SEMANTICS_SUPPORT
		template <class iterator_type>
		PLF_CONSTFUNC std::move_iterator<iterator_type> make_move_iterator(iterator_type it)
		{
			return std::move_iterator<iterator_type>(std::move(it));
		}
	#endif



	enum priority { performance = 1, memory_use = 4};
#endif


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



	template< class T > struct remove_pointer 						{typedef T type;};
	template< class T > struct remove_pointer<T*>					{typedef T type;};
	template< class T > struct remove_pointer<T* const>				{typedef T type;};
	template< class T > struct remove_pointer<T* volatile>			{typedef T type;};
	template< class T > struct remove_pointer<T* const volatile>	{typedef T type;};



	template <bool flag, class the_type> struct derive_type;

	template <class the_type> struct derive_type<true, the_type>
	{
		typedef typename remove_pointer<the_type>::type type;
	};

	template <class the_type> struct derive_type<false, the_type>
	{
		typedef typename the_type::value_type type;
	};



	// Function-object, used to redirect the sort function to compare element pointers by the elements they point to, and sort the element pointers instead of the elements:

	template <class comparison_function, class iterator_type, class size_type>
	struct random_access_sort_dereferencer
	{
		comparison_function stored_instance;
		const iterator_type stored_first_iterator;

		PLF_CONSTFUNC explicit random_access_sort_dereferencer(const comparison_function &function_instance, const iterator_type first):
			stored_instance(function_instance),
			stored_first_iterator(first)
		{}

		PLF_CONSTFUNC bool operator() (const size_type index1, const size_type index2)
		{
			return stored_instance(*(stored_first_iterator + index1), *(stored_first_iterator + index2));
		}
	};



	template <class iterator_type, class comparison_function, typename size_type>
	PLF_CONSTFUNC void random_access_sort(const iterator_type first, comparison_function compare, const size_type size)
	{
		typedef typename derive_type<is_pointer<iterator_type>::value, iterator_type>::type	element_type;
		typedef typename std::allocator<size_type> size_type_allocator_type;

		size_type_allocator_type size_type_allocator;
		size_type * const sort_array = PLF_ALLOCATE(size_type_allocator_type, size_type_allocator, size, NULL);
		size_type *size_type_pointer = sort_array;

		// Construct pointers to all elements in the sequence:
		for (size_type index = 0; index != size; ++index, ++size_type_pointer)
		{
			PLF_CONSTRUCT(size_type_allocator_type, size_type_allocator, size_type_pointer, index);
		}

		// Now, sort the pointers by the values they point to (std::sort is default sort function if the macro below is not defined prior to header inclusion):
		PLF_SORT_FUNCTION(sort_array, size_type_pointer, random_access_sort_dereferencer<comparison_function, iterator_type, size_type>(compare, first));

		// Sort the actual elements via the tuple array:
		size_type index = 0;

		for (size_type *current_index = sort_array; current_index != size_type_pointer; ++current_index, ++index)
		{
			if (*current_index != index)
			{
				size_type destination_index = index;

				#ifdef PLF_MOVE_SEMANTICS_SUPPORT
					element_type end_value = std::move(*(first + destination_index));
				#else
					element_type end_value = *(first + destination_index);
				#endif

				size_type source_index = *current_index;

				do
				{
					#ifdef PLF_MOVE_SEMANTICS_SUPPORT
						*(first + destination_index) = std::move(*(first + source_index));
					#else
						*(first + destination_index) = *(first + source_index);
					#endif

					destination_index = source_index;
					source_index = sort_array[destination_index];
					sort_array[destination_index] = destination_index;
				} while (source_index != index);

				#ifdef PLF_MOVE_SEMANTICS_SUPPORT
					*(first + destination_index) = std::move(end_value);
				#else
					*(first + destination_index) = end_value;
				#endif
			}
		}

		PLF_DEALLOCATE(size_type_allocator_type, size_type_allocator, sort_array, size);
	}



	template <class iterator_type, class comparison_function>
	PLF_CONSTFUNC void call_random_access_sort(const iterator_type first, const iterator_type last, comparison_function compare)
	{
		assert(first <= last);
		typedef typename derive_type<is_pointer<iterator_type>::value, iterator_type>::type	element_type;

		#ifdef PLF_TYPE_TRAITS_SUPPORT
			if PLF_CONSTEXPR ((std::is_trivially_copyable<element_type>::value || std::is_move_assignable<element_type>::value) && sizeof(element_type) < 152) // ie. below benchmarked threshold for improved performance over direct std::sort
		#else
			if PLF_CONSTEXPR (sizeof(element_type) < 152)
		#endif
		{
			PLF_SORT_FUNCTION(first, last, compare);
			return;
		}


		const std::size_t size = static_cast<std::size_t>(last - first);

		if (size < 2)
		{
			return;
		}
		else if (size <= std::numeric_limits<unsigned char>::max())
		{
			random_access_sort<iterator_type, comparison_function, unsigned char>(first, compare, static_cast<unsigned char>(size));
		}
		else if (size <= std::numeric_limits<unsigned short>::max())
		{
			random_access_sort<iterator_type, comparison_function, unsigned short>(first, compare, static_cast<unsigned short>(size));
		}
		else if (size <= std::numeric_limits<unsigned int>::max())
		{
			random_access_sort<iterator_type, comparison_function, unsigned int>(first, compare, static_cast<unsigned int>(size));
		}
		else
		{
			random_access_sort<iterator_type, comparison_function, std::size_t>(first, compare, size);
		}
	}



	template <class comparison_function, class element_type>
	struct sort_dereferencer
	{
		comparison_function stored_instance;

		PLF_CONSTFUNC explicit sort_dereferencer(const comparison_function &function_instance):
			stored_instance(function_instance)
		{}

		PLF_CONSTFUNC bool operator() (const element_type first, const element_type second)
		{
			return stored_instance(*(first.original_location), *(second.original_location));
		}
	};



	// This struct must be non-local to the function below for C++03 compatibility:

	template <class pointer, typename size_type>
	struct pointer_index_tuple
	{
		pointer original_location;
		size_type original_index;

		PLF_CONSTFUNC pointer_index_tuple(const pointer _item, const size_type _index) PLF_NOEXCEPT:
			original_location(_item),
			original_index(_index)
		{}
	};



	template <class iterator_type, class comparison_function>
	PLF_CONSTFUNC void non_random_access_sort(const iterator_type first, const iterator_type last, comparison_function compare, const std::size_t size)
	{
		if (size < 2)
		{
			return;
		}

		typedef typename derive_type<is_pointer<iterator_type>::value, iterator_type>::type	element_type;

 		#ifdef PLF_TYPE_TRAITS_SUPPORT
			if PLF_CONSTEXPR ((std::is_trivially_copyable<element_type>::value || std::is_move_assignable<element_type>::value) && sizeof(element_type) <= sizeof(element_type *) * 2) // If element is <= 2 pointers, just copy to an array and sort that then copy back - consumes less memory and may be faster
		#else
			if PLF_CONSTEXPR (sizeof(element_type) <= sizeof(element_type *) * 2)
		#endif
		{
			typedef typename std::allocator<element_type> allocator_type;
			allocator_type alloc;
			element_type * const sort_array = PLF_ALLOCATE(allocator_type, alloc, size, NULL), * const end = sort_array + size;

			#ifdef PLF_TYPE_TRAITS_SUPPORT
				if PLF_CONSTEXPR (std::is_trivially_copyable<element_type>::value) // avoid construction
				{
					std::copy(first, last, sort_array);
				}
				else if PLF_CONSTEXPR (std::is_move_assignable<element_type>::value)
				{
					std::uninitialized_copy(plf::make_move_iterator(first), plf::make_move_iterator(last), sort_array);
				}
				else
			#endif
			{
				std::uninitialized_copy(first, last, sort_array);
			}

			PLF_SORT_FUNCTION(sort_array, end, compare);

			#ifdef PLF_TYPE_TRAITS_SUPPORT
				if PLF_CONSTEXPR (!std::is_trivially_copyable<element_type>::value && std::is_move_assignable<element_type>::value)
				{
					std::copy(plf::make_move_iterator(sort_array), plf::make_move_iterator(end), first);
				}
				else
			#endif
			{
				std::copy(sort_array, end, first);

				#ifdef PLF_TYPE_TRAITS_SUPPORT
					if (!std::is_trivially_destructible<element_type>::value)
				#endif
				{
					for (element_type *current = sort_array; current != end; ++current)
					{
						PLF_DESTROY(allocator_type, alloc, current);
					}
				}
			}
			
			PLF_DEALLOCATE(allocator_type, alloc, sort_array, size);
			return;
		}
 		else
		{
			typedef typename std::size_t							size_type;
			typedef pointer_index_tuple<element_type *, size_type> 	item_index_tuple;

			typedef typename std::allocator<item_index_tuple> tuple_allocator_type;
			tuple_allocator_type tuple_allocator;

			item_index_tuple * const sort_array = PLF_ALLOCATE(tuple_allocator_type, tuple_allocator, size, NULL);
			item_index_tuple *tuple_pointer = sort_array;

			// Construct pointers to all elements in the sequence:
			size_type index = 0;

			for (iterator_type current_element = first; current_element != last; ++current_element, ++tuple_pointer, ++index)
			{
				#ifdef PLF_VARIADICS_SUPPORT
					PLF_CONSTRUCT(tuple_allocator_type, tuple_allocator, tuple_pointer, &*current_element, index);
				#else
					PLF_CONSTRUCT(tuple_allocator_type, tuple_allocator, tuple_pointer, item_index_tuple(&*current_element, index));
				#endif
			}

			PLF_SORT_FUNCTION(sort_array, sort_array + size, sort_dereferencer<comparison_function, item_index_tuple>(compare));

			// Sort the actual elements via the tuple array:
			index = 0;

			for (item_index_tuple *current_tuple = sort_array; current_tuple != tuple_pointer; ++current_tuple, ++index)
			{
				if (current_tuple->original_index != index)
				{
					#ifdef PLF_MOVE_SEMANTICS_SUPPORT
						element_type end_value = std::move(*(current_tuple->original_location));
					#else
						element_type end_value = *(current_tuple->original_location);
					#endif

					size_type destination_index = index;
					size_type source_index = current_tuple->original_index;

					do
					{
						#ifdef PLF_MOVE_SEMANTICS_SUPPORT
							*(sort_array[destination_index].original_location) = std::move(*(sort_array[source_index].original_location));
						#else
							*(sort_array[destination_index].original_location) = *(sort_array[source_index].original_location);
						#endif

						destination_index = source_index;
						source_index = sort_array[destination_index].original_index;
						sort_array[destination_index].original_index = destination_index;
					} while (source_index != index);

					#ifdef PLF_MOVE_SEMANTICS_SUPPORT
						*(sort_array[destination_index].original_location) = std::move(end_value);
					#else
						*(sort_array[destination_index].original_location) = end_value;
					#endif
				}
			}

			PLF_DEALLOCATE(tuple_allocator_type, tuple_allocator, sort_array, size);
		}
	}



	// Range templates:
	template <class iterator_type, class comparison_function>
	PLF_CONSTFUNC void indiesort(const iterator_type first, const iterator_type last, comparison_function compare, const std::size_t size)
	{
		non_random_access_sort(first, last, compare, size);
	}



	template <class iterator_type, class comparison_function>
	#ifdef PLF_TYPE_TRAITS_SUPPORT
		PLF_CONSTFUNC void indiesort(const typename plf::enable_if<!(is_pointer<iterator_type>::value || std::is_same<typename std::iterator_traits<iterator_type>::iterator_category, std::random_access_iterator_tag>::value), iterator_type>::type first, const iterator_type last, comparison_function compare)
	#else
		PLF_CONSTFUNC void indiesort(const typename plf::enable_if<!is_pointer<iterator_type>::value, iterator_type>::type first, const iterator_type last, comparison_function compare)
	#endif
	{
		non_random_access_sort(first, last, compare, std::distance(first, last));
	}



	template <class iterator_type, class comparison_function>
	#ifdef PLF_TYPE_TRAITS_SUPPORT
		PLF_CONSTFUNC void indiesort(const typename plf::enable_if<(is_pointer<iterator_type>::value || std::is_same<typename std::iterator_traits<iterator_type>::iterator_category, std::random_access_iterator_tag>::value), iterator_type>::type first, const iterator_type last, comparison_function compare)
	#else
		PLF_CONSTFUNC void indiesort(const typename plf::enable_if<is_pointer<iterator_type>::value, iterator_type>::type first, const iterator_type last, comparison_function compare)
	#endif
	{
		call_random_access_sort(first, last, compare);
	}



	template <class iterator_type>
	PLF_CONSTFUNC void indiesort(const iterator_type first, const iterator_type last)
	{
		indiesort(first, last, plf::less<typename derive_type<is_pointer<iterator_type>::value, iterator_type>::type>());
	}



	// Container-based templates:

	#ifdef PLF_TYPE_TRAITS_SUPPORT
		template <class container_type, class comparison_function, typename plf::enable_if<std::is_same<typename std::iterator_traits<typename container_type::iterator>::iterator_category, std::random_access_iterator_tag>::value, container_type>::type * = nullptr>
		PLF_CONSTFUNC void indiesort(container_type &container, comparison_function compare)
		{
			call_random_access_sort(container.begin(), container.end(), compare);
		}
	#endif



	#ifdef PLF_DECLTYPE_SUPPORT
		template <typename T>
		class has_size_function
		{
			private:
				typedef char one;
				struct two { char x[2]; };

				template <typename C> PLF_CONSTFUNC static one test( decltype(&C::size) ) ;
				template <typename C> PLF_CONSTFUNC static two test(...);

			public:
				enum { value = sizeof(test<T>(0)) == sizeof(char) };
		};
	#endif



	#ifdef PLF_TYPE_TRAITS_SUPPORT
		template <class container_type, class comparison_function, typename plf::enable_if<!std::is_same<typename std::iterator_traits<typename container_type::iterator>::iterator_category, std::random_access_iterator_tag>::value, container_type>::type * = nullptr>
	#else
		template <class container_type, class comparison_function>
	#endif
	PLF_CONSTFUNC void indiesort(container_type &container, comparison_function compare)
	{
		#ifdef PLF_DECLTYPE_SUPPORT
			if PLF_CONSTEXPR (has_size_function<container_type>::value)
			{
				non_random_access_sort(container.begin(), container.end(), compare, static_cast<std::size_t>(container.size()));
			}
			else
		#endif
		{	// If no decltype support, assume container doesn't have size()
			indiesort(container.begin(), container.end(), compare); // call range indiesort
		}
	}



	template <class container_type>
	PLF_CONSTFUNC void indiesort(container_type &container)
	{
		indiesort(container, plf::less<typename container_type::value_type>());
	}
		
}


#undef PLF_DECLTYPE_SUPPORT
#undef PLF_TYPE_TRAITS_SUPPORT
#undef PLF_ALLOCATOR_TRAITS_SUPPORT
#undef PLF_VARIADICS_SUPPORT
#undef PLF_MOVE_SEMANTICS_SUPPORT
#undef PLF_NOEXCEPT
#undef PLF_CONSTEXPR
#undef PLF_CONSTFUNC

#undef PLF_CONSTRUCT
#undef PLF_ALLOCATE
#undef PLF_DEALLOCATE

#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
	#pragma warning ( pop )
#endif

#ifdef PLF_SORT_FUNCTION_DEFINED
	#undef PLF_SORT_FUNCTION
	#undef PLF_SORT_FUNCTION_DEFINED
#endif


#endif // PLF_INDIESORT_H
