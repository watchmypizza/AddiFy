# Authorization & Headers

To send a request to Spotify's GraphQL backend, we do not need any authentication. But to actually get a meaningful response back, we do need proper authentication.

::: warning ToS Information
Spotify does **not** allow this, and this is the exact reason why it is against the **ToS**.

Spotify has their own devoted page to this to create authorized bots. See [Spotify Developer Home](https://developer.spotify.com/)
:::

But as you are on this page, I don't think you want to create an authorized bot.

## Authorization Token

Spotify uses tokens for authorization flow. There are 2 types of different tokens that Spotify utilizes. We first of all have the `authorization` token. The authorization token exists to verify that you behind the screen accessing the current account is you. It also tells the website "This is an user, their request is probably legit." allowing for lesser strict limits enforced by spotify.

In short:

* The authorization token implies that you are authenticating as x user legitimately (or so Spotify thinks) 

## Client Token

The client token is a bit more complicated than the [Authorization Token](#authorization-token).

Listing some details about the client token below ↓

:::details Client Token Information
* API requests get anonymized by the client token.
* The client token prevents fraud. It also manages rate limits opposed onto your account
* It's passed during the initial stages of connecting third party apps (OAuth)
* Allows for grouping of telemetry and analytics data as well as crash reports originating from the same device session.
:::

## Headers

Here you will learn how to combine the authorization token and the client token to fit into a single request.

Starting off with a basic python code example once again:
```python
import requests

local url = "https://api-partner.spotify.com/pathfinder/v2/query"
local headers = {
    "content-type": "application/json"
}

requests.post(url, data = {}, headers=headers)
```
Because we are not authenticated as an user, our request will return an 401 "Unauthorized" response. In order to make a proper request as an user we will have to pass the `authorization-token` and the `client-token` into the headers alongside the `content-type`. The `content-type` header is very important as well, because without, the server doesn't know what to respond with.

```python
# example header structure
headers = {
    "content-type": "application/json",
    "authorization-token": "xxxxxxxxxxxxxxxxx",
    "client-token": "xxxxxxxxxxxxxxxx",
}
```

This would give us a valid response back from the server with actual response data.

## Grabbing your tokens

Before you can start firing requests, you need to extract your personal tokens from your browser session. To do this, you will need to use your browser's built-in **Developer Tools (DevTools)**—specifically the **Network** tab.

::: tip Developer Tools
If you've never used DevTools before, get familiar with the [Firefox DevTools Documentation](https://firefox-source-docs.mozilla.org/devtools-user/) or the Chrome equivalents first. It'll be of advantage later on if you want to contribute.
:::

### Step-by-Step Guide

1. Open your browser, head over to [Spotify Web Player](https://open.spotify.com/), and log into your account.

2. Press `F12` (or `Ctrl+Shift+I` / `Cmd+Option+I` on Mac) to open the DevTools, and switch to the **Network** tab.

![Network Tab](images/networkingtab.png)

3. At first, you will see a massive stream of random network garbage. To fix this, locate the **Filter** input field and paste the Spotify GraphQL endpoint URL:

https://api-partner.spotify.com/pathfinder/v2/query

4. Now, the list will only show legitimate GraphQL POST requests. Click on any of the captured requests and look at the **Headers** section on the right.

5. Scroll down to the **Request Headers** until you find these two specific keys:

* `authorization:` (Copy the entire value, including the `Bearer ` prefix if present)
* `client-token:`

Simply copy both values and paste them into your Python header dictionary.

::: danger TOKEN EXPIRATION
Both the `authorization` token and the `client-token` **expire after exactly 1 hour**. If your script suddenly starts throwing `401 Unauthorized` errors out of nowhere, you will have to refresh the Spotify tab and grab a new pair of tokens.
:::