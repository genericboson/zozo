#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

#include <boost/json.hpp>

#include <Engine/Singleton.h>
#include <Engine/StaticData/IStaticData.h>

namespace GenericBoson
{
	// 정적 데이터의 "프로토타입 레지스트리".
	//
	// 생성된 .cpp 파일의 GlobalInitializer가 프로그램 시작 시(static 초기화)
	// 클래스마다 프로토타입 하나씩을 여기에 등록한다.
	// 이후 json을 읽을 때 CLASS_ID로 프로토타입을 찾아 Create()로 행 객체를 만들고,
	// Insert()가 그 행을 자기 타입의 DataManager에 담는다.
	class StaticDataManager : public Singleton<StaticDataManager>
	{
	public:
		bool InsertStaticData(int64_t classId, std::shared_ptr<IStaticData>&& pNewStaticData);

		// classId에 등록된 프로토타입으로 행 객체를 하나 만든다.
		// 등록되지 않은 classId면 nullptr.
		std::shared_ptr<IStaticData> CreateStaticData(int64_t classId) const;

	private:
		std::unordered_map<int64_t, std::shared_ptr<IStaticData>> m_data;
	};
}
