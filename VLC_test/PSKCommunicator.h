#pragma once
#include "Communicator.h"
class PSKCommunicator :
	public Communicator
{
public:
	virtual string getVideoName(string outputVideoFile)
	{
		return "_PSK_" + outputVideoFile;
	}

	//Creat wave forms that will be embedded into the video or image
	virtual void initCommunication()
	{
		//The createWaveGivenFPS will deal with the msg and output a wave which to be inserted into the vector list
		amplitudes.push_back(WaveGenerator::createWaveGivenFPS(msg, 6));

		for (int i = 0; i < msg.size(); i++)
		{
			msg[i].amplitude = -msg[i].amplitude;
		}
		//amplitudes[1]
		amplitudes.push_back(WaveGenerator::createWaveGivenFPS(msg, 6));

		// 2 divisions, 1% to crop from the image, crop this percentage from the whole frame then divide, 
		ROIs = Utilities::getDivisions(2, 1, false, globalROI, true);
	}
	virtual void sendImageMainLoop()
	{
		for (int i = 0; i < amplitudes[0].size(); i++)
		{
			//Cloning the image object into new object for modification
			Mat frame = img.clone();

			Utilities::updateFrameLuminance(frame, ROIs[0], amplitudes[0][i]);
			Utilities::updateFrameLuminance(frame, ROIs[1], amplitudes[1][i]);

			//Using video writer object  "vidWriter" to write the frame to the output video
			vidWriter << frame;
		}
	}
	virtual void sendVideoMainLoop()
	{

	}
	vector<short> receive(string fileName, double ROI_Ratio)
	{
		int fps = 0;
		vector<vector<float> > frames = Utilities::getVideoFrameLuminancesSplitted(fileName, ROI_Ratio, fps, 2, true);
		vector<float> amplitude_difference;

		for (int i = 0; i < frames[0].size(); i++)
		{
			amplitude_difference.push_back(frames[0][i] - frames[1][i]);
		}
		return receive2(amplitude_difference, fps);
	}
	PSKCommunicator();
	~PSKCommunicator();
};
