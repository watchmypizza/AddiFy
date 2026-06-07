# Playlists

Everything is the operationName variable inside the data variable of a request.

## `addToPlaylist`
* extensions:
    * persistedQuery:
        * sha256Hash: "47b2a1234b17748d332dd0431534f22450e9ecbb3d5ddcdacbd83368636a0990"
        * version: 1

* operationName: "addToPlaylist"

* variables:
    * newPosition:
        * fromUId: null
        * moveType: "BOTTOM_OF_PLAYLIST" or "TOP_OF_PLAYLIST"

    * playlistItemUris:
        * \[stringList\]: spotify:track:xxxxxxxxxxxxxxxxxxxxxx

    * playlistUri: spotify:playlist:xxxxxxxxxxxxxxxxxxxxxx

:::details Raw Request
```json
{
	"extensions": {
		"persistedQuery": {
			"sha256Hash": "47b2a1234b17748d332dd0431534f22450e9ecbb3d5ddcdacbd83368636a0990",
			"version": 1
		}
	},
	"operationName": "addToPlaylist",
	"variables": {
		"newPosition": {
			"fromUid": null,
			"moveType": "BOTTOM_OF_PLAYLIST"
		},
		"playlistItemUris": [
            "spotify:track:xxxxxxxxxxxxxxxxxxxxxx",
		],
		"playlistUri": "spotify:playlist:xxxxxxxxxxxxxxxxxxxxxx"
	}
}
```
:::

## `removeFromPlaylist`
* extensions:
    * persistedQuery:
        * sha256Hash: "47b2a1234b17748d332dd0431534f22450e9ecbb3d5ddcdacbd83368636a0990"
        * version: 1

* operationName: "removeFromPlaylist"

* variables:
    * playlistUri: "spotify:playlist:xxxxxxxxxxxxxxxxxxxxxx"
    * uids:
        * \[stringList\]: "songUid"

:::details Raw Request
```json
{
	"extensions": {
		"persistedQuery": {
			"sha256Hash": "47b2a1234b17748d332dd0431534f22450e9ecbb3d5ddcdacbd83368636a0990",
			"version": 1
		}
	},
	"operationName": "removeFromPlaylist",
	"variables": {
		"playlistUri": "spotify:playlist:xxxxxxxxxxxxxx",
		"uids": [
			"songUid"
		]
	}
}
```
:::

### Response


## `fetchPlaylist`
* extensions:
    * persistedQuery:
        * sha256Hash: "a65e12194ed5fc443a1cdebed5fabe33ca5b07b987185d63c72483867ad13cb4"
        * version: 1

* operationName: "fetchPlaylist"

* variables:
    * enableWatchFeedEntrypoint: `true (bool)`
    * includeEpisodeContentRatingsV2: `true (bool)`
    * limit: `25 (int)`
    * offset: `0 (int)`
    * uri: `spotify:playlist:xxxxxxxxxxxxxxxxxxxxxx`

:::details Raw Request
```json
{
	"extensions": {
		"persistedQuery": {
			"sha256Hash": "a65e12194ed5fc443a1cdebed5fabe33ca5b07b987185d63c72483867ad13cb4",
			"version": 1
		}
	},
	"operationName": "fetchPlaylist",
	"variables": {
		"enableWatchFeedEntrypoint": true,
		"includeEpisodeContentRatingsV2": true,
		"limit": 25,
		"offset": 0,
		"uri": "spotify:playlist:7JVRfnqoFdXS5YBvDVf93V"
	}
}
```
:::

### Response

::: details Documented Response
* data:
    * playlistV2:
        * __typename: `"Playlist" (string)`
        * content:
            * __typename: `"PlaylistItemsPage" (string)`
            * items:
                * \[JSON OBJECT LIST\]:
                    * addedAt:
                        * isoString: `"2026-06-06T20:50:28.195Z" (datetime)`
                    * addedBy:
                        * data:
                            * __typename: `"User" (string)`
                            * avatar:
                                * sources: 
                                    * \[JSON DICTIONARY LIST ENTRY 0\]:
                                        * height: `64 (int)`
                                        * url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
                                        * width: `64 (int)`
                                    * \[JSON DICTIONARY LIST ENTRY 1\]:
                                        * height: `300 (int)`
                                        * url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
                                        * width: `300 (int)`
                                
                            * name: `"" (string)`
                            * uri: `"spotify:user:xxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
                            * username: `"xxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
                        
                        * attributes: \[\]
						* itemsV2: 
							* __typename: `"TrackResponseWrapper" (string)`
							* data:
								* __typename: `"Track" (string)`
								* albumOfTrack: 
									* artists:
										* items:
											* \[JSON OBJECT\]:
												* profile:
													* name: `"x" (string)`
												* uri: `"spotify:track:xxxxxxxxxxxxxxxxxxxxxxxxx (string)`
									* coverArt:
										* sources:
											* \[JSON OBJECT\]:
												* height: `300 (int)`,
												* url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
												* width: `300 (int)`
											* \[JSON OBJECT\]:
												* height: `64 (int)`
												* url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)"`
												* width: `64 (int)`
											* \[JSON OBJECT\]:
												* height: `640 (int)`
												* url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
												* width: `640 (int)`
									* name: `"x" (string)`
									* uri: `"spotify:album:xxxxxxxxxxxxxxxxxxxxxx" (string)`
								* artists:
									* items:
										* \[JSON OBJECT LIST\]:
											* profile: 
												* name: `(string)`
											* uri: `"spotify:artist:xxxxxxxxxxxxxxxxxxxxxx (string)"`
								* associationsV3:
									* audioAssociations:
										* __typename: `"TrackAudioAssociationPage" (string)`
										* items: \[\]
									* videoAssociations:
										* totalCount: `0 (int)`
								* contentRating:
									* label: `NONE (string)`
								* discNumber: `1 (int)`
								* trackDuration:
									* totalMilliseconds: `(long)`
								* mediaType: `"AUDIO" (string)`
								* name: `(string)`
								* playability:
									* playable: `true (bool)`
									* reason: `"PLAYABLE" (string)`
								* playCount: `"number" (string)`
								* trackNumber: `(int)`
								* uri: `"spotify:track:xxxxxxxxxxxxxxxxxxxxxx" (string)`
						* itemV3:
							* __typename: `"EntityResponseWrapper" (string)`
							* data:
								* __typename: `"Entity (string)"`
								* consumptionExperienceTrait:
									* __typename: `"ConsumptionExperienceTrait" (string)`
									* contentRatings: \[\]
									* duration:
										* nanoSeconds: `(int)`
										* seconds: `(int)`
									* formats: `[ "FORMAT_AUDIO" (string), "FORMAT_LOSSLESS" (string) ]`
								* identityTrait:
									* __typename: `"IdentityTrait" (string)`
									* contentHierarchyParent:
										* __typename: `"Entity" (string)`
										* identityTrait:
											* __typename: `"IdentityTrait" (string)`
											* name: `(string)`
										* publishingMetadataTrait:
											* __typename: `"PublishingMetadataTrait" (string)`
											* firstPublishedAt:
												* isoString: `"" (DateTime, format: %YYYY-%MM-%DD)`
												* precision: `"DAY" (string)`
										* uri: `"spotify:album:xxxxxxxxxxxxxxxxxxxxxx" (string)`
									* contributors:
										* items:
											* \[JSON OBJECT LIST\]:
												* name: `(string)`
												* uri: `"spotify:artist:xxxxxxxxxxxxxxxxxxxxxx" (string)`
										* totalCount: `(int)`
								* description: `(string)`
								* name: `(string)`
								* type: `"Song" (string)`
							* playability:
								* playable: `true (bool)`
								* reason: `"PLAYABLE"`
							* uri: `"spotify:track:xxxxxxxxxxxxxxxxxxxxxx" (string)`
							* visualIdentityTrait:
								* __typename: `"VisualIdentityTrait" (string)`
								* sixteenByNineCoverImage: `null (presumably / unknown what other values exist)`
								* squareCoverImage:
									* extractedColorSet:
										* encoreBaseSetTextColor:
											* alpha: `(int)`
											* blue: `(int)`
											* green: `(int)`
											* red: `(int)`
										* highContrast:
											* backgroundBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* backgroundTintedBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textBrightAccent:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textSubdued:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
										* higherContrast:
											* backgroundBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* backgroundTintedBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textBrightAccent:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textSubdued:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
										* minContrast:
											* backgroundBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* backgroundTintedBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textBase:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textBrightAccent:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
											* textSubdued:
												* alpha: `(int)`
												* blue: `(int)`
												* green: `(int)`
												* red: `(int)`
									* image:
										* data:
											* __typename: `"ImageV2" (string)`
											* sources:
												* \[JSON OBJECT LIST\]:
													* imageFormat: `"WEBP" (string)`
													* maxHeight: `640 (int)`
													* maxWidth: `640 (int)`
													* uri: `"https://image-cdn-fa.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
												* \[JSON OBJECT LIST\]:
													* imageFormat: `"WEBP" (string)`
													* maxHeight: `64 (int)`
													* maxWidth: `64 (int)`
													* uri: `"https://image-cdn-fa.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
												* \[JSON OBJECT LIST\]:
													* imageFormat: `"WEBP" (string)`
													* maxHeight: `300 (int)`
													* maxWidth: `300 (int)`
													* uri: `"https://image-cdn-fa.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
						* uid: `(string)`
				* pagingInfo:
					* limit: `25 (int)`
					* offset: `0 (int)`
				* totalCount: `1 (int)`
			* abuseReportingEnabled: `true (bool)`
			* attributes: \[\]
			* basePermission: `"VIEWER"`
			* currentUserCapabilities:
				* canAbuseReport: `false (bool)`
				* canAdministratePermissions: `true (bool)`
				* canCancelMembership: `false (bool)`
				* canEditItems: `true (bool)`
				* canMixPlaylist: `true (bool)`
				* canView: `true (bool)`
			* description: `(string)`
			* followers: `(long)`
			* following: `true (bool)`
			* format: `(string)`
			* images:
				* items: \[
					* \[JSON OBJECT LIST\]:
						* sources: \[
							* \[JSON OBJECT LIST\]:
								* height: `null (unknown, presume int)`
								* url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
								* width: `null (unknown, presume int)`
						\]
				\]
			* members:
				* items: \[
					* \[JSON OBJECT LIST\]:
						* isOwner: `true (bool)`
						* permissionLevel: `"CONTRIBUTOR" (string)`
						* user:
							* data:
								* __typename: `"User" (string)`
								* avatar:
									* sources: \[
										* \[JSON OBJECT LIST\]:
											* height: `64 (int)`
											* url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
											* width: `64 (int)`
										* \[JSON OBJECT LIST\]:
											* height: `64 (int)`
											* url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
											* width: `64 (int)`
									\]
				\]
				* totalCount: `(int)`
			* name: `(string)`
			* ownerV2:
				* data:
					* __typename: `"User" (string)`
					* avatar:
						* sources: \[
							* \[JSON OBJECT LIST\]:
								* height: `64 (int)`
								* url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
								* width: `64 (int)`
							* \[JSON OBJECT LIST\]:
								* height: `64 (int)`
								* url: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
								* width: `64 (int)`
						\]
					* name: `(string)`
					* uri: `"spotify:user:xxxxxxxxxxxxxxxxxxxxxxxx" (string)`
					* username: `(string)`
			* revisionId: `(string)`
			* sharingInfo:
				* shareId: `(string)`
				* shareUrl: `https://open.spotify.com/playlist/xxxxxxxxxxxxxxxxxxxxxx (string)`
			* uri: `"spotify:playlist:xxxxxxxxxxxxxxxxxxxxxx" (string)`
			* visualIdentity:
				* squareCoverImage:
					* __typename: `"VisualIdentityImage" (string)`
					* extractedColorSet:
                        * encoreBaseSetTextColor:
							* alpha: `(int)`
							* blue: `(int)`
							* green: `(int)`
							* red: `(int)`
						* highContrast:
							* backgroundBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* backgroundTintedBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textBrightAccent:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textSubdued:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
						* higherContrast:
							* backgroundBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* backgroundTintedBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textBrightAccent:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textSubdued:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
						* minContrast:
							* backgroundBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* backgroundTintedBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textBase:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textBrightAccent:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
							* textSubdued:
								* alpha: `(int)`
								* blue: `(int)`
								* green: `(int)`
								* red: `(int)`
			* watchFeedEntryPoint:
				* entryPointUri: `"spotify:watch-feed:playlist:xxxxxxxxxxxxxxxxxxxxxx?itemId=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
				* thumbnailImage:
					* data:
						* __typename: `"ImageV2" (string)`
						* imageId: `"https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
						* imageIdType: `"IMAGE_URL" (string)`
						* sources: \[
							* \[JSON OBJECT LIST\]:
								* imageFormat: `"WEBP" (string)`
								* maxHeight: `640 (int)`
								* maxWidth: `640 (int)`
								* url: `"https://image-cdn-ak.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
							* \[JSON OBJECT LIST\]:
								* imageFormat: `"WEBP" (string)`
								* maxHeight: `64 (int)`
								* maxWidth: `64 (int)`
								* url: `"https://image-cdn-ak.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
							* \[JSON OBJECT LIST\]:
								* imageFormat: `"WEBP" (string)`
								* maxHeight: `300 (int)`
								* maxWidth: `300 (int)`
								* url: `"https://image-cdn-ak.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx" (string)`
						\]
				* video: `null (unknown, presumably string or bool)`
:::

:::details Raw Response
```json
{
	"data": {
		"playlistV2": {
			"__typename": "Playlist",
			"content": {
				"__typename": "PlaylistItemsPage",
				"items": [
					{
						"addedAt": {
							"isoString": "2026-06-06T20:50:28.195Z"
						},
						"addedBy": {
							"data": {
								"__typename": "User",
								"avatar": {
									"sources": [
										{
											"height": 64,
											"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
											"width": 64
										},
										{
											"height": 300,
											"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
											"width": 300
										}
									]
								},
								"name": "",
								"uri": "spotify:user:xxxxxxxxxxxxxxxxxxxxxxxxxx",
								"username": "xxxxxxxxxxxxxxxxxxxxxxxxxx"
							}
						},
						"attributes": [],
						"itemV2": {
							"__typename": "TrackResponseWrapper",
							"data": {
								"__typename": "Track",
								"albumOfTrack": {
									"artists": {
										"items": [
											{
												"profile": {
													"name": "x"
												},
												"uri": "spotify:artist:xxxxxxxxxxxxxxxxxxxxxx"
											},
											{
												"profile": {
													"name": "x"
												},
												"uri": "spotify:artist:xxxxxxxxxxxxxxxxxxxxxx"
											}
										]
									},
									"coverArt": {
										"sources": [
											{
												"height": 300,
												"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
												"width": 300
											},
											{
												"height": 64,
												"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
												"width": 64
											},
											{
												"height": 640,
												"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
												"width": 640
											}
										]
									},
									"name": "x",
									"uri": "spotify:album:xxxxxxxxxxxxxxxxx"
								},
								"artists": {
									"items": [
										{
											"profile": {
												"name": "x"
											},
											"uri": "spotify:artist:xxxxxxxxxxxxxxxxxxxxxx"
										},
										{
											"profile": {
												"name": "ZYZZCVNT"
											},
											"uri": "spotify:artist:xxxxxxxxxxxxxxxxxxxxxx"
										}
									]
								},
								"associationsV3": {
									"audioAssociations": {
										"__typename": "TrackAudioAssociationPage",
										"items": []
									},
									"videoAssociations": {
										"totalCount": 0
									}
								},
								"contentRating": {
									"label": "NONE"
								},
								"discNumber": 1,
								"trackDuration": {
									"totalMilliseconds": 92842
								},
								"mediaType": "AUDIO",
								"name": "x",
								"playability": {
									"playable": true,
									"reason": "PLAYABLE"
								},
								"playcount": "359892",
								"trackNumber": 1,
								"uri": "spotify:track:xxxxxxxxxxxxxxxxx"
							}
						},
						"itemV3": {
							"__typename": "EntityResponseWrapper",
							"data": {
								"__typename": "Entity",
								"consumptionExperienceTrait": {
									"__typename": "ConsumptionExperienceTrait",
									"contentRatings": [],
									"duration": {
										"nanoSeconds": 0,
										"seconds": 92
									},
									"formats": [
										"FORMAT_AUDIO",
										"FORMAT_LOSSLESS"
									]
								},
								"identityTrait": {
									"__typename": "IdentityTrait",
									"contentHierarchyParent": {
										"__typename": "Entity",
										"identityTrait": {
											"__typename": "IdentityTrait",
											"name": "x"
										},
										"publishingMetadataTrait": {
											"__typename": "PublishingMetadataTrait",
											"firstPublishedAt": {
												"isoString": "2026-01-23",
												"precision": "DAY"
											}
										},
										"uri": "spotify:album:xxxxxxxxxxxxxxxxx"
									},
									"contributors": {
										"items": [
											{
												"name": "x",
												"uri": "spotify:artist:xxxxxxxxxxxxxxxxxxxxxx"
											},
											{
												"name": "ZYZZCVNT",
												"uri": "spotify:artist:xxxxxxxxxxxxxxxxxxxxxx"
											}
										],
										"totalCount": 2
									},
									"description": "",
									"name": "x",
									"type": "Song"
								},
								"playability": {
									"playable": true,
									"reason": "PLAYABLE"
								},
								"uri": "spotify:track:xxxxxxxxxxxxxxxxxxxx",
								"visualIdentityTrait": {
									"__typename": "VisualIdentityTrait",
									"sixteenByNineCoverImage": null,
									"squareCoverImage": {
										"extractedColorSet": {
											"encoreBaseSetTextColor": {
												"alpha": 255,
												"blue": 240,
												"green": 163,
												"red": 231
											},
											"highContrast": {
												"backgroundBase": {
													"alpha": 255,
													"blue": 127,
													"green": 57,
													"red": 119
												},
												"backgroundTintedBase": {
													"alpha": 255,
													"blue": 89,
													"green": 19,
													"red": 81
												},
												"textBase": {
													"alpha": 255,
													"blue": 255,
													"green": 255,
													"red": 255
												},
												"textBrightAccent": {
													"alpha": 255,
													"blue": 255,
													"green": 255,
													"red": 255
												},
												"textSubdued": {
													"alpha": 255,
													"blue": 247,
													"green": 187,
													"red": 241
												}
											},
											"higherContrast": {
												"backgroundBase": {
													"alpha": 255,
													"blue": 92,
													"green": 22,
													"red": 84
												},
												"backgroundTintedBase": {
													"alpha": 255,
													"blue": 131,
													"green": 60,
													"red": 123
												},
												"textBase": {
													"alpha": 255,
													"blue": 255,
													"green": 255,
													"red": 255
												},
												"textBrightAccent": {
													"alpha": 255,
													"blue": 96,
													"green": 215,
													"red": 30
												},
												"textSubdued": {
													"alpha": 255,
													"blue": 247,
													"green": 187,
													"red": 241
												}
											},
											"minContrast": {
												"backgroundBase": {
													"alpha": 255,
													"blue": 160,
													"green": 88,
													"red": 152
												},
												"backgroundTintedBase": {
													"alpha": 255,
													"blue": 129,
													"green": 59,
													"red": 121
												},
												"textBase": {
													"alpha": 255,
													"blue": 255,
													"green": 255,
													"red": 255
												},
												"textBrightAccent": {
													"alpha": 255,
													"blue": 255,
													"green": 255,
													"red": 255
												},
												"textSubdued": {
													"alpha": 255,
													"blue": 255,
													"green": 255,
													"red": 255
												}
											}
										},
										"image": {
											"data": {
												"__typename": "ImageV2",
												"sources": [
													{
														"imageFormat": "WEBP",
														"maxHeight": 640,
														"maxWidth": 640,
														"url": "https://image-cdn-fa.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
													},
													{
														"imageFormat": "WEBP",
														"maxHeight": 64,
														"maxWidth": 64,
														"url": "https://image-cdn-fa.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
													},
													{
														"imageFormat": "WEBP",
														"maxHeight": 300,
														"maxWidth": 300,
														"url": "https://image-cdn-fa.spotifycdn.com/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
													}
												]
											}
										}
									}
								}
							}
						},
						"uid": "xxxxxxxxxxxxxx"
					}
				],
				"pagingInfo": {
					"limit": 25,
					"offset": 0
				},
				"totalCount": 1
			},
			"abuseReportingEnabled": true,
			"attributes": [],
			"basePermission": "VIEWER",
			"currentUserCapabilities": {
				"canAbuseReport": false,
				"canAdministratePermissions": true,
				"canCancelMembership": false,
				"canEditItems": true,
				"canMixPlaylist": true,
				"canView": true
			},
			"description": "",
			"followers": 0,
			"following": true,
			"format": "",
			"images": {
				"items": [
					{
						"sources": [
							{
								"height": null,
								"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxx",
								"width": null
							}
						]
					}
				]
			},
			"members": {
				"items": [
					{
						"isOwner": true,
						"permissionLevel": "CONTRIBUTOR",
						"user": {
							"data": {
								"__typename": "User",
								"avatar": {
									"sources": [
										{
											"height": 64,
											"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
											"width": 64
										},
										{
											"height": 300,
											"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
											"width": 300
										}
									]
								},
								"name": "x",
								"uri": "spotify:user:xxxxxxxxxxxxxxxxxxxxxxx",
								"username": "xxxxxxxxxxxxxxxxxxxxxxx"
							}
						}
					}
				],
				"totalCount": 1
			},
			"name": "x",
			"ownerV2": {
				"data": {
					"__typename": "User",
					"avatar": {
						"sources": [
							{
								"height": 64,
								"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
								"width": 64
							},
							{
								"height": 300,
								"url": "https://i.scdn.co/image/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
								"width": 300
							}
						]
					},
					"name": "x",
					"uri": "spotify:user:xxxxxxxxxxxxxxxxxxxxxxxxx",
					"username": "xxxxxxxxxxxxxxxxxxxxxxxxx"
				}
			},
			"revisionId": "xxxxxxxxxx/xxxxxxxxx/xxxx",
			"sharingInfo": {
				"shareId": "xxxxxxxxxxxxxxx",
				"shareUrl": "https://open.spotify.com/playlist/xxxxxxxxxxxxxxxxxxxxxxxx"
			},
			"uri": "spotify:playlist:x",
			"visualIdentity": {
				"squareCoverImage": {
					"__typename": "VisualIdentityImage",
					"extractedColorSet": {
						"encoreBaseSetTextColor": {
							"alpha": 255,
							"blue": 240,
							"green": 163,
							"red": 231
						},
						"highContrast": {
							"backgroundBase": {
								"alpha": 255,
								"blue": 127,
								"green": 57,
								"red": 119
							},
							"backgroundTintedBase": {
								"alpha": 255,
								"blue": 89,
								"green": 19,
								"red": 81
							},
							"textBase": {
								"alpha": 255,
								"blue": 255,
								"green": 255,
								"red": 255
							},
							"textBrightAccent": {
								"alpha": 255,
								"blue": 255,
								"green": 255,
								"red": 255
							},
							"textSubdued": {
								"alpha": 255,
								"blue": 247,
								"green": 187,
								"red": 241
							}
						},
						"higherContrast": {
							"backgroundBase": {
								"alpha": 255,
								"blue": 92,
								"green": 22,
								"red": 84
							},
							"backgroundTintedBase": {
								"alpha": 255,
								"blue": 131,
								"green": 60,
								"red": 123
							},
							"textBase": {
								"alpha": 255,
								"blue": 255,
								"green": 255,
								"red": 255
							},
							"textBrightAccent": {
								"alpha": 255,
								"blue": 96,
								"green": 215,
								"red": 30
							},
							"textSubdued": {
								"alpha": 255,
								"blue": 247,
								"green": 187,
								"red": 241
							}
						},
						"minContrast": {
							"backgroundBase": {
								"alpha": 255,
								"blue": 160,
								"green": 88,
								"red": 152
							},
							"backgroundTintedBase": {
								"alpha": 255,
								"blue": 129,
								"green": 59,
								"red": 121
							},
							"textBase": {
								"alpha": 255,
								"blue": 255,
								"green": 255,
								"red": 255
							},
							"textBrightAccent": {
								"alpha": 255,
								"blue": 255,
								"green": 255,
								"red": 255
							},
							"textSubdued": {
								"alpha": 255,
								"blue": 255,
								"green": 255,
								"red": 255
							}
						}
					}
				}
			},
			"watchFeedEntrypoint": {
				"entrypointUri": "spotify:watch-feed:playlist:x",
				"thumbnailImage": {
					"data": {
						"__typename": "ImageV2",
						"imageId": "https://i.scdn.co/image/x",
						"imageIdType": "IMAGE_URL",
						"sources": [
							{
								"imageFormat": "WEBP",
								"maxHeight": 640,
								"maxWidth": 640,
								"url": "https://image-cdn-ak.spotifycdn.com/image/x"
							},
							{
								"imageFormat": "WEBP",
								"maxHeight": 64,
								"maxWidth": 64,
								"url": "https://image-cdn-ak.spotifycdn.com/image/x"
							},
							{
								"imageFormat": "WEBP",
								"maxHeight": 300,
								"maxWidth": 300,
								"url": "https://image-cdn-ak.spotifycdn.com/image/x"
							}
						]
					}
				},
				"video": null
			}
		}
	}
}
```
:::