/*
current error:
2016-5-26 00:00:10 : 连续点击发送时会导致卡死&发送后不延时直接关闭串口数据可能未发送
*/
/*
Modified:
2015-10-27 11:41:23 :   finish basic frame:
						write serial function works well
						read  serial function can read from port but don't know whether exists loss packets
						new->delete new->delete need 10ms period
*/
/*
instructions:
instant class
->start begin read & write thread
->write
->read
delete when finish use
the buf size can be modified: const int maxRxTxBufSize = 1024;
*/
#ifndef _HFSERIALPORT_HPP_
#define _HFSERIALPORT_HPP_
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
namespace HF{
	using namespace std;
	template<class cl=int>
	class SerialPort
	{
	public:
		SerialPort(LPCTSTR ComName = _T("COM1"), int BaudRate = 9600, int ByteSize = 8, int StopBits = 1, int fParity = TRUE, int fNull = TRUE, int Parity = 0);
		~SerialPort();
		void Start(){
			StartReadHandler();
			StartWriteHandler();
		}
		void Write(char* data, int len){
			ToQueue(data, len);
		}
		int Read(char* data, int len){
			return OutQueue(data, len);
		}
		void StartReadHandler(){
			r_running_status = TRUE;
			r_exit = FALSE;
			thread t1([&](){ReadPort(); });
			t1.detach();
		}
		void StartWriteHandler(){
			w_running_status = TRUE;
			w_exit = FALSE;
			thread t1([&](){WritePort(); });
			t1.detach();
		}

	private:
		bool WritePort();
		bool ReadPort();
		void ToQueue(char *a, int size)
		{
			write_mtx.lock();
			for (int i = 0; i < size; i++, a++)
				TxQue.push(*a);
			write_mtx.unlock();
			condition_write.notify_one();
		}
		int OutQueue(char *a, int size)
		{
			int i = 0;
			read_mutex.lock();
			for (i; i < size && !RxQue.empty(); i++, a++)
			{
				*a = RxQue.front();
				RxQue.pop();
			}
			read_mutex.unlock();
			return i;	//real read byte
		}
	private:
		const int maxRxTxBufSize = 10240;
		HANDLE hComm;
		DCB dcb;
		queue<char> TxQue;
		queue<char> RxQue;
		OVERLAPPED rOverlapped;
		OVERLAPPED wOverlapped;
		mutex write_mtx, out_mutex, read_mutex;
		condition_variable condition_write;
		BOOL r_running_status, w_running_status;	//r/w thread running status
		BOOL r_exit, w_exit;						//r/w thread exit status
		char recvBuf[10240];
	};
	template<class cl = int>
	SerialPort<cl>::SerialPort(LPCTSTR ComName, int BaudRate, int ByteSize, int StopBits, int fParity, int fNull, int Parity)
	{
		hComm = CreateFile(ComName,											//串口号字符串
			GENERIC_READ | GENERIC_WRITE,									//读写模式
			NULL, NULL,
			OPEN_EXISTING,													//指定打开已存在的设备
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,					//异步读写
			NULL);
		if (hComm == NULL) MessageBox(NULL, _T("打开串口失败"), _T("error"), MB_OK);
		GetCommState(hComm, &dcb);											//获得默认串口属性
		dcb.BaudRate = BaudRate;											//修改串口波特率，一般为9600
		dcb.ByteSize = ByteSize;											//修改串口数据帧位长度，一般为8位
		dcb.StopBits = StopBits;											//修改串口数据帧停止位长度，一般为1位
		dcb.fParity = fParity;												//修改串口是否采用检验
		dcb.fNull = fNull;													//设置串口是否传输NULL
		dcb.Parity = Parity;												//修改通讯检验方式，一般为none/odd/even
		SetCommState(hComm, &dcb);
		SetupComm(hComm, maxRxTxBufSize, maxRxTxBufSize);							//将输入输出缓冲区大小设为1024
		SetCommMask(hComm, EV_RXCHAR);							//设置串口发送屏蔽字对串口收发数据事件进行控制，此处是直接发送监视接收屏蔽字为EV_RXCHAR
		memset(&wOverlapped, 0, sizeof(wOverlapped));
		memset(&rOverlapped, 0, sizeof(rOverlapped));
		wOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		rOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
	template<class cl = int>
	SerialPort<cl>::~SerialPort()
	{
		while (r_running_status)r_running_status = FALSE;
		while (w_running_status)w_running_status = FALSE;
		condition_write.notify_one();
		while (!w_exit || !r_exit);
		CloseHandle(wOverlapped.hEvent);
		CloseHandle(rOverlapped.hEvent);
		CloseHandle(hComm);
	}
	template<class cl = int>
	bool SerialPort<cl>::WritePort()
	{
		DWORD dwBytes;
		unique_lock<mutex> lck(out_mutex);
		while (w_running_status)
		{
			if (TxQue.empty())
			{
				condition_write.wait(lck, [&]()->bool{return (!TxQue.empty()) || (!w_running_status); });
				if (!w_running_status)
					break;
			}
			write_mtx.lock();
			char send = TxQue.front();
			write_mtx.unlock();
			if (!WriteFile(hComm, (LPVOID)&send, 1, &dwBytes, &wOverlapped))
			{
				if (GetLastError() == ERROR_IO_PENDING)
				{
					DWORD tState = WaitForSingleObject(wOverlapped.hEvent, 1000);
					if (tState != 0x0) MessageBox(NULL, _T("Write Failed!"), _T("error"), MB_OK);
				}
				else
				{
					return false;
				}
			}
			write_mtx.lock();
			TxQue.pop();
			write_mtx.unlock();
		}
		w_exit = TRUE;
		return true;
	}
	template<class cl = int>
	bool SerialPort<cl>::ReadPort()
	{
		DWORD dwEvt, dwErr, dwByte = 0;
		memset(&rOverlapped, 0, sizeof(rOverlapped));
		rOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		while (r_running_status)
		{
			WaitCommEvent(hComm, &dwEvt, &rOverlapped);
			if (WaitForSingleObject(rOverlapped.hEvent, 100) == WAIT_OBJECT_0)
			{
				if (dwEvt == EV_RXCHAR)
				{
					COMSTAT comstat;
					memset(&comstat, 0, sizeof(comstat));
					ClearCommError(hComm, &dwErr, &comstat);
					if (comstat.cbInQue)
					{
						if (!ReadFile(hComm, (LPVOID)(LPCTSTR)recvBuf, comstat.cbInQue, &dwByte, &rOverlapped))
						{
							if (GetLastError() == ERROR_IO_PENDING)
							{
								WaitForSingleObject(rOverlapped.hEvent, 1000);
								if (!dwByte) MessageBox(NULL, _T("ReadPort Failed!"), _T("error"), MB_OK);
							}
						}
					}
				}
			}
			if (dwByte)
			{
				//cout << recvBuf;
				read_mutex.lock();
				for (int i = 0; i < dwByte; i++)
					RxQue.push(recvBuf[i]);
				while (RxQue.size()>maxRxTxBufSize)
					RxQue.pop();
				read_mutex.unlock();
			}
		}
		r_exit = TRUE;
		return true;
	}
}
#endif
