
#include "signals_unity_bridge.h"
#include "cwipc_codec/include/api.h"

#include "CapturSUBThread.h"
#include <QtDebug>

#define STAR_PCL_DEBUG 0 // 500

#define IMPORT(name) ((decltype(name)*)SDL_LoadFunction(lib, # name))
QMutex mutexA;
bool stopThreadsA = false;


CapturSUBThread::CapturSUBThread()
    : QThread()
    , uID(0)
    , doStop(false)
	, iNumPoints(0)
	, mypcl(0)
	, iNumReads(1)
{
    qDebug("Constructor CapturSUBThread ");
	size_t  iSizeB = 1048576 * sizeof(cwipc_point) * 4;
	mypcl = (cwipc_point*)malloc(iSizeB);
	memset(mypcl, 0, iSizeB);
	qDebug() << QString("*********   Constructor  uID=%2 mypcl=%3 size=%4  cwipc_point=%5").arg(uID).arg((qlonglong)mypcl).arg(_msize(mypcl)).arg(sizeof(cwipc_point));

	dst = (uint8_t*)malloc(iSizeB);
	memset(dst, 0, iSizeB);

	timestampInfo = (FrameInfo*)malloc(1048576 * 4 * sizeof(FrameInfo));
	memset(timestampInfo, 0, 1048576 * 2 * sizeof(FrameInfo));

	iNumReads = 1;
}

void CapturSUBThread::run()
{
//	QMutexLocker l1(&m_tVectorAccessMutex);
//	doStopM01.lock();
	const std::string mediaUrl2 = "http://vrt-pcl2dash.viaccess-orca.com/loot/vrtogether.mpd";
	char buff1[1024];
    char buff2[64];
    char buff3[64];
	int n1 = 0;
	int iNum = 0;

	QString mediaUrl = QString("http://vrt-pcl2dash.viaccess-orca.com/loot/vrtogether.mpd");
	if (uID == 2)mediaUrl = QString("http://vrt-pcl2dash.viaccess-orca.com/loot/vrtogether.mpd");
	if (uID == 1)mediaUrl = QString("http://vrt-pcl2dash.viaccess-orca.com/longdress/vrtogether.mpd");
	if (uID == 0)mediaUrl = QString("http://vrt-pcl2dash.viaccess-orca.com/redandblack/vrtogether.mpd");

	memset(buff1, 0, 1024);
	memset(buff2, 0, 64);
	memset(buff3, 0, 64);

#if defined( Q_OS_WIN )
    SetDllDirectory(L"D:/i2cat_vrtogether/v30_stable_qt5/getSUB/w64");
#endif
	uint usize = GetDllDirectoryA(1024, buff1);
	qDebug() << QString("DLLdir=%1   th=%2").arg(buff1).arg(uID);

	QFile myFile("signals-unity-bridge.dll");
	QDir myDir;
    QString aasd = myDir.absoluteFilePath("signals-unity-bridge.dll");
	qDebug() << QString("path=%1  th=%2 ").arg(aasd).arg(uID);
	QLibrary library(aasd);
	library.setFileName(aasd);

	qDebug() << QString(".... %1 ....  th=%2 ").arg(library.fileName()).arg(uID);

	if (!library.load()) { qDebug() << library.errorString(); doStopM01.unlock(); exit(0); }
	if (library.load())qDebug() << QString("signals-unity-bridge library loaded.............  th=%1 ").arg(uID);


	func_sub_create = (sub_create)library.resolve("sub_create");

	func_sub_destroy = (sub_destroy)library.resolve("sub_destroy");

	func_sub_get_stream_count = (sub_get_stream_count)library.resolve("sub_get_stream_count");

	func_sub_play = (sub_play)library.resolve("sub_play");

	func_sub_grab_frame = (sub_grab_frame)library.resolve("sub_grab_frame");

	info = (FrameInfo*)malloc(sizeof(FrameInfo));
	int streamIndex = 0;

		doStopM01.lock();//----------------------------- lock --------------------------
	itoa(uID, buff3, 10);
    strcpy_s(buff2, 64, "MyMediaPipeline");
    strcat_s(buff2, buff3);
    auto handle = func_sub_create(buff2);
//	auto handle = func_sub_create("MyMediaPipeline");

	strcpy_s(buff1, 1024, mediaUrl.toLocal8Bit());
    qDebug() << QString("buff1=%1  th=%2 buff2=%3 ").arg(buff1).arg(uID).arg(buff2);
	bool bRes = func_sub_play(handle, buff1);
		doStopM01.unlock();//--------------------------- unlock ------------------------------

	size_t iSize = 0;
	size_t iSizeB = 0;
	uint iNumPLY = 0;



    while(1)
    {
        doStopMutex.lock();
        if(doStop)
        {
            qDebug() << QString("STOP in while .................... %1 %2").arg(doStop).arg(uID);
            doStopMutex.unlock();

            break;
        }
        doStopMutex.unlock();


		doStopM01.lock();
		myTimer.start();
		Sleep(DELAY);


		n1++;

		iNum = 0;
		iSize = 1048576 * 2;
        streamIndex = 0;
		iSize = (size_t)func_sub_grab_frame(handle, streamIndex, 0, 0, info);
				//QString msg01 = QString("First  iSize_compresed= %1  th=%2").arg( (int)iSize ).arg(uID);
				//qDebug() << msg01;
				if (uID == 0)theGLMessageTh->setSizePCL1comp(iSize);
				if (uID == 1)theGLMessageTh->setSizePCL2comp(iSize);
				if (uID == 2)theGLMessageTh->setSizePCL3comp(iSize);

		if (iSize > 0)
		{
			iSizeB = (size_t)func_sub_grab_frame(handle, streamIndex, dst, iSize, info);
					//	qDebug() << QString("CapturSUBThread::run   iSizeB_compresed_readed=%1    uID=%2 n1=%3 ").arg(iSizeB).arg(uID).arg(n1);
						if (uID == 0)theGLMessageTh->setReadedPCL1comp(iSize);
						if (uID == 1)theGLMessageTh->setReadedPCL2comp(iSize);
						if (uID == 2)theGLMessageTh->setReadedPCL3comp(iSize);

			
			if (iSizeB > 0) {
				//
				// Uncompress
				//
				cwipc_decoder *decoder = cwipc_new_decoder();
				if (decoder == NULL) {
					qDebug() << "CapturSUBThread" << ": Could not create decoder \n";
					doStopMutex.lock();
					doStop = true;
					doStopMutex.unlock();
					//				return 1;
				}
				decoder->feed((void*)dst, iSizeB);
				//			free((uint8_t *)dst); // After feed() we can free the input buffer

				bool ok = decoder->available(true);
				if (!ok) {
					qDebug() << "CapturSUBthread" << ": Decoder did not create pointcloud \n";
					doStopMutex.lock();
					doStop = true;
					doStopMutex.unlock();
					//				return 1;
				}
				cwipc *pc = decoder->get();
				if (pc == NULL) {
					qDebug() << "CapturSUBThread" << ": Decoder did not return cwipc \n";
					doStopMutex.lock();
					doStop = true;
					doStopMutex.unlock();
					//				return 1;
				}

				decoder->free(); // We don't need the decoder anymore
				if (pc) {
					int isizepcl = pc->get_uncompressed_size(CWIPC_POINT_VERSION);
					iNum = pc->copy_uncompressed(mypcl, isizepcl);
					timestampInfo->timestamp = info->timestamp;
			//		qDebug() << QString("CapturSUBThread::run  _________ isizepcl=%1 nelems=%2 iNum_readed=%3  uID=%4 mypcl=%5").arg(isizepcl).arg(isizepcl / sizeof(cwipc_point)).arg(iNum).arg(uID).arg((qlonglong)mypcl);
					if (uID == 0)theGLMessageTh->setUncomp1(iNum);
					if (uID == 1)theGLMessageTh->setUncomp1(iNum);
					if (uID == 2)theGLMessageTh->setUncomp1(iNum);


												//
												// Save pointcloud file
												//
					//char filename[128];
					//sprintf_s(filename, "D:/i2cat_vrtogether/v30_stable_qt5/getSUB/w64/ply/myply_%d.ply", iNumPLY);
					//qDebug() << QString("file=%1 ").arg(filename);
					//if (cwipc_write(filename, pc, NULL) < 0) {
					//	qDebug() << filename << ": Error writing PLY file " << filename ;
					//	exit(0) ;
					//}
					//iNumPLY++;

					pc->free(); // We no longer need to pointcloud

				}
			}
		}
		iNumPoints = iNum;
		myTimer.stop();
		double dTime = myTimer.getElapsedTimeInMilliSec();

		doStopM01.unlock();
    }// while(1)

	free(dst);
	dst = 0;
	free(mypcl);
	mypcl = 0;
	func_sub_destroy(handle);
    qDebug() << QString("Thread  OUT ......  uID=%1 ").arg(uID);
}

void CapturSUBThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    doStop=true;
    qDebug() << QString("CapturSUBThread    STOP .................... %1 uID=%2 ").arg(doStop).arg(uID);
}


void CapturSUBThread::unStop()
{
    QMutexLocker locker(&doStopMutex);
    doStop=false;
    qDebug() << QString("CapturSUBThread    unSTOP .................... %1 iID=%2 ").arg(doStop).arg(uID);
}




// set BOOST_ROOT="/home/juanpinto/boost_1_56_0"
// set BOOST_INCLUDEDIR="/home/juanpinto/boost_1_56_0/include"
// set BOOST_LIBRARYDIR="/home/juanpinto/boost_1_56_0/lib"
// set(BOOST_ROOT "/home/juanpinto/boost_1_56_0")
// set(BOOST_INCLUDEDIR "/home/juanpinto/boost_1_56_0/include")
// set(BOOST_LIBRARYDIR "/home/juanpinto/boost_1_56_0/lib")


//cmake -DBoost_NO_BOOST_CMAKE=TRUE -DBoost_NO_SYSTEM_PATHS=TRUE -DBOOST_ROOT:PATHNAME=/home/juanpinto/boost_1_56_0 -DBoost_LIBRARY_DIRS:FILEPATH=/home/juanpinto/boost_1_56_0/lib -DBoost_INCLUDE_DIR

/*
set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "/home/juanpinto/boost_1_56_0")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)
find_package(Boost REQUIRED regex date_time system filesystem thread graph program_options)
include_directories(${BOOST_INCLUDE_DIRS})


sudo apt-get install libboost-all-dev
/usr/include/boost/

*/
