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
extern const u8 gText_PkmnFellAsleep[];

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

void Task_TryUseSleepOnPartyMon(u8 taskId)
{
    u8 userPartyId = gPartyMenu.slotId;
    u8 recipientPartyId = gPartyMenu.slotId2;
    u32 move;
    TaskFunc closingTask;
    u8 recipientHp;
    recipientHp = GetMonData(&gPlayerParty[recipientPartyId], MON_DATA_HP);
    
    if (recipientPartyId > PARTY_SIZE)
    { 
        gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;
        DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
        gTasks[taskId].func = Task_HandleChooseMonInput;
    }
    else if (recipientHp == 0)
    {
        PlaySE(SE_FAILURE);
    }    
    else
    {
        u8 healMovePP, healMoveIndex;
        u8 status = STATUS1_SLEEP;
        GetHealMove(userPartyId, &healMovePP, &healMoveIndex);

        if (healMovePP < 1)
            CantUseSoftboiledOnMon(taskId);
        else
        {
            PlaySE(SE_M_SING);
            healMovePP -= 1;
            SetMonData(&gPlayerParty[userPartyId], MON_DATA_PP1 + healMoveIndex, &healMovePP);
            SetMonData(&gPlayerParty[recipientPartyId], MON_DATA_STATUS, &status);
            
            UpdatePartyMonAilmentGfxBySlotId(recipientPartyId);

            GetMonNickname(&gPlayerParty[gPartyMenu.slotId2], gStringVar1);
            StringExpandPlaceholders(gStringVar4, gText_PkmnFellAsleep);
            DisplayPartyMenuMessage(gStringVar4, FALSE);
            ScheduleBgCopyTilemapToVram(2);
            gTasks[taskId].func = Task_FinishSoftboiled;
        }
    }
}

void GetHealMove(u8 userPartyId, u8 *pp, u8 *moveIndex)
{
    u8 i, j;
    s16 fieldMove = gPartyMenu.data[0];

    if (gPartyMenu.data[1])
    {
        *moveIndex = gCurrentMove;
        *pp = GetMonData(&gPlayerParty[userPartyId], MON_DATA_PP1 + moveIndex);
        return;
    }

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

void Task_TryUseMoveOnPartyMon(u8 taskId)
{
    if (gPartyMenu.data[1])
    {
        // We are in battle
        Task_TryUseFixedHealingOnPartyMon(taskId);
        return;
    }

    switch (gPartyMenu.data[0])
    {
    case FIELD_MOVE_HEALING_SEED:
    case FIELD_MOVE_PATCH_UP:
        Task_TryUseFixedHealingOnPartyMon(taskId);
        break;
    case FIELD_MOVE_SING:
        Task_TryUseSleepOnPartyMon(taskId);
        break;
    default:
        break;
    }
}
