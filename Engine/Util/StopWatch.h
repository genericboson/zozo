#pragma once

using namespace std::chrono_literals;

namespace GenericBoson
{
	template <typename CALLABLE>
	class StopWatch final
	{
	public:
		StopWatch(CALLABLE&& OnEnd)
			: m_onEnd{ std::forward<CALLABLE>(OnEnd) }
		{
			m_startTime = std::chrono::steady_clock::now();
		}

		~StopWatch()
		{
			const auto endTime = std::chrono::steady_clock::now();
			m_onEnd(std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_startTime));
		}

	private:
		std::chrono::steady_clock::time_point m_startTime;
		const CALLABLE                        m_onEnd;
	};
}