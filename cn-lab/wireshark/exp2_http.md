# Exp 2 - HTTP (filter: http)
1. Clear browser cache. Start Wireshark. Visit http://neverssl.com (plain HTTP).
2. Filter `http`, stop capture. Select first GET, expand "Hypertext Transfer Protocol".

| Question | Where | Value |
|---|---|---|
| (a) src/dst IP of first GET | Source / Destination columns | |
| (b) accepted formats | Accept, Accept-Language, Accept-Encoding, Accept-Charset | |
| (c) URL, user agent | Host + GET path, User-Agent | |
| (d) src/dst IP of first response | first 200 OK packet | |
| (e) status code | response line | |
| (f) last modified | Last-Modified header | |
| (g) content-length | Content-Length header | |
| (h) time taken | response Time - GET Time, or [Time since request] | |
| (i) HTTP version | GET line (HTTP/1.1) | |
