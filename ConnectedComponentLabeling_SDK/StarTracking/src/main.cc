#include <xparameters.h>
#include "xCCLabel.h"
#include "xaxidma.h"
#include "platform.h"
#include "AxiTimerHelper.h"
#include "Image.h"
#include "CentroiderHW.h"
#include "Algorithm.h"
#include <iostream>

#define FOV 256
using namespace std;
int main() {
	init_platform();

	//Initialize
	init_core();
	XCclabel_EnableAutoRestart(&cCLabel);

	//Timer
	AxiTimerHelper timer;

	/********************************************** CC Labeling HW ****************************************************************/
	//Set parameters
	XCclabel_Set_imgHeight(&cCLabel, IMG_HEIGHT);
	XCclabel_Set_imgWidth(&cCLabel, IMG_WIDTH);

	//Flush the cache of the buffers
	Xil_DCacheFlushRange((u32)inputIMG, IMG_HEIGHT * IMG_WIDTH * sizeof(int));

	//Send data to IP core
	XAxiDma_SimpleTransfer(&axiDMA, (u32)inputIMG, IMG_HEIGHT * IMG_WIDTH * sizeof(int), XAXIDMA_DMA_TO_DEVICE);

	//Start IP core
	XCclabel_Start(&cCLabel);

	// Wait until it's done
	while(!XCclabel_IsDone(&cCLabel));

	//Output
	u32 centroidCountHW = XCclabel_Get_return(&cCLabel);

	/********************************************** Algorithm ****************************************************************/
	std::vector<Star> starList = chooseStarRef(XHW, YHW, centroidCountHW, IMG_HEIGHT, IMG_WIDTH);
	StarPattern sPattern = getStarPattern(starList,FOV);

	/********************************************** Matching ****************************************************************/




	cleanup_platform();
	return 0;
}
