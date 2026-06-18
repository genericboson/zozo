#pragma once

namespace GenericBoson
{
	class IStaticData
	{
	public:
		virtual std::shared_ptr<IStaticData> Clone() const = 0;
	};
}