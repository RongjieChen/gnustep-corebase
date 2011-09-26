/* atomic_ops.h
   
   Copyright (C) 2011 Free Software Foundation, Inc.
   
   Written by: Stefan Bidigaray
   Date: September, 2011
   
   This file is part of GNUstep CoreBase Library.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; see the file COPYING.LIB.
   If not, see <http://www.gnu.org/licenses/> or write to the 
   Free Software Foundation, 51 Franklin Street, Fifth Floor, 
   Boston, MA 02110-1301, USA.
*/

#ifndef __ATOMIC_OPS_H__
#define __ATOMIC_OPS_H__ 1

#if	_WIN32
#include <windows.h>
#ifndef _WIN64
#undef InterlockedIncrement
#undef InterlockedDecrement
LONG WINAPI InterlockedIncrement(LONG volatile *);
LONG WINAPI InterlockedDecrement(LONG volatile *);
#endif

#define	CF_ATOMIC_INC(X) InterlockedIncrement((LONG volatile*)X)
#define	CF_ATOMIC_DEC(X) InterlockedDecrement((LONG volatile*)X)

#elif defined(__FreeBSD__)
#include <sys/types.h>
#include <machine/atomic.h>
#define CF_ATOMIC_INC(X) atomic_fetchadd_long (X, 1)
#define CF_ATOMIC_DEC(X) atomic_fetchadd_long (X, -1)

#elif defined(__llvm__) \
      || (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))
#define CF_ATOMIC_INC(X) __sync_add_and_fetch(X, 1)
#define CF_ATOMIC_DEC(X) __sync_sub_and_fetch(X, 1)

#endif

#endif /* __ATOMIC_OPS_H__ */