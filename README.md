
# SA-MP Screen Colour Fader

This library is a fork of the original project by [Kristo Isberg](https://github.com/NebulaGB/samp-screen-colour-fader).

This library lets you add color filters to players' screens and fade between them. It was originally based on a modified version of Joe Staff's fader include, but as the previous implementation used a separate argument for each part of an RGBA color and had become outdated

The original fader was functional, but it was not as flexible or easy to use as I needed. As I was working on projects that required smoother, more customizable transitions between colors for player screens, I found myself in need of a more reliable and user-friendly fader library. Recognizing the limitations of the old solution, I decided to take over the project and overhaul the code to make it easier for developers to use while providing more robust functionality.

This library works with open.mp

[Pawn Colour Manipulation](https://github.com/NebulaGB/pawn-colour-manipulation) is required for this library.
## Installation

Include in your code and begin using the library:

```pawn
#include <screen-colour-fader>
```

## Functions

```pawn
SetPlayerScreenColour(playerid, colour);
GetPlayerScreenColour(playerid);
FadePlayerScreenColour(playerid, colour, time, steps);
StopPlayerScreenColourFade(playerid);
FadeAllPlayersScreenColour(colour, time, steps);
FadePlayerScreenColourRegion(playerid, colour, time, steps, x, y, width, height);
SetPlayerFader(playerid, colour, fadeAmount);
```

## Callbacks

```pawn
forward public OnScreenColourFadeComplete(playerid);
```

## Notes

* Both for the functions and the callback, the American spelling (color instead of colour) is also supported.


## Example

The following piece of code (also available in test.pwn) fades the player's screen to red and back to transparent five times.

```pawn
new bool:reverse, counter;

public OnPlayerConnect(playerid) {
	SetPlayerScreenColour(playerid, 0x00000000);
	FadePlayerScreenColour(playerid, 0xFF0000AA, 1000, 25);
	return 1;
}


public OnScreenColourFadeComplete(playerid) {
	if (++counter == 10) {
		return 1;
	}

	FadePlayerScreenColour(playerid, reverse ? 0xFF0000AA : 0x00000000, 1000, 50);

	reverse = !reverse;

	return 1;
}
```