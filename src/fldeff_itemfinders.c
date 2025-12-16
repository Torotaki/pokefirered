#include "global.h"
#include "gflib.h"
#include "field_player_avatar.h"
#include "field_effect.h"
#include "party_menu.h"
#include "script.h"
#include "fldeff.h"
#include "event_scripts.h"
#include "field_weather.h"
#include "wild_encounter.h"
#include "constants/songs.h"

static EWRAM_DATA u8 *sPlttBufferBak = NULL;

static void FieldCallback_MagnetPull(void);
static void StartMagnetPullFieldEffect(void);
static void TryMagnetPullEncounter(u8 taskId);
static void FailMagnetPullEncounter(u8 taskId);

bool8 SetUpFieldMove_MagnetPull(void)
{
    gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
    gPostMenuFieldCallback = FieldCallback_MagnetPull;
    return TRUE;
}

static void FieldCallback_MagnetPull(void)
{
    FieldEffectStart(FLDEFF_MAGNET_PULL);
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
}

bool8 FldEff_MagnetPull(void)
{
    u8 taskId;

    SetWeatherScreenFadeOut();
    taskId = CreateFieldEffectShowMon();
    FLDEFF_SET_FUNC_TO_DATA(StartMagnetPullFieldEffect);
    return FALSE;
}

static void StartMagnetPullFieldEffect(void)
{
    u8 taskId;

    PlaySE(SE_M_SWEET_SCENT);
    sPlttBufferBak = (u8 *)Alloc(PLTT_SIZE);
    CpuFastCopy(gPlttBufferUnfaded, sPlttBufferBak, PLTT_SIZE);
    CpuFastCopy(gPlttBufferFaded, gPlttBufferUnfaded, PLTT_SIZE);
    BeginNormalPaletteFade(~(1 << (gSprites[GetPlayerAvatarObjectId()].oam.paletteNum + 16)), 4, 0, 8, RGB(31, 31, 0));
    taskId = CreateTask(TryMagnetPullEncounter, 0);
    gTasks[taskId].data[0] = 0;
    FieldEffectActiveListRemove(FLDEFF_MAGNET_PULL);
}

static void TryMagnetPullEncounter(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (data[0] == 64)
        {
            data[0] = 0;
            if (MagnetPullWildEncounter() == TRUE)
            {
                Free(sPlttBufferBak);
                DestroyTask(taskId);
            }
            else
            {
                gTasks[taskId].func = FailMagnetPullEncounter;
                BeginNormalPaletteFade(~(1 << (gSprites[GetPlayerAvatarObjectId()].oam.paletteNum + 16)), 4, 8, 0, RGB(31, 31, 0));
            }
        }
        else
        {
            data[0]++;
        }
    }
}

static void FailMagnetPullEncounter(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CpuFastCopy(sPlttBufferBak, gPlttBufferUnfaded, PLTT_SIZE);
        WeatherProcessingIdle();
        Free(sPlttBufferBak);
        ScriptContext_SetupScript(EventScript_FailSweetScent);
        DestroyTask(taskId);
    }
}
