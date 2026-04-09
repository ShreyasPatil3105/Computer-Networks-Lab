/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

// Function to receive packets on server side
void ReceivePacket(Ptr<Socket> socket)
{
    Ptr<Packet> packet;
    Address from;
    
    while ((packet = socket->RecvFrom(from)))
    {
        std::cout << "Server received " << packet->GetSize() 
                  << " bytes from client at time: " 
                  << Simulator::Now().GetSeconds() << " seconds\n";
    }
}

// Function to send packets from client side
void SendPacket(Ptr<Socket> socket, uint32_t pktSize, uint32_t pktCount, Time pktInterval)
{
    if (pktCount > 0)
    {
        socket->Send(Create<Packet>(pktSize));
        std::cout << "Client sent " << pktSize 
                  << " bytes packet. Packets remaining: " << pktCount - 1 << "\n";
        
        Simulator::Schedule(pktInterval, &SendPacket, socket, pktSize, pktCount - 1, pktInterval);
    }
    else
    {
        socket->Close();
        std::cout << "Client finished sending all packets.\n";
    }
}

int main(int argc, char *argv[])
{
    std::cout << "\n========================================\n";
    std::cout << "NS3 - UDP CLIENT SERVER COMMUNICATION\n";
    std::cout << "========================================\n\n";
    
    Time::SetResolution(Time::NS);
    
    // Step 1: Create 2 nodes (Client and Server)
    NodeContainer nodes;
    nodes.Create(2);
    
    std::cout << "Step 1: Created 2 nodes (Node 0: Client, Node 1: Server)\n";
    
    // Step 2: Create point-to-point link between nodes
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    
    NetDeviceContainer devices = p2p.Install(nodes);
    std::cout << "Step 2: Created point-to-point link (5Mbps, 2ms delay)\n";
    
    // Step 3: Install Internet stack on both nodes
    InternetStackHelper internet;
    internet.Install(nodes);
    std::cout << "Step 3: Installed Internet stack on both nodes\n";
    
    // Step 4: Assign IP addresses
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);
    std::cout << "Step 4: Assigned IP addresses - Client: " 
              << interfaces.GetAddress(0) << ", Server: " 
              << interfaces.GetAddress(1) << "\n";
    
    uint16_t port = 8080;
    std::cout << "Step 5: Using port number: " << port << "\n\n";
    
    // Step 6: Create SERVER socket (UDP)
    Ptr<Socket> serverSocket = Socket::CreateSocket(nodes.Get(1), UdpSocketFactory::GetTypeId());
    InetSocketAddress local = InetSocketAddress(Ipv4Address::GetAny(), port);
    serverSocket->Bind(local);
    serverSocket->SetRecvCallback(MakeCallback(&ReceivePacket));
    std::cout << "Server socket created and listening on port " << port << "\n";
    
    // Step 7: Create CLIENT socket (UDP)
    Ptr<Socket> clientSocket = Socket::CreateSocket(nodes.Get(0), UdpSocketFactory::GetTypeId());
    InetSocketAddress remote = InetSocketAddress(interfaces.GetAddress(1), port);
    clientSocket->Connect(remote);
    std::cout << "Client socket created and connected to server at " 
              << interfaces.GetAddress(1) << ":" << port << "\n\n";
    
    std::cout << "========================================\n";
    std::cout << "Starting Communication...\n";
    std::cout << "========================================\n\n";
    
    // Step 8: Schedule packet transmission
    // Send 10 packets of 1024 bytes each, 1 second apart
    Simulator::Schedule(Seconds(2.0), &SendPacket, clientSocket, 1024, 10, Seconds(1.0));
    
    // Step 9: Stop simulation after 15 seconds
    Simulator::Stop(Seconds(15.0));
    
    // Step 10: Run simulation
    Simulator::Run();
    Simulator::Destroy();
    
    std::cout << "\n========================================\n";
    std::cout << "Simulation Completed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}

