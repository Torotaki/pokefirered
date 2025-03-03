#include "badge.h"

int GetBadgesEarned(void)
{
    u16 flagId;
    int nbadges = 0;
    for (flagId = FLAG_BADGE01_GET; flagId < FLAG_BADGE01_GET + NUM_BADGES; flagId++)
    {
        if (FlagGet(flagId))
            nbadges++;
    }

    return nbadges;
}