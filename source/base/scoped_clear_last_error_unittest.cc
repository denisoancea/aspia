//
// Aspia Project
// Copyright (C) 2018 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#include <gtest/gtest.h>

#include "base/scoped_clear_last_error.h"

#if defined(OS_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // defined(OS_WIN)

namespace aspia {

TEST(ScopedClearLastError, test_no_error)
{
    errno = 1;
    {
        ScopedClearLastError clear_error;
        EXPECT_EQ(0, errno);
    }
    EXPECT_EQ(1, errno);
}

TEST(ScopedClearLastError, test_error)
{
    errno = 1;
    {
        ScopedClearLastError clear_error;
        errno = 2;
    }
    EXPECT_EQ(1, errno);
}

#if defined(OS_WIN)

TEST(ScopedClearLastError, test_no_error_win)
{
    ::SetLastError(1);
    {
        ScopedClearLastError clear_error;
        EXPECT_EQ(0, ::GetLastError());
    }
    EXPECT_EQ(1, ::GetLastError());
}

TEST(ScopedClearLastError, test_error_win)
{
    ::SetLastError(1);
    {
        ScopedClearLastError clear_error;
        ::SetLastError(2);
    }
    EXPECT_EQ(1, ::GetLastError());
}

#endif  // defined(OS_WIN)

} // namespace aspia