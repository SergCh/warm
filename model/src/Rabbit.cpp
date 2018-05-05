#include "Rabbit.h"

bool Rabbit::step() {
    if (m_live < 0)
        return true;
    if (m_live > 0)
        m_live--;
    return m_live != 0;
}
