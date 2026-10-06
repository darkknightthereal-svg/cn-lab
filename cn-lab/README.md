# CN Lab - practical code

Programs: Exp 6 (UDP translator), Exp 8 (UDP time server), Exp 9 (TCP file server).
Router configs: Exp 11-14 (Figure 1). Wireshark answer sheets: Exp 2, 4.

## Get it
    git clone <your-repo-url>
    cd cn-lab
    make            # builds all six C programs (needs gcc)

## Exp 6 - UDP translator (port 8080)
    ./exp6_udp_translator/server            # terminal 1
    ./exp6_udp_translator/client            # terminal 2 (or: client <server-ip>)

## Exp 8 - concurrent UDP time server (port 9090)
    ./exp8_udp_time_server/server
    ./exp8_udp_time_server/client           # run several times; PIDs differ

## Exp 9 - concurrent TCP file server (port 7070)
    cd exp9_tcp_file_server
    ./server                                # run from the folder holding the files
    ./client                                # enter test.txt, then a missing file name

## Cisco (Packet Tracer)
Build Figure 1, then open each router's CLI and paste its file:
    cisco/1_base/<router>.txt      interfaces + clock rate   (do this first)
    cisco/2_static/<router>.txt    Exp 12
    cisco/3_rip/<router>.txt       Exp 13   (start from base, no static routes)
    cisco/4_ospf/<router>.txt      Exp 14   (start from base, no static/RIP)
Check with cisco/verify.txt. Port names: cisco/addresses.md.
