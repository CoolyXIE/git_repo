#include "stdafx.h"
#include "FeatureMatchThr.h"
#include "MomStation.h"

CFeatureMatchThr::CFeatureMatchThr()
{

}

CFeatureMatchThr::~CFeatureMatchThr()
{

}

int CFeatureMatchThr::ThreadFun()
{
    WaitForSingleObject(gGetMomStation()->GetFeatureDetQueSemaphore(), 10);

	if (!gGetMomStation()->GetFeatureDetQue()->IsEmpty())
	{
		CFeaturePointPatten pointPattenDes = gGetMomStation()->GetFeatureDetQue()->Top();

		CMyTimer time;
		time.Reset();

		//CFeaturePointPatten  descriptors;
		m_f2d_des->compute(pointPattenDes.m_matImage, pointPattenDes.m_vecKeyPoint, pointPattenDes.m_matDescriptor);

		CString str;
		str.Format("%.2f ms", time.GetTimeMilli());//¼ÆÊ±

		gGetMomStation()->GetDeatureDesQue()->Push(pointPattenDes);
		ReleaseSemaphore(gGetMomStation()->GetDescribeQueSemaphore(), 1, NULL);

		gGetMomStation()->GetFeatureDetQue()->Pop();
	}
	return 0;
}
