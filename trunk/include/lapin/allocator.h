/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

/*!
** \file allocator.h
** The allocator module contains functions to reserve memory with a specific fashion:
** with a specific limit of memory, with harsh bound checking (to make the software crash)
** and since the 1.11, to handle wave allocation.
*/

#ifndef				__LAPIN_ALLOCATOR_H__
# define			__LAPIN_ALLOCATOR_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The LAPIN_ALLOCATOR_OVERLOAD should be defined inside your Makefile with the -D option
** for GCC. The purpose of this macro is to transform every calls to malloc, calloc, realloc
** and free into calls to their bunny equivalent without having to change your code.
*/
# ifdef				LAPIN_ALLOCATOR_OVERLOAD
#  define			malloc						bunny_malloc
#  define			calloc						bunny_calloc
#  define			realloc						bunny_realloc
#  define			free						bunny_free
# endif

/*!
** The LAPIN_ALLOCATOR_DEACTIVATED should be defined inside your Makefile with the -D option
** for GCC. The purpose of this macro is to transform every calls to bunny_malloc, bunny_calloc,
** bunny_realloc and bunny_free to their standard equivalent without having to change your code.
** Considering that tools like valgrind cannot help you to debug if you use the bunny allocator,
** deactivating it may help you during your debugging.
*/
# ifdef				LAPIN_ALLOCATOR_DEACTIVATED
#  define			bunny_malloc					malloc
#  define			bunny_calloc					calloc
#  define			bunny_realloc					realloc
#  define			bunny_free					free
# endif

/*!
** Reserve a sent amount of bytes and return a pointer to it. If there is not enough
** memory available, the function returns NULL.
** \param siz The amount, in bytes, of data to reserve
** \return The address of the first byte of the allocated data. NULL if an error happened.
*/
void				*bunny_malloc(size_t				siz);

/*!
** Reserve a quantity of chunk of memories and return a pointer to the first of them.
** All bytes are reset before being returned. If there is not enough memory available,
** the function returns NULL.
** \param num The quantity of elements to reserve.
** \param siz The size of one single element.
** \return The address of the first byte of the first allocated element. NULL if an error happened.
*/
void				*bunny_calloc(size_t				num,
					      size_t				siz);
/*!
** Resize the space previously reserved at the sent address. The new size is given.
** If ptr is NULL, then calling bunny_realloc is the same as calling bunny_malloc with
** the given size.
** If ptr is not NULL but size is zero, then it is equivalent to calling bunny_free with
** the given pointer.
** There is no guarantee that the address will not change, even if the new  size is smaller
** than the original one, contrary to the standard realloc.
** The pointer validity is evaluated during bunny_realloc. If the pointer is invalid,
** your program will crash.
** \param ptr The address of the memory space to resize.
** \param siz The new size
** \return The new address of the data. NULL if an error happened. The original buffer
** is left unchanged if this happen.
*/
void				*bunny_realloc(void				*ptr,
					       size_t				siz);
/*!
** Make the given chunk of memory available again for a future call of bunny_malloc,
** bunny_calloc or bunny_realloc. Validity of the pointer is checked during this function,
** so if your pointer is invalid, your program will crash.
** \param ptr The address of the first byte of the memory space to free.
*/
void				bunny_free(void					*ptr);

/*!
** This function allow you to ask a memory checkup at the end of your program.
** The amount of asked bytes, of chunks, how many of them remains, etc.
** It also makes a memory check that will make your program crash if a buffer overflow
** occured previously.
** \param chk Activate or deactivate the memory check.
*/
void				bunny_set_memory_check(bool			chk);

/*!
** This function takes an amount of byte that will be the maximum amount of memory
** that the program will be able to use, allocator meta-datas included.
** This function must be called before any other allocation.
** \param byt The quantity of bytes the program will be allowed to use.
*/
void				bunny_set_maximum_ram(size_t			byt);

#endif	/*		__LAPIN_ALLOCATOR_H__	*/
