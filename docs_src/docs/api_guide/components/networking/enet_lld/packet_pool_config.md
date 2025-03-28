Ethernet Packet Pool Allocation Guidelines {#PACKETPOOL_CONFIG_TOP}
======================

[TOC]

Enet Driver creates memory for Ethernet packets based on configuration from "Packet Pool Config". To use various packet pools like Large, Medium and Small, the SysConfig GUI tool configuration has to be manually configured. The application can only allocate the Ethernet Packet memory available from SysConfig GUI configuration. If application tries to allocate packet pool which is not configured from SysConfig GUI tool, then assertion check in application will fail due to non-availability of Ethernet packet memory.

By default, networking out-of-box examples enable "Packet pool allocation" from SysConfig GUI tool and "EnetMem_allocEthPkt()" from application to allocate memory for Ethern
et packets. Users are free to disable "Packet Po0l Allocation" from GUI and write their own "EnetMem_allocEthPkt()" to allocate memory.
\imageStyle{disable_packetpool.png,width:35%}
 \image html disable_packetpool.png  Syscfg GUI with "Packet pool allocation" disabled 
 
In the below configuration(Figure1), only Medium Pool count is non-zero(32), Large and Small pool count is configured to be zero. So the Application can only allocate Medium packet pool for Tx,Rx DMA Ethernet packet queues. When application tries to allocate Large packet size Queues, then assertion check in application will fail.
 \imageStyle{syscfg_packetpool_mediumpool.png,width:35%}
 \image html syscfg_packetpool_mediumpool.png  **Figure1**: Packet pool configuration with only Medium Pool Configured
 

Non-Lwip Examples use "EnetMem_allocEthPkt()" API to allocate Ethernet packet queue for Tx,Rx DMA in the application. Total Scatter segment size(scatterSegments[]) which is given as argument to "EnetMem_allocEthPkt()" should be less than or equal to the Packet pool type configured from the SysConfig GUI tool. With the above packet pool configuration(Figure1), ethernet packet size less than or equal to 512 Bytes(Medium packet pool size) can be allocated and ethernet packet size more than 512 Bytes cannot be allocated in application. User has to manually change the scattersegments[](ENET_MEM_MEDIUM_POOL_PKT_SIZE in Figure2) and Ethernet packet queue count(ENET_SYSCFG_TOTAL_NUM_RX_PKT in Figure2) based on the usecase.
Ethernet packet which has to be allocated in the application should be in the range of packet pool configured from SysConfig GUI tool. 

 \imageStyle{packet_pool_allocEthPkt.png,width:30%}
 \image html packet_pool_allocEthPkt.png  **Figure2**: EnetMem_allocEthPkt() API usage in Application to allocate Ethernet packet memory
 \note Make sure to update the arguments of "EnetMem_allocEthPkt()" API in application when the packet pool configuration is updated from SysConfig GUI tool


Lwip Examples by default uses Large Pkt pool for Rx DMA Packet Queues. Users cannot set the 'Large Packet Pool Count' to 'Zero' in the default packet pool configuration. 
\cond SOC_AM263X || SOC_AM263PX || SOC_AM261X
If user wants to change the "Large pool count" to "0", then the "Rx Packet Buffer Size" size has to be updated with subsequent pool size whose count is Non-zero. 

In the following configuration(Figure3), "Large Packet Pool Count" configured to "Zero" and "Medium Packet Pool Count" to "32". To use this configuration, the "Rx Packet Buffer Size" is updated to "512" Bytes from the default value of "1536"Bytes

 \imageStyle{updated_lwip_packet_pool.png,width:30%}
 \image html updated_lwip_packet_pool.png  **Figure3**: Sample Packet pool configuration to change the default configuration for LWIP Examples
 \endcond
 
To transmit Ethernet packet, LWIP applciation uses memory pool configuration from "enet/lwippools.h" to allocate buffer memory. User can update following configuration from "enet/lwippools.h" based on the usecase. 
 \imageStyle{lwippool.png,width:20%}
 \image html lwippool.png  **Figure4**: Lwip pool memory configuration(lwipools.h) used for Tx LWIP Packets from EVM