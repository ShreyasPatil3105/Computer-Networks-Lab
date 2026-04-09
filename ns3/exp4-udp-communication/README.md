# Experiment 4: NS3 - TCP/UDP Communication (Single Client Chatting)

## Objective
To implement client-server communication using UDP protocol in NS3 where a client sends multiple packets to a server and the server receives and logs them.

## Simulation Details
| Parameter | Value |
|-----------|-------|
| Number of Nodes | 2 (Client + Server) |
| Link Type | Point-to-Point |
| Data Rate | 5 Mbps |
| Delay | 2 ms |
| Protocol | UDP |
| Port | 8080 |
| Packet Size | 1024 bytes |
| Number of Packets | 10 |
| Packet Interval | 1 second |

## Files in this Folder
- `udp-client-server.cc` - C++ source code
- `ss1_udp_client_server_output.png` - Terminal output screenshot
- Word document - Exp4_NS3_UDP_Communication_ShreyasPatil.docx

## Output Summary
- 10 packets of 1024 bytes each sent from client to server
- Each packet received with approximately 3.69 ms delay
- Zero packet loss
- Simulation completed successfully

## Author
SHREYAS PATIL
