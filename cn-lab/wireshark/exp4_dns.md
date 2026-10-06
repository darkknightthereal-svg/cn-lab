# Exp 4 - DNS (filter: dns)
1. `resolvectl flush-caches` (or `systemd-resolve --flush-caches`), clear browser cache.
2. Start Wireshark on the real interface (not lo). Visit the college website.
3. Filter `dns`, stop. Use the first query and its matching response (same Transaction ID).
If no DNS packets show: `nslookup college-site` in a terminal while capturing.

| Question | Answer / where |
|---|---|
| (a) query packet no. | No. column |
| (b) UDP or TCP | UDP |
| (c) response packet no. / transport | No. column / UDP |
| (d) query ports | src = ephemeral, dst = 53 |
| (e) response ports | src = 53, dst = query's src port |
| (f) query sent to | destination IP of query (DNS resolver) |
| (g) IDs, purpose | Transaction ID, same in both; matches response to query |
| (h) flags length | 16 bits |
| (i) query/response bit | QR bit, 0 = query, 1 = response |
| (j) response-only bits | AA, RA, RCODE (TC if truncated) |
| (k) record counts in query | read Questions / Answer / Authority / Additional RRs |
| (l) record counts in response | same four fields on the response |
