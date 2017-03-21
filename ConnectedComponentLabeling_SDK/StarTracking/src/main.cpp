#include <xparameters.h>
#include "xCCLabel.h"
#include "xaxidma.h"
#include "platform.h"
#include "AxiTimerHelper.h"
#include "Image.h"
#include "CentroiderSW.h"
#include "CentroiderHW.h"
#include "Algorithm.h"
#include "Database.h"
#include "StarPatternDatabase.h"

#define FOV 256
#define TOLERANCE 1

int main() {
	init_platform();

	//Initialize
	init_core();
	XCclabel_EnableAutoRestart(&cCLabel);

	//Timer
	AxiTimerHelper timer;

	/********************************************** CC Labeling SW ****************************************************************/
	timer.startTimer();
	u32 centroidCountSW = softwareCCLabel(inputIMG, XSW, YSW);
	timer.stopTimer();
	double swCCLabeltime = timer.getElapsedTimerInSeconds();

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
	timer.startTimer();
	while(!XCclabel_IsDone(&cCLabel));
	timer.stopTimer();
	double hwCCLabeltime = timer.getElapsedTimerInSeconds();

	//Output
	u32 centroidCountHW = XCclabel_Get_return(&cCLabel);

	/********************************************** Algorithm ****************************************************************/
	timer.startTimer();
	std::vector<Star> starList = chooseStarRef(XHW, YHW, centroidCountHW, IMG_HEIGHT, IMG_WIDTH);
	timer.stopTimer();
	double chooseStarRefTime = timer.getElapsedTimerInSeconds();

	timer.startTimer();
	StarPattern sPattern = getStarPattern(starList,FOV);
	timer.stopTimer();
	double getStarPatternTime = timer.getElapsedTimerInSeconds();

	/********************************************** Matching ****************************************************************/
	//Build Tree
	timer.startTimer();
	NodePtr root = buildTree(database);
	timer.stopTimer();
	double buildTreeTime = timer.getElapsedTimerInSeconds();

	timer.startTimer();
	int res1 = searchLin(database, TOLERANCE, sPattern.N, sPattern.d1, sPattern.d2, sPattern.d3);
	timer.stopTimer();
	double linSearchTime = timer.getElapsedTimerInSeconds();

	timer.startTimer();
	int res2 = searchTolerance(root, TOLERANCE, sPattern.N, sPattern.d1, sPattern.d2, sPattern.d3);
	timer.stopTimer();
	double treeSearchTime = timer.getElapsedTimerInSeconds();

	/********************************************** CHeck results and runtime ****************************************************************/
	xil_printf("\r\n --------------- Results --------------- \r\n");
	if(verifyResult(centroidCountSW, XSW, YSW, centroidCountHW, XHW, YHW))
		xil_printf("SW - HW Centroid result: Matched \r\n");
	else
		xil_printf("SW - HW Centroid result: Unmatched \r\n");
	if(res1 != -1) {
		if(res1 == res2)
			xil_printf("Star ID return: %d \r\n", res1);
		else
			xil_printf("Star ID return: %d %d\r\n", res1, res2);
	}
	else
		xil_printf("No star ID matched \r\n");

	xil_printf("--------------- Runtime --------------- \r\n");
	xil_printf("Build tree runtime: %d us\r\n", (unsigned)(buildTreeTime * 1000000));
	xil_printf("CCLAbel SW runtime: %d us -- HW runtime: %d us\r\n", (unsigned)(swCCLabeltime * 1000000), (unsigned)(hwCCLabeltime * 1000000));
	xil_printf("Choose reference star runtime: %d us\r\n", (unsigned)(chooseStarRefTime * 1000000));
	xil_printf("Find the star pattern runtime: %d us\r\n", (unsigned)(getStarPatternTime * 1000000));
	xil_printf("Linear search runtime: %d us -- Tree database search runtime: %d us\r\n", (unsigned)(linSearchTime * 1000000), (unsigned)(treeSearchTime * 1000000));

	xil_printf("---------- !!! SUCESS !!! ----------\r\n");

	cleanup_platform();
	return 0;
}