# MusicDownloader
This is where she makes a mod.

<img src="logo.png" width="150" alt="the mod's logo" />

A Geometry Dash Geode mod that automatically downloads the required songs and audio assets when you download a level.

The goal is simple: users should not have to manually open the audio assets menu and click download before playing a level.

## Features

- Automatically starts audio asset downloads after downloading a level.
- Supports the main custom song.
- Supports Geometry Dash 2.2 multi-song assets.
- Supports SFX assets.
- Uses Geometry Dash's native `CustomSongWidget` download flow.
- Keeps the native song info box/progress behavior instead of implementing a separate downloader.

## How it works

When a level finishes downloading, the mod hooks into `LevelInfoLayer::levelDownloadFinished`.

It then finds the visible `CustomSongWidget` in the level info screen, injects the level's song and SFX asset lists, refreshes the widget, and triggers the native download action.

This means the mod does not manually reimplement the full audio downloader. It reuses Geometry Dash's existing multi-asset download behavior.

## Installation

### From Geode

Once published, install the mod from the Geode Mod Hub.

### Manual installation

1. Download the `.geode` file from the latest release.
2. Place it in your Geode mods folder:

```txt
%localappdata%\GeometryDash\geode\mods
```

3. Launch Geometry Dash.

## Building from source

### Requirements

* Geometry Dash with Geode installed
* Geode CLI
* CMake
* A supported C++ compiler

### Build

```bash
geode build
```

The generated `.geode` file will be available in the build output directory.

## Repository structure

```txt
.
├── src/
│   └── main.cpp
├── about.md
├── changelog.md
├── support.md
├── mod.json
├── CMakeLists.txt
└── README.md
```

## Configuration

This mod currently has no user-facing settings.

It runs automatically when a level is downloaded.

## Support

If this mod helped you, you can support development here:

[buymeacoffee.com/champagnearden](https://buymeacoffee.com/champagnearden)

## Known notes

Very large levels may require many audio assets. The mod triggers the native Geometry Dash download flow, so download speed and behavior still depend on Geometry Dash's servers, the user's connection, and the normal in-game downloader.

## License

This project is licensed under the MIT License.

See the [LICENSE](LICENSE.txt) file for details.

## Build instructions
For more info, see [our docs](https://docs.geode-sdk.org/getting-started/create-mod#build)
```sh
# Assuming you have the Geode CLI set up already
geode build
```

# Resources
* [Geode SDK Documentation](https://docs.geode-sdk.org/)
* [Geode SDK Source Code](https://github.com/geode-sdk/geode/)
* [Geode CLI](https://github.com/geode-sdk/cli)
* [Bindings](https://github.com/geode-sdk/bindings/)
* [Dev Tools](https://github.com/geode-sdk/DevTools)
