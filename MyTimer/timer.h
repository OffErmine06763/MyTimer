#pragma once
#include <chrono>
#include <iostream>

#define START_TIMER			utils::timer::start()
#define SET_CHECKPOINT		utils::timer::setCheckpoint()
#define GET_ELAPSED			utils::timer::getElapsedTime()
#define GET_TOTOAL			utils::timer::getTotalTime()
#ifdef DEBUG
#define EXECUTION_TIME		utils::timer::totalTime()
#define ELAPSED_TIME(title) utils::timer::elapsedTime(title)
#else // RELEASE
#define EXECUTION_TIME 
#define ELAPSED_TIME(title) 
#endif // DEBUG

namespace utils
{
	namespace timer
	{
		int64_t startMs = 0, checkpointMs = 0;

		void start()
		{
			startMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			checkpointMs = startMs;
		}

		void setCheckpoint()
		{
			checkpointMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		}

		uint64_t  elapsedTime(std::string title = "")
		{
			int64_t nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			std::cout << "ELAPSED TIME";
			if (title.length() != 0)
				std::cout << " - " << title;
			uint64_t et = nowMs - checkpointMs;
			std::cout << ": " << et << '\n';
			checkpointMs = nowMs;
			return et;
		}

		void totalTime()
		{
			int64_t endMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			std::cout << "EXECUTION TIME: " << endMs - startMs << '\n';
		}

		uint64_t getTotalTime()
		{
			int64_t endMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			return  endMs - startMs;
		}

		int64_t getElapsedTime()
		{
			int64_t old = checkpointMs;
			checkpointMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			return checkpointMs - old;
		}
	}
}