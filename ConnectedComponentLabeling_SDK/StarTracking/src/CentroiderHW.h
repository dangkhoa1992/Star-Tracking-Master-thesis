#ifndef CCLABEL_H_
#define CCLABEL_H_

XCclabel cCLabel;
XCclabel_Config *cCLabel_cfg;
XAxiDma axiDMA;
XAxiDma_Config *axiDMA_cfg;

//BRAM addresses
int *XHW = (int *)0x40000000;
int *YHW = (int *)0x40010000;

//DMA addresses
#define MEM_BASE_ADDR 0x01000000
#define TX_BUFFER_BASE (MEM_BASE_ADDR + 0x00100000)


void init_core() {
	int status = 0;

	// init CC core
	cCLabel_cfg = XCclabel_LookupConfig(XPAR_CCLABEL_0_DEVICE_ID);
	if (!cCLabel_cfg) {
		xil_printf("Error loading config\r\n");
	}
	else {
		status = XCclabel_CfgInitialize(&cCLabel,cCLabel_cfg);
		if (status != XST_SUCCESS) {
			xil_printf("Error initializing CC core\r\n");
		}
	}

	//init DMA
	axiDMA_cfg = XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
	if(axiDMA_cfg) {
		status = XAxiDma_CfgInitialize(&axiDMA, axiDMA_cfg);
		if(status != XST_SUCCESS) {
			xil_printf("Error initializing DMA\r\n");
		}
	}

	//Disable Interrupts
	XAxiDma_IntrDisable(&axiDMA, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&axiDMA, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);
}

#endif
