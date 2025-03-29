#ifndef GUARD_FLDEFF_SOFTBOILED_H
#define GUARD_FLDEFF_SOFTBOILED_H

#include "global.h"

void Task_SoftboiledRestoreHealth(u8 taskId);
void Task_DisplayHPRestoredMessage(u8 taskId);
void Task_FinishSoftboiled(u8 taskId);
void CantUseSoftboiledOnMon(u8 taskId);

#endif // GUARD_FLDEFF_SOFTBOILED_H
