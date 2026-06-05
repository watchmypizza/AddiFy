# AddiFy

A high-performance C++ utility designed to rapidly clone and inject an entire artist's discography into your designated Spotify playlist.

---

## ⚠️ Terms of Service Notice & Disclaimer

This tool interacts with internal/undocumented endpoints and technically violates the Spotify Terms of Service (ToS). 

* **Risk:** While ban history for consumer-level tools like this is historically virtually non-existent, executing unauthorized API calls always carries an inherent risk.
* **Liability:** If your account is flagged, restricted, or banned due to aggressive endpoint spamming or malicious abuse of this utility, **I take absolutely no responsibility.** Use this software at your own risk.

---

## 🪟 Windows Users

> [!Important]
> **Running AddiFy on WINDOWS??!**
>
> First of all, no I do not support this behaviour. Second of all, embrace the penguin and download Windows Subsystem for Linux (WSL). A tutorial can be found [here](https://www.youtube.com/watch?v=QM3mzEJCzjY&vl=en). After installing WSL, follow the linux installation guide.

### Commands you will need:
```sh
touch
mkdir
git
cd
mv # Optional if you want to rename example-config.yaml to config.yaml
nano
./AddiFy # duh
```

## 🎯 Benchmark

This tool was benchmarked against Buckethead's massive discography. With the `render-ahead-limit` config option set to **437**, the script successfully fetched all albums, singles, and tracks in approximately **6 - 7 minutes**.

<!-- You know what else is massive? LOOOW TAPER FADEEEE -->

**Test Environment:**
* **CPU:** AMD Ryzen 5 5500U (Laptop)
* **Target:** 437 Releases (Buckethead)
* **Status:** 100% Success, 0 Crashes

## 🛠️ Building the Project

### Prerequisites
Ensure you have a C++20 compliant compiler, `libcurl`, and `yaml-cpp` installed on your system.

### Option 1: Automatic Build (Recommended)
A `Makefile` is included for convenience. Run the following commands:
```sh
git clone [https://github.com/watchmypizza/AddiFy.git](https://github.com/watchmypizza/AddiFy.git)
cd AddiFy
cmake --build build
```

### Option 2: Manual Compilation

If you prefer to compile manually without make, use g++:

```sh
git clone [https://github.com/watchmypizza/AddiFy.git](https://github.com/watchmypizza/AddiFy.git)
cd AddiFy
g++ Classes/*.cpp -o AddiFy -lcurl -lyaml-cpp -I/usr/include -std=c++20
```

## ⚙️ Configuration Guide

Before running the application, you must configure the `config.yaml` file located in the same directory as the executable.

### The config.yaml Template

```yaml
authorization-bearer: ""
client-token: ""

artists:
    - exampleName

render-ahead-limit: 20

playlist-to-add-to: exampleId
```

### Step 1: Extract Credentials (authorization-bearer & client-token)

1. To authentic your requests, you need to extract temporary tokens from a live browser session.

2. Navigate to the [Spotify Web Player](https://open.spotify.com/) and log in.

3. Open your browser's Developer Tools by pressing `Ctrl + Shift + I` or `F12`.

4. Locate the Network tab. If it isn't visible, click the More Tabs arrow icon:

5. Select Network from the dropdown menu:

6. If the network log is empty, refresh the page `(F5)` to populate the requests.

7. To isolate the correct traffic, type `api-partner.spotify.com` into the Filter URL text input.

8. Click on any filtered API request and ensure you are viewing the Headers sub-tab.

9. Scroll down to the Request Headers section until you locate the authorization blocks.

10. Copy the values:

`authorization-bearer:` Copy the string inside the authorization: header WITHOUT the leading word Bearer .

`client-token:` Copy the entire token string from the client-token: header.

### Images

![Image](Images/spotifydevconsole.png)

![Image](Images/arrow.png)

![Image](Images/dropdown.png)

![Image](Images/emptynetworktab.png)

![Image](Images/filterurl.png)

![Image](Images/apirequests.png)

![Image](Images/headers.png)

![Image](Images/thingstocopy.png)

### Step 2: Get the Target Artist ID

You need the unique identifier for the artist whose discography you want to fetch.

### Method A: Using Share Links

1. Right-click the artist in Spotify, go to Share, and click Copy link to artist.

2. Your link will look like this: `https://open.spotify.com/artist/42bRZvZrglzmj99X9alo1a?si=xxxxxxxxxx`

3. Strip away the tracking parameters (`?si=...`) and the URL base (`http://googleusercontent.com/spotify.com/artist/`).

4. You will be left with a clean alphanumeric ID, for example: `42bRZvZrglzmj99X9alo1a`

### Method B: Using Spotify URIs

1. If your client copies the raw URI, it will look like this: `spotify:artist:42bRZvZrglzmj99X9alo1a`

2. Simply strip away the `spotify:artist:` prefix to isolate the ID: `42bRZvZrglzmj99X9alo1a`

Paste this value into a new entry in the `artists:` field in your `config.yaml`.

### Step 3: Get the Target Playlist ID

Follow the exact same workflow from Step 2 on your target playlist.

* From Link: `http://open.spotify.com/playlist/0JOAYyVJHTg45SeORIAOhL?si=xxx` → Extract `0JOAYyVJHTg45SeORIAOhL`

* From URI: `spotify:playlist:0JOAYyVJHTg45SeORIAOhL` → Extract `0JOAYyVJHTg45SeORIAOhL`

Paste this value into the `playlist-to-add-to:` field in your `config.yaml`.

### Step 4: Final Validation & Execution

Your finalized `config.yaml` should match this structure:

```yaml
authorization-bearer: YOUR_RAW_AUTHORIZATION_STRING_WITHOUT_BEARER
client-token: YOUR_EXTRACTED_CLIENT_TOKEN_STRING

artists:
    - usedcvnt

playlist-to-add-to: 0JOAYyVJHTg45SeORIAOhL
```

> [!IMPORTANT]
> **Dealing with Large Discographies?**
> By default, the client handles layouts in chunks of 20. If you are adding an artist with more than 20 releases (albums, EPs, or singles), you **must** increase the `render-ahead-limit` in your `config.yaml` to match or exceed their total release count!
>
> **Program crashing with `Error parsing YAML file: bad file: config.yaml`?**
> Ensure `config.yaml` is saved directly in the same directory as the compiled `AddiFy` binary.

Run the binary from your terminal to begin the sync process:

```sh
./AddiFy
```

## 📜 License

Copyright (c) 2026 @watchmypizza. All rights reserved.

Licensed under a modified version of the [MIT license](https://github.com/watchmypizza/AddiFy/blob/main/LICENSE.md).


<!-- Oh yeah did you know that I like cats? Also I have a pet cat named "Michi". You know how I came up with this project? I was talking to gemini and was bored and just asked it what I can program. It told me something about reverse engineering. Too lazy to look it up right now, but yea I noticed spotify lacks an "add artist's discography" button I decided to make this program. This program basically does what this button should do if it would exist, just better with multiple artists at once. I don't knwo what more I can add after this commit, but I will always periodically find things while watching re:zero or when i notice something that I wanna add so badly. I don't really care about GUI so I'll probaby never add GUI but maybe I'll add an console interface that lets you interact with the program instead of the program just doing whatever its supposed to do at the moment. Like I thought about adding maybe some cool thing I forgot what it's called. Eh who cares, but basically I want to add a navigation menu on where you can type a number. Example:
[1] Something option
[2] Something second option like configure config.yaml
[3] Something like refresh cached config.yaml

Option [1, 2, 3]: USERINPUT
You know I thought about something like this. Maybe I will add this someday, but right now I am not particularly interested in this sort of stuff. I mainly just want to get it working. Also if I ever do add an actual GUI (over QT primarly) I will make sure it keeps its CLI commands functional. Since some BINDOWS users use DISGUSTING microslop I will keep CLI functionality present. Yeah so thats basically it for my little rant here and uh if you find this congratulations, I crown you a nerd! -->