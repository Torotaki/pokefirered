#include "global.h"
#include "gflib.h"
#include "field_player_avatar.h"
#include "field_effect.h"
#include "party_menu.h"
#include "script.h"
#include "event_data.h"
#include "fldeff.h"
#include "event_scripts.h"
#include "field_weather.h"
#include "wild_encounter.h"
#include "field_specials.h"
#include "fieldmap.h"
#include "constants/songs.h"

static EWRAM_DATA u8 *sPlttBufferBak = NULL;

static void FieldCallback_MagnetPull(void);
static void StartMagnetPullFieldEffect(void);
static void TryMagnetPullEncounter(u8 taskId);
static void FailMagnetPullEncounter(u8 taskId);
static void PickUpHiddenItem(u8 taskId);
static bool8 HiddenItemIsWithinRangeOfPlayer(u8 taskId);
static void HiddenItemOnMapIsWithinRangeOfPlayer(u8 taskId, const struct MapEvents * events, s16 x, s16 y);
static void RegisterHiddenItemRelativeCoordsIfCloser(u8 taskId, s16 dx, s16 dy, u32 hiddenItem);
static void PrepareHiddenItemForPickup(u32 hiddenItem);
static void FindHiddenItemsInConnectedMaps(u8 taskId);

#define tDistance data[0]
#define tHiddenItemFound data[1]

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
            else if (HiddenItemIsWithinRangeOfPlayer(taskId))
            {
                gTasks[taskId].func = PickUpHiddenItem;
                BeginNormalPaletteFade(~(1 << (gSprites[GetPlayerAvatarObjectId()].oam.paletteNum + 16)), 4, 8, 0, RGB(31, 31, 0));
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

static void PickUpHiddenItem(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CpuFastCopy(sPlttBufferBak, gPlttBufferUnfaded, PLTT_SIZE);
        WeatherProcessingIdle();
        Free(sPlttBufferBak);
        ScriptContext_SetupScript(EventScript_HiddenItemScript);
        DestroyTask(taskId);
    }
}

static bool8 HiddenItemIsWithinRangeOfPlayer(u8 taskId)
{
    s16 x, y, i, dx, dy;
    PlayerGetDestCoords(&x, &y);
    HiddenItemOnMapIsWithinRangeOfPlayer(taskId, gMapHeader.events, x, y);
    FindHiddenItemsInConnectedMaps(taskId);
    return gTasks[taskId].tHiddenItemFound;
}

static void HiddenItemOnMapIsWithinRangeOfPlayer(u8 taskId, const struct MapEvents * events, s16 x, s16 y)
{
    s16 i, dx, dy;

    for (i = 0; i < events->bgEventCount; i++)
    {
        if (events->bgEvents[i].kind == 7 && !FlagGet(GetHiddenItemAttr(events->bgEvents[i].bgUnion.hiddenItem, HIDDEN_ITEM_FLAG)))
        {
            dx = events->bgEvents[i].x + 7 - x;
            dy = events->bgEvents[i].y + 7 - y;
            if (
                dx >= -7
             && dx <=  7
             && dy >= -5
             && dy <=  5
            )
            {
                if (GetHiddenItemAttr(events->bgEvents[i].bgUnion.hiddenItem, HIDDEN_ITEM_UNDERFOOT) != TRUE)
                    RegisterHiddenItemRelativeCoordsIfCloser(taskId, dx, dy, events->bgEvents[i].bgUnion.hiddenItem);
            }
        }
    }
}

static void RegisterHiddenItemRelativeCoordsIfCloser(u8 taskId, s16 dx, s16 dy, u32 hiddenItem)
{
    s16 *data = gTasks[taskId].data;
    s16 distance;

    if (tHiddenItemFound == FALSE)
    {
        tDistance = dx * dx + dy * dy;
        tHiddenItemFound = TRUE;
        PrepareHiddenItemForPickup(hiddenItem);
    }
    else
    {
        distance = dx * dx + dy * dy;
        if (distance < tDistance)
        {
            tDistance = distance;
            tHiddenItemFound = TRUE;
            PrepareHiddenItemForPickup(hiddenItem);
        }
    }
}

static void PrepareHiddenItemForPickup(u32 hiddenItem)
{
    gSpecialVar_0x8005 = GetHiddenItemAttr(hiddenItem, HIDDEN_ITEM_ITEM);
    gSpecialVar_0x8004 = GetHiddenItemAttr(hiddenItem, HIDDEN_ITEM_FLAG);
    gSpecialVar_0x8006 = GetHiddenItemAttr(hiddenItem, HIDDEN_ITEM_QUANTITY);
}

static void FindHiddenItemsInConnectedMaps(u8 taskId)
{
    s32 connectionsCount;
    const struct MapConnection *connection;
    const struct MapHeader * mapHeader;
    s32 i;
    s16 playerX, playerY, relativePlayerX, relativePlayerY;
    bool8 connectionIsDirectional;

    if (gMapHeader.connections)
    {
        PlayerGetDestCoords(&playerX, &playerY);
        connectionsCount = gMapHeader.connections->count;
        connection = gMapHeader.connections->connections;

        for (i = 0; i < connectionsCount; i++, connection++)
        {
            mapHeader = GetMapHeaderFromConnection(connection);
            connectionIsDirectional = TRUE;

            switch (connection->direction)
            {
            case CONNECTION_NORTH:
                relativePlayerX = playerX - connection->offset;
                relativePlayerY = playerY + mapHeader->mapLayout->height;
                break;
            case CONNECTION_SOUTH:
                relativePlayerX = playerX - connection->offset;
                relativePlayerY = playerY - gMapHeader.mapLayout->height;
                break;
            case CONNECTION_WEST:
                relativePlayerX = playerX + mapHeader->mapLayout->width;
                relativePlayerY = playerY - connection->offset;
                break;
            case CONNECTION_EAST:
                relativePlayerX = playerX - gMapHeader.mapLayout->width;
                relativePlayerY = playerY - connection->offset;
                break;
            default:
                connectionIsDirectional = FALSE;
                break;
            }

            if (connectionIsDirectional)
            {
                HiddenItemOnMapIsWithinRangeOfPlayer(taskId, mapHeader->events, relativePlayerX, relativePlayerY);
            }
        }
    }
}
