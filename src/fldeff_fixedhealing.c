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
#include "../include/constants/battle_move_effects.h"

void GetHealMove(u8 userPartyId, u8 *pp, u8 *moveIndex);
void Task_DisplayHPRestoredMessageAndClose(u8 taskId);
void Task_DisplayReviveHPRestoredMessage(u8 taskId);

extern const u8 gText_PkmnHPRestoredByVar2[];
extern const u8 gText_PkmnFellAsleep[];
TaskFunc endingTask;

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
    u16 curHp, maxHp, healPower;
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
        if (isUsedInBattle && userPartyId == recipientPartyId) 
        {
            ApplyFixedHealToActiveMon();
            gTasks[taskId].func = Task_ClosePartyMenuAfterText;
            return;
        }
        
        curHp = GetMonData(&gPlayerParty[recipientPartyId], MON_DATA_HP);
        maxHp = GetMonData(&gPlayerParty[recipientPartyId], MON_DATA_MAX_HP);
        
        if (curHp == 0
            || maxHp == curHp)
            CantUseSoftboiledOnMon(taskId);
        else
        {
            PlaySE(SE_USE_ITEM);
            if (isUsedInBattle) {
                move = gCurrentMove;

                gBattlescriptCurrInstr += 6;
                closingTask = Task_DisplayHPRestoredMessageAndClose;
            } else {
                u8 healMovePP, healMoveIndex;

                GetHealMove(userPartyId, &healMovePP, &healMoveIndex);
                healMovePP -= 1;
                move = GetMonData(&gPlayerParty[userPartyId], MON_DATA_MOVE1 + healMoveIndex);
                SetMonData(&gPlayerParty[userPartyId], MON_DATA_PP1 + healMoveIndex, &healMovePP);

                closingTask = Task_DisplayHPRestoredMessage;
            }
            
            switch (gBattleMoves[move].effect)
            {
            case EFFECT_HEAL_ALLY_PERCENT:
                healPower = gBattleMoves[move].power * maxHp / 100;
                break;
            case EFFECT_HEAL_ALLY_FIXED:
            default:
                healPower = gBattleMoves[move].power;
                break;
            }

            if (GetMonAbility(&gPlayerParty[userPartyId]) == ABILITY_MEDIC)
            {
                healPower += GetMonData(&gPlayerParty[userPartyId], MON_DATA_MAX_HP) / 8;
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

void Task_TryUseReviveOnPartyMon(u8 taskId)
{
    u8 userPartyId = gPartyMenu.slotId;
    u8 recipientPartyId = gPartyMenu.slotId2;
    u16 maxHp, healPower;
    u32 move;
    TaskFunc closingTask;
    u8 recipientHp;
    bool8 isUsedInBattle = gPartyMenu.data[1];
    recipientHp = GetMonData(&gPlayerParty[recipientPartyId], MON_DATA_HP);
    
    if (recipientPartyId > PARTY_SIZE)
    { 
        gPartyMenu.action = PARTY_ACTION_CHOOSE_MON;
        DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
        gTasks[taskId].func = Task_HandleChooseMonInput;
    }
    else if (recipientHp != 0)
    {
        PlaySE(SE_FAILURE);
    }
    else
    {
        PlaySE(SE_USE_ITEM);
        if (isUsedInBattle) {
            move = gCurrentMove;

            gBattlescriptCurrInstr += 5;
            endingTask = Task_ClosePartyMenuAfterText;
        } else {
            u8 healMovePP, healMoveIndex;

            GetHealMove(userPartyId, &healMovePP, &healMoveIndex);
            healMovePP -= 1;
            move = GetMonData(&gPlayerParty[userPartyId], MON_DATA_MOVE1 + healMoveIndex);
            SetMonData(&gPlayerParty[userPartyId], MON_DATA_PP1 + healMoveIndex, &healMovePP);

            endingTask = Task_FinishSoftboiled;
        }
        maxHp = GetMonData(&gPlayerParty[recipientPartyId], MON_DATA_MAX_HP);

        healPower = gBattleMoves[move].power * maxHp / 100;

        if (GetMonAbility(&gPlayerParty[userPartyId]) == ABILITY_MEDIC)
        {
            healPower += GetMonData(&gPlayerParty[userPartyId], MON_DATA_MAX_HP) / 8;
        }

        if (healPower == 0)
        {
            healPower = 1;
        }

        PartyMenuModifyHP(taskId, recipientPartyId, 1, healPower, Task_DisplayReviveHPRestoredMessage);
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

void Task_DisplayReviveHPRestoredMessage(u8 taskId)
{
    StringCopy(gStringVar4, gStringVar2);
    UpdatePartyMonAilmentGfxBySlotId(gPartyMenu.slotId2);
    StringCopy(gStringVar2, gStringVar4);
    GetMonNickname(&gPlayerParty[gPartyMenu.slotId2], gStringVar1);
    StringExpandPlaceholders(gStringVar4, gText_PkmnHPRestoredByVar2);
    DisplayPartyMenuMessage(gStringVar4, FALSE);
    ScheduleBgCopyTilemapToVram(2);
    gTasks[taskId].func = endingTask;
}

void Task_TryUseMoveOnPartyMon(u8 taskId)
{
    if (gPartyMenu.data[1])
    {
        // We are in battle
        switch (gPartyMenu.data[0])
        {
        case EFFECT_HEAL_ALLY_FIXED:
        case EFFECT_HEAL_ALLY_PERCENT:
            Task_TryUseFixedHealingOnPartyMon(taskId);
            break;
        case EFFECT_REVIVE:
            Task_TryUseReviveOnPartyMon(taskId);
            break;
        }
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
    case FIELD_MOVE_REVIVE:
        Task_TryUseReviveOnPartyMon(taskId);
        break;
    default:
        break;
    }
}
