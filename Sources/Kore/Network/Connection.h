#pragma once

#include <Kore/Network/Socket.h>

namespace Kore {

	class Connection {
	public:
		enum State {
			Disconnected = 0,
			Connected = 1,
		};

		State state;
		double ping;
		bool congested;

		Connection(const char* url, int sendPort, int receivePort, double timeout = 10, double pngInterv = 1, double resndInterv = 0.2, double congestPing = 0.2, float congestShare = 0.5, int buffSize = 256, int cacheCount = 20);
		~Connection();

		void send(const u8* data, int size, bool reliable = true);
		int receive(u8* data);

	private:
		enum ControlType {
			Ping = 0,
			Pong = 1
		};

		const int sndPort;
		const int recPort;
		const char* url;
		Kore::Socket socket;

		int buffSize;
		int cacheCount;
		u32 lastSndNrRel;
		u32 lastSndNrURel;
		u32 lastAckNrRel;
		u32 lastRecNrRel;
		u32 lastRecNrURel;
		u32 congestBits;
		u8* recBuff;
		u8* recCache;
		u8* sndBuff;
		u8* sndCache;

		float congestShare;
		double timeout;
		double pngInterv;
		double resndInterv;
		double congestPing;
		double lastRec;
		double lastPng;

		void send(const u8* data, int size, bool reliable, bool control);
		bool checkSeqNr(u32 next, u32 last);
		void processControlMessage();
		int processMessage(int size, u8* returnBuffer);
		void reset();
	};
}