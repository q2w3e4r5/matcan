
#define MAT_NODE_ID				0x5		//(1 to 127), default node ID
#define MAT_CAN_BAUDRATE		3			//(0 to 7), default CAN bit rate
                                 			// 0 = 10 kbps    1 = 20 kbps
		                    	            // 2 = 50 kbps    3 = 125 kbps
        		        	                // 4 = 250 kbps   5 = 500 kbps
                		        	        // 6 = 800 kbps   7 = 1000 kbps

//#if MAT_NODE_ID == 0x02						// Sabemos que el nodo 2 es de 20
//	#define MAT_OSC_FREQ			20
//#else
	#define MAT_OSC_FREQ			40
//#endif           		        	        
