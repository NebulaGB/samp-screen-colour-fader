#if defined _SCF_included
    #endinput
#endif
#define _SCF_included

#include <open.mp>
#include <colour-manipulation>

#define SetPlayerScreenColor SetPlayerScreenColour
#define GetPlayerScreenColor GetPlayerScreenColour
#define FadePlayerScreenColor FadePlayerScreenColour
#define StopPlayerScreenColorFade StopPlayerScreenColourFade
#define OnScreenColorFadeComplete OnScreenColourFadeComplete

enum screenColourFadeData 
{
    sSteps,
    sCurrentStep,

    sOriginalColour,
    sFinalColour,

    sTimer,

    sRegionX,
    sRegionY,
    sRegionWidth,
    sRegionHeight 
}

static
    ScreenColour[MAX_PLAYERS],
    Text:ScreenColourTD,
    ScreenColourFadeData[MAX_PLAYERS][screenColourFadeData]
;

forward public OnScreenColourFadeComplete(playerid);

static stock _SetPlayerScreenColour(playerid, colour) 
{
    ScreenColour[playerid] = colour;

    TextDrawBoxColour(ScreenColourTD, ScreenColour[playerid]);
    TextDrawShowForPlayer(playerid, ScreenColourTD);
}

stock SetPlayerScreenColour(playerid, colour) 
{
    if (!IsPlayerConnected(playerid)) 
    {
        return 0;
    }

    _SetPlayerScreenColour(playerid, colour);
    return 1;
}

stock GetPlayerScreenColour(playerid) 
{
    if (!IsPlayerConnected(playerid)) 
    {
        return 0x00000000;
    }

    return ScreenColour[playerid];
}

static stock _KillScreenColourFadeTimer(playerid) 
{
    KillTimer(ScreenColourFadeData[playerid][sTimer]);

    ScreenColourFadeData[playerid][sTimer] = -1;
}

stock FadePlayerScreenColour(playerid, colour, time, steps) 
{
    if (!IsPlayerConnected(playerid) || steps < 1 || time < 0) 
    {
        return 0;
    }

    if (ScreenColourFadeData[playerid][sTimer] != -1) 
    {
        KillTimer(ScreenColourFadeData[playerid][sTimer]);
    }

    ScreenColourFadeData[playerid][sOriginalColour] = ScreenColour[playerid];
    ScreenColourFadeData[playerid][sFinalColour] = colour;

    ScreenColourFadeData[playerid][sSteps] = steps;
    ScreenColourFadeData[playerid][sCurrentStep] = 0;

    ScreenColourFadeData[playerid][sTimer] = SetTimerEx("ScreenColourFadeTimer", time / steps, true, "i", playerid);

    return 1;
}

stock StopPlayerScreenColourFade(playerid) 
{
    if (!IsPlayerConnected(playerid) || ScreenColourFadeData[playerid][sTimer] == -1) 
    {
        return 0;
    }

    _KillScreenColourFadeTimer(playerid);
    return 1;
}

forward ScreenColourFadeTimer(playerid);
public ScreenColourFadeTimer(playerid) 
{
    if (ScreenColourFadeData[playerid][sCurrentStep] == ScreenColourFadeData[playerid][sSteps]) 
    {
        _KillScreenColourFadeTimer(playerid);

        CallLocalFunction("OnScreenColourFadeComplete", "i", playerid);
        return 1;
    }

    _SetPlayerScreenColour(playerid, InterpolateColours(ScreenColourFadeData[playerid][sOriginalColour], ScreenColourFadeData[playerid][sFinalColour], float(ScreenColourFadeData[playerid][sCurrentStep] + 1) / float(ScreenColourFadeData[playerid][sSteps])));

    ScreenColourFadeData[playerid][sCurrentStep]++;
    return 1;
}

public OnGameModeInit() 
{
    ScreenColourTD = TextDrawCreate(0.0, 0.0, "_");
    TextDrawTextSize(ScreenColourTD, 640.0, 480.0);
    TextDrawLetterSize(ScreenColourTD, 0.0, 50.0);
    TextDrawUseBox(ScreenColourTD, true);

    #if defined SCF_OnGameModeInit
        return SCF_OnGameModeInit();
    #else
        return 1;
    #endif
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SCF_OnGameModeInit

#if defined SCF_OnGameModeInit
    forward SCF_OnGameModeInit();
#endif

public OnPlayerConnect(playerid) 
{
    ScreenColourFadeData[playerid][sTimer] = -1;

    _SetPlayerScreenColour(playerid, 0x00000000);

    #if defined SCF_OnPlayerConnect
        return SCF_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}

stock FadeAllPlayersScreenColour(colour, time, steps) {
    for (new playerid = 0; playerid < MAX_PLAYERS; playerid++) 
    {
        if (IsPlayerConnected(playerid)) 
        {
            FadePlayerScreenColour(playerid, colour, time, steps);
        }
    }
    return 1;
}

stock FadePlayerScreenColourRegion(playerid, colour, time, steps, x, y, width, height) 
{
    if (!IsPlayerConnected(playerid) || steps < 1 || time < 0) 
    {
        return 0;
    }

    if (ScreenColourFadeData[playerid][sTimer] != -1) 
    {
        KillTimer(ScreenColourFadeData[playerid][sTimer]);
    }

    ScreenColourFadeData[playerid][sOriginalColour] = ScreenColour[playerid];
    ScreenColourFadeData[playerid][sFinalColour] = colour;

    ScreenColourFadeData[playerid][sSteps] = steps;
    ScreenColourFadeData[playerid][sCurrentStep] = 0;

    ScreenColourFadeData[playerid][sRegionX] = x;
    ScreenColourFadeData[playerid][sRegionY] = y;
    ScreenColourFadeData[playerid][sRegionWidth] = width;
    ScreenColourFadeData[playerid][sRegionHeight] = height;

    ScreenColourFadeData[playerid][sTimer] = SetTimerEx("ScreenColourFadeTimerRegion", time / steps, true, "i", playerid);

    return 1;
}

forward ScreenColourFadeTimerRegion(playerid);
public ScreenColourFadeTimerRegion(playerid) 
{
    if (ScreenColourFadeData[playerid][sCurrentStep] == ScreenColourFadeData[playerid][sSteps]) 
    {
        _KillScreenColourFadeTimer(playerid);

        CallLocalFunction("OnScreenColourFadeComplete", "i", playerid);
        return 1;
    }

    TextDrawBoxColour(ScreenColourTD, InterpolateColours(ScreenColourFadeData[playerid][sOriginalColour], ScreenColourFadeData[playerid][sFinalColour], float(ScreenColourFadeData[playerid][sCurrentStep] + 1) / float(ScreenColourFadeData[playerid][sSteps])));
    TextDrawShowForPlayer(playerid, ScreenColourTD);

    ScreenColourFadeData[playerid][sCurrentStep]++;
    return 1;
}

stock SetPlayerFader(playerid, colour, fadeAmount) 
{
    if (!IsPlayerConnected(playerid) || fadeAmount < 0 || fadeAmount > 100) 
    {
        return SendClientMessage(playerid, -1, "[FADER]: You must select a value between 0 & 100"); 
    }

    new colorOpacity = (fadeAmount * 255) / 100;

    new colorWithOpacity = (colour & 0x00FFFFFF) | (colorOpacity << 24);

    _SetPlayerScreenColour(playerid, colorWithOpacity);
    
    return 1;
}


#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SCF_OnPlayerConnect

#if defined SCF_OnPlayerConnect
    forward SCF_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason) 
{
    if (ScreenColourFadeData[playerid][sTimer] != -1) 
    {
        _KillScreenColourFadeTimer(playerid);
    }

    #if defined SCF_OnPlayerDisconnect
        return SCF_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SCF_OnPlayerDisconnect

#if defined SCF_OnPlayerDisconnect
    forward SCF_OnPlayerDisconnect(playerid, reason);
#endif