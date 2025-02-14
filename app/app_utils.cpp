// SPDX-License-Identifier: GPL-2.0-or-later

#include <climits>
#include <cstdlib>

namespace Util {
bool strtol(const char* nptr, long& n) {
  if (!nptr || *nptr == '\0')
    return false;
  char* endptr = nullptr;
  long tmp = std::strtol(nptr, &endptr, 10);
  if (*endptr != '\0')
    return false;
  if (tmp == LONG_MAX || tmp == LONG_MIN)
    return false;
  n = tmp;
  return true;
}

}  // namespace Util
