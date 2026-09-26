#pragma once

#include <memory>

#include <boost/json.hpp>

namespace GenericBoson
{
	class IStaticData
	{
	public:
		virtual ~IStaticData() = default;

		// json 행 하나를 파싱해 자기 자신을 채우고,
		// 자기 타입의 DataManager에 스스로를 등록한다.
		virtual void Insert(const boost::json::object& obj) = 0;

		// 같은 타입의 빈 객체를 하나 만든다(프로토타입 패턴).
		virtual std::shared_ptr<IStaticData> Create() = 0;
	};
}
