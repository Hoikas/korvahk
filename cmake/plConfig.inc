/* This file is part of Korvahk.
 *
 * Korvahk is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Korvahk is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Korvahk.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/** Indicates that we are targetting The Path of the Shell. */
#cmakedefine PLASMA_TPOTS

/** Indicates that we are targetting Myst Online: Uru Live. */
#cmakedefine PLASMA_MOUL

/** Indicates that hsTArrays are std::vectors. */
#cmakedefine PLASMA_TARRAY_IS_VECTOR

/** Indicates that BOOLs are integers. */
#cmakedefine PLASMA_WIN32_BOOLS

/** Indicates that hsRefCount is atomic. */
#cmakedefine PLASMA_ATOMIC_REFCOUNT

/** Indicates that Plasma uses ST::string for string handling. */
#cmakedefine PLASMA_HAVE_STRING_THEORY
