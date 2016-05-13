#pragma once
#include <vector>
#include "AnimFrame.h"
#include "LogHandler.h"

struct AnimationData//undocced
{
	friend class Animation;
	private:
	bool loop;
	std::vector<AnimFrame> frames;
	bool realTime;
	double duration;
	void recalculateDuration();

	inline double getWidth(int i)
	{
		return frames[i].w;
	}
	inline double getHeight(int i)
	{
		return frames[i].h;
	}
	inline double getFromX(int i)
	{
		return frames[i].x1;
	}
	inline double getFromY(int i)
	{
		return frames[i].y1;
	}
	inline double getToX(int i)
	{
		return frames[i].x2;
	}
	inline double getToY(int i)
	{
		return frames[i].y2;
	}

	public:
	AnimationData(bool rt=0);
	inline void setLoop()
	{
		loop=1;
	}
	inline void unsetLoop()
	{
		loop=0;
	}
	inline bool getLoop()
	{
		return loop;
	}
	inline bool getRealTime()
	{
		return realTime;
	}
	inline void addFrame(double x,double y,double w,double h,double duration=1)
	{
		frames.push_back(AnimFrame(x,y,x+w,y+h,duration));
		recalculateDuration();
	}
	/*inline AnimFrame getFrame(int i)
	{
		return frames[i];
	}*/
	inline double getDuration()
	{
		return duration;
	}
	inline unsigned int getFrames()
	{
		return frames.size();
	}
	int getFrameAt(double pos);
	void addFrameStrip(double x,double y,double w,double h,int imagesx,int start,int length,double duration=1);
	void setFrameDuration(unsigned int i,double dur);
	~AnimationData();
};
