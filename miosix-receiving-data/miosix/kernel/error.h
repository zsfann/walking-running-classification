/***************************************************************************
 *   Copyright (C) 2010 by Terraneo Federico                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#ifndef ERROR_H
#define	ERROR_H

namespace miosix {

/**
 * \enum Error
 * This enum will be passed as argument to the error handler.<br>
 * If the error is marked UNRECOVERABLE, then the error handler will not return.
 */
enum Error
{
    /// The heap is full, malloc/new returned NULL.<br>Error is UNRECOVERABLE
    OUT_OF_MEMORY,

    /// The stack of a thread overflowed.<br>Error is UNRECOVERABLE
    STACK_OVERFLOW,

    /// Unexpected error occurred.<br>Error is UNRECOVERABLE
    UNEXPECTED,

    /// A call to restartKernel that does not match a previous call
    /// to pauseKernel<br>Error is UNRECOVERABLE
    PAUSE_KERNEL_NESTING,

    /// A call to enableInterrupts that does not match a previous call
    /// to disableInterrupts<br>Error is UNRECOVERABLE
    DISABLE_INTERRUPTS_NESTING,

    /// An attempt to lock twice a non recursive mutex happened.<br>
    /// Error is UNRECOVERABLE
    MUTEX_DEADLOCK,

    /// The calls to pauseKernel or disableInterrupts were nested too
    ///much. Error is UNRECOVERABLE
    NESTING_OVERFLOW,

    /// Interrupts are wrongly enabled during boot
    /// Error is UNRECOVERABLE
    INTERRUPTS_ENABLED_AT_BOOT
};

/**
 * Handles errors generated by kernel.
 * Prints an error message on the Console (only if WITH_ERRLOG is defined
 * in miosix_config.h).
 * For information about possible errors, see the enum Error
 * Can be called with the kernel not started, started, paused, with interrupts
 * disabled and within an interrupt routine.
 */
void errorHandler(Error e);

} //namespace miosix

#endif	//ERROR_H
