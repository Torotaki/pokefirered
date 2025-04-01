#include "global.h"
#include "gflib.h"
#include "party_menu.h"
#include "menu.h"
#include "new_menu_helpers.h"
#include "constants/songs.h"
#include "constants/moves.h"
#include "fldeff_softboiled.h"
#include "battle_controllers.h"
#include "battle_script_commands.h"

void GetHealMove(u8 userPartyId, u8 *pp, u8 *moveIndex);
void Task_DisplayHPRestoredMessageAndClose(u8 taskId);

extern const u8 gText_PkmnHPRestoredByVar2[];

bool8 SetUpFieldMove_FixedHealing(void)
{
    u8 healMovePP, i;
    GetHealMove(GetCursorSelectionMonId(), &healMovePP, &i);
    
    if (healMovePP > 0)
        return TRUE;
    else
        return FALSE;
}

void ChooseMonForFixedHealing(u8 taskId)
{
    gPartyMenu.action = PARTY_ACTION_FIXED_HEAL_MOVE;
    gPartyMenu.slotId2 = gPartyMenu.slotId;
    AnimatePartySlot(GetCursorSelectionMonId(), 1);
    DisplayPartyMenuStdMessage(PARTY_MSG_USE_ON_WHICH_MON);
    gTasks[taskId].func = Task_HandleChooseMonInput;
}

void Task_TryUseFixedHealingOnPartyMon(u8 taskId)
{
    u8 userPartyId = gPartyMenu.slotId;
    u8 recipientPartyId = gPartyMenu.slotId2;
    u16 curHp, healPower;
    u32 move;
    TaskFunc closingTask;
    bool8 isUsedInBattle = gPartyMenu.data[1]; 
    
    if (recipientPartyId > PARTY_SIZE)
    { 
        gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;
        DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
        gTasks[taskId].func = Task_HandleChooseMonInput;
    }
    else
    {
        u8 healMovePP, healMoveIndex;
        GetHealMove(userPartyId, &healMovePP, &healMoveIndex);
        curHp = GetMonData(&gPlayerParty[recipientPartyId], MON_DATA_HP);

        if (isUsedInBattle && userPartyId == recipientPartyId)
        {
            ApplyFixedHealToActiveMon();
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
            return;
        }

        if (curHp == 0
            || healMovePP < 1
            || GetMonData(&gPlayerParty[recipientPartyId], MON_DATA_MAX_HP) == curHp)
            CantUseSoftboiledOnMon(taskId);
        else
        {
            PlaySE(SE_USE_ITEM);
            healMovePP -= 1;
            move = GetMonData(&gPlayerParty[userPartyId], MON_DATA_MOVE1 + healMoveIndex);
            healPower = gBattleMoves[move].power;
            SetMonData(&gPlayerParty[userPartyId], MON_DATA_PP1 + healMoveIndex, &healMovePP);

            if (isUsedInBattle)
            {
                gBattlescriptCurrInstr += 6;
                closingTask = Task_DisplayHPRestoredMessageAndClose;
            } else {
                closingTask = Task_DisplayHPRestoredMessage;
            }

            PartyMenuModifyHP(taskId, recipientPartyId, 1, healPower, closingTask);
        }
    }
}

void GetHealMove(u8 userPartyId, u8 *pp, u8 *moveIndex)
{
    u8 i, j;
    s16 fieldMove = gPartyMenu.data[0];

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = GetMonData(&gPlayerParty[userPartyId], MON_DATA_MOVE1 + i);        
        if (isMoveFieldMove(fieldMove, move))
        {
            *pp = GetMonData(&gPlayerParty[userPartyId], MON_DATA_PP1 + i);
            *moveIndex = i;

            if (*pp != 0)
            {
                return;
            }
        }
    }
}

void Task_DisplayHPRestoredMessageAndClose(u8 taskId)
{
    GetMonNickname(&gPlayerParty[gPartyMenu.slotId2], gStringVar1);
    StringExpandPlaceholders(gStringVar4, gText_PkmnHPRestoredByVar2);
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = Task_ClosePartyMenuAfterText;
}
