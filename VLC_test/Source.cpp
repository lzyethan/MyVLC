#include "Properties.h"


int main(int argc, char** argv)
{
	// create the signals to use in correlation
	/*vector<float> zeroSignal, oneSignal;
	for (int i = 0; i < 30; i++)
	{
		zeroSignal.push_back(sin(2 * MM_PI * FREQ[ZERO] * i / 30));
		oneSignal.push_back(sin(2 * MM_PI * FREQ[ONE] * i / 30));
		cout << zeroSignal[i] << "\t" << oneSignal[i] << endl;
	}*/
	//Utilities::testVideoBackGround("..\\Release\\revised\\20141216_101410_1275875420_long_testtestrand_12Hz_9Hz_1000ms_001levels_I420_Tree24avi_output.mp4",
	//	"masks.avi",15,10,20);
	return Properties::getInst()->testSendReceive(argc, argv);
	//BCH bch;
	//bch.testBCH();
	//MyHamming myHamming;
	//ReedSolomon MyReed;
	//vector<short> msg;
	//for (int i = 0; i < 40; i++)
	//{
	//	msg.push_back(rand() & 1);
	//	//cout << msg[i];
	//}
	//cout << endl;
	//vector<short> result = MyReed.encode_bit_stream(msg);
	//for (int i = 0; i < result.size(); i++)
	//{
	//	cout << result[i];
	//}
	//cout << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	result[i % result.size()] = ((~result[i % 40]) & 1);
	//}
	//for (int i = 0; i < result.size(); i++)
	//{
	//	cout << result[i];
	//}
	//cout << endl;
	//vector<short> decoded = MyReed.decode_bit_stream(result);
	//for (int i = 0; i < 40; i++)
	//{
	//	cout << msg[i];
	//}
	//cout << endl;

	//for (int i = 0; i < 40; i++)
	//{
	//	cout <<decoded[i];
	//}
	//cout << endl;
	//Utilities::LCS_greedy(msg, decoded);
	//Mat test = VLCCalibration::createChessBoard(0.9, cv::Size(4,4));
	//imshow("test", test);
	//cv::waitKey(0);

	//VLCCalibration::detectMyBoard(test, cv::Size(4,4));
	
	return 0;
}