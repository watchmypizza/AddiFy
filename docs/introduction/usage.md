## GraphQL Requests
Most GraphQL requests are [POST](https://curl.se/docs/tutorial.html#:~:text=POST%20%28HTTP) and **not** [GET](https://curl.se/docs/tutorial.html) requests.

Using POST we can send data and get data in return, so we don't have to ping an infinite amount of API endpoints with get requests just to get what we want. Using this we have 1 static URL, the only thing that changes is the request body.

## Fundamental Requirements
We can use this to our advantage, as we only have to declare one function to send requests:

```python
import requests as rq

def sendPostRequest(url, payload):
    response = rq.post(url, payload)
    return response
```
This function called `sendPostRequest(url, payload)` takes 2 arguments as context.

* `URL`: The URL to send a post request to, in this documentation we will declare `URL` as the Spotify GraphQL backend URL. 
```python
url = "https://api-partner.spotify.com/pathfinder/v2/query"
```

* `payload`: This is the data being passed in the POST request. This is often a [JSON](https://www.json.org/json-en.html) object
```python
payload = {
    "operationName": "addToPlaylist"
}
```

## Sending a basic request

By having this [basic structure](#fundamental-requirements) we can now send a POST request with no body to spotify's backend GraphQL URL.

```python
response = sendPostRequest(url, payload = {})
```

The response body when the URL did not return any error code can be viewed with this:

```python
response.content
```

Though with an empty payload, the response body will return nothing, an empty response body.

## Utilization

Utilizing the `sendPostRequest(url, payload)` function, we can grab all kind of data from Spotify. Though without a proper token, spotify is likely to reject your request.