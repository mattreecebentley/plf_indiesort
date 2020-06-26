#if defined(_MSC_VER)
	#define PLF_FORCE_INLINE __forceinline

	#if _MSC_VER < 1600
		#define PLF_NOEXCEPT throw()
		#define PLF_NOEXCEPT_SWAP(the_allocator)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) throw()
	#elif _MSC_VER == 1600
		#define PLF_MOVE_SEMANTICS_SUPPORT
		#define PLF_NOEXCEPT throw()
		#define PLF_NOEXCEPT_SWAP(the_allocator)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) throw()
	#elif _MSC_VER == 1700
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_MOVE_SEMANTICS_SUPPORT
		#define PLF_NOEXCEPT throw()
		#define PLF_NOEXCEPT_SWAP(the_allocator)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) throw()
	#elif _MSC_VER == 1800
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_VARIADICS_SUPPORT // Variadics, in this context, means both variadic templates and variadic macros are supported
		#define PLF_MOVE_SEMANTICS_SUPPORT
		#define PLF_NOEXCEPT throw()
		#define PLF_NOEXCEPT_SWAP(the_allocator)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) throw()
		#define PLF_INITIALIZER_LIST_SUPPORT
	#elif _MSC_VER >= 1900
		#define PLF_ALIGNMENT_SUPPORT
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_VARIADICS_SUPPORT
		#define PLF_MOVE_SEMANTICS_SUPPORT
		#define PLF_NOEXCEPT noexcept
		#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_swap::value || std::allocator_traits<the_allocator>::is_always_equal::value)
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_move_assignment::value || std::allocator_traits<the_allocator>::is_always_equal::value)
		#define PLF_INITIALIZER_LIST_SUPPORT
	#endif

	#if defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L)
		#define PLF_CONSTEXPR constexpr
		#define PLF_CONSTEXPR_SUPPORT
	#else
		#define PLF_CONSTEXPR
	#endif

	#if defined(_MSVC_LANG) && (_MSVC_LANG > 201703L)
		#define PLF_CPP20_SUPPORT
	#endif

#elif defined(__cplusplus) && __cplusplus >= 201103L // C++11 support, at least
	#define PLF_FORCE_INLINE // note: GCC creates faster code without forcing inline

	#if defined(__GNUC__) && defined(__GNUC_MINOR__) && !defined(__clang__) // If compiler is GCC/G++
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || __GNUC__ > 4 // 4.2 and below do not support variadic templates
			#define PLF_VARIADICS_SUPPORT
		#endif

		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 4) || __GNUC__ > 4 // 4.3 and below do not support initializer lists
			#define PLF_INITIALIZER_LIST_SUPPORT
		#endif

		#if (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || __GNUC__ < 4
			#define PLF_NOEXCEPT throw()
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator)
			#define PLF_NOEXCEPT_SWAP(the_allocator)
		#elif __GNUC__ < 6
			#define PLF_NOEXCEPT noexcept
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept
			#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept
		#else // C++17 support
			#define PLF_NOEXCEPT noexcept
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_move_assignment::value || std::allocator_traits<the_allocator>::is_always_equal::value)
			#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_swap::value || std::allocator_traits<the_allocator>::is_always_equal::value)
		#endif

		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7) || __GNUC__ > 4
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#endif
		#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 8) || __GNUC__ > 4
			#define PLF_ALIGNMENT_SUPPORT
		#endif
		#if __GNUC__ >= 5 // GCC v4.9 and below do not support std::is_trivially_copyable
			#define PLF_TYPE_TRAITS_SUPPORT
		#endif
	#elif defined(__GLIBCXX__) // Using another compiler type with libstdc++ - we are assuming full c++11 compliance for compiler - which may not be true
		#if __GLIBCXX__ >= 20080606 	// libstdc++ 4.2 and below do not support variadic templates
			#define PLF_VARIADICS_SUPPORT
		#endif
		#if __GLIBCXX__ >= 20090421 	// libstdc++ 4.3 and below do not support initializer lists
			#define PLF_INITIALIZER_LIST_SUPPORT
		#endif
		#if __GLIBCXX__ >= 20160111
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
			#define PLF_NOEXCEPT noexcept
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_move_assignment::value || std::allocator_traits<the_allocator>::is_always_equal::value)
			#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_swap::value || std::allocator_traits<the_allocator>::is_always_equal::value)
		#elif __GLIBCXX__ >= 20120322
			#define PLF_ALLOCATOR_TRAITS_SUPPORT
			#define PLF_NOEXCEPT noexcept
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept
			#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept
		#else
			#define PLF_NOEXCEPT throw()
			#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator)
			#define PLF_NOEXCEPT_SWAP(the_allocator)
		#endif
		#if __GLIBCXX__ >= 20130322
			#define PLF_ALIGNMENT_SUPPORT
		#endif
		#if __GLIBCXX__ >= 20150422 // libstdc++ v4.9 and below do not support std::is_trivially_copyable
			#define PLF_TYPE_TRAITS_SUPPORT
		#endif
	#elif defined(_LIBCPP_VERSION)
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_VARIADICS_SUPPORT
		#define PLF_INITIALIZER_LIST_SUPPORT
		#define PLF_ALIGNMENT_SUPPORT
		#define PLF_NOEXCEPT noexcept
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_move_assignment::value || std::allocator_traits<the_allocator>::is_always_equal::value)
		#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_swap::value || std::allocator_traits<the_allocator>::is_always_equal::value)

		#if !(defined(_LIBCPP_CXX03_LANG) || defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES))
			#define PLF_TYPE_TRAITS_SUPPORT
		#endif
	#else // Assume type traits and initializer support for other compilers and standard libraries
		#define PLF_ALLOCATOR_TRAITS_SUPPORT
		#define PLF_ALIGNMENT_SUPPORT
		#define PLF_VARIADICS_SUPPORT
		#define PLF_INITIALIZER_LIST_SUPPORT
		#define PLF_TYPE_TRAITS_SUPPORT
		#define PLF_NOEXCEPT noexcept
		#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_move_assignment::value || std::allocator_traits<the_allocator>::is_always_equal::value)
		#define PLF_NOEXCEPT_SWAP(the_allocator) noexcept(std::allocator_traits<the_allocator>::propagate_on_container_swap::value || std::allocator_traits<the_allocator>::is_always_equal::value)
	#endif

	#if __cplusplus >= 201703L
		#if defined(__clang__) && ((__clang_major__ == 3 && __clang_minor__ == 9) || __clang_major__ > 3)
			#define PLF_CONSTEXPR constexpr
			#define PLF_CONSTEXPR_SUPPORT
		#elif defined(__GNUC__) && __GNUC__ >= 7
			#define PLF_CONSTEXPR constexpr
			#define PLF_CONSTEXPR_SUPPORT
		#elif !defined(__clang__) && !defined(__GNUC__)
			#define PLF_CONSTEXPR constexpr // assume correct C++17 implementation for other compilers
			#define PLF_CONSTEXPR_SUPPORT
		#else
			#define PLF_CONSTEXPR
		#endif
	#else
		#define PLF_CONSTEXPR
	#endif

	#if __cplusplus > 201703L // C++20
		#if defined(__clang__) && (__clang_major__ >= 10)
			#define PLF_CPP20_SUPPORT
		#elif defined(__GNUC__) && __GNUC__ >= 10
			#define PLF_CPP20_SUPPORT
		#elif !defined(__clang__) && !defined(__GNUC__) // assume correct C++20 implementation for other compilers
			#define PLF_CPP20_SUPPORT
		#endif
	#endif

	#define PLF_MOVE_SEMANTICS_SUPPORT
#else
	#define PLF_FORCE_INLINE
	#define PLF_NOEXCEPT throw()
	#define PLF_NOEXCEPT_SWAP(the_allocator)
	#define PLF_NOEXCEPT_MOVE_ASSIGNMENT(the_allocator)
	#define PLF_CONSTEXPR
#endif



#include <functional> // std::greater
#include <vector>
#include <list>
#include <iostream>

#include "plf_indiesort.h"



void title1(const char *title_text)
{
	std::cout << std::endl << std::endl << std::endl << "*** " << title_text << " ***" << std::endl;
	std::cout << "===========================================" << std::endl << std::endl << std::endl; 
}



void title2(const char *title_text)
{
	std::cout << std::endl << std::endl << "--- " << title_text << " ---" << std::endl << std::endl;
}


void title3(const char *title_text)
{
	std::cout << std::endl << title_text << std::endl;
}



void failpass(const char *test_type, bool condition)
{
	std::cout << "\n" << test_type << ": ";

	if (condition)
	{
		std::cout << "Pass\n\n";
	}
	else
	{
		std::cout << "Fail" << std::endl;
		std::cin.get();
		abort();
	}
}


void breakfail(const char *error_message)
{
	std::cout << error_message << std::endl;
	std::cin.get();
	abort();
}



struct small_struct
{
	double *empty_field_1;
	double unused_number;
	unsigned int empty_field2;
	double *empty_field_3;
	int number;
	unsigned int empty_field4;

	small_struct() PLF_NOEXCEPT: number(0) {};
	small_struct(const int num) PLF_NOEXCEPT: number(num) {};
	int operator * () const { return number; };
	bool operator == (const small_struct &source) const { return source.number == number; };
	bool operator != (const small_struct &source) const { return source.number != number; };
	bool operator > (const small_struct &source) const { return number > source.number; };
	bool operator < (const small_struct &source) const { return number < source.number; };
	bool operator >= (const small_struct &source) const { return number >= source.number; };
	bool operator <= (const small_struct &source) const { return number <= source.number; };
};


int global_counter = 0;

struct small_struct_non_trivial
{
	double *empty_field_1;
	double unused_number;
	unsigned int empty_field2;
	double *empty_field_3;
	int number;
	unsigned int empty_field4;

	small_struct_non_trivial() PLF_NOEXCEPT: number(0) {};
	small_struct_non_trivial(const int num) PLF_NOEXCEPT: number(num) {};
	int operator * () const { return number; };
	bool operator == (const small_struct_non_trivial &source) const { return source.number == number; };
	bool operator != (const small_struct_non_trivial &source) const { return source.number != number; };
	bool operator > (const small_struct_non_trivial &source) const { return number > source.number; };
	bool operator < (const small_struct_non_trivial &source) const { return number < source.number; };
	bool operator >= (const small_struct_non_trivial &source) const { return number >= source.number; };
	bool operator <= (const small_struct_non_trivial &source) const { return number <= source.number; };
};


struct large_struct
{
	int numbers[100];
	char a_string[50];
	double unused_number;
	int number;
	double *empty_field_1;
	double *empty_field_2;
	unsigned int empty_field3;
	unsigned int empty_field4;

	large_struct() PLF_NOEXCEPT: number(0) {};
	large_struct(const int num) PLF_NOEXCEPT: number(num) {};
	int operator * () const { return number; };
	bool operator == (const large_struct &source) const { return source.number == number; };
	bool operator != (const large_struct &source) const { return source.number != number; };
	bool operator > (const large_struct &source) const { return number > source.number; };
	bool operator < (const large_struct &source) const { return number < source.number; };
	bool operator >= (const large_struct &source) const { return number >= source.number; };
	bool operator <= (const large_struct &source) const { return number <= source.number; };
};



// Fast xorshift+128 random number generator function (original: https://codingforspeed.com/using-faster-psudo-random-generator-xorshift/)
unsigned int xor_rand()
{
	static unsigned int x = 123456789;
	static unsigned int y = 362436069;
	static unsigned int z = 521288629;
	static unsigned int w = 88675123;

	const unsigned int t = x ^ (x << 11);

	// Rotate the static values (w rotation in return statement):
	x = y;
	y = z;
	z = w;

	return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}



int main()
{
	freopen("error.log","w", stderr); // For catching assertion failure info when run outside of a command line prompt

	unsigned int looper = 0;

	while (++looper != 600)
	{
		title1("Indiesort");

		{
			title2("Test Basics Int");

			std::vector<int> vec;
			
			for (int i = 60; i != -1; --i)
			{
				vec.push_back(i);
			}
			
			for (int i = 0; i != 60; ++i)
			{
				vec.push_back(i);
			}
			
			plf::indiesort(vec);
			
			int last = 0;
			
			for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				if (last > *it)
				{
					breakfail("Sequential int last > *it!.");
				}
				
				last = *it;
			}

			std::cout << "Sequential int passed\n";

			vec.clear();
			
			
			for (int i = 0; i != 70000; ++i)
			{
				vec.push_back(xor_rand() & 65535);
			}
			
			plf::indiesort(vec, std::greater<int>());
			
			last = 65535;
			
			for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				if (last < *it)
				{
					breakfail("Random int last < *it!.");
				}
				
				last = *it;
			}

			std::cout << "Random int passed\n";
		}

		
		{
			title2("Test Basics small_struct");

			std::vector<small_struct> vec;
			
			for (int i = 60; i != -1; --i)
			{
				vec.push_back(i);
			}
			
			for (int i = 0; i != 60; ++i)
			{
				vec.push_back(i);
			}
			
			plf::indiesort(vec);
			
			small_struct last = 0;
			
			for (std::vector<small_struct>::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				if (last > **it)
				{
					breakfail("Sequential small_struct last > *it!.");
				}
				
				last = **it;
			}

			std::cout << "Sequential Small Struct passed\n";

			vec.clear();
			
			
			for (int i = 0; i != 6000; ++i)
			{
				vec.push_back(xor_rand() & 65535);
			}
			
			plf::indiesort(vec, std::greater<small_struct>());
			
			last = 65535;
			
			for (std::vector<small_struct>::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				if (last < *it)
				{
					breakfail("Random small_struct last < *it!.");
				}
				
				last = *it;
			}

			std::cout << "Random Small Struct passed\n";
		}



		{
			title2("Test Basics C array");

			large_struct *structs = new large_struct[500];

			for (int i = 0; i != 500; ++i)
			{
				structs[i] = xor_rand() & 65535;
			}

			plf::indiesort(&structs[0], &structs[500]);

			large_struct last = 0;

			for (int i = 0; i != 500; ++i)
			{
				if (last > structs[i])
				{
					breakfail("Random large_struct last > *it!.");
				}
				
				last = structs[i];
			}

			std::cout << "Random large_struct C array passed\n";
		}



		{
			title2("Test Basics small_struct_non_trivial");

			std::vector<small_struct_non_trivial> vec;
			
			for (int i = 60; i != -1; --i)
			{
				vec.push_back(i);
			}
			
			for (int i = 0; i != 60; ++i)
			{
				vec.push_back(i);
			}
			
			plf::indiesort(vec);

			small_struct_non_trivial last = 0;
			
			for (std::vector<small_struct_non_trivial>::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				if (last > **it)
				{
					breakfail("Sequential small_struct_non_trivial last > *it!.");
				}
				
				last = **it;
			}

			std::cout << "Sequential small_struct_non_trivial passed\n";

			vec.clear();
			
			
			for (int i = 0; i != 6000; ++i)
			{
				vec.push_back(xor_rand() & 65535);
			}
			
			plf::indiesort(vec, std::greater<small_struct_non_trivial>());
			
			last = 65535;
			
			for (std::vector<small_struct_non_trivial>::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				if (last < *it)
				{
					breakfail("Random small_struct_non_trivial last < *it!.");
				}
				
				last = *it;
			}

			std::cout << "Random small_struct_non_trivial passed\n";
		}



		{
			title2("Test Basics large_struct");

			std::vector<large_struct> vec;
			
			for (int i = 60; i != -1; --i)
			{
				vec.push_back(i);
			}
			
			for (int i = 0; i != 60; ++i)
			{
				vec.push_back(i);
			}
			
			plf::indiesort(vec);
			
			large_struct last = 0;
			
			for (std::vector<large_struct>::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				if (last > **it)
				{
					breakfail("Sequential large_struct last > *it!.");
				}
				
				last = **it;
			}

			std::cout << "Sequential large_struct passed\n";

			vec.clear();
			
			
			for (int i = 0; i != 6000; ++i)
			{
				vec.push_back(xor_rand() & 65535);
			}
			
			plf::indiesort(vec, std::greater<large_struct>());
			
			last = 65535;
			
			for (std::vector<large_struct>::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				if (last < *it)
				{
					breakfail("Random large_struct last < *it!.");
				}
				
				last = *it;
			}

			std::cout << "Random large_struct passed\n";
		}




		{
			title2("std::list int range tests");

			{		
				std::list<int> ivec;
				
				for (int i = 0; i != 2000; ++i)
				{
					ivec.push_back(xor_rand() & 65535);
				}
				
				
				std::list<int>::iterator start = ivec.begin(), end = ivec.end();

				plf::indiesort(start, end);
				

				int last = 0;

				do
				{
					if (last > *start)
					{
						breakfail("Worst-case std::list sort test > *it!.");
					}
					
					last = *start;
				} while (++start != end);

				std::cout << "Worst-case std::list sort test passed\n";
			}



			{
				title2("std::list small_struct range tests");

				std::list<small_struct> vec;
				
				for (int i = 0; i != 5000; ++i)
				{
					vec.push_back(xor_rand() & 65535);
				}
				
				
				std::list<small_struct>::iterator start = vec.begin(), end = vec.end();
				std::advance(start, 150);
				std::advance(end, -300);

				plf::indiesort(start, end);
				

				int last = 0;

				do
				{
					if (last > **start)
					{
						breakfail("Worst-case std::list small_struct sort test > *it!.");
					}
					
					last = **start;
				} while (++start != end);

				std::cout << "Worst-case std::list small_struct sort test passed\n";
			}



			{
				title2("std::list large_struct range tests");

				std::list<large_struct> vec;
				
				for (int i = 0; i != 6000; ++i)
				{
					vec.push_back(xor_rand() & 65535);
				}
				
				
				std::list<large_struct>::iterator start = vec.begin(), end = vec.end();
				std::advance(start, 15);
				std::advance(end, -200);

				plf::indiesort(start, end);
				

				int last = 0;

				do
				{
					if (last > **start)
					{
						breakfail("Worst-case std::list large_struct sort test > *it!.");
					}
					
					last = **start;
				} while (++start != end);

				std::cout << "Worst-case std::list large_struct sort test passed\n";
			}


		}
	}


	title1("All tests passed! Press Enter to Exit.");
	std::cin.get();

	return 0;
}
