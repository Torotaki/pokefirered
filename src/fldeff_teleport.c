#include "global.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fldeff.h"
#include "party_menu.h"
#include "overworld.h"

static void FieldCallback_Teleport(void);
static void StartTeleportFieldEffect(void);

bool8 SetUpFieldMove_Teleport(void)
{
    gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
    gPostMenuFieldCallback = FieldCallback_Teleport;
    return TRUE;
}

static void FieldCallback_Teleport(void)
{
    Overworld_ResetStateAfterTeleport();
    FieldEffectStart(FLDEFF_USE_TELEPORT);
    gFieldEffectArguments[0] = (u32)GetCursorSelectionMonId();
}

bool8 FldEff_UseTeleport(void)
{
    u8 taskId = CreateFieldEffectShowMon();
    FLDEFF_SET_FUNC_TO_DATA(StartTeleportFieldEffect);
    SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ON_FOOT);
    return FALSE;
}

static void StartTeleportFieldEffect(void)
{
    FieldEffectActiveListRemove(FLDEFF_USE_TELEPORT);
    CreateTeleportFieldEffectTask();
}
