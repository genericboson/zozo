#pragma once

#include <cstdint>
#include <string>

#include <boost/json.hpp>

namespace GenericBoson::StaticDataParse
{
	// 생성된 정적 데이터 클래스의 Insert()가 쓰는 파싱 헬퍼.
	// 키가 없거나 타입이 맞지 않으면 값을 건드리지 않고 false를 반환한다
	// (멤버는 선언 시점의 기본값을 유지한다).

	inline bool Read(const boost::json::object& obj, const char* pKey, int32_t& out)
	{
		const auto found = obj.find(pKey);
		if (found == obj.end() || !found->value().is_number())
			return false;

		out = static_cast<int32_t>(found->value().to_number<int64_t>());
		return true;
	}

	inline bool Read(const boost::json::object& obj, const char* pKey, int64_t& out)
	{
		const auto found = obj.find(pKey);
		if (found == obj.end() || !found->value().is_number())
			return false;

		out = found->value().to_number<int64_t>();
		return true;
	}

	inline bool Read(const boost::json::object& obj, const char* pKey, float& out)
	{
		const auto found = obj.find(pKey);
		if (found == obj.end() || !found->value().is_number())
			return false;

		out = static_cast<float>(found->value().to_number<double>());
		return true;
	}

	inline bool Read(const boost::json::object& obj, const char* pKey, double& out)
	{
		const auto found = obj.find(pKey);
		if (found == obj.end() || !found->value().is_number())
			return false;

		out = found->value().to_number<double>();
		return true;
	}

	inline bool Read(const boost::json::object& obj, const char* pKey, bool& out)
	{
		const auto found = obj.find(pKey);
		if (found == obj.end() || !found->value().is_bool())
			return false;

		out = found->value().as_bool();
		return true;
	}

	inline bool Read(const boost::json::object& obj, const char* pKey, std::string& out)
	{
		const auto found = obj.find(pKey);
		if (found == obj.end() || !found->value().is_string())
			return false;

		const auto& str = found->value().as_string();
		out.assign(str.data(), str.size());
		return true;
	}
}
