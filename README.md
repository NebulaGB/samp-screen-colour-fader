
# SA-MP Screen Colour Fader

This library is a fork of the original project by [Kristo Isberg](https://github.com/NebulaGB/samp-screen-colour-fader).

[![sampctl](https://img.shields.io/badge/sampctl-samp--screen--colour--fader-2f2f2f.svg?style=for-the-badge)](https://github.com/NebulaGB/samp-screen-colour-fader)



This library lets you add color filters to players' screens and fade between them. It was originally based on a modified version of Joe Staff's fader include, but as the previous implementation used a separate argument for each part of an RGBA color and had become outdated

The original fader was functional, but it was not as flexible or easy to use as I needed. As I was working on projects that required smoother, more customizable transitions between colors for player screens, I found myself in need of a more reliable and user-friendly fader library. Recognizing the limitations of the old solution, I decided to take over the project and overhaul the code to make it easier for developers to use while providing more robust functionality.

My goal was to design a fader library that offered seamless transitions between screen colors, allowing for both full-screen color fades and region-specific fades. I also aimed for simplicity in its use so that developers could focus on their core features rather than worry about complex color management.

This library works with open.mp

## Installation

Simply install to your project:

```bash
sampctl package install NebulaGB/samp-screen-colour-fader
```

Include in your code and begin using the library:

```pawn
#include <screen-colour-fader>
```

## Functions

```pawn
native SetPlayerScreenColour(playerid, colour);
```
Will set the player's screen colour to the specified colour. Can be used during a fade, but the fade will continue after the current step is finished. Returns `1` if the specified player is connected or `0` if not.


```pawn
native GetPlayerScreenColour(playerid);
```
Can be used during a fade. Returns the current colour of the player's screen if the player is connected or `0x00000000` if not.

```pawn
native FadePlayerScreenColour(playerid, colour, time, steps);
```
Fades the player's screen from the current colour to the colour specified in the function. `time` specifies the duration of the fade and `steps` specifies the amount of steps made during the fade. Returns `1` if the specified player is connected and the values of `time` and `steps` are valid or `0` if not.

```pawn
native StopPlayerScreenColourFade(playerid);
```
Stops the ongoing fade. The colour of the player's screen will remain as it is at the time of the function call. Returns `1` if the specified player is connected and has an ongoing fade or `0` if not.

### `FadeAllPlayersScreenColour(colour, time, steps)`

This function fades the screen colour for all connected players simultaneously.

#### Usage:

```pawn
FadeAllPlayersScreenColour(0xFF0000FF, 2000, 10); // Fades all players' screens to red in 2 seconds with 10 steps
```

### `FadePlayerScreenColourRegion(playerid, colour, time, steps, x, y, width, height)`

This function applies the fade effect to a specific region of the player's screen, given the `x`, `y`, `width`, and `height` of the region.

#### Usage:

```pawn
FadePlayerScreenColourRegion(playerid, 0x00FF00FF, 1500, 10, 100.0, 100.0, 300.0, 200.0); // Fades a specific region to green
```

### `SetPlayerFader(playerid, colour, fadeAmount) `

```pawn
SetPlayerFader(playerid, 0x00FF00FF, 100); // 0x00FF00FF is green with 100% opacity
SetPlayerFader(playerid, 0x00FF00FF, 50);  // 0x00FF00FF is green with 50% opacity
SetPlayerFader(playerid, 0x00FF00FF, 0); // 0x00FF00FF is green with 0% opacity
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

## Testing

To test, simply run the package:

```bash
sampctl package run
```

And connect to `localhost:7777` to test.
