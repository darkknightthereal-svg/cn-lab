# Figure 1 addressing (all /24)

| Router | Figure port | Packet Tracer port | IP |
|---|---|---|---|
| 2621A | F0/0 | Fa0/0 | 172.16.10.1 |
| 2501A | E0 | Fa0/0 | 172.16.10.2 |
| 2501A | S0 (DCE) | Se0/0/0 | 172.16.20.1 |
| 2501B | S0 | Se0/0/0 | 172.16.20.2 |
| 2501B | E0 | Fa0/0 | 172.16.30.1 |
| 2501B | S1 (DCE) | Se0/0/1 | 172.16.40.1 |
| 2501C | S0 | Se0/0/0 | 172.16.40.2 |
| 2501C | E0 | Fa0/0 | 172.16.50.1 |

If your router port names differ, edit the interface lines in the files before pasting
(check names with `show ip interface brief`).
